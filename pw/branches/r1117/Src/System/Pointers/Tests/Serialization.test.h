//!Component("System/Pointers/Pointers")
//!Component("System/Savers")


#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include <string>

#include "System/Pointers/BaseObjectST.h"
#include "System/Pointers/BaseInterface.h"
#include "System/Pointers/Strong.h"
#include "System/Pointers/Weak.h"

#include "System/Progress.h"
#include "System/BinChunkSerializer.h"
#include "System/MemoryStream.h"



class Foo : public BaseObjectST
{
  NI_DECLARE_SERIALIZABLE_CLASS_1( 0xC57BBCC1, Foo, BaseObjectST );

public:
  Foo() : fooIndex( 0 ) {}
  Foo( int _index, const char * _name ) : name( _name ), fooIndex( _index ) {}

  const string & Name() const { return name; }
  int FooIndex() const { return fooIndex; }

private:
  ZDATA
  ZNOPARENT( BaseObjectST )
  string      name;
  int         fooIndex;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&name); f.Add(3,&fooIndex); return 0; }
};

NI_DEFINE_SERIALIZABLE( Foo );


class Koon : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( Koon, IBaseInterfaceST )

public:
  Koon( int _index ) : koonIndex( _index ) {}

  int KoonIndex() const { return koonIndex; }

private:
  ZDATA
  ZNOPARENT( IBaseInterfaceST )
  int koonIndex;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&koonIndex); return 0; }
};

NI_DEFINE_REFCOUNT( Koon );



namespace KoonFooNamespace {

class KoonFoo : public Koon, public Foo
{
  NI_DECLARE_SERIALIZABLE_CLASS_2( 0xC57BBCC2, KoonFoo, Koon, Foo );

public:
  KoonFoo( int _fooIndex, const char * _name, int _koonIndex ) : Koon( _koonIndex ), Foo( _fooIndex, _name ) {}
  KoonFoo() : Koon( 0 ), Foo( 0, "" ) {}

private:
  ZDATA_( Koon )
  ZPARENT( Foo )
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,( Koon *)this); f.Add(2,( Foo *)this); return 0; }
};

} //namespace KoonFooNamespace

NI_DEFINE_SERIALIZABLE_NM( KoonFooNamespace, KoonFoo );



class KoonFooCollection : public BaseObjectST
{
  NI_DECLARE_SERIALIZABLE_CLASS_1( 0xC57BBBC2, KoonFooCollection, BaseObjectST );

public:
  KoonFooCollection() {}

  void Add( KoonFooNamespace::KoonFoo * kf )
  {
    foos.push_back( kf );
  }

  int Count() const { return foos.size(); }

  KoonFooNamespace::KoonFoo * Get( int index ) const
  {
    if ( index >= 0 && index < foos.size() )
      return foos[index];
    return 0;
  }

  Foo * CustomFoo() const { return customFoo; }
  void SetCustomFoo( Foo * f ) { customFoo = f; }

  Foo * WeakFoo() const { return weakFoo; }
  void SetWeakFoo( Foo * f ) { weakFoo = f; }

private:
  ZDATA
  ZNOPARENT( BaseObjectST )
  vector< Strong<KoonFooNamespace::KoonFoo> > foos;
  Strong<Foo> customFoo;
  Weak<Foo> weakFoo;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&foos); f.Add(3,&customFoo); f.Add(4,&weakFoo); return 0; }
};

NI_DEFINE_SERIALIZABLE( KoonFooCollection );






////////
class CObjectTestA : public CObjectBase
{
  OBJECT_METHODS( 0xC57BCC80, CObjectTestA );
public:
  CObjectTestA( int i = 0 ) : m_i( i ) {}
  ZDATA
  int m_i;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&m_i); return 0; }
};
REGISTER_SAVELOAD_CLASS( CObjectTestA )

class CObjectTestB : public CObjectBase
{
  OBJECT_METHODS( 0xC57BCCC0, CObjectTestB );
public:
  CObjectTestB( int j = 0, CObjectTestA * a = 0, CObjectTestA * aa = 0 ) : m_j( j ), m_a( a ), m_aa( aa ) {}
  ZDATA
  int m_j;
  CObj<CObjectTestA> m_a, m_aa;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&m_j); f.Add(3,&m_a); f.Add(4,&m_aa); return 0; }
};
REGISTER_SAVELOAD_CLASS( CObjectTestB )



class Test_PointerasSerialization : public CxxTest::TestSuite
{
public:
  virtual void setUp()
  {
  }


  virtual void tearDown()
  {
  }


  void test_linear()
  {
    CObj<MemoryStream> buffer = new MemoryStream;

    {
      Strong<KoonFooNamespace::KoonFoo> koonfoo = new KoonFooNamespace::KoonFoo( 5, "My Koonfoo", 8 );
      {
        CObj<IBinSaver> saver = CreateWriteBinSaver( buffer, 0, false );
        (*koonfoo) & (*saver);
      }
    }

    TS_ASSERT( buffer->GetSize() > 0 );
    buffer->Seek( 0, SEEKORIGIN_BEGIN );

    Strong<KoonFooNamespace::KoonFoo> newKoonfoo = new KoonFooNamespace::KoonFoo;

    TS_ASSERT( IsValid( newKoonfoo ) );

    {
      CObj<IBinSaver> saver = CreateReadBinSaver( buffer, 0 );
      (*newKoonfoo) & (*saver);
    }

    TS_ASSERT_EQUALS( newKoonfoo->FooIndex(), 5 );
    TS_ASSERT_EQUALS( newKoonfoo->Name(), "My Koonfoo" );
    TS_ASSERT_EQUALS( newKoonfoo->KoonIndex(), 8 );
  }



  void test_pointers()
  {
    Strong<KoonFooCollection> collection = new KoonFooCollection;
    collection->Add( new KoonFooNamespace::KoonFoo( 1, "My Koonfoo", 1 ) );
    collection->Add( new KoonFooNamespace::KoonFoo( 2, "My Koonfoo", 2 ) );
    collection->Add( new KoonFooNamespace::KoonFoo( 3, "Your Koonfoo", 4 ) );
    collection->Add( new KoonFooNamespace::KoonFoo( 5, "Your Koonfoo", 8 ) );

    collection->SetCustomFoo( 0 );
    collection->SetWeakFoo( collection->Get( 2 ) );

    CObj<MemoryStream> buffer = new MemoryStream;
    {
      CObj<IBinSaver> saver = CreateWriteBinSaver( buffer, 0, false );
      (*collection) & (*saver);
    }

    TS_ASSERT( buffer->GetSize() > 0 );
    buffer->Seek( 0, SEEKORIGIN_BEGIN );

    ///////
    Strong<KoonFooCollection> newCollection = ni_detail::ProduceObject<KoonFooCollection>();
    TS_ASSERT( newCollection );

    {
      CObj<IBinSaver> saver = CreateReadBinSaver( buffer, 0 );
      (*newCollection) & (*saver);
    }

    TS_ASSERT_EQUALS( newCollection->Count(), 4 );
    for ( int i = 0; i < 4; ++i )
      TS_ASSERT( newCollection->Get( i ) );

    TS_ASSERT( !newCollection->CustomFoo() );
    TS_ASSERT( newCollection->WeakFoo() );
    TS_ASSERT_EQUALS( newCollection->WeakFoo(), newCollection->Get( 2 ) );

    TS_ASSERT_EQUALS( newCollection->Get( 0 )->FooIndex(), 1 );
    TS_ASSERT_EQUALS( newCollection->Get( 1 )->FooIndex(), 2 );
    TS_ASSERT_EQUALS( newCollection->Get( 2 )->FooIndex(), 3 );
    TS_ASSERT_EQUALS( newCollection->Get( 3 )->FooIndex(), 5 );
    TS_ASSERT_EQUALS( newCollection->Get( 0 )->KoonIndex(), 1 );
    TS_ASSERT_EQUALS( newCollection->Get( 1 )->KoonIndex(), 2 );
    TS_ASSERT_EQUALS( newCollection->Get( 2 )->KoonIndex(), 4 );
    TS_ASSERT_EQUALS( newCollection->Get( 3 )->KoonIndex(), 8 );
  }



  void test_CObj()
  {
    CObj<MemoryStream> buffer = new MemoryStream;

    {
      CObj<CObjectTestB> b = new CObjectTestB( 5, new CObjectTestA( 10 ), 0 );
      {
        CObj<IBinSaver> saver = CreateWriteBinSaver( buffer, 0, false );
        (*b) & (*saver);
      }
    }

    TS_ASSERT( buffer->GetSize() > 0 );
    buffer->Seek( 0, SEEKORIGIN_BEGIN );

    CObj<CObjectTestB> newB = new CObjectTestB;

    {
      CObj<IBinSaver> saver = CreateReadBinSaver( buffer, 0 );
      (*newB) & (*saver);
    }

    TS_ASSERT_EQUALS( newB->m_j, 5 );

    TS_ASSERT( newB->m_a );
    TS_ASSERT_EQUALS( newB->m_a->m_i, 10 );

    TS_ASSERT( !newB->m_aa );
  }
};
