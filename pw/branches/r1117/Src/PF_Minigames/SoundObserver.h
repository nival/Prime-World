#pragma once

#include "EaselNotifications.h"

namespace PF_Minigames
{

// forward declaration area
class Easel;
class IEaselSounds;

class LuxBallColorChangedNotification;
class LuxChainElementExplodedNotification;
class LuxBallFiredNotification;
class LuxBallHitChainNotification;
class LuxBallMissNotification;

class LuxBallEntersTunnelNotification;
class LuxBallLeavesTunnelNotification;

class LuxSorterBoostFiredNotification;

class PaintFlyingNotification;

class LuxChainMovingNotification;
class LuxChainStoppedNotification;
class LuxChainSlideLowNotification;
class LuxChainGeneratedNotification;
class LuxChainMergedNotification;
class LuxChainDestroyedNotification;
class LuxChainsFallingNotification;

class EaselLevelWonBeginNotification;
class EaselLevelWonSkipNotification;
class EaselGameLostNotification;

class LuxBoardRequestStateChangeNotification;

const int EASEL_MAX_SOUND_PATHS = 2;
//////////////////////////////////////////////////////////////////////////
//
// Luxor and Paint events observer class 
// based on a given event, generates sound
//
//////////////////////////////////////////////////////////////////////////
class SoundObserver : public EaselNotifier::tObserver
{
  OBJECT_METHODS(0x9763FAC0,SoundObserver);

public:
  SoundObserver();
  ~SoundObserver();
  
  void StartObserving() { fIsObserving = true; };
  void StopObserving()  { fIsObserving = false; };

  virtual void Init(Easel& _easel);
  
  void SetEaselSoundsPtr(IEaselSounds *pSounds);
  void ClearEaselSoundsPtr();
    
private:
  SoundObserver(const SoundObserver &rhs);
  SoundObserver& operator=(const SoundObserver &rhs);
  
  // notification handlers
  void ProcessLevelWonBeginNotification(const EaselLevelWonBeginNotification &notification);
  void ProcessLevelWonSkipNotification(const EaselLevelWonSkipNotification &notification);
  void ProcessGameLostNotification(const EaselGameLostNotification &notification);

  void ProcessBulletBallColorChanged(const LuxBallColorChangedNotification& notification);
  void ProcessChainElementExploded(const LuxChainElementExplodedNotification& notification);
  void ProcessBulletFired(const LuxBallFiredNotification& notification);
  void ProcessBulletHitChain(const LuxBallHitChainNotification& notification);
  void ProcessBulletMiss(const LuxBallMissNotification& notification);

  void ProcessSorterBoostFiredNotification(const LuxSorterBoostFiredNotification& notification);

  void ProcessBallEntersTunnelNotification(const LuxBallEntersTunnelNotification& notification);
  void ProcessBallLeaverTunnelNotification(const LuxBallLeavesTunnelNotification& notification);

  void PaintFlyHandler(const PaintFlyingNotification& notification);

  void ProcessChainMovingNotification(const LuxChainMovingNotification& notification);
  void ProcessChainStoppedNotification(const LuxChainStoppedNotification& notification);
  void ProcessChainSlideLowNotification(const LuxChainSlideLowNotification& notification);
  void ProcessLuxChainGeneratedNotification(const LuxChainGeneratedNotification& notification);
  void ProcessChainMergedNotification(const LuxChainMergedNotification& notification);
  void ProcessChainDestroyedNotification(const LuxChainDestroyedNotification& notification);
  void ProcessChainsFallingNotification(const LuxChainsFallingNotification& notification);

  void ProcessRequestStateChangeNotification(const LuxBoardRequestStateChangeNotification& notification);

  // data
  bool          fIsObserving;
  bool          gameIsEnding;
  IEaselSounds *pEaselSounds;

  // paths at exit notifications ...
  bool fIsAtExit[EASEL_MAX_SOUND_PATHS];

protected:
  virtual void SubscribeUpdates();
};

//////////////////////////////////////////////////////////////////////////
//
// null sound observer class, is used on remote clients only
// to supress extra sounds
//
//////////////////////////////////////////////////////////////////////////
class NullSoundObserver :  public SoundObserver
{
  OBJECT_METHODS(0xF4685200,NullSoundObserver);
public:
  NullSoundObserver() : SoundObserver() {};
  ~NullSoundObserver() {};

  virtual void Init(Easel& _easel) {};
  
private:
  NullSoundObserver(const NullSoundObserver &rhs);
  NullSoundObserver& operator=(const NullSoundObserver &rhs);

protected:

};

} //namespace PF_Minigames