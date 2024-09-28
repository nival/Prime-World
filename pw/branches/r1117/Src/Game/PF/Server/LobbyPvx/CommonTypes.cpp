#include "stdafx.h"

#include "CommonTypes.h"

namespace lobby
{

SERIALIZE_FACTORY( SUserInfo );
SERIALIZE_FACTORY( GameGuildData );
SERIALIZE_FACTORY( SGameParameters );
SERIALIZE_FACTORY( SPlayerGameContext );
SERIALIZE_FACTORY( SGameMember );
SERIALIZE_FACTORY( SDevGameInfo );


NI_ENUM_BEGIN_STD( EOperationResult );
  NI_ENUM_ITEM( Ok );
  NI_ENUM_ITEM( InProgress );
  NI_ENUM_ITEM( InternalError );
  NI_ENUM_ITEM( NoFreeSlot );
  NI_ENUM_ITEM( GameNotFound );
  NI_ENUM_ITEM( GameStarted );
  NI_ENUM_ITEM( AlreadyInGame );
  NI_ENUM_ITEM( RevisionDiffers );
  NI_ENUM_ITEM( RestrictedAccess );
NI_ENUM_END_STD;


NI_ENUM_BEGIN_STD( ETeam );
  NI_ENUM_ITEM( None );
  NI_ENUM_ITEM( Team1 );
  NI_ENUM_ITEM( Team2 );
NI_ENUM_END_STD;


NI_ENUM_BEGIN_STD( ESex );
  NI_ENUM_ITEM( Undefined );
  NI_ENUM_ITEM( Male );
  NI_ENUM_ITEM( Female );
NI_ENUM_END_STD;


NI_ENUM_BEGIN_STD( EPlayerType );
  NI_ENUM_ITEM( Invalid );
  NI_ENUM_ITEM( Human );
  NI_ENUM_ITEM( Computer );
NI_ENUM_END_STD;


NI_ENUM_BEGIN_STD( EGameType );
  NI_ENUM_ITEM( None );
  NI_ENUM_ITEM( Custom );
  NI_ENUM_ITEM( SocialMMaking );
NI_ENUM_END_STD;


NI_ENUM_BEGIN_STD( EGameResult );
  NI_ENUM_ITEM( SyncResults );
  NI_ENUM_ITEM( NoResults );
  NI_ENUM_ITEM( NobodyCame );
  NI_ENUM_ITEM( AsyncResults );
  NI_ENUM_ITEM( Async );
  NI_ENUM_ITEM( Unknown );
NI_ENUM_END_STD;


const char * FmtGameId( TGameId _id )
{
  return NI_STRFMT( "%016llx", _id );
}

}
