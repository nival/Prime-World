#pragma once
#include <ace/Atomic_Op.h>

namespace naio
{
  template < typename T > class Ptr
  {
  public:

    Ptr(): m_Ptr( NULL )
    {}

    Ptr( Ptr const &p )
      :m_Ptr(p.get())
    {
      if ( m_Ptr )
        m_Ptr->addRef();
    }

    template< typename T2 >
    Ptr( Ptr<T2> const &p )
      :m_Ptr(p.get())
    {
      if ( m_Ptr )
        m_Ptr->addRef();
    }

    Ptr( T * const p, bool addref = true )
    {
      m_Ptr = p;
      if ( m_Ptr && addref )
        m_Ptr->addRef();
    }

    ~Ptr()
    {
      if ( m_Ptr )
      {
        m_Ptr->releaseRef();
        m_Ptr = NULL;
      }
    }

    operator bool() const
    { return m_Ptr != NULL; }

    //operator T * () const
    //{ return m_Ptr; }

    //T & operator * () const
    //{
    //  assert( NULL != m_Ptr );
    //  return * m_Ptr;
    //}

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

    T * operator = ( Ptr const &p )
    { return assign( p.get() ); }

    T * operator = ( T * const p )
    { return assign( p ); }

    T * get() const
    { return m_Ptr; }

    //T * Attach( T * const p )
    //{
    //  if ( m_Ptr )
    //    m_Ptr->releaseRef();

    //  return m_Ptr = p;
    //}

    //T * Detach()
    //{
    //  T *p = m_Ptr;
    //  m_Ptr = NULL;

    //  return p;
    //}

    long refCount() const
    {
      if ( m_Ptr )
        return m_Ptr->refCount();

      return 0;
    }

  protected:

    T * assign( T * const p )
    {
      if ( m_Ptr != p ) {

        if ( p )
          p->addRef();

        if ( m_Ptr )
          m_Ptr->releaseRef();

        return m_Ptr = p;
      }

      return m_Ptr;
    }

  private:

    T * m_Ptr;

  };
}
