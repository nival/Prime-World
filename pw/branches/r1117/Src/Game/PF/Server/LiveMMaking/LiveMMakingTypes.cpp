#include "stdafx.h"
#include "LiveMMakingTypes.h"

namespace mmaking
{

SERIALIZE_FACTORY( SLocationPing );
SERIALIZE_FACTORY( SGeoInfo );
SERIALIZE_FACTORY( SRequestMember );
SERIALIZE_FACTORY( SRequestCommonData );
SERIALIZE_FACTORY( SGameParty );
SERIALIZE_FACTORY( SBotGameMember );
SERIALIZE_FACTORY( SGame );
SERIALIZE_FACTORY( SReconnectSlot );


NI_ENUM_BEGIN_STD( EBasket );
  NI_ENUM_ITEM( Undefined );
  NI_ENUM_ITEM( Newbie );
  NI_ENUM_ITEM( Normal );
  NI_ENUM_ITEM( Leaver );
NI_ENUM_END_STD;


NI_ENUM_BEGIN_STD( EDebugGameType );
  NI_ENUM_ITEM( Normal );
  NI_ENUM_ITEM( LongWait );
  NI_ENUM_ITEM( FullParty );
NI_ENUM_END_STD;


NI_ENUM_BEGIN_STD( EServiceGameModes );
  NI_ENUM_ITEM( Any );
  NI_ENUM_ITEM( ProductionOnly );
  NI_ENUM_ITEM( DevelopmentOnly );
NI_ENUM_END_STD;


string SGeoInfo::FmtPings() const
{
  string tmp;
  for ( int i = 0; i < pings.size(); ++i ) {
    char buf[64]="";
    NStr::Printf( buf, 63, "%s%s:%d", ( i > 0 ? "/" : "" ), pings[i].clusterId.c_str(), pings[i].ping );
    tmp += buf;
  }
  return tmp;
}


string PrepareGameModeName( const string & mapId )
{
  string key;
  NStr::ToLower( &key, mapId );
  if ( !key.empty() && ( ( key[0] == '/' ) || ( key[0] == '\\' ) ) )
      key.erase( 0, 1 );

  if ( ( key.length() > 4 ) && ( key.substr( key.length() - 4 ) == ".xdb" ) )
    key.erase( key.length() - 4 );

  return key;
}

}
