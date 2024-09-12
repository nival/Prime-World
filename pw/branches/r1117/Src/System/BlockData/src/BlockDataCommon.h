#ifndef __BLOCKDATACOMMON_H_INCLUDED__778280__
#define __BLOCKDATACOMMON_H_INCLUDED__778280__

#include <System/Node/PoolableEntity.h>
#include <System/BlockData/BlockData.h>

#include <json/reader.h>

namespace nvl {
namespace bds {

	class CBlocksStackGuard
	{
	public:

		CBlocksStackGuard( IBlock * pStack ): m_BlocksStack( pStack )
		{}

		~CBlocksStackGuard()
		{
			if ( m_BlocksStack )
				DestroyStack( m_BlocksStack );
		}

		IBlock * Get() const
		{ return m_BlocksStack; }

	private:

		IBlock * m_BlocksStack;

	};

	class CDataFlow:
		public IEntity
	{
	public:

		CDataFlow( cstr_t csFlowIdentifier ):
			m_bIsClosed( false )
//			m_nProcessedDataSize( 0 ),
//			m_nProcessingDataSize( 0 )
		{
			assert( NULL != csFlowIdentifier );
			m_sFlowIdentifier = csFlowIdentifier;
		}

		cstr_t GetFlowIdentifier() const
		{ return m_sFlowIdentifier.c_str(); }

		void ProxyClosedNotify()
		{ SetIsClosed(); }

		bool IsClosed() const
		{ return m_bIsClosed; }

		virtual result_t StoreBlock( CBlockServices const &Block ) = 0;
		virtual result_t StoreBinaryData( BlockTypeID_t BlockTypeID, void const * pData, size_t nDataSize ) = 0;

		result_t EnqueueBlock( IBlock * pBlock )
		{
			assert( NULL != pBlock );

			m_Blocks.Push( pBlock );
			return result_ok;
		}

		virtual result_t ProcessBlocks( IBlockDataService * pBDS ) = 0;

		virtual cstr_t GetFlowData() const = 0;
		virtual size_t GetFlowSize() const = 0;

		virtual result_t WriteData( bool bIsFinal ) = 0;

//		uint64_t GetProcessedDataSize() const
//		{ return m_nProcessedDataSize; }

//		void SetProcessedDataSize( uint64_t nSize )
//		{ m_nProcessedDataSize = nSize; }

//		size_t GetProcessingDataSize() const
//		{ return m_nProcessingDataSize; }

//		void SetProcessingDataSize( size_t nNewSize )
//		{ m_nProcessingDataSize = nNewSize; }

	protected:

		void SetIsClosed()
		{ m_bIsClosed = true; }

		IBlock * GetBlocksStack()
		{ return m_Blocks.PopReversedStack(); }

	private:

		CLFStack< IBlock > m_Blocks;

		std::string m_sFlowIdentifier;
		volatile bool m_bIsClosed;
//		uint64_t m_nProcessedDataSize;
//		size_t m_nProcessingDataSize;

	};

	class CDataFlowProxy:
		public CStackableEntity,
		public IDataFlow
	{
	public:

		~CDataFlowProxy()
		{
			if ( m_cpDataFlow.Get() )
				m_cpDataFlow->ProxyClosedNotify();
		}

		void Initialize( CDataFlow * pDataFlow )
		{
			assert( NULL != pDataFlow );
			m_cpDataFlow = pDataFlow;
		}

		void CleanEntity()
		{
			if ( m_cpDataFlow.Get() ) {

				m_cpDataFlow->ProxyClosedNotify();
				m_cpDataFlow.Release();

			}
		}

		result_t StoreBlock( CBlockServices const &Block )
		{ return m_cpDataFlow->StoreBlock( Block ); }

		result_t StoreBinaryData( BlockTypeID_t BlockTypeID, void const * pData, size_t nDataSize )
		{ return m_cpDataFlow->StoreBinaryData( BlockTypeID, pData, nDataSize ); }

		result_t EnqueueBlock( IBlock * pBlock )
		{ return m_cpDataFlow->EnqueueBlock( pBlock ); }

	private:

		CPtr< CDataFlow > m_cpDataFlow;

	};

	class CBinaryBlock:
		public IBlock
	{
	public:

		BlockTypeID_t GetBlockTypeID() const
		{ return m_BlockTypeID; }

		result_t ToBinary( CBinaryBuffer &Buffer ) const
		{
			Buffer.Write( GetBuffer() );
			return result_ok;
		}

		void CleanEntity()
		{ m_Buffer.Clear(); }

		void SetBlockTypeID( BlockTypeID_t ID )
		{ m_BlockTypeID = ID; }

		CBinaryBuffer & GetBuffer()
		{ return m_Buffer; }

		CBinaryBuffer const & GetBuffer() const
		{ return m_Buffer; }

	private:

		BlockTypeID_t m_BlockTypeID;
		CBinaryBuffer m_Buffer;

	};

	class CBinaryDataFlow:
		public CDataFlow
	{
	public:

		CBinaryDataFlow( cstr_t csFlowIdentifier ): CDataFlow( csFlowIdentifier )
		{}

		result_t StoreBlock( CBlockServices const &Block )
		{
			CPtr< CBinaryBlock > cpBlock = CPoolableMTEntity< CBinaryBlock >::Create();
			assert( cpBlock.Get() != NULL );

			cpBlock->SetBlockTypeID( Block.GetBlockTypeID() );
			NV_CRR( Block.ToBinary( cpBlock->GetBuffer() ) );

			return EnqueueBlock( cpBlock.Detach() );
		}

		result_t StoreBinaryData( BlockTypeID_t BlockTypeID, void const * pData, size_t nDataSize )
		{
			CPtr< CBinaryBlock > cpBlock = CPoolableMTEntity< CBinaryBlock >::Create();
			assert( cpBlock.Get() != NULL );

			cpBlock->SetBlockTypeID( BlockTypeID );
			cpBlock->GetBuffer().Write( pData, nDataSize );

			return EnqueueBlock( cpBlock.Detach() );
		}

		CBinaryBuffer & GetBuffer()
		{ return m_Buffer; }

		CBinaryBuffer const & GetBuffer() const
		{ return m_Buffer; }

		cstr_t GetFlowData() const
		{ return m_Buffer.GetData(); }

		size_t GetFlowSize() const
		{ return m_Buffer.GetSize(); }

	private:

		CBinaryBuffer m_Buffer;

	};

	class CPureBinaryDataFlow:
		public CBinaryDataFlow
	{
	public:

		CPureBinaryDataFlow( cstr_t csFlowIdentifier ): CBinaryDataFlow( csFlowIdentifier )
		{}

		result_t ProcessBlocks( IBlockDataService * pBDS )
		{
			CBlocksStackGuard Blocks = GetBlocksStack();

			IBlock * pBlock = Blocks.Get();
			while ( pBlock ) {

				if ( NV_CFAIL( pBlock->ToBinary( GetBuffer() ) ) ) {
				}

				pBlock->GetNextEntity( pBlock );

			}

			return result_ok;
		}

	};

	class CStructuredBinaryDataFlow:
		public CBinaryDataFlow
	{
	public:

		CStructuredBinaryDataFlow( cstr_t csFlowIdentifier ): CBinaryDataFlow( csFlowIdentifier )
		{}

		result_t ProcessBlocks( IBlockDataService * pBDS )
		{
			assert( NULL != pBDS );

			CBlocksStackGuard Blocks = GetBlocksStack();

			IBlock * pBlock = Blocks.Get();
			while ( pBlock ) {

				BlockTypeID_t ID = pBlock->GetBlockTypeID();

				if ( m_StoredBlockTypes.size() <= ID )
					m_StoredBlockTypes.resize( ID + 1, false );

				if ( false == m_StoredBlockTypes[ ID ] ) {

					cstr_t csBlockIdentifier = NULL;
					if ( NV_CFAIL( pBDS->GetBlockTypeIdentifier( ID, csBlockIdentifier ) ) ) {
					}

					uint32_t nIdentifierLength = csBlockIdentifier ? strlen( csBlockIdentifier ) : 0;

					GetBuffer()
						<< UndefinedBlockType
						<< uint32_t( sizeof( ID ) + sizeof( uint32_t ) + nIdentifierLength )
						<< ID
						<< nIdentifierLength;

					if ( nIdentifierLength )
						GetBuffer().Write( csBlockIdentifier, nIdentifierLength );

					m_StoredBlockTypes[ ID ] = true;

				}

				GetBuffer() << ID;

				size_t nBlockSizeOffset = GetBuffer().GetSize();
				GetBuffer() << BlockSize_t( -1 );

				if ( NV_CFAIL( pBlock->ToBinary( GetBuffer() ) ) ) {
				}

				BlockSize_t nBlockSize = GetBuffer().GetSize() - nBlockSizeOffset - sizeof( BlockSize_t );
				GetBuffer().Write( nBlockSizeOffset, &nBlockSize, sizeof( nBlockSize ) );

				pBlock->GetNextEntity( pBlock );

			}

			return result_ok;
		}

	private:

		typedef std::vector< bool > StoredBlockTypes_t;
		StoredBlockTypes_t m_StoredBlockTypes;

	};

	class CTextBlock:
		public IBlock
	{
	public:

		BlockTypeID_t GetBlockTypeID() const
		{ return m_BlockTypeID; }

		result_t ToBinary( CBinaryBuffer &Buffer ) const
		{ return result_not_impl; }

		result_t ToText( CTextBuffer &Buffer ) const
		{
			Buffer << GetBuffer();
			return result_ok;
		}

		void CleanEntity()
		{ m_Buffer.Clear(); }

		void SetBlockTypeID( BlockTypeID_t ID )
		{ m_BlockTypeID = ID; }

		CTextBuffer & GetBuffer()
		{ return m_Buffer; }

		CTextBuffer const & GetBuffer() const
		{ return m_Buffer; }

	private:

		BlockTypeID_t m_BlockTypeID;
		CTextBuffer m_Buffer;

	};

	class CTextDataFlow:
		public CDataFlow
	{
	public:

		CTextDataFlow( cstr_t csFlowIdentifier ): CDataFlow( csFlowIdentifier )
		{}

		result_t StoreBlock( CBlockServices const &Block )
		{
			CPtr< CTextBlock > cpBlock = CPoolableMTEntity< CTextBlock >::Create();
			assert( cpBlock.Get() != NULL );

			cpBlock->SetBlockTypeID( Block.GetBlockTypeID() );
			NV_CRR( Block.ToText( cpBlock->GetBuffer() ) );

			return EnqueueBlock( cpBlock.Detach() );
		}

		result_t StoreBinaryData( BlockTypeID_t BlockTypeID, void const * pData, size_t nDataSize )
		{ return result_impossible_action; }

		CTextBuffer & GetBuffer()
		{ return m_Buffer; }

		CTextBuffer const & GetBuffer() const
		{ return m_Buffer; }

		cstr_t GetFlowData() const
		{ return m_Buffer.GetData(); }

		size_t GetFlowSize() const
		{ return m_Buffer.GetSize(); }

		result_t ProcessBlocks( IBlockDataService * pBDS )
		{
			CBlocksStackGuard Blocks = GetBlocksStack();

			IBlock * pBlock = Blocks.Get();
			while ( pBlock ) {

				if ( NV_CFAIL( pBlock->ToText( GetBuffer() ) ) ) {
				}

				pBlock->GetNextEntity( pBlock );

			}

			return result_ok;
		}

	private:

		CTextBuffer m_Buffer;

	};

	struct ITerminatorEx;

	struct IBlockDataServiceEx: IBlockDataService {

		virtual result_t OnTerminatorFinished( ITerminatorEx * pTerminator ) = 0;

	};

	struct ITerminatorEx: ITerminator {

		virtual result_t Initialize( IBlockDataServiceEx * pBDS, Json::Value const &Settings ) = 0;
		virtual result_t Close() = 0;

	};

	class CTerminatorBase:
		public ITerminatorEx
	{
	public:

		CTerminatorBase(): m_nProcessingBlocksPeriod( 0 ), m_nWriteDataPeriod( 0 )
		{}

		result_t Initialize( IBlockDataServiceEx * pBDS, IEventsThread * pOwnThread, uint32_t nProcessingBlocksPeriod, uint32_t nWriteDataPeriod )
		{
			assert( NULL != pBDS );
			assert( NULL != pOwnThread );

			m_cpBDS = pBDS;
			SetOwnThread( pOwnThread );

			m_nProcessingBlocksPeriod = nProcessingBlocksPeriod;
			NV_CRR( StartProcessingBlocks() );

			m_nWriteDataPeriod = nWriteDataPeriod;
			NV_CRR( StartWritingData() );

			return result_ok;
		}
    
    NV_DECLARE_EVENT( CCloseTerminatorEvent )
      NV_PROCESS_EVENT_FUNCTION( CTerminatorBase, CloseTerminator() );
    NV_DECLARE_EVENT_END

		result_t Close()
		{
			CPtr< CCloseTerminatorEvent > cpEvent = new CMTEntity< CCloseTerminatorEvent >;
			return PostEvent( NULL, cpEvent );
		}

		result_t CloseTerminator()
		{
			if ( m_cpProcessDataFlowsEvent.Get() ) {

				m_cpProcessDataFlowsEvent->Cancel();
				m_cpProcessDataFlowsEvent.Release();

			}

			if ( m_cpWriteDataEvent.Get() ) {

				m_cpWriteDataEvent->Cancel();
				m_cpWriteDataEvent.Release();

			}

			NV_CRR( ProcessDataFlows() );
			NV_CRR( WriteFlowsData( true ) );

			NV_CRR( m_cpBDS->OnTerminatorFinished( this ) );

			return result_ok;
		}

		NV_DECLARE_POOLABLE_EVENT( CRegisterDataFlowEvent )

			NV_PROCESS_EVENT_FUNCTION( CTerminatorBase, RegisterDataFlow( m_cpDataFlow ) );

			void CleanEntity()
			{ m_cpDataFlow.Release(); }

			CPtr< CDataFlow > m_cpDataFlow;

		NV_DECLARE_EVENT_END

		result_t CreateDataFlow( cstr_t csFlowIdentifier, CPtr< IDataFlow > &cpFlow )
		{
			assert( NULL != csFlowIdentifier );

			CRegisterDataFlowEventPtr cpEvent = CPoolableMTEntity< CRegisterDataFlowEvent >::Create();
			NV_CRR( AllocateDataFlow( csFlowIdentifier, cpEvent->m_cpDataFlow ) );
			NV_CRR( PostEvent( NULL, cpEvent ) );

			CPtr< CDataFlowProxy > cpProxy = CPoolableMTEntity< CDataFlowProxy >::Create();
			cpProxy->Initialize( cpEvent->m_cpDataFlow );

			return cpProxy.Detach( cpFlow );
		}

		result_t RegisterDataFlow( CDataFlow * pDataFlow )
		{
			assert( NULL != pDataFlow );

			if ( std::find( m_DataFlows.begin(), m_DataFlows.end(), pDataFlow ) == m_DataFlows.end() )
				m_DataFlows.push_back( pDataFlow );

			return result_ok;
		}

		IBlockDataService * GetBlockDataService() const
		{ return m_cpBDS; }

	protected:

		virtual result_t AllocateDataFlow( cstr_t csFlowIdentifier, CPtr< CDataFlow > &cpFlow ) = 0;
    
    NV_DECLARE_EVENT( CProcessDataFlowsEvent )
      NV_PROCESS_EVENT_FUNCTION( CTerminatorBase, ProcessDataFlows() );
    NV_DECLARE_EVENT_END

		result_t StartProcessingBlocks()
		{
			if ( m_cpProcessDataFlowsEvent.Get() )
				m_cpProcessDataFlowsEvent->Cancel();

			if ( 0 == m_nProcessingBlocksPeriod )
				return result_ok;

			m_cpProcessDataFlowsEvent = new CMTEntity< CProcessDataFlowsEvent >;
			return PostEvent( NULL, m_cpProcessDataFlowsEvent, m_nProcessingBlocksPeriod, m_nProcessingBlocksPeriod );
		}

		result_t ProcessDataFlows()
		{
			DataFlows_t::const_iterator iEnd = m_DataFlows.end();
			for ( DataFlows_t::const_iterator iDataFlow = m_DataFlows.begin(); iEnd != iDataFlow; ++iDataFlow ) {

				NV_CRR( ( *iDataFlow )->ProcessBlocks( GetBlockDataService() ) );
				if ( ( *iDataFlow )->IsClosed() )
					m_DataFlowsToRemove.push_back( *iDataFlow );

			}

			return result_ok;
		}
    
    NV_DECLARE_EVENT( CWriteDataEvent )
      NV_PROCESS_EVENT_FUNCTION( CTerminatorBase, WriteFlowsData( false ) );
    NV_DECLARE_EVENT_END

		result_t StartWritingData()
		{
			if ( m_cpWriteDataEvent.Get() )
				m_cpWriteDataEvent->Cancel();

			if ( 0 == m_nWriteDataPeriod )
				return result_ok;

			m_cpWriteDataEvent = new CMTEntity< CWriteDataEvent >;
			return PostEvent( NULL, m_cpWriteDataEvent, m_nWriteDataPeriod, m_nWriteDataPeriod );
		}

		result_t WriteFlowsData( bool bIsFinal )
		{
			NV_CRR( WriteData( bIsFinal ) );
			CheckRemovedFlows();

			return result_ok;
		}

		virtual result_t WriteData( bool bIsFinal ) = 0;

		void CheckRemovedFlows()
		{
			if ( m_DataFlowsToRemove.empty() == false ) {

				for ( DataFlowsToRemove_t::iterator iDataFlow = m_DataFlowsToRemove.begin(); m_DataFlowsToRemove.end() != iDataFlow; ++iDataFlow ) {

					if ( ( *iDataFlow )->GetFlowSize() == 0 ) {

						DataFlows_t::iterator i = std::find( m_DataFlows.begin(), m_DataFlows.end(), *iDataFlow );
						if ( m_DataFlows.end() != i )
							m_DataFlows.erase( i );

					}

				}

				m_DataFlowsToRemove.clear();

			}
		}

	protected:

		CPtr< IBlockDataServiceEx > m_cpBDS;

		uint32_t m_nProcessingBlocksPeriod;
		uint32_t m_nWriteDataPeriod;

		typedef std::list< CPtr< CDataFlow > > DataFlows_t;
		DataFlows_t m_DataFlows;

		typedef std::vector< CPtr< CDataFlow > > DataFlowsToRemove_t;
		DataFlowsToRemove_t m_DataFlowsToRemove;

		CEventPtr m_cpProcessDataFlowsEvent;
		CEventPtr m_cpWriteDataEvent;

	};

	enum PACKET_TYPES {

		SYNCHRONIZE_STATE_REQUEST,
		SYNCHRONIZE_STATE_RESPONSE,
		REGISTER_FLOW_REQUEST,
		REGISTER_FLOW_RESPONSE,
		FLOW_CLOSED_REQUEST,
		SEND_DATA_REQUEST,
		SEND_DATA_RESPONSE

	};

	typedef uint32_t TFlowID;
	typedef uint32_t TFlowKey;

	struct ICollector: IEventsReceiver {

		virtual result_t Initialize( IBlockDataServiceEx *pBDS, cstr_t csCollectorID, Json::Value const &Settings ) = 0;

	};

} // namespace bds
} // namespace nvl

#endif // __BLOCKDATACOMMON_H_INCLUDED__778280__
