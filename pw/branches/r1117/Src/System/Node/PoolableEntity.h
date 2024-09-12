#ifndef __POOLABLE_ENTITY_H_INCLUDED__402809__
#define __POOLABLE_ENTITY_H_INCLUDED__402809__

#include "Entity.h"
#include "Stack.h"
#include "LockFreeStack.h"

#include <boost/thread/tss.hpp>

namespace nvl {

	inline void InitEntity()
	{}

	inline void CleanEntity()
	{}

	template < typename T > class CPoolableEntity:
		public CEntity< T >
	{
	public:

		CPoolableEntity() {}

		template< typename T1 > CPoolableEntity( T1 &V1 ): CEntity< T >( V1 ) {}
		template< typename T1 > CPoolableEntity( T1 const &V1 ): CEntity< T >( V1 ) {}

		template< typename T1, typename T2 > CPoolableEntity( T1 &V1, T2 &V2 ): CEntity< T >( V1, V2 ) {}
		template< typename T1, typename T2 > CPoolableEntity( T1 const &V1, T2 const &V2 ): CEntity< T >( V1, V2 ) {}

		template< typename T1, typename T2, typename T3 > CPoolableEntity( T1 &V1, T2 &V2, T3 &V3 ):
			CEntity< T >( V1, V2, V3 ) {}

		template< typename T1, typename T2, typename T3 > CPoolableEntity( T1 const &V1, T2 const &V2, T3 const &V3 ):
			CEntity< T >( V1, V2, V3 ) {}

		template< typename T1, typename T2, typename T3, typename T4 >
			CPoolableEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4 ): CEntity< T >( V1, V2, V3, V4 ) {}

		template< typename T1, typename T2, typename T3, typename T4 >
			CPoolableEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4 ): CEntity< T >( V1, V2, V3, V4 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5 >
			CPoolableEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5 ):
			CEntity< T >( V1, V2, V3, V4, V5 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5 >
			CPoolableEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5 ):
			CEntity< T >( V1, V2, V3, V4, V5 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
			CPoolableEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
			CPoolableEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
			CPoolableEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6, V7 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
			CPoolableEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6, V7 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
			CPoolableEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6, V7, V8 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
			CPoolableEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6, V7, V8 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
			CPoolableEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6, V7, V8, V9 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
			CPoolableEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6, V7, V8, V9 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
			CPoolableEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9, T10 &V10 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
			CPoolableEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9, T10 const &V10 ):
			CEntity< T >( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ) {}

		static T * Create()
		{
			CPoolableEntity * pEntity;

			if ( m_cpPool.Get() )
				pEntity = m_cpPool->Pop();

			if ( NULL == pEntity )
				pEntity = new CPoolableEntity;

			if ( pEntity ) {

				pEntity->m_cpOwnPool = m_cpPool;
				pEntity->InitEntityInternal();

			}

			return pEntity;
		}

		void ReleaseReference()
		{
			if ( 0 == --(this -> m_nRFCount) ) {

				if ( m_cpOwnPool.Get() == NULL || m_cpPool.Get() == NULL )
					DestroyEntity();
				else {

					m_cpOwnPool.Release();
					CleanEntity();
					m_cpPool->Push( this );

				}

			}
		}

		virtual cstr_t GetClassIdentifier() const
		{
#if defined( NV_WIN_PLATFORM )
			return typeid( *this ).raw_name();	// call UnDecorateSymbolName to undecorate
#elif defined( NV_LINUX_PLATFORM )
			return typeid( *this ).name();		// To undecorate use #include <cxxabi.h> or c++filt utility
#endif
		}

		void DestroyEntity()
		{ delete this; }

	protected:

		void InitEntityInternal()
		{ InitEntity(); }

	protected:

		class CEntityPool:
			public IEntity
		{
		public:

			~CEntityPool()
			{
				for ( typename Entities_t::iterator iEntity = m_Entities.begin(); m_Entities.end() != iEntity; ++iEntity )
					CPtr< T > cpEntity = *iEntity;
			}

			void Push( CPoolableEntity * pEntity )
			{
				assert( NULL != pEntity );
				m_Entities.push_back( pEntity );
			}

			CPoolableEntity * Pop()
			{
				if ( m_Entities.empty() )
					return NULL;

				CPoolableEntity * pEntity = m_Entities.back();
				m_Entities.pop_back();

				return pEntity;
			}

		private:

			typedef std::list< CPoolableEntity * > Entities_t;
			Entities_t m_Entities;

		};

	protected:

		CPtr< CEntityPool > m_cpOwnPool;
		static CPtr< CEntityPool > m_cpPool;

	};

	#define NV_POOLABLE_ENTITY( __entity )								\
		typedef CPoolableEntity< __entity > __entity##Entity;	\
		CPtr< __entity##Entity::CEntityPool > __entity##Entity::m_cpPool( new CEntity< __entity##Entity::CEntityPool > );

	template < typename T > class CPoolableMTEntity:
		public CMTEntity< T >
	{
	public:

		CPoolableMTEntity() {}

		template< typename T1 > CPoolableMTEntity( T1 &V1 ): T( V1 ) {}
		template< typename T1 > CPoolableMTEntity( T1 const &V1 ): T( V1 ) {}

		template< typename T1, typename T2 > CPoolableMTEntity( T1 &V1, T2 &V2 ): T( V1, V2 ) {}
		template< typename T1, typename T2 > CPoolableMTEntity( T1 const &V1, T2 const &V2 ): T( V1, V2 ) {}

		template< typename T1, typename T2, typename T3 >
			CPoolableMTEntity( T1 &V1, T2 &V2, T3 &V3 ): T( V1, V2, V3 ) {}

		template< typename T1, typename T2, typename T3 >
			CPoolableMTEntity( T1 const &V1, T2 const &V2, T3 const &V3 ): T( V1, V2, V3 ) {}

		template< typename T1, typename T2, typename T3, typename T4 >
			CPoolableMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4 ):
			T( V1, V2, V3, V4 ) {}

		template< typename T1, typename T2, typename T3, typename T4 >
			CPoolableMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4 ):
			T( V1, V2, V3, V4 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5 >
			CPoolableMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5 ):
			T( V1, V2, V3, V4, V5 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5 >
			CPoolableMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5 ):
			T( V1, V2, V3, V4, V5 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
			CPoolableMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6 ):
			T( V1, V2, V3, V4, V5, V6 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
			CPoolableMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6 ):
			T( V1, V2, V3, V4, V5, V6 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
			CPoolableMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7 ):
			T( V1, V2, V3, V4, V5, V6, V7 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
			CPoolableMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7 ):
			T( V1, V2, V3, V4, V5, V6, V7 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
			CPoolableMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
			CPoolableMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
			CPoolableMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
			CPoolableMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
			CPoolableMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9, T10 &V10 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
			CPoolableMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9, T10 const &V10 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ) {}

		static T * Create()
		{
			CPtr< CStack > * pStack = m_Pool.get();
			if ( NULL == pStack ) {

				pStack = new CPtr< CStack >( new CMTEntity< CStack > );
				m_Pool.reset( pStack );

			}

			CPoolableMTEntity * pEntity = ( *pStack )->Pop();
			if ( NULL == pEntity )
				pEntity = new CPoolableMTEntity;

			if ( pEntity ) {

				pEntity->m_cpOwnPool = *pStack;
				pEntity->InitEntityInternal();

			}

			return pEntity;
		}

		void ReleaseReference()
		{
			if ( 0 == --(this -> m_RFCount) ) {

				CleanEntity();

				if ( m_cpOwnPool.Get() ) {

					CPtr< CStack > cpPool( m_cpOwnPool.Detach(), attach );
					cpPool->Push( this );

				} else
					delete this;

			}
		}

		cstr_t GetClassIdentifier() const
		{
#if defined( NV_WIN_PLATFORM )
			return typeid( *this ).raw_name();
#elif defined( NV_LINUX_PLATFORM )
			return typeid( *this ).name();
#endif
		}

		void DestroyEntity()
        { CPtr< CPoolableMTEntity > cpEntity( this, attach ); }

	public:

		struct CStack:
			IEntity,
			CLFStack< CPoolableMTEntity >
		{};

	protected:

		void InitEntityInternal()
		{ InitEntity(); }

	protected:

		CPtr< CStack > m_cpOwnPool;

		static boost::thread_specific_ptr< CPtr< CStack > > m_Pool;

	};

	#define NV_POOLABLE_MT_ENTITY( __entity )																					\
		namespace nvl {																											\
      template<> \
			boost::thread_specific_ptr< CPtr< CPoolableMTEntity< __entity >::CStack > > CPoolableMTEntity< __entity >::m_Pool;	\
		}

} // namespace nvl

#endif // __POOLABLE_ENTITY_H_INCLUDED__402809__
