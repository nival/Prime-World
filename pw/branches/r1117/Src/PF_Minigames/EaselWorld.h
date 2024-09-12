#pragma once

#include "../Core/WorldCommand.h"
#include "../PF_Core/WorldObject.h"

#include "SoundObserver.h"

#include "EaselPriestess.h"
#include "EaselDef.h"
namespace NWorld
{
  class PFEaselPlayer;
}
namespace PF_Minigames
{

class      Easel;
class      EaselLevelStatistics;
class      IEaselSounds;
class      LuxGameLogic;
class      PaintLogic;

_interface IWorldSessionInterface;

//////////////////////////////////////////////////////////////////////////
// class provides functionality for easel world - start and end game, step for luxor and paint parts.
// class instance always presents in all sessions when easel minigame is online
//////////////////////////////////////////////////////////////////////////
class EaselWorld : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D6BBBC0, EaselWorld );
public:
	EaselWorld( PF_Core::IWorld* _pWorld );
  virtual ~EaselWorld();

  EaselPriestess*  GetPriestessProxy() const { return easelPriestess; };
  LuxGameLogic* GetLogic() { return luxGameLogic; }
  PaintLogic* GetPaintLogic() { return paintGameLogic; }
  IEaselSounds* GetSound() { return easelSound; }
  EaselLevelStatistics* GetLevelStatistics() { return levelStatistics; }
  Easel* GetEasel() { return easel; }

  bool Init(Easel& _easel);

	void StartGame(int currentLevel, const CObj<EaselLevelStatistics> _levelStatistics, NWorld::PFEaselPlayer* player );
	void StopGame();

  void UpdateInputMove(SVector _mousePos);
	void StepM(const EaselStepInfo& info);

  bool ProcessKeyboardEvent( EEaselKeyboardEvents::Enum event );

  int GetNextID() { nextID++; return nextID; }

protected:
  EaselWorld() {}
private:

  ZDATA_(PF_Core::WorldObjectBase)
  CObj<LuxGameLogic> luxGameLogic;   // luxor logic data
  CObj<PaintLogic> paintGameLogic; // paint logic data

  // easel statistics object
  CObj<EaselPriestess>       easelPriestess;
  CObj<EaselLevelStatistics> levelStatistics;

  int nextID;

  CPtr<Easel> easel;

public:
ZEND ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&luxGameLogic); f.Add(3,&paintGameLogic); f.Add(4,&easelPriestess); f.Add(5,&levelStatistics); f.Add(6,&nextID); f.Add(7,&easel); return 0; }

private:

  // sound logic data
  CObj<IEaselSounds> easelSound;
  CObj<SoundObserver>     soundObserver;


  // luxor game logic data start/stop methods
  void StartLuxGameLogic( NWorld::PFEaselPlayer* player );

  // sound logic data start/stop methods
  void StartSoundLogic();
  bool StopSoundLogic();

  // statistics logic start/stop methods
  bool StartStatistics();

  // objects creation methods ....
  virtual EaselPriestess* CreatePriestessProxy() { return 0; }
  virtual SoundObserver* CreateSoundObserver() { return 0; }
  virtual IEaselSounds* CreateEaselSounds() { return 0; }
};

//////////////////////////////////////////////////////////////////////////
//
// local luxor world copy
//
//////////////////////////////////////////////////////////////////////////
class EaselWorldLocal : public EaselWorld
{
  OBJECT_METHODS( 0x9D6BBBC5, EaselWorldLocal );
public:
  EaselWorldLocal( PF_Core::IWorld* _pWorld );
  ~EaselWorldLocal();

  //
  //
  //

private:
  EaselWorldLocal() {}

  virtual EaselPriestess* CreatePriestessProxy();
  virtual SoundObserver* CreateSoundObserver();
  virtual IEaselSounds* CreateEaselSounds();

protected:

};

//////////////////////////////////////////////////////////////////////////
//
// remote luxor world copy
//
//////////////////////////////////////////////////////////////////////////
class EaselWorldRemote : public EaselWorld
{
  OBJECT_METHODS( 0x9D6BBBC6, EaselWorldRemote );
  EaselWorldRemote() {}

public:
  EaselWorldRemote( PF_Core::IWorld* _pWorld, IRemoteToLocalLink * featCb );
  ~EaselWorldRemote();

private:
  CPtr<IRemoteToLocalLink> localLink;

  virtual EaselPriestess* CreatePriestessProxy();
  virtual SoundObserver* CreateSoundObserver();
  virtual IEaselSounds* CreateEaselSounds();

protected:

};

} // namespace PF_Minigames