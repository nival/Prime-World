#include "stdafx.h"


#include "PFAbilityData.h"
#include "PFAdvMapObject.h"
#include "PFClientFlagpole.h"
#include "PFScriptedFlagpole.h"
#include "PFTargetSelector.h"
#include "PFWorldNatureMap.h"
#include "TileMap.h"
#include "SessionEventType.h"
#include "PFStatistics.h"
#include "PFMaleHero.h"
#include "PFClientHero.h"

namespace NWorld
{
  PFScriptedFlagpole::TGroups PFScriptedFlagpole::s_groups;
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFScriptedFlagpole::PFScriptedFlagpole(PFWorld *pWorld, const NDb::AdvMapObject &_dbObject)
    : PFFlagpole( pWorld, _dbObject )
    ,indexInGroup(0)
    ,isProtected(false)
  {
    const NDb::Flagpole* db = dynamic_cast<const NDb::ScriptedFlagpole*>(_dbObject.gameObject.GetPtr());
    NI_VERIFY( db, "Need gameObject to create ScriptedFlagpole!", return );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFScriptedFlagpole::Reset()
  {
    PFFlagpole::Reset();
    TryAddIntoGroups();
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFScriptedFlagpole::CanRaise( const NDb::EFaction _faction ) const
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

    return ( !isProtected || ( GetFaction() == _faction ) );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFScriptedFlagpole::OnRaise( NDb::EFaction _faction, PFBaseUnit * unitWhoRaised )
  {
    PFFlagpole::OnRaise( _faction, unitWhoRaised );
  }
  void PFScriptedFlagpole::OnDropFlag(PFBaseUnit * unitWhoDropped)
  {
    PFFlagpole::OnDropFlag(unitWhoDropped);
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFScriptedFlagpole::IsOutermost( const NDb::EFaction _faction ) const
  {
    if ( !IsNeutral() )
      return false;

    const PFFlagpole* prev = PFFlagpole::GetPrevFlagpole( _faction);
    return prev == 0 || !prev->IsNeutral();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFScriptedFlagpole::IsProtectedByTower( const NDb::EFaction _faction ) const
  {
    return isProtected;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFScriptedFlagpole::IsProtectedByNext() const
  {
    if ( IsNeutral() )
      return false;

    const PFFlagpole* next = PFFlagpole::GetNextFlagpole( faction );
    return next != 0 && next->GetFaction() == faction;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  PFFlagpole* PFScriptedFlagpole::GetPrevFlagpole( NDb::EFaction _faction )
  {
    if ( group.empty() )
      return 0;

    TGroups::const_iterator it = s_groups.find(group);
    NI_VERIFY( it != s_groups.end(), "Flagpole not in s_groups", return 0 );
    
    if ( indexInGroup <= 0 )
      return 0;

    return it->second[indexInGroup-1];
  }

  PFFlagpole* PFScriptedFlagpole::GetNextFlagpole( NDb::EFaction _faction )
  {
    if ( group.empty() )
      return 0;

    TGroups::const_iterator it = s_groups.find(group);
    NI_VERIFY( it != s_groups.end(), "Flagpole not in s_groups", return 0 );

    if ( indexInGroup >= (it->second.size()-1) )
      return 0;

    return it->second[indexInGroup+1];
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool PFScriptedFlagpole::Step(float dtInSeconds)
  {
    NI_PROFILE_FUNCTION;

    if (!PFFlagpole::Step(dtInSeconds))
      return false;
    return true;
  }

  void PFScriptedFlagpole::OnDestroyContents()
  {
    if ( group.empty() )
      return;

    TGroups::iterator it = s_groups.find(group);
    NI_VERIFY( it != s_groups.end(), "Flagpole not in s_groups", return );
    NI_VERIFY( it->second[indexInGroup] == this, "Flagpole not in s_groups", return );
    it->second[indexInGroup] = 0;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void PFScriptedFlagpole::LogFlagEvent( NDb::EFaction _faction, PFBaseUnit * unit, bool raised )
  {
    StatisticService::RPC::SessionEventInfo flagParams;
    flagParams.intParam1 = _faction;
    flagParams.intParam2 = 0;
    flagParams.strParam1 = NStr::ToUnicode(group);
    flagParams.intParam3 = indexInGroup;

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
  void PFScriptedFlagpole::TryAddIntoGroups()
  {
    if ( group.empty() )
      return;
    vector<CPtr<PFScriptedFlagpole>>& grp = s_groups[group];

    if ( grp.size() <= indexInGroup )
      grp.resize( indexInGroup + 1, this );
      
     if( grp[indexInGroup] != this )
       grp[indexInGroup] = this;
  }

  void PFScriptedFlagpole::CreateGroup( const vector<PFScriptedFlagpole*>& flagpoles, const string& name )
  {
    for ( int i = 0; i < flagpoles.size(); ++i )
    {
      PFScriptedFlagpole* pf = flagpoles[i];
      pf->group = name;
      pf->indexInGroup = i;
      pf->TryAddIntoGroups();
    }
  }

  int PFScriptedFlagpole::GetRaisedCountInGroup( const string& name )
  {
    TGroups::const_iterator it = s_groups.find(name);
    NI_VERIFY( it != s_groups.end(), NStr::StrFmt("ScriptedFlagpole group %s not found", name.c_str() ), return -1 );

    for ( int i = 0; i < it->second.size(); ++i )
    {
      if ( it->second[i]->IsNeutral() )
        return i;
    }
    return it->second.size();
  }
  void PFScriptedFlagpole::SetRaisedCountInGroup( const string& name, int count, PFBaseUnit* pWho )
  {
    TGroups::const_iterator it = s_groups.find(name);
    NI_VERIFY( it != s_groups.end(), NStr::StrFmt("ScriptedFlagpole group %s not found", name.c_str() ), return );

    const vector<CPtr<PFScriptedFlagpole>>& group = it->second;
    NI_VERIFY( count > 0 && count <= group.size(), NStr::StrFmt("ScriptedFlagpole raised count invalid (%d), should be 0..%d", count, group.size() ), return );

    for ( int i = 0; i < group.size(); ++i )
    {
      PFScriptedFlagpole* pole = group[i];
      if ( i < count && pole->IsNeutral() )
        pole->OnRaise( pWho->GetFaction(), pWho );
      else if ( i >= count && !pole->IsNeutral() )
        pole->OnDropFlag( pWho );
    }
  }

  void PFScriptedFlagpole::PushAll( vector<PFFlagpole*>* pFlagpoles )
  {
    for( TGroups::const_iterator it = s_groups.begin(); it != s_groups.end(); ++it )
    {
      for ( int i = 0; i < it->second.size(); ++i )
      {
        PFScriptedFlagpole* pole = it->second[i];
        pFlagpoles->push_back( pole );
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING
  namespace
  {
    static bool g_showFlagpole = false;
  }

  class PFScriptedFlagpoleDebug : public PFBaseUnitDebug
  {
    OBJECT_METHODS(0x9A9BA440, PFScriptedFlagpoleDebug);
  public:
    PFScriptedFlagpoleDebug(CPtr<PFBaseUnit> const &pUnit) : PFBaseUnitDebug (pUnit) { }
  protected:
    PFScriptedFlagpoleDebug() {}

    virtual bool Process(Render::IDebugRender* pRender)
    {
      if ( PFBaseUnitDebug::Process(pRender) )
        return true;

      PFScriptedFlagpole const *pFlagpole = dynamic_cast<PFScriptedFlagpole const*>(pOwner.GetPtr());
      char buffer[256];
      sprintf_s(buffer, "%s/%d", pFlagpole->group.c_str(), pFlagpole->indexInGroup );
      pRender->DrawText3D(buffer, pFlagpole->GetPosition(), 14, Render::Color(255, 255, 128));
      return false;
    }
  };

  CObj<NDebug::DebugObject> PFScriptedFlagpole::CreateDebugObject()
  {
    return CObj<NDebug::DebugObject>(new PFScriptedFlagpoleDebug(this));
  }
#endif
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

REGISTER_WORLD_OBJECT_NM(PFScriptedFlagpole, NWorld);


