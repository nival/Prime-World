#pragma once

#include "../libdb/Placement.h"
#include "../Scene/SceneObject.h"

#include "../Sound/SoundUI.h"
#include "../Client/Overtips.h"

#include "DBClinic.h"
#include "ClinicCreepWish.h"
#include "ClinicUIDesc.h"
#include "MinigameBase.h"
#include "MinigameSessionInterface.h"
#include "Random.h"
#include "ClinicHeader.h"
#include "ClinicDecorationObject.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
	_interface IScene;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NGameX
{
	struct TooltipsManager;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

namespace ECreepType { enum Enum; }

class ClinicScreen;

class ClinicBonus;
class ClinicCreep;
class ClinicPlace;
class ClinicPlayer;
class ClinicEntrance;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EClinicGameMode
{
	enum Enum
	{
		None,
		Game,
		GameFinished, // After time is away, we must move all creeps out
		GameIsWon,
		GameIsLosed,
		Shop,
	};
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Clinic : /*public MinigameBase,*/ public CObjectBase
{
	OBJECT_METHODS( 0x9A678C04, Clinic )
public:
	Clinic();
	virtual ~Clinic();

	typedef nstl::hash_map< int, CObj<MinigameClientObject> >   ClientObjects;
	typedef nstl::hash_map< int, CObj<MinigameWorldObject> >    WorldObjects;
  typedef nstl::map< int, CPtr<ClinicPlace> >                 ClinicPlaces; // place ndb index -> place world object
  typedef nstl::map< NDb::EBonusType, CPtr<ClinicBonus> >     ClinicBonuses;
  typedef nstl::set< CPtr<ClinicItem> >                       ClinicItems;

  bool Init( Minigames * _minigameManager, NScene::IScene * _scene );

	MinigameWorldObject* GetWorldObject( int _objectID );
	ClinicDecorationClientObject* CreateDecoration( const NDb::DBSceneObject* _DBSceneObject );

  void SetOvertips(Overtips::IManager * pOvertips) { overtips = pOvertips; }

	void RemoveWorldObject( int _objectID ); 
	void RemoveClientObject( int _objectID ); 

	const WorldObjects& GetWorldObjects() const;

  const ClinicPlaces & GetGiftedPlaces() const { return giftedPlaces; }

  const ClinicPlaces & GetPlaces() const { return clinicPlaces; }
  const ClinicBonuses & GetBonuses() const { return clinicBonuses; }
  void RetrieveAllItems(ClinicItems * pDest) const;

  void SetBuyUICallback(IClinicBuyUIRequest * req) { buyUIRequest = req; }
  IClinicBuyUIRequest * BuyUICallback() const { return IsValid(buyUIRequest) ? buyUIRequest : NULL; }

	EClinicGameMode::Enum GetGameMode() const;
  bool IsInGame() const { return (gameMode == EClinicGameMode::Game) || (gameMode == EClinicGameMode::GameFinished); }

	ClinicCreep* InitCreepOfType( ECreepType::Enum type, const Placement& placement );
  const NDb::BaseUIMaterial* GetImageOfCreepType( ECreepType::Enum type ) const;

	void FillCreepResults( ClinicCreepsUIDesc & _descriptions );
  void FillCreepSpawnResults( MinigameCreeps& _spawnCreeps );

	ClinicPlayer* GetPlayer();
	const Placement& GetExitPlacement();

	void MovePlayerTo( int _objectID, bool pushFront );
  void CancelPlayerQueue();

  bool ItemCanBeBought(ClinicItem * clinicItem, bool ignorePrice = false) const;
  bool BuyItem(ClinicItem * clinicItem, bool correctOther = true);
	static bool IsShopCheatOn(); // $TODO remove

  void OnCreepSatisfied();

	bool IsBonusBought( NDb::EBonusType _bonusType );
	ClinicBonus * GetBonusByType( NDb::EBonusType _bonusType );

	int FindFriend( int _creepID, int _placeID, int& _friendID );
	int FindExistedFriend( ClinicCreep* _creep );
	bool CheckFriendIsNear( int _placeID, int _friendshipID );
	int GetNextFriendshipID();

	MinigameClientObject* GetClientObject( int objID ) const;
	MinigameWorldObject* GetWorldObject( int objID ) const;
  void EraseClientObjectById( int objId );
  void EraseClientObject( MinigameWorldObject * worldObject );

  // for states
  void GetWishProbabilities( WishProbabilities _wishProbabilities, NDb::ECreepWish exclude );
  bool IsWishAvailable( NDb::EPlaceType _placeType, NDb::ECreepWish _wishType );

	// for bonuses
	void OnWakeAll();
	void OnStartBell( bool start );
	void OnCleanAll( bool start );
	void OnStarBonus();

	bool IsBellChiming();
	bool IsCleaningStarted();

	float GetClickBonusValue();
	float GetPlayerVelocity();

  int   GetGold() const;
	void  AddGold( int _amount );
  void  TakeGold( int _amount ) const;

  float GetLevelTime() const { return currentLevelTime; }
  float GetLevelDuration() const { return levelDuration; }

	const NDb::CreepBehaviourDesc* GetCreepBehaviourDesc();
	const NDb::DBMinigame_Clinic* GetClinicDesc();


	// for Clinic Lobby
	int GetMaxAvailableLevel() const;
	int GetNextLevel() const;
	int GetCurrentLevel() const;
	int GetLevelNumber();
	void GetLevelUIDesc(ClinicLevelUIDesc * pLevelDesc, int _levelID = -1);

  void PlaySound( NDb::EClinicSounds clinicSound );
  void PlayBonusSound( NDb::EBonusType bonusSound );

  void StartShop();
  bool StartLevel( int _levelID );
  void StopLevel( const MinigameCreeps& _spawnCreeps );

	// only for prototyping
	bool IsMinigameSceneObject( NScene::SceneObject* sceneObject );
  void InsertMinigameSceneObject( NScene::SceneObject* sceneObject );

	RandomGenerator* GetRandom();

	// from ISingleMinigame
	virtual bool    Start( NWorld::PFMinigamePlace * place );
	virtual bool    StartClient();

  virtual void    Leave();

	virtual void    Step( float deltaTime );
  virtual void    Update( float deltaTime, bool gameOnPause );

  virtual const NDb::DBID & GetDBID() const;

  virtual void    PlaceUnderFogOfWar( bool underFogOfWar );

  virtual void    CheatDropCooldowns();

  virtual void    SessionFinished( bool victory );

private:
	void Clear();
	void PrepareClientObjectForShop( int _objectID, bool _init, int _cost, int _accessLevel );
	void PrepareClientObjectsForShop( bool _init );
	void ClearCreeps();
  void SpawnCreepsAtSession( const MinigameCreeps& _spawnCreeps );
	
	void AutoBuyPlacesBonuses();
  void RecalcPurchasedBonusesAndPlaces();
	void InitGeometry( const CVec3& _pos, const CVec3& _scale );
  ClinicBonus* InitBonusObject( NDb::EBonusType _type, const NDb::BonusDesc* _bonusDesc );
  void UpdateAllPositions( const CVec3 & _pos, const CVec3 & _scale );
  void GetWorldPlacement( const CVec3& localGamePos, Placement& worldPlacement );
	void LevelSpecificInit();
  void StartLevelClient();
	
	NDb::EPlaceType GetPlaceType( int _placeID );

	bool CheckGameMode();
  void OnLevelIsWon( bool giveOutAwards );

  void InitSounds();

  template<class _T> _T* InitClientObject(  MinigameWorldObject* _worldObject, const NDb::DBSceneObject* _DBSceneObject, 
                                            const CVec3& localGamePos, bool collidable = true );

  template<class _T> _T* CreateWorldObject();
	template<class _T> _T* CreateClientObject( MinigameWorldObject* _worldObject, const NDb::DBSceneObject* _DBSceneObject, 
																							const Placement& _placement, bool collidable = true );

  typedef nstl::list<CPtr<ClinicCreep>> ClinicCreeps;

	// only for prototype refactor later
	typedef nstl::set<NScene::SceneObject *> MinigameSceneObject;

  struct SLevelCompletionInfo
  {
    EClinicLevelStatus::Enum  lastStatus, bestStatus;
    float                     goldMade;
    SLevelCompletionInfo() : lastStatus(EClinicLevelStatus::Incomplete), bestStatus(EClinicLevelStatus::Incomplete), goldMade(0) {}
  };

  typedef nstl::vector<SLevelCompletionInfo> LevelCompletion;
  typedef vector< pair<int, int> > TNeighbours;

  ClientObjects clientObjects;
  CPtr<IClinicBuyUIRequest> buyUIRequest;
  MinigameSceneObject minigameSceneObjects;

  ZDATA_(MinigameBase)
  ZNOPARENT( CObjectBase)
	bool clientInitialized;

  WorldObjects worldObjects;

  ClinicPlaces clinicPlaces;
	ClinicCreeps clinicCreeps;
	ClinicBonuses clinicBonuses;
	CPtr<ClinicPlayer> player;
	CPtr<ClinicEntrance> entrance;

	int nextObjectID;
  int nextDecorID;

	float levelDuration;
	float currentLevelTime;

	NDb::Ptr<NDb::DBMinigame_Clinic> pDBClinic;

	CVec3 placePos;
	CVec3 placeScale;

	// gameplay logic
	LevelCompletion levelCompletion;
  ZSKIP //Was 'float timeSpentUntilVictory'

	bool isBellChiming;
	bool isCleaningStated; 
	int nextFriendshipID;

	TNeighbours neighbours;

	int levelID;
	int nextLevelID;

	EClinicGameMode::Enum gameMode;

  ClinicPlaces giftedPlaces;

	RandomGenerator randomGenerator;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(MinigameBase*)this); f.Add(2,&clientInitialized); f.Add(3,&worldObjects); f.Add(4,&clinicPlaces); f.Add(5,&clinicCreeps); f.Add(6,&clinicBonuses); f.Add(7,&player); f.Add(8,&entrance); f.Add(9,&nextObjectID); f.Add(10,&nextDecorID); f.Add(11,&levelDuration); f.Add(12,&currentLevelTime); f.Add(13,&pDBClinic); f.Add(14,&placePos); f.Add(15,&placeScale); f.Add(16,&levelCompletion); f.Add(18,&isBellChiming); f.Add(19,&isCleaningStated); f.Add(20,&nextFriendshipID); f.Add(21,&neighbours); f.Add(22,&levelID); f.Add(23,&nextLevelID); f.Add(24,&gameMode); f.Add(25,&giftedPlaces); f.Add(26,&randomGenerator); return 0; }
private:
  int placeTypesBought[NDb::KnownEnum<NDb::EPlaceType>::sizeOf];
  bool bonusTypeBought[NDb::KnownEnum<NDb::EBonusType>::sizeOf];

  CPtr<ClinicBonus> bonuses[NDb::KnownEnum<NDb::EBonusType>::sizeOf];

  //client code
  //TODO: refactor
  Weak<Overtips::IManager> overtips;

  // sound //$TODO refactor it after EventSystem
  NSound::Sound2D* sounds[ NDb::KnownEnum<NDb::EClinicSounds>::sizeOf ];
  NSound::Sound2D* soundsForBonus[ NDb::KnownEnum<NDb::EBonusType>::sizeOf ];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline EClinicGameMode::Enum Clinic::GetGameMode() const { return gameMode; }

inline int Clinic::GetNextLevel() const { return nextLevelID; }
inline int Clinic::GetCurrentLevel() const { return levelID; }
inline int Clinic::GetNextFriendshipID() { int tmp = nextFriendshipID; ++nextFriendshipID; return tmp; }

inline bool Clinic::IsBellChiming() { return isBellChiming; }
inline bool Clinic::IsCleaningStarted() { return isCleaningStated; }

inline const Clinic::WorldObjects& Clinic::GetWorldObjects() const { return worldObjects; }

inline bool Clinic::IsBonusBought( NDb::EBonusType _bonusType ) { return bonusTypeBought[_bonusType]; } 
inline ClinicBonus* Clinic::GetBonusByType( NDb::EBonusType _bonusType ) { return bonuses[_bonusType]; }  

inline RandomGenerator* Clinic::GetRandom() { return &randomGenerator; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _T> 
inline _T* Clinic::CreateWorldObject()
{
	_T* newObject = new _T();

	worldObjects.insert( nstl::make_pair( nextObjectID, newObject ) );

	newObject->SetObjectID( nextObjectID );
  newObject->InitWorldObject( this );

	nextObjectID++;

	return newObject;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _T> 
inline _T* Clinic::CreateClientObject(  MinigameWorldObject* _worldObject, const NDb::DBSceneObject* _DBSceneObject, const Placement& _placement, bool collidable /*= true*/ )
{
	_T* newObject = new _T();

  newObject->SetClinic( this );

	NScene::SceneObject* sceneObject = newObject->Init( _worldObject, GetScene(), _DBSceneObject, _placement, collidable );

  int _objectID = IsValid( _worldObject ) ?  _worldObject->GetObjectID() :	--nextDecorID;

	sceneObject->SetOwnerID( _objectID );
	InsertMinigameSceneObject( sceneObject );

	clientObjects.insert( nstl::make_pair( _objectID, newObject ) );

	return newObject;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class _T> 
inline _T* Clinic::InitClientObject(  MinigameWorldObject* _worldObject, const NDb::DBSceneObject* _DBSceneObject, 
                      const CVec3& localGamePos, bool collidable /*= true*/ )
{
  Placement placement;
  GetWorldPlacement( localGamePos, placement );

  return CreateClientObject<_T>( _worldObject, _DBSceneObject, placement, collidable );
}


} // namespace PF_Minigames
