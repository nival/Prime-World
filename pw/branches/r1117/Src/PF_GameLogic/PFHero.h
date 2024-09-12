#pragma once

#include "PFCreature.h"
#include "PFPlayer.h"
#include "PFApplMod.h"
#include "InventoryInterface.h"
#include "System\StarForce\StarForce.h"

namespace NDb
{
  struct Hero;
  enum EStat;
  struct Consumable;
  enum EConsumableOrigin;
}

  
namespace NGameX { class PFBaseClientHero;}

namespace SessionEventType {enum EventType;}

namespace EHeroState
{
  enum Enum
  {
    First = 0,
    Second,
    _Count,
  };
}

namespace NWorld
{
class PFAbilityData;
class PFConsumable;
class PFTalent;
class PFTalentsSet;
class PFHeroStatistics;
class PFGlyph;

namespace ETalentActivation { enum Enum; }

struct CloneParams
{
	float				lifeTime;
	float				followRange;
	bool				mirrorOwnerAbilities;
  bool        shouldPlaySummonEffect;
  bool        copyStats;
  bool        bSlave;
  NDb::Ptr<NDb::UnitTargetingParameters> targetingParams;
  PFBaseHero* pOwner;
  bool        isDummy;
  bool        initTalents;

	CloneParams()
	: lifeTime(0)
	, followRange(0)
  , mirrorOwnerAbilities(false)
  , shouldPlaySummonEffect(true)
  , copyStats(false)
  , bSlave(false)
  , pOwner(NULL)
  , isDummy(false)
  , initTalents(false)
	{}
};

class PFBetweenSessionsData: public PFWorldObjectBase
{
  // Not yet truly between sessions, but will be)

  WORLD_OBJECT_METHODS(0x2B7B2340, PFBetweenSessionsData);

	PFBetweenSessionsData() {}
  ZDATA_(PFWorldObjectBase)
  int impulsePoints;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&impulsePoints); return 0; }

public:
  PFBetweenSessionsData( PFWorld* world ) : PFWorldObjectBase( world, 0 ), impulsePoints( 0 ) {}

  int  GetImpulsePoints( int gamesLimit = 0 ) { return    impulsePoints; } //gamesLimit is needed for interface propose (yet)
  void SetImpulsePoints( int points )         { impulsePoints  = points; }
  void AddImpulsePoints( int points )         { impulsePoints += points; }
};

class PFHeroBehaviour : public PFBaseBehaviour
{
  WORLD_OBJECT_METHODS( 0xE78C2C40, PFHeroBehaviour )

private:
  ZDATA_(PFBaseBehaviour)
  float screamCooldown;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseBehaviour*)this); f.Add(2,&screamCooldown); return 0; }

  PFHeroBehaviour( PFBaseMovingUnit* pUnit ) : PFBaseBehaviour( pUnit ), screamCooldown(0.0f) {}

  virtual void OnDamage( const PFBaseUnitDamageDesc& desc );
  virtual bool OnStep( float dtInSeconds );
  virtual void OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget );
private:
  explicit PFHeroBehaviour() {}
};

class PFHeroEventConsumableObtained : public PFBaseUnitEvent
{
public:
  PFHeroEventConsumableObtained( NDb::Consumable const* _pDBConsumable, NDb::EConsumableOrigin _origin)
    : PFBaseUnitEvent(NDb::BASEUNITEVENT_CONSUMABLEOBTAINED), pDBConsumable(_pDBConsumable), origin(_origin) {}

  NDb::Consumable const* GetDBConsumable() const { return pDBConsumable; }
  NDb::EConsumableOrigin GetOrigin() const { return origin; }
private:
  NDb::Consumable const* pDBConsumable;
  NDb::EConsumableOrigin origin;
};

class PFHeroEventWantMoveTo : public PFBaseUnitEvent
{
public:
  PFHeroEventWantMoveTo( const CVec2& _target)
    : PFBaseUnitEvent(NDb::BASEUNITEVENT_WANTMOVETO),  target(_target) {}

  const CVec2& GetDestination() const { return target; }
private:
  CVec2 target;
};

class PFBaseHero : public PFCreature, public IInventory
{
  NAMEMAP_DECLARE;
  WORLD_OBJECT_METHODS_WITH_CLIENT(0xE618C80, PFBaseHero, NGameX::PFBaseClientHero )
public:
  //static const int NUM_INVENTORY_SLOTS = 3;

  struct SpawnInfo
  {
    int                     playerId;
    int                     inTeamId;
    Placement               placement;
    NDb::Ptr<NDb::BaseHero> pHero;
    NDb::EFaction           faction;       // used only when playerId is invalid
    bool                    bInitTalents;
    bool                    bInitInventory;
		bool										isClone;
		bool										shouldPlaySummonEffect;
    NCore::PlayerInfo       playerInfo;
    bool                    usePlayerInfoTalentSet;
    NDb::EFaction           originalFaction;
	
    SpawnInfo() : playerId(-1), inTeamId(-1), faction(NDb::FACTION_NEUTRAL), bInitTalents(true), bInitInventory(true), isClone(false)
      , shouldPlaySummonEffect(true), usePlayerInfoTalentSet(false), originalFaction(NDb::FACTION_NEUTRAL) {}
  };

  PFBaseHero(PFWorld* pWorld, const SpawnInfo &info, NDb::EUnitType unitType, NDb::EFaction faction, NDb::EFaction _originalFaction);

  // damage/health/energy methods
  virtual float                   OnDamage(const DamageDesc &desc);
  void SetAdditionalDamageParam( float _takeModDmg, NDb::ESpellTarget _takeTypeUnit ) { takeModDmg = _takeModDmg; takeTypeUnit = _takeTypeUnit; }

  virtual bool  OnDispatchApply(PFDispatch const &dispatch);

  //logging session events
  void LogSessionEvent( SessionEventType::EventType eventType, const StatisticService::RPC::SessionEventInfo & params);
  void LogSessionEvent( SessionEventType::EventType eventType, const NDb::DbResource *  resource);
  void LogSessionEvent( SessionEventType::EventType eventType, int intParam1);

  PFBaseHero*             Clone( const CloneParams& params, float takeModDmg, NDb::ESpellTarget takeTypeUnit, const string& summonGroupName );
  void                    RemoveClone( int id );
  bool                    IsClone() const   { return isClone; }
  
  virtual bool            IsTrueHero() const { return IsHero() && !isClone; }

  virtual void            DoLevelups(int count, float statsBonusBudget = 0.0f);
  virtual float           GetUltimateCD() const;

  virtual bool            Step(float dtInSeconds);
  void                    CallForTowerHelp ( const CPtr<PFBaseUnit>& pTarget );
  virtual float           OnBeforeDamage(const DamageDesc &desc);
  virtual void            OnScream      (const CPtr<PFBaseUnit> pTarget, ScreamTarget::ScreamType st );
  virtual void            OnAddGold     (CPtr<PFBaseUnit> pSender, float amount, bool showGold = true);
  virtual float           OnHeal        (CPtr<PFBaseUnit> pSender, float amount, bool ignoreHealingMods = false);
  virtual void            OnAfterSuspend(bool isLongSuspend);
  virtual void            OnIdle();

  virtual void            RestoreClientObject() {}

  virtual void            OnMapLoaded() {}
  virtual void            DoPetLogic() {}

  void                           OnMountSpecial( CPtr<PFBaseMovingUnit> const& pMountUnit, bool controlMount );
  void                           OnUnmountSpecial();
  CPtr<PFBaseMovingUnit> const&  GetMount() const { return pMount; }
  bool                           ControlsMount() const { return IsMounted() && canControlMount; }
  bool                           CanControlMount() const { return canControlMount; }
  void                           DismountSpecial();
  CObj<PFHeroStatistics> const& GetHeroStatistics() const { return pStatistics; }
  CObj<PFHeroStatistics> &      GetHeroStatistics() { return pStatistics; }

  const PFBetweenSessionsData* GetProfile() const { return pProfile; }
  PFBetweenSessionsData*      GetProfile()       { return pProfile; }

  virtual bool IsRecommended( int stat ) const;

  void                    AttachToPlayer(CPtr<PFPlayer> const& pNewPlayer);
  void                    ClientAttachToPlayer();
  void                    DetachFromPlayer();
  bool                    UpdateClientColor();
	CPtr<PFPlayer> const&   GetPlayer() const { return pPlayer; }
  const wstring&          GetPlayerName() const;
  int                     GetStatisticsUid() const;
  bool                    IsLocal() const   { return IsValid( pPlayer ) ? pPlayer->IsLocal() : false; }

  virtual int             GetOriginalTeamId() const;

  virtual int             GetZZimaSex() const;

  virtual bool            IsMale() const;

  virtual int             GetTotalNaftaEarned() const;
  virtual int             GetNafta() const { return GetGold(); }

  virtual int             GetKillStreak() const;
  virtual int             GetDeathStreak() const;

  virtual int             GetTSliceSalary() const;
  virtual void            SetTSliceSalary(float salary);
  virtual void            AddTSliceSalary(float salary);

  virtual const wstring & GetDescription() const;
  virtual const NDb::Texture * GetUiAvatarImage() const;
  const NDb::Texture *    GetUiMinimapImage() const;

  virtual void            DropCooldowns( DropCooldownParams const& dropCooldownParams );

  virtual void            DropImpulsesCooldowns();

  void                    DoStop();

  //void                    AutoTargetOnIdle(float dtInSeconds);
  virtual void            OnTargetDropped();
  virtual void            OnStopped();
  virtual void            NotifyMoving( bool teleported );


	CVec3                   GetPetEscortPosition() const;

  // http://SITE - No more XP
  // experience methods
  // const int               GetExperience() const;
  // const int               GetLevelMaxExperience() const;
  const int &             GetLevelMaxExperienceRef() const; // for namemap
  // const float             GetLevelExperiencePercent() const;
  // void                    AddExperience(float value);

  // http://SITE - No more XP
  // dev. points methods
  const int               GetLevelMaxDevPoints() const;
  const int &             GetLevelMaxDevPointsRef() const;
  const float             GetLevelDevPointsPercent() const;

	void                    AddGold(float val, bool show = true) { OnAddGold(this, val, show); }
	float                   TakeGold(float val) { return OnRemoveGold(this, val); }

	void                    AwardForKill(CPtr<PFBaseUnit> const& pVictim, const float money, bool fromVictim = false );
  void                    OnKill( CPtr<PFBaseUnit> const& pVictim, bool lastHit );

  void                    DebugDie();

  //_interface IInventory
  virtual int GetSlotCount() const;
  virtual const PFConsumable * GetConsumable(int slot ) const;
  virtual bool CanAddItem( const NDb::Consumable * dbItem, int quantity ) const { return GetSlotForConsumable( dbItem, quantity ) >= 0; }
  virtual bool CanUseConsumables() const;


  // consumables methods
  bool                    IsSlotValid( int slot ) const;
  void                    DropConsumable( int slot, const CVec2& target);
  bool                    CanUseConsumable(int slot) const;
  CObj<PFAbilityInstance> UseConsumable( int slot, Target const& target, bool isLocal );
  CObj<PFAbilityInstance> UseConsumable( CObj<PFConsumable>& pConsumable, const Target& target, bool isLocal );
  bool                    TakeConsumable( const NDb::Consumable * pDBDesc, int quantity, NDb::EConsumableOrigin origin = (NDb::EConsumableOrigin)0, int slotIndex = -1 );
  void                    SwapConsumables(int id1, int id2); ///@todo temporary
  bool                    RemoveConsumable(int slot);
  void                    RemoveConsumable( PFConsumable const* pConsumable );
  float                   GetConsumableCost( const NDb::Consumable * pDBDesc ) const;

  int                     GetSlotForConsumable( const NDb::Consumable * pDBDesc, int quantity ) const;
  bool                    CanPutConsumableIntoSlot( const NDb::Consumable * pDBDesc, int quantity, int slot) const;
  bool                    CanTakeConsumable( const NDb::Consumable * pDBDesc, int quantity) const;
  void                    DropConsumablesCooldowns( DropCooldownParams const& dropCooldownParams );

  bool                    CanStackConsumables( int src, int dst ) const;
  bool                    StackConsumables( int src, int dst );

  void                    SellConsumable(int slot);

  CObj<PFConsumableAbilityData> GetConsumableAbility( const NDb::Ability * pDBDesc );
  void                    AddConsumableToGroup( PFConsumableAbilityData* pConsumableAD );
  void                    RestartGroupCooldowns( PFConsumableAbilityData const* pConsumableAD );
  //
  const CVec3&            GetSpawnPosition() const { return spawnPos;     }

  float                   GetRespawnDelay() const  { return respawnDelay; }
  float                   GetRedeemCost() const    { return redeemCost;   }

  virtual float           GetForce( bool = false ) const { return force; }
  void                    SetForce( float force_ ) { force = force_; }
  float                     GetRaiting() const { return raiting;}
  uint                     GetPartyId() const { return partyId; }
  virtual IMiscFormulaPars const* GetTalent(const char* id) const;
  virtual PFTalent*               GetTalent(int level, int slot) const { NI_ALWAYS_ASSERT("Invoke dummy method"); return 0; }
  virtual PFTalent*               GetTalentById(const char* id) const;
  virtual bool                    HasTalentFromPack( const char* id ) const;
  
  void AddTalentActivatedWhileDead( CPtr<PFTalent> pTalent );

  //original faction
  virtual NDb::EFaction  GetOriginalFaction() const { return originalFaction; }

  virtual void           OnGameFinished( const NDb::EFaction failedFaction );
  virtual void           SetHappy();

  const nstl::string&    GetSkinId() const { return heroSkinId; }
  void PrepareExcludedResourcesList( const NDb::EFaction& sourceFaction );

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class TF>
  void ForAllTalents(TF &talFunc) const
  {
    const int levels = NDb::KnownEnum<NDb::ETalentLevel>::SizeOf();
    const int slots  = NDb::KnownEnum<NDb::ETalentSlot>::SizeOf();

    for ( int i = 0; i < levels; i++ )
    {
      for ( int j = 0; j < slots; j++ )
      {
        PFTalent* currentTalent = GetTalent( i, j );
        if ( currentTalent )
        {
          talFunc( currentTalent, i, j );
        }
      }
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct CloneFunc
  {
    virtual void operator()( PFBaseHero* pClone ) = 0;
  };

  void                    ForAllClones( CloneFunc& cloneFunc );

  struct ResurrectParams
  {
    enum Place { Base, Death };
    ZDATA
    Place resurrectAt;
    float healthPercent;
    float energyPercent;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&resurrectAt); f.Add(3,&healthPercent); f.Add(4,&energyPercent); return 0; }

    explicit ResurrectParams(Place resurrectAt = Base, float healthPercent = 1.0f, float energyPercent = 1.0f)
      : resurrectAt(resurrectAt), healthPercent(healthPercent), energyPercent(energyPercent) {}
  };

  struct CloneInfo
  {
    ZDATA
    CObj<PFBaseHero> clone;
    int id;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&clone); f.Add(3,&id); return 0; }

    CloneInfo( PFBaseHero* _clone, int _id ) : clone( _clone ), id ( _id ) { }
    CloneInfo() : clone( NULL ), id ( 0 ) { }
  };

  void                    Resurrect(ResurrectParams const& params = ResurrectParams() );

  float                   GetTimeToRespawn() const;

  void                    AddDistanceRun(float dist) {distanceRun += dist;}
  float                   GetDistanceRun() const {return distanceRun;}

  void                    Emote(NDb::EEmotion emotion);

  // misc
  const NDb::BaseHero *   GetDbHero() const { return pDbHero; };
  bool                    IsIsolated() const { return isolated; }

  float                   GetTimeInDeath() const { return ripTime; }
  int                     GetInTeamId() const { return inTeamId; }
  const wstring&          GetTeamName() const;

  bool                    IsResurrecting() const { return IsDead() && advanceRespawnDelay < 0 && 0 < respawnDelay; }

  float                   GetModifiedAbilityValue( float value, NDb::EAbilityModMode mode, NDb::EAbilityTypeId abilityType, NDb::Ptr<NDb::Ability> const& dbAbility ) const;
  void                    AddAbilityModifier( PFApplAbilityMod* appl );
  void                    RemoveAbilityModifier( PFApplAbilityMod* appl );
  void                    RecacheAbilitiesModifiers();
  float                   AbilitiesModsGetActualizationTime() const { return abilityModsActualizationTime; }
  PFApplAbilityMod::Ring const& GetAbilitiesMods() const { return rgAbilitiesModifiers; }

  NDb::ERoute              GetNearestRoute(float* pDistance = NULL) const;

  void                    SetForbidRespawn(bool _forbidRespawn) { forbidRespawn = _forbidRespawn; }
  bool                    GetForbidRespawn() const { return forbidRespawn; }
  void                    SetRespawnPosition( const CVec3& pos ) { spawnPos = pos; }
  bool                    IsMuted() const { return isMuted; }

  bool                    SetSkin( const nstl::string& skinId, bool invalidateClientObject );
  virtual bool            SetSkin( const nstl::string& skinId ) {  return SetSkin(skinId, false);  }
  void                    SetAnimatedAvatar(bool animatedAvatar) { isAnimatedAvatar = animatedAvatar; }
  bool                    GetAnimatedAvatar() const { return isAnimatedAvatar; }
  void                    SetLeagueIndex(int _leagueIndex) { leagueIndex = _leagueIndex; }
  int                     GetLeagueIndex() const { return leagueIndex; }
  void                    SetOwnLeaguePlace(int _ownLeaguePlace) { ownLeaguePlace = _ownLeaguePlace; }
  int                     GetOwnLeaguePlace() const { return ownLeaguePlace; }

  const nstl::vector<int>& GetLeaguePlaces() const { return leaguePlaces; }

  const NDb::HeroSkin*    GetHeroSkin() const { return pCurrentHeroSkin; }
  const NDb::DbResource*  GetSkin() const { return pCurrentHeroSkin; }
  static const NDb::HeroSkin*  GetHeroSkin(const NDb::Hero* dbHeroPtr, const string& skinId);  
  static const NDb::Texture *  GetUiAvatarImage(const NDb::Hero* dbHeroPtr, NDb::EFaction faction, const string& skinId);
  const NDb::AskSounds*   GetHeroAsks(EHeroState::Enum forHeroState) const;
  void                    PlayAskSound( int id, NWorld::PFBaseHero const * pTarget = 0, int announcePriority = -1 ) const;
  virtual const NDb::UnitDeathParameters* GetDeathParams() const;

  string                  GetFlagId() const {return flagId;}

  const nstl::list<const NDb::DbResource*>& GetExcludedResourcesList() const { return excludedResources; }

  //script-controlled progress bar 
  float                   GetScriptControlledProgressValue() const { return scriptControlledProgressValue; }
  bool                    HasScriptControlledProgressValue() const { return scriptControlledProgressValue > 0.0f; }
  void                    SetScriptControlledProgressValue( float _value ){scriptControlledProgressValue = _value;}


  seDECLARE_COBJRING(PFBaseHero, factionRingPart, FactionRing);

  NDb::EGender            GetDbGender() const;
  NCore::ESex::Enum       PlayerGenderFromDbGender();

  void OnScrollReceived();
  void                    OnGlyphPickUp( const PFGlyph* pGlyph );

  virtual float GetHeroStatisticsValue( HeroStatisticsId heroStatId ) const;
  virtual int GetHeroAchievementCount( const char* achievId ) const;
  virtual bool IsSkinUsed(const char * skinId) const { return GetSkinId() == skinId; }

  bool CanMove() const;
  void Move(const CVec2 & target);

  bool HasCustomEnergy() const { return customEnergy; }

  float GetCustomEnergyValue() const;
  float GetCustomEnergyMaximum() const;
  float GetCustomEnergyRegeneration() const;

  EHeroState::Enum GetHeroState() const { return heroState; }
  void SetHeroState(EHeroState::Enum newHeroState) { heroState = newHeroState; }

private:
  //note that this is not under zdata. its only for logging purpose not for logic needs
  float timeSinceLastSlice;
  int slicesCount;
  void LoggTimeSliceIfNeeded(float deltaTime);

  NDb::Ptr< NDb::HeroSkin >   pCurrentHeroSkin;
  nstl::list<const NDb::DbResource*> excludedResources;
  bool            isMuted;
  string flagId;

protected:

  explicit PFBaseHero() {}

  virtual void            Initialize(InitData const& data);
  virtual void            InitHero(NDb::BaseHero const* pDesc);
  virtual void            OnDestroyContents();
  virtual void            Reset();

  int                     CountLevelups();
  virtual void                OnLevelUp();

  // Death stuffs
  STARFORCE_EXPORT virtual void OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags, PFBaseUnitDamageDesc const* pDamageDesc = 0);
  virtual void            OnDie();
  virtual void            RemoveCorpse();

  void                    StartRespawnTimer();
  void                    AdvanceResurrect();
  void                    DoResurrect();
  void                    RecalculateRedeemCost();

  void                    AddConsumableCooldown( CObj<PFConsumable> const& pConsumable );

  typedef vector<CObj<PFConsumable>> Consumables;

  ZDATA_(PFCreature)
  ZNOPARENT(IInventory)
	vector< CPtr<PFTalent> > activatedWhileLastDeathtime;
  Consumables     consumables;
  float           respawnDelay;
  float           advanceRespawnDelay;
  bool            forbidRespawn;
  ResurrectParams resurrectParams;
  float           redeemCost;
  float           redeemCostRecalculateDelay;

  // http://SITE - No more XP
  float           experience; // 0.0f — for namemap

  CVec3           spawnPos;
  CPtr<PFPlayer>  pPlayer;
  bool            isClone;
  float           giveWorldGoldOffset;
  float           distanceRun;
  NDb::Ptr< NDb::BaseHero >   pDbHero;    //this field in ZDATA ONLY to simplify asynchrony analysis
  bool            isolated;
  float           ripTime;
  int             inTeamId;
  vector< CObj<PFConsumableAbilityData> > rgConsumablesAbilities;

  vector<CloneInfo> clones;
  int cloneCounter;

  PFApplAbilityMod::Ring  rgAbilitiesModifiers;
  float                   abilityModsActualizationTime;

  CPtr<PFBaseMovingUnit>  pMount;
  CObj<PFHeroStatistics> pStatistics;

  CObj<PFBetweenSessionsData> pProfile;

  CVec3           fountainPos;
  bool            canControlMount;
  float           force;
  float             raiting;
  

  NDb::EFaction   originalFaction; // used for hero clones

  float takeModDmg;
  NDb::ESpellTarget takeTypeUnit;
  nstl::string heroSkinId;
  NCore::ESex::Enum playerGender;
  float scriptControlledProgressValue;
  uint partyId;
  EHeroState::Enum heroState;
  bool isAnimatedAvatar;
  int  leagueIndex;
  int ownLeaguePlace;
  vector<int> leaguePlaces;

  ZONSERIALIZE
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFCreature*)this); f.Add(2,&activatedWhileLastDeathtime); f.Add(3,&consumables); f.Add(4,&respawnDelay); f.Add(5,&advanceRespawnDelay); f.Add(6,&forbidRespawn); f.Add(7,&resurrectParams); f.Add(8,&redeemCost); f.Add(9,&redeemCostRecalculateDelay); f.Add(10,&experience); f.Add(11,&spawnPos); f.Add(12,&pPlayer); f.Add(13,&isClone); f.Add(14,&giveWorldGoldOffset); f.Add(15,&distanceRun); f.Add(16,&pDbHero); f.Add(17,&isolated); f.Add(18,&ripTime); f.Add(19,&inTeamId); f.Add(20,&rgConsumablesAbilities); f.Add(21,&clones); f.Add(22,&cloneCounter); f.Add(23,&rgAbilitiesModifiers); f.Add(24,&abilityModsActualizationTime); f.Add(25,&pMount); f.Add(26,&pStatistics); f.Add(27,&pProfile); f.Add(28,&fountainPos); f.Add(29,&canControlMount); f.Add(30,&force); f.Add(31,&raiting); f.Add(32,&originalFaction); f.Add(33,&takeModDmg); f.Add(34,&takeTypeUnit); f.Add(35,&heroSkinId); f.Add(36,&playerGender); f.Add(37,&scriptControlledProgressValue); f.Add(38,&partyId); f.Add(39,&heroState); f.Add(40,&isAnimatedAvatar); f.Add(41,&leagueIndex); f.Add(42,&ownLeaguePlace); f.Add(43,&leaguePlaces); OnSerialize( f ); return 0; }
  
private:
  void OnSerialize(IBinSaver& f);

  void InitializeCustomEnergyVariables();

  bool customEnergy;

  ValueWithModifiers* customEnergyValue;
  ValueWithModifiers* customEnergyMaximum;
  ValueWithModifiers* customEnergyRegeneration;

  friend void MakeTrueAsyncForTest( PFBaseHero *pHero );
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseHero* CreateHero(PFWorld* pWorld, NWorld::PFBaseHero::SpawnInfo const& info);

} // namespace NWorld
