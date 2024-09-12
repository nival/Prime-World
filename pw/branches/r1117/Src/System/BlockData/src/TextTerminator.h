#ifndef __TEXTTERMINATOR_H_INCLUDED__728231__
#define __TEXTTERMINATOR_H_INCLUDED__728231__

#include "BlockDataServices.h"
#include <fstream>

namespace nvl {
namespace bds {

	class CTextTerminator:
		public CTerminatorBase
	{
	public:

		typedef CFileDataFlow< CTextFlow > DataFlow_t;

		CTextTerminator(): m_nMaxWriteDelay( 5000 )
		{}

		result_t Initialize( IBlockDataService * pBDS, Json::Value const &Settings )
		{
			cstr_t const csFolderIdentifier = "folder";
			if ( Settings.size() != 1 || Settings.isMember( csFolderIdentifier ) == false )
				return result_inv_args;

			m_sFolder = Settings[ csFolderIdentifier ].asCString();
			if ( m_sFolder.empty() )
				return result_inv_args;

			if ( '/' != *m_sFolder.rbegin() && '\\' != *m_sFolder.rbegin() )
				m_sFolder += '/';

			return CTerminatorBase::Initialize( pBDS );
		}

	protected:

		result_t AllocateDataFlow( cstr_t csFlowIdentifier, CPtr< CDataFlowBase > &cpFlow )
		{
			CPtr< DataFlow_t > cpFileDataFlow = new CMTEntity< DataFlow_t >( this );
			NV_CRR( cpFileDataFlow->Initialize( m_sFolder + csFlowIdentifier ) );

			return cpFileDataFlow.Detach( cpFlow );
		}

		static bool DataFlowsSortTime( DataFlow_t const * pFirst, DataFlow_t const * pSecond )
		{ return ( pSecond->GetLastWriteTime() - pFirst->GetLastWriteTime() ) < 0x7FFFFFFF; }

		static bool DataFlowsSortSize( DataFlow_t const * pFirst, DataFlow_t const * pSecond )
		{ return pFirst->GetBufferSize() < pSecond->GetBufferSize(); }

		result_t WriteData()
		{
			uint32_t nCurrentTick = GetTickCount();
			m_DataFlowsToProcess.clear();
			m_AdditionalFlows.clear();

			for ( DataFlows_t::const_iterator iDataFlow = m_DataFlows.begin(); m_DataFlows.end() != iDataFlow; ++iDataFlow ) {

				DataFlow_t * pDataFlow = static_cast< DataFlow_t * >( iDataFlow->Get() );

				if ( nCurrentTick - pDataFlow->GetLastWriteTime() >= m_nMaxWriteDelay )
					m_DataFlowsToProcess.push_back( pDataFlow );
				else
					m_AdditionalFlows.push_back( pDataFlow );

			}

			std::sort( m_DataFlowsToProcess.begin(), m_DataFlowsToProcess.end(), &DataFlowsSortTime );
			std::sort( m_AdditionalFlows.begin(), m_AdditionalFlows.end(), &DataFlowsSortSize );

			m_DataFlowsToProcess.insert( m_DataFlowsToProcess.end(), m_AdditionalFlows.begin(), m_AdditionalFlows.end() );

			for ( DataFlowsToProcess_t::iterator iDataFlow = m_DataFlowsToProcess.begin(); m_DataFlowsToProcess.end() != iDataFlow; ++iDataFlow ) {

				if ( GetTickCount() - nCurrentTick >= m_nWriteDataPeriod )
					break;

				(*iDataFlow)->WriteBufferData();

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

#endif // __TEXTTERMINATOR_H_INCLUDED__728231__
