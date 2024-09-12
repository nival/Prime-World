#pragma once
#include "Easel.h"

namespace NWorld
{
  class PFEaselPlayer;
}

namespace PF_Minigames
{

// forward declaration 
class EaselCommandsSender;

class EaselLocal : public Easel
{
  OBJECT_METHODS(0xF467F440,EaselLocal);
public:
  EaselLocal( PF_Core::IWorld* _pWorld );
  ~EaselLocal();

  void SetCommandsHatch( EaselCommandsSender* _hatch ) { sessionHatch = _hatch; };

  virtual void StartLevel( int paintId, int levelID, int seed, NWorld::PFEaselPlayer* player );
  virtual void StopLevel();

  virtual void StepM( float deltaTime );  
  virtual bool Update( float deltaTime, bool gameOnPause );

  virtual bool ProcessMouseMove( const CVec2& _pos );
  virtual bool ProcessMouseEvent( EEaselMouseEvents::Enum _key );

private:
  EaselLocal() {}

  void StepInterval();

  // creation overloads
  virtual EaselWorld* CreateWorldObject();
  virtual EaselView* CreateViewObject( Easel* _easel );

  CPtr<EaselCommandsSender> sessionHatch;

  int numMouseLeftButtonClicked;
  int numMouseRightButtonClicked;
  SVector mousePos;

  uint stepCounter;
  bool gameStarted;
};

}