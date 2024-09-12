#include "PFAbilityData.h"
#include "PFAbilityInstance.h"

#include "PFUniTarget.h"
#include "PFDispatch.h"


namespace NWorld
{

class PFBaseAttackData;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFBaseAttackInstance
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseAttackInstance : public PFAbilityInstance
{
  WORLD_OBJECT_METHODS(0xF671B80, PFBaseAttackInstance);

public:
  PFBaseAttackInstance( CObj<PFBaseAttackData> const& pAbilityData, Target const& target, bool _allowAllies = false );

  void                        Cancel();

  virtual bool                Update(float dt);
  void                        ApplyAttack();
  void                        DoAttack();
  bool                        IsAttackFinished() const { return isAttackFinished; }
  bool                        IsReadyToDie() const;

private:
  PFBaseAttackInstance() {} // ~~~ HACK : for CPtr/CObj support only! ~~~
  
  ZDATA_(PFAbilityInstance);
  PFDispatchHolder            dispatch;
  float                       attackDelay;
  float                       rawAttackDelay;
  bool                        isAttackFinished;
  bool                        allowAllies;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFAbilityInstance*)this); f.Add(2,&dispatch); f.Add(3,&attackDelay); f.Add(4,&rawAttackDelay); f.Add(5,&isAttackFinished); f.Add(6,&allowAllies); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFBaseAttackData
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseAttackData : public PFAbilityData
{
  WORLD_OBJECT_METHODS(0xF670C40, PFBaseAttackData)

public:
  PFBaseAttackData(CPtr<PFBaseUnit> const& pOwner, NDb::Ptr<NDb::BaseAttack> const& pDBDesc);
  ~PFBaseAttackData() {}

  virtual void                Update(float dt, bool fullUpdate);

  bool                        DoAttack( Target const& target, bool allowAllies = false );
  void                        Cancel();

  virtual float               GetWorkTime() const;
  virtual float               GetSpeed() const;
  NDb::EApplicatorDamageType  GetDamageType() const;

  bool                        CanHitFlying() const { return (GetDBDesc()->targetType & NDb::SPELLTARGET_FLYING) != 0; }
  virtual bool                IsMelee() const;

  typedef vector<CObj<PFBaseAttackInstance>> AttackInstances;

  const AttackInstances& GetAttackInstances() const { return rgAttackInstances; }
private:
  PFBaseAttackData();

	float GetAttackNodeDuration( NScene::SceneObject* pSO ) const;

  CObj<PFAbilityInstance>     ApplyToTarget(Target const& target);
  
  bool processInstances;
  bool delayedCancel;

  ZDATA_(PFAbilityData);
  NDb::EApplicatorDamageType  damageType;
  AttackInstances             rgAttackInstances;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFAbilityData*)this); f.Add(2,&damageType); f.Add(3,&rgAttackInstances); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline NDb::EApplicatorDamageType PFBaseAttackData::GetDamageType() const
{
  return damageType;
}
inline CObj<PFAbilityInstance> PFBaseAttackData::ApplyToTarget(Target const& target)
{
  NI_ALWAYS_ASSERT("Use DoAttack instead ApplyToTarget!");
  return NULL;
}

} //namespace NWorld
