#include "stdafx.h"

#include "AdventureScreen.h"
#include "AdventureScreenEvents.h"
#include "PFAchievement.h"
#include "PFAIWorld.h"
#include "PFCommonCreep.h"
#include "PFFactionStatistics.h"
#include "PFHero.h"
#include "PFTalent.h"
#include "PFNeutralCreep.h"
#include "PFStatistics.h"
#include "PFStatisticsStuff.h"
#include "PFConsumable.h"
//#include "PlayerData.h"
#include "SessionEventType.h"
#include "Terrain/Terrain.h"
#include "System/InlineProfiler.h"
#include "PFTriggerApplicator.h"

#include "../System/InlineProfiler.h"
#include "AnnouncementParams.h"
#include "System/StarForce/StarForce.h"
#include "PFBaseSpawner.h"
REGISTER_WORLD_OBJECT_NM(PFStatistics, NWorld)

namespace
{

DEV_VAR_STATIC bool g_uniqAwardOnly = true;
DEV_VAR_STATIC bool s_DbgEnableCheatNotice = true;

REGISTER_DEV_VAR( "cheat_ui_notice", s_DbgEnableCheatNotice, STORAGE_NONE );
REGISTER_DEV_VAR( "score_stat_uniqAwardOnly", g_uniqAwardOnly, STORAGE_NONE );

struct Killer
{
  Killer(const CPtr<NWorld::PFBaseUnit>& unit, const CPtr<NWorld::PFBaseUnit>& killer, float time) { pVictim = unit; pKiller = killer; curTime = time; }
  void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->OnKill(pVictim, pKiller, curTime); }

  CPtr<NWorld::PFBaseUnit> pVictim;
  CPtr<NWorld::PFBaseUnit> pKiller;
  float curTime;
};

struct Assister
{
  Assister(const CPtr<NWorld::PFBaseUnit>& unit, const CPtr<NWorld::PFBaseUnit>& killer, float time) { pVictim = unit; pKiller = killer; curTime = time; }
  void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->OnAssist(pVictim, pKiller, curTime); }

  CPtr<NWorld::PFBaseUnit> pVictim;
  CPtr<NWorld::PFBaseUnit> pKiller;
  float curTime;
};

struct TowerDestroyer
{
  TowerDestroyer(const CPtr<NWorld::PFTower>& tower) { pTower = tower; }
  void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->OnTowerDestroy(pTower); }

  CPtr<NWorld::PFTower> pTower;
};

struct TowerAssister
{
  TowerAssister(const CPtr<NWorld::PFTower>& tower) { pTower = tower; }
  void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->OnTowerAssist(pTower); }

  CPtr<NWorld::PFTower> pTower;
};

struct ApplApplier
{
  ApplApplier(const NWorld::PFBaseApplicator* pApplicator, float time) { pAppl = pApplicator; curTime = time; }
  void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->OnApplicatorUse(pAppl, curTime); }

  const NWorld::PFBaseApplicator* pAppl;
  float curTime;
};

struct Resetter
{
  Resetter() { }
  void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->OnOwnerDie(); }
};

struct MinigameCompletter
{
  MinigameCompletter(const NDb::DBID &game) : game(game) {}
  void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->OnMinigameComplete(game); }

  NDb::DBID game;
};

struct MinigameLevelEnder
{
  MinigameLevelEnder(const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum status ) 
    : game(game)
    , idx(levelIndex)
    , status(status)
  {}
  void operator()(CObj<NWorld::PFAchievBase> const& p) const { p->OnMinigameLevelEnd(game, idx, status); }

  NDb::DBID game;
  int idx;
  EMinigameLevelStatus::Enum status;
};

struct RankGetter
{
  RankGetter(DWORD achievTypeId, int* _rank) : id(achievTypeId), rank(_rank) {}
  void operator()(CObj<NWorld::PFAchievBase> const& p)
  { 
    if (id == p->GetDBBase()->GetObjectTypeID())
      *rank = p->GetRank(); 
  }

  int* rank;
  DWORD id;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct GatherFactionStats_
{
  GatherFactionStats_(NDb::EFaction faction, NWorld::PerFactionStatistics &stat) : faction(faction), stat(stat)
  {
    stat.numKills = 0;
    stat.numAssists = 0;
  }

  void operator()(NWorld::PFBaseHero &hero)
  {
    NWorld::PFHeroStatistics * pHeroStatistics = hero.GetHeroStatistics().GetPtr();
    if (hero.GetFaction() == faction && pHeroStatistics)
    {
      stat.numKills   += pHeroStatistics->GetTotalNumHeroKills();
      stat.numAssists += pHeroStatistics->GetTotalNumHeroAssists();
    }
  }

  NDb::EFaction faction;
  NWorld::PerFactionStatistics &stat;

private:
  GatherFactionStats_ &operator = (GatherFactionStats_ const &);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StepAllHeroes_
{
public:
  StepAllHeroes_( float _dt, float time ): dt(_dt), curTime(time), bRet(true) {}

  void operator()(NWorld::PFBaseHero &hero)
  {
    if (NWorld::PFHeroStatistics * pHeroStatistics = hero.GetHeroStatistics().GetPtr())
      bRet &= pHeroStatistics->OnStep(dt, curTime);
  }
  bool GetResult() { return bRet; }
private:
  float dt;
  float curTime;
  bool bRet;

  StepAllHeroes_ &operator = (StepAllHeroes_ const &);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct GetLastApplicator_
{
  GetLastApplicator_(): lastAppl(0) {}
  void operator()(CObj<NWorld::PFBaseApplicator> &app)
  {
    lastAppl = app;
  }
  NWorld::PFBaseApplicator *lastAppl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct AddFinalScore_
{
  NWorld::PFStatistics &stat;

  AddFinalScore_(NWorld::PFStatistics &stat) : stat(stat) {}

  void operator()(NWorld::PFBaseHero &hero)
  {
    if (NWorld::PFHeroStatistics * pHeroStatistics = hero.GetHeroStatistics().GetPtr())
      pHeroStatistics->AddFinalScore(stat);
  }

private:
  AddFinalScore_ &operator = (AddFinalScore_ const &);
};

} // End of anonymous namespace

namespace NWorld
{

//================================ SignsEventsNameMap =============================================================================
NAMEMAP_BEGIN(CustomEventNameMap)
  NAMEMAP_CUSTOM_SUBMAP(owner,  &ownerData, true )
  NAMEMAP_CUSTOM_SUBMAP(killer, &ownerData, true )
  NAMEMAP_CUSTOM_SUBMAP(victim, &victimData, true )
  NAMEMAP_FUNC_RO(achievCount,    &CustomEventNameMap::GetAchievementCount)  //number of linear achievements
  NAMEMAP_FUNC_RO(enemyTeamName,  &CustomEventNameMap::GetEnemyTeamName)
  NAMEMAP_FUNC_RO(assistants,     &CustomEventNameMap::GetAssistanstsNames)
  NAMEMAP_FUNC_RO( customParam,   &CustomEventNameMap::GetCustomParameter )
  NAMEMAP_FUNC_RO(victimIsHero, &CustomEventNameMap::IsVictimHero)
NAMEMAP_END

//=========================================================================================================================
CustomEventNameMap::CustomEventNameMap()
: m_pOwner(NULL)
, m_pVictim(NULL)        
, m_enemyTeamName(L"error_not_inited!!!")
, m_tmpString(L"error_not_inited!!!")
, m_achievementCount(L"error_not_inited!!!")
{ }

//=================================================================================================================================
void CustomEventNameMap::Clear()
{
  m_enemyTeamName    = L"error_not_inited!!!";
  m_tmpString        = L"error_not_inited!!!";
  m_achievementCount = L"error_not_inited!!!";
}

//=================================================================================================================================
void CustomEventNameMap::SetOwner(const NWorld::PFBaseUnit* owner)
{ 
  m_pOwner = owner;

  PFBaseHero const* pHero = dynamic_cast<PFBaseHero const*>(owner);
  ownerData.name = pHero ? pHero->GetPlayerName() : owner->GetDescription();
}

//=================================================================================================================================
void CustomEventNameMap::SetVictim(const NWorld::PFBaseUnit* victim)
{ 
  m_pVictim = victim;

  PFBaseHero const* pHero = dynamic_cast<PFBaseHero const*>(victim);
  victimData.name = pHero ? pHero->GetPlayerName() : victim->GetDescription();
}

//=================================================================================================================================
void CustomEventNameMap::SetAssistants(const vector<NWorld::PFBaseHero*>& eventAssistants)
{ 
  //криворукие писатели nstl не могли даже написать assign нормальный!!!
  m_eventAssistants.clear();
  vector<NWorld::PFBaseHero*>::const_iterator iter;
  for(iter = eventAssistants.begin(); iter != eventAssistants.end(); ++iter )
    m_eventAssistants.push_back( *iter );
}

//=================================================================================================================================
const wstring& CustomEventNameMap::GetAssistanstsNames() const
{
  static wstring assistantsNames;
  assistantsNames = L"";
  if ( !m_eventAssistants.empty() )
  {
    vector<NWorld::PFBaseHero*>::const_iterator iter, iEnd ;  
    for(iter = m_eventAssistants.begin(), iEnd = m_eventAssistants.end(); iter != iEnd; ++iter )
    { 
      if ( (*iter) != NULL && NGameX::AdventureScreen::Instance() != NULL )
        assistantsNames += NGameX::AdventureScreen::Instance()->GetPlayerName( (*iter)->GetPlayerId() );

      if ( iter != iEnd - 1 )
      {
        assistantsNames += L", ";
      }
    }
  
    wchar_t buf[128] = {};
    _snwprintf_s(buf, 128, L"Assistants: %s.", assistantsNames.c_str());
    assistantsNames = wstring(buf);
    return assistantsNames;      
  }
  
  return m_tmpString;
}

//=================================================================================================================================
const wstring& CustomEventNameMap::GetAchievementCount() const
{
  return m_achievementCount;
}

//=================================================================================================================================
void CustomEventNameMap::SetEnemyTeamName(const wstring& enemyTeamName)
{
  m_enemyTeamName = enemyTeamName;
}

//=================================================================================================================================
const wstring& CustomEventNameMap::GetEnemyTeamName() const
{
  return m_enemyTeamName;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPtr<NWorld::PFBaseHero> PFStatistics::GetHeroById( const CPtr<NWorld::PFAIWorld>& pAIWorld, int id )
{
  struct FindHero
  {
    FindHero(int _id) : id(_id) {}
    void operator()(NWorld::PFBaseHero & hero) { if (hero.GetObjectId() == id) pHero = &hero; }
    CPtr<NWorld::PFBaseHero> pHero;
    int id;
  } finder(id);

  pAIWorld->ForAllHeroes(finder, NDb::FACTION_BURN);

  if (IsValid(finder.pHero))
    return finder.pHero;

  pAIWorld->ForAllHeroes(finder, NDb::FACTION_FREEZE);

  return finder.pHero;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFStatistics::PFStatistics(const CPtr<PFWorld> pWorld) 
: PFWorldObjectBase( pWorld, 0 )
, pWorld(pWorld)
, firstMiniGameWinner(-1)
, towersDestroyedCnt(0) 
, mainBuildingKiller(-1)
, firstMerciless(-1)
, firstMGAllLevelsWinner(-1)
, wasFirstAssault(false)
{
  scoring = NDb::SessionRoot::GetRoot()->logicRoot->scoringTable; 

  // create UI message
  ResetUiEvents();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddQuartersDestroy( PFQuarters* pQuarters, CPtr<PFBaseUnit> pKiller )
{
  NI_VERIFY(IsValid(pKiller), "Killer invalid", return);

  GetWorld()->GetAIWorld()->GetKiller( pQuarters, pKiller );

  PFBaseHero *pHeroKiller = dynamic_cast<PFBaseHero *>(pKiller.GetPtr());

  if ( pHeroKiller )
  {
    pHeroKiller->GetHeroStatistics()->AddQuartersDestroyed();
  }
}


void PFStatistics::NoMoreFirstAssault()
{
  wasFirstAssault = true;
}

bool PFStatistics::WasFirstAssault() const
{
  return wasFirstAssault;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddAssist(CPtr<PFBaseUnit> const& pVictim, CPtr<PFBaseUnit> const& pKiller, CPtr<PFBaseHero> const& pHeroAssistant)
{
  NI_VERIFY(IsValid(pHeroAssistant), "Assister invalid", return);
  NI_VERIFY(!pHeroAssistant->IsClone(), "Assister is a clone", return);

  PFHeroStatistics &stat = *pHeroAssistant->GetHeroStatistics();
  float curTime = pWorld->GetTimeElapsed();

  if ( pVictim->IsTrueHero() )
  {
    PFBaseHero *pHeroVictim = static_cast<PFBaseHero *>(pVictim.GetPtr());

    StatisticsStuff::UpdateArray_(stat.heroAssistTime.begin(), stat.heroAssistTime.size(), curTime);
    assistInstances.push_back(StatisticsStuff::HeroAssistInstance(pHeroVictim, pHeroAssistant, curTime));
  
    StatisticService::RPC::SessionEventInfo eventParams;
    eventParams.intParam1 = pHeroVictim->GetStatisticsUid();

    if ( pKiller->IsTrueHero() )
    {
      PFBaseHero* pKillerHero = static_cast<PFBaseHero*>(pKiller.GetPtr());
      eventParams.intParam2 = pKillerHero->GetStatisticsUid();
    }
    else
    {
      eventParams.intParam3 = pKiller->DbUnitDesc()->GetDBID().GetHashKey();
    }

    pHeroAssistant->LogSessionEvent(SessionEventType::KillAssist, eventParams);
    // update scores for assist
    stat.AddHeroAssist( pHeroVictim->GetObjectId() );
  }
  else if (StatisticsStuff::IsBoss(pVictim.GetPtr()))
  {
	  bool bIsBossCat = false, bIsBossDragon = false;
	  NWorld::PFNeutralCreep* pNC = dynamic_cast<NWorld::PFNeutralCreep*>(pVictim.GetPtr());
	  if (pNC)
	  {
	    NWorld::PFBaseSpawner* pBS = (NWorld::PFBaseSpawner*)pNC->GetSpawner();
	    nstl::string sName = pBS->GetSpawnerName();
	    bIsBossCat = sName == "Boss_Cat";		  
	    bIsBossDragon = sName == "Boss_Dragon";
	  }

    stat.AddBossKillScore(bIsBossCat, bIsBossDragon);
  }  

  // process all achievements
  Assister checkAssist(pVictim, pKiller, curTime);
  stat.ForAllAchievements(checkAssist);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddKill(CPtr<PFBaseUnit> pVictim, CPtr<PFBaseHero> pKiller)
{
  NI_VERIFY( IsValid(pVictim) && IsValid(pKiller), "Victim and killer must be valid!", return );
  NI_ASSERT( !dynamic_cast<PFTower const *>(pVictim.GetPtr()), "Tower must go through AddTowerDestroy only!");
  NI_VERIFY( !pKiller->IsClone(), "Killer is a clone", return );

  PFHeroStatistics &killerStatistics = *pKiller->GetHeroStatistics();
  float curTime = pWorld->GetTimeElapsed();

  ++killerStatistics.numKillsTotal;
  
  if ( pVictim->IsTrueHero() )
  {
    PFBaseHero *pHeroVictim = static_cast<PFBaseHero *>(pVictim.GetPtr());

    StatisticsStuff::UpdateArray_(killerStatistics.heroKillTime.begin(), killerStatistics.heroKillTime.size(), curTime);
    // store kill to array
    killInstances.push_back(StatisticsStuff::HeroKillInstance(pHeroVictim, pKiller, curTime, *this));

    StatisticService::RPC::SessionEventInfo eventParams;
    eventParams.intParam1 = pHeroVictim->GetStatisticsUid();
    pKiller->LogSessionEvent(SessionEventType::HeroKill, eventParams);
    // update scores for kill
    killerStatistics.AddHeroKill( pHeroVictim->GetObjectId() );
    
    if ( killerStatistics.currentDeathSpree == 0 ) // workaround mentioned at ::AddHeroDeath
    {
      ++killerStatistics.currentKillSpree;
    }
    else
    {
      killerStatistics.currentKillSpree = 1;
      killerStatistics.currentDeathSpree = 0;
    }
  }
  else 
  {
    bool needToLog = false;

    if (IsValid(pVictim) && pVictim->GetMasterUnit())
    {
      needToLog = true;
    }

    if (StatisticsStuff::IsBoss(pVictim.GetPtr()))
    {
	  bool bIsBossCat = false, bIsBossDragon = false;
	  NWorld::PFNeutralCreep* pNC = dynamic_cast<NWorld::PFNeutralCreep*>(pVictim.GetPtr());
	  if (pNC)
	  {
		  NWorld::PFBaseSpawner* pBS = (NWorld::PFBaseSpawner*)pNC->GetSpawner();
		  nstl::string sName = pBS->GetSpawnerName();
		  bIsBossCat = sName == "Boss_Cat";		  
		  bIsBossDragon = sName == "Boss_Dragon";
	  }
      PerFactionStatistics &factionStat = perFactionStatistics[pKiller->GetFaction()];

      killerStatistics.AddBossKillScore(bIsBossCat, bIsBossDragon);

      factionStat.AddBossKill(scoring->faction, bIsBossCat, bIsBossDragon);

      needToLog = true;
    }
    else if (dynamic_cast<PFCommonCreep *>(pVictim.GetPtr()) )
    {
      ++killerStatistics.numCreepsKilled;
    }
    else if ( dynamic_cast<PFNeutralCreep *>(pVictim.GetPtr()))
    {
      ++killerStatistics.numNeutralCreepsKilled;

      needToLog = true;
    }

    if (IsValid(pVictim) && needToLog)
    {
      StatisticService::RPC::SessionEventInfo eventParams;
      eventParams.intParam2 = pVictim->DbUnitDesc()->GetDBID().GetHashKey();
      
      if( PFNeutralCreep* creep = dynamic_cast<PFNeutralCreep *>( pVictim.GetPtr() ) )
      {
        eventParams.strParam1.assign( NStr::StrFmtW(L"x=%d, y=%d", (int)creep->GetInitialPlacement().pos.x, (int)creep->GetInitialPlacement().pos.y ) );

        if( creep->GetSpawner() && creep->GetSpawner()->GetSpawnedCreepsCount() == 0 )
        {
          StatisticService::RPC::SessionEventInfo eventParamsSpawner;
          eventParamsSpawner.intParam2 = pVictim->DbUnitDesc()->GetDBID().GetHashKey();
          eventParamsSpawner.strParam1.assign( NStr::StrFmtW(L"x=%d, y=%d", (int)creep->GetSpawner()->GetSpawnPosition().pos.x, (int)creep->GetSpawner()->GetSpawnPosition().pos.y ) );
          pKiller->LogSessionEvent(SessionEventType::SpawnerDead, eventParamsSpawner);
        }
      }
      pKiller->LogSessionEvent(SessionEventType::HeroKill, eventParams);
    }

    // Announce neutral creep killing
    PFBaseCreep const* pCreepVictim = dynamic_cast<PFBaseCreep const*>(pVictim.GetPtr());
    if ( IsValid( pCreepVictim ) && GetWorld()->GetAIWorld()->IsNeutralCreepInAnnounceList( pCreepVictim ) )
    {
      CustomEventNameMap eventData;
      eventData.SetOwner(pKiller.GetPtr());
      eventData.SetVictim(pVictim);
      eventData.SetEnemyTeamName(pKiller->GetFactionName());

      vector<PFBaseHero*> assistants;
      pVictim->GetWorld()->GetAIWorld()->GetAssistants(pVictim.GetPtr(), pKiller.GetPtr(), assistants);
      if ( !assistants.empty() ) 
        eventData.SetAssistants(assistants);

      NGameX::AnnouncementParams announcementParams;
      announcementParams.victim = pVictim;
      announcementParams.killer = pKiller;

      if (pEventHeroKill)
      {
        pEventHeroKill->SetOwner(pKiller.GetPtr());
        NGameX::AdventureScreen::Instance()->OnUIEvent(pEventHeroKill, &eventData, &announcementParams);
      }
    }
  }

  Killer kill(pVictim, pKiller.GetPtr(), curTime);
  killerStatistics.ForAllAchievements(kill);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::NoMoreDomination(CPtr<PFBaseHero> pPossibleKiller, CPtr<PFBaseHero> pPossibleVictim)
{
  NI_VERIFY(IsValid(pPossibleKiller), "Killer invalid", return);
  NI_VERIFY(!pPossibleKiller->IsClone(), "Killer is a clone", return);

  vector<int> &cannotDominate = pPossibleKiller->GetHeroStatistics()->cannotDominate;
  PushUnique(cannotDominate, pPossibleVictim->GetObjectId());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFStatistics::CanDominate(CPtr<PFBaseHero> pPossibleKiller, CPtr<PFBaseHero> pPossibleVictim)
{
  NI_VERIFY(IsValid(pPossibleKiller), "Killer invalid", return false);
  NI_VERIFY(!pPossibleKiller->IsClone(), "Killer is a clone", return false);

  vector<int> const &cannotDominate = pPossibleKiller->GetHeroStatistics()->cannotDominate;
  return find(cannotDominate.begin(), cannotDominate.end(), pPossibleVictim->GetObjectId()) == cannotDominate.end();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get number of dominating kills
// - ingoreLast - for Vendetta achievement
int PFStatistics::GetDominate(CPtr<PFBaseHero> pHeroVictim, CPtr<PFBaseHero> pKiller, bool ignoreLast)
{
  // comment: swap killer and victim to know when new victim killed new killer
  float lastKillerKilledTime = max(GetLastKillTime(pKiller, pHeroVictim, ignoreLast), GetLastAssistTime(pKiller, pHeroVictim, ignoreLast));
  // IgorKaa: todo - update lastKillerKilledTime via new killer death
  
  return GetNumKills(pHeroVictim, pKiller, lastKillerKilledTime);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFStatistics::GetHeroAchievmentRank(CPtr<PFBaseHero> const& pHero, DWORD achievTypeId) const
{
  int resRank = -1;
  RankGetter f(achievTypeId, &resRank);

  if (!IsValid(pHero))
    return 0;

  NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr();
  if (!pHeroStatistics)
    return 0;

  pHeroStatistics->ForAllAchievements(f);
  NI_VERIFY( resRank >= 0, "Wrong achiev type ID", return 0; );

  return resRank;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFStatistics::GetTerrainOwnerID(PFTower const *tower) const
{
  Terrain::NatureMap &nm = pWorld->GetScene()->GetTerrain()->GetNatureMap();
  Terrain::NatureMapElementId id = nm.LocateElement(tower->GetPos().x, tower->GetPos().y);
  NI_VERIFY(id != Terrain::NATUREMAPELEMENTID_BAD, "Bad terrain pos", return -1);

  return nm.GetElementInfo( id ).ownerData;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddFlagDestroyed(CPtr<PFBaseUnit> pDestroyer)
{
  NI_VERIFY(IsValid(pDestroyer), "Invalid flag destoyer unit!", return; );

  if ( pDestroyer->IsTrueHero() )
  {
    PFBaseHero * pHero = static_cast<PFBaseHero *>(pDestroyer.GetPtr());
    if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
      pHeroStatistics->AddFlagDestroyed();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddHealedAmount(CPtr<PFBaseHero> pHero, float amount)
{
  NI_VERIFY(IsValid(pHero), "Hero must be valid!", return; );

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
    pHeroStatistics->AddHealedAmount(amount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFStatistics::GetMoney(const PFBaseHero* const pHero) const
{
  NI_ASSERT(IsValid(pHero), "Hero invalid");
  NI_ASSERT(!IsValid(pHero->GetMasterUnit()), "Hero has a master, may be hero is a clone");

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
    return pHeroStatistics->GetMoney();

  return 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFStatistics::GetTSliceSalary(const PFBaseHero* const pHero) const
{
  NI_ASSERT(IsValid(pHero), "Hero invalid");
  NI_ASSERT(!IsValid(pHero->GetMasterUnit()), "Hero has a master, may be hero is a clone");

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
    return pHeroStatistics->GetTSliceSalary();

  return 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::SetTSliceSalary(const PFBaseHero* const pHero, float salary)
{
  NI_ASSERT(IsValid(pHero), "Hero invalid");
  NI_ASSERT(!IsValid(pHero->GetMasterUnit()), "Hero has a master, may be hero is a clone");

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
    pHeroStatistics->SetTSliceSalary(salary);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddTSliceSalary(const PFBaseHero* const pHero, float salary)
{
  NI_ASSERT(IsValid(pHero), "Hero invalid");
  NI_ASSERT(!IsValid(pHero->GetMasterUnit()), "Hero has a master, may be hero is a clone");

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
    pHeroStatistics->AddTSliceSalary(salary);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddMoney(CPtr<PFBaseHero> const& pHero, float money)
{
  NI_ASSERT(IsValid(pHero), "Hero invalid");
  NI_ASSERT(!IsValid(pHero->GetMasterUnit()), "Hero has a master, may be hero is a clone");

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
    pHeroStatistics->money += money;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFStatistics::GetNumKills(CPtr<PFBaseHero> pVictim, CPtr<PFBaseHero> pKiller, float minTime)
{
  int num = 0;
  nstl::vector<StatisticsStuff::HeroKillInstance>::const_iterator const end = killInstances.end();
  for(nstl::vector<StatisticsStuff::HeroKillInstance>::const_iterator it = killInstances.begin(); it != end; ++it)
  {
    StatisticsStuff::HeroKillInstance const &ki = *it;
    if (ki.pSlayer == pKiller && ki.pVictim == pVictim && ki.time > minTime)
    {
      ++num;
    }
  }
  return num;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float PFStatistics::GetLastKillTime(CPtr<PFBaseHero> pVictim, CPtr<PFBaseHero> pKiller, bool ignoreLast)
{
  float ret = -1.f;

  // ktodo they don't have const_reverse_iterator.
  nstl::vector<StatisticsStuff::HeroKillInstance>::const_iterator const end = killInstances.end();
  for(nstl::vector<StatisticsStuff::HeroKillInstance>::const_iterator it = killInstances.begin(); it != end; ++it)
  {
    StatisticsStuff::HeroKillInstance const &ki = *it;
    if (ki.pSlayer == pKiller && ki.pVictim == pVictim)
    {
      if (ignoreLast)
      {
        nstl::vector<StatisticsStuff::HeroKillInstance>::const_iterator next = it;
        ++next;

        if (next == end)
          continue;
      }

      ret = max(ret, ki.time);
    }
  }

  return ret;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ktodo copy-paste
float PFStatistics::GetLastAssistTime(CPtr<PFBaseHero> pVictim, CPtr<PFBaseHero> pAssistant, bool ignoreLast)
{
  float ret = -1.f;

  // ktodo they don't have const_reverse_iterator.

  nstl::vector<StatisticsStuff::HeroAssistInstance>::const_iterator const end = assistInstances.end();
  for(nstl::vector<StatisticsStuff::HeroAssistInstance>::const_iterator it = assistInstances.begin(); it != end; ++it)
  {
    StatisticsStuff::HeroAssistInstance const &ki = *it;
    if (ki.pSlayer == pAssistant && ki.pVictim == pVictim)
    {
      if (ignoreLast)
      {
        nstl::vector<StatisticsStuff::HeroAssistInstance>::const_iterator next = it;
        ++next;
        
        if (next == end)
          continue;
      }

      ret = max(ret, ki.time);
    }
  }

  return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::MinigameComplete( const NDb::DBID &game, int player )
{
  if (firstMiniGameWinner == -1)
    firstMiniGameWinner = player;

  CPtr<PFBaseHero> pHero = GetHeroById(pWorld->GetAIWorld(), player);
  NI_VERIFY(IsValid(pHero), "Unable to find hero", return);

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
  {
    MinigameCompletter f(game);
    pHeroStatistics->ForAllAchievements(f);
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::MinigameLevelEnded( const NDb::DBID &game, int player, int levelIndex, EMinigameLevelStatus::Enum status, bool lastLevel )
{
  CPtr<PFBaseHero> pHero = GetHeroById(pWorld->GetAIWorld(), player);
  NI_VERIFY(IsValid(pHero), "Unable to find hero", return);

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
  {
    MinigameLevelEnder f(game, levelIndex, status);

    pHeroStatistics->ForAllAchievements(f);

    // update per hero stat
    pHeroStatistics->OnMinigameLevelEnd( game, levelIndex, status );

    if (lastLevel)
      SetFirstMGAllLevelsWinner(player);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFStatistics::GetScore(CPtr<PFBaseHero> pHero) const
{
  if (IsValid(pHero))
    if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
      return perFactionStatistics[ pHero->GetFaction() ].score + pHeroStatistics->score;

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::SetMainBuildingKiller(CPtr<PFBaseUnit> pKiller)
{
  if ( IsValid(pKiller) && pKiller->IsTrueHero() )
  {
    PFBaseHero const * pHero = static_cast<PFBaseHero const *>(pKiller.GetPtr());
    SetMainBuildingKiller(pHero->GetPlayerId());
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::SetFirstMerciless(int playerID)
{
  if (-1 == firstMerciless)
    firstMerciless = playerID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::SetFirstMGAllLevelsWinner(int playerID)
{
  if (-1 == firstMGAllLevelsWinner)
    firstMGAllLevelsWinner = playerID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFStatistics::OnStep( float dtInSeconds )
{
  NI_PROFILE_FUNCTION

  StepAllHeroes_ tr(dtInSeconds, pWorld->GetTimeElapsed());
  ForAllHeroes(tr);

  return tr.GetResult();
}

// Registers all facts of instant moving, including pushes and cheats. Data is used for Wanderer title logics.
void PFStatistics::NotifyTeleport( PFBaseMovingUnit &pUnit )
{
  if (!pUnit.IsTrueHero())
    return;

  PFBaseHero *pHero = static_cast<PFBaseHero*>(&pUnit);

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
    pHeroStatistics->NotifyTeleport();
}

// Registers 'true' teleports triggered by specified abilities. Data is used for Teleporter title logics.
void PFStatistics::NotifyTeleportByAbility( PFBaseMovingUnit* pUnit, NDb::Ability const* pDBAbility )
{
  PFBaseHero *pHero = dynamic_cast<PFBaseHero*>(pUnit);
  if (!pHero) return;

  if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
  {
    vector<NDb::Ptr<NDb::Ability>> const& dbTeleportAbilities = scoring->teleporterAbilities;

    for ( vector<NDb::Ptr<NDb::Ability>>::const_iterator it = dbTeleportAbilities.begin(); it != dbTeleportAbilities.end(); ++it )
    {
      if ( (*it)->GetDBID() == pDBAbility->GetDBID() )
      {
        pHeroStatistics->AddTeleportsByAbility();
        return;
      }
    }
  }
}

void PFStatistics::SendCheatMessage( PFBaseHero * hero )
{
  // Set UI Data
  CustomEventNameMap eventData;
  eventData.SetOwner( hero );

  if ( pEventCheat )
  {
    pEventCheat->SetOwner( hero );

    if ( s_DbgEnableCheatNotice )
      NGameX::AdventureScreen::Instance()->OnUIEvent(pEventCheat, &eventData);
  }
}



void PFStatistics::NotifyItemTransfer( PFBaseHero * from, PFBaseHero * to, const NDb::Consumable * dbItem )
{
  if ( !pCustomUiEvents )
    return;
  if ( !pCustomUiEvents->evItemGain || !pCustomUiEvents->evItemTransfer )
    return;

  // Set UI Data
  CustomEventNameMap eventData;
  eventData.SetOwner( from );
  eventData.SetVictim( to );
  eventData.SetCustomParam( dbItem->name.GetText() );

  NDb::Ptr<NDb::UIEvent> dbEvent = ( from == to ) ? pCustomUiEvents->evItemGain : pCustomUiEvents->evItemTransfer;
  CObj<NGameX::PFUIEvent> event = new NGameX::PFUIEvent( dbEvent, from );
  NGameX::AdventureScreen::Instance()->OnUIEvent( event, &eventData );
}



void PFStatistics::OnApplicatorApply(const PFBaseApplicator* pApplicator)
{
  PFBaseUnit *pUnit = pApplicator->GetAbilityOwner();
  if ( !IsValid( pUnit ) )
    return;

  if ( !pUnit->IsTrueHero() )
    pUnit = pUnit->GetMasterUnit();

  if ( IsValid( pUnit ) && pUnit->IsTrueHero() )
  {
    PFBaseHero *pHero = static_cast<PFBaseHero *>(pUnit);

    NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics();
    if ( !pHeroStatistics )
      return;

    float curTime = pWorld->GetTimeElapsed();
    ApplApplier apply(pApplicator, curTime);
    pHeroStatistics->ForAllAchievements(apply);

    // Verify and count the ability, if it related to gender talent
    const NWorld::PFTriggerApplicator * pTriggerApplicator = dynamic_cast<const NWorld::PFTriggerApplicator *> (pApplicator);
    if (pTriggerApplicator)
    {
      const NWorld::PFAbilityInstance * pAbilityInstance = dynamic_cast<const NWorld::PFAbilityInstance *>(pTriggerApplicator->GetAbility().GetPtr());
      if (pAbilityInstance)
      {
        const NWorld::PFTalent * pTalent = dynamic_cast<const NWorld::PFTalent *> (pAbilityInstance->GetData());
        if (pTalent)
        {
          NDb::Ptr<NDb::Talent> const & pTalentDesc = pTalent->GetTalentDesc();
          if (IsValid(pTalentDesc) && pTalentDesc->isGenderTalent)
            pHeroStatistics->AddSexHelp();
        }
      }
    }
  }
}



void PFStatistics::ResetUiEvents()
{
  pCustomUiEvents = NDb::SessionRoot::GetRoot()->visualRoot->uiEvents;

  if ( pCustomUiEvents )
  {
    if ( pCustomUiEvents->evHeroKill )
      pEventHeroKill = new NGameX::PFUIEvent( pCustomUiEvents->evHeroKill, 0 );

    if ( pCustomUiEvents->evHeroKillByAI )
      pEventHeroKillByAI = new NGameX::PFUIEvent( pCustomUiEvents->evHeroKillByAI, 0 );

    if ( pCustomUiEvents->evHeroKillByNeutralAI )
      evHeroKillByNeutralAI = new NGameX::PFUIEvent( pCustomUiEvents->evHeroKillByNeutralAI, 0 );
    
    if ( pCustomUiEvents->evTowerDestroy )
      pEventTowerDestroy = new NGameX::PFUIEvent( pCustomUiEvents->evTowerDestroy, 0 );

    if ( pCustomUiEvents->evTowerDestroyByAI )
      pEventTowerDestroyByAI = new NGameX::PFUIEvent( pCustomUiEvents->evTowerDestroyByAI, 0 );

    if ( pCustomUiEvents->evHeroCheat )
      pEventCheat = new NGameX::PFUIEvent( pCustomUiEvents->evHeroCheat, 0 );
  }
}


void PFStatistics::Reset()
{
  PFWorldObjectBase::Reset();

  ResetUiEvents();
}

#pragma code_seg(push, "~")

void PFStatistics::CalculateFinalScore( NGameX::HeroTitleCalculator const* heroTitleCalculator )
{
  STARFORCE_STOPWATCH();

  // update faction statistics
  GatherFactionStats_ classObj1(NDb::FACTION_BURN,   perFactionStatistics[NDb::FACTION_BURN]);
  ForAllHeroes(classObj1);

  GatherFactionStats_ classObj2(NDb::FACTION_FREEZE, perFactionStatistics[NDb::FACTION_FREEZE]);
  ForAllHeroes(classObj2);

  if (!IsValid(scoring))
  {
    return;
  }

  // score faction for max kills
  {
    int maxNumKills = 0, maxNumKillsFaction = -1;
    for (int i = 0; i < NDb::KnownEnum<NDb::EFaction>::sizeOf; ++i)
    {
      if ( perFactionStatistics[i].numKills > maxNumKills )
      {
        maxNumKills = perFactionStatistics[i].numKills;
        maxNumKillsFaction = i;
      }
      else if ( perFactionStatistics[i].numKills == maxNumKills )
      {
        // we're interested in ONE & ONLY winner
        maxNumKillsFaction = -1;
      }
    }

    if (maxNumKillsFaction != -1)
    {
      perFactionStatistics[maxNumKillsFaction].SetBestKiller();
    }
  }

  // score faction for max assists
  {
    int maxNumAssists = 0, maxNumAssistsFaction = -1;
    for (int i = 0; i < NDb::KnownEnum<NDb::EFaction>::sizeOf; ++i)
    {
      if ( perFactionStatistics[i].numAssists > maxNumAssists )
      {
        maxNumAssists = perFactionStatistics[i].numAssists;
        maxNumAssistsFaction = i;
      }
      else if ( perFactionStatistics[i].numAssists == maxNumAssists )
      {
        // we're interested in ONE & ONLY winner
        maxNumAssistsFaction = -1;
      }
    }

    if (maxNumAssistsFaction != -1)
    {
      perFactionStatistics[maxNumAssistsFaction].SetBestAssistant();
    }
  }

  // calculate basic faction score
  for (int i = 0; i < NDb::KnownEnum<NDb::EFaction>::sizeOf; ++i)
  {
    DebugTrace( "Final Scoring for team %s", EnumToString( (NDb::EFaction)i ) );
    perFactionStatistics[i].sessionTime = pWorld->GetTimeElapsed();
    perFactionStatistics[i].CalculateFinalScore(scoring->faction);
  }

  // add final hero score
  AddFinalScore_ classObj(*this);
  ForAllHeroes(classObj);

  // add title score
  struct AddTitleScore : public NonCopyable
  {
    AddTitleScore( NGameX::HeroTitleCalculator const* _heroTitleCalculator) : heroTitleCalculator(_heroTitleCalculator) {}

    void operator()(NWorld::PFBaseHero &hero)
    {
      if (NWorld::PFHeroStatistics * pHeroStatistics = hero.GetHeroStatistics().GetPtr())
        pHeroStatistics->AddTitleScore(heroTitleCalculator);
    }

    NGameX::HeroTitleCalculator const* heroTitleCalculator;
  } addTitleScore( heroTitleCalculator );
  ForAllHeroes( addTitleScore );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddTowerDestroy(CPtr<PFTower> tower, CPtr<PFBaseUnit> pKiller) 
{   
  STARFORCE_STOPWATCH();

  NI_VERIFY(IsValid(pKiller), "Killer invalid", return);

  GetWorld()->GetAIWorld()->GetKiller( tower.GetPtr(), pKiller );

  PFBaseHero *pHeroKiller = dynamic_cast<PFBaseHero *>(pKiller.GetPtr());

  // increase total tower destroyed counter
  ++towersDestroyedCnt;

  // Set UI Data
  CustomEventNameMap eventData;
  eventData.SetOwner(pKiller);
  eventData.SetVictim(tower.GetPtr());

  TowerDestroyer towerDestroy(tower);
  TowerAssister  towerAssist(tower);

  // 1. who are killers?
  vector<PFBaseHero *> killers;
  if (pHeroKiller && !pHeroKiller->IsClone())
    killers.push_back(pHeroKiller);

  Protection::CheckSystemDlls();

  // 2. who are assistants?
  vector<PFBaseHero *> assistants;
  tower->GetWorld()->GetAIWorld()->GetAssistants(tower.GetPtr(), pKiller.GetPtr(), assistants);

  // 3. killer may not be assistant
  StatisticsStuff::Minus_(assistants, killers);

  // award killers
  for (vector<PFBaseHero*>::iterator it = killers.begin(), itEnd = killers.end(); it != itEnd; ++it)
  {
    PFBaseHero *killer = *it;
    if (NWorld::PFHeroStatistics * pHeroStatistics = killer->GetHeroStatistics().GetPtr())
    {
      pHeroStatistics->AddTowerKill(tower->GetRouteId());
      pHeroStatistics->ForAllAchievements(towerDestroy);
    } 
  }

  // award assistants only if no hero killers
  if ( killers.empty() )
  {
    for (vector<PFBaseHero*>::iterator it = assistants.begin(), itEnd = assistants.end(); it != itEnd; ++it)
    {
      PFBaseHero *assister = *it;
      if (NWorld::PFHeroStatistics * pHeroStatistics = assister->GetHeroStatistics().GetPtr())
      {
        pHeroStatistics->AddTowerAssist(tower->GetRouteId());
        pHeroStatistics->ForAllAchievements(towerAssist);
      }
    }
  }

  // ktodo think of code below
  if ( !IsValid(pKiller) )//invalid killer or destroyed by Ctrl+D
    return;

  if (pKiller->GetFaction() != NDb::FACTION_NEUTRAL)
  {
    perFactionStatistics[pKiller->GetFaction()].AddTowerDestroy(tower, scoring->faction);
  }

  NGameX::AnnouncementParams announcementParams;
  announcementParams.victim = tower;
  announcementParams.killer = pKiller;

  // process ui message
  //if the killer is not a hero - send another message - killed by enemy AI
  if (pHeroKiller && pHeroKiller->GetFaction() != NDb::FACTION_NEUTRAL )
  {
    if (pEventTowerDestroy)
    {
      pEventTowerDestroy->SetOwner(pHeroKiller);
      NGameX::AdventureScreen::Instance()->OnUIEvent(pEventTowerDestroy, &eventData, &announcementParams);
    }
  }
  else //creeps
  {
    if ( pKiller->GetFaction() == NDb::FACTION_NEUTRAL )
    {
      CObj<NGameX::PFUIEvent> event = new NGameX::PFUIEvent( pCustomUiEvents->evTowerDestroyByNeutralAI, 0 );
      NGameX::AdventureScreen::Instance()->OnUIEvent( event, &eventData, &announcementParams );
    }
    else if (pEventTowerDestroyByAI)
    {
      // set ui data
      eventData.SetEnemyTeamName( pWorld->GetAIWorld()->GetFactionName( pKiller->GetFaction() ) );
      NGameX::AdventureScreen::Instance()->OnUIEvent(pEventTowerDestroyByAI, &eventData, &announcementParams);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddHeroDeath(CPtr<PFBaseHero> pVictim, CPtr<PFBaseUnit> pKiller)
{
  STARFORCE_STOPWATCH();

  struct Proxy
  {
    PFStatistics *pThis;
    CPtr<PFBaseHero> pVictim;
    CPtr<PFBaseUnit> pKiller;

    static void Call( const void *pProxyRaw )
    {
      const Proxy * const pProxy = static_cast<const Proxy *>(pProxyRaw);     
      pProxy->pThis->AddHeroDeathImpl( pProxy->pVictim, pProxy->pKiller ); 
    } 
  };

  Proxy proxy;

  proxy.pThis = this;
  proxy.pVictim = pVictim;
  proxy.pKiller = pKiller;

  Protection::CallFunctionInProtectedSpace( &Proxy::Call, &proxy );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddHeroDeathImpl(CPtr<PFBaseHero> pVictim, CPtr<PFBaseUnit> pKiller)
{
  STARFORCE_STOPWATCH();

  NI_VERIFY(IsValid(pVictim), "Victim invalid", return);
  NI_VERIFY(!pVictim->IsClone(), "Victim is a clone", return);

  GetWorld()->GetAIWorld()->GetKiller(pVictim.GetPtr(), pKiller);

  PFHeroStatistics &s = *pVictim->GetHeroStatistics();
  ++s.numDeaths;

  if (PFNeutralCreep const * pNeutralCreep = dynamic_cast<PFNeutralCreep const *>(pKiller.GetPtr()))
    s.AddKilledByNeutral();

  // send "owner die" event for all achievements
  Resetter ownerDie;
  s.ForAllAchievements(ownerDie);

  PFBaseHero * heroKiller = dynamic_cast<PFBaseHero*>(pKiller.GetPtr());

  if (heroKiller)
  {
    int killerId = pKiller->GetObjectId();
    ++s.numKilledMe[killerId];

    // Tricky workaround! Can't simply nullify currentKillSpree, because GetKillerAward uses it after ::AddHeroDeath call
    if ( s.currentDeathSpree++ > 0 && s.currentKillSpree > 0 ) 
    {
      s.currentKillSpree = 0;
    }
  }

  if (IsValid(pKiller))
  {
    CustomEventNameMap eventData;

    eventData.SetOwner(pKiller);
    eventData.SetVictim(pVictim.GetPtr());
    eventData.SetEnemyTeamName(pKiller->GetFactionName());

    vector<PFBaseHero*> assistants;
    pVictim->GetWorld()->GetAIWorld()->GetAssistants(pVictim.GetPtr(), pKiller.GetPtr(), assistants);
    if ( !assistants.empty() ) 
      eventData.SetAssistants(assistants);

    StatisticService::RPC::SessionEventInfo eventParams;
    NGameX::AnnouncementParams announcementParams;

    announcementParams.victim = pVictim;
    announcementParams.killer = pKiller;

    //if the killer is not a hero or neutral hero - send another message - killed by enemy AI
    if ( heroKiller && heroKiller->GetFaction() != NDb::FACTION_NEUTRAL )
    {      
      eventParams.intParam1 = heroKiller->GetStatisticsUid();
      if (pEventHeroKill)
      {
        pEventHeroKill->SetOwner(pKiller) ;
        NGameX::AdventureScreen::Instance()->OnUIEvent(pEventHeroKill, &eventData, &announcementParams);
      }
    }
    else
    {
      eventParams.intParam2 = pKiller->DbUnitDesc()->GetDBID().GetHashKey();

      NGameX::PFUIEvent * uiEvent = pKiller->GetFaction() == NDb::FACTION_NEUTRAL? evHeroKillByNeutralAI : pEventHeroKillByAI;

      if (uiEvent)
        NGameX::AdventureScreen::Instance()->OnUIEvent(uiEvent, &eventData, &announcementParams);
    }

    pVictim->LogSessionEvent(SessionEventType::HeroDeath, eventParams);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFStatistics::AddFlagRaised(CPtr<PFBaseUnit> pRaiser)
{
  STARFORCE_STOPWATCH();

  NI_VERIFY(IsValid(pRaiser), "Invalid flag raiser unit!", return; );

  if ( pRaiser->IsTrueHero() )
  {
    PFBaseHero * pHero = static_cast<PFBaseHero *>(pRaiser.GetPtr());
    if (NWorld::PFHeroStatistics * pHeroStatistics = pHero->GetHeroStatistics().GetPtr())
      pHeroStatistics->AddFlagRaised();

    Protection::CheckReadOnlyAndExecutable();
  }
}

#pragma code_seg(pop)

} //namespace NWorld
