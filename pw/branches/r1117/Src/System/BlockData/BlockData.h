#ifndef __BLOCKDATA_H_INCLUDED__854277__
#define __BLOCKDATA_H_INCLUDED__854277__

#include <System/Node/NodeManager.h>
#include <System/Node/PoolableEntity.h>
#include <System/Node/BinaryBuffer.h>
#include <System/Node/TextBuffer.h>

#include <vector>

namespace nvl {

	typedef uint16_t BlockTypeID_t;
	typedef uint32_t BlockSize_t;

	const cstr_t g_csBDSIdentifier = "BlockData Service";

	struct ITerminator;
	typedef CPtr< ITerminator > CTerminatorPtr;

	struct IBlockFactory;
	typedef CPtr< IBlockFactory > CBlockFactoryPtr;

	struct IBlockDataService: IService {

		virtual result_t GetTerminator( cstr_t csTerminatorID, CTerminatorPtr &cpTerminator ) const = 0;
		virtual result_t CreateTerminator( cstr_t csTerminatorID, cstr_t csSettings ) = 0;
		virtual result_t RegisterBlockType( IBlockFactory * pFactory, cstr_t csBlockIdentifier, BlockTypeID_t &ID ) = 0;
		virtual result_t GetBlockTypeID( cstr_t csBlockIdentifier, BlockTypeID_t &BlockTypeID ) const = 0;
		virtual result_t GetBlockTypeIdentifier( BlockTypeID_t BlockTypeID, cstr_t &csBlockIdentifier ) const = 0;
		virtual size_t GetBlockTypesCount() const = 0;

	};

	typedef CPtr< IBlockDataService > CBlockDataServicePtr;

	typedef size_t OperationID_t;

	const BlockTypeID_t UndefinedBlockType = 0;

	struct CBlockServices {

		virtual BlockTypeID_t GetBlockTypeID() const
		{ return UndefinedBlockType; }

		virtual result_t ToBinary( CBinaryBuffer &Buffer ) const = 0;

		virtual result_t ToText( CTextBuffer &Buffer ) const
		{ return result_not_impl; }

		virtual result_t FromBinary( CBinaryBufferReader &Buffer )
		{ return result_not_impl; }

	};

	struct IBlock: IEntity, CStackableEntity, CBlockServices {
	};

	typedef CPtr< IBlock > CBlockPtr;

	struct IBlockFactory: IEntity {

		IBlockFactory(): m_BlockTypeID( UndefinedBlockType )
		{}

		BlockTypeID_t GetBlockTypeID() const
		{ return m_BlockTypeID; }

		virtual result_t CreateFromBuffer( CBinaryBufferReader &Buffer, CBlockPtr &Block ) = 0;

	protected:

		BlockTypeID_t m_BlockTypeID;

	};

	struct IDataFlow: IEntity {

		virtual result_t StoreBlock( CBlockServices const &Block ) = 0;

		virtual result_t StoreBinaryData( BlockTypeID_t BlockTypeID, void const * pData, size_t nDataSize ) = 0;

		template< typename T > result_t EnqueueBlock( CPtr< T > &cpBlock )
		{ return EnqueueBlock( cpBlock.Detach() ); }

	protected:

		virtual result_t EnqueueBlock( IBlock * pBlock ) = 0;

	};

	struct ITerminator: IEventsReceiver {

		virtual result_t CreateDataFlow( cstr_t csFlowIdentifier, CPtr< IDataFlow > &cpFlow ) = 0;

	};

	#define NV_BLOCK_TYPE( __block_type )																	\
																											\
		class __block_type;																					\
		typedef ::nvl::CPtr< __block_type > __block_type##Ptr;												\
																											\
		class __block_type:																					\
			public ::nvl::IBlock																			\
		{																									\
		private:																							\
																											\
			CBlockFactoryPtr m_cpFactory;																	\
																											\
		public:																								\
																											\
			void SetFactory( IBlockFactory * pFactory )														\
			{																								\
				assert( NULL != pFactory );																	\
				m_cpFactory = pFactory;																		\
			}																								\
																											\
			BlockTypeID_t GetBlockTypeID() const															\
			{ return m_cpFactory->GetBlockTypeID(); }														\

	#define NV_BLOCK_TYPE_END																				\
		};																									\

	#define NV_BLOCK_TYPE_FACTORY( __block_type )															\
																											\
		class __block_type##Factory;																		\
		typedef nvl::CPtr< __block_type##Factory > __block_type##FactoryPtr;								\
																											\
		typedef nvl::CPoolableMTEntity< __block_type > __block_type##MTEntity;								\
		NV_POOLABLE_MT_ENTITY( __block_type );																\
																											\
		class __block_type##Factory:																		\
			public nvl::IBlockFactory																		\
		{																									\
		public:																								\
																											\
			static nvl::result_t Register( nvl::IBlockDataService *pBDS, __block_type##Factory **ppFactory )\
			{																								\
				assert( NULL != pBDS );																		\
																											\
				nvl::CPtr< __block_type##Factory > cpFactory;												\
				cpFactory = new( std::nothrow ) nvl::CMTEntity< __block_type##Factory >;					\
																											\
				NV_CRR( pBDS->RegisterBlockType( cpFactory, #__block_type, cpFactory->m_BlockTypeID ) );	\
																											\
				return ppFactory ? cpFactory.Detach( ppFactory ) : nvl::result_ok;							\
			}																								\
																											\
			nvl::result_t CreateFromPool( __block_type##Ptr &cpBlock )										\
			{																								\
				cpBlock = __block_type##MTEntity::Create();													\
				if ( cpBlock.Get() == NULL )																\
					cpBlock = new __block_type##MTEntity;													\
																											\
				cpBlock->SetFactory( this );																\
																											\
				return nvl::result_ok;																		\
			}																								\
																											\
			nvl::result_t CreateFromBuffer( nvl::CBinaryBufferReader &Buffer, nvl::CPtr< IBlock > &cpBlock )\
			{																								\

	#define NV_BLOCK_TYPE_FACTORY_END																		\
			}																								\
		};																									\

	namespace bds {

		result_t CreateServicesFactory( CServicesFactoryPtr &cpFactory );

	}

} // namespace nvl

#endif // __BLOCKDATA_H_INCLUDED__854277__
