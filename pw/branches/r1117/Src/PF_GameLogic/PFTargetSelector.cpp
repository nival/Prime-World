#include "stdafx.h"
#include "PFTargetSelector.h"
#include "PFAIWorld.h"
#include "PFBaseUnit.h"
#include "PFSummoned.h"
#include "PFMaleHero.h"
#include "PFMainBuilding.h"
#include "PFAbilityInstance.h"
#include "PFAbilityData.h"
#include "TileMap.h"
#include "PFAIContainer.h"
#include "TargetSelectorFormulaPars.h"
#include "PFApplInstant.h"
#include "TargetSelectorHelper.hpp"

namespace
{
  static int g_show_ts_ranges = 0;
}

namespace
{
  // @angle в градусах!
  inline void RotateVector(CVec2& v, const float angle)
  {
    struct Local
    {
      static inline float DegToRadAndWrap(const float angle)
      {
        const float a = (angle / 360.f);

        float r = (a - floor(a));

        if (r < 0.f)
          r += 1.f;

        return (r * FP_2PI);
      }
    };

    const float alpha = Local::DegToRadAndWrap(angle);

    if (alpha < FLT_EPSILON)
      return;

    const float s = sin(alpha);
    const float c = cos(alpha);

    const float x = v.x * c - v.y * s;
    const float y = v.y * c + v.x * s;

    v.x = x;
    v.y = y;
  }
}

namespace NWorld
{

namespace
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct WrapperFunctor : public NonCopyable
{
  explicit WrapperFunctor(DumpTargetWrapper action_, const PFTargetSelector::RequestParams& request)
    : action(action_)
    , request(request)
  {
  }

  void operator()(PFLogicObject &unit)
  {
    const Target targ(&unit);
    if (CheckTargetCondition(targ, request))
      action(targ);
  }

  DumpTargetWrapper action;

  const PFTargetSelector::RequestParams& request;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float SqrDist2Segment(const CVec2 &p, const CVec2 &b, const CVec2 &e, const CVec2 &dir, float length, bool beginCutoffCheck)
{
  CVec2 d = p - b;
	float proj = d.Dot(dir);
	if (proj <= 0.0f)
	{
    if ( beginCutoffCheck )
      return -1.0f;

		return fabs2(d);
	} else if (proj >= length)
	{
		return fabs2(p - e);
	} else
	{
		float range = Cross(d, dir);
		return range * range;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct RangeSelectorFunctor : public NonCopyable
{
	DumpTargetWrapper action;
	CVec2         pos;
  float         range;

  const PFTargetSelector::RequestParams& request;

  RangeSelectorFunctor(DumpTargetWrapper action_, CVec2 pos_, float range_, const PFTargetSelector::RequestParams& request)
    : action(action_)
    , pos(pos_)
    , range(range_)
    , request(request)
  {
  }

  void operator()( PFLogicObject& unit )
  {
    if ( unit.IsInRange( pos, range ) )
    {
      const Target targ( &unit );
      if (CheckTargetCondition(targ, request))
        action( targ );
    }
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct NormalTargetSelector : public ITargetAction, public NonCopyable
{
	ITargetAction &action;
	const Target  *pOriginalTarget;
  bool deadAllowed;

	NormalTargetSelector(ITargetAction &action_, const Target *pTarget, const bool deadAllowed_ )
		: action(action_), pOriginalTarget(pTarget), deadAllowed(deadAllowed_)
	{}

	bool CheckTarget(const Target &target)
	{
		return target.IsValid(deadAllowed) && !(pOriginalTarget && target == *pOriginalTarget);
	}

	virtual void operator()(const Target &target)
	{
		if (CheckTarget(target))
			action(target);
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct VectoredSelector : public NormalTargetSelector
{
	vector<Target> &targets;

	VectoredSelector(ITargetAction &action_, vector<Target> &targets_, const Target *pTarget, const bool deadAllowed_ )
		: NormalTargetSelector(action_, pTarget, deadAllowed_), targets(targets_) {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CaptureTargetsSelector : public VectoredSelector
{
	CaptureTargetsSelector(ITargetAction &action_, vector<Target> &targets_, const Target *pTarget, const bool deadAllowed_)
		: VectoredSelector(action_, targets_, pTarget, deadAllowed_) {}
	virtual void operator()(const Target &target)
	{
		if (!CheckTarget(target))
			return;

		action(target);
		targets.push_back(target);
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SendOnceSelector : public VectoredSelector
{
	SendOnceSelector(ITargetAction &action_, vector<Target> &targets_, const Target *pTarget, const bool deadAllowed_)
    : VectoredSelector(action_, targets_, pTarget, deadAllowed_) {}
	virtual void operator()(const Target &target)
	{
		if ( !CheckTarget(target) || find(targets.begin(), targets.end(), target) != targets.end() )
			return;

		action(target);
		targets.push_back(target);
	}
};

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
  inline const ITargetCondition* GetDefaultTargetCondition()
  {
    static const CheckValidAbilityTargetCondition condition;

    return &condition;
  }
  
}

PFTargetSelector::RequestParams::RequestParams(const PFBaseApplicator &appl_, const Target &requester_)
  : pMiscPars(&appl_)
  , pOwner(appl_.GetAbilityOwner())
  , pRequester(&requester_)
  , pAbility(appl_.GetAbility())
  , pReceiver(appl_.GetReceiver())
  , condition(GetDefaultTargetCondition())
{
}

PFTargetSelector::RequestParams::RequestParams(const PFBaseApplicator &appl_, const Target &requester_, const ITargetCondition& cond)
  : pMiscPars(&appl_)
  , pOwner(appl_.GetAbilityOwner())
  , pRequester(&requester_)
  , pAbility(appl_.GetAbility())
  , pReceiver(appl_.GetReceiver())
  , condition(&cond)
{
}

PFTargetSelector::RequestParams::RequestParams(const PFBaseApplicator &appl_, const Target &requester_, const ITargetCondition* const cond)
  : pMiscPars(&appl_)
  , pOwner(appl_.GetAbilityOwner())
  , pRequester(&requester_)
  , pAbility(appl_.GetAbility())
  , pReceiver(appl_.GetReceiver())
  , condition(cond)
{
}

PFTargetSelector::RequestParams::RequestParams(const CPtr<PFBaseUnit> &pOwner_, const IMiscFormulaPars * pMiscPars_, const Target &requester_)
  : pMiscPars(pMiscPars_)
  , pOwner(pOwner_)
  , pRequester(&requester_)
  , pReceiver(pOwner_)
  , condition(GetDefaultTargetCondition())
{
}

PFTargetSelector::RequestParams::RequestParams(const CPtr<PFBaseUnit> &pOwner_, const IMiscFormulaPars * pMiscPars_, const Target &requester_, const ITargetCondition& cond)
  : pMiscPars(pMiscPars_)
  , pOwner(pOwner_)
  , pRequester(&requester_)
  , pReceiver(pOwner_)
  , condition(&cond)
{
}

PFTargetSelector::RequestParams::RequestParams(const CPtr<PFBaseUnit> &pOwner_, const IMiscFormulaPars * pMiscPars_, const Target &requester_, const ITargetCondition* const cond)
  : pMiscPars(pMiscPars_)
  , pOwner(pOwner_)
  , pRequester(&requester_)
  , pReceiver(pOwner_)
  , condition(cond)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFTargetSelector::RetrieveParam(ExecutableFloatString const &par, const RequestParams &pars, float defaultValue)
{
	return par(pars.pOwner, pars.pOwner, pars.pMiscPars, defaultValue);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFTargetSelector::RetrieveParam(ExecutableIntString const &par, const RequestParams &pars, int defaultValue)
{
	return par(pars.pOwner, pars.pOwner, pars.pMiscPars, defaultValue);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NWorld::PFTargetSelector::s_DumpSelectors = false;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string PFTargetSelector::GetDebugName() const
{
  string res = NStr::IntToStr( GetObjectId() ) + " (" + GetObjectTypeName() + ")";
  return res;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string PFTargetSelector::DumpTarget( const Target& target ) const
{
  string res;
  string name;
  if ( target.IsObject() )
  {
    res = target.IsUnit()? "Unit:" : "Object:";
    if (!GetWorld()->GetAIContainer()->FindObjectName( name, target.GetObject() ) )
      name = NStr::IntToStr( target.GetObject()->GetObjectId() );
  }
  else 
  {
    res = "Point ";
  }
  res += name + " @";
  CVec3 pos = target.AcquirePosition();

  res  += NStr::IntToStr( (int)pos.x ) + ", " + NStr::IntToStr( (int)pos.y );
  return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFMultipleTargetSelector::EnumerateTargets(ITargetAction &action, const RequestParams &pars)
{
	NI_VERIFY(IsValid(pars.pOwner), "Target selector owner should be valid", return; );

	const NDb::MultipleTargetSelector *pDBData = static_cast<const NDb::MultipleTargetSelector*>(pDB.GetPtr());

	const Target *pOriginalTarget = (pDBData->flags & NDb::TARGETSELECTORFLAGS_IGNOREORIGINALTARGET) ? pars.pRequester : 0;

  const bool deadAllowed = pDBData->flags & NDb::TARGETSELECTORFLAGS_DEADALLOWED;

  DUMP_SELECTOR_START()

	switch (pDBData->mode)
	{
		case NDb::TARGETSELECTORMODE_NORMAL:
		{
			NormalTargetSelector sel(action, pOriginalTarget, deadAllowed);
			ForAllTargets(sel, pars);
			break;
		}
		case NDb::TARGETSELECTORMODE_CAPTURETARGETS:
		{
			if (runCount == 0)
			{
				CaptureTargetsSelector sel(action, rememberedTargets, pOriginalTarget, deadAllowed);
				ForAllTargets(sel, pars);
			}
			else
			{
				for (vector<Target>::iterator it = rememberedTargets.begin(); it != rememberedTargets.end(); ++it)
        {
          if ( it->IsValid() ) // We need to check, because targets captured by CaptureTargetsSelector may be invalid on next frame
					  action(*it);
        }
			}
			break;
		}
		case NDb::TARGETSELECTORMODE_SENDONCE:
		{
			SendOnceSelector sel(action, rememberedTargets, pOriginalTarget, deadAllowed);
			ForAllTargets(sel, pars);
			break;
		}
		default:
			NI_ALWAYS_ASSERT("Invalid mode");
	}
  DUMP_SELECTOR_END()

	++runCount;
}

struct MultipleTargetSelectorFormulaPars : TargetSelectorFormulaPars, NonCopyable
{
  MultipleTargetSelectorFormulaPars( const IMiscFormulaPars* _pMisc, const PFMultipleTargetSelector * _pTS )
    : TargetSelectorFormulaPars(_pMisc), rememberedTargets(_pTS->rememberedTargets) {}

  virtual float GetVariable( const char *name ) const
  {
    if ( strcmp( name, "RememberedTargetsNumber" ) == 0 )
      return rememberedTargets.size();

    return TargetSelectorFormulaPars::GetVariable(name);
  }

  virtual CVec2 GetVectorVariable( const char * name ) const
  {
    if ( strcmp( name, "LastRememberedTargetPos" ) == 0 )
      return rememberedTargets.empty() ? VNULL2 : rememberedTargets.back().AcquirePosition().AsVec2D();

    return TargetSelectorFormulaPars::GetVectorVariable(name);
  }
private:
  const vector<Target>& rememberedTargets;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSingleTargetSelector::EnumerateTargets(ITargetAction &action, const RequestParams &pars)
{
	Target targ;
	if (FindTarget(pars, targ))
	{
		NI_ASSERT(targ.IsValid(true), "Target should be valid");
		action(targ);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFAreaTargetSelector::PFAreaTargetSelector(const NDb::TargetSelector &db, PFWorld* world)
: Base( db, world )
#ifndef _SHIPPING
, debug_show(false)
#endif
{
  if ( GetDB().targetSelector )
    pTargetSelector = static_cast<PFSingleTargetSelector*>(GetDB().targetSelector->Create( world ));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAreaTargetSelector::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
	PFAIWorld const* pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();
  const Target* target = pars.pRequester;

  if ( target->IsUnit() && !IsValid( target->GetUnit() ) )
  {
    return;
  }

	float range = RetrieveParam(GetDB().range, pars);

  CVec3 pos( 0.0f, 0.0f, 0.0f );
  if ( fabs2( GetDB().absolutePosition ) > 0.0f )
  {
    pos = CVec3( GetDB().absolutePosition, 0.0f );
  }
  else if ( pTargetSelector )
  {
    Target targ;
    if ( pTargetSelector->FindTarget( pars, targ ) )
      pos = targ.AcquirePosition();
    else
      return;
  }
  else
  {
    pos = pars.pRequester->AcquirePosition();
  }

	RangeSelectorFunctor func(DumpTargetWrapper(this,action), pos.AsVec2D(), range, pars);
	pAIWorld->ForAllInRange(pos, range + pAIWorld->GetMaxObjectSize() * 0.5f, func,
		                      UnitMaskingPredicate(pars.pOwner, GetDB().targetFilter));
#ifndef _SHIPPING
  if (g_show_ts_ranges && !debug_show)
  {
    NDebug::ShowTargetSelectorRange(pars.pOwner, this, pos, range);
    debug_show = true; // Do not show range twice
  }
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFDblPointTargetSelector::MakePos(const RequestParams &pars, NDb::ETargetSelectorPoint pointSpec, CVec2 &pos) const
{
	switch (pointSpec)
	{
		case NDb::TARGETSELECTORPOINT_ABILITYOWNER:
			pos = pars.pOwner->GetPosition().AsVec2D();
			break;
		case NDb::TARGETSELECTORPOINT_CURRENTPOSITION:
			pos = pars.pRequester->AcquirePosition().AsVec2D();
			break;
		case NDb::TARGETSELECTORPOINT_PREVIOUSPOSITION:
			pos = prevPos;
			break;
    case NDb::TARGETSELECTORPOINT_OWNERDIRECTION:
      pos = pars.pOwner->GetPosition().AsVec2D();
      if ( PFBaseMovingUnit const *pMovingUnit = dynamic_cast<PFBaseMovingUnit const*>(pars.pOwner.GetPtr()) )
      {
        pos += pMovingUnit->GetMoveDirection();
      }
			break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFDblPointTargetSelector::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
	CVec2 newPos = pars.pRequester->AcquirePosition().AsVec2D();

	// When previous position is not defined
	if (runCount == 0)
		prevPos = newPos;

	OnForAllTargets(action, pars);

	prevPos = newPos;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSectorTargetSelector::OnForAllTargets(ITargetAction &action, const RequestParams &pars)
{
	float limitAngle = ToRadian(GetDB().angle);

	// Evaluate direction
	CVec2 beginPos, endPos;
	MakePos(pars, GetDB().segmentBegin, beginPos);
	MakePos(pars, GetDB().segmentEnd, endPos);
	CVec2 dir = endPos - beginPos;
	Normalize(&dir);

  const float offset = GetDB().segmentDirectionOffset;

  if (abs(offset) > FLT_EPSILON)
  {
    RotateVector(dir, offset);
  }

	float range = RetrieveParam(GetDB().range, pars);

  if ( GetDB().centerIsSegmentEnd )
   beginPos = endPos;

	// Functor
	struct SectorSelectorFunctor : public NonCopyable
	{
		DumpTargetWrapper action;
		CVec2         pos;
		CVec2         dir;
		float         range;
		float         refAngle;

    const PFTargetSelector::RequestParams& request;

    SectorSelectorFunctor(DumpTargetWrapper action_, const CVec2 &pos_, const CVec2 &dir_, float range_, float refAngle_, const PFTargetSelector::RequestParams& request)
      : action(action_)
      , pos(pos_)
      , dir(dir_)
      , range(range_)
      , refAngle(refAngle_)
      , request(request)
    {
    }

    void operator()( PFLogicObject& unit )
    {
      if ( unit.IsInRange( pos, range ) )
      {
        const float halfSize = unit.GetObjectSize() * 0.5f;
        const CVec2 vectorToTarget = unit.GetPosition().AsVec2D() - pos;

        const float distToTarget = fabs( vectorToTarget );

        // ÷ель дальше своего размера
        if ( distToTarget > halfSize )
        {
          const float invertDist = 1.0f / distToTarget;

          const float angle = acosf( dir.Dot( vectorToTarget ) * invertDist ) - asinf( halfSize * invertDist );

          //  рай цели оказываетс€ за сектором
          if ( angle > refAngle )
            return;
        }

        const Target targ( &unit );
        if (CheckTargetCondition(targ, request))
          action( targ );
      }
    }
	};

  SectorSelectorFunctor func(DumpTargetWrapper(this,action), beginPos, dir, range, limitAngle, pars);

	PFAIWorld const *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();
  pAIWorld->ForAllInRange(CVec3(beginPos, 0.0f), range + pAIWorld->GetMaxObjectSize() * 0.5f, func,
										  		UnitMaskingPredicate(pars.pOwner, GetDB().targetFilter));
}

PFCapsuleTargetSelector::PFCapsuleTargetSelector(const NDb::TargetSelector &db, PFWorld* world) 
: Base( db, world ), origin(0.0f, 0.0f) 
{
  if ( GetDB().segmentEndTargetSelector )
    pSegmentEndTargetSelector = static_cast<PFSingleTargetSelector*>( GetDB().segmentEndTargetSelector->Create( world ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCapsuleTargetSelector::OnForAllTargets(ITargetAction &action, const RequestParams &pars)
{
	// Evaluate direction
	CVec2 beginPos, endPos;
	MakePos(pars, GetDB().segmentBegin, beginPos);
  if ( !pSegmentEndTargetSelector )
  {
	  MakePos(pars, GetDB().segmentEnd, endPos);
  }
  else
  { 
    Target targ;
    if (!pSegmentEndTargetSelector->FindTarget( pars, targ ) )
      return;
    endPos = targ.AcquirePosition().AsVec2D();
  }

  const float offset = GetDB().segmentDirectionOffset;

  if (abs(offset) > FLT_EPSILON)
  {
    CVec2 dir(endPos - beginPos);

    RotateVector(dir, offset);

    endPos = beginPos + dir;
  }

  if ( runCount == 0 )
    origin = pars.pOwner->GetPosition().AsVec2D();

	float range = RetrieveParam(GetDB().range, pars);
  float rangeFromOrigin = RetrieveParam( GetDB().rangeFromOwner, pars );
	// Functor
	struct CapsuleSelectorFunctor : public NonCopyable
	{
		DumpTargetWrapper action;
		CVec2 const   &bPos;
		CVec2 const   &ePos;
		CVec2         dir;
		float         length;
		float         range;
    CVec2 const   &origin;
    float         rangeFromOrigin;
    bool          cutoff;

    const PFTargetSelector::RequestParams& request;

    CapsuleSelectorFunctor(DumpTargetWrapper action_, CVec2 &begPos, CVec2 &endPos, float range_, CVec2 const &origin_, float rangeFromOrigin_, bool cutoff_, const PFTargetSelector::RequestParams& request)
      : action(action_)
      , bPos(begPos)
      , ePos(endPos)
      , range(range_)
      , origin(origin_)
      , rangeFromOrigin(rangeFromOrigin_)
      , cutoff(cutoff_)
      , request(request)
    {
      dir = endPos - begPos;
      length = dir.Length();
      if (length > 1.0e-6f)
        dir /= length;
    }

		void CalculateCenterAndRadius(CVec2 &center, float &radius)
		{
			center = (bPos + ePos) * 0.5f;
			radius = length * 0.5f;
		}

    void operator()(PFLogicObject &unit)
    {
      if ( rangeFromOrigin > 0.0f && !unit.IsInRange( origin, rangeFromOrigin ) )
        return;

      float sqrDist = SqrDist2Segment(unit.GetPosition().AsVec2D(), bPos, ePos, dir, length, cutoff );
      if ( 0.0f <= sqrDist && sqrDist < fabs2( range + unit.GetObjectSize() * 0.5f ) )
      {
        const Target targ(&unit);
        if (CheckTargetCondition(targ, request))
          action(targ);
      }
    }
	};

  CapsuleSelectorFunctor func(DumpTargetWrapper(this,action), beginPos, endPos, range, origin, rangeFromOrigin, runCount <= 1 && GetDB().cutoffFirstSegment, pars );

	CVec2 center;
	float addRange;
	func.CalculateCenterAndRadius(center, addRange);

	PFAIWorld const *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();
	pAIWorld->ForAllInRange(CVec3(center, 0.0f), range + addRange + pAIWorld->GetMaxObjectSize() * 0.5f, func,
		UnitMaskingPredicate(pars.pOwner, GetDB().targetFilter));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFNearestInAreaTargetSelector::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
	PFAIWorld const *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();

	CVec3 const pos  = pars.pRequester->AcquirePosition();

	struct Func : public NonCopyable
	{
		CVec2         pos;
		float         sqrDistance;
		PFLogicObject *pFoundObject;

    const PFTargetSelector::RequestParams& request;

    explicit Func(const CVec2 &pos_, const PFTargetSelector::RequestParams& request)
      : pos(pos_)
      , sqrDistance(FLT_MAX)
      , pFoundObject(0)
      , request(request)
    {
    }

		void operator()(PFLogicObject &obj)
		{
			if (obj.IsDead())
				return;

      if (!CheckTargetCondition(obj, request))
        return;

			float d = fabs2(obj.GetPosition().AsVec2D() - pos);
			if (d < sqrDistance)
			{
				sqrDistance = d;
				pFoundObject = &obj;
			}
		}
	};

  Func f(pos.AsVec2D(), pars);

	float range = RetrieveParam(GetDB().range, pars);

	pAIWorld->ForAllInRange(pos, range, f, UnitMaskingPredicate(pars.pOwner, GetDB().targetFilter));

	// if object found - call functor for it
	if (f.pFoundObject)
	{
		Target targ(CPtr<PFLogicObject>(f.pFoundObject));
    DUMP_TARGET(targ)
		action(targ);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSummonEnumerator::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
	if (!pars.pRequester->IsUnitValid())
		return;

	PFBaseMaleHero *pHero = dynamic_cast<PFBaseMaleHero*>(pars.pRequester->GetUnit().GetPtr());
	NI_VERIFY(pHero, "Invalid requester for summon enumerator. Should be male hero", return; );

  struct Func : public ISummonAction, public PFBaseHero::CloneFunc, public NonCopyable
	{
		DumpTargetWrapper action;

    const PFTargetSelector::RequestParams& request;

    Func(DumpTargetWrapper a, const PFTargetSelector::RequestParams& request)
      : action(a)
      , request(request)
    {
    }

    virtual void operator()(PFBaseUnit * pUnit)
    {
      const Target targ(pUnit);
      if (CheckTargetCondition(targ, request))
        action(targ);
    }

    virtual void operator()(PFBaseHero* pClone)
    {
      const Target targ(pClone);
      if (CheckTargetCondition(targ, request))
        action(targ);
    }
	};

  Func f(DumpTargetWrapper(this,action), pars);

  if ( ( GetDB().summonTypes & NDb::SUMMONTYPEFLAGS_PRIMARY ) != 0 )
	  pHero->ForAllSummons( f, NDb::SUMMONTYPE_PRIMARY );
  if ( ( GetDB().summonTypes & NDb::SUMMONTYPEFLAGS_SECONDARY ) != 0 )
	  pHero->ForAllSummons( f, NDb::SUMMONTYPE_SECONDARY );
  if ( ( GetDB().summonTypes & NDb::SUMMONTYPEFLAGS_PET ) != 0 )
    pHero->ForAllSummons( f, NDb::SUMMONTYPE_PET );
  if ( ( GetDB().summonTypes & NDb::SUMMONTYPEFLAGS_CLONE ) != 0 )
    pHero->ForAllClones( f );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFUnitEnumerator::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
	PFAIWorld const *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();
	WrapperFunctor func(DumpTargetWrapper(this,action), pars);
  NDb::ESpellTarget targetFilter = GetDB().targetFilter;

  if ( (targetFilter & NDb::SPELLTARGET_FLAGPOLE) )
  {
    pAIWorld->ForAllFlagpoles( func, MakeSpellTargetFactionFlags( *pars.pOwner, targetFilter ) );
    targetFilter = (NDb::ESpellTarget)(targetFilter & ~NDb::SPELLTARGET_FLAGPOLE);
  }
  if ( targetFilter & NDb::SPELLTARGET_ALL )
	  pAIWorld->ForAll(func, UnitMaskingPredicate(pars.pOwner, targetFilter));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFHeroEnumerator::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
	PFAIWorld const *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();

	int factionFlags = MakeSpellTargetFactionFlags(*pars.pOwner, GetDB().targetFilter);

	WrapperFunctor func(DumpTargetWrapper(this,action), pars);
	if (factionFlags & (1L << NDb::FACTION_FREEZE))
		pAIWorld->ForAllHeroes(func, NDb::FACTION_FREEZE, GetDB().targetFilter);
	if (factionFlags & (1L << NDb::FACTION_BURN))
		pAIWorld->ForAllHeroes(func, NDb::FACTION_BURN, GetDB().targetFilter);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFNearestTargetSelector::PFNearestTargetSelector(const NDb::TargetSelector &db, PFWorld* world)
  : DBLinker(db, world)
{
	if (GetDB().targetSelector)
		pTargetSelector = GetDB().targetSelector->Create( world );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFNearestTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
	if (!pTargetSelector)
		return false;

	// Has target selector
	struct Func : public ITargetAction, public NonCopyable
	{
		Target &targ;
		float  minRangeSqr;
		CVec2  checkPos;

		Func(Target &t, const CVec2 &pos)
			: targ(t), checkPos(pos), minRangeSqr(FLT_MAX)
		{}

		virtual void operator()(const Target &target)
		{
			float rangeSqr = fabs2(target.AcquirePosition().AsVec2D() - checkPos);
			if (rangeSqr < minRangeSqr)
			{
				targ = target;
				minRangeSqr = rangeSqr;
			}
		}
	} f(target, pars.pRequester->AcquirePosition().AsVec2D());

	pTargetSelector->EnumerateTargets(f, pars);
	if ( f.minRangeSqr < FLT_MAX )
  {
    DUMP_SELECTOR_TARGET( target );
    return true;
  }
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFUnitPlaceCorrector::PFUnitPlaceCorrector(const NDb::TargetSelector &db, PFWorld* world)
  : DBLinker(db, world)
{
	if (GetDB().targetSelector)
		pTargetSelector = static_cast<PFSingleTargetSelector*>(GetDB().targetSelector->Create(world));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFUnitPlaceCorrector::FindTarget(const RequestParams &pars, Target &target)
{
	if (!pTargetSelector)
		return false;

	if (!pTargetSelector->FindTarget(pars, target))
		return false;

  PFBaseMovingUnit *pMovingUnit = dynamic_cast<PFBaseMovingUnit*>(pars.pOwner.GetPtr());
	NI_VERIFY(pMovingUnit, "UnitPlaceCorrector target selector can be applied to moving unit only", return false);

	CVec2 targetPos  = target.AcquirePosition().AsVec2D();
  float radius = GetDB().radius;

  CVec2 foundPosition;
	bool  posFound = false;

  int checkMode = 0;
  if ( GetDB().passabilityCheckMode != 0 )
  {
    if ( ( GetDB().passabilityCheckMode & NDb::TRACEMODE_DYNAMIC ) != 0 )
      checkMode |= MAP_MODE_DYNAMIC;
    if ( ( GetDB().passabilityCheckMode & NDb::TRACEMODE_BUILDING ) != 0 )
      checkMode |= MAP_MODE_BUILDING;
    if ( ( GetDB().passabilityCheckMode & NDb::TRACEMODE_STATIC ) != 0 )
      checkMode |= MAP_MODE_STATIC;
  }

	// Try once (in the case of direction used)
	if (GetDB().checkByRangeToRequester)
	{
		CVec2 requestPos = pars.pRequester->AcquirePosition().AsVec2D();

    if ( radius > 0.0f )
    {
      CVec2 dir = targetPos - requestPos;
      float dist = fabs( dir );
      if ( dist > radius )
      {
        // Correct target pos
        targetPos = requestPos + dir * radius / dist;
      }
    }

		if (fabs2(requestPos - targetPos) > 1.0f)
		{
			posFound = pMovingUnit->FindFreePlace2( targetPos, requestPos, radius, foundPosition, false, GetDB().nativeTerrainOnly, checkMode, GetDB().checkLineOfSight );
		}
	}

	//  Try second time
	if ( !posFound )
	{
		if ( !pMovingUnit->FindFreePlace( targetPos, radius, foundPosition, false, GetDB().nativeTerrainOnly, checkMode, GetDB().checkLineOfSight ) )
			return false;
	}

	target.SetPosition(CVec3(foundPosition, 0.0f));
  DUMP_SELECTOR_TARGET( target )
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFConvertTargetToLand::PFConvertTargetToLand(const NDb::TargetSelector &db, PFWorld* world)
  : DBLinker(db, world)
{
	if (GetDB().targetSelector)
		pTargetSelector = GetDB().targetSelector->Create(world);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFConvertTargetToLand::FindTarget(const RequestParams &pars, Target &target)
{
  if ( !pTargetSelector )
  {
	  target.SetPosition( pars.pRequester->AcquirePosition() );
	  return true;
  }

  struct Collector : public ITargetAction
  {
    vector<CVec3> targets;

    virtual void operator()(const Target &target)
    {
      targets.push_back(target.AcquirePosition());
    }
  } coll;
  pTargetSelector->EnumerateTargets( coll, pars );

  struct DistComparator{
    DistComparator( const CVec3& targ ):targ(targ) {}

    bool operator()(const CVec3& a, const CVec3& b) {
      return fabs2(a - targ) > fabs2(b - targ);
    }
    CVec3 targ;
  };

  if ( coll.targets.empty() )
    return false;

  if ( coll.targets.size() == 1 )
  {
     target.SetPosition( coll.targets[0] );
     return true;
  }
  switch( GetDB().aggregateMode )
  {
  case NDb::TARGETTOLANDMODE_FIRST:
    target.SetPosition( coll.targets[0] );
    break;

  case NDb::TARGETTOLANDMODE_NEAREST:
    sort( coll.targets.begin(), coll.targets.end(), DistComparator( pars.pOwner->GetPosition() ) );
    target.SetPosition( coll.targets[0] );
    break;

  case NDb::TARGETTOLANDMODE_CENTER:
    {
      CVec3 avg(0,0,0);
      for ( vector<CVec3>::iterator it = coll.targets.begin(); it != coll.targets.end(); ++it )
        avg += *it;
      avg /= coll.targets.size();

      target.SetPosition( avg );
      break;
    }
  case NDb::TARGETTOLANDMODE_CENTERTARGET:
    {
      CVec3 avg(0,0,0);
      for ( vector<CVec3>::iterator it = coll.targets.begin(); it != coll.targets.end(); ++it )
        avg += *it;
      avg /= coll.targets.size();

      CVec3 nearest = coll.targets.front();
      float minDist = fabs2( nearest - avg );
      for ( vector<CVec3>::iterator it = coll.targets.begin()+1; it != coll.targets.end(); ++it )
      {
        float d = fabs2( *it - avg );
        if ( d < minDist )
          minDist = d, nearest = *it;
      }

      target.SetPosition( nearest );
      break;
    }
  }
  DUMP_SELECTOR_TARGET( target )
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFMainBuildingTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
  NI_VERIFY(IsValid(pars.pOwner), "Invalid owner", return false);

  PFAIWorld const *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();
  NI_VERIFY(NULL != pAIWorld, "Invalid world", return false);

  m_pMainBuilding = NULL;
  m_faction       = pars.pOwner->GetFaction();

  pAIWorld->ForAllUnits(*this);

  if (IsValid(m_pMainBuilding))
  {
    NWorld::PFBaseUnit *pMainBuilding = dynamic_cast<NWorld::PFBaseUnit*>(m_pMainBuilding.GetPtr());

    target.SetUnit(pMainBuilding);
    DUMP_SELECTOR_TARGET( target )

    return true;
  }

  return false;
}

void PFMainBuildingTargetSelector::operator()(PFLogicObject &object)
{
  if (object.GetUnitType() == NDb::UNITTYPE_MAINBUILDING && object.GetFaction() == m_faction)
  {
    m_pMainBuilding = &object;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFFountainTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
  NI_VERIFY(IsValid(pars.pOwner), "Invalid owner", return false);

  PFAIWorld const *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();
  NI_VERIFY(NULL != pAIWorld, "Invalid world", return false);

  m_pFountain = NULL;
  m_faction   = pars.pOwner->GetFaction();

  pAIWorld->ForAllUnits(*this);

  if (IsValid(m_pFountain))
  {
    NWorld::PFBaseUnit *pFountain = dynamic_cast<NWorld::PFBaseUnit*>(m_pFountain.GetPtr());

    target.SetUnit(pFountain);
    DUMP_SELECTOR_TARGET( target )

    return true;
  }

  return false;
}

void PFFountainTargetSelector::operator()(PFLogicObject &object)
{
  if (object.GetUnitType() == NDb::UNITTYPE_BUILDING && object.GetFaction() == m_faction)
  {
    if (NWorld::PFFountain *pFountain = dynamic_cast<NWorld::PFFountain*>(&object))
    {
      m_pFountain = pFountain;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFShopTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
  NI_VERIFY(IsValid(pars.pOwner), "Invalid owner", return false);

  PFAIWorld const *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();
  NI_VERIFY(NULL != pAIWorld, "Invalid world", return false);

  m_pShop = NULL;
  m_faction   = pars.pOwner->GetFaction();
  m_ownerPos = pars.pOwner->GetPosition();
  m_minDist = 1e9;
  pAIWorld->ForAllUnits(*this);
  
  if (IsValid(m_pShop))
  {
    NWorld::PFBaseUnit *pShop= dynamic_cast<NWorld::PFBaseUnit*>(m_pShop.GetPtr());
    target.SetUnit(pShop);
    target.SetPosition(pShop->GetPosition());
    DUMP_SELECTOR_TARGET( target )
    return true;
  }

  return false;
}

void PFShopTargetSelector::operator()(PFLogicObject &object)
{
  if (object.GetUnitType() == NDb::UNITTYPE_SHOP && (object.GetFaction() == m_faction || object.GetFaction() == NDb::FACTION_NEUTRAL))
  {
    if (NWorld::PFShop *pShop = static_cast<NWorld::PFShop*>(&object))
    {
      NDb::Ptr<NDb::ConsumablesShop> const& pDBShop = pShop->GetConsumablesShop();
      NI_VERIFY(pDBShop, "ConsumablesShop should be valid!", return );
      if ( pDBShop->secretShop == GetDB().secret)
      {
        float dist = (pShop->GetPosition() - m_ownerPos).Length();
        if (dist < m_minDist)
        {
          m_pShop = pShop;
          m_minDist = dist;
        }
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFRelativeUnitTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
	if (!pars.pRequester->IsUnit())
		return false;

	PFBaseUnit *pUnit = pars.pRequester->GetUnit().GetPtr();
	switch (GetDB().relation)
	{
	 	
		case NDb::UNITRELATION_MASTER:
		{
			const CPtr<PFBaseUnit> &pMale = pUnit->GetMasterUnit();
			if (IsValid(pMale))
			{
				target.SetUnit( pMale );
        if (!CheckTargetCondition(target, pars))
          return false;
        DUMP_SELECTOR_TARGET( target )
				return true;
			}
			break;
		}

    case NDb::UNITRELATION_TARGET:
    {
      const CPtr<PFBaseUnit> &pTarget = pUnit->GetCurrentTarget();
      if (IsValid(pTarget))
			{
				target.SetUnit( pTarget );
        if (!CheckTargetCondition(target, pars))
          return false;
        DUMP_SELECTOR_TARGET( target )
				return true;
			}
			break;
    }

    case NDb::UNITRELATION_ALPHASUMMON:
    {
      const CPtr<PFBaseUnit> &pAlphaSummon = pUnit->GetAlphaSummon();
      if (IsValid(pAlphaSummon))
			{
				target.SetUnit( pAlphaSummon );
        if (!CheckTargetCondition(target, pars))
          return false;
        DUMP_SELECTOR_TARGET( target )
				return true;
			}
			break;
    }

    case NDb::UNITRELATION_MOUNT:
    {
      CDynamicCast<PFBaseHero const> pHero(pUnit);
      if ( IsValid(pHero) )
      {
        const CPtr<PFBaseMovingUnit> &pMount = pHero->GetMount();
        if (IsValid(pMount))
        {
          target.SetUnit( pMount.GetPtr() );
          if (!CheckTargetCondition(target, pars))
            return false;
          DUMP_SELECTOR_TARGET( target )
          return true;
        }
      }
      break;
    }
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Heavily based on PFApplKickAway
bool PFUnitShiftTarget::FindTarget(const RequestParams &pars, Target &target)
{
	PFAbilityInstance *pAbility = pars.pAbility;
	NI_VERIFY(pAbility, "PFUnitShiftTarget requires ability", return false);

	const Target *pAbilityTarget = pars.pRequester;
	NI_VERIFY(pAbilityTarget->IsUnit(), "Ability target should be a unit", return false);
	PFBaseMovingUnit *pMovingUnit = dynamic_cast<PFBaseMovingUnit*>(pAbilityTarget->GetUnit().GetPtr());
	NI_VERIFY(pMovingUnit, "PFUnitShiftTarget target selector can be applied to moving unit only", return false);

	// Target pos
	CVec2 pos = pMovingUnit->GetPosition().AsVec2D();

	CVec3 posTo = pAbility->GetTarget().AcquirePosition();
	const CVec3 &posFrom = pars.pAbility->GetOwner()->GetPosition();
  CVec2 moveDir = posTo.AsVec2D() - posFrom.AsVec2D();

	float maxKickDistance = RetrieveParam(GetDB().distance, pars);

	CVec2 foundPosition;
	if (fabs2(moveDir) > 1.0e-8f)
	{
		Normalize(&moveDir);
		CVec2 ortDir = CVec2( moveDir.y, -moveDir.x );

		CVec2 dir = pos - posFrom.AsVec2D();
		float distanceFromMoveLine = dir.Dot(ortDir);

		if (fabs(distanceFromMoveLine) > maxKickDistance)
			return false;

		float kickDist;
		if (distanceFromMoveLine > 0.0f)
			kickDist = maxKickDistance - distanceFromMoveLine;
		else
		{
			ortDir = -ortDir;
			kickDist = maxKickDistance + distanceFromMoveLine;
		}

		kickDist = pMovingUnit->CheckStraightMove(pos + ortDir * kickDist, MAP_MODE_ALL_STATICS);
		foundPosition = pos + ortDir * kickDist;
	}
	else
	{
		// Kick from point
		CVec2 dir = pos - posFrom.AsVec2D();
		float dirLenSqr = fabs2(dir);
		if (dirLenSqr > maxKickDistance * maxKickDistance)
			return false;

		if (dirLenSqr < 1.0e-8f)
		{
			NI_ALWAYS_ASSERT("Don't know where to kick!");
			return false;
		}

		Normalize(&dir);

		float kickDist = pMovingUnit->CheckStraightMove(posFrom.AsVec2D() + maxKickDistance * dir, MAP_MODE_ALL_STATICS);
		NI_ASSERT(kickDist <= maxKickDistance, "Logic failed");
		foundPosition = posFrom.AsVec2D() + dir * kickDist;
	}

	target.SetPosition(CVec3(foundPosition, 0.0f));
  DUMP_SELECTOR_TARGET( target )
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFPointTargetSelector::PFPointTargetSelector(const NDb::TargetSelector &db, PFWorld* world)
: DBLinker(db, world)
{
  if (GetDB().targetSelector)
    pTargetSelector = static_cast<PFSingleTargetSelector*>( GetDB().targetSelector->Create( GetWorld() ) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFPointTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
  if ( !pars.pOwner || !pars.pRequester || !pars.pRequester->IsValid() )
    return false;
    
  const CPtr<PFLogicObject> pOwner = pars.pOwner;
  
  Target requestedTarget;
  if ( pTargetSelector )
  {
    if ( !pTargetSelector->FindTarget(pars, requestedTarget) )
      return false;
  }
  else
  {
    requestedTarget = *pars.pRequester;

    if (!CheckTargetCondition(requestedTarget, pars))
      return false;
  }
  
  NI_VERIFY( requestedTarget.IsValid(), "Requester must be an valid target!", return false; );
  
  const CVec3& targetPos = requestedTarget.AcquirePosition();
  CPtr<PFLogicObject> pTarget = requestedTarget.IsObject() ? requestedTarget.GetObject() : NULL;
  
  float range = RetrieveParam(GetDB().range, pars);

  const float minRange = GetDB().checkMinRange && pTarget ? 0.5f * (pOwner->GetObjectSize() + pTarget->GetObjectSize() ) : 0.0f;

  if ( GetDB().checkMinRange )
  {
    if ( range < 0 && range > -minRange ) 
      range = -minRange;
    else if ( range >= 0 && range < minRange )
      range = minRange;
  }

  switch ( GetDB().mode )
  {
  case NDb::POINTTARGETSELECTORMODE_TOOWNER:
    target.SetPosition(pars.pOwner->GetPosition());
    break;
  case NDb::POINTTARGETSELECTORMODE_TOTARGET:
    target.SetPosition(targetPos);
    break;
  case NDb::POINTTARGETSELECTORMODE_RANGEFROMOWNER:
    {
      float traceDist = 1e10f;

      CVec3 pos;

      PFBaseMovingUnit *pMovingUnit = dynamic_cast<PFBaseMovingUnit*>(pars.pReceiver ? pars.pReceiver.GetPtr() : pOwner.GetPtr());

      if ( GetDB().traceMode != 0 && pMovingUnit )
      {
        int traceMode = 0;
        if ( ( GetDB().traceMode & NDb::TRACEMODE_DYNAMIC ) != 0 )
          traceMode |= MAP_MODE_DYNAMIC;
        if ( ( GetDB().traceMode & NDb::TRACEMODE_BUILDING ) != 0 )
          traceMode |= MAP_MODE_BUILDING;
        if ( ( GetDB().traceMode & NDb::TRACEMODE_STATIC ) != 0 )
          traceMode |= MAP_MODE_STATIC;
        traceDist = pMovingUnit->CheckStraightMove(targetPos.AsVec2D(), traceMode);

        pos = pMovingUnit->GetPosition();
      }
      else
      {
        pos = pOwner->GetPosition();
      }
      CVec3 direction = targetPos - pos;

      if (GetDB().paralleledTarget)
      {
        CVec3 direction2target = targetPos - pOwner->GetPosition();
        CVec3 direction2Receiver = pos - pOwner->GetPosition();
        
        CVec3 perpTargetReceiverDir =  direction2Receiver - (direction2Receiver * direction2target / (direction2target.Length()*direction2target.Length()))*direction2target;
        float perpTargetReceiverDist = perpTargetReceiverDir.Length();

        Normalize(&perpTargetReceiverDir);

        CVec3 targetPosFromOwner = targetPos;
        targetPosFromOwner += perpTargetReceiverDist * perpTargetReceiverDir;

        direction = targetPosFromOwner - pos;
      }

      direction.z = 0.0f;
      Normalize(&direction);

      float distance = range;

      if ( traceDist < range )
      {
        distance = traceDist;
      }

      pos += direction * distance;
      target.SetPosition(pos);

      break;
    }
  case NDb::POINTTARGETSELECTORMODE_RANGEFROMTARGET:
    {
      CVec3 pos = targetPos;
      CVec3 direction = pOwner->GetPosition() - pos;
      direction.z = 0.0f;
      Normalize(&direction);

      pos += direction * range;
      target.SetPosition(pos);
      break;
    }
  case NDb::POINTTARGETSELECTORMODE_INTERPOLATION:
    {
      CVec3 pos = targetPos;
      CVec3 direction = pars.pReceiver->GetPosition() - pos;
      direction.z = 0.0f;
      Normalize(&direction);

      pos += direction * range;
      target.SetPosition(pos);
      break;
    }
  case NDb::POINTTARGETSELECTORMODE_OFFSETFROMOWNER:
  case NDb::POINTTARGETSELECTORMODE_OFFSETFROMTARGET:
    {
      CVec2 dir( 0.0f, 1.0f );
      PFLogicObject* pLogicObject = GetDB().mode == NDb::POINTTARGETSELECTORMODE_OFFSETFROMOWNER ? pOwner : pTarget;
      PFBaseMovingUnit* pBaseMovingUnit = dynamic_cast<PFBaseMovingUnit*>( pLogicObject );
      if ( pBaseMovingUnit )
      {
        dir = pBaseMovingUnit->GetMoveDirection();
        Normalize( &dir );
      }


      CVec2 offset = GetDB().offset;
      if ( ( fabs(offset.x) < EPS_VALUE ) && ( fabs(offset.y) < EPS_VALUE ) )
      {
        NI_DATA_ALWAYS_ASSERT( "Offset vector should't be [0,0]!" );
        offset.x = 0.0f;
        offset.y = 1.0f;
      }

      float distance = range;
      if ( distance == 0.0f )
      {
        distance = Min( offset.Length(), minRange );
      }

      Normalize( &offset );

      offset = dir.CProduct( offset ) * distance;

      CVec3 newPos = targetPos + CVec3( offset.y, -offset.x, 0.0f );

      if ( pBaseMovingUnit )
      {
        if ( GetDB().traceMode != 0 && pBaseMovingUnit )
        {
          int traceMode = 0;
          if ( ( GetDB().traceMode & NDb::TRACEMODE_DYNAMIC ) != 0 )
            traceMode |= MAP_MODE_DYNAMIC;
          if ( ( GetDB().traceMode & NDb::TRACEMODE_BUILDING ) != 0 )
            traceMode |= MAP_MODE_BUILDING;
          if ( ( GetDB().traceMode & NDb::TRACEMODE_STATIC ) != 0 )
            traceMode |= MAP_MODE_STATIC;
          float traceDist = pBaseMovingUnit->CheckStraightMove(newPos.AsVec2D(), traceMode);
          CVec3 pos = pBaseMovingUnit->GetPosition();
          CVec3 direction = newPos - pos;
          direction.z = 0.0f;
          traceDist = Min( traceDist, direction.Length() );
          Normalize(&direction);

          pos += direction * traceDist;
          newPos = pos;
        }
      }

      target.SetPosition( newPos );
      break;
    }
  case NDb::POINTTARGETSELECTORMODE_RANGEFROMTARGETTOREQUESTER:
    {
      if ( requestedTarget == *pars.pRequester )
      {
        NI_DATA_ALWAYS_ASSERT( "Target selector should be specified for RangeFromTargetToRequester mode" );
      }
      else
      {
        CVec3 pos = targetPos;
        CVec3 direction = pars.pRequester->AcquirePosition() - pos;
        direction.z = 0.0f;
        Normalize(&direction);

        pos += direction * range;
        target.SetPosition(pos);
      }
      break;
    }
  case NDb::POINTTARGETSELECTORMODE_RANGEFROMTARGETTOABILITY:
    {
      if ( requestedTarget == *pars.pRequester )
      {
        NI_DATA_ALWAYS_ASSERT( "Target selector should be specified for RangeFromTargetToAbility mode" );
      }
      else
      {
        if (IsValid(pars.pAbility) && pars.pAbility->GetTarget().IsValid())
        {
          CVec3 pos = targetPos;
          CVec3 direction = pars.pAbility->GetTarget().AcquirePosition() - pos;
          direction.z = 0.0f;
          Normalize(&direction);

          // »щем позицию в пределах карты по направлению
          for (int i = 0; i < range; i++)
          {
            CVec3 tempPos = targetPos + direction * (range - i);

            TileMap *tileMap = GetWorld()->GetTileMap();
            SVector tile = tileMap->GetTile(tempPos.AsVec2D());
            if (!tileMap->IsPointOutsideMap( tile.x, tile.y ))
            {
              pos = tempPos;
              break;
            }
          }

          target.SetPosition(pos);
        }
        else
        {
          // RangeFromTargetToRequester
          CVec3 pos = targetPos;
          CVec3 direction = pars.pRequester->AcquirePosition() - pos;
          direction.z = 0.0f;
          Normalize(&direction);

          pos += direction * range;
          target.SetPosition(pos);
        }
      }
      break;
    }
  case NDb::POINTTARGETSELECTORMODE_RANDOMPOINT:
  case NDb::POINTTARGETSELECTORMODE_RANDOMDIRECTION:
    {
      float dist = 0.f;
      float angle  = 0.f;

      if(GetWorld())
      {
        dist = GetWorld()->GetRndGen()->NextF( 0.f, range );
        angle = GetWorld()->GetRndGen()->NextF( -FP_PI, FP_PI );
      }
      else
      {
        dist = NRandom::Random(0.f, range );
        angle = NRandom::Random( -FP_PI, FP_PI );
      }

      dist = GetDB().mode == NDb::POINTTARGETSELECTORMODE_RANDOMPOINT ? dist : range;
      CVec3 pos( dist * cos( angle ), dist * sin( angle ), 0.f );
      pos += targetPos;

      target.SetPosition( pos );
      break;
    }
  }
  DUMP_SELECTOR_TARGET( target )
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFFirstTargetSelector::PFFirstTargetSelector(NDb::FirstTargetSelector const &db, PFWorld* world)
  : DBLinker(db, world)
{
  if (GetDB().targetSelector)
    pTargetSelector = GetDB().targetSelector->Create(world);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFFirstTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
  if (!pTargetSelector)
    return false;

  // Has target selector
  struct Func : public ITargetAction, public NonCopyable
  {
    inline Func(Target &t, const CVec2 &pos, bool nearestTarget)
      : checkPos(pos), minRangeSqr(FLT_MAX), nearestTarget(nearestTarget)
    {}

    virtual void operator()(const Target &target)
    {
      if ( nearestTarget || !targ.IsValid() )
      {
        float rangeSqr = fabs2(target.AcquirePosition().AsVec2D() - checkPos);
        if (rangeSqr < minRangeSqr)
        {
          targ = target;
          minRangeSqr = rangeSqr;
        }
      }
    }

    Target& GetTarget() { return targ; }
  private:
    Target  targ;
    float   minRangeSqr;
    CVec2   checkPos;
    bool    nearestTarget;
  } targetFinder(target, pars.pRequester->AcquirePosition().AsVec2D(), GetDB().nearestTarget);

  pTargetSelector->EnumerateTargets(targetFinder, pars);
  if ( targetFinder.GetTarget().IsValid() )
  {
    target = targetFinder.GetTarget();
    DUMP_SELECTOR_TARGET( target )
    return true;
  }
  
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFWeightTargetSelector::PFWeightTargetSelector(NDb::WeightTargetSelector const &db, PFWorld* world)
  : DBLinker(db, world)
{
  if (GetDB().targetSelector)
    pTargetSelector = GetDB().targetSelector->Create(world);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFWeightTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
  if (!pTargetSelector || !pars.pRequester || !pars.pRequester->IsUnit())
    return false;

  PFBaseUnit * pOwner = pars.pRequester->GetUnit();

  if (!pOwner)
    return false;

  // Selection functor, based on TargetFinder from PFBaseUnit (very castrated version)
  struct Func : public ITargetAction, public NonCopyable
  {
    const PFBaseUnit                    &owner;
    float                               maxWeight;
    CPtr<PFBaseUnit>                    pTarget;
    const NDb::UnitTargetingParameters  &unitPars;

    Func(PFBaseUnit &owner, const NDb::UnitTargetingParameters &unitPars)
      : owner(owner), maxWeight(-1.0f), unitPars(unitPars) { }

    const CPtr<PFBaseUnit>& GetTarget() { return pTarget; }

    void operator ()(const Target &target)
    {
      if (!target.IsUnit())
        return;

      PFBaseUnit * unit = target.GetUnit();

		  if ( !owner.CanSelectTarget(unit, true) )
        return;

      const CPtr<PFBaseUnit> pUnit = unit;

      float weight = owner.GetTargetWeight( pUnit, unitPars, NULL );

      if (weight > maxWeight)
      {
        maxWeight = weight;
        pTarget   = unit;
      }
    }
  } targetFinder(*pOwner, pOwner->GetTargetingParams());

  pTargetSelector->EnumerateTargets(targetFinder, pars);

  if ( IsValid(targetFinder.GetTarget()) )
  {
    target = Target(targetFinder.GetTarget());
    DUMP_SELECTOR_TARGET( target )
    return true;
  }
  
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFListOfTargetSelectors::PFListOfTargetSelectors(NDb::ListOfTargetSelectors const &db, PFWorld* world)
  : DBLinker(db, world)
{
  targetSelectors.reserve( db.targetSelectors.size() );
  
  for ( vector<NDb::Ptr<NDb::TargetSelector>>::const_iterator iTS = db.targetSelectors.begin(), iEnd = db.targetSelectors.end(); iTS != iEnd; ++iTS )
  {
    if ( CObj<PFTargetSelector> pTS = (*iTS)->Create(world) )
      targetSelectors.push_back(pTS);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFListOfTargetSelectors::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
  for( vector<CObj<PFTargetSelector>>::iterator iTS = targetSelectors.begin(), iEnd = targetSelectors.end(); iTS != iEnd; ++iTS )
    (*iTS)->EnumerateTargets(action, pars);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFFilterTargetSelector::PFFilterTargetSelector(NDb::FilterTargetSelector const &db, PFWorld* world)
  : DBLinker(db, world)
{
  if (GetDB().targetSelector)
    pTargetSelector = GetDB().targetSelector->Create(world);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFFilterTargetSelector::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
  if (!pTargetSelector)
    return;
  
  struct TargetsFilter : public ITargetAction, public NonCopyable
  {
    vector<NDb::Ptr<NDb::Unit>> const& units;
    DumpTargetWrapper action;
    RequestParams const& pars;
    
    TargetsFilter( vector<NDb::Ptr<NDb::Unit>> const& units, DumpTargetWrapper action, RequestParams const& pars )
      : units(units), action(action), pars(pars) {}
    virtual void operator()(const Target &target)
    {
      if (target.IsUnit())
      {
        if (const NDb::Unit * dbUnit = target.GetUnit()->DbUnitDesc())
        {
          for ( vector<NDb::Ptr<NDb::Unit>>::const_iterator iSuitableUnit = units.begin(), iEnd = units.end(); iSuitableUnit != iEnd; ++iSuitableUnit )
          {
            if ( *iSuitableUnit && (*iSuitableUnit)->GetDBID() == dbUnit->GetDBID() )
            {
              action(target);
              return;
            }
          }
        }
      }
    }
  } targetsProcessor(GetDB().suitableUnits, DumpTargetWrapper(this,action), pars) ;
  
  pTargetSelector->EnumerateTargets(targetsProcessor, pars);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFConditionTargetSelector::PFConditionTargetSelector( const NDb::ConditionTargetSelector& db, PFWorld* world )
  : DBLinker( db, world )
{
  if ( GetDB().targetSelector )
  {
    pTargetSelector = GetDB().targetSelector->Create(world);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFConditionTargetSelector::ForAllTargets( ITargetAction& action, const RequestParams& pars )
{
  struct Func : public ITargetAction, public NonCopyable
  {
    const PFConditionTargetSelector* pTS;
    DumpTargetWrapper action;
    const RequestParams& pars;
    
    Func( const PFConditionTargetSelector* _pTS, DumpTargetWrapper _action, const RequestParams& _pars )
      : pTS( _pTS ), action( _action ), pars( _pars ) { }

    virtual void operator()( const Target& target )
    {
      if ( target.IsObjectValid() )
      {
        bool condition = pTS->GetDB().condition( pars.pOwner, target.GetObject(), pars.pMiscPars, true );
        if ( condition )
        {
          action( target );
        }
      }
    }
  } targetsProcessor( this, DumpTargetWrapper(this,action), pars );

  pTargetSelector->EnumerateTargets( targetsProcessor, pars );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFCountingTargetSelector::PFCountingTargetSelector(NDb::CountingTargetSelector const &db, PFWorld* world)
  : DBLinker(db, world)
{
  if (GetDB().targetSelector)
    pTargetSelector = GetDB().targetSelector->Create(world);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFCountingTargetSelector::ForAllTargets( ITargetAction& action, const RequestParams& pars )
{
  if ( !pTargetSelector )
  {
    return;
  }
  
  int targetsNumber = RetrieveParam( GetDB().targetsNumber, pars );
  if ( targetsNumber <= 0 )
  {
    return;
  }


  struct TargetData
  {
    Target target;
    float sortingValue;
    TargetData() { }
    TargetData( Target _target, float _sortingValue ) : target( _target ), sortingValue( _sortingValue ) {}
  };

  // collect targets
  vector<TargetData> collectedTargets;

  MultipleTargetSelectorFormulaPars formulaPars( pars.pMiscPars, this );

  struct TargetsCollector : public ITargetAction, public NonCopyable
  {
    TargetsCollector( vector<TargetData>& _targets, const NDb::CountingTargetSelector& _dbTS, const RequestParams& _pars, const TargetSelectorFormulaPars* _formulaPars, const vector<Target>& _rememberedTargets )
      : targets( _targets ), dbTS( _dbTS ), pars( _pars ), formulaPars(_formulaPars), rememberedTargets(_rememberedTargets) {}

    virtual void operator()( const Target& target )
    {
      if ( target.IsObject() && ( (dbTS.mode & NDb::TARGETSELECTORMODE_SENDONCE) == 0 || find(rememberedTargets.begin(), rememberedTargets.end(), target) == rememberedTargets.end() ) )
      {
        float sortingValue = dbTS.enableSorting ? dbTS.sortingValue( pars.pOwner, target.GetObject(), formulaPars, true ) : 0.0f;
        targets.push_back( TargetData( target, sortingValue ) );
      }
    }

    vector<TargetData>& targets;
    const NDb::CountingTargetSelector& dbTS;
    const RequestParams& pars;
    const TargetSelectorFormulaPars* formulaPars;
    const vector<Target>& rememberedTargets;
  } collectingTargetsProcessor( collectedTargets, GetDB(), pars, &formulaPars, rememberedTargets );

  pTargetSelector->EnumerateTargets( collectingTargetsProcessor, pars );

  struct CompareTargets
  {
    CompareTargets( const NDb::CountingTargetSelector& dbTS )
      : heroesFirst( dbTS.heroesFirst ), enableSorting( dbTS.enableSorting ), decreasingOrder( dbTS.order == NDb::SORTINGORDER_INCREASING ) {}

    bool operator()( const TargetData& first, const TargetData& second )
    {
      if ( heroesFirst && ( first.target.GetObject()->IsHero() != second.target.GetObject()->IsHero() ) )
      {
        return first.target.GetObject()->IsHero();
      }

      if ( !enableSorting )
      {
        return true;
      }

      bool result = first.sortingValue < second.sortingValue;
      if ( !decreasingOrder )
      {
        result = !result;
      }
      return result;
    }

    bool heroesFirst;
    bool enableSorting;
    bool decreasingOrder;
  }compareTargets( GetDB() );

  sort( collectedTargets.begin(), collectedTargets.end(), compareTargets );

  targetsNumber = min( targetsNumber, collectedTargets.size() );

  // proceed targets
  for( int i = 0; i < targetsNumber; ++i )
  {
    DUMP_TARGET( collectedTargets[i].target )
    action( collectedTargets[i].target );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFComparingTargetSelector::PFComparingTargetSelector(NDb::ComparingTargetSelector const &db, PFWorld* world)
  : DBLinker(db, world)
{
  if (GetDB().targetSelector)
    pTargetSelector = GetDB().targetSelector->Create(world);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFComparingTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
  if (!pTargetSelector)
    return false;

  // Has target selector
  struct ComparingFunc : public ITargetAction, public NonCopyable
  {
    ComparingFunc( float valueToCompare, PFComparingTargetSelector const* pTS, const RequestParams &pars )
      : valueToCompare( valueToCompare ), pTS(pTS), pars(pars), prevDifference(FLT_MAX)
    {}

    virtual void operator()( const Target &target )
    {
      if ( target.IsUnitValid() )
      {
        float formulaValue = pTS->GetDB().valueToCompare( pars.pOwner, target.GetUnit(), pars.pMiscPars, true );
        float difference = fabs( valueToCompare - formulaValue );
        if ( difference < prevDifference )
        {
          targ = target;
          prevDifference = difference;
        }
      }
    }

    Target& GetTarget() { return targ; }
  private:
    Target  targ;
    float valueToCompare;
    float prevDifference;
    PFComparingTargetSelector const* pTS;
    const RequestParams &pars;
 
  } targetFinder(RetrieveParam( GetDB().referenceValue, pars ), this, pars );

  pTargetSelector->EnumerateTargets(targetFinder, pars);
  if ( targetFinder.GetTarget().IsValid() )
  {
    target = targetFinder.GetTarget();
    DUMP_SELECTOR_TARGET(target)
    return true;
  }
  
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFSelectApplicatorTarget::FindTarget(const RequestParams &pars, Target &target)
{
  if ( GetDB().selectTarget == NDb::APPLICATORAPPLYTARGET_ABILITYOWNER )
  {
    target.SetUnit( pars.pOwner );
  }
  else 
  {
    PFBaseApplicator const* pAppl = dynamic_cast<PFBaseApplicator const*>(pars.pMiscPars);
    if ( !pAppl )
      return false;
    pAppl->MakeApplicationTarget( target, GetDB().selectTarget );
  }

  if ( !GetDB().applicatorName.empty() )
  {
    if ( !target.IsUnitValid( true ) )
      return false;
    PFBaseApplicator const* pAppl = dynamic_cast<PFBaseApplicator const*>( target.GetUnit()->FindApplicator( GetDB().applicatorName.c_str(), pars.pMiscPars, GLOBAL, GetDB().applicatorIndex ) );
    if ( !pAppl )
      return false;
    pAppl->MakeApplicationTarget( target, GetDB().namedApplicatorTarget );
  }

  if ( target.IsValid(true) )
  {
    if (!CheckTargetCondition(target, pars))
      return false;
    DUMP_SELECTOR_TARGET(target)
    return true;
  }

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFApplicatorRecipientsTargetSelector::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
  struct ApplRecipientsProcessor : public NonCopyable
  {
    ApplRecipientsProcessor( const NDb::DBID& dbid_, const DumpTargetWrapper &action_, const PFTargetSelector::RequestParams& request)
      : dbid(dbid_)
      , action(action_)
      , request(request)
    {
    }

    void operator()( const CObj<PFBaseApplicator>& pAppl )
    {
      if ( pAppl->GetDBBase()->GetDBID() == dbid )
      {
        const Target target( pAppl->GetReceiver() );
        if (CheckTargetCondition(target, request))
          action( target );
      }
    }

  private:
    NDb::DBID dbid;
    const DumpTargetWrapper &action;

    const PFTargetSelector::RequestParams& request;
  };

  ApplRecipientsProcessor applRecipientsProcessor( GetDB().applicator->GetDBID(), DumpTargetWrapper(this,action), pars );

  pars.pOwner->ForAllSentApplicators( applRecipientsProcessor );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFFixToCenterTargetSelector::PFFixToCenterTargetSelector(NDb::FixToCenterTargetSelector const &db, PFWorld* world)
: DBLinker(db, world)
{
  if (GetDB().targetSelector)
    pTargetSelector = static_cast<PFSingleTargetSelector*>(GetDB().targetSelector->Create( world ));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFFixToCenterTargetSelector::FindTarget(const RequestParams &pars, Target &target)
{
  if (!pTargetSelector)
    return false;

  Target targ;

  if (!pTargetSelector->FindTarget(pars, targ))
    return false;

  if ( !targ.IsValid() )
    return false;

  CVec2 pos = targ.AcquirePosition().AsVec2D();

  vector<const NDb::ScriptArea*> scriptAreas;

  GetWorld()->GetAIContainer()->GetScriptAreasByName( GetDB().nameScriptArea, scriptAreas );

  for( vector<const NDb::ScriptArea*>::const_iterator it = scriptAreas.begin(), itEnd = scriptAreas.end(); it != itEnd; ++it )
  {
    if( fabs( pos - (*it)->position ) <= (*it)->radius )
    {
      pos = (*it)->position;
      break;
    }
  }

  target.SetPosition(CVec3(pos, 0.0f));
  DUMP_SELECTOR_TARGET( target )
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBetweenUnitsTargetSelector::PFBetweenUnitsTargetSelector( const NDb::BetweenUnitsTargetSelector &db, PFWorld* world )
: DBLinker(db, world)
{
  if (GetDB().targetSelector)
    pTargetSelector = static_cast<PFMultipleTargetSelector*>(GetDB().targetSelector->Create( world ));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFBetweenUnitsTargetSelector::ForAllTargets( ITargetAction &action, const RequestParams &pars )
{
  struct Collector : public ITargetAction, public NonCopyable
  {
    Collector( vector<Target>& targets, const PFTargetSelector::RequestParams& request )
      : targets(targets)
      , request(request)
    {
    }

    virtual void operator()(const Target &target)
    {
      if (CheckTargetCondition(target, request))
        targets.push_back(target);
    }

    vector<Target>& targets;

    const PFTargetSelector::RequestParams& request;
  };

  vector<Target> targets;

  Collector coll(targets, pars);

  pTargetSelector->EnumerateTargets(coll, pars);

  if( targets.size() < 2 )
    return;

  int maxTargets = RetrieveParam( GetDB().maxTargets, pars );
  float minDist2 = RetrieveParam( GetDB().minDistBetweenTargets, pars );
  minDist2 = minDist2 * minDist2;
  int targetCount = 0;

  if ( GetDB().pairMode == NDb::BETWEENUNITSMODE_ALLPAIRS )
  {
    for( int i = 0; i < targets.size(); ++i )
    {
      for ( int j = i + 1; j < targets.size(); ++j )
      {
        CVec3 p1 = targets[i].AcquirePosition();
        CVec3 p2 = targets[j].AcquirePosition();
        if ( fabs2(p1-p2) < minDist2 )
          continue;
        const Target targ(0, (p1 + p2) / 2.f );
        DUMP_TARGET(targ);
        action(targ);
        ++targetCount;
        if ( maxTargets > 0 && targetCount >= maxTargets )
          return;
      }
    }
  }
  else if ( GetDB().pairMode == NDb::BETWEENUNITSMODE_CHAIN )
  {
    for( int i = 1; i < targets.size(); ++i )
    {
      CVec3 p1 = targets[i-1].AcquirePosition();
      CVec3 p2 = targets[i].AcquirePosition();
      if ( fabs2(p1-p2) < minDist2 )
        continue;
      const Target targ(0, (p1 + p2) / 2.f );
      DUMP_TARGET(targ);
      action(targ);
      ++targetCount;
      if ( maxTargets > 0 && targetCount >= maxTargets )
        return;
    }
  }

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFWallTargetSelector::PFWallTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world )
{
  if ( GetDB().origin )
    pOriginTS = static_cast<PFSingleTargetSelector*>(GetDB().origin->Create(world));
  if ( GetDB().direction )
    pDirectionTS = static_cast<PFSingleTargetSelector*>(GetDB().direction->Create(world));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFWallTargetSelector::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
  // Evaluate direction
  CVec2 origin(0.0f, 0.0f), direction(0.0f, 0.0f);

  if ( pOriginTS )
  {
    Target target;
    if ( !pOriginTS->FindTarget( pars, target ) )
      return;
    origin = target.AcquirePosition().AsVec2D();
  }
  else
  {
    origin = pars.pRequester->AcquirePosition().AsVec2D();
  }

  if ( pDirectionTS )
  {
    Target target;
    if ( !pDirectionTS->FindTarget( pars, target ) )
      return;
    direction = target.AcquirePosition().AsVec2D();
  }
  else
  {
    direction = pars.pRequester->AcquirePosition().AsVec2D();
  }

  const float width = RetrieveParam(GetDB().width, pars) * 0.5f;
  const float length = RetrieveParam( GetDB().length, pars ) * 0.5f;

  direction -= origin; // now it is actual direction
  Normalize( &direction );
  direction *= length;

  const CVec2 startPos ( origin.x - direction.y, origin.y + direction.x );
  const CVec2 endPos   ( origin.x + direction.y, origin.y - direction.x );
  
  // Functor
  struct WallSelectorFunctor : public NonCopyable
  {
    ITargetAction &action;
    CVec2 const   &bPos;
    CVec2 const   &ePos;
    CVec2         dir;
    float         length;
    float         range;

    const PFTargetSelector::RequestParams& request;

    WallSelectorFunctor(ITargetAction &action_, CVec2 const &begPos, CVec2 const &endPos, float range_, const PFTargetSelector::RequestParams& request)
      : action(action_)
      , bPos(begPos)
      , ePos(endPos)
      , range(range_)
      , request(request)
    {
      dir = endPos - begPos;
      length = dir.Length();
      if (length > 1.0e-6f)
        dir /= length;
    }

    void operator()(PFLogicObject &unit)
    {
      float sqrDist = SqrDist2Segment(unit.GetPosition().AsVec2D(), bPos, ePos, dir, length, false );
      if ( 0.0f <= sqrDist && sqrDist < fabs2( range + unit.GetObjectSize() * 0.5f ) )
      {
        const Target targ(&unit);
        if (CheckTargetCondition(targ, request))
          action(targ);
      }
    }
  };

  WallSelectorFunctor func(action, startPos, endPos, width, pars);

  PFAIWorld const *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();
  pAIWorld->ForAllInRange(CVec3(origin, 0.0f), length + width + pAIWorld->GetMaxObjectSize() * 0.5f, func,
    UnitMaskingPredicate(pars.pOwner, GetDB().targetFilter));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFAttackersTargetSelector::PFAttackersTargetSelector(const NDb::TargetSelector &db, PFWorld* world)
  : Base( db, world )
{
    if ( GetDB().targetSelector )
    pTargetSelector = static_cast<PFSingleTargetSelector*>( GetDB().targetSelector->Create( world ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct FilterFunc : NonCopyable
{
  FilterFunc(DumpTargetWrapper action_, PFBaseUnit * _pOwner, NDb::ESpellTarget targetFilter, const PFTargetSelector::RequestParams& request )
    : mask( _pOwner, targetFilter)
    , action(action_)
    , request(request)
  {
  }

  bool operator()( PFBaseUnit& unit )
  {
    if ( mask( unit ) )
    {
      Target targ( &unit );
      if (CheckTargetCondition(targ, request))
        action( targ );
    }
    return false;
  }

  UnitMaskingPredicate mask;
  DumpTargetWrapper action;

  const PFTargetSelector::RequestParams& request;
};

struct DamageDealersFilterUniqueFunc : NonCopyable
{
  DamageDealersFilterUniqueFunc( DumpTargetWrapper action_, PFBaseUnit * _pOwner, NDb::ESpellTarget targetFilter, const PFTargetSelector::RequestParams& request)
    : mask( _pOwner, targetFilter)
    , action(action_)
    , request(request)
  {
  }

  void operator()(const NWorld::PFBaseApplicator * pApp)
  {
    const NWorld::PFApplDamage * damageAppl = dynamic_cast<const NWorld::PFApplDamage *> (pApp);
    if (damageAppl)
    {
      PFBaseUnit* pOwner = damageAppl->GetAbilityOwner();
      if ( mask( *pOwner ) )
      {
        if ( find( processed.begin(), processed.end(), pOwner ) == processed.end() )
        {
          processed.push_back( pOwner );
          Target targ( pOwner );
          if (CheckTargetCondition(targ, request))
            action( targ );
        }
      }
    }
  }

  vector<PFBaseUnit*> processed;
  UnitMaskingPredicate mask;
  DumpTargetWrapper action;

  const PFTargetSelector::RequestParams& request;
};

void PFAttackersTargetSelector::ForAllTargets( ITargetAction &action, const RequestParams &pars )
{

  Target target = *pars.pRequester;

  if ( pTargetSelector )
  {
    if ( !pTargetSelector->FindTarget( pars, target ) )
      return;
  }

  if ( !target.IsUnitValid() )
  {
    return;
  }

  PFBaseUnit* pUnit = target.GetUnit();



  if ( GetDB().type == NDb::ATTACKERSTYPE_TARGETERS )
  {
    FilterFunc f( DumpTargetWrapper( this, action ), pars.pOwner, GetDB().targetFilter, pars );
    pUnit->ForAllAttackersOnce( f );
  }
  else if ( GetDB().type == NDb::ATTACKERSTYPE_DAMAGEDEALERS )
  {
    float dt = RetrieveParam(GetDB().damageDealTime, pars);
    DamageDealersFilterUniqueFunc f( DumpTargetWrapper( this, action ), pars.pOwner, GetDB().targetFilter, pars );
    pUnit->ForAllAppliedApplicatorsInHistoryLess( f, dt );
  }
}

} // namespace NWorld

REGISTER_DEV_VAR("show_ts_range", g_show_ts_ranges, STORAGE_NONE);

REGISTER_WORLD_OBJECT_NM(PFTargetSelector                 , NWorld);
REGISTER_WORLD_OBJECT_NM(PFMultipleTargetSelector         , NWorld);
REGISTER_WORLD_OBJECT_NM(PFAreaTargetSelector             , NWorld);
REGISTER_WORLD_OBJECT_NM(PFSummonEnumerator               , NWorld);
REGISTER_WORLD_OBJECT_NM(PFUnitEnumerator                 , NWorld);
REGISTER_WORLD_OBJECT_NM(PFHeroEnumerator                 , NWorld);
REGISTER_WORLD_OBJECT_NM(PFNearestInAreaTargetSelector    , NWorld);
REGISTER_WORLD_OBJECT_NM(PFSingleTargetSelector           , NWorld);
REGISTER_WORLD_OBJECT_NM(PFNearestTargetSelector          , NWorld);
REGISTER_WORLD_OBJECT_NM(PFRelativeUnitTargetSelector     , NWorld);
REGISTER_WORLD_OBJECT_NM(PFSectorTargetSelector           , NWorld);
REGISTER_WORLD_OBJECT_NM(PFDblPointTargetSelector         , NWorld);
REGISTER_WORLD_OBJECT_NM(PFCapsuleTargetSelector          , NWorld);
REGISTER_WORLD_OBJECT_NM(PFFountainTargetSelector         , NWorld);
REGISTER_WORLD_OBJECT_NM(PFMainBuildingTargetSelector     , NWorld);
REGISTER_WORLD_OBJECT_NM(PFShopTargetSelector             , NWorld);
REGISTER_WORLD_OBJECT_NM(PFUnitShiftTarget                , NWorld);
REGISTER_WORLD_OBJECT_NM(PFUnitPlaceCorrector             , NWorld);
REGISTER_WORLD_OBJECT_NM(PFConvertTargetToLand            , NWorld);
REGISTER_WORLD_OBJECT_NM(PFPointTargetSelector            , NWorld);
REGISTER_WORLD_OBJECT_NM(PFFirstTargetSelector            , NWorld);
REGISTER_WORLD_OBJECT_NM(PFWeightTargetSelector           , NWorld);
REGISTER_WORLD_OBJECT_NM(PFListOfTargetSelectors          , NWorld);
REGISTER_WORLD_OBJECT_NM(PFFilterTargetSelector           , NWorld);
REGISTER_WORLD_OBJECT_NM(PFConditionTargetSelector        , NWorld);
REGISTER_WORLD_OBJECT_NM(PFCountingTargetSelector         , NWorld);
REGISTER_WORLD_OBJECT_NM(PFComparingTargetSelector        , NWorld);
REGISTER_WORLD_OBJECT_NM(PFSelectApplicatorTarget         , NWorld);
REGISTER_WORLD_OBJECT_NM(PFApplicatorRecipientsTargetSelector, NWorld);
REGISTER_WORLD_OBJECT_NM(PFFixToCenterTargetSelector      , NWorld);
REGISTER_WORLD_OBJECT_NM(PFBetweenUnitsTargetSelector     , NWorld);
REGISTER_WORLD_OBJECT_NM(PFWallTargetSelector             , NWorld);
REGISTER_WORLD_OBJECT_NM(PFAttackersTargetSelector        , NWorld);