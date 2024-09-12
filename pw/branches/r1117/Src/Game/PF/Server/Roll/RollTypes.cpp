#include "stdafx.h"
#include "RollTypes.h"

namespace roll
{

SERIALIZE_FACTORY( SPreGamePerUserData );
SERIALIZE_FACTORY( SPreGameData );
SERIALIZE_FACTORY( SPostGamePerUserData );
SERIALIZE_FACTORY( SPostGameData );
SERIALIZE_FACTORY( SForgeRollData );
SERIALIZE_FACTORY( SAwardInfo );
SERIALIZE_FACTORY( SUserAward );
SERIALIZE_FACTORY( SGuildAward );


NI_ENUM_BEGIN_STD( EMode );
  NI_ENUM_ITEM( None );
  NI_ENUM_ITEM( PvP );
  NI_ENUM_ITEM( LobbyPvp );
  NI_ENUM_ITEM( Train );
  NI_ENUM_ITEM( Tutorial );
  NI_ENUM_ITEM( CustomGame );
  NI_ENUM_ITEM( Singleplayer );
  NI_ENUM_ITEM( Coop );
NI_ENUM_END_STD;



NI_ENUM_BEGIN_STD( EAwardType );
  NI_ENUM_ITEM( None );
  NI_ENUM_ITEM( Talent );
  NI_ENUM_ITEM( Silver );
  NI_ENUM_ITEM( Hero );
  NI_ENUM_ITEM( HeroRating );
  NI_ENUM_ITEM( Reliability );
  NI_ENUM_ITEM( Experience );
  NI_ENUM_ITEM( Resource1 );
  NI_ENUM_ITEM( Resource2 );
  NI_ENUM_ITEM( HeroEnergy );
  NI_ENUM_ITEM( Fame );
  NI_ENUM_ITEM( Resource3 );
  NI_ENUM_ITEM( Pearl );
  NI_ENUM_ITEM( NewSeed );
  NI_ENUM_ITEM( PlayerRating );
  NI_ENUM_ITEM( DodgePoints );
  NI_ENUM_ITEM( GuardRating );
  NI_ENUM_ITEM( GuildWarEventPoints );
  NI_ENUM_ITEM( GuildResource );
  NI_ENUM_ITEM( MarketingEvent );
  NI_ENUM_ITEM( ClanWarsPlayerRating );
  NI_ENUM_ITEM( ClanWarsClanRating );
  NI_ENUM_ITEM( RedPearl );
  NI_ENUM_ITEM( Shard );
  NI_ENUM_ITEM( CustomCurrency );
NI_ENUM_END_STD;



string DbgDumpAwards( const vector<SAwardInfo> & awards )
{
  string s;
  s.reserve( 512 );
  for ( int i = 0; i < awards.size(); ++i )
  {
    if ( i > 0 )
      s += ", ";

    const SAwardInfo & a = awards[i];

    if ( a.count != 1 )
      s += NI_STRFMT( "%gx", a.count );

    s += EAwardType::ToString( a.type );

    //if ( ( a.type == EAwardType::Talent ) || ( a.type == EAwardType::Hero ) )
    if ( a.id )
      s += NI_STRFMT( ":%d", a.id );
  }

  return s;
}


} //roll
