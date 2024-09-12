#include <System/BlockData/BlockData.h>
#include "FileTerminator.h"
//#include "NetworkTerminator.h"
//#include "Collector.h"

#include <map>
#include <vector>
#include <string>

#include <json/reader.h>
#include <json/writer.h>
#include <boost/thread.hpp>

namespace nvl {
namespace bds {

	class CBlockDataService:
		public IBlockDataServiceEx
	{
	public:

		CBlockDataService(): m_FinishOperationID( 0 )
		{
			m_BlockIdentifiers.reserve( 10 );
			m_BlockIdentifiers.push_back( BlockInfo_t() );
		}

		// IService

		result_t ServiceStart( cstr_t csGlobalSettings, cstr_t csSettings, OperationID_t ID )
		{
			assert( NULL != csSettings );

			Json::Value Settings;
			Json::Reader Reader;
			if ( Reader.parse( csSettings, Settings ) == false )
				return result_inv_args;

			if ( Settings.isMember( "terminators" ) ) {

				Json::Value const &Terminators = Settings[ "terminators" ];
				Json::Value::const_iterator iTerminatorEnd = Terminators.end();
				for ( Json::Value::const_iterator iTerminator = Terminators.begin(); iTerminatorEnd != iTerminator; ++iTerminator )
					NV_CRR( CreateTerminator( iTerminator.memberName(), *iTerminator ) );

			}

/*			if ( Settings.isMember( "collectors" ) ) {

				Json::Value const &Collectors = Settings[ "collectors" ];
				Json::Value::const_iterator iCollectorEnd = Collectors.end();
				for ( Json::Value::const_iterator iCollector = Collectors.begin(); iCollectorEnd != iCollector; ++iCollector )
					NV_CRR( CreateCollector( iCollector.memberName(), *iCollector ) );

			}*/

			GetNodeManager()->ServiceReport( this, ID, result_ok, "The service is started");
			return result_ok;
		}

		result_t ServiceFinish( OperationID_t ID )
		{
			m_FinishOperationID = ID;

			for ( CTerminatorsList::iterator iTerminator = m_Terminators.begin(); m_Terminators.end() != iTerminator; ++iTerminator )
				iTerminator->second->Close();

			CheckFinishingStatus();

			return result_ok;
		}

		// IBlockDataService

		result_t GetTerminator( cstr_t csTerminatorID, CPtr< ITerminator > &cpTerminator ) const
		{
			CTerminatorsList::const_iterator iTerminator = m_Terminators.find( csTerminatorID );
			return m_Terminators.end() == iTerminator ? result_inv_args : iTerminator->second.Copy( cpTerminator );
		}

		result_t CreateTerminator( cstr_t csTerminatorID, cstr_t csSettings )
		{
			assert( NULL != csSettings );

			Json::Value Settings;
			Json::Reader Reader;
			if ( Reader.parse( csSettings, Settings ) == false )
				return result_inv_args;

			return CreateTerminator( csTerminatorID, Settings );
		}

		result_t RegisterBlockType( IBlockFactory * pFactory, cstr_t csBlockIdentifier, BlockTypeID_t &ID )
		{
			assert( NULL != csBlockIdentifier );

			boost::mutex::scoped_lock Protector( m_BlockTypesMutex );

			std::string sIdentifier = csBlockIdentifier;
			BlockTypes_t::const_iterator iBlockType = m_BlockTypes.find( sIdentifier );
			if ( m_BlockTypes.end() != iBlockType ) {

				ID = iBlockType->second;
				return result_already_done;

			}

			ID = static_cast< BlockTypeID_t >( m_BlockIdentifiers.size() );
			m_BlockTypes[ sIdentifier ] = ID;

			m_BlockIdentifiers.resize( m_BlockIdentifiers.size() + 1 );
			m_BlockIdentifiers.back().m_sIdentifier.swap( sIdentifier );
			m_BlockIdentifiers.back().m_cpFactory = pFactory;

			return result_ok;
		}

		result_t GetBlockTypeID( cstr_t csBlockIdentifier, BlockTypeID_t &BlockTypeID ) const
		{
			assert( NULL != csBlockIdentifier );

			boost::mutex::scoped_lock Protector( m_BlockTypesMutex );

			BlockTypes_t::const_iterator iBlockTypeID = m_BlockTypes.find( csBlockIdentifier );
			if ( m_BlockTypes.end() == iBlockTypeID )
				return result_inv_args;

			BlockTypeID = iBlockTypeID->second;
			return result_ok;
		}

		result_t GetBlockTypeIdentifier( BlockTypeID_t BlockTypeID, cstr_t &csBlockIdentifier ) const
		{
			boost::mutex::scoped_lock Protector( m_BlockTypesMutex );

			if ( m_BlockIdentifiers.size() <= BlockTypeID )
				return result_inv_args;

			csBlockIdentifier = m_BlockIdentifiers[ BlockTypeID ].m_sIdentifier.c_str();

			return result_ok;
		}

		size_t GetBlockTypesCount() const
		{
			boost::mutex::scoped_lock Protector( m_BlockTypesMutex );
			return m_BlockIdentifiers.size();
		}
    
    NV_DECLARE_EVENT( CTFNotifyEvent )

      NV_PROCESS_EVENT_FUNCTION( CBlockDataService, OnTerminatorFinishedEvent( m_cpTerminator ) );
      CPtr< ITerminatorEx > m_cpTerminator;

    NV_DECLARE_EVENT_END

		result_t OnTerminatorFinished( ITerminatorEx * pTerminator )
		{
			assert( NULL != pTerminator );

			CPtr< CTFNotifyEvent > cpEvent = new CMTEntity< CTFNotifyEvent >;
			cpEvent->m_cpTerminator = pTerminator;

			return PostEvent( this, cpEvent );
		}

	protected:

		result_t CreateTerminator( cstr_t csTerminatorID, Json::Value const &Settings )
		{
			cstr_t csTypeIdentifier = "type";
			if ( Settings.isMember( csTypeIdentifier ) == false )
				return result_inv_args;

			Json::Value const &Type = Settings[ csTypeIdentifier ];

			cstr_t csSettingsIdentifier = "settings";
			if ( Settings.isMember( csSettingsIdentifier ) == false )
				return result_inv_args;

			Json::Value const &TerminatorSettings = Settings[ csSettingsIdentifier ];
			CPtr< ITerminatorEx > cpTerminator;

			if ( strcmp( Type.asCString(), "File" ) == 0 )
				cpTerminator = new( std::nothrow ) CMTEntity< CFileTerminator< CPureBinaryDataFlow > >;
			else if ( strcmp( Type.asCString(), "StructuredFile" ) == 0 )
				cpTerminator = new( std::nothrow ) CMTEntity< CFileTerminator< CStructuredBinaryDataFlow > >;
			else if ( strcmp( Type.asCString(), "TextFile" ) == 0 )
				cpTerminator = new( std::nothrow ) CMTEntity< CFileTerminator< CTextDataFlow > >;
//			else if ( strcmp( Type.asCString(), "Network" ) == 0 )
//				cpTerminator = new( std::nothrow ) CMTEntity< CNetworkTerminator< CPureBinaryDataFlow > >;
			else
				return result_inv_args;

			if ( cpTerminator.Get() ) {

				NV_CRR( cpTerminator->Initialize( this, TerminatorSettings ) );
				m_Terminators[ csTerminatorID ] = cpTerminator;

				return result_ok;

			}

			return result_inv_args;
		}

/*		result_t CreateCollector( cstr_t csCollectorID, Json::Value const &Settings )
		{
			CPtr< ICollector > cpCollector = new( std::nothrow ) CMTEntity< CCollector >;
			if ( cpCollector.Get() == NULL )
				return result_out_of_memory;

			NV_CRR( cpCollector->Initialize( this, csCollectorID, Settings ) );
			m_Collectors[ csCollectorID ] = cpCollector;

			return result_ok;
		}*/

		result_t OnTerminatorFinishedEvent( ITerminatorEx * pTerminator )
		{
			for ( CTerminatorsList::iterator iTerminator = m_Terminators.begin(); m_Terminators.end() != iTerminator; ++iTerminator )
				if ( iTerminator->second == pTerminator ) {

					m_Terminators.erase( iTerminator );
					break;

				}

			CheckFinishingStatus();

			return result_ok;
		}

		void CheckFinishingStatus()
		{
			if ( m_FinishOperationID && m_Terminators.empty() ) {

				GetNodeManager()->ServiceReport( this, m_FinishOperationID, result_ok, "The service is finished");
				m_FinishOperationID = 0;

			}
		}

	private:

		OperationID_t m_FinishOperationID;

		typedef std::map< std::string, CPtr< ITerminatorEx > > CTerminatorsList;
		CTerminatorsList m_Terminators;

		typedef std::map< std::string, CPtr< ICollector > > CCollectors;

		CCollectors m_Collectors;

		mutable boost::mutex m_BlockTypesMutex;

		typedef std::map< std::string, BlockTypeID_t > BlockTypes_t;
		BlockTypes_t m_BlockTypes;

		struct BlockInfo_t {

			std::string m_sIdentifier;
			CBlockFactoryPtr m_cpFactory;

		};

		typedef std::vector< BlockInfo_t > BlockIdentifiers_t;
		BlockIdentifiers_t m_BlockIdentifiers;

	};

	class CBlockDataServicesFactory:
		public IServicesFactory
	{
	public:

		size_t GetServiceTypesCount() const
		{ return 1; }

		cstr_t GetServiceTypeID( size_t nIndex ) const
		{
			assert( 0 == nIndex );
			return g_csBDSIdentifier;
		}

		cstr_t GetServiceMetainfo( size_t nIndex ) const
		{
			assert( 0 == nIndex );
			return "{}";
		}

		result_t Create( cstr_t csServiceTypeID, cstr_t csServiceIdentififer, CServicePtr &cpService )
		{
			assert( NULL != csServiceTypeID );
			assert( strcmp( csServiceTypeID, g_csBDSIdentifier ) == 0 );

			cpService = new( std::nothrow ) CMTEntity< CBlockDataService >;
			return cpService.Get() ? result_ok : result_out_of_memory;
		}

	};

	result_t CreateServicesFactory( CServicesFactoryPtr &cpFactory )
	{
		cpFactory = new( std::nothrow ) CMTEntity< CBlockDataServicesFactory >;
		return cpFactory.Get() ? result_ok : result_out_of_memory;
	}

} // namespace bds
} // namespace nvl
