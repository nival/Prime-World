#ifndef CLONEDPTR_H_98FEF86C_4FF0_446E_B
#define CLONEDPTR_H_98FEF86C_4FF0_446E_B

#include "Db.h"
#include "IDbTypesRegistrator.h"
#include "../System/MetaProg.h"

namespace NDb
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class TDbResource >
class ClonedPtr
{
public:
  //Non-constant references and pointers are _intentional_

  ClonedPtr() :
  clone( 0 ),
  changed( false ),
  pointer( HackyThis(), &ClonedPtr::OnResourceChanged )
  {}

  ClonedPtr( const ClonedPtr< TDbResource > & other ) :
  clone( 0 ),
  changed( false ),
  pointer( HackyThis(), &ClonedPtr::OnResourceChanged )
  {
    Assign( other.GetSourcePtr(), other.GetPtr() );
  }

  template< class TAnotherDbResource >
  ClonedPtr( const ClonedPtr< TAnotherDbResource > & other ) :
  clone( 0 ),
  changed( false ),
  pointer( HackyThis(), &ClonedPtr::OnResourceChanged )
  {
    NI_STATIC_ASSERT( SUPERSUBCLASS( TAnotherDbResource, TDbResource ), Wrong_ClonedPtr_arguments );
    const TDbResource * srcPtr = dynamic_cast < const TDbResource * > ( other.GetSourcePtr() );
    TDbResource * clonePtr = dynamic_cast < TDbResource * > ( other.GetPtr() );
    Assign( srcPtr, clonePtr );
  }

  ~ClonedPtr() { DbResource::ReleaseRef ( clone ); }

private:
  ClonedPtr * HackyThis() { return this; } //To circumvent C4355: 'this' : used in base member initializer list
public:

	const TDbResource * operator -> () const { return GetPtr(); }
  TDbResource * operator -> () { return GetPtr(); }
	operator const TDbResource * () const { return GetPtr(); }
  operator TDbResource * () { return GetPtr(); }

  virtual ClonedPtr& operator = ( const ClonedPtr & other ) {
    Assign( other.GetSourcePtr(), other.GetPtr() );
    return *this;
  }

  bool IsEmpty() const { return clone ? false : true; }

  void Clone( const TDbResource * p )
  {
    pointer = p;
    CloneImpl( p );
  }

  void SetState( const string& stateName )
  {
    pointer.SetState( stateName );
    CloneImpl( pointer );
  }

  TDbResource* GetPtr() const
  {
    return clone;
  }

  TDbResource* GetPtr()
  {
    return clone;
  }

  const TDbResource* GetSourcePtr() const
  {
    return pointer.GetPtr();
  }

  bool IsModified( bool reset = true )
  {
    bool result = changed;
    if( reset )
      changed = false;
    return result;
  }

private:
  ChangeablePtr< TDbResource >  pointer;
  TDbResource *  clone;
  bool changed;

  void Assign( const TDbResource * srcPtr, TDbResource * clonePtr )
  {
    pointer = srcPtr;

    if( clonePtr == clone )
      return;

    TDbResource * pOld = clone;
    clone = clonePtr;
    DbResource::AddRef( clone );
    DbResource::ReleaseRef( pOld );
  }

  void CloneImpl( const TDbResource * p )
  {
    if( p == clone )
      return;

    DbResource::ReleaseRef ( clone );
    clone = 0;

    if( p )
    {
      DbResource * newRes = GetDbTypesRegistrator().Create( DBID(), p->GetObjectTypeName(), true );
      clone = dynamic_cast < TDbResource * > ( newRes );
      DbResource::AddRef ( clone );
      clone->OverridableAssign( p );
    }
  }

  void OnResourceChanged( const NDb::DBID & param )
  {
    if( clone )
    {
      const bool ptrValid = ( pointer.GetPtr() != 0 ); //HACK: GetPtr() is changing 'pointer' !! And clears if pointer is outdated..
      if ( ptrValid )
      {
        clone->OverridableAssign( pointer );
        changed = true;
      }
      else
      {
        DbResource::ReleaseRef( clone );
        clone = 0;
      }
    }
  }
};

} //namespace NDb;

#endif //#define CLONEDPTR_H_98FEF86C_4FF0_446E_B
