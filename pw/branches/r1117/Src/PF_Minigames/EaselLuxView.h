#pragma once

#include "EaselNotifications.h"
#include "EaselLuxLerpContainer.h"
#include "RollCoordsConverter.h"
#include "ViewBallCoordsConverter.h"

namespace NDb
{
  enum EColor;
}

namespace PF_Minigames
{

class LuxBallCreateNotification;
class LuxBallDeleteNotification;
class LuxChainBallAddedNotification;

class MinigameClientObject;
class EaselLuxViewPath;

class Easel;
class LuxBall;
class LuxBall;

class LuxGameLogic;
class LuxPlatform;
class LuxTunnelPoint;

class EaselLuxViewFallingObject;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class represents view logic for luxor part. It listens for luxor logic notifications and acts correspondingly
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselLuxView: public EaselNotifier::tObserver
{
	OBJECT_METHODS(0x99639AC0, EaselLuxView);
public:

	EaselLuxView( Easel* _easel );

	void Reset();

  void InitAfterWorld( LuxGameLogic* _gameLogic );
  void ReleaseAfterWorld( LuxGameLogic* _gameLogic );

  void Step( float deltaTime, LuxGameLogic* _gameLogic );
  void Update( float deltaTime, LuxGameLogic* _gameLogic );

protected:
	virtual void SubscribeUpdates();

private:
  EaselLuxView();

  // lerp container
  LuxViewLerpContainer lerpContainer;
	
	// ball notification handlers 
	void CreateBallHandler( const LuxBallCreateNotification& notification );
  void DeleteBallHandler( const LuxBallDeleteNotification& notification );

  // falling object notification handlers
  void StartPickEffect();
  
  // chain notifications
  void ChainBallAddedHandler(const LuxChainBallAddedNotification& notification);

  void AddBall( LuxBall* ball );
  void AddPainBlastBall( LuxBall* ball );
  void AddCommonBall( LuxBall* ball );

  void DeleteBall( void* ball );

  void ReleaseClientObject(void* logicObject);


  void CreatePlatform( LuxPlatform* _worldPlatform );
  void CreatePaths( LuxGameLogic* _gameLogic );
  void CreateTunnels( LuxGameLogic* _gameLogic );
  void CreateTunnelPoint( const SVector& _point );

  void OnLevelStarted();
  void OnLevelFinished();

  void CheckFreezeBoost( LuxGameLogic* _gameLogic );

  void StepFallingObjects( LuxGameLogic* _gameLogic );

	CPtr<Easel> easel;

  CObj<PathConverter> subConverter;
  CObj<BallCoordsConverter> pathConverter;

  typedef nstl::map<int,CObj<EaselLuxViewPath>> Paths;
  Paths ballPaths;

	typedef nstl::map<void* , CPtr<MinigameClientObject> > TClientObjects;
	TClientObjects clientObjects;

  typedef nstl::list< CPtr<MinigameClientObject> > DecorativeObjects;
  DecorativeObjects decorativeObjects;

	CPtr<MinigameClientObject> platformObject;

  bool levelStarted;
  bool clientIsFrozen;

  typedef nstl::list< CObj<EaselLuxViewFallingObject> > FallingObjects;
  FallingObjects fallingObjects;
};

} // PF_Minigames
