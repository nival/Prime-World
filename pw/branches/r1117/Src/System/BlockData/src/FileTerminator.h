#ifndef __FILETERMINATOR_H_INCLUDED__809898__
#define __FILETERMINATOR_H_INCLUDED__809898__

#include "BlockDataCommon.h"
#include "get_tick_count.h"
#include <fstream>

namespace nvl {
namespace bds {

	cstr_t const g_csFileTerminatorsThreadIdentififer = "BDS File Terminators Thread";

	template< typename T > class CFileDataFlow:
		public T
	{
	public:

		CFileDataFlow( cstr_t csFlowIdentifier ):
			T( csFlowIdentifier ),
			m_nLastWriteTime( nival::get_tick_count() )
		{}

		result_t Initialize( std::string const &csFileName )
		{
			m_File.open( csFileName.c_str(), std::ios::binary );

			if ( m_File.is_open() == false )
				return result_inv_args;

			return result_ok;
		}

		uint32_t GetLastWriteTime() const
		{ return m_nLastWriteTime; }

		result_t WriteData( bool bIsFinal )
		{
			if ( this -> GetFlowSize() ) {

				m_File.write( this -> GetFlowData(), this -> GetFlowSize() );
				if ( m_File.fail() )
					return result_fail;

				this -> GetBuffer().Clear();

			}

			m_nLastWriteTime = nival::get_tick_count();

			if ( bIsFinal )
				m_File.close();

			return result_ok;
		}

	private:

		std::ofstream m_File;
		uint32_t m_nLastWriteTime;

	};

	template< typename T > class CFileTerminator:
		public CTerminatorBase
	{
	public:

		typedef CFileDataFlow< T > DataFlow_t;

		CFileTerminator(): m_nMaxWriteDelay( 5000 )
		{}

		result_t Initialize( IBlockDataServiceEx * pBDS, Json::Value const &Settings )
		{
			assert( NULL != pBDS );

			cstr_t const csFolderIdentifier = "folder";
			if ( Settings.size() != 1 || Settings.isMember( csFolderIdentifier ) == false )
				return result_inv_args;

			m_sFolder = Settings[ csFolderIdentifier ].asCString();
			if ( m_sFolder.empty() )
				return result_inv_args;

			if ( '/' != *m_sFolder.rbegin() && '\\' != *m_sFolder.rbegin() )
				m_sFolder += '/';

			CPtr< IThreadManager > cpThreadManager = pBDS->GetNodeManager()->GetThreadManager();

			CPtr< IEventsThread > cpThread;
			if ( NV_CFAIL( cpThreadManager->GetThreadByIdentifier( g_csFileTerminatorsThreadIdentififer, cpThread ) ) ) {

				NV_CRR( cpThreadManager->CreateEventsThread( g_csFileTerminatorsThreadIdentififer, cpThread ) );
				NV_CRR( cpThreadManager->StartThread( cpThread ) );

			}

			return CTerminatorBase::Initialize( pBDS, cpThread, 100, 500 );
		}

	protected:

		result_t AllocateDataFlow( cstr_t csFlowIdentifier, CPtr< CDataFlow > &cpFlow )
		{
			CPtr< DataFlow_t > cpFileDataFlow = new CMTEntity< DataFlow_t >( csFlowIdentifier );
			NV_CRR( cpFileDataFlow->Initialize( m_sFolder + csFlowIdentifier ) );

			return cpFileDataFlow.Detach( cpFlow );
		}

		static bool DataFlowsSortTime( DataFlow_t const * pFirst, DataFlow_t const * pSecond )
		{ return ( pSecond->GetLastWriteTime() - pFirst->GetLastWriteTime() ) < 0x7FFFFFFF; }

		static bool DataFlowsSortSize( DataFlow_t const * pFirst, DataFlow_t const * pSecond )
		{ return pFirst->GetFlowSize() < pSecond->GetFlowSize(); }

		result_t WriteData( bool bIsFinal )
		{
			uint32_t nCurrentTick = GetTickCount();
			m_DataFlowsToProcess.clear();
			m_AdditionalFlows.clear();

			if ( bIsFinal ) {

				for ( DataFlows_t::const_iterator iDataFlow = m_DataFlows.begin(); m_DataFlows.end() != iDataFlow; ++iDataFlow )
					m_AdditionalFlows.push_back( static_cast< DataFlow_t * >( iDataFlow->Get() ) );

			} else {

				for ( DataFlows_t::const_iterator iDataFlow = m_DataFlows.begin(); m_DataFlows.end() != iDataFlow; ++iDataFlow ) {

					DataFlow_t * pDataFlow = static_cast< DataFlow_t * >( iDataFlow->Get() );

					if ( nCurrentTick - pDataFlow->GetLastWriteTime() >= m_nMaxWriteDelay )
						m_DataFlowsToProcess.push_back( pDataFlow );
					else
						m_AdditionalFlows.push_back( pDataFlow );

				}

			}

			std::sort( m_DataFlowsToProcess.begin(), m_DataFlowsToProcess.end(), &DataFlowsSortTime );
			std::sort( m_AdditionalFlows.begin(), m_AdditionalFlows.end(), &DataFlowsSortSize );

			m_DataFlowsToProcess.insert( m_DataFlowsToProcess.end(), m_AdditionalFlows.begin(), m_AdditionalFlows.end() );

			for ( typename DataFlowsToProcess_t::iterator iDataFlow = m_DataFlowsToProcess.begin(); m_DataFlowsToProcess.end() != iDataFlow; ++iDataFlow ) {

				if ( false == bIsFinal && GetTickCount() - nCurrentTick >= m_nWriteDataPeriod )
					break;

				(*iDataFlow)->WriteData( bIsFinal );

			}

			return result_ok;
		}

	private:

		std::string m_sFolder;
		uint32_t m_nMaxWriteDelay;

		typedef std::vector< DataFlow_t * > DataFlowsToProcess_t;
		DataFlowsToProcess_t m_DataFlowsToProcess;
		DataFlowsToProcess_t m_AdditionalFlows;

	};

} // namespace bds
} // namespace nvl

#endif // __FILETERMINATOR_H_INCLUDED__809898__
