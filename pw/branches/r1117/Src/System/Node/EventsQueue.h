#ifndef __EVENTS_QUEUE_H_INCLUDED__251988__
#define __EVENTS_QUEUE_H_INCLUDED__251988__

#include "Entity.h"

namespace nvl {

	struct IEvent;
	struct IEventsReceiver;

	struct IEventsQueue: IEntity {

		virtual result_t SendEvent(
			IEventsReceiver * const pSender,
			IEventsReceiver * const pReceiver,
			IEvent * const pEvent
		) = 0;

		virtual result_t PostEvent(
			IEventsReceiver * const pSender,
			IEventsReceiver * const pReceiver,
			IEvent * const pEvent,
			uint_t const nDelay = 0,
			uint_t const nPeriod = 0
		) = 0;

	};

	typedef CPtr< IEventsQueue > CEventsQueuePtr;

	struct IEvent: IEntity {

		IEvent(): m_bIsCancelled( false )
		{}

		virtual void ProcessEvent( IEventsReceiver * const pSender, IEventsReceiver * const pReceiver ) = 0;

		void Cancel()
		{ m_bIsCancelled = true; }

		bool IsCancelled() const
		{ return m_bIsCancelled; }

	private:

		volatile bool m_bIsCancelled;

	};

	typedef CPtr< IEvent > CEventPtr;

	struct IEventsReceiver: IEntity {

		virtual result_t OnEventReceived( IEventsReceiver * const pSender, IEvent * const pEvent )
		{ return result_not_impl; }

		IEventsQueue * GetEventsQueue() const
		{ return m_cpEventsQueue; }

		result_t SendEvent( IEventsReceiver * const pReceiver, IEvent * const pEvent )
		{
			assert( NULL != pReceiver );
			return pReceiver->GetEventsQueue()->SendEvent( this, pReceiver, pEvent );
		}

		result_t PostEvent( IEventsReceiver * const pReceiver, IEvent * const pEvent, uint_t const nDelay = 0, uint_t const nPeriod = 0 )
		{
			assert( NULL != pReceiver );
			return pReceiver->GetEventsQueue()->PostEvent( this, pReceiver, pEvent, nDelay, nPeriod );
		}

	protected:

		void SetEventsQueue( IEventsQueue * const pQueue )
		{ m_cpEventsQueue = pQueue; }

	protected:

		CEventsQueuePtr m_cpEventsQueue;

	};

	typedef CPtr< IEventsReceiver > CEventsReceiverPtr;

	#define NV_DECLARE_EVENT( __event_class_name ) struct __event_class_name: IEvent

	#define NV_DECLARE_PROCESS_EVENT_FUNCTION( __receiver_class, __calling_function ) \
		result_t ProcessEvent( IEventReceiver * const pSender, IEventReceiver * const pReceiver ) { \
		assert( NULL != pReceiver ); \
		return static_cast< __receiver_class * >( pReceiver )->__calling_function; }

} // namespace nvl

#endif // __EVENTS_QUEUE_H_INCLUDED__251988__
