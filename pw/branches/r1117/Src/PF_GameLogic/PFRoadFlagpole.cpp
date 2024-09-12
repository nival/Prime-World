#include "stdafx.h"

#include "PFAbilityData.h"
#include "PFAdvMapObject.h"
#include "PFClientFlagpole.h"
#include "PFRoadFlagpole.h"
#include "PFTargetSelector.h"
#include "PFWorldNatureMap.h"
#include "TileMap.h"
#include "SessionEventType.h"
#include "PFStatistics.h"
#include "PFMaleHero.h"
#include "PFClientHero.h"



namespace NWorld
{
  StaticArray<PFRoadFlagpole::RoadRing, PFRoadFlagpole::NUM_ROADS> PFRoadFlagpole::s_roads;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  unsigned int OwnerListener::OnEvent( const PFBaseUnitEvent *event )
  {
    if ( IsValid( listener ) )
      listener->OnEvent( event );
    return 0;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFRoadFlagpole::PFRoadFlagpole(PFWorld *pWorld, const NDb::AdvMapObject &_dbObject)
    : PFFlagpole( pWorld, _dbObject )
  {
    const NDb::Flagpole* db = dynamic_cast<const NDb::Flagpole*>(_dbObject.gameObject.GetPtr());
    NI_VERIFY( db, "Need gameObject to create Flagpole!", return; );

    needFindOwners = IsValid( db->ownerTowers );

    PFWorldNatureMap *pWorldNatureMap = pWorld->GetNatureMap();
    pWorldNatureMap->GetNatureSegment(GetPosition().AsVec2D(), natureRoad, natureSegment);
    NI_ASSERT( 0 <= natureRoad && natureRoad < NDb::KnownEnum<NDb::ENatureRoad>::sizeOf, "Wrong road index" );

    PFRoadFlagpole *pNext = s_roads[natureRoad].first();
    PFRoadFlagpole *pLast = s_roads[natureRoad].last();
    while (NULL != pNext && pLast != pNext && pNext->natureSegment < natureSegment)
      pNext = RoadRing::next(pNext);
    if (NULL != pNext)
      RoadRing::insertBefore(this, pNext);
    else
      s_roads[natureRoad].addLast(this);
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFRoadFlagpole::Reset()
  {
    //Call to FindOwners is disabled here, because it leads to async
    //const NDb::Flagpole* db = static_cast<const NDb::Flagpole*>( DbUnitDesc() );
    //if ( IsValid( db->ownerTowers ) )
    if ( needFindOwners )
      FindOwners();
    PFFlagpole::Reset();
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFRoadFlagpole::CanRaise( const NDb::EFaction _faction ) const
  {
    if ( !IsNeutral() )
    {
      return false;
    }

    if ( IsRising() )
    {
      return false;
    }

    if ( !IsOutermost( _faction ) )
    {
      return false;
    }

    return ( !IsProtectedByTower(faction) || ( GetOwnersFaction() == _faction ) );
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFRoadFlagpole::OnRaise( NDb::EFaction _faction, PFBaseUnit * unitWhoRaised )
  {
    PFFlagpole::OnRaise( _faction, unitWhoRaised );

    PFWorldNatureMap* natureMap = GetWorld()->GetNatureMap();
    int resultSegment = natureSegment;
    if ( this == GetLastFlagpole( faction, natureRoad ) )
    {
      // This flagpole is closest to enemy base.
      resultSegment = ( faction == NDb::FACTION_FREEZE ) ? natureMap->GetNumSegments() : 0;
    }

    natureMap->SetDesiredPosition( faction, natureRoad, resultSegment );
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFRoadFlagpole::OnDropFlag(PFBaseUnit * unitWhoDropped)
  {
    NDb::EFaction oldFaction = faction;

    PFFlagpole::OnDropFlag(unitWhoDropped);

    PFWorldNatureMap* natureMap = GetWorld()->GetNatureMap();
    if ( natureMap && oldFaction != NDb::FACTION_NEUTRAL )
    {
      int resultSegment = 0;

      if ( const PFRoadFlagpole* prev = (const PFRoadFlagpole*)GetPrevFlagpole( oldFaction ) )
      {
        resultSegment = prev->natureSegment;
      }
      else 
      {
        // This flagpole is closest to enemy base.
        resultSegment = ( oldFaction == NDb::FACTION_FREEZE ) ? 0 : natureMap->GetNumSegments();
      }
      natureMap->SetDesiredPosition( oldFaction, natureRoad, resultSegment );
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFRoadFlagpole::OnEvent( const PFBaseUnitEvent *event )
  {
    if ( event->GetType() == NDb::BASEUNITEVENT_DEATH )
    {
      if ( !IsProtected() )
      {
        UpdateVulnerable();
      }
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFRoadFlagpole::IsOutermost( const NDb::EFaction _faction ) const
  {
    if ( !IsNeutral() )
    {
      return false;
    }

    const PFFlagpole* prev = PFFlagpole::GetPrevFlagpole( _faction);

    return prev == 0 || prev->GetFaction() == _faction;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFRoadFlagpole::IsProtectedByTower( const NDb::EFaction _faction ) const
  {
    if ( GetOwnersFaction() == NDb::FACTION_NEUTRAL )
    {
      return false;
    }

    if ( GetOwnersFaction() == faction )
    {
      return true;
    }

    if ( IsNeutral() )
    {
      return ( GetOwnersFaction() != _faction );
    }

    NI_ALWAYS_ASSERT( "Flagpole is behind an enemy tower!" );
    return false;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFRoadFlagpole::IsProtectedByNext() const
  {
    if ( IsNeutral() )
      return false;

    const PFFlagpole* next = PFFlagpole::GetNextFlagpole( faction );
    return next != 0 && next->GetFaction() == faction;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFFlagpole* PFRoadFlagpole::GetPrevFlagpole( NDb::EFaction _faction )
  {
    if ( GetFirstFlagpole( _faction,natureRoad ) == this )
      return 0;
    return ( _faction == NDb::FACTION_FREEZE ) ? RoadRing::prev( this ) : RoadRing::next( this );
  }

  PFFlagpole* PFRoadFlagpole::GetNextFlagpole( NDb::EFaction _faction )
  {
    if ( GetLastFlagpole( _faction, natureRoad ) == this )
      return 0;
    return ( _faction == NDb::FACTION_FREEZE ) ? RoadRing::next( this ) : RoadRing::prev( this );
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFRoadFlagpole::Step(float dtInSeconds)
  {
    NI_PROFILE_FUNCTION;

    if (!PFFlagpole::Step(dtInSeconds))
      return false;

    if ( needFindOwners )
      FindOwners();

    return true;
  }

  void PFRoadFlagpole::OnDestroyContents()
  {
    RoadRing::safeRemove(this);
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFRoadFlagpole::LogFlagEvent( NDb::EFaction _faction, PFBaseUnit * unit, bool raised )
  {
    StatisticService::RPC::SessionEventInfo flagParams;
    flagParams.intParam1 = _faction;
    flagParams.intParam2 = natureRoad;
    flagParams.intParam3 = natureSegment;

    if (unit)
    {
      if (unit->IsTrueHero())
      {
        PFBaseHero * hero = static_cast<PFBaseHero*>(unit);
        flagParams.intParam4 = hero->GetStatisticsUid();
      }
      else
      {
        flagParams.intParam5 = unit->DbUnitDesc()->GetDBID().GetHashKey();
      }
    }

    GetWorld()->GetIAdventureScreen()->LogWorldSessionEvent( raised? SessionEventType::FlagPoleRaised : SessionEventType::FlagPoleDropped, flagParams );
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFRoadFlagpole::FindOwners()
  {
    for ( int i = 0; i < listeners.size(); i++ )
    {
      listeners[i]->Unregister();
    }

    owners.clear();
    listeners.clear();
    struct Enumerator : public ITargetAction
    {
      vector<CPtr<PFBaseUnit>>& owners;
      Enumerator( vector<CPtr<PFBaseUnit>>& _owners ) : owners( _owners ) { }
      virtual void operator()( const Target &target )
      {
        owners.push_back( target.GetUnit() );
      }
    private:
      void operator=( const Enumerator& ) { }
    } enumerator( owners );

    const NDb::Flagpole* db = static_cast<const NDb::Flagpole*>( DbUnitDesc() );
    CObj<PFTargetSelector> ownersSelector = db->ownerTowers->Create( 0 );
    PFTargetSelector::RequestParams params( this, NULL, Target( CPtr<PFBaseUnit>( this ) ) );
    ownersSelector->EnumerateTargets( enumerator, params );
    needFindOwners = false;
    for( vector<CPtr<PFBaseUnit>>::iterator it = owners.begin(), end = owners.end(); it != end; ++it )
      listeners.push_back( new OwnerListener( this, *it )  );
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  NDb::EFaction PFRoadFlagpole::GetOwnersFaction() const
  {
    for( vector<CPtr<PFBaseUnit>>::const_iterator it = owners.begin(), end = owners.end(); it != end; ++it )
    {
      if ( IsUnitValid( *it ) )
      {
        return (*it)->GetFaction();
      }
    }
    return NDb::FACTION_NEUTRAL;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// static functions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFFlagpole* PFRoadFlagpole::GetFirstFlagpole( const NDb::EFaction _faction, const NDb::ENatureRoad _natureRoad )
  {
    NI_DATA_VERIFY( (unsigned int)_natureRoad < s_roads.capacity(), 
      NStr::StrFmt( "Wrong nature road index: %d (0-%d available)", _natureRoad, s_roads.capacity() ), return 0 );
    NI_DATA_VERIFY( !s_roads[_natureRoad].empty(), 
      NStr::StrFmt( "No flagpoles on nature road: %d", _natureRoad ), return 0 );

    RoadRing& road = s_roads[_natureRoad];
    return ( _faction == NDb::FACTION_FREEZE ) ? road.first() : RoadRing::prev( road.last() );
  }

  PFFlagpole* PFRoadFlagpole::GetLastFlagpole( const NDb::EFaction _faction, const NDb::ENatureRoad _natureRoad )
  {
    NI_DATA_VERIFY( (unsigned int)_natureRoad < s_roads.capacity(), 
      NStr::StrFmt( "Wrong nature road index: %d (0-%d available)", _natureRoad, s_roads.capacity() ), return 0 );
    NI_DATA_VERIFY( !s_roads[_natureRoad].empty(), 
      NStr::StrFmt( "No flagpoles on nature road: %d", _natureRoad ), return 0 );

    RoadRing& road = s_roads[_natureRoad];
    return ( _faction == NDb::FACTION_FREEZE ) ? RoadRing::prev( road.last() ) : road.first();
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFRoadFlagpole::Attack( NDb::EFaction _faction, NDb::ENatureRoad _natureRoad, int count )
  {
    NI_VERIFY( _faction != NDb::FACTION_NEUTRAL, "Neutral faction can't attack", return );

    PFFlagpole* pFirst = GetFirstFlagpole( _faction, _natureRoad );
    PFFlagpole* pLast  = GetLastFlagpole(  _faction, _natureRoad );

    if ( !IsValid( pFirst ) || !IsValid( pLast ) )
    {
      return;
    }

    PFFlagpole* firstNotOur = pFirst;
    for ( ; firstNotOur->GetFaction() == _faction; firstNotOur = firstNotOur->GetNextFlagpole( _faction ) )
    {
      if ( firstNotOur == pLast )
      {
        return;
      }
    }

    NI_VERIFY( count >= 0, "You should provide positive count value", return );
    for ( ; count > 0; count-- )
    {
      if ( !firstNotOur->IsNeutral() )
      {
        firstNotOur->OnDropFlag( 0 );
      }

      firstNotOur->OnStartRaise( GetTeamId(_faction), 0.0f );
      firstNotOur->OnRaise( _faction, 0 );
      firstNotOur = firstNotOur->GetNextFlagpole( _faction );

      if ( firstNotOur == s_roads[_natureRoad].last() )
      {
        return;
      }
    }
  }

  void PFRoadFlagpole::PushAll( vector<PFFlagpole*>* pFlagpoles )
  {
    for ( uint road = 0; road < s_roads.capacity(); ++road )
    {
      PFRoadFlagpole *pNext = s_roads[road].first();
      PFRoadFlagpole *pLast = s_roads[road].last();
      while (NULL != pNext && pLast != pNext )
      {
        pFlagpoles->push_back( pNext );
        pNext = RoadRing::next(pNext);
      }
    }
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING
  namespace
  {
    static bool g_showFlagpole = false;
  }

  class PFFlagpoleDebug : public PFBaseUnitDebug
  {
    OBJECT_METHODS(0xB76B480, PFFlagpoleDebug);
  public:
    PFFlagpoleDebug(CPtr<PFBaseUnit> const &pUnit) : PFBaseUnitDebug (pUnit) { }
  protected:
    PFFlagpoleDebug() {}

    virtual bool Process(Render::IDebugRender* pRender)
    {
      if ( PFBaseUnitDebug::Process(pRender) )
        return true;
      if (g_showFlagpole)
      {
        PFRoadFlagpole const *pFlagpole = dynamic_cast<PFRoadFlagpole const*>(pOwner.GetPtr());
        char buffer[256];
        sprintf_s(buffer, "%d/%d", (int)pFlagpole->natureRoad, pFlagpole->natureSegment );
        pRender->DrawText3D(buffer, pFlagpole->GetPosition(), 14, Render::Color(255, 255, 255));
      }
      return false;
    }
  };

  CObj<NDebug::DebugObject> PFRoadFlagpole::CreateDebugObject()
  {
    //return CObj<NDebug::DebugObject>(0);
    return CObj<NDebug::DebugObject>(new PFFlagpoleDebug(this));
  }

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
REGISTER_WORLD_OBJECT_NM(PFRoadFlagpole, NWorld);
REGISTER_WORLD_OBJECT_NM(OwnerListener, NWorld);

REGISTER_DEV_VAR("show_flagpole",   NWorld::g_showFlagpole,   STORAGE_NONE);
