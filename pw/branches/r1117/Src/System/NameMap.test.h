//!Component('Vendor/Libc')
//!Component('System/Ptr')
//!Component('System/NameMap')
//!Component('System/DebugVar')
//!Component('System/Commands')

#pragma warning(disable: 4121)

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "NameMap.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NMTestSuper : public NNameMap::Map
{
  NAMEMAP_DECLARE;

protected:
  float superValue;
  NNameMap::WStringListT friends;

public:
  NMTestSuper() : superValue(-5.0f)
  {
    friends.push_back( L"Barak" );
    friends.push_back( L"Obama" );
    friends.push_back( L"ShootinPutin" );
  }

  const float& GetSuper() const { return superValue; }
  void SetSuper(const float & x) { superValue = x; }

  const float & GetG() const { const static float p = 9.81f; return p; }

  const NNameMap::WStringListT & GetFriends() const { return friends; }
};

NAMEMAP_BEGIN( NMTestSuper )
  NAMEMAP_FUNC( super, &NMTestSuper::GetSuper , &NMTestSuper::SetSuper )
  NAMEMAP_FUNC_RO( g, &NMTestSuper::GetG )
  NAMEMAP_STRING_LIST( friends, &NMTestSuper::GetFriends )
NAMEMAP_END


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NMTestSub : public CObjectBase, public NMTestSuper
{
  NAMEMAP_DECLARE;
  OBJECT_BASIC_METHODS(NMTestSub);

public:
  string ku;
  bool bull;

  NMTestSub() : ku("Kukuku"), bull(true)
  {
  }
};

NAMEMAP_BEGIN( NMTestSub )
  NAMEMAP_PARENT( NMTestSuper )
  NAMEMAP_VAR( ku )
  NAMEMAP_VAR( bull )
NAMEMAP_END


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NMTest : public NNameMap::Map, public CObjectBase
{
  NAMEMAP_DECLARE;
  OBJECT_BASIC_METHODS(NMTest);

public:
  float x;
  int index;
  wstring name;
  CPtr<NMTestSub> submap;

  NMTest() : x(3.14f), index(1024), name(L"Namemap test class"), submap( new NMTestSub() )
  {
  }
};

NAMEMAP_BEGIN( NMTest )
  NAMEMAP_VAR( x )
  NAMEMAP_VAR_RO( index )
  NAMEMAP_VAR( name )
  NAMEMAP_SUBMAP( submap )
NAMEMAP_END


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NameMapTest : public CxxTest::TestSuite
{
  CObj<NMTest> map;

public:
  virtual void setUp()
  {
    if(!IsValid(map))
      map = new NMTest;
  }

  virtual void tearDown()
  {
  }

  void testVariant()
  {
    TS_ASSERT(IsValid(map));

    const NMTest * constMap = map;

    CObj<NNameMap::Variant> variantX = map->GetVariant("x");
    TS_ASSERT( variantX );
    TS_ASSERT( variantX->GetType() == NNameMap::VariantType::Float );
    TS_ASSERT( variantX->GetFloat() == map->x );

    CObj<NNameMap::ReadonlyVariant> variantIndex = constMap->GetVariant("index");
    TS_ASSERT( variantIndex );
    TS_ASSERT( variantIndex->GetType() == NNameMap::VariantType::Int );
    TS_ASSERT( variantIndex->GetInt() == map->index );

    CObj<NNameMap::Variant> variantName = map->GetVariant("name");
    TS_ASSERT( variantName );
    TS_ASSERT( variantName->GetType() == NNameMap::VariantType::WString );
    TS_ASSERT( variantName->GetWString() == map->name );

    CObj<NNameMap::Variant> variantSubmap = map->GetVariant("submap.ku");
    TS_ASSERT( variantSubmap );
    TS_ASSERT( variantSubmap->GetType() == NNameMap::VariantType::String );
    TS_ASSERT( variantSubmap->GetString() == map->submap->ku );

    CObj<NNameMap::Variant> variantSubmapBull = map->GetVariant("submap.bull");
    TS_ASSERT( variantSubmapBull );
    TS_ASSERT( variantSubmapBull->GetType() == NNameMap::VariantType::Bool );
    TS_ASSERT( variantSubmapBull->GetBool() == map->submap->bull );

    CObj<NNameMap::Variant> variantSuper = map->GetVariant("submap.super");
    TS_ASSERT( variantSuper );
    TS_ASSERT( variantSuper->GetType() == NNameMap::VariantType::Float );
    TS_ASSERT( variantSuper->GetFloat() == map->submap->GetSuper() );
    const float E = 2.7183f;
    variantSuper->SetFloat( E );
    TS_ASSERT( variantSuper->GetFloat() == E );

    CObj<NNameMap::ReadonlyVariant> variantG = constMap->GetVariant("submap.g");
    TS_ASSERT( variantG );
    TS_ASSERT( variantG->GetType() == NNameMap::VariantType::Float );
    TS_ASSERT( variantG->GetFloat() == map->submap->GetG() );

    //Test formatting
    wchar_t buffer[256] = L"";
    int chars = 0;

    chars = variantX->Format(buffer, L"05.2");
    TS_ASSERT( chars == 6 );
    TS_ASSERT( wcscmp(buffer, L"003.14") == 0 );

    chars = variantIndex->Format(buffer, L"08");
    TS_ASSERT( chars == 8 );
    TS_ASSERT( wcscmp(buffer, L"00001024") == 0 );

    variantName->SetWString(L"Quick brown fox");

    chars = variantName->Format(buffer, L".5");
    TS_ASSERT( chars == 5 );
    TS_ASSERT( wcscmp(buffer, L"Quick") == 0 );


    ////////
    CObj<NNameMap::ReadonlyVariant> variantList = ( static_cast<const NNameMap::Map *>( map ) )->GetVariant( "submap.friends", 0 );
    size_t listCopied = variantList->Format( buffer, 24, L", " );
    TS_ASSERT( listCopied == 24 );
    TS_ASSERT( wcscmp( buffer, L"Barak, Obama, ShootinPu" ) == 0 );
  }
};
