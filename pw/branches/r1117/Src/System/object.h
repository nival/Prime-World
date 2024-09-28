#ifndef __OBJECT_H_INCLUDED__543222__
#define __OBJECT_H_INCLUDED__543222__

#include "interlocked.h"

#include <assert.h>
#include <list>

namespace nival {

struct object_interface_t {

	virtual void add_reference() const = 0;
	virtual void release_reference() const = 0;
	virtual size_t get_references_count() const = 0;
	virtual bool is_ts_object() const = 0;

	virtual cstr_t get_object_identifier() const
	{ return NULL; }

};

template < typename T > class object_t:
	public T
{
private:

	object_t( object_t const & );
	void operator = ( object_t const & );

public:

	object_t(): m_rfcount( 0 ) {}

	template< typename T1 > object_t( T1 &V1 ):
		T( V1 ), m_rfcount( 0 ) {}

	template< typename T1 > object_t( T1 const &V1 ):
		T( V1 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2 > object_t( T1 &V1, T2 &V2 ):
		T( V1, V2 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2 > object_t( T1 const &V1, T2 const &V2 ):
		T( V1, V2 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3 >
		object_t( T1 &V1, T2 &V2, T3 &V3 ):
		T( V1, V2, V3 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3 >
		object_t( T1 const &V1, T2 const &V2, T3 const &V3 ):
		T( V1, V2, V3 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4 >
		object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4 ):
		T( V1, V2, V3, V4 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4 >
		object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4 ):
		T( V1, V2, V3, V4 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
		object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5 ):
		T( V1, V2, V3, V4, V5 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
		object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5 ):
		T( V1, V2, V3, V4, V5 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
		object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6 ):
		T( V1, V2, V3, V4, V5, V6 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
		object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6 ):
		T( V1, V2, V3, V4, V5, V6 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
		object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7 ):
		T( V1, V2, V3, V4, V5, V6, V7 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
		object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7 ):
		T( V1, V2, V3, V4, V5, V6, V7 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
		object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
		object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
		object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
		object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
		object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9, T10 &V10 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
		object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9, T10 const &V10 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ), m_rfcount( 0 ) {}

	~object_t()
	{ assert( 0 == get_references_count() ); }

	void add_reference() const
	{ ++m_rfcount; }

	void release_reference() const
	{
		if ( 0 == --m_rfcount )
			delete this;
	}

	size_t get_references_count() const
	{ return m_rfcount; }

	bool is_ts_object() const
	{ return false; }

protected:

	mutable size_t m_rfcount;

};

template < typename T > class ts_object_t:
	public T
{
private:

	ts_object_t(ts_object_t const &);
	void operator = (ts_object_t const &);

public:

	ts_object_t(): m_rfcount( 0 ) {}

	template< typename T1 > ts_object_t( T1 &V1 ):
		T( V1 ), m_rfcount( 0 ) {}

	template< typename T1 > ts_object_t( T1 const &V1 ):
		T( V1 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2 > ts_object_t( T1 &V1, T2 &V2 ):
		T( V1, V2 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2 > ts_object_t( T1 const &V1, T2 const &V2 ):
		T( V1, V2 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3 >
		ts_object_t( T1 &V1, T2 &V2, T3 &V3 ):
		T( V1, V2, V3 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3 >
		ts_object_t( T1 const &V1, T2 const &V2, T3 const &V3 ):
		T( V1, V2, V3 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4 >
		ts_object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4 ):
		T( V1, V2, V3, V4 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4 >
		ts_object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4 ):
		T( V1, V2, V3, V4 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
		ts_object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5 ):
		T( V1, V2, V3, V4, V5 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5 >
		ts_object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5 ):
		T( V1, V2, V3, V4, V5 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
		ts_object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6 ):
		T( V1, V2, V3, V4, V5, V6 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
		ts_object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6 ):
		T( V1, V2, V3, V4, V5, V6 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
		ts_object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7 ):
		T( V1, V2, V3, V4, V5, V6, V7 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
		ts_object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7 ):
		T( V1, V2, V3, V4, V5, V6, V7 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
		ts_object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
		ts_object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
		ts_object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
		ts_object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8, V9 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
		ts_object_t( T1 &V1, T2 &V2, T3 &V3, T4 &V4, T5 &V5, T6 &V6, T7 &V7, T8 &V8, T9 &V9, T10 &V10 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ), m_rfcount( 0 ) {}

	template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10 >
		ts_object_t( T1 const &V1, T2 const &V2, T3 const &V3, T4 const &V4, T5 const &V5, T6 const &V6, T7 const &V7, T8 const &V8, T9 const &V9, T10 const &V10 ):
		T( V1, V2, V3, V4, V5, V6, V7, V8, V9, V10 ), m_rfcount( 0 ) {}

	~ts_object_t()
	{ assert( 0 == get_references_count() ); }

	void add_reference() const
	{ interlocked_increment( m_rfcount ); }

	void release_reference() const
	{
		if ( 0 == interlocked_decrement( m_rfcount ) )
			delete this;
	}

	size_t get_references_count() const
	{ return m_rfcount; }

	bool is_ts_object() const
	{ return true; }

protected:

	mutable volatile size_t m_rfcount;

};

template < typename T > class ptr_t
{
public:

	ptr_t(): m_ptr(NULL)
	{}

	ptr_t( T *ptr )
	{
		if ( ( m_ptr = ptr ) )
			m_ptr->add_reference();
	}

	ptr_t( ptr_t const &ptr )
	{
		if ( ( m_ptr = ptr.get() ) )
			m_ptr->add_reference();
	}

	~ptr_t()
	{
		if ( m_ptr )
			m_ptr->release_reference();
	}

	operator T * () const
	{ return m_ptr; }

	T & operator * () const
	{
		assert( NULL != m_ptr );
		return * m_ptr;
	}

	T * operator -> () const
	{
		assert( NULL != m_ptr );
		return m_ptr;
	}

	bool operator ! () const
	{ return !m_ptr; }

	bool operator < ( T *ptr ) const
	{ return m_ptr < ptr; }

	bool operator == ( T *ptr ) const
	{ return m_ptr == ptr; }

	T * operator = ( T *ptr )
	{ return assign( ptr ); }

	T * get() const
	{ return m_ptr; }

	T ** get_ref()
	{ return &m_ptr; }

	void release()
	{
		T *p = m_ptr;
		if ( p ) {
			m_ptr = NULL;
			p->release_reference();
		}
	}

	T * attach( T *ptr )
	{
		if ( m_ptr )
			m_ptr->release_reference();

		return m_ptr = ptr;
	}

	T * detach()
	{
		T *p = m_ptr;
		m_ptr = NULL;

		return p;
	}

	template< typename T2 > result_t detach( T2 **pptr )
	{
		if ( pptr ) {

			if ( ( *pptr = m_ptr ) )
				m_ptr = NULL;

			return result_ok;

		}

		return result_inv_args;
	}

	template< typename T2 > result_t copy( T2 **pptr ) const
	{
		if ( pptr ) {

			if ( ( *pptr = m_ptr ) )
				m_ptr->add_reference();

			return result_ok;

		}

		return result_inv_args;
	}

	size_t get_references_count() const
	{
		if ( m_ptr )
			return m_ptr->get_references_count();

		return 0;
	}

protected:

	T * assign( T *ptr )
	{
		if ( ptr )
			ptr->add_reference();

		if ( m_ptr )
			m_ptr->release_reference();

		return m_ptr = ptr;
	}

private:

	T * m_ptr;

};

typedef ptr_t< object_interface_t > object_ptr_t;

template < typename T > class guard_t
{
private:

	guard_t(guard_t const &);
	void operator = (guard_t const &);

public:

	guard_t(): m_ptr(NULL)
	{}

	guard_t( T *ptr ): m_ptr(ptr)
	{}

	~guard_t()
	{
		if (m_ptr)
			delete m_ptr;
	}

	void reset( T *ptr )
	{
		if ( m_ptr && m_ptr != ptr )
			delete m_ptr;

		m_ptr = ptr;
	}

	T * get() const
	{ return m_ptr; }

	T * detach()
	{
		T *ptr = m_ptr;
		m_ptr = NULL;

		return ptr;
	}

	void release()
	{ m_ptr = NULL; }

	T * operator -> ()
	{
		assert( NULL != m_ptr );
		return m_ptr;
	}

	T const * operator -> () const
	{
		assert( NULL != m_ptr );
		return m_ptr;
	}

private:

	T * m_ptr;

};

} // namespace nival

#endif // __OBJECT_H_INCLUDED__543222__

