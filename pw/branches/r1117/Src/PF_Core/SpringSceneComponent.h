#pragma once
#include "../Scene/SceneComponent.h"
#include "../Scene/Scene.h"
#include "DBEffect.h"

namespace PF_Core
{

template<typename VALUE>
class TargetedValue : public NonCopyable
{
public:
  TargetedValue(NDb::SpringParamDynamics const &d) : dynamics(d) {}
  
  void Init(VALUE const &val);
  bool Update(VALUE target, float dt);
  
  VALUE GetValue() const { return val; }
  float Distance(VALUE v1, VALUE v2);

protected:
  void StepPhysics(VALUE target, float dt);

  NDb::SpringParamDynamics dynamics;
  VALUE val;
};

// particular template specialization
template<> float TargetedValue<CQuat>::Distance(CQuat v1, CQuat v2);
template<> bool  TargetedValue<CQuat>::Update(CQuat target, float dt);

class TargetedPlacement
{
public:
  TargetedPlacement(NDb::SpringParamDynamics const &_pos, NDb::SpringParamDynamics const &_rot, NDb::SpringParamDynamics const &_scale)
    : pos(_pos)
    , rot(_rot)
    , scale(_scale)
  { }

  void Init(Placement const &val)
  {
    pos.Init(val.pos);
    rot.Init(val.rot);
    scale.Init(val.scale);
  }

  bool Update(Placement &val, Placement const &target, float dt)
  {
    bool bReached = true;
    bReached &= pos.Update(target.pos, dt);
    bReached &= rot.Update(target.rot, dt);
    bReached &= scale.Update(target.scale, dt);
    val = Placement(pos.GetValue(), rot.GetValue(), scale.GetValue());
    return bReached;
  }

protected:
  TargetedValue<CVec3> pos;
  TargetedValue<CQuat> rot;
  TargetedValue<CVec3> scale;
};



class SpringSceneComponent : public NScene::SceneComponent
{
protected:
	SpringSceneComponent() {}

public:
	SpringSceneComponent( const NDb::SpringSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos );

  virtual void Reinit();
  virtual bool IsStayInWorld();
  virtual void Update( UpdatePars &pars, const Placement& parentPos, float timeDiff );

protected:
  ScopedPtr<TargetedPlacement> tplace;
  bool  bTPlaceInited;
};


////////////////////////////////////////////////////////////////////////////////////////////////
// template implementation
////////////////////////////////////////////////////////////////////////////////////////////////

template<typename VALUE>
void TargetedValue<VALUE>::Init(VALUE const &_val)
{
  val = _val;
}

template<typename VALUE>
float TargetedValue<VALUE>::Distance(VALUE v1, VALUE v2)
{
  return fabs(v2 - v1);
}

template<typename VALUE>
bool TargetedValue<VALUE>::Update(VALUE target, float dt)
{
  float minCoef = 0.f;

  float d = Distance(val, target);
  if (d > 1e-5f)
  {
    minCoef = 1.f - dynamics.maxValue / d;
  }

  float coef = dynamics.speed * dt;
  coef = Clamp(coef, 0.f, 1.f);
  val.Lerp(Max(coef, minCoef), val, target);
  return false;
}

}
