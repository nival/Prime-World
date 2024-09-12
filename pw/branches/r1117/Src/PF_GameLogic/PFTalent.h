#pragma once

#include "PFAbilityData.h"

#include "DBTalent.h"

namespace NWorld
{

class PFBaseMaleHero;
class PFResourcesCollection;
struct ITalentCalculator;

//////////////////////////////////////////////////////////////////////////
class PFTalentActivationCondition : public CObjectBase
{
public:
  virtual bool IsReady(PFBaseMaleHero* pHero)const = 0;
};

namespace ETalentActivation
{
  enum Enum
  {
    Ok,
    Denied,
    NoMoney,
  };
}

struct TalentKit
{
  TalentKit() : activatedTalents(0) {}

  NDb::TalentKit const* dbDesc;
  int activatedTalents;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFTalent : public PFAbilityData
{
  WORLD_OBJECT_METHODS(0xF690BC0, PFTalent);

  NAMEMAP_DECLARE;

public:
  PFTalent( CPtr<PFBaseMaleHero> const& pOwner, NDb::Ptr<NDb::Talent> const& pDBTalentDesc, int refineRate, int aIPriority, int _actionBarIndex, bool _isInstaCast );

  const bool &IsActivated() const { return bActivated; }
  bool CanBeActivated() const;
  bool Activate();
  virtual void RestartCooldown( float cooldownTime_ );

  int GetMoneyCost() const;
  int const &GetDevPoints() const {return pDBTalentDesc->devPoints; }
  int const &GetMinLevel() const { return pDBTalentDesc->minLevel; }
  const bool IsUltimate() const { return pDBTalentDesc->isUltimateTalent; }
  wstring const &GetRarityName() const;
  virtual int GetTalentRarity() const { return pDBTalentDesc->rarity; }
  const bool IsClass()       const { return pDBTalentDesc->rarity == NDb::TALENTRARITY_CLASS; }
  const bool IsOrdinary()    const { return pDBTalentDesc->rarity == NDb::TALENTRARITY_ORDINARY; }
  const bool IsGood()        const { return pDBTalentDesc->rarity == NDb::TALENTRARITY_GOOD; }
  const bool IsExcellent()   const { return pDBTalentDesc->rarity == NDb::TALENTRARITY_EXCELLENT; }
  const bool IsMagnificent() const { return pDBTalentDesc->rarity == NDb::TALENTRARITY_MAGNIFICENT; }
  const bool IsExclusive()   const { return pDBTalentDesc->rarity == NDb::TALENTRARITY_EXCLUSIVE; }
  const bool ConsumptionBonusPercent() const { return false; }  // fake to fix http://SITE
  wstring const &GetKitName() const;
  const bool IsInKit()       const { return pTalentKit != 0; }
  const bool IsInPack()      const { return pTalentPack != 0;}
  const bool IsSpecialInKit() const;
  const string& GetPackIconStyle() const;

  int GetAIPriority() const { return aIPriority; }

  // for formulas
  int   GetTalentLevel()     const { return GetMinLevel();  } 
  int   GetTalentDevPoints() const { return GetDevPoints(); }
  int   GetRefineRate()      const { return refineRate; }
  void  SetRefineRate(int refineRate_)     { refineRate = refineRate_; }
  int   GetNaftaCost()       const { return GetMoneyCost(); }
  bool  IsTalentBought()     const { return IsActivated(); }
  bool  IsGenderTalent()     const { return pDBTalentDesc->isGenderTalent; }
  int   GetVendorCost() const;
  virtual int GetActivatedWithinKit() const;
  virtual int GetTalentsWithinKit() const;

  int GetActionBarIndex() const {return actionBarIndex;}

  NDb::Ptr<NDb::Talent> const& GetTalentDesc() const { return pDBTalentDesc; }

  NDb::TalentGroup const* GetGroup() const { return pDBGroup; }
  void SetGroup( NDb::TalentGroup const* pDBGroup_ ) { pDBGroup = pDBGroup_; }
  bool IsInGroup() const { return pDBGroup != 0; }
  wstring const& GetGroupName() const;
  wstring const& GetGroupDescription() const;

  void SetKit( NDb::TalentKit const* pTalentKit_ ) { pTalentKit = pTalentKit_; }
  void SetPack( NDb::TalentPack const* pTalentPack_ ) { pTalentPack = pTalentPack_; }
  NDb::TalentPack const* GetPack() const { return pTalentPack; }

  void SetLastUseStep(int _lastUseStep) { lastUseStep = _lastUseStep; }
  int  GetLastUseStep() const { return lastUseStep; }

  int  GetLastActivatedStep() const { return lastActivatedStep; }
  virtual void NotifyCastProcessed();
  

  static float CalcBudget(const NDb::AILogicParameters* pAIParams, int refineRate, int level, int rarity);

  virtual void Reset();

  virtual void PlayAck( const PFBaseHero* pAuxAckRecipient ) const;

private:
  PFTalent() : bActivated(false), pDBGroup(0) {} // CObj/CPtr and serialization support
  
  ZDATA_(PFAbilityData);
  NDb::Ptr<NDb::Talent> pDBTalentDesc;
  CPtr<PFBaseMaleHero> pOwner;
private:
  int aIPriority;
  int   refineRate;
  bool  bActivated;
  int   actionBarIndex;
  int   lastUseStep;
  int   lastActivatedStep;
public:
  bool  isInstaCast;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFAbilityData*)this); f.Add(2,&pDBTalentDesc); f.Add(3,&pOwner); f.Add(4,&aIPriority); f.Add(5,&refineRate); f.Add(6,&bActivated); f.Add(7,&actionBarIndex); f.Add(8,&lastUseStep); f.Add(9,&lastActivatedStep); f.Add(10,&isInstaCast); return 0; }
private:
  const NDb::TalentGroup* pDBGroup;
  NDb::Ptr<NDb::TalentKit> pTalentKit;
  NDb::Ptr<NDb::TalentPack> pTalentPack;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PFTalentsSet : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS(0xF691B80, PFTalentsSet);

public:
  
	PFTalentsSet( PFWorld* world );

	virtual bool NeedToBeStepped() { return false; }

  struct SlotInfo
  {
    ZDATA;
    NDb::ETalentSlotStatus status;
    NDb::Ptr<NDb::Talent> pTalentDesc;
    int refineRate;
    int aIPriority;
    int actionBarIndex;
    bool isInstaCast;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&status); f.Add(3,&pTalentDesc); f.Add(4,&refineRate); f.Add(5,&aIPriority); f.Add(6,&actionBarIndex); f.Add(7,&isInstaCast); return 0; }
    
    SlotInfo( NDb::ETalentSlotStatus status = NDb::TALENTSLOTSTATUS_NORMAL, NDb::Ptr<NDb::Talent> const& pTalentDesc = 0, int refineRate = 0, int aIPriority = 0 );
  };
  
  enum { 
    LEVELS_COUNT = NDb::KnownEnum<NDb::ETalentLevel>::sizeOf,
    SLOTS_COUNT = NDb::KnownEnum<NDb::ETalentSlot>::sizeOf,
  };

  typedef StaticArray<SlotInfo,   SLOTS_COUNT> LevelInfo;
  typedef StaticArray<LevelInfo,  LEVELS_COUNT> SetInfo;
  
  // ~~~~~~
  
  void CleanSet();
  
  void  LoadSet( CPtr<PFBaseMaleHero> const& pOwner, SetInfo const& setInfo );
  void  Update(float dt);
  virtual void Reset();

  int GetTalentAIPriority( int level, int slot ) const;
  CObj<PFTalent> const& GetTalent(int level, int slot) const;

  ETalentActivation::Enum CanActivateTalent( int level, int slot ) const;
  bool HasFreshTalentsToBuy() const;
  bool ActivateTalent(int level, int slot);
  void ActivateTakenOnStart();
  vector<PFTalent*> const& GetTalentsFromGroup( NDb::TalentGroup const* group ) { return talentGroups[group]; }

  void IncActivatedWithinKit( NDb::TalentKit const* kit ) { talentKits[kit]++; }
  int GetActivatedWithinKit( NDb::TalentKit const* kit ) { return talentKits[kit]; }
  
  int   GetLevelOfDevelopment() const { return devPoints / NDb::TALENTS_POINTS_PER_LEVEL; }
  int   GetLevelOfDevelopmentCapped() const { return Min( LEVELS_COUNT - 1, GetLevelOfDevelopment() ); }
  int const &GetDevPoints() const { return devPoints; }
  float GetAcquiredBudgetPercent() const { return acquiredBudgetPercent; }

  void CalculateForce(ITalentCalculator& calculator);

  static float PFTalentsSet::PreloadTalentsSetAndCalcForce(const NDb::AILogicParameters* pAIParams, const NDb::BaseHero* pDBHero, 
                                                            bool usePlayerInfoTalentSet, const NWorld::PFResourcesCollection* collection,
                                                            const NCore::PlayerInfo& playerInfo, PFTalentsSet::SetInfo& info);
  

  //////////////////////////////////////////////////////////////////////////
  // *** Temporary stuff! For debug only! Do not use! *** //
  void  LoadPredefinedSet(CPtr<PFBaseMaleHero> const& pOwner, string const& forceSetName, ITalentCalculator& calculator);

private:
  static void PrepareCustomSet(const NCore::PlayerTalentSet* talentSet, const NWorld::PFResourcesCollection* collection, ITalentCalculator& calculator, SetInfo& info);
  //////////////////////////////////////////////////////////////////////////
  // *** Temporary stuff! For debug only! Do not use! *** //
  static void PreparePredefinedSet(const NDb::AILogicParameters* pAIParams, const NDb::BaseHero* pDBHero, string const& forceSetName, 
                            ITalentCalculator& calculator, SetInfo& info);

	PFTalentsSet( );

  typedef map<NDb::TalentGroup const*, vector<PFTalent*>> TalentGroups;
  typedef map<NDb::TalentKit const*, int> ActivatedInTalentKits;

  void CreateGroups();
  void CreateKits();
  void CreatePacks();

  typedef StaticArray<CObj<PFTalent>, SLOTS_COUNT> TalentsLevel;
  typedef StaticArray<TalentsLevel,   LEVELS_COUNT> TalentsSet;
  
  ZDATA_(PFWorldObjectBase)
  CPtr<PFBaseMaleHero>  pOwner;
  int                   devPoints;
  TalentsSet            talents;
  float                 acquiredBudgetPercent;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pOwner); f.Add(3,&devPoints); f.Add(4,&talents); f.Add(5,&acquiredBudgetPercent); return 0; }

private:
  vector<pair<int,int>> talentsToActivate;
  TalentGroups talentGroups;
  ActivatedInTalentKits talentKits;
};

//////////////////////////////////////////////////////////////////////////
_interface ITalentCalculator
{
  virtual void operator()( NDb::Ptr<NDb::Talent> const& pDBTalent, int level, const PFTalentsSet::SlotInfo& slot ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline PFTalentsSet::SlotInfo::SlotInfo( NDb::ETalentSlotStatus _status/* = NDb::TALENTSLOTSTATUS_NORMAL*/, NDb::Ptr<NDb::Talent> const& _pTalentDesc/* = 0*/, int _refineRate/* = 0*/, int _aIPriority/* = 0*/ )
  : status( _status )
  , pTalentDesc( _pTalentDesc )
  , refineRate( _refineRate )
  , aIPriority( _aIPriority )
{
}

} //namespace NWorld
