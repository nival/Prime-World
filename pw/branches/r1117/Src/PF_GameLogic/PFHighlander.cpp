#include "stdafx.h"

#include "PFAbilityData.h"
#include "PFAIWorld.h"
#include "PFBaseUnit.h"
#include "PFHighlander.h"
#include "TargetSelectorHelper.hpp"

namespace NWorld
{

namespace
{
  struct BaseUnitWithDistance
  {
    CPtr<PFBaseUnit> unit;
    float            distance;

    bool operator <(BaseUnitWithDistance const right) const { return distance < right.distance; }
  };

  struct TargetCollection: public NonCopyable
  {
    TargetCollection(CVec2 const& _position, float range, const PFTargetSelector::RequestParams& request)
      : position(_position)
      , range(range)
      , request(request)
    {
      units.reserve(16);
    }

    void operator()(PFBaseUnit &unit)
    {
      float distance = fabs2( unit.GetPosition().AsVec2D() - position );
      if ( unit.IsInRange( position, range ) && IsUnitValid(&unit) )
      {
        if (!CheckTargetCondition(unit, request))
          return;

        BaseUnitWithDistance item;
        
        item.unit     = &unit;
        item.distance = distance;

        units.push_back(item);
      }
    };

    template <class F> void ForAll(F &action)
    {
      for (int i = 0, count = units.size(); i < count; ++i)
      {
        action(units[i]);
      }
    }

    CVec2                          position;
    float                          range;
    vector< BaseUnitWithDistance > units;

    const PFTargetSelector::RequestParams& request;
  };

  struct ComputeDistanceForTargets: public NonCopyable
  {
    ComputeDistanceForTargets(CVec2 const& from) : position(from) {}

    void operator()(BaseUnitWithDistance &value) const
    {
      value.distance = fabs2( value.unit->GetPosition().AsVec2D() - position );
    }

    CVec2 position;
  };

  // Find latest target
  struct FindBestTarget : public NonCopyable
  {
    FindBestTarget() : pBest(NULL) {}
    void operator()(BaseUnitWithDistance const &value)
    {
      CPtr<PFBaseUnit> const &pUnit = value.unit;
      if (!IsUnitValid(pUnit) )
        return;
      if (NULL == pBest ||                                 // Best value not set
          (!pBest->unit->IsHero() && pUnit->IsHero()) ||   // select hero if best value is unit
          (value.distance < pBest->distance && (pBest->unit->IsHero() == pUnit->IsHero()))) // find nearest target
      {
        pBest = &value;
        return;
      }
    }
    BaseUnitWithDistance const *pBest;
  };

  struct HeroesFirst
  {
    HeroesFirst( CPtr<PFBaseUnit> const& _pBest ) : pBest(_pBest) {}
    bool operator()( BaseUnitWithDistance &value1, BaseUnitWithDistance &value2 )
    {
      CPtr<PFBaseUnit> const &pUnit1 = value1.unit;
      CPtr<PFBaseUnit> const &pUnit2 = value2.unit;

      // best unit is always first
      if ( pUnit1 == pBest )
        return true;

      // heroes first
      if ( pUnit1->IsHero() && !pUnit2->IsHero() )
        return true;

      return false;
    } 
    CPtr<PFBaseUnit> pBest;
  };
} // End of anonymous namespace

void PFHighlanderA1TargetSelector::ForAllTargets(ITargetAction &action, const RequestParams &pars)
{
  PFAIWorld *pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();

  int targetsNumber = RetrieveParam( GetDB().targetCount, pars );
  float range       = RetrieveParam( GetDB().range, pars );

  TargetCollection collection(pars.pRequester->GetUnit()->GetPosition().AsVec2D(), range, pars);
  pAIWorld->ForAllUnitsInRange(pars.pRequester->GetUnit()->GetPosition(), range + pAIWorld->GetMaxObjectSize() * 0.5f, collection,
    UnitMaskingPredicate(pars.pOwner, GetDB().targetFilter) );

  if (0 == collection.units.size()) // There are no targets
    return;

  FindBestTarget best;
  collection.ForAll(best);

  ComputeDistanceForTargets dist2Best( best.pBest->unit->GetPosition().AsVec2D() );
  collection.ForAll(dist2Best);

  // Sort targets by type (counting best target)
  HeroesFirst heroesFirst(best.pBest->unit);
  nstl::sort(collection.units.begin(),collection.units.end(), heroesFirst );

  // Drop excess targets
  if ( targetsNumber < collection.units.size() )
    collection.units.resize( targetsNumber );

  // Sort targets by distance to best target
  nstl::sort(collection.units.begin(), collection.units.end());

  // Form last target to best
  for (int i = collection.units.size() - 1; i >=0 ; --i)
  {
    action(Target(collection.units[i].unit));
  }
}

} // End of namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFHighlanderA1TargetSelector, NWorld);