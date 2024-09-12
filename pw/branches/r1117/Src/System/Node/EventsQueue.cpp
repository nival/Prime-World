#include "EventsQueue.h"
#include "Stack.h"
#include "LockFreeStack.h"
#include "atomic.h"

#include <map>
#include <boost/thread.hpp>
#include <assert.h>

namespace nvl {

	class CEventNode;

	struct CEventNodesContainer: IEntity, CLockFreeStack< CEventNode > {
	};

	typedef CPtr< CEventNodesContainer > CEventNodesContainerPtr;
	typedef CMTEntity< CEventNodesContainer > CEventNodesContainerEntity;

	class CEventNode:
		public CStackNode< CEventNode >
	{
	public:

		CEventNode(): m_nDeliveryTime( 0 ), m_nPeriod( 0 )
		{}

		void SendToOwner()
		{
			assert( m_cpOwner.Get() != NULL );

			CEventNodesContainerPtr cpContainer;
			cpContainer.Attach( m_cpOwner.Detach() )->Push( this );
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

	class CEventsQueue:
		public IEventsQueue
	{
	public:

		CEventsQueue(): m_CycleFlag( 0 ), m_pPreparedEventsLast( NULL )
		{}

		~CEventsQueue()
		{
			FreeStack( m_PreparedEvents.PopStack() );
			FreeStack( m_FreeNodes.PopStack() );
			FreeStack( m_EventsNoDelay.PopStack() );
			FreeStack( m_EventsDelay.PopStack() );
		}

		result_t Start()
		{
			long nFlagValue = 0;
			if ( m_CycleFlag.compare_exchange_strong( nFlagValue, 1 ) == false )
				return result_wrong_state;

			try {

				CEventNode *pStack = NULL;

				while ( m_CycleFlag ) {

					result_t Result = result_ok;

					uint_t nCounter = 100;
					while ( m_PreparedEvents.IsEmpty() == false && --nCounter ) {

						CEventNode *pNode = m_PreparedEvents.Pop();

						if ( pNode == m_pPreparedEventsLast )
							m_pPreparedEventsLast = NULL;

						if ( pNode->m_nPeriod ) {

							assert( pNode->m_cpEvent.Get() != NULL );
							Result = pNode->m_cpEvent->ProcessEvent();

							if ( result_cancel != Result ) {

								uint_t nCurrentTick = GetTickCount();
								while ( static_cast< int >(( pNode->m_nDeliveryTime += pNode->m_nPeriod ) - nCurrentTick ) <= 0 )
								{}

								InsertDelayedEvent( pNode );

							}

						} else
							Result = pNode->m_cpEvent->ProcessEvent();

						pNode->m_cpEvent.Release();

						if ( pNode->m_cpOwner.get() )
							pNode->SendToOwner();
						else
							m_FreeNodes.Push( pNode );

					}

					if ( m_EventsNoDelay.IsEmpty() == false ) {

						pStack = m_EventsNoDelay.PopReversedStack();

						if ( m_pPreparesEventsLast )
							m_pPreparesEventsLast->SetNextNode( pStack );
						else {

							assert( m_PreparedEvents.IsEmpty() == true );
							m_PreparedEvents.PushStack( pStack  );

						}

						m_pPreparesEventsLast = FindLastStackNode( pStack );

					}

					if ( m_EventsDelay.IsEmpty() == false ) {

						pStack = m_EventsDelay.PopReversedStack();
						while ( pStack ) {

							InsertDelayedEvent( pStack );
							pStack = pStack->GetNextNode();

						}

					}

					while ( m_DelayedEvents.Empty() == false ) {

						CDelayedEventsList::iterator iEnd = m_DelayedEvents.upper_bound( GetTickCount() );
						if ( m_DelayedEvents.begin() != iEnd ) {

							for ( CDelayedEventsList::iterator iEvent = m_DelayedEvents.begin(); iEnd != iEvent; ++iEvent ) {

								if ( m_pPreparesEventsLast )
									m_pPreparesEventsLast->SetNextNode( iEvent->second );

								m_pPreparesEventsLast = iEvent->second;

							}

							m_pPreparedEventsLast->SetNextNode( NULL );

							if ( m_PreparedEvents.IsEmpty() )
								m_PreparedEvents.PushStack( m_DelayedEvents.front().second );

							m_DelatedEventsList.erase( m_DelayedEvents.begin(), iEnd );

						}

					}

					if ( m_PreparedEvents.IsEmpty() )
						Sleep( 1 );

				}

			} catch ( std::exception & ) {

				m_CycleFlag = 0;
				throw;

			}

			return result_ok;
		}

		result_t Stop()
		{
			return m_CycleFlag.compare_exchange_strong( 1, 0 ) ? result_ok : result_wrong_state;
		}

		result_t Post( IEventsReceiver * const pSender,  IEvent * const pEvent )
		{
			assert( NULL != pEvent );
			assert( pEvent->IsMTEntity() == true );

			CEventNode *pNode = AllocMTNode();
			pNode->m_cpEvent = pEvent;

			m_EventsNoDelay.Push( pNode );

			return result_ok;
		}

		result_t Enqueue( IEvent * const pEvent )
		{
			assert( NULL != pEvent );
			assert( GetCurrentThread()->GetType() == EVENTS_THREAD );
			assert( static_cast< IEventsThread * >( GetCurrentThread() )->GetQueue() == this );

			CEventNode *pNode = AllocNode();
			pNode->m_cpEvent = pEvent;

			if ( m_pPreparedMessagesLast ) {

				m_pPreparedMessagesLast->SetNextNode( pNode );
				pNode->SetNextNode( NULL );

			} else
				m_PreparedMessages.Push( pNode );

			m_pPreparedMessagesLast = pNode;

			return result_ok;
		}

		result_t Post( IEvent * const pEvent, uint_t nDelay, uint_t nPeriod )
		{
			assert( NULL != pEvent );
			assert( pEvent->IsMTEntity() == true );

			CEventNode *pNode = AllocMTNode();

			pNode->m_cpEvent = pEvent;
			pNode->m_nDeliveryTime = GetTickCount() + nDelay;
			pNode->m_nPeriod = nPeriod;

			m_EventsDalay.Push( pNode );

			return result_ok;
		}

		result_t Enqueue( IEvent * const pEvent, uint_t nDelay, uint_t nPeriod )
		{
			assert( NULL != pEvent );
			assert( GetCurrentThread()->GetType() == EVENTS_THREAD );
			assert( static_cast< IEventsThread * >( GetCurrentThread() )->GetQueue() == this );

			message_node *node = alloc_node();

			node->m_message = message;
			node->m_delivery_time = get_tick_count() + delay;
			node->m_period = period;

			guard< message_node > node_guard(node);
			insert_delayed_message(node);
			node_guard.detach();

			return result_ok;
		}

		result_t SendEvent( IEventsReceiver * const pSender, IEventsReceiver * const pReceiver, IEvent * const pEvent )
		{
			return result_ok;
		}

		result_t PostEvent( IEventsReceiver * const pSender, IEventsReceiver * const pReceiver, IEvent * const pEvent, uint_t const nDelay, uint_t const nPeriod )
		{
			assert( NULL != pEvent );
			assert( GetCurrentThread()->GetType() == EVENTS_THREAD );
			assert( static_cast< IEventsThread * >( GetCurrentThread() )->GetQueue() == this );

			return result_ok;
		}

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
			CEventNodesContainerPtr *pContainer = tls_free_message_nodes.get();
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

				CEventNode *pNode = pStack->Get_next_node();

				if ( pStack->m_cpOwner.Get() )
					pStack->SendToOwner();
				else
					pStack->DestroyNode();

				pStack = pNode;

			}
		}

		void InsertDelayedEvent( CEventNode * const pNode )
		{
			m_DelayedEvent.insert( CDelayedEventsList::value_type( pNode->m_nDeliveryTime, pNode ) );
		}

	private:

		nstd::atomic< long > m_CycleFlag;

		CStack< CEventNode > m_FreeNodes;
		CStack< CEventNode > m_PreparedEvents;
		CEventNode * m_pPreparedEventsLast;

		typedef std::multimap< uint_t, CEventNode * > CDelayedEventsList;

		CDelayedEventsList m_DelayedEvents;

		CLockFreeStack< CEventNode > m_EventsNoDelay;
		CLockFreeStack< CEventNode > m_EventsDelay;

	};

	typedef CMTEntity< CEventsQueue > CEventsQueueEntity;

	result_t Create( CEventsQueuePtr & const cpEQ )
	{
		return CEventsQueuePtr( new CEventsQueueEntity ).Detach( cpEQ );
	}

} // namespace nvl
