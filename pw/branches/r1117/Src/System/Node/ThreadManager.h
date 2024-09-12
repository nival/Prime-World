#ifndef __THREAD_MANAGER_H_INCLUDED__734941__
#define __THREAD_MANAGER_H_INCLUDED__734941__

#include "Entity.h"

namespace nvl {

	struct IThread: IEntity {

		enum enumThreadTypes {

			REGULAR_THREAD,
			FOREIGN_THREAD,
			EVENTS_THREAD

		};

		enum enumThreadStates {

			CREATED,
			STARTING,
			WORKING,
			FINISHING,
			FINISHED

		};

		IThread(): m_ThreadState( CREATED ), m_ExecutionResult( result_unknown )
		{}

		virtual result_t Run() = 0;

		virtual result_t Finish()
		{ return result_ok; }

		virtual enumThreadTypes GetThreadType() const
		{ return REGULAR_THREAD; }

		enumThreadStates GetThreadState() const
		{ return static_cast< enumThreadStates >( m_ThreadState.load( nstd::memory_order_relaxed ) ); }

		void SetThreadState( enumThreadStates State )
		{ m_ThreadState = long( State ); }

		result_t GetExecutionResult() const
		{ return m_ExecutionResult; }

		void SetExecutionResult( result_t Result )
		{ m_ExecutionResult = Result; }

		bool CanProcessEvents() const
		{ return GetThreadType() == EVENTS_THREAD; }

		bool IsForeignThread() const
		{ return GetThreadType() == FOREIGN_THREAD; }

	protected:

		nstd::atomic< long > m_ThreadState;
		volatile result_t m_ExecutionResult;

	};

	typedef CPtr< IThread > CThreadPtr;

	struct IEventsReceiver;

	struct IEvent: IEntity {

		IEvent(): m_bIsCancelled( false )
		{}

		virtual result_t ProcessEvent( IEventsReceiver * pSender, IEventsReceiver * pReceiver ) = 0;

		void Cancel()
		{ m_bIsCancelled = true; }

		bool IsCancelled() const
		{ return m_bIsCancelled; }

	private:

		volatile bool m_bIsCancelled;

	};

	typedef CPtr< IEvent > CEventPtr;

	struct IEventsThread: IThread {

		virtual result_t PostEvent(
			IEventsReceiver * pSender,
			IEventsReceiver * pReceiver,
			IEvent * pEvent,
			uint_t nDelay = 0,
			uint_t nPeriod = 0
		) = 0;

	};

	typedef CPtr< IEventsThread > CEventsThreadPtr;

	struct IEventsReceiver: IEntity {

		virtual result_t OnEventReceived( IEventsReceiver * pSender, IEvent * pEvent )
		{ return result_not_impl; }

		IEventsThread * GetOwnThread() const
		{ return m_cpOwnThread; }

		result_t PostEvent( IEventsReceiver * pSender, IEvent * pEvent, uint_t nDelay = 0, uint_t nPeriod = 0 )
		{
			return GetOwnThread()->PostEvent( pSender, this, pEvent, nDelay, nPeriod );
		}

		void SetOwnThread( IEventsThread * pThread )
		{
			assert( m_cpOwnThread.Get() == NULL );
			assert( NULL != pThread );

			m_cpOwnThread = pThread;
		}

	protected:

		CEventsThreadPtr m_cpOwnThread;

	};

	typedef CPtr< IEventsReceiver > CEventsReceiverPtr;

	struct INodeManager;

	struct IThreadManager: IEntity {

		typedef result_t ( * fnMain )( INodeManager * );

		virtual result_t RunMainThread( INodeManager * pNodeManager, IEventsReceiver * pReceiver, IEvent * pFirstEvent ) = 0;
		virtual result_t RunMainThread( INodeManager * pNodeManager, fnMain pMain ) = 0;

		virtual result_t StartThread( IThread * pThread ) = 0;
		virtual result_t Finish() = 0;
		virtual size_t GetThreadsCount() = 0;
		virtual result_t GetThreadByIdentifier( cstr_t csIdentifier, CPtr< IThread > &cpThread ) = 0;
		virtual result_t GetThreadByIdentifier( cstr_t csIdentifier, CPtr< IEventsThread > &cpThread ) = 0;
		virtual IEventsThread * GetMainThread() = 0;
		virtual IThread * GetCurrentThread() = 0;
		virtual void OnThreadFinishedReport( IThread * pThread ) = 0;

		virtual result_t CreateEventsThread( cstr_t csIdentifier, CPtr< IEventsThread > &cpEventsThread ) = 0;
		virtual result_t AcquireEventsThread( cstr_t csIdentifier, CPtr< IEventsThread > &cpEventsThread ) = 0;

	};

	typedef CPtr< IThreadManager > CThreadManagerPtr;

	result_t CreateThreadManager( CThreadManagerPtr &cpTM );

	#define NV_DECLARE_EVENT( __event_name )			\
		struct __event_name;							\
		typedef CPtr< __event_name > __event_name##Ptr;	\
		struct __event_name: IEvent {					\
			::nvl::cstr_t GetIdentifier() const			\
			{ return GetClassIdentifier(); }

	#define NV_DECLARE_POOLABLE_EVENT( __event_name )	\
		struct __event_name;							\
		typedef CPtr< __event_name > __event_name##Ptr;	\
		struct __event_name: IEvent, CStackableEntity {	\
			::nvl::cstr_t GetIdentifier() const			\
			{ return GetClassIdentifier(); }

	#define NV_PROCESS_EVENT_FUNCTION( __receiver_class, __calling_function )				\
		result_t ProcessEvent( IEventsReceiver * pSender, IEventsReceiver * pReceiver )		\
		{																					\
			assert( dynamic_cast< __receiver_class * >( pReceiver) != NULL );				\
			return static_cast< __receiver_class * >( pReceiver )->__calling_function;		\
		}

	#define NV_DECLARE_EVENT_END	\
		};

} // namespace nvl

#include "NodeManager.h"

#endif // __THREAD_MANAGER_H_INCLUDED__734941__
