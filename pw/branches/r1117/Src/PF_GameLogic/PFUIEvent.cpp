#include "stdafx.h"
#include "PFUIEvent.h"

namespace NGameX
{ 
PFUIEventData::PFUIEventData(NDb::Ptr<NDb::UIEvent> const& dbDesc)
  : signRecipients(dbDesc->signRecipients)
  , dbEvent(dbDesc)
{  
  for ( vector<NDb::Ptr<NDb::UISign> >::const_iterator iUISign = dbDesc->UISigns.begin(), iEnd = dbDesc->UISigns.end(); iUISign != iEnd; ++iUISign )
  {
    signs.push_back( (*iUISign)->Create() );
  }
}

PFUISignMessageToChat::PFUISignMessageToChat(NDb::UISignMessageToChat const& dbDesc) : PFUISign(dbDesc),chatChannel(dbDesc.channel)
{
  signType = NDb::SIGN_SEND_MESSAGE_TO_CHAT;

  for (int i = 0; i < NDb::KnownEnum<NDb::EMessage>::sizeOf; ++i)
  {
    messages[i] = dbDesc.messages[i].GetText();
  }  
}

PFUISignFlyOffText::PFUISignFlyOffText(NDb::UISignFlyOffText const& dbDesc) : PFUISign(dbDesc), text(dbDesc.text)
{
  signType = NDb::SIGN_FLYOFF_TEXT;
}

PFUISignAnnouncement::PFUISignAnnouncement(NDb::UISignAnnouncement const& dbDesc)
: PFUISign(dbDesc)
, pDBDesc(&dbDesc)
{
  signType = NDb::SIGN_ANNOUNCEMENT;
}

PFUISignPlaySound::PFUISignPlaySound(NDb::UISignPlaySound const& dbDesc) : PFUISign(dbDesc), soundDesc(dbDesc.soundDesc)
{
  signType = NDb::SIGN_PLAY_SOUND;
}


PFUISignMessageToStatusLine::PFUISignMessageToStatusLine(NDb::UISignMessageToStatusLine const& dbDesc) : PFUISign(dbDesc)
{
  signType = NDb::SIGN_SEND_MESSAGE_TO_STATUS_LINE;

  for (int i = 0; i < NDb::KnownEnum<NDb::EMessage>::sizeOf; ++i)
  {
    messages[i] = dbDesc.messages[i].GetText();
  }  
}

bool PFUIEvent::CheckSignRecipients(NWorld::PFPlayer const * pCurentPlayer, CObj<PFUISign> const pSign)
{
  NI_VERIFY( pSign, "Invalid the UI event sign!", return false);
  messageId = NDb::MESSAGE_SIMPLE_MESSAGE;

  NDb::ERecipients &signRecipients = pSign->signRecipients;

  if (NDb::RECIPIENTS_USE_FROM_PARENT == signRecipients)
    signRecipients = pEvent.signRecipients;

  switch( signRecipients )
  {
  case NDb::RECIPIENTS_EVENT_PARTICIPANTS:
    // If this event is only for participants and we are not in that list we shouldn't process this event!!!!
    if ( !IsCurrentHeroEventParticipant(pCurentPlayer) )
      return false;
    break;

    // we should determine the killer team and check all players.
  case NDb::RECIPIENTS_EVENT_MAKER_TEAM:
    if ( !IsCurrentHeroInKillerTeam(pCurentPlayer) )
      return false;
    break;

  case NDb::RECIPIENTS_EVENT_MAKER_OPPOSITE_TEAM:
    if ( IsCurrentHeroInKillerTeam(pCurentPlayer) )
      return false;
    break;

  case NDb::RECIPIENTS_ALL_PLAYERS:
    break;

    // we should determine the killer and his Priestess
  case NDb::RECIPIENTS_ALL_PLAYERS_WITHOUT_PRIESTESS:
    break;

    // we should determine the player
  case NDb::RECIPIENTS_PLAYER_ONLY:
    if ( !IsCurrentHeroEventOwner(pCurentPlayer) )
      return false;
    break;

  default:
    NI_ALWAYS_ASSERT("Undefined message recipient type!");
  }//end of switch

  return true;
}

bool PFUIEvent::IsCurrentHeroEventParticipant(NWorld::PFPlayer const * pCurentPlayer)
{
  return IsCurrentHeroEventOwner(pCurentPlayer);
}

bool PFUIEvent::IsCurrentHeroInKillerTeam(NWorld::PFPlayer const * pCurentPlayer)
{
  if ( pCurentPlayer && IsValid(pOwner) )
  {
    if ( pOwner->GetTeamId() != pCurentPlayer->GetTeamID() )
      return false;
  }
  else
    return false;

  return true;
}


bool PFUIEvent::IsCurrentHeroEventOwner(NWorld::PFPlayer const * pCurentPlayer)
{
  CPtr<NWorld::PFBaseUnit> pMyHero(NULL);
  if ( pCurentPlayer )
  {
    pMyHero = (NWorld::PFBaseUnit*)pCurentPlayer->GetHero();
  }

  if ( !IsValid(pMyHero) )
  {
    return false;
  }

  // it's not only killer - it is person who made achievement (incl. priestess)
  if ( IsValid(pOwner) )
  {
    if ( pMyHero == pOwner )
      return true;
  }

  return false;
}

bool PFUIEvent::ExtractLinearAchievement ( NWorld::PFPlayer const * pCurentPlayer, CObj<PFUISign> const pSign )
{
  if ( NDb::MESSAGE_ONLY_FOR_PRIESTESS_MESSAGE == messageId )
    return false;

  messageId = messageLinearId;

  return true;
}

//////////////////////////////////////////////////////////////////////////
// custom events
//////////////////////////////////////////////////////////////////////////
bool PFUITwoUnitsEvent::IsCurrentHeroEventParticipant( NWorld::PFPlayer const * pCurentPlayer )
{
  NI_VERIFY(IsValid(GetOwner()) && IsValid(pSender) && IsValid(pReciever), "All data should be valid.", return false);
  NI_VERIFY((pSender == GetOwner()) || (pReciever == GetOwner()), "Sender or Reciever should be equal to the event's owner.", return false);

  NWorld::PFBaseUnit* pLocalHero(NULL);

  if ( pCurentPlayer )
  {
    pLocalHero = (NWorld::PFBaseUnit*)pCurentPlayer->GetHero();
  }

  if ( !pLocalHero )
  {
    return false;
  }

  // if summoned unit is sender and its master is local hero
  CPtr<NWorld::PFBaseUnit> const& pSenderMaster(pSender->GetMasterUnit());
  bool sameTarget = IsValid(pSenderMaster) && (pSenderMaster == pLocalHero);

  if ( (pLocalHero == GetSender()) || (pLocalHero == GetReciever()) || sameTarget )
    return true;

  return false;
}

bool PFUITwoUnitsEvent::IsCurrentHeroEventOwner( NWorld::PFPlayer const * pCurentPlayer )
{
  NI_VERIFY(IsValid(GetOwner()) && IsValid(pSender) && IsValid(pReciever), "All data should be valid.", return false);
  NI_VERIFY((pSender == GetOwner()) || (pReciever == GetOwner()), "Sender or Reciever should be equal to the event's owner.", return false);

  NWorld::PFBaseUnit* pLocalHero(NULL);

  if ( pCurentPlayer )
  {
    pLocalHero = (NWorld::PFBaseUnit*)pCurentPlayer->GetHero();
  }

  if ( !pLocalHero )
  {
    return false;
  }

  if ( (pLocalHero == GetReciever()) )
    return true;

  return false;
}



} // namespace NGameX

