#include "stdafx.h"
#include "SocialLobbyTypes.h"

namespace socialLobby
{

SERIALIZE_FACTORY( SMatchmakingRequestCore );
SERIALIZE_FACTORY( SMatchmakingRequest );
SERIALIZE_FACTORY( SGameResults );
SERIALIZE_FACTORY( SMatchmakingStatus );
SERIALIZE_FACTORY( SServerStatus );
SERIALIZE_FACTORY( SPlayerData );
SERIALIZE_FACTORY( PlayerDetails );
SERIALIZE_FACTORY( PvxClusterSettings );
SERIALIZE_FACTORY( PvxGameDetails );


NI_ENUM_BEGIN_STD( ERequestStatus );
  NI_ENUM_ITEM( Null );
  NI_ENUM_ITEM( JustAddedToSocialServer );
  NI_ENUM_ITEM( JustAddedToHttpGateway );
  NI_ENUM_ITEM( JustAddedToLobby );
  NI_ENUM_ITEM( WaitingPartyMembers );
  NI_ENUM_ITEM( InLine );
  NI_ENUM_ITEM( WaitingAccept );
  NI_ENUM_ITEM( Accepted );
  NI_ENUM_ITEM( PreparingPvX );
  NI_ENUM_ITEM( WaitingInPvX );
  NI_ENUM_ITEM( InGame );
  NI_ENUM_ITEM( GameFinished );
  NI_ENUM_ITEM( ClientDropped );
  NI_ENUM_ITEM( WaitingGameFinish );
  NI_ENUM_ITEM( PreGameLobby );
  NI_ENUM_ITEM( AcceptTimedOut );
  NI_ENUM_ITEM( IncompleteParty );
  NI_ENUM_ITEM( PartyCameApart );
NI_ENUM_END_STD;


const PlayerDetails * PvxGameDetails::FindPlayer( TUserIdPvX _pvxUserId )
{
  for ( int i = 0; i < playerDetails.size(); ++i )
    if ( playerDetails[i].pvxUserId == _pvxUserId )
      return &playerDetails[i];
  return 0;
}


NI_ENUM_BEGIN_STD( EPvxLobbyInstanceMode );
  NI_ENUM_ITEM( Normal );
  NI_ENUM_ITEM( ForcePartial );
  NI_ENUM_ITEM( ForceFullGames );
NI_ENUM_END_STD;
} //socialLobby
