#include "stdafx.h"

#include "MapCollection.h"
#include "DBAdvMap.h"

#include "PFAdvMap.h"

NI_DEFINE_REFCOUNT( NWorld::IMapCollection );


namespace NWorld
{


IMapCollection * CreatePWMapCollection()
{
  return new PWMapCollection;
}


PWMapCollection::PWMapCollection() :
 listCustom(0)
{
}

void PWMapCollection::ScanForMaps()
{
  maps.Scan( "Maps\\", "*.ADMPDSCR.xdb" );
}



int PWMapCollection::MapsListSize() const
{
  return maps.size();
}

const char * PWMapCollection::CustomDescId( int index ) const
{
  NI_VERIFY( IsValid(listCustom) && index >= 0 && index < listCustom->maps.size(), "", return "" );
  return listCustom->maps[index]->GetDBID().GetFileName().c_str();
}

const wchar_t * PWMapCollection::CustomTitle( int index ) const
{
  NI_VERIFY( IsValid(listCustom) && index >= 0 && index < listCustom->maps.size(), "", return L"" );
  return listCustom->maps[index]->title.GetText().c_str();
}

const wchar_t * PWMapCollection::CustomDescription( int index ) const
{
  NI_VERIFY( IsValid(listCustom) && index >= 0 && index < listCustom->maps.size(), "", return L"" );
  return listCustom->maps[index]->description.GetText().c_str();
}

void PWMapCollection::InitCustomList( const NDb::Ptr<NDb::MapList> list )
{
  listCustom = list;
}

const char * PWMapCollection::MapId( int index ) const
{
  //FIXME: We use resource filename as a map's id
  //That's wrong in case someone will inline them
  NI_VERIFY( index >= 0 && index < maps.size(), "", return "" );
  return maps[index]->map->GetDBID().GetFileName().c_str();
}

const char * PWMapCollection::MapDescId( int index ) const
{
  //FIXME: We use resource filename as a map's id
  //That's wrong in case someone will inline them
  NI_VERIFY( index >= 0 && index < maps.size(), "", return "" );
  return maps[index]->GetDBID().GetFileName().c_str();
}


const wchar_t * PWMapCollection::MapTitle( int index ) const
{
  NI_VERIFY( index >= 0 && index < maps.size(), "", return L"" );
  return maps[index]->title.GetText().c_str();
}



const wchar_t * PWMapCollection::MapDescription( int index ) const
{
  NI_VERIFY( index >= 0 && index < maps.size(), "", return L"" );
  return maps[index]->description.GetText().c_str();
}



int PWMapCollection::FindMapById( const char * id ) const
{
  if ( !id ) //Yes, it can be null
    return -1;

  for ( int i = 0; i < maps.size(); ++i )
  {
    //We can select by map title
    if ( !_stricmp( id, NStr::ToMBCS( maps[i]->title.GetText() ).c_str() ) )
      return i;
  }
  for ( int i = 0; i < maps.size(); ++i )
  {
    //We can select by map description
    if ( !_stricmp( id, maps[i]->GetDBID().GetFileName().c_str() ) )
      return i;
  }
  return -1;
}


IMapLoader * PWMapCollection::CreateMapLoader( const char * id )
{
  int index = FindMapById( id );

  if ( index >= 0 && index < maps.size() )
    return NWorld::CreatePWFillMapStartInfo( maps[index] );

  NDb::Ptr<NDb::AdvMap> map = NDb::Get<NDb::AdvMap>( NDb::DBID( id ) );
  if ( IsValid( map ) )
    return NWorld::CreatePWFillMapStartInfo( map );

  NI_ALWAYS_ASSERT( NStr::StrFmt( "\"%s\" is not valid name or DBID of a map", id ) );
  return 0;
}

} //namespace NWorld
