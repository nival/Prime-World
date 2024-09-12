#pragma once

#include "PFUniTarget.h"
#include "PFWorldObjectBase.h"

namespace NWorld
{

enum ELookKind;

class PFAbilityData;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFAbilityInstance : public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS(0xF670B00, PFAbilityInstance);

public:
  PFAbilityInstance( const CObj<PFAbilityData>& _pAbilityData, const Target& _target, bool _passive );
  virtual void OnDestroyContents();
	virtual bool NeedToBeStepped() { return false; }

  void                  ApplyPassive( bool permanentStatModsOnly = false );   // apply on self (passive part only)
  bool                  ApplyToTarget();  // apply on target (active part only)

  virtual bool          Update(float dt);
  void                  Remove();
  void                  Cancel();
  void                  Interrupt();
  
  bool                  IsOn() const;
  bool                  IsActivated() const; // check if dispatched
  bool                  IsCastDone() const;      // check if workTimeDone
  bool                  IsFinished() const;
  bool                  IsCastFinished() const;
  ELookKind             IsCasterShouldLookAtTarget() const;
  int                   GetActiveApplicatorsCount() const;

  void                  NotifyApplicatorStarted(PFBaseUnit * target);
  void                  NotifyApplicatorStopped(PFBaseUnit * target);
  void                  NotifyAbilityEnd();
  void                  RemoveApplicatorsFrom(CPtr<PFBaseUnit> const& pUnit) const;

  void                  NotifyChannelingCreateStop(bool fire);

  void                  LogAbilityUsed() const;
  
  PFAbilityData const*  GetData() const;
  PFAbilityData*        GetData();
  CPtr<PFBaseUnit>      GetOwner() const;
  int                   GetRank() const;
	const AbilityTarget&  GetTarget() const { return target; }
  float                 GetScale() const;
  const CVec2&          GetCastPosition() const { return castPosition; }
  const CVec2&          GetCastMasterPosition() const { return castMasterPosition; }

  bool                  GetWarFogOpened(NDb::EFaction faction) const;
  void                  SetWarFogOpened(NDb::EFaction faction, bool opened = true);

  unsigned int          GetFlags() const;
  
protected:
  PFAbilityInstance() {} // ~~~ HACK : for CPtr/CObj support only! ~~~

  class PFDispatchHolder
  {
  public:
    ~PFDispatchHolder();
    void Attach(CPtr<PFDispatch> const& pDispatch_);
    void Start();
    void Cancel();
    CPtr<PFDispatch> const& Get() const;
  private:
    ZDATA;
    CPtr<PFDispatch> pDispatch;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&pDispatch); return 0; }
  };
private:
  //////////////////////////////////////////////////////////////////////////
  // Temporary hack for PFBaseAttackInstance
  friend class PFBaseAttackInstance;
  //////////////////////////////////////////////////////////////////////////
  
  void Activate();

  ZDATA_(PFWorldObjectBase)
  CObj<PFAbilityData> pAbilityData;
  CPtr<PFBaseUnit>    pOwner;
  PFDispatchHolder    dispatch;
  int                 activeApplicatorsCount;
  bool                abilityApplicatorsFinished;
  AbilityTarget       target;
  bool                passive;
  int                 rank;
  float               activateDelay;
  float               clientActivateDelay;
  float               castTime;
  vector<bool>        warfogOpened;
  CVec2               castPosition;
  CVec2               castMasterPosition;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pAbilityData); f.Add(3,&pOwner); f.Add(4,&dispatch); f.Add(5,&activeApplicatorsCount); f.Add(6,&abilityApplicatorsFinished); f.Add(7,&target); f.Add(8,&passive); f.Add(9,&rank); f.Add(10,&activateDelay); f.Add(11,&clientActivateDelay); f.Add(12,&castTime); f.Add(13,&warfogOpened); f.Add(14,&castPosition); f.Add(15,&castMasterPosition); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline int PFAbilityInstance::GetActiveApplicatorsCount() const
{
  return activeApplicatorsCount;
}

inline PFAbilityData const* PFAbilityInstance::GetData() const
{
  return pAbilityData;
}

inline PFAbilityData* PFAbilityInstance::GetData()
{
  return pAbilityData;
}

inline int PFAbilityInstance::GetRank() const
{
  return rank;
}

inline CPtr<PFBaseUnit> PFAbilityInstance::GetOwner() const
{
  return pOwner;
}

inline bool PFAbilityInstance::IsActivated() const
{
  return activateDelay < 0.0f;
}

inline bool PFAbilityInstance::IsCastDone() const
{
  return castTime < EPS_VALUE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline PFAbilityInstance::PFDispatchHolder::~PFDispatchHolder()
{
  Cancel();
}
inline void PFAbilityInstance::PFDispatchHolder::Attach(CPtr<PFDispatch> const& pDispatch_)
{
  Cancel();
  pDispatch = pDispatch_;
}
inline CPtr<PFDispatch> const& PFAbilityInstance::PFDispatchHolder::Get() const
{
  return pDispatch;
}

} //namespace NWorld
