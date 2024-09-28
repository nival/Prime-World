#include "ThreadManager.h"
#include "LockFreeStack.h"
#include "../get_tick_count.h"
#include "../sleep.h"
#include "../Asserts.h"

#include <boost/thread.hpp>
#include <list>

namespace nvl {
namespace node {

    class CEventNode;

    struct CEventNodesContainer: IEntity, CLFStack< CEventNode > {

        CEventNodesContainer()
        {}

        ~CEventNodesContainer()
        {}

    };

    typedef CPtr< CEventNodesContainer > CEventNodesContainerPtr;
    typedef CMTEntity< CEventNodesContainer > CEventNodesContainerEntity;

    class CEventNode:
        public CStackableEntity
    {
    public:

        CEventNode(): m_nDeliveryTime( 0 ), m_nPeriod( 0 )
        {}

        void DestroyEntity()
        { delete this; }

        void SendToOwner()
        {
            assert( m_cpOwner.Get() != NULL );

            CPtr< CEventNodesContainer > cpContainer( m_cpOwner.Detach(), attach );
            cpContainer->Push( this );
        }

    public:

        CEventNodesContainerPtr m_cpOwner;
        CEventPtr m_cpEvent;
        CEventsReceiverPtr m_cpSender;
        CEventsReceiverPtr m_cpReceiver;
        uint_t m_nDeliveryTime;
        uint_t m_nPeriod;

    };

    boost::thread_specific_ptr< CEventNodesContainerPtr > g_TLSFreeMessageNodes;

    class CEventsThread:
        public IEventsThread
    {
    public:

        CEventsThread( cstr_t csIdentifier, IThreadManager * pTM ):
            m_pPreparedEventsLast( NULL ), m_cpThreadManager( pTM )
        {
            assert( NULL != pTM );

            if ( csIdentifier )
                m_sIdentifier = csIdentifier;
        }

        ~CEventsThread()
        {
            FreeStack( m_PreparedEvents.PopStack() );
            FreeStack( m_FreeNodes.PopStack() );
            FreeStack( m_EventsNoDelay.PopStack() );
            FreeStack( m_EventsDelay.PopStack() );
        }

        cstr_t GetIdentifier() const
        { return m_sIdentifier.empty() ? NULL : m_sIdentifier.c_str(); }

        result_t Run()
        {
            long nState = STARTING;
            if ( m_ThreadState.compare_exchange_strong( nState, WORKING ) == false )
                return result_wrong_state;

            try {

                CEventNode *pStack = NULL;

                while ( m_ThreadState.load( nstd::memory_order_relaxed ) == WORKING ) {

                    uint_t nCounter = 100;
                    while ( m_PreparedEvents.IsEmpty() == false && --nCounter ) {

                        CEventNode *pNode = m_PreparedEvents.Pop();

                        if ( pNode == m_pPreparedEventsLast )
                            m_pPreparedEventsLast = NULL;

                        assert( pNode->m_cpEvent.Get() != NULL );

                        if ( pNode->m_nPeriod ) {

                            if ( pNode->m_cpEvent->IsCancelled() == false && pNode->m_cpEvent->ProcessEvent( pNode->m_cpSender, pNode->m_cpReceiver ) != result_cancel ) {

                                uint_t nCurrentTick = nival::get_tick_count();
                                while ( static_cast< int >(( pNode->m_nDeliveryTime += pNode->m_nPeriod ) - nCurrentTick ) <= 0 )
                                {}

                                InsertDelayedEvent( pNode );
                                pNode = NULL;

                            } else
                                pNode->m_cpEvent.Release();

                        } else {

                            pNode->m_cpEvent->ProcessEvent( pNode->m_cpSender, pNode->m_cpReceiver );
                            pNode->m_cpEvent.Release();

                        }

                        if ( pNode ) {

                            if ( pNode->m_cpOwner.Get() )
                                pNode->SendToOwner();
                            else
                                m_FreeNodes.Push( pNode );

                        }

                    }

                    if ( m_EventsNoDelay.IsEmpty() == false ) {

                        pStack = m_EventsNoDelay.PopReversedStack();

                        if ( m_pPreparedEventsLast )
                            m_pPreparedEventsLast->SetNextEntity( pStack );
                        else {

                            assert( m_PreparedEvents.IsEmpty() == true );
                            m_PreparedEvents.PushStack( pStack  );

                        }

                        m_pPreparedEventsLast = FindLastStackEntity( pStack );

                    }

                    if ( m_EventsDelay.IsEmpty() == false ) {

                        pStack = m_EventsDelay.PopReversedStack();
                        while ( pStack ) {

                            InsertDelayedEvent( pStack );
                            pStack = pStack->GetNextEntity< CEventNode >();

                        }

                    }

                    if ( m_DelayedEvents.empty() == false ) {

                        CDelayedEventsList::iterator iEnd = m_DelayedEvents.upper_bound( GetTickCount() );
                        if ( m_DelayedEvents.begin() != iEnd ) {

                            for ( CDelayedEventsList::iterator iEvent = m_DelayedEvents.begin(); iEnd != iEvent; ++iEvent ) {

                                if ( m_pPreparedEventsLast )
                                    m_pPreparedEventsLast->SetNextEntity( iEvent->second );

                                m_pPreparedEventsLast = iEvent->second;

                            }

                            m_pPreparedEventsLast->SetNextEntity( NULL );

                            if ( m_PreparedEvents.IsEmpty() )
                                m_PreparedEvents.PushStack( m_DelayedEvents.begin()->second );

                            m_DelayedEvents.erase( m_DelayedEvents.begin(), iEnd );

                        }

                    }

                    if ( m_PreparedEvents.IsEmpty() )
                        nival::sleep( 1 );

                }

            } catch ( std::exception & ) {

                m_ThreadState = FINISHING;
                throw;

            }

            return result_ok;
        }

        result_t Finish()
        {
            long nFlagValue = WORKING;
            return m_ThreadState.compare_exchange_strong( nFlagValue, FINISHING ) ? result_ok : result_wrong_state;
        }

        enumThreadTypes GetThreadType() const
        { return EVENTS_THREAD; }

        result_t SendEvent( IEventsReceiver * pSender, IEventsReceiver * pReceiver, IEvent * pEvent )
        {
            assert( NULL != pReceiver );
            assert( pReceiver->GetOwnThread() == static_cast< IEventsThread * >( this ) );
            assert( NULL != pEvent );

            return result_not_impl;
        }

        result_t PostEvent(
            IEventsReceiver * pSender,
            IEventsReceiver * pReceiver,
            IEvent * pEvent,
            uint_t nDelay,
            uint_t nPeriod )
        {
            assert( NULL != pReceiver );

            if ( GetThreadManager()->GetCurrentThread() == static_cast< IThread * >( pReceiver->GetOwnThread() ) ) {

                if ( nDelay || nPeriod )
                    return Enqueue( pSender, pReceiver, pEvent, nDelay, nPeriod );
                else
                    return Enqueue( pSender, pReceiver, pEvent );

            }

            if ( nDelay || nPeriod )
                return Post( pSender, pReceiver, pEvent, nDelay, nPeriod );

            return Post( pSender, pReceiver, pEvent );
        }

        result_t Post( IEventsReceiver * pSender, IEventsReceiver * pReceiver, IEvent * pEvent )
        {
            assert( NULL != pReceiver );
            assert( NULL != pEvent );
            assert( pEvent->IsMTEntity() == true );

            CEventNode *pNode = AllocMTNode();

            pNode->m_cpEvent = pEvent;
            pNode->m_cpSender = pSender;
            pNode->m_cpReceiver = pReceiver;

            m_EventsNoDelay.Push( pNode );

            return result_ok;
        }

        result_t Enqueue( IEventsReceiver * pSender, IEventsReceiver * pReceiver, IEvent * pEvent )
        {
            assert( NULL != pReceiver );
            assert( NULL != pEvent );
            assert( GetThreadManager()->GetCurrentThread()->GetThreadType() == EVENTS_THREAD );
            assert( static_cast< CEventsThread * >( GetThreadManager()->GetCurrentThread() ) == this );

            CEventNode *pNode = AllocNode();
            pNode->m_cpEvent = pEvent;
            pNode->m_cpSender = pSender;
            pNode->m_cpReceiver = pReceiver;

            if ( m_pPreparedEventsLast ) {

                m_pPreparedEventsLast->SetNextEntity( pNode );
                pNode->SetNextEntity( NULL );

            } else
                m_PreparedEvents.Push( pNode );

            m_pPreparedEventsLast = pNode;

            return result_ok;
        }

        result_t Post( IEventsReceiver * pSender, IEventsReceiver * pReceiver, IEvent * pEvent, uint_t nDelay, uint_t nPeriod )
        {
            assert( NULL != pReceiver );
            assert( NULL != pEvent );
            assert( pEvent->IsMTEntity() == true );

            CEventNode *pNode = AllocMTNode();

            pNode->m_cpEvent = pEvent;
            pNode->m_cpSender = pSender;
            pNode->m_cpReceiver = pReceiver;
            pNode->m_nDeliveryTime = GetTickCount() + nDelay;
            pNode->m_nPeriod = nPeriod;

            m_EventsDelay.Push( pNode );

            return result_ok;
        }

        result_t Enqueue( IEventsReceiver * pSender, IEventsReceiver * pReceiver, IEvent * pEvent, uint_t nDelay, uint_t nPeriod )
        {
            assert( NULL != pReceiver );
            assert( NULL != pEvent );
            assert( GetThreadManager()->GetCurrentThread()->GetThreadType() == EVENTS_THREAD );
            assert( static_cast< CEventsThread * >( GetThreadManager()->GetCurrentThread() ) == this );

            CEventNode *pNode = AllocNode();

            pNode->m_cpEvent = pEvent;
            pNode->m_cpSender = pSender;
            pNode->m_cpReceiver = pReceiver;
            pNode->m_nDeliveryTime = GetTickCount() + nDelay;
            pNode->m_nPeriod = nPeriod;

            InsertDelayedEvent( pNode );

            return result_ok;
        }

        IThreadManager * GetThreadManager() const
        { return m_cpThreadManager; }

    protected:

        CEventNode * AllocNode()
        {
            CEventNode *pNode = m_FreeNodes.Pop();
            if ( NULL == pNode )
                pNode = new CEventNode;

            return pNode;
        }

        static CEventNode * AllocMTNode()
        {
            CEventNodesContainerPtr *pContainer = g_TLSFreeMessageNodes.get();
            if ( NULL == pContainer ) {

                g_TLSFreeMessageNodes.reset( new CEventNodesContainerPtr( new CEventNodesContainerEntity ) );
                pContainer = g_TLSFreeMessageNodes.get();

            }

            CEventNode *pNode = pContainer->Get()->Pop();
            if ( NULL == pNode )
                pNode = new CEventNode;

            pNode->m_cpOwner = pContainer->Get();

            return pNode;
        }

        static void FreeStack( CEventNode *pStack )
        {
            while ( pStack ) {

                CEventNode *pNode = pStack->GetNextEntity< CEventNode >();

                if ( pStack->m_cpOwner.Get() )
                    pStack->SendToOwner();
                else
                    pStack->DestroyEntity();

                pStack = pNode;

            }
        }

        void InsertDelayedEvent( CEventNode * pNode )
        {
            m_DelayedEvents.insert( CDelayedEventsList::value_type( pNode->m_nDeliveryTime, pNode ) );
        }

    private:

        std::string m_sIdentifier;

        CStack< CEventNode > m_FreeNodes;
        CStack< CEventNode > m_PreparedEvents;
        CEventNode * m_pPreparedEventsLast;

        typedef std::multimap< uint_t, CEventNode * > CDelayedEventsList;

        CDelayedEventsList m_DelayedEvents;

        CLFStack< CEventNode > m_EventsNoDelay;
        CLFStack< CEventNode > m_EventsDelay;

        CThreadManagerPtr m_cpThreadManager;

    };

    class CForeignThread:
        public IThread
    {
    public:

        CForeignThread()
        { SetThreadState( WORKING ); }

        cstr_t GetIdentifier() const
        { return "Foreign Thread"; }

        result_t Run()
        { return result_not_impl; }

    };

    class CMainThread:
        public CEventsThread
    {
    public:

        CMainThread( IThreadManager * pTM ): CEventsThread( "Main Thread", pTM )
        {}

        result_t Run()
        {
            if ( GetThreadManager()->GetCurrentThread() != GetThreadManager()->GetMainThread() )
                return result_impossible_action;

            if ( GetThreadState() == FINISHING )
                return result_wrong_state;

            SetThreadState( STARTING );

            m_ExecutionResult = CEventsThread::Run();

            if ( GetThreadState() == FINISHING )
                while ( GetThreadManager()->GetThreadsCount() )
                    nival::yield();

            SetThreadState( FINISHED );

            return result_ok;
        }

        result_t Finish()
        {
            boost::mutex::scoped_lock Locker( m_FinishProtector );

            if ( GetThreadState() == WORKING ) {

                CEventsThread::Finish();
                Locker.unlock();

                GetThreadManager()->Finish();

            }

            return result_already_done;
        }

    private:

        boost::mutex m_FinishProtector;

    };

    boost::thread_specific_ptr< CThreadPtr > g_TLSCurrentThread;

    class CThreadManager:
        public IThreadManager
    {
    public:

        CThreadManager(): m_IsFinishing( 0 ), m_IsMainThreadWorking( 0 )
        {}

        cstr_t GetIdentifier() const
        { return "Thread Manager"; }

        result_t RunMainThread( INodeManager * pNodeManager, IEventsReceiver * pReceiver, IEvent * pFirstEvent )
        {
            assert( NULL != pNodeManager );

            long nFlag = 0;
            if ( m_IsMainThreadWorking.compare_exchange_strong( nFlag, 1 ) ) {

                CThreadManagerPtr cpGuard( this );

                m_cpMainThread = new CMTEntity< CMainThread >( this );
                g_TLSCurrentThread.reset( new CThreadPtr( m_cpMainThread ) );
                NV_CRR( RegisterThread( m_cpMainThread ) );

                if ( pReceiver && pFirstEvent ) {

                    if ( pReceiver->GetOwnThread() == NULL )
                        pReceiver->SetOwnThread( m_cpMainThread );

                    NV_CRR( m_cpMainThread->PostEvent( NULL, pReceiver, pFirstEvent ) );

                }

                result_t ExecutionResult = m_cpMainThread->Run();

                UnregisterThread( m_cpMainThread );
                m_cpMainThread.Release();
                g_TLSCurrentThread.reset( NULL );

                m_IsMainThreadWorking = 0;
                return ExecutionResult;

            }

            return result_wrong_state;
        }

        result_t RunMainThread( INodeManager * pNodeManager, fnMain pMain )
        {
            assert( NULL != pNodeManager );
            assert( NULL != pMain );

            long nFlag = 0;
            if ( m_IsMainThreadWorking.compare_exchange_strong( nFlag, 1 ) ) {

                CThreadManagerPtr cpGuard( this );

                m_cpMainThread = new CMTEntity< CMainThread >( this );
                g_TLSCurrentThread.reset( new CThreadPtr( m_cpMainThread ) );
                NV_CRR( RegisterThread( m_cpMainThread ) );

                result_t ExecutionResult = pMain( pNodeManager );

                UnregisterThread( m_cpMainThread );
                m_cpMainThread.Release();
                g_TLSCurrentThread.reset( NULL );

                m_IsMainThreadWorking = 0;
                return ExecutionResult;

            }

            return result_wrong_state;
        }

        result_t StartThread( IThread * pThread )
        {
            assert( NULL != pThread );

            boost::mutex::scoped_lock Locker( m_ThreadsProtector );

            if (( std::find( m_Threads.begin(), m_Threads.end(), pThread ) != m_Threads.end() ) ||
                ( pThread->GetIdentifier() && m_Identifiers.find( pThread->GetIdentifier() ) != m_Identifiers.end() ))
            {
                return result_inv_args;
            }

            CThreadStarter Starter( this, pThread );

            try {

                boost::thread TaskThread( Starter );

            } catch ( boost::thread_resource_error & ) {

                return result_no_resources;

            }

            m_Threads.push_back( pThread );
            RegisterThread( pThread );

            return result_ok;
        }

        result_t Finish()
        {
            long nFlag = 0;
            if ( m_IsFinishing.compare_exchange_strong( nFlag, 1 ) ) {

                boost::mutex::scoped_lock Locker( m_ThreadsProtector );

                for ( CThreadsList::iterator iThread = m_Threads.begin(); m_Threads.end() != iThread; ++iThread )
                    ( *iThread )->Finish();

                GetMainThread()->Finish();
                m_IsFinishing = 0;

            }

            return result_ok;
        }

        size_t GetThreadsCount()
        {
            boost::mutex::scoped_lock Locker( m_ThreadsProtector );
            return m_Threads.size();
        }

        result_t GetThreadByIdentifier( cstr_t csIdentifier, CPtr< IThread > &cpThread )
        {
            assert( NULL != csIdentifier );

            boost::mutex::scoped_lock Locker( m_ThreadsProtector );

            CIdentifiersList::iterator iID = m_Identifiers.find( csIdentifier );
            if ( m_Identifiers.end() != iID )
                return iID->second.Copy( cpThread );

            return result_inv_args;
        }

        result_t GetThreadByIdentifier( cstr_t csIdentifier, CPtr< IEventsThread > &cpThread )
        {
            assert( NULL != csIdentifier );

            boost::mutex::scoped_lock Locker( m_ThreadsProtector );

            CIdentifiersList::iterator iID = m_Identifiers.find( csIdentifier );
            if ( m_Identifiers.end() != iID ) {

                if ( iID->second->CanProcessEvents() == false )
                    return result_wrong_state;

                cpThread = checked_cast< IEventsThread * >( iID->second.Get() );
                return result_ok;

            }

            return result_inv_args;
        }

        IEventsThread * GetMainThread()
        {
            return m_cpMainThread.Get();
        }

        IThread * GetCurrentThread()
        {
            CThreadPtr *pcpThread = g_TLSCurrentThread.get();
            if ( NULL == pcpThread )
                g_TLSCurrentThread.reset( pcpThread = new CThreadPtr( new CMTEntity< CForeignThread > ) );

            return pcpThread->Get();
        }

        void OnThreadFinishedReport( IThread * pThread )
        {
            assert( NULL != pThread );

            pThread->SetThreadState( IThread::FINISHED );

            boost::mutex::scoped_lock Locker( m_ThreadsProtector );

            if ( pThread->GetIdentifier() )
                m_Identifiers.erase( pThread->GetIdentifier() );

            CThreadsList::iterator iThread = std::find( m_Threads.begin(), m_Threads.end(), pThread );
            if ( m_Threads.end() != iThread )
                m_Threads.erase( iThread );
        }

        result_t CreateEventsThread( cstr_t csIdentifier, CPtr< IEventsThread > &cpThread )
        {
            cpThread = new( std::nothrow ) CMTEntity< CEventsThread >( csIdentifier, this );
            return cpThread.Get() ? result_ok : result_out_of_memory;
        }

        result_t AcquireEventsThread( cstr_t csIdentifier, CPtr< IEventsThread > &cpThread )
        {
            if ( NV_CFAIL( GetThreadByIdentifier( csIdentifier, cpThread ) ) ) {

                NV_CRR( CreateEventsThread( csIdentifier, cpThread ) );
                NV_CRR( StartThread( cpThread ) );

            }

            return result_ok;
        }

    protected:

        result_t RegisterThread( IThread * pThread )
        {
            assert( NULL != pThread );

            if ( pThread->GetIdentifier() ) {

                if ( m_Identifiers.find( pThread->GetIdentifier() ) != m_Identifiers.end() )
                    return result_inv_args;

                m_Identifiers[ pThread->GetIdentifier() ] = pThread;

            }

            return result_ok;
        }

        void UnregisterThread( IThread * pThread )
        {
            assert( NULL != pThread );

            if ( pThread->GetIdentifier() ) {

                CIdentifiersList::iterator iThread = m_Identifiers.find( pThread->GetIdentifier() );
                if ( m_Identifiers.end() != iThread )
                    m_Identifiers.erase( iThread );

            }
        }

        struct CThreadStarter {

            CThreadStarter( CThreadManager * pManager, IThread * pThread ): m_cpThreadManager( pManager ), m_cpThread( pThread )
            {
                if ( pThread )
                    pThread->SetThreadState( IThread::STARTING );
            }

            CPtr< CThreadManager > m_cpThreadManager;
            CThreadPtr m_cpThread;

            void operator()()
            {
                if ( m_cpThread ) {

                    try {

                        if ( m_cpThread->GetThreadType() == IThread::REGULAR_THREAD )
                            m_cpThread->SetThreadState( IThread::WORKING );

                        g_TLSCurrentThread.reset( new CThreadPtr( m_cpThread ) );

                        m_cpThread->SetExecutionResult( m_cpThread->Run() );

                        m_cpThreadManager->OnThreadFinishedReport( m_cpThread );

                    } catch ( std::exception & ) {

                        // TODO: Need to inform about a critical situation

                    }

                }
            }

        };

    private:

        boost::mutex m_ThreadsProtector;

        typedef std::list< CThreadPtr > CThreadsList;

        CThreadsList m_Threads;

        typedef std::map< std::string, CThreadPtr > CIdentifiersList;

        CIdentifiersList m_Identifiers;

        nstd::atomic< long > m_IsFinishing;

        CEventsThreadPtr m_cpMainThread;

        nstd::atomic< long > m_IsMainThreadWorking;

    };

} // namespace node

    result_t CreateThreadManager( CThreadManagerPtr &cpTM )
    {
        cpTM = new( std::nothrow ) CMTEntity< node::CThreadManager >;
        return cpTM.Get() ? result_ok : result_out_of_memory;
    }

} // namespace nvl
