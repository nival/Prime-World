#include "stdafx.h"
#include "PFAIWorld.h"
#include "PFAITargetSelectors.h"
#include "TargetSelectorHelper.hpp"

namespace NWorld
{
  namespace
  {
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    struct RangeSelectorFunctor : public NonCopyable
    {
      ITargetAction& action;
      CVec2         pos;
      float         range;

      const PFTargetSelector::RequestParams& request;

      RangeSelectorFunctor(ITargetAction& action_, CVec2 pos_, float range_, const PFTargetSelector::RequestParams& request)
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

  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFMaximizingTargetSelector::PFMaximizingTargetSelector(NDb::MaximizingTargetSelector const &db, PFWorld* world)
    : DBLinker(db, world)
  {
    if (GetDB().targetSelector)
      pTargetSelector = GetDB().targetSelector->Create( world );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFMaximizingTargetSelector::FindTarget(const RequestParams &pars, Target &target)
  {
    if (!pTargetSelector)
      return false;

    Target targ;

    CVec3 center = pars.pRequester->AcquirePosition();

    float radius = RetrieveParam( GetDB().range, pars, 0.f );
    if ( radius <= 0.f )
      return false;


    int minTargets = Max( RetrieveParam(GetDB().minTargetsNumber, pars, 0 ), 1 );
    float angleStep = 5.f / (FP_2PI * radius);

    struct Func : public ITargetAction, public NonCopyable
    {
      int targets;
      Func() : targets(0){}
      virtual void operator()(const Target &target)
      { ++targets;}
    };

    { //optimization: if there is no targets in range 'searchRange' -> do not check all angles 
      Func pf;
      PFAIWorld const* pAIWorld = pars.pOwner->GetWorld()->GetAIWorld();

      float searchRange = Max( RetrieveParam( GetDB().searchRange, pars, 0.f ), radius);

      RangeSelectorFunctor func(pf, center.AsVec2D(), searchRange, pars);
      pAIWorld->ForAllInRange(center, searchRange + pAIWorld->GetMaxObjectSize() * 0.5f, func, UnitMaskingPredicate(pars.pOwner, GetDB().searchFilter));

      if ( pf.targets <= 0 )
        return false;
    }

    int maxTargets = 0;
    int prevTargets = 0;
    float sectorAngle = 0.f;
    int sectorLen = 0;
    float bestSectorAngle = 0.f;
    int bestSectorLen = 0;

    float startSectorTargets = 0.f;
    int startSectorLen = 0;
    bool startSectorFilled = false;

    Target destPoint;
    RequestParams destPars( pars.pOwner, pars.pMiscPars, destPoint, pars.condition );

    for ( float angle = 0.f; angle < FP_2PI; angle += angleStep )
    {
      destPoint.SetPosition( center + CVec3( radius * sin(angle), radius * cos(angle), 0.f ) );
      Func f;
      pTargetSelector->EnumerateTargets( f, destPars );

      if ( angle == 0.f )
      {
        startSectorTargets = f.targets;
        startSectorFilled = f.targets <= 0;
      }

      if ( f.targets <= 0 )
      {
        prevTargets = 0;
        continue;
      }

      //DebugTrace( NStr::StrFmt("Ang: %f targets=%d", angle, f.targets) );

      if ( !startSectorFilled )
      {
        if ( f.targets == startSectorTargets )
          ++startSectorLen;
        else 
          startSectorFilled = true;
      }

      if ( f.targets >= maxTargets )
      {
        if ( f.targets > maxTargets )
        {
          maxTargets = f.targets;
          bestSectorLen = 0;
        }

        if ( f.targets > prevTargets )
        {
          sectorAngle = angle;
          sectorLen = 1;
        }
        else if ( f.targets == prevTargets )
        {
          ++sectorLen;
        }
      }
      else 
      {
        if ( sectorLen > bestSectorLen )
        {
          bestSectorAngle = sectorAngle;
          bestSectorLen = sectorLen;
        }
        sectorLen = 0;
      }

      prevTargets = f.targets;
    }

    //glue together start and end sectors if both has equal( and max) targets in it
    if ( startSectorFilled && startSectorTargets == maxTargets && prevTargets == maxTargets )
    {
      sectorLen += startSectorLen;
    }

    // compare last sector
    if ( sectorLen > bestSectorLen )
    {
      bestSectorAngle = sectorAngle;
      bestSectorLen = sectorLen;
    }

    float resAngle = bestSectorAngle + angleStep * bestSectorLen / 2.f;
    //if ( maxTargets > 0 )
    //  DebugTrace(NStr::StrFmt("Best ang: %.3f (sector %.3f+%d) targets=%d", resAngle, bestSectorAngle, bestSectorLen, maxTargets) );

    target.SetPosition( center + CVec3( radius * sin(resAngle), radius * cos(resAngle), 0.f ) );
    DUMP_SELECTOR_TARGET(target)
    if ( maxTargets < minTargets )
      return false;

    return true;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFDelayTargetSelector::PFDelayTargetSelector( const NDb::DelayTargetSelector &db, PFWorld* world )
    : DBLinker( db, world )
    , lastUpdateTime(0.f)
  {
    if (GetDB().targetSelector)
      pTargetSelector = GetDB().targetSelector->Create( world );
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFDelayTargetSelector::ForAllTargets( ITargetAction &action, const RequestParams &pars )
  {
    if (!pTargetSelector)
      return;

    float time = GetWorld()->GetTimeElapsed();

    float delay = RetrieveParam( GetDB().delay, pars, 0.f );
    if ( delay <= 0.f )
    {
      pTargetSelector->EnumerateTargets( action, pars );
      return;
    }

    struct Func : public ITargetAction, public NonCopyable
    {
      hash_map<int, float> newTargets;
      const hash_map<int, float>& oldTargets;
      float time;
      float delay;
      DumpTargetWrapper action;
      Func(const hash_map<int, float>& oldTargets, DumpTargetWrapper action ) : oldTargets(oldTargets),action(action){}
      virtual void operator()(const Target &target)
      {
        if ( !target.IsObject() )
          return;
        int woid = target.GetObject()->GetWOID();
        hash_map<int, float>::const_iterator it = oldTargets.find(woid);
        float appearTime = time;
        if ( it != oldTargets.end() )
          appearTime = it->second;
        newTargets[woid] = appearTime;
        if ( appearTime + delay <= time )
        {
          Target t(target.GetObject());
          action( t );
        }
      }
      void MergeOldTargets()
      {
        for( hash_map<int, float>::const_iterator it = oldTargets.begin(); it != oldTargets.end(); ++it )
        {
          if( newTargets.find(it->first) != newTargets.end() )
            continue;
          newTargets.insert(*it);
        }
      }
    };

    Func proc( targetAppearTimes, DumpTargetWrapper(this,action) );
    proc.time = time;
    proc.delay = delay;
    pTargetSelector->EnumerateTargets( proc, pars );

    if ( lastUpdateTime == time )
      proc.MergeOldTargets();
    lastUpdateTime = time;

    targetAppearTimes.swap( proc.newTargets );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFCheckConditionTargetSelector::PFCheckConditionTargetSelector( const NDb::CheckConditionTargetSelector &db, PFWorld* world )
    : DBLinker( db, world )
  {
    if (GetDB().targetSelector)
      pTargetSelector = GetDB().targetSelector->Create( world );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFCheckConditionTargetSelector::ForAllTargets( ITargetAction &action, const RequestParams &pars )
  {
    struct Collector : public ITargetAction, public NonCopyable
    {
      const ExecutableBoolString& condition;
      const RequestParams& pars;
      int counter;
      vector<Target> targets;

      Collector( const ExecutableBoolString& condition, const RequestParams& pars ) : condition(condition), pars(pars), counter(0) {}

      virtual void operator()(const Target &target)
      {
        targets.push_back(target);

        if ( target.IsUnitValid() )
        {
          bool cond = condition( pars.pOwner, target.GetUnit(), pars.pMiscPars, true );
          if ( cond )
            ++counter;
        }
      }
    } coll( GetDB().condition, pars );
    
    pTargetSelector->EnumerateTargets( coll, pars );

    if ( coll.counter >= RetrieveParam( GetDB().minTargetsNumber, pars, 1 ) )
    {
      for( vector<Target>::iterator it= coll.targets.begin(); it != coll.targets.end(); ++it )
      {
        DUMP_TARGET( *it )
        action( *it );
      }

    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFNotTargetOfSameAbilitySelector::PFNotTargetOfSameAbilitySelector( const NDb::NotTargetOfSameAbilitySelector &db, PFWorld* world )
    : DBLinker( db, world )
  {
    if (GetDB().targetSelector)
      pTargetSelector = GetDB().targetSelector->Create( world );
    if (GetDB().abilityCastersSelector)
      pCastersSelector = GetDB().abilityCastersSelector->Create( world );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFNotTargetOfSameAbilitySelector::ForAllTargets( ITargetAction &action, const RequestParams &pars )
  {
    if ( !pTargetSelector )
      return;
    if ( !pCastersSelector )
    {
      pTargetSelector->EnumerateTargets( action, pars );
      return;
    }

    const PFAbilityData* myAbility;
    if ( pars.pAbility )
      myAbility = pars.pAbility->GetData();
    else
      myAbility = dynamic_cast<const PFAbilityData*>(pars.pMiscPars);
    NI_DATA_VERIFY( myAbility, NStr::StrFmt( "Cannot retrieve ability: %s", GetDB().GetDBID().GetFormatted().c_str() ), return );

    struct Collector : public ITargetAction, public NonCopyable
    {
    private:
      vector<Target> targets;
      bool hasTargets;
      const PFAbilityData* myAbility;
      PFTargetSelector* pCastersSelector;
      const RequestParams &pars;
    public:

      Collector( const PFAbilityData* myAbility, PFTargetSelector* pCastersSelector,const RequestParams &pars ) 
        : myAbility(myAbility), pCastersSelector(pCastersSelector), pars(pars), hasTargets(false) {}

      const vector<Target>& NeedTargets()
      {
        if ( !hasTargets )
          pCastersSelector->EnumerateTargets( *this, pars );
        hasTargets = true;
        return targets;
      }

      virtual void operator()(const Target &target)
      {
        if ( !target.IsUnitValid() )
          return;
        PFBaseUnit* unit = target.GetUnit();

        if ( myAbility->GetOwner() == unit )
          return;

        PFBaseUseState* abilityState = dynamic_cast<PFBaseUseState*>(unit->GetCurrentState());
        if ( !abilityState || !abilityState->GetDBDesc()  )
          return;

        if ( abilityState->GetDBDesc()->GetDBID() != myAbility->GetDBDesc()->GetDBID() )
          return;

        targets.push_back( abilityState->GetTarget() );
      }
    } coll( myAbility, pCastersSelector, pars  );

    //оптимизация: если pTargetSelector не нашел целей - не запускаем pCastersSelector

    float minDist = RetrieveParam( GetDB().minDistBetweenTargets, pars, 0.f );
    struct Filter : public ITargetAction, public NonCopyable
    {
      DumpTargetWrapper action;
      float minDist2;
      Collector& coll;

      Filter( DumpTargetWrapper action, Collector& coll, float minDist ) : action(action), coll(coll), minDist2(minDist*minDist) {}
      virtual void operator()(const Target &target)
      {
        const vector<Target>& targets = coll.NeedTargets();

        if ( PFLogicObject* pObj = target.GetObject() )
        {
          for ( int i = 0; i < targets.size(); ++i )
            if ( pObj == targets[i].GetObject().GetPtr() )
              return;
        }
        else 
        {
          CVec3 pos = target.AcquirePosition();
          for ( int i = 0; i < targets.size(); ++i )
            if ( fabs2( pos - targets[i].AcquirePosition() ) <= minDist2 )
              return;
        }
        action( target );
      }
    } filter( DumpTargetWrapper(this,action), coll, minDist );

    pTargetSelector->EnumerateTargets( filter, pars );

  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFDamagingLinksTargetSelector::PFDamagingLinksTargetSelector(NDb::DamagingLinksTargetSelector const &db, PFWorld* world)
    : DBLinker(db, world)
  {
    if (GetDB().linkEndsSelector)
      pLinkEndsSelector = GetDB().linkEndsSelector->Create( world );
    if (GetDB().linkTargetsSelector)
      pLinkTargetsSelector = GetDB().linkTargetsSelector->Create( world );
  }

  inline CVec2 Normalize( const CVec2 &vec ) { CVec2 ret(vec); Normalize( &ret ); return ret; }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFDamagingLinksTargetSelector::FindTarget(const RequestParams &pars, Target &target)
  {
    if (!pLinkEndsSelector || !pLinkTargetsSelector )
      return false;

    float radius = RetrieveParam( GetDB().moveRange, pars, 0.f );
    if ( radius <= 0.f )
      return false;

    float minRadius2 = RetrieveParam( GetDB().minRangeFromLinkEnds, pars, 0.f );
    minRadius2 *= minRadius2;
    float maxRadius2 = RetrieveParam( GetDB().maxRangeFromLinkEnds, pars, 0.f );
    maxRadius2 *= maxRadius2;

    float angleStep = 5.f / (FP_2PI * radius);

    vector<CVec2> linkEnds;
    struct PositionCollector : public ITargetAction, public NonCopyable
    {
      vector<CVec2>& positions; 
      CVec2 ownerPos;
      PositionCollector(vector<CVec2>& _positions, const CVec2& _ownerPos ) : positions(_positions), ownerPos(_ownerPos){}
      virtual void operator()(const Target &target)
      { 
        CVec2 p = target.AcquirePosition().AsVec2D();
        if ( fabs( ownerPos - p ) > EPS_VALUE )
          positions.push_back( p );
      }
    };
    struct TargetsCounter : public ITargetAction, public NonCopyable
    {
      int targets;
      TargetsCounter() : targets(0){}
      virtual void operator()(const Target &target)
      { ++targets;}
    };

    CVec2 ownerPoint = pars.pRequester->AcquirePosition().AsVec2D();
    {
      PositionCollector f(linkEnds, ownerPoint);
      pLinkEndsSelector->EnumerateTargets( f, pars );
    }

    if ( linkEnds.empty() )
      return false;

    CVec2 center = ownerPoint;
    for ( int i = 0; i < linkEnds.size(); ++i )
      center += linkEnds[i];
    center /= linkEnds.size() + 1; // center point between link ends and me

    float bestTargetWeight = 0.f;
    float bestSectorAngle = 0.f;
    int maxTargets = 0.f;

    Target destPoint;
    RequestParams destPars( pars.pOwner, pars.pMiscPars, destPoint, pars.condition );

    for ( float angle = 0.f; angle < FP_2PI; angle += angleStep )
    {
      CVec2 curPoint = ownerPoint + CVec2( radius * sin(angle), radius * cos(angle) );
      
      destPoint.SetPosition( CVec3( curPoint, 0.f ) );
      TargetsCounter f;
      pLinkTargetsSelector->EnumerateTargets( f, destPars );
     
      float weight = f.targets;

      // if target outside of ranges - give penalty
      for ( int i = 0; i < linkEnds.size(); ++i )
      {
        float d2 = fabs2( curPoint - linkEnds[i] );
        if ( d2 > maxRadius2 || d2 < minRadius2 )
          weight -= 1.7f;
        else
          weight -= 0.7f * fabs( d2 - ( maxRadius2 + minRadius2 ) / 2) / ( ( maxRadius2 - minRadius2 ) / 2 );
      }

      // bonus for increasing dist from line between others
      if ( linkEnds.size() > 1 )
      {
        CSegment seg( linkEnds[0], linkEnds[1] );
        weight -= 0.3 * Max( 1.f - sqr( seg.GetDistToPoint( curPoint ) ) / minRadius2, 0.f );
      }
      // bonus for moving radially relative to center pooint
      weight += 0.5f *( 1.f - fabs( Normalize( center - ownerPoint ) * Normalize( curPoint - ownerPoint ) ) );

      if ( weight > bestTargetWeight )
      {
        bestTargetWeight = weight;
        bestSectorAngle = angle; 
        maxTargets = f.targets;
      }
    }

    if ( maxTargets <= 0 )
      return false;

    CVec2 resPos = ownerPoint + CVec2( radius * sin(bestSectorAngle), radius * cos(bestSectorAngle) );
    //if ( maxTargets > 0 )
    //  DebugTrace(NStr::StrFmt("Best ang: %.3f (sector %.3f+%d) targets=%d", resAngle, bestSectorAngle, bestSectorLen, maxTargets) );

    target.SetPosition( CVec3( resPos, 0.f ) );
    DUMP_SELECTOR_TARGET(target)

    return true;
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace NWorld

REGISTER_WORLD_OBJECT_NM(PFMaximizingTargetSelector       , NWorld);
REGISTER_WORLD_OBJECT_NM(PFDelayTargetSelector            , NWorld);
REGISTER_WORLD_OBJECT_NM(PFCheckConditionTargetSelector   , NWorld);
REGISTER_WORLD_OBJECT_NM(PFNotTargetOfSameAbilitySelector , NWorld);
REGISTER_WORLD_OBJECT_NM(PFDamagingLinksTargetSelector , NWorld);
