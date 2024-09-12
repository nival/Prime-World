#include "stdafx.h"

#include "SoundObserver.h"

#include "Easel.h"

#include "LuxBallColorChangedNotification.h"
#include "LuxChainElementExplodedNotification.h"
#include "LuxBallFiredNotification.h"
#include "LuxBallMissNotification.h"
#include "LuxBallHitNotification.h"
#include "LuxBallInTunnelNotifications.h"

#include "LuxSorterBoostFiredNotification.h"

#include "PaintFlyingNotification.h"

#include "LuxChainMovingNotification.h"
#include "LuxChainStoppedNotification.h"
#include "LuxChainSlideLowNotification.h"
#include "LuxChainGeneratedNotification.h"
#include "LuxChainMergedNotification.h"
#include "LuxChainDestroyedNotification.h"
#include "LuxChainFallingNotification.h"

#include "EaselGameWonNotitfication.h"
#include "EaselGameLostNotitfication.h"

#include "LuxBoardRequestStateChangeNotification.h"

#include "EaselSoundsInterface.h"

namespace PF_Minigames
{
bool g_enableEaselSound = true;
static const string g_enableEaselSoundStr = "easel_sound_enable";

REGISTER_DEV_VAR(g_enableEaselSoundStr, g_enableEaselSound, STORAGE_NONE);

//////////////////////////////////////////////////////////////////////////
//
// class SoundObserver implementation
//
//////////////////////////////////////////////////////////////////////////
SoundObserver::SoundObserver() :
EaselNotifier::tObserver(),
pEaselSounds(),
fIsObserving(false),
gameIsEnding( false )
{
  for(int i=0; i<EASEL_MAX_SOUND_PATHS; ++i)
    fIsAtExit[i] = false;
}

SoundObserver::~SoundObserver()
{
  if ( fIsObserving  )
    StopObserving();

  pEaselSounds = 0;
}

void SoundObserver::Init(Easel& _easel)
{
  (_easel.GetNotifier())->Register(*this);
  SubscribeUpdates();
}

void SoundObserver::SetEaselSoundsPtr(IEaselSounds *pSounds)
{
  if(pSounds != 0)
    pEaselSounds = pSounds;
}

void SoundObserver::ClearEaselSoundsPtr()
{
  pEaselSounds = 0;
}

void SoundObserver::SubscribeUpdates()
{
  Subscribe(&SoundObserver::ProcessBulletBallColorChanged);
  Subscribe(&SoundObserver::ProcessChainElementExploded);
  Subscribe(&SoundObserver::ProcessBulletFired);
  Subscribe(&SoundObserver::ProcessBulletHitChain);
  Subscribe(&SoundObserver::ProcessBulletMiss);
  Subscribe(&SoundObserver::ProcessSorterBoostFiredNotification);
  Subscribe(&SoundObserver::PaintFlyHandler);
  Subscribe(&SoundObserver::ProcessChainMovingNotification);
  Subscribe(&SoundObserver::ProcessChainStoppedNotification);
  Subscribe(&SoundObserver::ProcessChainSlideLowNotification);
  Subscribe(&SoundObserver::ProcessChainMergedNotification);
  Subscribe(&SoundObserver::ProcessChainDestroyedNotification);
  Subscribe(&SoundObserver::ProcessChainsFallingNotification);
  Subscribe(&SoundObserver::ProcessLevelWonBeginNotification);
  Subscribe(&SoundObserver::ProcessLevelWonSkipNotification);
  Subscribe(&SoundObserver::ProcessGameLostNotification);
  Subscribe(&SoundObserver::ProcessLuxChainGeneratedNotification);
  Subscribe(&SoundObserver::ProcessBallEntersTunnelNotification);
  Subscribe(&SoundObserver::ProcessBallLeaverTunnelNotification);
  Subscribe(&SoundObserver::ProcessRequestStateChangeNotification);
}


void SoundObserver::ProcessLevelWonBeginNotification(const EaselLevelWonBeginNotification &notification)
{  
  if(g_enableEaselSound == true && pEaselSounds != 0)
  {
    pEaselSounds->StopAllSounds();
    pEaselSounds->StopMusic(true);
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_GAME_WIN);
  }
}

void SoundObserver::ProcessLevelWonSkipNotification(const EaselLevelWonSkipNotification &notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
  {
    pEaselSounds->StopAllSounds();
    pEaselSounds->StopMusic(true);
  }
}

void SoundObserver::ProcessGameLostNotification(const EaselGameLostNotification &notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
  {
    pEaselSounds->StopAllSounds();
    pEaselSounds->StopMusic(true);
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_GAME_LOOSE);
  } 
}

void SoundObserver::ProcessBulletBallColorChanged(const LuxBallColorChangedNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_BALLCOLORCHANGED);
}

void SoundObserver::ProcessChainElementExploded(const LuxChainElementExplodedNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_BALLEXPLODED);
}

void SoundObserver::ProcessBulletFired(const LuxBallFiredNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_BALLFIRED);
}

void SoundObserver::ProcessBulletHitChain(const LuxBallHitChainNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
  {
    if ( notification.fColorMatch  )
      pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_BALLHIT_COLOR_MATCH);
    else
      pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_BALLHIT_COLOR_MISSMATCH);
  }
}

void SoundObserver::ProcessBulletMiss(const LuxBallMissNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_BALLMISS);
}

void SoundObserver::ProcessSorterBoostFiredNotification(const LuxSorterBoostFiredNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_BOOST_SORTER_CLICK);
}

void SoundObserver::ProcessBallEntersTunnelNotification(const LuxBallEntersTunnelNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0 && !gameIsEnding )
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_BALL_IN_TUNNEL);
}

void SoundObserver::ProcessBallLeaverTunnelNotification(const LuxBallLeavesTunnelNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0 && !gameIsEnding )
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_BALL_OUT_TUNNEL);
}

void SoundObserver::PaintFlyHandler(const PaintFlyingNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_PAINT_FLOW);
}

void SoundObserver::ProcessChainMovingNotification(const LuxChainMovingNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_CHAINS_MOVING);
}

void SoundObserver::ProcessChainStoppedNotification(const LuxChainStoppedNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->StopSound(NDb::EASELSOUNDTYPE_CHAINS_MOVING);
}

void SoundObserver::ProcessChainSlideLowNotification(const LuxChainSlideLowNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_DROP_SLIDING_LOW);
}

void SoundObserver::ProcessLuxChainGeneratedNotification(const LuxChainGeneratedNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_DROP_SLIDING_HIGH);
}

void SoundObserver::ProcessChainMergedNotification(const LuxChainMergedNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_CHAIN_MERGED);
}

void SoundObserver::ProcessChainDestroyedNotification(const LuxChainDestroyedNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_CHAIN_DESTROYED);
}

void SoundObserver::ProcessChainsFallingNotification(const LuxChainsFallingNotification& notification)
{
  if(g_enableEaselSound == true && pEaselSounds != 0)
    pEaselSounds->PlaySound(NDb::EASELSOUNDTYPE_CHAIN_REACHED_END);
}

void SoundObserver::ProcessRequestStateChangeNotification(const LuxBoardRequestStateChangeNotification& notification)
{
  gameIsEnding = ( notification.requestState == BOARDSTATE_LEVEL_WON ) || ( notification.requestState == BOARDSTATE_LEVEL_FAIL );
}

} //namespace PF_Minigames

BASIC_REGISTER_CLASS(PF_Minigames::SoundObserver);
BASIC_REGISTER_CLASS(PF_Minigames::NullSoundObserver);