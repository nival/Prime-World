#pragma once

#include "MinigameSessionInterface.h"
//#include "Minigames.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
	_interface IScene;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
  class PFStatistics;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

class Minigames;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MinigameBase : public ISingleMinigame
{
public:
  MinigameBase();
  virtual ~MinigameBase();

  virtual bool          InitMinigames( Minigames * minigames, NScene::IScene * _scene );

  bool                  IsPaused() const { return pausedNow; }
  Minigames *           GetMinigames() const { return minigames; }
  NScene::IScene *      GetScene() const { return scene; }

  NWorld::PFStatistics * GetStatistics();
  int                   GetPriestessId();
  int                   GetUserId();

  bool                  InitiatePause( bool enablePause );

protected:
  //ISingleMinigame
  virtual void          OnPause( bool paused ) {}
  virtual const NDb::DBID & getDBID() const;

private:
  CPtr<NScene::IScene>  scene;

  ZDATA
  ZNOPARENT(ISingleMinigame)
  CPtr<Minigames> minigames;
  ZNOCRC
  bool                  pausedNow;
  ZNOCRCEND
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&minigames);  if(!f.IsChecksum()){ f.Add(3,&pausedNow);  } return 0; }
};

} //namespace PF_Minigames
