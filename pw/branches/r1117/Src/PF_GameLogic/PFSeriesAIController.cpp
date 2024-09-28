#include "stdafx.h"
#include "PFMaleHero.h"
#include "PFTalent.h"
#include "PFAIWorld.h"
#include "PFGlyph.h"
#include "PFHeroStates.h"

#include "PFSeriesAIController.h"
#include "PFAIStates.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{

  PFSeriesAIController::PFSeriesAIController( PFBaseHero* hero, NCore::ITransceiver* transceiver )
    : PFBaseAIController(hero, transceiver)
    , talents( AiConst::ACTIVATE_TALENT_DELAY(), AiConst::USE_TALENT_DELAY() )
    , glyphs( AiConst::MOVE_START_DELAY() * 2 )
    , signals( AiConst::MOVE_START_DELAY() )
    , signalsEnabled(false)
    , isLvlUpAvailable(true)
  {
  }

  PFSeriesAIController::PFSeriesAIController( PFBaseHero* hero, NCore::ITransceiver* transceiver, bool lvlUpAvailable )
    : PFBaseAIController(hero, transceiver)
    , talents( AiConst::ACTIVATE_TALENT_DELAY(), AiConst::USE_TALENT_DELAY() )
    , glyphs( AiConst::MOVE_START_DELAY() * 2 )
    , signals( AiConst::MOVE_START_DELAY() )
    , signalsEnabled(false)
    , isLvlUpAvailable(lvlUpAvailable)
  {
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void PFSeriesAIController::Step( float timeDelta )
  {
    PFBaseAIController::Step(timeDelta);

    if ( GetHero()->IsInChannelling() || GetHero()->IsDead() )
      return;

    PFFsm::FsmStep( timeDelta );

    if (isLvlUpAvailable)
      talents.ActivateTalents( GetHelper() );
    
    signals.Step( GetHelper(), talents );
    if ( signals.IsActive() )
      return;

    if ( glyphs.TryUseGlyphs( GetHelper() ) )
      return;

    if ( currentPart )
      currentPart->Step();
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSeriesAIController::OnDie()
{
  signals.Cleanup();
  Cleanup();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFSeriesAIController::OnRespawn()
{
  if ( currentPart )
    currentPart->Restart();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFSeriesAIController::OnMinimapSignal( const Target& target, bool dedicated )
  {
    if ( !signalsEnabled )
      return false;

    if ( !dedicated )
    {
      if ( signals.IsActive() )
        return false;
      if ( !currentPart->CanReactToSignal( target ) )
        return false ;
    }
    signals.Activate( GetHelper(), target );

    return true;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFSeriesAIController::StartPushPath( const vector<CVec2>& path )
  {
    Cleanup();
    currentPart = AutoPtr<ControllerPart>( new PushLineControllerPart( this, path ) );
  }

  void PFSeriesAIController::StartSupport( PFBaseUnit* pMaster )
  {
    Cleanup();
    currentPart = AutoPtr<ControllerPart>( new SupportControllerPart( this, pMaster ) );
  }

  void PFSeriesAIController::StartGuardPoint( const CVec2& point, float radius, float lookToAreaRadius )
  {
    Cleanup();
    currentPart = AutoPtr<ControllerPart>( new GuardControllerPart( this, point, radius, lookToAreaRadius ) );
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PushLineControllerPart
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PushLineControllerPart::Restart()
  {
    active = false;
  }

  void PushLineControllerPart::Step()
  {
    if ( owner->GetHero()->IsMounted() && !owner->GetHero()->CanControlMount() )
      return;

    if ( path.empty() )
      return;

    if ( active )
    {
      owner->talents.UseTalents( owner->GetHelper() );
    }
    else 
    {
      DBG( "AI queue: walk path to ( %f, %f )", path.back().x, path.back().y );
      active = true;
      owner->PushState( new AIMoveByLineState( owner, path, false, 0 ) );
    }

  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // SupportControllerPart
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void SupportControllerPart::Restart()
  {
    
  }

  void SupportControllerPart::Step()
  {
    if ( owner->GetCurrentState() == NULL )
    {
      owner->PushState( new AIGoToObjectState(owner, pMaster) );
    }
    owner->talents.UseTalents( owner->GetHelper() );

  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // GuardControllerPart
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void GuardControllerPart::Restart()
  {
    active = false;
    commandDelay = 0;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class LongTargetFinder : NonCopyable
  {
  public:
    LongTargetFinder(PFBaseUnit &owner, const NDb::UnitTargetingParameters &unitPars, float maxRange)
      : owner(owner)
      , maxWeight(-100000.0f)
      , unitPars(unitPars)
      , maxRange(maxRange)
    {
    }
    const CPtr<PFBaseUnit>& GetTarget() { return pTarget; }

    void operator ()(PFBaseUnit &unit)
    {
      const CPtr<PFBaseUnit> pUnit = &unit;

      // need to check distance between target and owner
      if ( !unit.IsVisibleForEnemy( owner.GetFaction() ) )
        return;
  
      const int unitTypeMask = NDb::SPELLTARGET_ALLWOBUILDINGS;
      bool checkFogOfWar = (unitTypeMask & (1L << unit.GetUnitType())) == 0;

      if ( !owner.CanSelectTarget(&unit, checkFogOfWar) )
        return;

      float weight = owner.GetTargetWeight( pUnit, unitPars, NULL );
      if (weight > maxWeight)
      {
        maxWeight = weight;
        pTarget   = &unit;
      }
    }

  private:
    const PFBaseUnit                &owner;
    float                           maxWeight;
    CPtr<PFBaseUnit>                pTarget;
    const NDb::UnitTargetingParameters  &unitPars;
    const float                     maxRange;
  };

  void GuardControllerPart::Step()
  {
    if ( commandDelay > 0 )
    {
      --commandDelay;
      return;
    }
    if ( returnDelay > 0 )
      --returnDelay;

    PFBaseMaleHero *pHero = owner->GetHelper().pUnit;
    PFAIWorld *pAIWorld = pHero->GetWorld()->GetAIWorld();

    CVec2 pos = pHero->GetPos();

    owner->talents.UseTalents( owner->GetHelper() );

    if ( !owner->GetCurrentState() )
    {
      if ( !pHero->GetCurrentTarget() )
      {
        PFBaseUnit* unit = FindTargetInGuardArea( pAIWorld, pHero );
        if ( unit )
        {
          owner->PushState( new AIAttackUnitState( owner, unit ) );
          commandDelay = AiConst::MOVE_START_DELAY();
        }
        else if ( returnDelay <= 0 && fabs2( pos - point ) > fabs2(radius/2) )
        {
          owner->PushState( new AIMoveToState(owner, point, radius/4 ) );
          commandDelay = AiConst::MOVE_START_DELAY();
        }
      }
    }
    else 
    {
      returnDelay = 30;

      if ( lookToAreaRadius > radius && fabs2( pos - point ) > fabs2(lookToAreaRadius) )
      {
        PFBaseUnit* unit = FindTargetInGuardArea( pAIWorld, pHero );
        if ( unit && fabs2( pos - unit->GetPos() ) > fabs2( pHero->GetTargetingRange() ) )
        {
          owner->PushState( new AIAttackUnitState( owner, unit ) );
          commandDelay = AiConst::MOVE_START_DELAY();
        }
      }
    }
  }

  PFBaseUnit* GuardControllerPart::FindTargetInGuardArea( PFAIWorld * pAIWorld, PFBaseMaleHero * pHero )
  {
    float searchRadius = radius + pAIWorld->GetMaxObjectSize() * 0.5f;
    int targetTypesToFind = NDb::SPELLTARGET_ALL | NDb::SPELLTARGET_VULNERABLETARGETSONLY | ( pHero->CanAttackFlying() ? NDb::SPELLTARGET_FLYING : 0 ) ;
    LongTargetFinder targetFinder( *pHero, pHero->GetTargetingParams(), radius );
    pAIWorld->ForAllUnitsInRange( CVec3( point, 0 ), searchRadius, targetFinder, UnitMaskingPredicate( pHero->GetOppositeFactionFlags(), targetTypesToFind, pHero ) );

    return targetFinder.GetTarget();
  }

  /////////////////////////////////////////////////////////////////////////////
  // GlyphPart
  /////////////////////////////////////////////////////////////////////////////

  bool GlyphPart::TryUseGlyphs( PFAIHelper &aiHelper )
  {
    // process delay
    if ( useTimeLeft > 0 )
    {
      --useTimeLeft;
      return true;
    }

    //wait for pickup finished
    if ( IPFState* curState = aiHelper.pUnit->GetCurrentState() )
    {
      if ( dynamic_cast<PFHeroPickupObjectState*>(curState) )
      {
        inactiveTimeLeft = 5; //wait before next pickup attempt
        return true;
      }
    }

    // process inactive delay
    if ( inactiveTimeLeft > 0 )
    {
      --inactiveTimeLeft;
      return false;
    }

    if ( aiHelper.pUnit->IsMoving() || aiHelper.pUnit->CheckFlag( NDb::UNITFLAG_FORBIDMOVE ) ||  aiHelper.pUnit->CheckFlag( NDb::UNITFLAG_FORBIDPICK ) )
      return false;

    struct Func
    {
      vector<PFGlyph*> glyphs;
      void operator()(PFLogicObject &object)
      {
        CDynamicCast<PFGlyph> glyph(&object);
        if ( glyph.GetPtr() )
          glyphs.push_back( glyph ); 
      }

    } f;

    UnitMaskingPredicate pred( 1L << NDb::FACTION_NEUTRAL, NDb::SPELLTARGET_PICKUPABLE );
    aiHelper.GetWorld()->GetAIWorld()->ForAllObjectsInRange( aiHelper.pUnit->GetPosition(), aiHelper.pUnit->GetVisibilityRange(), f, pred );

    if ( f.glyphs.empty() )
      return false;

    struct GlyphIsLess {
      GlyphIsLess( PFBaseUnit* pUnit ) {center = pUnit->GetPos();}
      CVec2 center;
      inline bool operator()( const PFGlyph* a, const PFGlyph* b ) const 
      {  return fabs2( a->GetPos() - center ) < fabs2( b->GetPos() - center ); } 
    };
    sort(f.glyphs.begin(), f.glyphs.end(), GlyphIsLess(aiHelper.pUnit) );

    PFGlyph* bestGlyph = 0;
    float bestValue = 0.f;
    for ( vector<PFGlyph*> ::iterator it = f.glyphs.begin(); it != f.glyphs.end(); ++it )
    {
      NDb::EGlyph id = (*it)->GetDBDesc()->id;
      float val = 0.f;
      if ( id == NDb::GLYPH_LIFERESTORER )
        val = EstimateLifeRestorer( aiHelper );
      DBG( "Found glyph: %s, estimate=%f", NDb::EnumToString(id), val );
      if ( val > bestValue )
      {
        bestValue = val;
        bestGlyph = (*it);
      }
    }
    if ( bestGlyph )
    {
      aiHelper.PickupObject( bestGlyph );
      DBG( "Picking glyph: %s", NDb::EnumToString(bestGlyph->GetDBDesc()->id) );
      useTimeLeft = useDelay;
      inactiveTimeLeft = 0;
      return true;
    }

    inactiveTimeLeft = 5;

    return false;
  }
static const float GLYPH_LIFERESTORER_HUMANHERO_MIN_HEALTH = 0.6f;
static const float GLYPH_LIFERESTORER_MAX_HEALTH_NON_COMBAT = 0.5f;
static const float GLYPH_LIFERESTORER_MAX_HEALTH_COMBAT = 0.1f;

  float GlyphPart::EstimateLifeRestorer( PFAIHelper & aiHelper )
  {
    vector<PFBaseHero*> humanHeroes;
    GetHumanHeroesNear( &humanHeroes, aiHelper );

    for ( vector<PFBaseHero*>::iterator it = humanHeroes.begin(); it != humanHeroes.end(); ++it )
    {
      if ( (*it) != aiHelper.pUnit && (*it)->GetHealthPercent() < GLYPH_LIFERESTORER_HUMANHERO_MIN_HEALTH )
        return 0.f;
    }

    float lifeCoef = GLYPH_LIFERESTORER_MAX_HEALTH_NON_COMBAT;
    if ( aiHelper.pUnit->GetCurrentTarget() )
      lifeCoef = GLYPH_LIFERESTORER_MAX_HEALTH_COMBAT;

    if ( aiHelper.pUnit->GetLife() < aiHelper.pUnit->GetMaxLife() * lifeCoef )
      return 10.f;


    return 0.f;
  }

  void GlyphPart::GetHumanHeroesNear( vector<PFBaseHero*>* humanHeroes, PFAIHelper & aiHelper )
  {
    /*
    struct Func
    {
      vector<PFGlyph*>* humanHeroes;
      Func( vector<PFGlyph*>* _humanHeroes ) : humanHeroes(_humanHeroes ) {}
      void operator()(PFBaseUnit &object)
      {
        CDynamicCast<PFBaseMaleHero> hero(&object);
        if ( hero.GetPtr() )
          humanHeroes->push_back( hero ); 
      }
    } f(humanHeroes);

    UnitMaskingPredicate pred( 1L << aiHelper.pUnit->GetFaction(), NDb::SPELLTARGET_HEROMALE );
    aiHelper.GetWorld()->GetAIWorld()->ForAllObjectsInRange( aiHelper.pUnit->GetPosition(), aiHelper.pUnit->GetVisibilityRange() * 2, f, pred );
    */
    int nPlayers = aiHelper.GetWorld()->GetPlayersCount();
    for ( int i = 0; i < nPlayers; ++i )
    {
      PFPlayer* player = aiHelper.GetWorld()->GetPlayer( i );
      if ( player->IsBot() )
        continue;
      PFBaseHero * hero = player->GetHero();
      if ( !hero || hero->GetFaction() != aiHelper.pUnit->GetFaction() )
        continue;
      
      if ( hero->IsDead() )
        continue;

      humanHeroes->push_back( hero );
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  // SignalPart
  /////////////////////////////////////////////////////////////////////////////
  void SignalPart::Activate( PFAIHelper &aiHelper, const Target& _target )
  { 
    target = _target;
    active = true;

#ifndef _SHIPPING
    debugName = NStr::StrFmt("Signal %s -> (%d,%d)", NStr::ToMBCS(aiHelper.pUnit->GetPlayerName()).c_str(), target.AcquirePosition().x, target.AcquirePosition().y );
#endif
    DevTrace( "%s : Activated", debugName.c_str() );

    if ( !ConsiderUsePortal( aiHelper.pUnit ) )
    {
      DevTrace( "%s : Start move", debugName.c_str() );
      aiHelper.MoveTo( target.AcquirePosition().AsVec2D() );
    }
    else 
    {
      DevTrace( "%s : Teleporting", debugName.c_str() );
      aiHelper.UsePortal( target );
    }

    lastStopPos = aiHelper.pUnit->GetPosition();
    movingTo = true;
    useTimeLeft = useDelay;
  }

  void SignalPart::Step( PFAIHelper &aiHelper, TalentPart& talents )
  {
    if ( !active )
      return;

    // process delay
    if ( useTimeLeft > 0 )
    {
      --useTimeLeft;
      return;
    }
    PFBaseMaleHero* pUnit = aiHelper.pUnit;

    if ( movingTo )
    {
      if ( ConsiderUsePortal( pUnit ) )
      {
        DevTrace( "%s : Teleporting", debugName.c_str() );
        aiHelper.UsePortal( target );
        useTimeLeft = useDelay;
      }
      else if ( fabs( pUnit->GetPosition() - target.AcquirePosition() ) < pUnit->GetTargetingRange() )
      {
        DevTrace( "%s : At position", debugName.c_str() );
        movingTo = false;
      }
      else if ( pUnit->IsIdle() )
      {
        if ( fabs( lastStopPos - pUnit->GetPosition() ) < 4.f )
        {
          DevTrace( "%s : Stuck, end move", debugName.c_str() );
          movingTo = false;
        }
        else 
        {
          DevTrace( "%s : Repeat move", debugName.c_str() );
          lastStopPos = aiHelper.pUnit->GetPosition();
          aiHelper.MoveTo( target.AcquirePosition().AsVec2D() );
          useTimeLeft = useDelay;
        }
      }
    }
    else 
    {
      talents.UseTalents( aiHelper );
      PFBaseUnit* pEnemy = FindEnemyNear( pUnit );
      if ( pEnemy )
      {
        if ( pUnit->IsIdle() )
        {
          DevTrace( "%s : Attack", debugName.c_str() );
          aiHelper.Attack( pEnemy );
        }
        useTimeLeft = useDelay;
      }
      else
      {
        struct FlagFinder
        {
          PFFlagpole*  pFlagpole;
          NDb::EFaction faction;
          explicit FlagFinder(NDb::EFaction faction) : pFlagpole(0), faction(faction) {}
          void operator () ( NWorld::PFBaseUnit const& unit)
          {
            const PFFlagpole* pf = dynamic_cast<const PFFlagpole*>(&unit); 
            if ( pf )
            {
              if ( pf->IsNeutral() && !pf->CanRaise( faction ) )
                return;

              if ( !pf->IsNeutral() && ( pf->GetFaction() == faction || !pf->IsVulnerable() ) )
                return;

              pFlagpole = const_cast<PFFlagpole*>(pf);
            }
          } 
        } flagFinder( pUnit->GetFaction() );
        int targetTypesToFind = NDb::SPELLTARGET_FLAGPOLE;
        pUnit->GetWorld()->GetAIWorld()->ForAllUnitsInRange( pUnit->GetPosition(), pUnit->GetVisibilityRange(), flagFinder, UnitMaskingPredicate( pUnit->GetOppositeFactionFlags(), targetTypesToFind, pUnit ) );
        if ( flagFinder.pFlagpole )
        {
          DevTrace( "%s : Flag", debugName.c_str() );
          if ( flagFinder.pFlagpole->CanRaise( pUnit->GetFaction() ) )
          {
            aiHelper.RaiseFlag( flagFinder.pFlagpole );
            useTimeLeft = useDelay;
          }
          else if( flagFinder.pFlagpole->GetFaction() != pUnit->GetFaction() && pUnit->CanAttackTarget( flagFinder.pFlagpole ) )
          {
            aiHelper.Attack( flagFinder.pFlagpole );
            useTimeLeft = useDelay;
          }
        }
      }
      if ( useTimeLeft == 0 )
      {
        DevTrace( "%s : Done", debugName.c_str() );
        Cleanup();
      }
    }
  }

  bool SignalPart::IsEnemiesNear( PFBaseMaleHero* pUnit )
  {
    int targetTypesToFind = NDb::SPELLTARGET_ALL | NDb::SPELLTARGET_FLYING ;

    if ( pUnit->GetDamageTaken( 2.f ) > 0.f )
      return true;

    struct UnitCounter
    {
      int count;
      explicit UnitCounter() : count(0) {}
      void operator () ( NWorld::PFBaseUnit const& unit)
      {
        if( !unit.IsDead() && !unit.CheckFlag(NDb::UNITFLAG_FORBIDAUTOTARGETME) )
          ++count;
      } 
    } unitCounter;

    pUnit->GetWorld()->GetAIWorld()->ForAllUnitsInRange( pUnit->GetPosition(), pUnit->GetVisibilityRange(), unitCounter, UnitMaskingPredicate( pUnit->GetOppositeFactionFlags(), targetTypesToFind, pUnit ) );
  
    return unitCounter.count > 0;
  }

  bool SignalPart::ConsiderUsePortal( PFBaseMaleHero* pUnit )
  {
    bool isEnemiesNear = IsEnemiesNear( pUnit );
    bool portalReady = pUnit->GetPortal()->CanBeUsed() && (pUnit->GetPortal()->CheckCastLimitations( target ) == 0);
    float dist2Target = fabs( pUnit->GetPosition() - target.AcquirePosition() );
  
    return !isEnemiesNear && portalReady && dist2Target > pUnit->GetMoveSpeedMpS() * 5;
  }

  PFBaseUnit* SignalPart::FindEnemyNear( PFBaseMaleHero* pHero )
  {
    float searchRadius = pHero->GetVisibilityRange();
    int targetTypesToFind = NDb::SPELLTARGET_ALL | ( pHero->CanAttackFlying() ? NDb::SPELLTARGET_FLYING : 0 ) ;
    LongTargetFinder targetFinder( *pHero, pHero->GetTargetingParams(), searchRadius );
    pHero->GetWorld()->GetAIWorld()->ForAllUnitsInRange( pHero->GetPosition(), searchRadius, targetFinder, UnitMaskingPredicate( pHero->GetOppositeFactionFlags(), targetTypesToFind, pHero ) );

    return targetFinder.GetTarget();
  }

}
BASIC_REGISTER_CLASS(NWorld::PFSeriesAIController)