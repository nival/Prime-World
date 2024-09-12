#pragma once

#include "../PF_Core/BasicEffect.h"

#include "EaselNotifications.h"

#include "DBEasel.h"

namespace NDb
{
  struct BasicEffectAttached;
}

namespace PF_Core
{
  class SceneComponentsEffect;
  class BasicEffectStandalone;
}

namespace NScene
{
  class SceneObject;
}


namespace PF_Minigames
{

class Easel;
class EaselViewAlchemistPot;
class MinigameClientObject;

class LuxBallExplodedNotification;
class PaintFlyingNotification;
class LuxSorterBoostFiredNotification;
class PaintFlyingInPointNotification;

class LuxAlchemistIncomingFlowNotification;
class LuxAlchemistOutgoinFlowNotification;

class LuxGameLogic;

// class listens for all logic notifications and creates corresponding effects. All effects should be standalone
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselViewEffects : public EaselNotifier::tObserver
{
  OBJECT_METHODS(0x99640C00, EaselViewEffects)
public:

	EaselViewEffects();

  void Init(Easel& _easel);

  // kills all effects
  void Reset();

  // update effects and remove dead
  void Update( float deltaTime, LuxGameLogic* _gameLogic );

  void OnPaintBlastBallExplosion( const SVector& worldCoords );

  void OnFreeze();
  void OnUnfreeze();

  void ShowPaintBlastCursor( const Placement& placement );
  void HidePaintBlastCursor();

protected:

  virtual void SubscribeUpdates();

private:
  void ClearFreeze( bool brute );

  void CheckAlchemist( LuxGameLogic* _gameLogic );

  void UpdateStartMovie( LuxGameLogic* _gameLogic );
  void CreateStartMovie();
  void ReleaseStartMovie();

  void UpdateEndMovie( LuxGameLogic* _gameLogic );
  void CreateEndMovie();
  void ReleaseEndMovie();

  // notification handlers 

  void BallExplosionHandler(const LuxBallExplodedNotification& notification);
  void PaintFlyHandler(const PaintFlyingNotification& notification);
  void PaintFlyInPointHandler(const PaintFlyingInPointNotification& notification);

  void SorterBoostFiredNotification(const LuxSorterBoostFiredNotification& notification);
  
  //Alchemist notifications
  void AlchemistIncomingFlowHandler( const LuxAlchemistIncomingFlowNotification & notification );
  void AlchemistOutgoinFlowHandler( const LuxAlchemistOutgoinFlowNotification & notification );

  
  // get list of colored flow effects by distance. We will use different flow effects for different distance interval. So we can scale them without fear
  const NDb::DBEaselFlowEffectGroup* GetDBFlowEffectGroup( float distance ) const;

	CPtr<Easel> easel;

  CObj<PF_Core::BasicEffectStandalone> startMovie;    // start level movie 
  CObj<PF_Core::BasicEffectStandalone> endMovie;      // end level movie

  CObj<PF_Core::BasicEffectStandalone> freezeEffect;
  CObj<PF_Core::BasicEffectStandalone> paintblastCursorEffect;

  float lastExplosionRotationAngle;

  CObj<EaselViewAlchemistPot> alchemistPot;
};

} // PF_Minigames
