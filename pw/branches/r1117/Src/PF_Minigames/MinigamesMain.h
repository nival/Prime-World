#pragma once

#include "MinigameSessionInterface.h"
#include "Core/WorldBase.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCore
{
  class WorldCommand;
  class ITransceiver;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
  _interface IScene;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MinigamesMain : public IMinigamesMain, public CObjectBase
{
	OBJECT_METHODS( 0x9A678C06, MinigamesMain )

public:
	MinigamesMain();

  MinigamesMain( const NDb::DBMinigamesCommon & resource );

  void SetResource( const NDb::DBMinigamesCommon * pRes ) { commonDBData = pRes; }

  virtual void    Set( NScene::IScene* _scene, NCore::IWorldBase* _worldBase );
  virtual void    SetTransceiver( NCore::ITransceiver * _pTransceiver );

  virtual NScene::IScene* GetScene() { return scene; }
  virtual NCore::IWorldBase* GetWorld() { return world; }

  virtual IMinigames * ProduceMinigamesObject( NWorld::PFWorld* _pWorld, IWorldSessionInterface * worldInterf, bool _isLocal );

  virtual void    SendWorldCommand( NCore::WorldCommand* _worldCommand );
  virtual void    Step( float deltaTime );

  // Creep Pool
  virtual bool    GetCreepDesc( int creepID, MinigameCreepDesc& creepDesc );
  virtual void    GetFreeCreep( int playerID, ECreepType::Enum creepType, MinigameCreepDesc& creepDesc );
	virtual void    ReturnCreep( int creepID );

  // Session routes
  virtual void    RegisterCreepSpawner( NDb::EFaction faction, NDb::ERoute routeID, int spawnerObjectID );
  virtual int     GetSpawnerID( NDb::EFaction faction, NDb::ERoute routeID ) const;

  virtual const NDb::DBMinigamesCommon* GetCommonDBData() const { return commonDBData; }

private:
	void  InitPersonalCreeps();   
  void  ParseCreepNames( const CTextRef& names, ECreepType::Enum creepType );

  CPtr<NScene::IScene> scene;
  Weak<NCore::ITransceiver> pTransceiver;
  CPtr<NCore::IWorldBase> world;

  NDb::Ptr<NDb::DBMinigamesCommon> commonDBData;

	typedef nstl::hash_map<int, MinigameCreepDesc> PersonalCreeps;

	PersonalCreeps personalCreepStack;
	int nextCreepID;

  typedef nstl::map<NDb::ERoute, int> RouteSpawners;
  typedef nstl::map<NDb::EFaction, RouteSpawners> Spawners;

  Spawners spawners;

  float sessionTime;
};

} // namespace PF_Minigames
