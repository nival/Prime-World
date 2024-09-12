#pragma once

#include "../PF_GameLogic/DBStats.h"
#include "../PF_GameLogic/DBMinigamesTypes.h"
#include "DBMinigames.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{

_interface IScene;
class SceneObject;

} //namespace NScene



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCore
{
  _interface IWorldBase;
  class WorldCommand;
  class ITransceiver;
}

namespace NDb
{
  struct Consumable;
  struct Texture;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//From PF_GameLogic
namespace NWorld
{
  class PFWorld;
  class PFMinigamePlace;
  class PFBaseHero;
}

namespace NGameX
{
  _interface INaftaInfoProvider;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace SessionEventType {enum EventType;}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

_interface IWorldSessionInterface;
_interface IClientSessionInterface;
_interface IMinigames;
_interface ISingleMinigame;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ECreepType
{
  enum Enum
  {
    Melee,
    Range,
    Siege,
    Last
  };
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct MinigameCreepDesc
{
  ZDATA
    nstl::wstring name;
    float	trainBar; // [0, 1]
    bool isOut;
    int creepID;
    int ownerPlayerID;
    bool instant;

    ECreepType::Enum type;

    nstl::vector<float> statsModifiers;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&name); f.Add(3,&trainBar); f.Add(4,&isOut); f.Add(5,&creepID); f.Add(6,&ownerPlayerID); f.Add(7,&instant); f.Add(8,&type); f.Add(9,&statsModifiers); return 0; }

  MinigameCreepDesc() : creepID(-1), trainBar(0.f), isOut(false), instant(false), ownerPlayerID(-1), type(ECreepType::Melee) {}
  MinigameCreepDesc( const nstl::wstring& _name, int _creepID, ECreepType::Enum _type ) : 
    creepID(_creepID), 
    trainBar(0.f), 
    isOut(false), 
    name(_name), 
    instant(false), 
    ownerPlayerID(-1), 
    type(_type) 
  {}
};

typedef nstl::list<MinigameCreepDesc> MinigameCreeps;




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ex MinigameSharedData
//@iA@TODO: сейчас фабрика не умеет создавать классы, объ€вленные через _interface, поэтому этот интерфейс определим как 'class'
class IMinigamesMain : public IObjectBase
{
public:
  virtual void    Set( NScene::IScene* _scene, NCore::IWorldBase* _worldBase ) = 0;
  virtual void    SetTransceiver( NCore::ITransceiver *_pTransceiver ) = 0;

  virtual NScene::IScene* GetScene() = 0;
  virtual NCore::IWorldBase* GetWorld() = 0;

  //Factory
  virtual IMinigames * ProduceMinigamesObject( NWorld::PFWorld* _pWorld, IWorldSessionInterface * worldInterf, bool _isLocal ) = 0;

  //Stuff
  virtual void    SendWorldCommand( NCore::WorldCommand* _worldCommand ) = 0;
  virtual void    Step( float deltaTime ) = 0;

  // Creep Pool
  virtual bool    GetCreepDesc( int creepID, MinigameCreepDesc& creepDesc ) = 0;
  virtual void    GetFreeCreep( int playerID, ECreepType::Enum creepType, MinigameCreepDesc& creepDesc ) = 0;
	virtual void    ReturnCreep( int creepID ) = 0;

  // Session routes
  virtual void    RegisterCreepSpawner( NDb::EFaction faction, NDb::ERoute routeID, int spawnerObjectID ) = 0;
  virtual int     GetSpawnerID( NDb::EFaction faction, NDb::ERoute routeID ) const = 0;

  virtual const NDb::DBMinigamesCommon* GetCommonDBData() const = 0;
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ex Minigames
_interface IMinigames : public IObjectBase
{
public:
  virtual bool    StartMinigame( NWorld::PFMinigamePlace * _place ) = 0;
  virtual void    LeaveMinigame()                                   = 0;
  virtual void    SetLocal( bool _isLocal )                         = 0;
  virtual bool    IsLocal() const                                   = 0;

  virtual void    OnStep( float _deltaTime )                        = 0;

  virtual IMinigamesMain* GetMain() const                           = 0;

  virtual IWorldSessionInterface * GetWorldSessionInterface() const = 0;

  virtual int     MinigamesCount()                                  = 0;
  virtual ISingleMinigame * GetMinigame( const char * id )          = 0;
  virtual ISingleMinigame * GetMinigame( int index )                = 0;
  virtual const char * GetMinigameId( int index )                   = 0; // Returns 0 for invalid index!

  virtual ISingleMinigame * GetCurrentMinigame()                    = 0;

  virtual void    UpdateM( float _deltaTime )                       = 0;

  virtual void    SetPlacement( const Placement & _placement )      = 0;

  virtual float   GetMinigamePlaceOpacity() const                   = 0;
  virtual bool    DoFade() const                                    = 0;

  virtual void    ForceLeaveMinigame() = 0;

  virtual void    OnMapLoaded() = 0;
  virtual void    InitGames()                                       = 0;
  virtual void    ReinitGames()                                     = 0;
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface ISingleMinigame : public IObjectBase
{
  virtual bool    Start( NWorld::PFMinigamePlace * place )    = 0;
	virtual bool    StartClient()                               = 0;
	
  virtual void    Leave()                                     = 0;

  virtual void    SendLeaveMinigameCommand( IWorldSessionInterface * _worldInterface ) = 0;
  virtual void    SendPauseMinigameCommand( IWorldSessionInterface * _worldInterface, bool enablePause ) = 0;

	virtual void    OnStep( float deltaTime )                   = 0; // Logic
  virtual void    Update( float deltaTime, bool gameOnPause ) = 0; // Visual
  virtual void    OnPause( bool paused )                      = 0; // Logic

  virtual const NDb::DBID & GetDBID() const                   = 0;

  virtual void    PlaceUnderFogOfWar( bool underFogOfWar )    = 0;

  virtual void    CheatDropCooldowns()                        = 0;
  virtual void    CheatWinGame()                              = 0;

  virtual void    SessionFinished( bool victory )             = 0;

  virtual void    OnMapLoaded() = 0;

  virtual void    Eject() = 0;
};



_interface IWorldSessionInterface : public IObjectBase
{
  virtual IMinigames * GetMinigames() = 0;
  virtual int GetPriestessID() const = 0;
  virtual int GetPriestessUserId() const = 0; //Mainly for debug purpose

  virtual NWorld::PFWorld * GetSessionWorld() = 0;

  virtual bool OnLeaveMinigameCmd() = 0;

  virtual int GetPriestessLevel() const = 0;

  virtual void SetNaftaInfoProvider(NGameX::INaftaInfoProvider * naftaInfoProvider) = 0;

  virtual int GetGold() const = 0;
  virtual void AddGold( int _toAdd ) = 0;
  virtual void TakeGold( int _value ) = 0;

  virtual bool CanBuyZZBoost() = 0;
  virtual void BuyZZBoost() = 0;

  virtual int GetTotalNaftaEarned() const = 0;

  virtual NDb::EBidonType GetCurrentBidon() const = 0;
  virtual void SetCurrentBidon( NDb::EBidonType _type ) = 0;

  virtual NWorld::PFMinigamePlace * GetMinigamePlace() const = 0;

  virtual void GetItemTransferTargets( vector<CPtr<NWorld::PFBaseHero>> & targets ) = 0;
  virtual bool AddItemToHero( NWorld::PFBaseHero * target, const NDb::Consumable * pDBDesc, int quantity ) = 0;

  //loggint session events
  virtual void LogMinigameEvent( SessionEventType::EventType eventType, int param1, int param2) = 0;
};

} // namespace PF_Minigames
