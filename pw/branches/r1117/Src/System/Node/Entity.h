#ifndef __ENTITY_H_INCLUDED__543222__
#define __ENTITY_H_INCLUDED__543222__

#include "System/Node/Config.h"
#include "atomic.h"

#include <assert.h>
#include <list>
#include <typeinfo>

namespace nvl {

  struct IEntity: non_copyable_t {

		virtual void AddReference() = 0;
		virtual void ReleaseReference() = 0;
		virtual size_t GetReferencesCount() const = 0;
		virtual bool IsMTEntity() const = 0;
		virtual cstr_t GetClassIdentifier() const = 0;

		virtual cstr_t GetIdentifier() const
		{ return NULL; }

	};

	template < typename T > class CEntity:
		public T
	{
	public:

		CEntity(): m_nRFCount( 0 ) {}

		template< typename T1 > CEntity( T1 &V1 ):
			T( V1 ), m_nRFCount( 0 ) {}

		template< typename T1 > CEntity( T1 const &V1 ):
			T( V1 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2 > CEntity( T1 &V1, T2 &V2 ):
			T( V1, V2 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2 > CEntity( T1 const &V1, T2 const &V2 ):
			T( V1, V2 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3 >
			CEntity( T1 &V1, T2 &V2, T3 &V3 ):
			T( V1, V2, V3 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3 >
			CEntity( T1 const &V1, T2 const &V2, T3 const &V3 ):
			T( V1, V2, V3 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4 >
			CEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4 ):
			T( V1, V2, V3, V4 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4 >
			CEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4 ):
			T( V1, V2, V3, V4 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5 >
			CEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5 ):
			T( V1, V2, V3, V4, V5 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5 >
			CEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5 ):
			T( V1, V2, V3, V4, V5 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
			CEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6 ):
			T( V1, V2, V3, V4, V5, V6 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
			CEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6 ):
			T( V1, V2, V3, V4, V5, V6 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
			CEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7 ):
			T( V1, V2, V3, V4, V5, V6, V7 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
			CEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7 ):
			T( V1, V2, V3, V4, V5, V6, V7 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
			CEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
			CEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
			CEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
			CEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
			CEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9, T10 &V10 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ), m_nRFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
			CEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9, T10 const &V10 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ), m_nRFCount( 0 ) {}

		~CEntity()
		{ assert( 0 == GetReferencesCount() ); }

		void AddReference()
		{ ++m_nRFCount; }

		void ReleaseReference()
		{
			if ( 0 == --m_nRFCount )
				delete this;
		}

		size_t GetReferencesCount() const
		{ return m_nRFCount; }

		bool IsMTEntity() const
		{ return false; }

		cstr_t GetClassIdentifier() const
		{
#if defined( NV_WIN_PLATFORM )
			return typeid( *this ).raw_name();	// call UnDecorateSymbolName to undecorate
#elif defined( NV_LINUX_PLATFORM )
			return typeid( *this ).name();		// To undecorate use #include <cxxabi.h> or c++filt utility
#endif
		}

	protected:

		size_t m_nRFCount;

	};

	template < typename T > class CMTEntity:
		public T
	{
	public:

		CMTEntity(): m_RFCount( 0 ) {}

		template< typename T1 > CMTEntity( T1 &V1 ):
			T( V1 ), m_RFCount( 0 ) {}

		template< typename T1 > CMTEntity( T1 const &V1 ):
			T( V1 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2 > CMTEntity( T1 &V1, T2 &V2 ):
			T( V1, V2 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2 > CMTEntity( T1 const &V1, T2 const &V2 ):
			T( V1, V2 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3 >
			CMTEntity( T1 &V1, T2 &V2, T3 &V3 ):
			T( V1, V2, V3 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3 >
			CMTEntity( T1 const &V1, T2 const &V2, T3 const &V3 ):
			T( V1, V2, V3 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4 >
			CMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4 ):
			T( V1, V2, V3, V4 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4 >
			CMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4 ):
			T( V1, V2, V3, V4 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5 >
			CMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5 ):
			T( V1, V2, V3, V4, V5 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5 >
			CMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5 ):
			T( V1, V2, V3, V4, V5 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
			CMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6 ):
			T( V1, V2, V3, V4, V5, V6 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
			CMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6 ):
			T( V1, V2, V3, V4, V5, V6 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
			CMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7 ):
			T( V1, V2, V3, V4, V5, V6, V7 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
			CMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7 ):
			T( V1, V2, V3, V4, V5, V6, V7 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
			CMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
			CMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
			CMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
			CMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
			CMTEntity( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9, T10 &V10 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ), m_RFCount( 0 ) {}

		template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
			CMTEntity( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9, T10 const &V10 ):
			T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ), m_RFCount( 0 ) {}

		~CMTEntity()
		{ assert( 0 == GetReferencesCount() ); }

		void AddReference()
		{ ++m_RFCount; }

		void ReleaseReference()
		{
			if ( 0 == --m_RFCount )
				delete this;
		}

		size_t GetReferencesCount() const
		{ return static_cast< size_t >( m_RFCount.load() ); }

		bool IsMTEntity() const
		{ return true; }

		cstr_t GetClassIdentifier() const
		{
#if defined( NV_WIN_PLATFORM )
			return typeid( *this ).raw_name();
#elif defined( NV_LINUX_PLATFORM )
			return typeid( *this ).name();
#endif
		}

	protected:

		nstd::atomic< size_t > m_RFCount;

	};

	typedef bool attach_t;
	const bool attach = true;

	template < typename T > class CPtr
	{
	public:

		CPtr(): m_Ptr( NULL )
		{}

		CPtr( CPtr const &p )
		{
			m_Ptr = p.Get();
			if ( m_Ptr )
				m_Ptr->AddReference();
		}

		CPtr( T * const p )
		{
			m_Ptr = p;
			if ( m_Ptr )
				m_Ptr->AddReference();
		}

		CPtr( T * const p, attach_t const ): m_Ptr( p )
		{}

		~CPtr()
		{
			if ( m_Ptr ) {

				m_Ptr->ReleaseReference();
				m_Ptr = NULL;

			}
		}

		operator T * () const
		{ return m_Ptr; }

		T & operator * () const
		{
			assert( NULL != m_Ptr );
			return * m_Ptr;
		}

		T * operator -> () const
		{
			assert( NULL != m_Ptr );
			return m_Ptr;
		}

		bool operator ! () const
		{ return !m_Ptr; }

		bool operator < ( T * const p ) const
		{ return m_Ptr < p; }

		bool operator == ( T * const p ) const
		{ return m_Ptr == p; }

		T * operator = ( CPtr const &p )
		{ return Assign( p.Get() ); }

		T * operator = ( T * const p )
		{ return Assign( p ); }

		T * Get() const
		{ return m_Ptr; }

		T ** GetRef()
		{ return &m_Ptr; }

		void Release()
		{
			T *p = m_Ptr;
			if ( p ) {
				m_Ptr = NULL;
				p->ReleaseReference();
			}
		}

		T * Attach( T * const p )
		{
			if ( m_Ptr )
				m_Ptr->ReleaseReference();

			return m_Ptr = p;
		}

		T * Detach()
		{
			T *p = m_Ptr;
			m_Ptr = NULL;

			return p;
		}

		template< typename T2 > result_t Detach( CPtr< T2 > &p )
		{
			p.Attach( Detach() );
			return result_ok;
		}

		template< typename T2 > result_t Detach( T2 ** const pPtr )
		{
			if ( pPtr ) {

				*pPtr = m_Ptr;
				if ( m_Ptr )
					m_Ptr = NULL;

				return result_ok;

			}

			return result_inv_args;
		}

		template< typename T2 > result_t Copy( CPtr< T2 > &Ptr ) const
		{
			Ptr = m_Ptr;
			return result_ok;
		}

		template< typename T2 > result_t Copy( T2 ** const pPtr ) const
		{
			if ( pPtr ) {

				*pPtr = m_Ptr;
				if ( m_Ptr )
					m_Ptr->AddReference();

				return result_ok;

			}

			return result_inv_args;
		}

		size_t GetReferencesCount() const
		{
			if ( m_Ptr )
				return m_Ptr->GetReferencesCount();

			return 0;
		}

	protected:

		T * Assign( T * const p )
		{
			if ( m_Ptr != p ) {

				if ( p )
					p->AddReference();

				if ( m_Ptr )
					m_Ptr->ReleaseReference();

				return m_Ptr = p;
			}

			return m_Ptr;
		}

	private:

		T * m_Ptr;

	};

	typedef CPtr< IEntity > CEntityPtr;

} // namespace nvl

#endif // __ENTITY_H_INCLUDED__543222__
