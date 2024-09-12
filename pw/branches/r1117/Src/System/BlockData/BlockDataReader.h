#ifndef __BLOCKDATAREADER_H_INCLUDED__338373__
#define __BLOCKDATAREADER_H_INCLUDED__338373__

#include "BlockData.h"

#include <fstream>
#include <vector>

namespace nvl {
namespace bds {

	class CBlockDataReader
	{
	public:

		enum { MaxBlockSize = 4 * 1024 * 1024 }; // 4 Mb

		CBlockDataReader( IBlockDataService *pBDS ): m_cpBDS( pBDS )
		{ assert( NULL != pBDS ); }

		result_t Open( cstr_t csSourceFileName )
		{
			assert( NULL != csSourceFileName );

			m_File.open( csSourceFileName, std::ios::binary );
			if ( m_File.is_open() == false )
				return result_fail;

			m_Buffer.clear();
			m_Reader.Clear();
			m_NextReader.Clear();
			m_IDCorrespondence.clear();

			return result_ok;
		}

		result_t GetNextBlock( cstr_t * pcsBlockIdentifier, BlockTypeID_t * pBlockID )
		{
			while ( m_Reader.GetDataSize() > 0 || m_File.eof() == false ) {

				if ( m_NextReader.IsValid() ) {

					m_Reader = m_NextReader;
					m_NextReader.Clear();
					continue;

				}

				uint32_t nBlockSize = 0;
				NV_CRR( PrepareFileData( sizeof( m_CurrentID ) + sizeof( nBlockSize ) ) );

				m_Reader
					>> m_CurrentID
					>> nBlockSize;

				NV_CRR( PrepareFileData( nBlockSize ) );

				m_NextReader = m_Reader;
				m_NextReader.Seek( nBlockSize );

				if ( UndefinedBlockType == m_CurrentID ) {

					BlockTypeID_t BlockID;

					m_Reader
						>> BlockID
						>> m_sBlockIdentifier;

					NV_CRR( RegisterBlockType( BlockID, m_sBlockIdentifier ) );

					m_NextReader.Clear();
					continue;

				}

				if ( m_IDCorrespondence.size() <= m_CurrentID || UndefinedBlockType == m_IDCorrespondence[ m_CurrentID ].m_ID ) {

					return result_fail;

				}

				if ( pcsBlockIdentifier )
					*pcsBlockIdentifier = m_IDCorrespondence[ m_CurrentID ].m_sIdentifier.c_str();

				m_CurrentID = m_IDCorrespondence[ m_CurrentID ].m_ID;

				if ( pBlockID )
					*pBlockID = m_CurrentID;

				return result_ok;

			}

			return result_false;
		}

		result_t LoadBlock( CBlockServices *pBlock )
		{
			assert( NULL != pBlock );

			if ( m_NextReader.IsValid() == false || pBlock->GetBlockTypeID() != m_CurrentID )
				return result_impossible_action;

			result_t Result = pBlock->FromBinary( m_Reader );
			assert( NV_CFAIL( Result ) || m_Reader == m_NextReader );

			return Result;
		}

	protected:

		result_t PrepareFileData( size_t nDataSize )
		{
			if ( m_Reader.GetDataSize() < nDataSize ) {

				if ( m_File.is_open() == false )
					return result_fail;

				if ( m_Reader.GetDataSize() )
					m_Buffer.erase( m_Buffer.begin(), m_Buffer.end() - m_Reader.GetDataSize() );
				else
					m_Buffer.clear();

				size_t nBlockSize = std::max< size_t >( nDataSize, MaxBlockSize );

				size_t nToReadSize = nBlockSize - m_Buffer.size();
				m_Buffer.resize( nBlockSize );

				m_File.read( &m_Buffer[ m_Buffer.size() - nToReadSize ], nToReadSize );

				size_t nTotalSize = nBlockSize - nToReadSize + m_File.gcount();
				if ( m_Buffer.size() != nTotalSize ) {

					if ( nTotalSize < nDataSize )
						return result_fail;

					m_Buffer.resize( nTotalSize );

				}

				m_Reader.SetData( &m_Buffer[ 0 ] );
				m_Reader.SetDataSize( m_Buffer.size() );

			}

			return result_ok;
		}

		result_t RegisterBlockType( BlockTypeID_t ID, std::string const &csIdentifier )
		{
			if ( m_IDCorrespondence.size() > ID && m_IDCorrespondence[ ID ].m_ID != UndefinedBlockType ) {

				return result_inv_args;

			}

			BlockTypeID_t BDSBlockTypeID = 0;
			NV_CRR( m_cpBDS->GetBlockTypeID( csIdentifier.c_str(), BDSBlockTypeID ) );

			if ( m_IDCorrespondence.size() <= ID )
				m_IDCorrespondence.resize( ID + 1 );

			m_IDCorrespondence[ ID ].m_ID = BDSBlockTypeID;

			cstr_t csBDSIdentifier = NULL;
			NV_CRR( m_cpBDS->GetBlockTypeIdentifier( BDSBlockTypeID, csBDSIdentifier ) );
			m_IDCorrespondence[ ID ].m_sIdentifier = csBDSIdentifier;

			return result_ok;
		}

	private:

		CBlockDataServicePtr m_cpBDS;

		std::ifstream m_File;
		std::vector< char > m_Buffer;

		CBinaryBufferReader m_Reader;
		CBinaryBufferReader m_NextReader;

		BlockTypeID_t m_CurrentID;
		std::string m_sBlockIdentifier;

		struct BlockInfo {

			BlockInfo(): m_ID( UndefinedBlockType )
			{}

			BlockTypeID_t m_ID;
			std::string m_sIdentifier;

		};

		typedef std::vector< BlockInfo > IDCorrespondence_t;

		IDCorrespondence_t m_IDCorrespondence;

	};

} // namespace bds
} // namespace nvl

#endif // __BLOCKDATAREADER_H_INCLUDED__338373__
