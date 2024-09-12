#ifndef __NODE_MANAGER_H_INCLUDED__390280__
#define __NODE_MANAGER_H_INCLUDED__390280__

#include "ThreadManager.h"

namespace nvl {

	namespace node {

		class CNodeManager;

	}

	typedef size_t OperationID_t;

	struct INodeManager;
	typedef CPtr< INodeManager > CNodeManagerPtr;

	struct IService: IEventsReceiver {

		enum SERVICE_STATES {

			CREATED = 0,
			STARTING,
			WORKING,
			FINISHING,
			FINISHED

		};

		IService(): m_ServiceState( CREATED )
		{}

		INodeManager * GetNodeManager() const
		{ return m_cpNodeManager; }

		SERVICE_STATES GetServiceState() const
		{ return m_ServiceState; }

		// IEntity methods

		virtual cstr_t GetIdentifier() const
		{ return m_sServiceIdentifier.c_str(); }

		// Own methods

		/*
			Метод определяет поток, в котором будет запущен сервис. Вызывается только один раз
			непосредственно перед запуском. По умолчанию, если сервис не переопределил данный
			метод, он всегда соглашается с предлагаемым для запуска потоком. Поток, в котором
			будет запущен сервис, должен быть событийным - GetThreadType() == EVENTS_THREAD

			csRecomendedThread - строчный идентификатор предлагаемого системой потока, в котором
				будет запущен сервис. Значение берется из настроек, а если не указано, то будет
				передан идентификатор основного потока.

			csApprovedThread - сервис принимает решение в каком потоке запуститься и возвращает
				в данной переменной указатель на его идентификатор.
		*/
		virtual result_t ServiceThreadChoice( cstr_t csRecomendedThread, cstr_t &csApprovedThread )
		{ return result_ok; }

		virtual result_t GetServiceMetainfo( cstr_t &csMetainfo, cstr_t &csCommands )
		{
			csMetainfo = "{}";
			csCommands = "{}";

			return result_ok;
		}

		virtual result_t ServiceStart( cstr_t csGlobalSettings, cstr_t csSettings, OperationID_t ID ) = 0;
		virtual result_t ServiceFinish( OperationID_t ID ) = 0;

		virtual result_t ServiceUpdate( cstr_t csGlobalSettings, cstr_t csSettings, cstr_t csUpdatedSettings, OperationID_t ID )
		{ return result_not_impl; }

		virtual result_t ServiceExecute( cstr_t csCommand, cstr_t csSettings, OperationID_t ID )
		{ return result_not_impl; }

	private:

		friend class node::CNodeManager;

		void SetNodeManager( INodeManager * pNodeManager )
		{
			assert( NULL != pNodeManager );
			m_cpNodeManager = pNodeManager;
		}

		void SetServiceState( SERVICE_STATES State )
		{ m_ServiceState = State; }

		void SetServiceIdentifier( cstr_t csServiceIdentifier )
		{
			assert( NULL != csServiceIdentifier );
			m_sServiceIdentifier = csServiceIdentifier;
		}

	private:

		CNodeManagerPtr m_cpNodeManager;
		volatile SERVICE_STATES m_ServiceState;
		std::string m_sServiceIdentifier;

	};

	typedef CPtr< IService > CServicePtr;

	struct IServicesFactory: IEntity {

		virtual size_t GetServiceTypesCount() const = 0;
		virtual cstr_t GetServiceTypeID( size_t nIndex ) const = 0;
		virtual cstr_t GetServiceMetainfo( size_t nIndex ) const = 0;

		virtual result_t Create( cstr_t csServiceTypeID, cstr_t csServiceIdentififer, CServicePtr &cpService ) = 0;

	};

	typedef CPtr< IServicesFactory > CServicesFactoryPtr;

	typedef size_t SubscribeID_t;

	struct IServiceStatesProcessor: IEventsReceiver {

		virtual result_t ServiceStateNotify( IService * pService, IService::SERVICE_STATES NewState ) = 0;

	};

	typedef CPtr< IServiceStatesProcessor > CServiceStatesProcessorPtr;

	struct INodeManager: IEntity {

		virtual IThreadManager * GetThreadManager() = 0;
		virtual result_t RunMainThread( IEventsReceiver * pReceiver, IEvent * pFirstEvent ) = 0;

		virtual result_t RegisterServices( IServicesFactory * pFactory ) = 0;

		virtual result_t ServiceRun( cstr_t csGlobalSettings, cstr_t csSettings ) = 0;

		virtual result_t ServiceCreate( cstr_t csServiceTypeID, cstr_t csServiceIdentififer, CServicePtr &cpService ) = 0;
		virtual result_t ServiceStart( IService * pService, cstr_t csGlobalSettings, cstr_t csSettings ) = 0;

		virtual result_t ServiceFinish( IService * pService ) = 0;

		virtual result_t GetServiceByIdentifier( cstr_t csServiceIdentifier, CServicePtr &cpService ) const = 0;

		template< typename T > result_t GetService( cstr_t csServiceIdentififer, T **ppService = NULL ) const;

		virtual result_t ServiceStateSubscribe( IServiceStatesProcessor * pProcessor ) = 0;
		virtual result_t ServiceStateUnsubscribe( IServiceStatesProcessor * pProcessor ) = 0;

		virtual result_t ServiceReport( IService * pService, OperationID_t ID, result_t Result, cstr_t csResultDescription ) = 0;

	};

	template< typename T > inline result_t INodeManager::GetService( cstr_t csServiceIdentififer, T **ppService ) const
	{
		CServicePtr cpService;
		NV_CRR( GetServiceByIdentifier( csServiceIdentififer, cpService ) );

		if ( ppService ) {

			assert( dynamic_cast< T * >( cpService.Get() ) != NULL );
			*ppService = static_cast< T * >( cpService.Detach() );

		}

		return result_ok;
	}

	result_t CreateNodeManager( CNodeManagerPtr &cpNM );

} // namespace nvl

#endif // __NODE_MANAGER_H_INCLUDED__390280__
