#pragma once

#include "PF_Core/WorldObject.h"

#include "EaselDef.h"

#include "EaselClient.h"
#include "EaselStatistics.h"
#include "EaselConstants.h"

namespace NScene
{
  _interface IScene;
}

namespace UI
{
  class Window;
}


namespace NWorld
{
  class PFBaseHero;
  class PFEaselPlayer;
}


namespace PF_Minigames
{

_interface IWorldSessionInterface;

class EaselWorldClientConvertHelper;
class EaselWorld;
class EaselView;

#define BOOST_COUNT 3

class Easel :	public PF_Core::WorldObjectBase
{
  // common object functionality
  OBJECT_METHODS( 0x99636C40, Easel );

public:
  typedef StaticArray<NDb::EBoostType, BOOST_COUNT> CurrentBoosts;

private:

  ZDATA_(PF_Core::WorldObjectBase)

  NDb::Ptr<NDb::DBEaselData> easelData;
  
  CObj<EaselWorld> world;
  CurrentBoosts currentBoost;

  nstl::vector<int> trajectoryUseCount;
  bool firstTrajectory;
  int lastTrajectory;

  int randomSeed;

  EaselStatistics easelStatistics;

  CPtr<IWorldSessionInterface> worldSessIFace;

  // shared notification object
  CObj<EaselNotifier> easelNotifier;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&easelData); f.Add(3,&world); f.Add(4,&currentBoost); f.Add(5,&trajectoryUseCount); f.Add(6,&firstTrajectory); f.Add(7,&lastTrajectory); f.Add(8,&randomSeed); f.Add(9,&easelStatistics); f.Add(10,&worldSessIFace); f.Add(11,&easelNotifier); return 0; }

private:
  CObj<EaselView>  view;  // basic view component
    
  EaselClient client;   // scene objects management

  // conversion handlers
  CObj<EaselWorldClientConvertHelper> convertHelper;
  
  
  // positioning and scaling
  Placement easelPlacement;

  // Screens cache
  NDb::Ptr<NDb::UIBaseLayout> easelScreenCache;
  NDb::Ptr<NDb::UIBaseLayout> failScreenCache;
  NDb::Ptr<NDb::UIBaseLayout> lobbyScreenCache;
  NDb::Ptr<NDb::UIBaseLayout> newboostScreenCache;
  NDb::Ptr<NDb::UIBaseLayout> resultsScreenCache;
  NDb::Ptr<NDb::UIBaseLayout> tutorScreenCache;

  // scene
  CPtr<NScene::IScene>    scene;
 
  void PrefetchMaterial( const char * _name );
  void ReserveSceneObject( const NDb::Ptr<NDb::DBSceneObject>& db, int reserve = 1);
  void ReserveStandaloneEffect(const NDb::Ptr<NDb::BasicEffectStandalone>& db, int reserve = 1);
  void ReserveAttachedEffect(const NDb::Ptr<NDb::BasicEffectAttached>& db, int reserve = 1);

  // creation overloads
  virtual EaselWorld* CreateWorldObject();
  virtual EaselView* CreateViewObject( Easel* _easel );

protected:
  Easel() {}

public:
  Easel( PF_Core::IWorld* _pWorld );
  virtual ~Easel();
 
  void PrefetchData();

  EaselWorld* GetWorld() const { return world; };
  PF_Core::IWorld* GetPFWorld() const { return PF_Core::WorldObjectBase::GetWorld(); };
  EaselClient& GetClient() { return client; }
  EaselView* GetView() { return view; }

  EaselWorldClientConvertHelper* GetConvertHelper()  const { return convertHelper; };

  EaselNotifier* GetNotifier()  { return easelNotifier; };

  const NDb::DBEaselData* GetData() { return easelData; }
  const NDb::DBPriestessLevelStats* GetPriestessLevelStats();
  const NDb::DBPainterFragment* GetPainterLevelData();

  int GetRandomSeed() const { return randomSeed;  };
  void SetRandomSeed( int _seed ) { randomSeed = _seed; }; 

  const EaselStatistics& GetStatistics() const { return easelStatistics; };
  
  // init/uninit
  bool Init( NScene::IScene * _scene, IWorldSessionInterface * _worldSessionFace, const CVec3 & _minigamePos );

  // placement and scaling
  bool ChangePlacement(const Placement& _placement);
  

  NScene::IScene* GetScene()               const { return scene; }
  IWorldSessionInterface * GetWorldSessionInterface() const { return worldSessIFace; };
  
  const Placement& GetPlacement() const { return easelPlacement; };

  void CheatResetCooldowns();
  void CheatWinGame();

  //level
  virtual void StartLevel( int paintId, int levelID, int seed, NWorld::PFEaselPlayer* player );
  virtual void StopLevel();
  virtual bool PauseLevel( bool _fPause );

  virtual void StepM( float deltaTime );
  virtual bool Update( float deltaTime, bool gameOnPause );

  virtual bool ProcessMouseMove( const CVec2& _pos );
  virtual bool ProcessMouseEvent( EEaselMouseEvents::Enum _key );

  bool ProcessKeyboardEvent( EEaselKeyboardEvents::Enum event );

  int GetLevelID() { return easelStatistics.GetCurrentLevelStatistics()->GetLevelID(); }
  int GetPaintID() { return easelStatistics.GetCurrentLevelStatistics()->GetPaintID(); }


  // boosts
  const CurrentBoosts& GetCurrentBoosts() { return currentBoost; }

  typedef nstl::vector<NDb::EBoostType> BoostTypes;

  int GetLevelBoostCount( int levelID );
  bool CanRegenerateBoosts( int levelID, int gold );
  void GetBoostTypesForSlot( int slotID, int levelID, BoostTypes& types, NDb::EBoostType exceptType );
  int GetRegenerateBoostPrice( int levelID );
  int GetBoostPrice( NDb::EBoostType _type );

  void RegenerateBoosts( bool haveToBuy, int levelID, int seed );

  void OnBoost( NDb::EBoostType _type );

  // trajectories
  int SelectTrajectory();

  void Copy( Easel* _remoteCopy );
};

} // namespace PF_Minigames