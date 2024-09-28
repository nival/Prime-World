#ifndef SYSTEM_STRONG_H_INCLUDED
#define SYSTEM_STRONG_H_INCLUDED

#include "PointersDetail.h"


namespace ni_detail
{

template <class T, class TBaseObject>
class StrongTemplate
{
  T * ptr;

public:
  enum EDoNotIncrementReferenceFlag { DoNotIncrementReferenceFlag };

  StrongTemplate() : ptr( 0 ) {}

  ~StrongTemplate()
  {
    ImplementationRelease( ptr );
  }

  StrongTemplate( T * p )
  {
    ImplementationAddRef( p );
    ptr = p;
  }

  //Only for weak-pointer locking mechanism
  StrongTemplate( EDoNotIncrementReferenceFlag, T * p )
  {
    ptr = p;
  }

  StrongTemplate( const StrongTemplate & other )
  {
    ImplementationAddRef( other.ptr );
    ptr = other.ptr;
  }

  void Set( T * p )
  {
    ImplementationAddRef( p );
    ImplementationRelease( ptr );
    ptr = p;
  }

  T * Get() { return ptr; }
  T * Get() const { return ptr; }

  T * GetSafe() { NI_ASSERT( ptr, "Null pointer" ); return ptr; }
  T * GetSafe() const { NI_ASSERT( ptr, "Null pointer" ); return ptr; }

  bool Valid() const { return ptr ? true : false; }

  TBaseObject * GetBaseObject() { return ptr ? ni_detail::CastToBaseObject<TBaseObject>( ptr ) : 0; }

private:
  static void ImplementationAddRef( T * p )
  {
    if ( p )
    {
      TBaseObject * base = ni_detail::CastToBaseObject<TBaseObject>( p );
      base->StrongAddRef();
    }
  }

  static void ImplementationRelease( T * p )
  {
    if ( p )
    {
      TBaseObject * base = ni_detail::CastToBaseObject<TBaseObject>( p );
      base->StrongRelease();
    }
  }
};

} //namespace ni_detail





//FIXME: Ugly macroses
#define NII_DECLARE_STRONG_POINTER( className, baseObject ) \
template <class T> \
class className : public ni_detail::StrongTemplate<T, baseObject>  \
{ \
  typedef ni_detail::StrongTemplate< T, baseObject > base_class_t; \
\
public: \
  className() {} \
  className( T * p ) : base_class_t::StrongTemplate( p ) {} \
  className( typename base_class_t::EDoNotIncrementReferenceFlag, T * p ): \
    base_class_t::StrongTemplate( base_class_t::DoNotIncrementReferenceFlag, p ) {} \
  className( const className & other ) : base_class_t::StrongTemplate( other ) {} \
\
  className & operator = ( T * p ) { this->Set( p ); return *this; } \
  className & operator = ( const className & other ) { this->Set( other.Get() ); return *this; } \
\
  T * operator -> () { return this->GetSafe(); } \
  T * operator -> () const { return this->GetSafe(); } \
\
  operator T * () { return this->Get(); } \
  operator T * () const { return this->Get(); } \
\
  int operator & ( IBinSaver & f ); \
}; \


NII_DECLARE_STRONG_POINTER( Strong, BaseObjectST );
NII_DECLARE_STRONG_POINTER( StrongMT, BaseObjectMT );

#endif //SYSTEM_STRONG_H_INCLUDED
