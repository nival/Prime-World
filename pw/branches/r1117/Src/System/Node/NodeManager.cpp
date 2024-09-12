#include "NodeManager.h"

#include <map>
#include <list>

#include <boost/thread.hpp>
#include <boost/optional.hpp>

#include <json/reader.h>
#include <json/writer.h>

namespace nvl {

	namespace node {

		class CNodeManager:
			public INodeManager
		{
		public:

			enum OPERATION_TYPES {

				START,
				FINISH

			};

			CNodeManager(): m_NextOperationID( 0 )
			{}

			result_t Initialize()
			{
				NV_CRR( CreateThreadManager( m_cpThreadManager ) );

				return result_ok;
			}

			IThreadManager * GetThreadManager()
			{ return m_cpThreadManager; }

			result_t RunMainThread( IEventsReceiver * pReceiver, IEvent * pFirstEvent )
			{
				return GetThreadManager()->RunMainThread( this, pReceiver, pFirstEvent );
			}

			result_t RegisterServices( IServicesFactory * pFactory )
			{
				assert( NULL != pFactory );

				boost::mutex::scoped_lock Protector( m_ServicesMutex );

				size_t nServicesCount = pFactory->GetServiceTypesCount();
				for ( size_t i = 0; i < nServicesCount; ++i ) {

					cstr_t csServiceTypeID = pFactory->GetServiceTypeID( i );

					if ( NULL == pFactory->GetServiceMetainfo( i )
						|| NULL == csServiceTypeID
						|| m_ServiceTypes.find( csServiceTypeID ) != m_ServiceTypes.end() )
					{
						return result_inv_args;
					}

				}

				for ( size_t i = 0; i < nServicesCount; ++i ) {

					CServiceTypeInfo &Info = m_ServiceTypes[ pFactory->GetServiceTypeID( i ) ];
					Info.cpFactory = pFactory;
					Info.nIndex = i;

				}

				return result_ok;
			}

			result_t ServiceRun( cstr_t csGlobalSettings, cstr_t csSettings )
			{
				assert( NULL != csGlobalSettings );
				assert( NULL != csSettings );

				Json::Value Settings;
				Json::Reader Reader;
				if ( Reader.parse( csSettings, Settings ) == false )
					return result_inv_args;

				boost::optional< std::string > sServiceType, sServiceID, sThreadID;
				Json::Value *pSettings = NULL;

				Json::Value::Members Names;
				Settings.getMemberNames().swap( Names );

				for ( Json::Value::Members::iterator iName = Names.begin(); Names.end() != iName; ++iName ) {

					if ( iName->compare( "service" ) == 0 )
						sServiceType = Settings[ *iName ].asString();
					else if ( iName->compare( "id" ) == 0 )
						sServiceID = Settings[ *iName ].asString();
					else if ( iName->compare( "thread" ) == 0 )
						sThreadID = Settings[ *iName ].asString();
					else if ( iName->compare( "settings" ) == 0 )
						pSettings = &Settings[ *iName ];
					else
						return result_inv_args;

				}

				if ( sServiceType.is_initialized() == false
					|| sServiceID.is_initialized() == false
					|| NULL == pSettings )
				{
					return result_inv_args;
				}

				CServicePtr cpService;
				NV_CRR( ServiceCreate( sServiceType->c_str(), sServiceID->c_str(), cpService ) );

				cstr_t csRecomendedThread = sThreadID.is_initialized() ? sThreadID->c_str() : "Main Thread";
				cstr_t csApprovedThread = csRecomendedThread;

				NV_CRR( cpService->ServiceThreadChoice( csRecomendedThread, csApprovedThread ) );

				CThreadPtr cpThread;
				if ( NV_CFAIL( GetThreadManager()->GetThreadByIdentifier( csApprovedThread, cpThread ) ) ) {

					CEventsThreadPtr cpEventsThread;
					NV_CRR( GetThreadManager()->CreateEventsThread( csApprovedThread, cpEventsThread ) );
					NV_CRR( GetThreadManager()->StartThread( cpEventsThread ) );

					cpThread = cpEventsThread;

				} else if ( cpThread->CanProcessEvents() == false )
					return result_inv_args;

				cpService->SetOwnThread( static_cast< IEventsThread * >( cpThread.Get() ) );

				{
					boost::mutex::scoped_lock Protector( m_ServicesMutex );
					NV_CRR( ProcessSubscribes( cpService ) );
				}

				Json::StyledWriter Writer;
				return ServiceStart( cpService, csGlobalSettings, Writer.write( *pSettings ).c_str() );
			}

			result_t ServiceCreate( cstr_t csServiceTypeID, cstr_t csServiceIdentififer, CServicePtr &cpService )
			{
				assert( NULL != csServiceTypeID );
				assert( NULL != csServiceIdentififer );

				boost::mutex::scoped_lock Protector( m_ServicesMutex );

				CServiceTypes::const_iterator iServiceType = m_ServiceTypes.find( csServiceTypeID );
				if ( m_ServiceTypes.end() == iServiceType )
					return result_inv_args;

				result_t Result = iServiceType->second.cpFactory->Create( csServiceTypeID, csServiceIdentififer, cpService );
				if ( NV_CSUCCESS( Result ) ) {

					cpService->SetNodeManager( this );
					cpService->SetServiceIdentifier( csServiceIdentififer );

				}

				return Result;
			}

			NV_DECLARE_EVENT( CServiceStartEvent )

				CServiceStartEvent( cstr_t csGlobalSettings, cstr_t csSettings, OperationID_t ID ):
					m_sGlobalSettings( csGlobalSettings ), m_sSettings( csSettings ), m_OperationID( ID )
				{}

				result_t ProcessEvent( IEventsReceiver * pSender, IEventsReceiver * pReceiver )
				{
					assert( dynamic_cast< IService * >( pReceiver) != NULL );

					IService *pService = static_cast< IService * >( pReceiver );
					result_t Result = pService->ServiceStart( m_sGlobalSettings.c_str(), m_sSettings.c_str(), m_OperationID );

					if ( NV_CFAIL( Result ) )
						NV_CRR( pService->GetNodeManager()->ServiceReport( pService, m_OperationID, Result, "NodeManager cannot start the service" ) );

					return result_ok;
				}

				std::string m_sGlobalSettings;
				std::string m_sSettings;
				OperationID_t m_OperationID;

			NV_DECLARE_EVENT_END

			result_t ServiceStart( IService * pService, cstr_t csGlobalSettings, cstr_t csSettings )
			{
				assert( NULL != pService );
				assert( NULL != pService->GetIdentifier() );
				assert( NULL != csGlobalSettings );
				assert( NULL != csSettings );

				boost::mutex::scoped_lock Protector( m_ServicesMutex );

				if ( m_Services.find( pService->GetIdentifier() ) != m_Services.end() )
					return result_inv_args;

				if ( IService::CREATED != pService->GetServiceState() && IService::FINISHED != pService->GetServiceState() )
					return result_wrong_state;

				pService->SetServiceState( IService::STARTING );
				m_Services[ pService->GetIdentifier() ] = pService;

				NV_CRR( ProcessSubscribes( pService ) );

				CServiceStartEventPtr cpEvent = new CMTEntity< CServiceStartEvent >( csGlobalSettings, csSettings, AllocNewOperation( START, pService ) );
				return pService->PostEvent( NULL, cpEvent );
			}

			NV_DECLARE_EVENT( CServiceFinishEvent )

				CServiceFinishEvent( OperationID_t ID ): m_OperationID( ID )
				{}

				result_t ProcessEvent( IEventsReceiver * pSender, IEventsReceiver * pReceiver )
				{
					assert( dynamic_cast< IService * >( pReceiver) != NULL );

					IService *pService = static_cast< IService * >( pReceiver );
					result_t Result = pService->ServiceFinish( m_OperationID );

					if ( NV_CFAIL( Result ) )
						NV_CRR( pService->GetNodeManager()->ServiceReport( pService, m_OperationID, Result, "NodeManager cannot start the service" ) );

					return result_ok;
				}

				OperationID_t m_OperationID;

			NV_DECLARE_EVENT_END

			result_t ServiceFinish( IService * pService )
			{
				assert( NULL != pService );

				boost::mutex::scoped_lock Protector( m_ServicesMutex );

				if ( IService::STARTING != pService->GetServiceState() && IService::WORKING != pService->GetServiceState() )
					return result_wrong_state;

				pService->SetServiceState( IService::FINISHING );
				NV_CRR( ProcessSubscribes( pService ) );

				CServiceFinishEventPtr cpEvent = new CMTEntity< CServiceFinishEvent >( AllocNewOperation( FINISH, pService ) );
				return pService->PostEvent( NULL, cpEvent );
			}

			result_t GetServiceByIdentifier( cstr_t csServiceIdentifier, CServicePtr &cpService ) const
			{
				assert( NULL != csServiceIdentifier );

				boost::mutex::scoped_lock Protector( m_ServicesMutex );

				CServicesList::const_iterator iService = m_Services.find( csServiceIdentifier );
				if ( m_Services.end() == iService )
					return result_inv_args;

				cpService = iService->second;

				return result_ok;
			}

			result_t ServiceReport( IService * pService, OperationID_t ID, result_t Result, cstr_t csResultDescription )
			{
				boost::mutex::scoped_lock Protector( m_ServicesMutex );

				COperationsInProgress::iterator iOperation = m_OperationsInProgress.find( ID );
				if ( m_OperationsInProgress.end() == iOperation )
					return result_inv_args;

				assert( iOperation->second.m_cpService == pService );

				IService::SERVICE_STATES PreviousState = pService->GetServiceState();

				switch ( iOperation->second.m_Type ) {

				case START:

					if ( pService->GetServiceState() == IService::STARTING )
						pService->SetServiceState( NV_CSUCCESS( Result ) ? IService::WORKING : IService::FINISHED );

					break;

				case FINISH: {

						if ( pService->GetServiceState() == IService::FINISHING )
							pService->SetServiceState( IService::FINISHED );

						CServicesList::iterator iService = m_Services.find( pService->GetIdentifier() );
						if ( m_Services.end() != iService )
							m_Services.erase( iService );

					}
					break;

				}

				m_OperationsInProgress.erase( iOperation );

				if ( pService->GetServiceState() != PreviousState )
					NV_CRR( ProcessSubscribes( pService ) );

				return result_ok;
			}

			result_t ServiceStateSubscribe( IServiceStatesProcessor * pProcessor )
			{
				assert( NULL != pProcessor );

				boost::mutex::scoped_lock Protector( m_ServicesMutex );

				if ( std::find( m_StateProcessors.begin(), m_StateProcessors.end(), pProcessor ) != m_StateProcessors.end() )
					return result_already_done;

				m_StateProcessors.push_back( pProcessor );

				for ( CServicesList::const_iterator iService = m_Services.begin(); m_Services.end() != iService; ++iService )
					ProcessSubscribes( iService->second );

				return result_ok;
			}

			result_t ServiceStateUnsubscribe( IServiceStatesProcessor * pProcessor )
			{
				assert( NULL != pProcessor );

				boost::mutex::scoped_lock Protector( m_ServicesMutex );

				CStateProcessors::iterator iProcessor = std::find( m_StateProcessors.begin(), m_StateProcessors.end(), pProcessor );
				if ( m_StateProcessors.end() == iProcessor )
					return result_already_done;

				m_StateProcessors.erase( iProcessor );

				return result_ok;
			}

		protected:

			OperationID_t AllocNewOperation( OPERATION_TYPES Type, IService * pService )
			{
				while ( m_OperationsInProgress.find( ++m_NextOperationID ) != m_OperationsInProgress.end() )
				{}

				COperationInfo &Info = m_OperationsInProgress[ m_NextOperationID ];
				Info.m_Type = Type;
				Info.m_cpService = pService;

				return m_NextOperationID;
			}

			NV_DECLARE_EVENT( CStateNotifyEvent )

				CStateNotifyEvent( IService * const pService, IService::SERVICE_STATES State ):
					m_cpService( pService ), m_State( State )
				{}

				NV_PROCESS_EVENT_FUNCTION( IServiceStatesProcessor, ServiceStateNotify( m_cpService, m_State ) );

				CServicePtr m_cpService;
				IService::SERVICE_STATES m_State;

			NV_DECLARE_EVENT_END

			result_t ProcessSubscribes( IService * const pService )
			{
				assert( NULL != pService );

				if ( m_StateProcessors.empty() == false ) {

					CEventPtr cpNotifyEvent = new CMTEntity< CStateNotifyEvent >( pService, pService->GetServiceState() );

					for ( CStateProcessors::const_iterator iProcessor = m_StateProcessors.begin(); m_StateProcessors.end() != iProcessor; ++iProcessor )
						NV_CRR( (*iProcessor)->PostEvent( NULL, cpNotifyEvent ) );

				}

				return result_ok;
			}

		private:

			CThreadManagerPtr m_cpThreadManager;
			mutable boost::mutex m_ServicesMutex;

			struct CServiceTypeInfo {

				CServicesFactoryPtr cpFactory;
				size_t nIndex;

			};

			typedef std::map< std::string, CServiceTypeInfo > CServiceTypes;

			CServiceTypes m_ServiceTypes;

			typedef std::map< std::string, CServicePtr > CServicesList;

			CServicesList m_Services;

			OperationID_t m_NextOperationID;

			struct COperationInfo {

				OPERATION_TYPES m_Type;
				CServicePtr m_cpService;

			};

			typedef std::map< OperationID_t, COperationInfo > COperationsInProgress;

			COperationsInProgress m_OperationsInProgress;

			typedef std::list< CServiceStatesProcessorPtr > CStateProcessors;

			CStateProcessors m_StateProcessors;

		};

	} // namespace node

	result_t CreateNodeManager( CNodeManagerPtr &cpNM )
	{
		CPtr< node::CNodeManager > cpNMC = new( std::nothrow ) CMTEntity< node::CNodeManager >;
		if ( cpNMC.Get() == NULL )
			return result_out_of_memory;

		NV_CRR( cpNMC->Initialize() );

		cpNM = cpNMC;

		return result_ok;
	}

} // namespace nvl
