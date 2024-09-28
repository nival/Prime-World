#include "stdafx.h"
#include "HeroesTable.h"

namespace mmaking
{

struct HeroesTable::HeroInfo : public BaseObjectMT, public SHeroDescription
{
  NI_DECLARE_REFCOUNT_CLASS_1( HeroInfo, BaseObjectMT );

  HeroInfo( const SHeroDescription & hdescr ) :
  SHeroDescription( hdescr ) {}
};




THeroShortId HeroesTable::Add( const SHeroDescription & descr )
{
  StrongMT<HeroInfo> hero = new HeroInfo( descr );
  hero->shortId = _array.size() + 1;

  pair<TById::iterator, bool> insertResult = _byId.insert( TById::value_type( descr.id, hero ) );
  NI_VERIFY( insertResult.second, NI_STRFMT( "Duplicate hero id '%s'", descr.id ), return 0 );

  _array.push_back( hero );

  return hero->shortId;
}



const SHeroDescription * HeroesTable::FindDescr( const string & id ) const
{
  TById::iterator it = _byId.find( id );
  NI_VERIFY( it != _byId.end(), NI_STRFMT( "Hero id '%s' not found", id ), return 0 );
  return it->second;
}


SHeroDescription * HeroesTable::FindDescr( const string & id )
{
  TById::iterator it = _byId.find( id );
  NI_VERIFY( it != _byId.end(), NI_STRFMT( "Hero id '%s' not found", id ), return 0 );
  return it->second;
}


const SHeroDescription * HeroesTable::FindDescr( THeroShortId id ) const
{
  NI_VERIFY( id >= 1 && id <= _array.size(), NI_STRFMT( "Hero id '%d' not found", id ), return 0 );
  return _array[id - 1];
}

} //namespace mmaking

NI_DEFINE_REFCOUNT( mmaking::HeroesTable::HeroInfo );
