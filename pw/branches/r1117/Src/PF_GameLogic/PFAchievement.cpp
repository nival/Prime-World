#include "stdafx.h"
#include "PFAchievement.h"
#include "PlayerData.h"
#include "PFCommonCreep.h"
#include "PFNeutralCreep.h"
#include "PFStatisticsImpl.h"
#include "PFAIWorld.h"
#include "PFApplInstant.h"
#include "PFApplUtils.h"
#include "PFApplicatorHistoryAnalysis.h"

#include "AdventureScreen.h"
#include "AdventureScreenEvents.h"
#include "SessionEventType.h"
#include "AnnouncementParams.h"


namespace
{
//=========================================================================================================================
// IgorKaa todo: remake this class (http://SITE)
class AchievementsNameMap : public NNameMap::Map
{
  NAMEMAP_DECLARE;

  CPtr<NWorld::PFBaseUnit>          m_pOwner;

  NGameX::PlayerData  ownerData;

  wstring                           m_achievementName;
  wstring                           m_achievementCount;    

public:
  AchievementsNameMap( NWorld::PFAchievBase* achiev );

  void           SetOwner (CPtr<NWorld::PFBaseUnit> owner);
  const wstring& GetAchievementName() const;
  const wstring& GetAchievementCount() const;
  void           SetAchievementCount(const wstring& count);
  void           SetAchievementCount(int count);
  void           SetAchievementName(const wstring& name);
};

//================================ AchievementsNameMap =============================================================================
NAMEMAP_BEGIN(AchievementsNameMap)
  NAMEMAP_CUSTOM_SUBMAP(owner,  &ownerData, true )
  NAMEMAP_CUSTOM_SUBMAP(killer, &ownerData, true )
  NAMEMAP_FUNC_RO(achievCount,    &AchievementsNameMap::GetAchievementCount)  //number of linear achievements
  NAMEMAP_FUNC_RO(achievName,     &AchievementsNameMap::GetAchievementName)
NAMEMAP_END

//=========================================================================================================================
AchievementsNameMap::AchievementsNameMap( NWorld::PFAchievBase* achiev )
  : m_pOwner(NULL)
  , m_achievementCount(L"error_not_inited!!!")
  , m_achievementName(L"error_not_inited!!!")
{ }

//=================================================================================================================================
void AchievementsNameMap::SetOwner(const CPtr<NWorld::PFBaseUnit> owner)
{ 
  m_pOwner = owner;

  NWorld::PFBaseHero const* pHero = dynamic_cast<NWorld::PFBaseHero const*>(owner.GetPtr());
  ownerData.name = pHero ? pHero->GetPlayerName() : owner->GetDescription();
}

//=================================================================================================================================
const wstring& AchievementsNameMap::GetAchievementName() const
{
  return m_achievementName;
}

//=================================================================================================================================
const wstring& AchievementsNameMap::GetAchievementCount() const
{
  return m_achievementCount;
}

//=================================================================================================================================
void AchievementsNameMap::SetAchievementCount(const wstring& count)
{
  m_achievementCount = count;
}

//=================================================================================================================================
void AchievementsNameMap::SetAchievementCount(int count)
{
  m_achievementCount = NStr::ToUnicode( NStr::StrFmt( "%d", count ));
}

//=================================================================================================================================
void AchievementsNameMap::SetAchievementName(const wstring& name)
{
  m_achievementName = name;
}

class FirstApplicatorGetter
{
public:
  FirstApplicatorGetter(CPtr<NWorld::PFBaseHero> &hero) : pHero(hero), first(0), isFirst(0)  { }

  CPtr<NWorld::PFBaseApplicator> const & Get() { return first; }

  void operator()(CObj<NWorld::PFBaseApplicator> const &pApp)
  {
    if (!isFirst)
    {
      CPtr<NWorld::PFBaseUnit> pSender(pApp->GetAbilityOwner());

      if (IsValid(pSender))
      {
        NWorld::PFBaseHero *pSenderHero = dynamic_cast<NWorld::PFBaseHero *>(pSender.GetPtr());
        if (pSenderHero == pHero.GetPtr())
        {
          first = pApp.GetPtr();
          isFirst = true;
        }
      }
    }
  }

private:  
  CPtr<NWorld::PFBaseHero> pHero;
  CPtr<NWorld::PFBaseApplicator> first;
  bool isFirst;
};

class NonHeroAttackChecker
{
public:
  NonHeroAttackChecker() : was(false) { }

  bool Get() { return was; }

  void operator()(CObj<NWorld::PFBaseApplicator> const &pApp)
  {
    CPtr<NWorld::PFBaseUnit> pSender(pApp->GetAbilityOwner());

    if (IsValid(pSender))
    {
      NDb::EUnitType type = pSender->GetUnitType();

      if (NDb::UNITTYPE_HEROMALE != type && NDb::UNITTYPE_HEROFEMALE != type && NDb::UNITTYPE_SUMMON != type)
        was = true;
    }
  }

private:  
  bool was;
};

class HeroAttackChecker
{
public:
  HeroAttackChecker() : was(false) { }

  bool Get() { return was; }

  void operator()(CObj<NWorld::PFBaseApplicator> const &pApp)
  {
    CPtr<NWorld::PFBaseUnit> pSender(pApp->GetAbilityOwner());

    if (IsValid(pSender))
    {
      NDb::EUnitType type = pSender->GetUnitType();

      if (NDb::UNITTYPE_HEROMALE == type || NDb::UNITTYPE_HEROFEMALE == type)
        was = true;
    }
  }

private:  
  bool was;
};


class ControlApplicatorChecker
{
public:
  ControlApplicatorChecker(CPtr<NWorld::PFBaseHero> &hero) : pHero(hero), bWas(0)  { }

  bool Get() { return bWas; }

  void operator()(CObj<NWorld::PFBaseApplicator> const &pApp)
  {
    // we are interested in applicators wrapped into status
    if ( IsValid( pApp->GetParentAppl() ) && pApp->GetParentAppl()->GetDBBase()->GetObjectTypeID() == NDb::StatusApplicator::typeId )
    {
      NDb::Ptr<NDb::BaseApplicator> const &db = pApp->GetDBBase();

      if( db->GetObjectTypeID() == NDb::FlagsApplicator::typeId ) // we are interested in FlagsApplicator
      {
        NDb::FlagsApplicator const* flagsApplDb = static_cast<NDb::FlagsApplicator const*>(db.GetPtr());

        // these flags are supposed to mean "control" effects
        int flagsToCheck = NDb::UNITFLAG_FORBIDMOVE | NDb::UNITFLAG_FORBIDMOVESPECIAL | NDb::UNITFLAG_FORBIDATTACK | NDb::UNITFLAG_FORBIDUSETALENTS |
                           NDb::UNITFLAG_FORBIDPLAYERCONTROL;

        // check flags
        if ( ( flagsApplDb->flag & flagsToCheck ) == 0 )
          return;
      }
      else if ( db->GetObjectTypeID() != NDb::MovementControlApplicator::typeId ) // we are interested in MovementControlApplicator
      {
        return;
      }
      
      CPtr<NWorld::PFBaseUnit> pSender(pApp->GetAbilityOwner());
      if (IsValid(pSender))
      {
        NWorld::PFBaseHero *pSenderHero = dynamic_cast<NWorld::PFBaseHero *>(pSender.GetPtr());
        if (pSenderHero == pHero.GetPtr())
        {
          bWas = true;
        }
      }
    }
  }

private:  
  CPtr<NWorld::PFBaseHero> pHero;
  bool bWas;
};

//////////////////////////////////////////////////////////////////////////
// hero history stuff
//////////////////////////////////////////////////////////////////////////
class Getter
{
public:
  Getter() {}
  NWorld::PFHeroHistoryData const * pLast;

  void Init(NWorld::PFHeroHistoryData const& data) 
  { 
    pLast = &data; 
  }
  void operator () ( NWorld::PFHeroHistoryData const& data )
  {
    pLast = &data;
  }
};

class MinHealth
{
public:
  MinHealth() {}
  float minHealth;

  void Init ( NWorld::PFHeroHistoryData const& data ) 
  {
    minHealth = data.health;
  }

  void operator () ( NWorld::PFHeroHistoryData const& data )
  {
    if ( minHealth > data.health )
      minHealth = data.health;
  }
};

class MilageCalculator
{
public:
  MilageCalculator() : distance(0.f) {}
  float distance;

  void Init( NWorld::PFHeroHistoryData const& data )
  {
    pCur = &data;
  }

  void operator () ( NWorld::PFHeroHistoryData const& data )
  {
    if (pCur)
      distance += (pCur->pos - data.pos).Length();

    pCur = &data;
  }
private:
  NWorld::PFHeroHistoryData const * pCur;
};

class GetPosition
{
public:
  GetPosition() {}
  CVec3 pos;

  void Init ( NWorld::PFHeroHistoryData const& data ) 
  {
    pos = data.pos;
  }

  void operator () ( NWorld::PFHeroHistoryData const& data )
  {
    pos = data.pos;
  }
};

//////////////////////////////////////////////////////////////////////////
// Kill by tower stuff
//////////////////////////////////////////////////////////////////////////
struct TowerCollaborationEnumerator_
{
  TowerCollaborationEnumerator_(): totalDamageDealedToVictim(0.f) {}
  void operator()(CObj<NWorld::PFBaseApplicator> &applicator)
  {
    NWorld::PFApplDamage const *pApplDamage = dynamic_cast<NWorld::PFApplDamage const *>(applicator.GetPtr());
    if (!pApplDamage)
    {
      return;
    }
    float damageDealed = pApplDamage->GetDamageDealed();
    totalDamageDealedToVictim += damageDealed;

    NWorld::PFBaseUnit* pSlayer = applicator->GetAbilityOwner();
    NWorld::PFTower *pTowerSlayer = dynamic_cast<NWorld::PFTower *>(pSlayer);
    if (pTowerSlayer)
    {
      towersCollaborated[pTowerSlayer->GetObjectId()] += damageDealed;
    }
  }

  nstl::map<int, float> towersCollaborated;
  float totalDamageDealedToVictim;
};

bool HasTowerTakenMore_(CPtr<NWorld::PFBaseUnit> pVictim, float ratio, float assistTime)
{
  TowerCollaborationEnumerator_ eTower;
  EnumerateAppliedApplicators(pVictim, assistTime, eTower);

  nstl::map<int, float>::const_iterator const iEnd = eTower.towersCollaborated.end();
  for (nstl::map<int, float>::const_iterator i = eTower.towersCollaborated.begin(); i != iEnd; ++i)
  {
    if (i->second > ratio * eTower.totalDamageDealedToVictim)
    {
      return true;
    }
  }
  return false;
}
}


namespace NWorld
{

bool PFKillerVictimEvent::IsCurrentHeroEventParticipant( PFPlayer const * pCurentPlayer )
{
  CPtr<NWorld::PFBaseUnit> pLocalHero(NULL);
  if ( pCurentPlayer )
  {
    pLocalHero = (NWorld::PFBaseUnit*)pCurentPlayer->GetHero();
  }

  if ( !IsValid(pLocalHero) )
  {
    return false;
  }

  // it's not only killer - it is person who made achievement (incl. priestess)
  if ( IsValid(GetOwner()) && IsValid(pVictim) )
  {
    if ( (pLocalHero == GetOwner()) || (pLocalHero == pVictim.GetPtr()) )
      return true;
  }

  return false;
}


PFAchievBase::PFAchievBase( NDb::AchievBase const& dbDesc, PFWorld* world ) 
 : PFWorldObjectBase( world, 0 )
 , pDB(&dbDesc)
 , pEvent(0)
 , count(0)
 , maxRank(0)
 , score(0)
 , newScore(0)
#ifndef _SHIPPING
 , timeToPlayFakeAchiev(0.0f)
#endif
{
}

void PFAchievBase::CreateUIEvent()
{
  if ( !pDB->evUI.IsEmpty() )
    pEvent = new NGameX::PFUIEvent( pDB->evUI, 0 );
}

void PFAchievBase::Init( const CPtr<NWorld::PFBaseHero> owner, CPtr<NWorld::PFStatistics> statistics )
{
  CreateUIEvent();

  pOwner = owner;
  if (pEvent)
    pEvent->SetOwner(pOwner.GetPtr());

  pStatistics = statistics;
}

void PFAchievBase::Process()
{
  ProcessCustom();

  ++count;

  // send UI event
  SendUIEvent();

  // update owners scores
  UpdateScore();

  PFHeroStatistics &stat = *pOwner->GetHeroStatistics();

  int delta = newScore - score;
  if (delta > 0)
  {
    stat.AddAchievementScore(delta);
    score = newScore;    
  }

  StatisticService::RPC::SessionEventInfo params;
  params.intParam1 = GetDBBase()->GetDBID().GetHashKey();
  pOwner->LogSessionEvent(SessionEventType::Deed, params);

  //add prime 
  if (pDB->naftaAward > 0)
  {
    pOwner->AddGold(pDB->naftaAward);
    pOwner->LogSessionEvent(SessionEventType::NaftaIncomeFromAchievement, params);
  }
}

#ifndef _SHIPPING
void PFAchievBase::OnCheatPlay( float time )
{
  timeToPlayFakeAchiev = time;
}

bool PFAchievBase::Step(float dtInSeconds)
{
  if ( timeToPlayFakeAchiev > 0.0f )
  {
    timeToPlayFakeAchiev -= dtInSeconds;
    if ( timeToPlayFakeAchiev <= 0.0f )
    {
      count = 1;
      SendUIEvent();
      timeToPlayFakeAchiev = 0.0f;
    }
  }
  return true;
}

#endif


void PFAchievBase::SendUIEvent()
{
  // send UI message
  AchievementsNameMap eventData(this);
  eventData.SetOwner(pOwner.GetPtr());
  eventData.SetAchievementName(pDB->name.GetText());

  NGameX::AnnouncementParams announcementParams;

  announcementParams.achiev = this;
  announcementParams.killer = pOwner;

  NGameX::AdventureScreen::Instance()->OnUIEvent(pEvent, &eventData, &announcementParams);
}

void PFAchievBase::UpdateScore()
{
  newScore = pDB->perAchievementScore * count;
  if (pDB->limit)
  {
    newScore = Clamp( newScore, 0, pDB->limit );
  }
}

bool PFAchievBase::IsNoAssistance( const CPtr<PFBaseUnit>& pVictim )
{
  NI_ASSERT(StatisticsStuff::IsBoss(pVictim.GetPtr()), "Wrong function call. Victim is BOSS-only.");

  vector<PFBaseHero*> assistants;
  pVictim->GetWorld()->GetAIWorld()->GetAssistants(pVictim, pOwner.GetPtr(), assistants);

  if (assistants.empty())
  {
    return true;
  }
  return false;
}

//////////////////////////////////////////////////////////////////////////
// Ruler achievement base class
//////////////////////////////////////////////////////////////////////////
PFAchievRuler::PFAchievRuler( CreateParams const &db, PFWorld* world )
 : Base(db, world)
 , curVal(0)
 , maxSpree(0)
{
}

void PFAchievRuler::OnOwnerDie()
{
  if (GetDB().breakOnDeath)
    curVal = 0;
}

// update ruler rank
void PFAchievRuler::ProcessCustom()
{
  NI_ASSERT(curVal >= GetDB().start, "Wrong ruller process call.");
  int rank = (curVal - GetDB().start) / GetDB().step + 1;

  maxRank = max(maxRank, rank);
}

void PFAchievRuler::IncreaseValue()
{
  bool needProcess = false;
  ++curVal;

  maxSpree = max(curVal, maxSpree);

  if (curVal >= GetDB().start)
  {
    needProcess = !((curVal - GetDB().start) % GetDB().step);
  }

  if (needProcess)
    Process();
}

#ifndef _SHIPPING
void PFAchievRuler::OnCheatPlay( float time )
{
  curVal = GetDB().start+1;
  Base::OnCheatPlay( time );
}
#endif

void PFAchievRuler::SendUIEvent()
{
  NI_ASSERT(curVal >= GetDB().start, "Achievements logical error!");

  // send UI message
  AchievementsNameMap eventData(this);
  eventData.SetOwner(pOwner.GetPtr());
  eventData.SetAchievementCount(curVal);
  eventData.SetAchievementName(GetDB().name.GetText());

  NDb::EMessage id = ((curVal == GetDB().start)? NDb::MESSAGE_SIMPLE_MESSAGE : NDb::MESSAGE_LINEAR_FEAT_MESSAGE);
  pEvent->SetCurLinearMessageID(id);

  NGameX::AnnouncementParams announcementParams;

  announcementParams.achiev = this;
  announcementParams.killer = pOwner;

  NGameX::AdventureScreen::Instance()->OnUIEvent(pEvent, &eventData, &announcementParams);
}

//////////////////////////////////////////////////////////////////////////
// First Blood
//////////////////////////////////////////////////////////////////////////
void PFAchievFirstBlood::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( pVictim->IsTrueHero() )
    if ( pStatistics->isFirstKill() )
      Process();
}

//////////////////////////////////////////////////////////////////////////
// Double kill
//////////////////////////////////////////////////////////////////////////
void PFAchievDoubleKill::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;

  if ( pOwner->GetHeroStatistics()->GetTotalNumHeroKillsInTime( GetDB().timeLimit ) == 2 )
    Process();
}

//////////////////////////////////////////////////////////////////////////
// Mass kill
//////////////////////////////////////////////////////////////////////////
void PFAchievMassKill::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;

  int killsCount = pOwner->GetHeroStatistics()->GetTotalNumHeroKillsInTime( GetDB().timeLimit );

  if ( killsCount >= GetDB().cnt && killsCount > maxKillCount )
  {
    maxKillCount = killsCount;
  }

  if ( killsCount == GetDB().cnt )
  {
    Process();
  }
}

//////////////////////////////////////////////////////////////////////////
// Double Assist
//////////////////////////////////////////////////////////////////////////
void PFAchievDoubleAssist::OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( pOwner->GetHeroStatistics()->GetTotalNumHeroAssistInTime( GetDB().timeLimit ) == 2 )
    Process();
}

//////////////////////////////////////////////////////////////////////////
// Mass Assist
//////////////////////////////////////////////////////////////////////////
void PFAchievMassAssist::OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( pOwner->GetHeroStatistics()->GetTotalNumHeroAssistInTime( GetDB().timeLimit ) == GetDB().cnt )
  {
    pOwner->GetHeroStatistics()->ResetHeroAssistsTimes();
    Process();
  }
}

//////////////////////////////////////////////////////////////////////////
// Ceremonial kill
//////////////////////////////////////////////////////////////////////////
void PFAchievCeremonialKill::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( pVictim->IsTrueHero() )
  {
    if (pVictim->GetVariableValue("KUStickApplied") > 0.0f)
    {
      Process();
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// First Assault
//////////////////////////////////////////////////////////////////////////
PFAchievFirstAssault::PFAchievFirstAssault( CreateParams const &db, PFWorld* world )
 : Base( db, world )
{
}

void PFAchievFirstAssault::ProcessCustom()
{
  pStatistics->NoMoreFirstAssault();
}

void PFAchievFirstAssault::OnTowerDestroy( const CPtr<PFTower>& pTower )
{
  // Process only once
  if ( pStatistics->WasFirstAssault() )
    return;

  // skip tower deny 
  if (pOwner->GetFaction() == pTower->GetFaction())
    return;

  if (pStatistics->isFirstTowerDestroy())
  {
    Process();
  }
}

void PFAchievFirstAssault::OnTowerAssist( const CPtr<PFTower>& pTower )
{
  if ( pStatistics->WasFirstAssault() )
    return;

  if (pStatistics->isFirstTowerDestroy())
  {
    Process();
  }
}

//////////////////////////////////////////////////////////////////////////
// Tower Deny
//////////////////////////////////////////////////////////////////////////
void PFAchievTowerDeny::OnTowerDestroy( const CPtr<PFTower>& pTower )
{
  if (pOwner->GetFaction() == pTower->GetFaction())
  {
    Process();
  }
}

//////////////////////////////////////////////////////////////////////////
// Clearing Way
//////////////////////////////////////////////////////////////////////////
void PFAchievClearWay::OnTowerDestroy( const CPtr<PFTower>& pTower )
{
  // skip tower deny 
  if (pOwner->GetFaction() == pTower->GetFaction())
    return;

  PFHeroStatistics &stat = *pOwner->GetHeroStatistics();

  if ( GetDB().minClearWayTowers == stat.GetNumTowersKilled(pTower->GetRouteId(), true, true))
    Process();
}

void PFAchievClearWay::OnTowerAssist( const CPtr<PFTower>& pTower )
{
  PFHeroStatistics &stat = *pOwner->GetHeroStatistics();

  if ( GetDB().minClearWayTowers == stat.GetNumTowersKilled(pTower->GetRouteId(), true, true))
    Process();
}

//////////////////////////////////////////////////////////////////////////
// Base strike
//////////////////////////////////////////////////////////////////////////(
PFAchievBaseStrike::PFAchievBaseStrike(CreateParams const &db, PFWorld* world)
 : Base(db, world)
 , barracks(0)
{
}

void PFAchievBaseStrike::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if (dynamic_cast<PFQuarters *>(pVictim.GetPtr()))
  {
    ++barracks;

    if (GetDB().minBarracks == barracks)
      Process();
  }
}

//////////////////////////////////////////////////////////////////////////
// War Lord
//////////////////////////////////////////////////////////////////////////
void PFAchievWarLord::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if (dynamic_cast<PFCommonCreep *>(pVictim.GetPtr()))
  {
    IncreaseValue();
  }
}

void PFAchievWarLord::UpdateScore()
{
  NI_ASSERT(curVal >= GetDB().start, "Achievements logical error!");
  newScore += (int(GetDB().multiplier * curVal) / GetDB().step);
}

//////////////////////////////////////////////////////////////////////////
// Forest Hunter
//////////////////////////////////////////////////////////////////////////
void PFAchievForestHunter::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if (dynamic_cast<PFNeutralCreep *>(pVictim.GetPtr()))
  {
    IncreaseValue();
  }
}

void PFAchievForestHunter::UpdateScore()
{
  NI_ASSERT(curVal >= GetDB().start, "Achievements logical error!");
  newScore += (int(GetDB().multiplier * curVal) / GetDB().step);
}

//////////////////////////////////////////////////////////////////////////
// Vandalism
//////////////////////////////////////////////////////////////////////////
void PFAchievVandalism::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if (pVictim->GetUnitType() == NDb::UNITTYPE_BUILDING)
  {
    PFBuilding const *pBuilding = dynamic_cast<PFBuilding const *>(pVictim.GetPtr());

    if (pBuilding && NDb::ROUTE_TREE == pBuilding->GetRouteId() && pBuilding->IsDecoration())
    {
       IncreaseValue();
    }
  }
}

void PFAchievVandalism::UpdateScore()
{
  NI_ASSERT(curVal >= GetDB().start, "Achievements logical error!");
  newScore += (int(GetDB().multiplier * curVal));
}

//////////////////////////////////////////////////////////////////////////
// Clean up creeps
//////////////////////////////////////////////////////////////////////////
PFAchievCleanUpCreeps::PFAchievCleanUpCreeps(CreateParams const &db, PFWorld* world) : Base(db, world)
{
  // reset time array
  creepKillTime.resize(GetDB().minCreepsKilled);
  for (int i = 0; i < creepKillTime.size(); ++i)
  {
    creepKillTime[i] = -1.f;
  }
}

void PFAchievCleanUpCreeps::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if (dynamic_cast<PFCommonCreep *>(pVictim.GetPtr()))
  {
    StatisticsStuff::UpdateArray_(creepKillTime.begin(), creepKillTime.size(), curTime);
    float const oldKillTime = creepKillTime[creepKillTime.size() - 1];
    if (oldKillTime >= 0.f && creepKillTime[0] - oldKillTime < GetDB().timePeriod)
    {
      Process();

      // reset array
      for (int i = 0; i < creepKillTime.size(); ++i)
      {
        creepKillTime[i] = -1.f;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// Killing spree
//////////////////////////////////////////////////////////////////////////
void PFAchievKillingSpree::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( pVictim->IsTrueHero() )
  {
    IncreaseValue();
  }
}

void PFAchievKillingSpree::UpdateScore()
{
  NI_ASSERT(curVal >= GetDB().start, "Achievements logical error!");
  newScore += int(curVal * GetDB().multiplier);
}

//////////////////////////////////////////////////////////////////////////
// Assisting spree
//////////////////////////////////////////////////////////////////////////
void PFAchievAssistingSpree::OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( pVictim->IsTrueHero() )
  {
    IncreaseValue();
  }
}

void PFAchievAssistingSpree::UpdateScore()
{
  NI_ASSERT(curVal >= GetDB().start, "Achievements logical error!");
  newScore += int(curVal * GetDB().multiplier);
}

//////////////////////////////////////////////////////////////////////////
// Demolishing spree
//////////////////////////////////////////////////////////////////////////
void PFAchievDemolishingSpree::OnTowerDestroy( const CPtr<PFTower>& pTower )
{
  // skip tower deny 
  if (pOwner->GetFaction() == pTower->GetFaction())
    return;

  IncreaseValue();
}

void PFAchievDemolishingSpree::UpdateScore()
{
  NI_ASSERT(curVal >= GetDB().start, "Achievements logical error!");
  newScore += int(curVal * GetDB().multiplier);
}

//////////////////////////////////////////////////////////////////////////
// Dragon slayer
//////////////////////////////////////////////////////////////////////////
PFAchievDragonSlayer::PFAchievDragonSlayer(CreateParams const &db, PFWorld* world)
 : Base(db, world)
 , was(false)
 , time(-1.0f)
{
}

void PFAchievDragonSlayer::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  // this achievement give only once per game
  if ( was )
  {
    return;
  }

  if (IsDragon(pVictim.GetPtr()))
  {
    // If no kill assistance, then it is a Legend achievement to award
    if ( PFAchievBase::IsNoAssistance(pVictim) )
      return;


    // Проверяем, что мы не убийца
    if ( IsValid(pEvent) && IsValid(NGameX::AdventureScreen::Instance()->GetPlayer()) )
    {
      CPtr<NWorld::PFBaseUnit> pMyHero(NULL);
      pMyHero = (NWorld::PFBaseUnit*)(NGameX::AdventureScreen::Instance()->GetPlayer()->GetHero());

      if ( IsValid(pMyHero) )
      {
        if ( IsValid(pKiller) )
        {
          if ( pKiller != pMyHero )
          {
            vector<PFBaseHero*> assistants;
            pVictim->GetWorld()->GetAIWorld()->GetAssistants(pVictim, pOwner.GetPtr(), assistants);

            bool isAssist = false;
            for ( int i = 0; i < assistants.size(); i++ )
            {
              if ( pMyHero == assistants[i] )
              {
                isAssist = true;
                break;
              }
            }

            // Проверяем, что мы и не ассистили
            if ( !isAssist && pKiller->GetTeamId() == NGameX::AdventureScreen::Instance()->GetPlayer()->GetTeamID() )
            {
              // send UI message
              AchievementsNameMap eventData(this);
              eventData.SetOwner(pOwner.GetPtr());
              eventData.SetAchievementName(pDB->name.GetText());

              NGameX::AnnouncementParams announcementParams;

              announcementParams.achiev = this;
              announcementParams.killer = pOwner;

              NGameX::AdventureScreen::Instance()->OnUIEvent( pEvent, &eventData, &announcementParams, true );  
            }
          }
        }
      }
    }

    if ( pKiller == pOwner )
    {
      Process();
    }

    was = true;
    time = curTime;
    return;
  }
}

void PFAchievDragonSlayer::OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  // this achievement give only once per game
  if (was)
    return;

  // Если мы убийца, то не показываем ачивку - тк показали уже в OnKill
  if ( pKiller == pOwner )
  {
    was = true;
    return;
  }

  if (IsDragon(pVictim.GetPtr()))
  {
    Process();
    was = true;
    time = curTime;
  }
}

//////////////////////////////////////////////////////////////////////////
// Kitty slayer
//////////////////////////////////////////////////////////////////////////
PFAchievKittySlayer::PFAchievKittySlayer(CreateParams const &db, PFWorld* world)
 : Base(db, world)
 , killCount(0)
 , assistCount(0)
 , time(-1.0f)
{
}

void PFAchievKittySlayer::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( pDB->limit && pDB->perAchievementScore && killCount + assistCount >= pDB->limit/pDB->perAchievementScore )
    return;

  if (IsKitty(pVictim.GetPtr()))
  {
    // Проверяем, что мы не убийца
    if ( IsValid(pEvent) && IsValid(NGameX::AdventureScreen::Instance()->GetPlayer()) )
    {
      CPtr<NWorld::PFBaseUnit> pMyHero(NULL);
      pMyHero = (NWorld::PFBaseUnit*)(NGameX::AdventureScreen::Instance()->GetPlayer()->GetHero());

      if ( IsValid(pMyHero) )
      {
        if ( IsValid(pKiller) )
        {
          if ( pKiller != pMyHero )
          {
            vector<PFBaseHero*> assistants;
            pVictim->GetWorld()->GetAIWorld()->GetAssistants(pVictim, pOwner.GetPtr(), assistants);

            bool isAssist = false;
            for ( int i = 0; i < assistants.size(); i++ )
            {
              if ( pMyHero == assistants[i] )
              {
                isAssist = true;
                break;
              }
            }

            // Проверяем, что мы и не ассистили
            if ( !isAssist && pKiller->GetTeamId() == NGameX::AdventureScreen::Instance()->GetPlayer()->GetTeamID() )
            {
              // send UI message
              AchievementsNameMap eventData(this);
              eventData.SetOwner(pOwner.GetPtr());
              eventData.SetAchievementName(pDB->name.GetText());

              NGameX::AnnouncementParams announcementParams;

              announcementParams.achiev = this;
              announcementParams.killer = pOwner;

              NGameX::AdventureScreen::Instance()->OnUIEvent( pEvent, &eventData, &announcementParams, true );  
            }
          }
        }
      }
    }

    if ( pKiller == pOwner )
    {
      killCount++;
      Process();
    }
    time = curTime;
  }
}

void PFAchievKittySlayer::OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( pDB->limit && pDB->perAchievementScore && killCount + assistCount >= pDB->limit/pDB->perAchievementScore )
    return;

  // Если мы убийца, то не показываем ачивку - тк показали уже в OnKill
  if ( pKiller == pOwner )
  {
    return;
  }

  if (IsKitty(pVictim.GetPtr()))
  {
    assistCount++;
    Process();
    time = curTime;
  }
}

//////////////////////////////////////////////////////////////////////////
// Legend
//////////////////////////////////////////////////////////////////////////
PFAchievLegend::PFAchievLegend(CreateParams const &db, PFWorld* world)
 : Base(db, world)
 , was(false)
 , time(-1.0f)
{
}

void PFAchievLegend::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  // this achievement give only once per game
  if (was)
    return;

  typedef nstl::vector<NDb::Ptr<NDb::Creature>> Creatures;

  Creatures creatures = GetDB().creatures;

  for ( Creatures::iterator iter = creatures.begin(); iter != creatures.end(); iter++ )
  {
    if ( pVictim->DbUnitDesc() == *iter )
    {
      // check for assister
      if ( PFAchievBase::IsNoAssistance(pVictim) )
      {
        Process();
        was = true;
        time = curTime;
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// Duel
//////////////////////////////////////////////////////////////////////////
void PFAchievDuel::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;

  //////////////////////////////////////////////////////////////////////////
  // define beginning of the battle
  PFHeroStatistics &stat = *pOwner->GetHeroStatistics();
  float startTime = curTime - GetDB().timeLimit;

  // min health calculator
  MinHealth healthCalc;

  stat.ForAllHistoryAfterTime(startTime, healthCalc);

  if ( (pOwner->GetHealth()  <= pOwner->GetMaxHealth() * (GetDB().maxRestLifePercent / 100.f) ) 
    || (healthCalc.minHealth <= pOwner->GetMaxHealth() * (GetDB().minLifePercent / 100.f)) )
  {
    vector<PFBaseHero*> assistants;
    pVictim->GetWorld()->GetAIWorld()->GetAssistants(pVictim, pOwner.GetPtr(), assistants);

    if (assistants.empty())
    {
      pVictim->GetWorld()->GetAIWorld()->GetAssistants(pOwner.GetPtr(), pVictim, assistants);

      if (assistants.empty())
      {
        // check for creep support
        NonHeroAttackChecker ow, vi;
        pOwner->ForAllAppliedApplicatorsInHistoryLess(ow, GetDB().timeLimit);
        pVictim->ForAllAppliedApplicatorsInHistoryLess(vi, GetDB().timeLimit);

        if (!ow.Get() && !vi.Get())
          Process();
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// Chase
//////////////////////////////////////////////////////////////////////////
void PFAchievChase::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;
  
  //////////////////////////////////////////////////////////////////////////
  // define beginning of the battle
  PFHeroStatistics &stat = *pOwner->GetHeroStatistics();
  float startTime = curTime - GetDB().timeLimit;

  // calculate running distance 
  MilageCalculator milage;

  stat.ForAllHistoryAfterTime(startTime, milage);

  float limit = GetDB().distanceMult * pStatistics->GetWorldSize().Length();
  if (milage.distance > limit)
  {
    Process();
  }
}

//////////////////////////////////////////////////////////////////////////
// Avenge
//////////////////////////////////////////////////////////////////////////
void PFAchievAvenge::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;

  const vector<StatisticsStuff::HeroKillInstance> &killInstances = pStatistics->GetKillInstances();
  PFHeroStatistics &stat = *pOwner->GetHeroStatistics();

  nstl::vector<StatisticsStuff::HeroKillInstance>::const_iterator const end = killInstances.end();
  for(nstl::vector<StatisticsStuff::HeroKillInstance>::const_iterator it = killInstances.begin(); it != end; ++it)
  {
    StatisticsStuff::HeroKillInstance const &ki = *it;

    if (ki.pSlayer == pVictim && ki.time > curTime - GetDB().timeLimit && (ki.pVictim->GetFaction() == pOwner->GetFaction())) 
    {
      GetPosition posGetter;
      stat.ForAllHistoryAfterTime(ki.time, posGetter);

      if (fabs(ki.victimPosition - posGetter.pos) > GetDB().distanceLimit)
        Process();
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// Master Control
//////////////////////////////////////////////////////////////////////////
void PFAchievMasterControl::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;

  // Check master control
  ControlApplicatorChecker f(pOwner);
  pVictim->ForAllAppliedApplicators(f);

  if (f.Get())
  {
    IncreaseValue();
  }
}

void PFAchievMasterControl::OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  // totally similar OnKill() routine
  if ( !pVictim->IsTrueHero() )
    return;

  // Check master control
  ControlApplicatorChecker f(pOwner);
  pVictim->ForAllAppliedApplicators(f);

  if (f.Get())
  {
    IncreaseValue();
  }
}

void PFAchievMasterControl::UpdateScore()
{
  NI_ASSERT(curVal >= GetDB().start, "Achievements logical error!");
  newScore += int(curVal * GetDB().multiplier);
}

//////////////////////////////////////////////////////////////////////////
// Dominating
//////////////////////////////////////////////////////////////////////////
void PFAchievDominate::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;

  PFBaseHero *pHero = static_cast<PFBaseHero *>(pVictim.GetPtr());

  // update value
  curVal = pStatistics->GetDominate(pHero, pOwner);

  if ( pStatistics->CanDominate(pOwner, pHero) && (curVal >= GetDB().minKillsForDominate) )
  {
    // update UI data 
    PFKillerVictimEvent * pKillerVictimEvent = dynamic_cast<PFKillerVictimEvent *>( pEvent.GetPtr() );
    NI_DATA_VERIFY(pKillerVictimEvent, "Wrong type of event", return);
    pKillerVictimEvent->SetVictim(pHero);

    Process();
  }
}

#ifndef _SHIPPING
void PFAchievDominate::OnCheatPlay( float time )
{
  curVal = GetDB().minKillsForDominate+1;
  PFBaseHero *pHero = NGameX::AdventureScreen::Instance()->GetHero();
  if ( pHero )
  {
    PFKillerVictimEvent * pKillerVictimEvent = dynamic_cast<PFKillerVictimEvent *>( pEvent.GetPtr() );
    NI_DATA_VERIFY(pKillerVictimEvent, "Wrong type of event", return);
    pKillerVictimEvent->SetVictim(pHero);
    Base::OnCheatPlay( time );
  }
}
#endif

void PFAchievDominate::ProcessCustom()
{
  NI_ASSERT(curVal >= GetDB().minKillsForDominate, "Wrong ruller process call.");
  int rank = (curVal - GetDB().minKillsForDominate) + 1; // similar Ruler with step == 1

  maxRank = max(maxRank, rank);
}

void PFAchievDominate::SendUIEvent()
{
  NI_ASSERT(curVal >= GetDB().minKillsForDominate, "Achievements logical error!");

  // send UI message
  AchievementsNameMap eventData(this);
  eventData.SetOwner(pOwner.GetPtr());
  eventData.SetAchievementCount(curVal);
  eventData.SetAchievementName(GetDB().name.GetText());

  NDb::EMessage id = ((curVal == GetDB().minKillsForDominate)? NDb::MESSAGE_SIMPLE_MESSAGE : NDb::MESSAGE_LINEAR_FEAT_MESSAGE);
  pEvent->SetCurLinearMessageID(id);

  NGameX::AnnouncementParams announcementParams;

  announcementParams.achiev = this;
  announcementParams.killer = pOwner;

  NGameX::AdventureScreen::Instance()->OnUIEvent(pEvent, &eventData, &announcementParams);
}

PFAchievDominate::PFAchievDominate( CreateParams const &db, PFWorld* world )
 : Base(db, world)
 , curVal(0)
{
}

void PFAchievDominate::CreateUIEvent()
{
  if ( !pDB->evUI.IsEmpty() )
    pEvent = new PFKillerVictimEvent( pDB->evUI, 0 );
}

//////////////////////////////////////////////////////////////////////////
// Vendetta
//////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING
void PFAchievVendetta::OnCheatPlay( float time )
{
  PFBaseHero *pHero = NGameX::AdventureScreen::Instance()->GetHero();
  if ( pHero )
  {
    PFKillerVictimEvent * pKillerVictimEvent = dynamic_cast<PFKillerVictimEvent *>( pEvent.GetPtr() );
    NI_DATA_VERIFY(pKillerVictimEvent, "Wrong type of event", return);
    pKillerVictimEvent->SetVictim(pHero);
    Base::OnCheatPlay( time );
  }
}
#endif

void PFAchievVendetta::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;

  PFBaseHero *pHero = static_cast<PFBaseHero *>(pVictim.GetPtr());

  bool didVictimDominatedMe = (pStatistics->GetDominate(pOwner, pHero, true) >= GetDB().minKillsForDominate);

  // no vendetta repetitions
  if (didVictimDominatedMe && pStatistics->CanDominate( pHero, pOwner ) )
  {
    // pVictim will never dominate me!
    pStatistics->NoMoreDomination(pHero, pOwner);

    // update UI data 
    PFKillerVictimEvent * pKillerVictimEvent = dynamic_cast<PFKillerVictimEvent *>( pEvent.GetPtr() );
    NI_DATA_VERIFY(pKillerVictimEvent, "Wrong type of event", return);
    pKillerVictimEvent->SetVictim(pHero);

    Process();
  }
}

void PFAchievVendetta::CreateUIEvent()
{
  if ( !pDB->evUI.IsEmpty() )
    pEvent = new PFKillerVictimEvent( pDB->evUI, 0 );
}

//////////////////////////////////////////////////////////////////////////
// Border guard
//////////////////////////////////////////////////////////////////////////
void PFAchievBorderGuard::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;  

  // has tower taken >50% of live?
  if (HasTowerTakenMore_(pVictim, GetDB().byTowerLifePercent * 0.01f, GetDB().timePeriod))
  {
    Process();
  }
}

void PFAchievBorderGuard::OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  if ( !pVictim->IsTrueHero() )
    return;  

  // has tower taken >50% of live?
  if (HasTowerTakenMore_(pVictim, GetDB().byTowerLifePercent * 0.01f, GetDB().timePeriod))
  {
    Process();
  }
}
//////////////////////////////////////////////////////////////////////////
// Saviour
//////////////////////////////////////////////////////////////////////////
void PFAchievSaviour::OnApplicatorUse ( const PFBaseApplicator* pAppl, float curTime )
{
  if ( !pAppl->GetReceiver()->IsTrueHero() )
    return; 

  PFBaseHero *pLamb = static_cast<PFBaseHero *>(pAppl->GetReceiver().GetPtr());

  // skip itself
  if (pLamb == pOwner.GetPtr())
    return;

  // check friendly hero
  if (pLamb->GetFaction() != pOwner->GetFaction())
    return;

  // skip achievement cooldown
  PFHeroStatistics &stat = *pLamb->GetHeroStatistics();
  if (stat.GetSaviourTime() + GetDB().cooldownPeriod > curTime)
    return;

  // check rest life percent 
  if (pLamb->GetHealthPercent() > (GetDB().minLifePercent / 100.f))
    return;

  // check for damage
  HeroAttackChecker damageDealed;
  pLamb->ForAllAppliedApplicatorsInHistoryLess(damageDealed, GetDB().damageDealedPeriod);
  if (!damageDealed.Get())
    return;

  // check for healing
  NDb::Ptr<NDb::BaseApplicator> const &db = pAppl->GetDBBase();
  if ( db->GetObjectTypeID() == NDb::HealApplicator::typeId && pAppl->GetTypeId() == PFApplHeal::typeId )
  {
    NDb::HealApplicator const *healApplDb = static_cast<NDb::HealApplicator const*>(db.GetPtr());
    const PFApplHeal * pHealAppl = static_cast<const PFApplHeal *>(pAppl);
    if ( healApplDb->healTarget == NDb::HEALTARGET_HEALTH && pHealAppl->GetAmountRestored() > EPS_VALUE )
    {
      CheckForRunProcess( pLamb, curTime );
      return;
    }
  }

  // check applicator type
  if ( IsApplicatorInList( pAppl->GetDBBase(), GetDB().applicatorTypes, ByTypeID ) )
  {
    CheckForRunProcess( pLamb, curTime );
    return;
  }

  if ( IsApplicatorInList( pAppl->GetDBBase(), GetDB().exactApplicators, ByDBID ) )
  {
    CheckForRunProcess( pLamb, curTime );
    return;
  }
}

void PFAchievSaviour::CheckForRunProcess( const PFBaseHero* lamb, float time )
{
  bool isFind = false;
  int index = 0;
  for ( int i = 0; i < saviourInfos.size(); i++ )
  {
    if ( saviourInfos[i].lamb == lamb )
    {
      index = i;
      isFind = true;
    }
  }

  if ( isFind )
  {
    // nope
  }
  else
  {
    SaviourInfo info;
    info.lamb = lamb;
    info.timeToLog = time;
    info.waitForDie = true;
    info.timeToProcess = 0.0f;
    saviourInfos.push_back( info );
  }
}

bool PFAchievSaviour::Step(float dtInSeconds)
{
#ifndef _SHIPPING
  Base::Step(dtInSeconds);
#endif

  bool needErase = false;
  for ( int i = 0; i < saviourInfos.size(); i++ )
  {
    SaviourInfo& info = saviourInfos[i];
    if ( info.waitForDie && IsValid(info.lamb) )
    {
      info.timeToProcess += dtInSeconds;
      if ( info.timeToProcess > GetDB().timeToLive )
      {
        if ( !info.lamb->IsDead() )
        {
          HeroAttackChecker damageDealed;
          info.lamb->ForAllAppliedApplicatorsInHistoryLess( damageDealed, GetDB().timeToNoDamage );
          if ( !damageDealed.Get() )
          {
            PFHeroStatistics &stat = *info.lamb->GetHeroStatistics();
            stat.SetSaviourTime(info.timeToLog+info.timeToProcess);
            Process();
          }
        }
        needErase = true;
        info.waitForDie = false;
        info.timeToProcess = 0.0f;
      }
    }
  }

  if ( needErase )
  {
    struct WaitForDieRemover
    {
      bool operator () (const SaviourInfo& info) { return !info.waitForDie; } 
    };

    saviourInfos.erase( remove_if( saviourInfos.begin(), saviourInfos.end(), WaitForDieRemover() ), saviourInfos.end() );
  }

  return true;
}


//////////////////////////////////////////////////////////////////////////
//
// Priestess section
// 
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Streak
//////////////////////////////////////////////////////////////////////////
PFAchievStreak::PFAchievStreak( CreateParams const &db, PFWorld* world ) 
: Base(db, world)
, streak(Statistics::EStreakCounterMode::WithGaps, GetDB().start)
{
}

// update rank
void PFAchievStreak::ProcessCustom()
{
  int rank = streak.DisplayLength();

  maxRank = max(maxRank, rank);
}

void PFAchievStreak::CheckForAchiev()
{
  bool needProcess = (streak.DisplayLength() > 0);

  if (needProcess)
    Process();
}

void PFAchievStreak::SendUIEvent()
{
  // send UI message
  AchievementsNameMap eventData(this);
  eventData.SetOwner(pOwner.GetPtr());
  eventData.SetAchievementCount(streak.DisplayLength());
  eventData.SetAchievementName(GetDB().name.GetText());

  NDb::EMessage id = ((streak.DisplayLength() > 1) ? NDb::MESSAGE_LINEAR_FEAT_MESSAGE : NDb::MESSAGE_SIMPLE_MESSAGE);
  pEvent->SetCurLinearMessageID(id);

  NGameX::AnnouncementParams announcementParams;

  announcementParams.achiev = this;
  announcementParams.killer = pOwner;

  NGameX::AdventureScreen::Instance()->OnUIEvent(pEvent, &eventData, &announcementParams);
}


//////////////////////////////////////////////////////////////////////////
// Ascension 
//////////////////////////////////////////////////////////////////////////
void PFAchievAscension::OnMinigameLevelEnd( const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum newStatus )
{
  PFHeroStatistics &stat = *pOwner->GetHeroStatistics();
  EMinigameLevelStatus::Enum status = stat.GetMinigamesStatus(game, levelIndex);

  switch ( newStatus )
  {
    //Fall through is OK here
  case EMinigameLevelStatus::Failed:
    streak.Reset();
  }

  if ( newStatus < status )
    return;

  //Улучшили результат, продвинем ачивменты
  switch ( newStatus )
  {
    //Fall through is OK here
  case EMinigameLevelStatus::Gold:
  case EMinigameLevelStatus::Silver:
  case EMinigameLevelStatus::Done:
    streak.CheckOut( levelIndex );
  }

  CheckForAchiev();
}

//////////////////////////////////////////////////////////////////////////
// Necklace of glory
//////////////////////////////////////////////////////////////////////////
void PFAchievNecklaceOfGlory::OnMinigameLevelEnd ( const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum newStatus )
{
  PFHeroStatistics &stat = *pOwner->GetHeroStatistics();
  EMinigameLevelStatus::Enum status = stat.GetMinigamesStatus(game, levelIndex);

  switch ( newStatus )
  {
    //Fall through is OK here
    case EMinigameLevelStatus::Failed:
    case EMinigameLevelStatus::Done:
      streak.Reset();
  }

  if ( newStatus < status )
    return;

  //Улучшили результат, продвинем ачивменты
  switch ( newStatus )
  {
    //Fall through is OK here
    case EMinigameLevelStatus::Gold:
    case EMinigameLevelStatus::Silver:
      streak.CheckOut( levelIndex );
  }

  CheckForAchiev();
}

//////////////////////////////////////////////////////////////////////////
// Gold rite
//////////////////////////////////////////////////////////////////////////
void PFAchievGoldRite::OnMinigameLevelEnd ( const NDb::DBID &game, int levelIndex, EMinigameLevelStatus::Enum newStatus )
{
  PFHeroStatistics &stat = *pOwner->GetHeroStatistics();
  EMinigameLevelStatus::Enum status = stat.GetMinigamesStatus(game, levelIndex);

  switch ( newStatus )
  {
    //Fall through is OK here
    case EMinigameLevelStatus::Failed:
    case EMinigameLevelStatus::Done:
    case EMinigameLevelStatus::Silver:
      streak.Reset();
  }

  if ( newStatus < status )
    return;

  //Улучшили результат, продвинем ачивменты
  switch ( newStatus )
  {
    //Fall through is OK here
    case EMinigameLevelStatus::Gold:
      streak.CheckOut( levelIndex );
  }

  CheckForAchiev();
}

//////////////////////////////////////////////////////////////////////////
// Craft Woman
//////////////////////////////////////////////////////////////////////////
PFAchievCraftWoman::PFAchievCraftWoman(CreateParams const &db, PFWorld* world) 
:  Base(db, world)
, was(0)
, curHearts(0.f)
{
}

void PFAchievCraftWoman::OnHeartsFromMG( float hearts )
{
  curHearts += hearts;

  if (!was)
  {
    if (curHearts >= GetDB().heartsCnt)
    {
      was = true;
      Process();
    }
  }
}

//////////////////////////////////////////////////////////////////////////
// First minigame complete
//////////////////////////////////////////////////////////////////////////
PFAchievFirstMinigameComplete::PFAchievFirstMinigameComplete(CreateParams const &db, PFWorld* world)
:  Base(db, world)
, was(0)
{
}

void PFAchievFirstMinigameComplete::OnMinigameComplete( const NDb::DBID &game )
{
  if (!was)
  {
    was = true;

    Process();
  }
}

//////////////////////////////////////////////////////////////////////////
void PFAchievSessionDuration::OnVictory( const NDb::EFaction failedFaction )
{
  if ( !( GetDB().loosers && failedFaction == pOwner->GetFaction() ) && !( GetDB().winners && failedFaction != pOwner->GetFaction() ) )
    return;

  float sessionTimeMinutes = GetWorld()->GetTimeElapsed() / 60.0f;

  if ( GetDB().minTime < sessionTimeMinutes && sessionTimeMinutes < GetDB().maxTime )
    Process();
}


//////////////////////////////////////////////////////////////////////////
// Boss Slayer
//////////////////////////////////////////////////////////////////////////
PFAchievBossSlayer::PFAchievBossSlayer(CreateParams const &db, PFWorld* world)
 : Base(db, world)
 , currentDataIdx(-1)
 , time(-1.0f)
 , was(false)
{
  CreateCustomEvents();
}

void PFAchievBossSlayer::CreateCustomEvents()
{
  CustomAchievData& creatures = GetDB().creatures;
  for ( CustomAchievData::const_iterator iter = creatures.begin(); iter != creatures.end(); ++iter )
  {
    if ( IsValid(iter->boss) && !iter->evUI.IsEmpty() )
      customEvents[iter->boss->GetDBID()] = new NGameX::PFUIEvent( iter->evUI, 0 );
  }
}

int PFAchievBossSlayer::HasAchievForVictim( const CPtr<PFBaseUnit>& pVictim )
{
  CustomAchievData& creatures = GetDB().creatures;

  int idx = 0;
  for ( CustomAchievData::const_iterator iter = creatures.begin(); iter != creatures.end(); ++iter, ++idx )
  {
    if ( IsValid(iter->boss) && pVictim->DbUnitDesc()->GetDBID() == iter->boss->GetDBID() )
      return idx;
  }

  return -1;
}

void PFAchievBossSlayer::ProcessAchiev( int achievDataIdx, float curTime )
{
  if ( was || achievDataIdx < 0 )   // this achievement give only once per game
    return;

  was = true;
  time = curTime;
  currentDataIdx = achievDataIdx;
  Process();
}

void PFAchievBossSlayer::Init( const CPtr<NWorld::PFBaseHero> owner, CPtr<NWorld::PFStatistics> statistics )
{
  CreateUIEvent();

  pOwner = owner;
  if (pEvent)
    pEvent->SetOwner(pOwner.GetPtr());

  CustomAchievData& creatures = GetDB().creatures;
  for ( CustomAchievData::const_iterator iter = creatures.begin(); iter != creatures.end(); ++iter )
  {
    if ( IsValid(iter->boss))
    {
      NGameX::PFUIEvent* customEvent = customEvents[iter->boss->GetDBID()];
      if (customEvent) customEvent->SetOwner(owner);
    }
  }

  pStatistics = statistics;
}

void PFAchievBossSlayer::SendUIEvent()
{
  // send UI message
  AchievementsNameMap eventData(this);
  eventData.SetOwner(pOwner.GetPtr());
  const CTextRef& name = (currentDataIdx >= 0) ? GetDB().creatures[currentDataIdx].name : GetDB().name;
  eventData.SetAchievementName(name.GetText());

  NGameX::AnnouncementParams announcementParams;

  announcementParams.achiev = this;
  announcementParams.killer = pOwner;


  NGameX::PFUIEvent* currentEvent = pEvent;
  if (currentDataIdx >= 0)
  {
    NGameX::PFUIEvent* customEvent = customEvents[GetDB().creatures[currentDataIdx].boss->GetDBID()];
    if (customEvent)
      currentEvent = customEvent;
  }
  
  NGameX::AdventureScreen::Instance()->OnUIEvent(currentEvent, &eventData, &announcementParams);
}

void PFAchievBossSlayer::UpdateScore()
{
  int achievScore = (currentDataIdx >= 0) ? GetDB().creatures[currentDataIdx].perAchievementScore : GetDB().perAchievementScore;
  newScore = achievScore * count;
  int limit = (currentDataIdx >= 0) ? GetDB().creatures[currentDataIdx].limit : GetDB().limit;
  if (limit)
  {
    newScore = Clamp( newScore, 0, limit );
  }
}






void PFAchievBossSlayer::OnKill( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  struct AddBossSlayerAchievFunctor
  {
    AddBossSlayerAchievFunctor( const CPtr<PFBaseUnit>& victim, const CPtr<PFBaseUnit>& killer, float curTime ) 
    {
      time = curTime;
      pVictim = victim;
      pKiller = killer;
    }
    
    void operator()(const NWorld::PFAchievBase* p) 
    { 
      if (p->GetDBBase()->achievType != NDb::ACHIEVEMENTTYPE_BOSSSLAYER)
        return;

      NWorld::PFAchievBossSlayer* achievBossSlayer = const_cast<NWorld::PFAchievBossSlayer*>(static_cast<const NWorld::PFAchievBossSlayer *> (p));
      if (IsValid(achievBossSlayer))
        achievBossSlayer->OnAssist(pVictim, pKiller, time);
    }

    float time;
    CPtr<PFBaseUnit> pVictim;
    CPtr<PFBaseUnit> pKiller;
  };

  struct ProcessAchievFunctor
  {
    ProcessAchievFunctor( const CPtr<PFBaseHero>& owner, const CPtr<PFBaseUnit>& victim, const CPtr<PFBaseUnit>& killer, float curTime ) 
    {
      time = curTime;
      pOwner = static_cast<PFBaseUnit*>(owner.GetPtr());
      pVictim = victim;
      pKiller = killer;
    }
    void operator()(NWorld::PFBaseHero &hero) 
    {
      if (&hero == pOwner)
        return;

      AddBossSlayerAchievFunctor f(pVictim, pKiller, time);
      hero.GetHeroStatistics()->ForAllAchievements( f );
      //hero.GetWorld()->GetStatistics()->AddAssist( pVictim, pOwner, &hero );
    }

    float time;
    CPtr<PFBaseUnit> pOwner;
    CPtr<PFBaseUnit> pVictim;
    CPtr<PFBaseUnit> pKiller;
  } functor (pOwner, pVictim, pKiller, curTime);

  int idx = HasAchievForVictim(pVictim);
  if (idx < 0)
    return;

  ProcessAchiev( idx, curTime );
  if (GetDB().creatures[idx].mode == NDb::BOSSSLAYERACHIEVMODE_FORALLTEAMMATES)
    GetWorld()->GetAIWorld()->ForAllHeroes( functor, pOwner->GetFaction() );
}

void PFAchievBossSlayer::OnAssist( const CPtr<PFBaseUnit>& pVictim, const CPtr<PFBaseUnit>& pKiller, float curTime )
{
  int idx = HasAchievForVictim(pVictim);
  if (idx < 0)
    return;

  if (GetDB().creatures[idx].mode == NDb::BOSSSLAYERACHIEVMODE_ONLYFORKILLER)
    return;

  ProcessAchiev( idx, curTime );
}

//////////////////////////////////////////////////////////////////////////


}

REGISTER_WORLD_OBJECT_NM(PFAchievBase, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievRuler, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievFirstBlood, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievDoubleKill, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievMassKill, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievDuel, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievChase, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievAvenge, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievDominate, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievVendetta, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievCeremonialKill, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievKillingSpree, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievDoubleAssist, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievMassAssist, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievSaviour, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievMasterControl, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievAssistingSpree, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievBorderGuard, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievFirstAssault, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievDemolishingSpree, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievTowerDeny, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievClearWay, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievBaseStrike, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievVandalism, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievWarLord, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievCleanUpCreeps, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievDragonSlayer, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievKittySlayer, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievLegend, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievForestHunter, NWorld);

REGISTER_WORLD_OBJECT_NM(PFAchievStreak, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievAscension, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievNecklaceOfGlory, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievGoldRite, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievCraftWoman, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievFirstMinigameComplete, NWorld);

REGISTER_WORLD_OBJECT_NM(PFAchievSessionDuration, NWorld);
REGISTER_WORLD_OBJECT_NM(PFAchievBossSlayer, NWorld);