#include "stdafx.h"

#include "PFImpulsiveBuffs.h"

#include "PFAIWorld.h"
#include "PFAbilityInstance.h"
#include "PFHero.h"
#include "PFTower.h"

#include "System\nalgoritm.h"
#include "Client/LobbyPvx/ClientAccountingGadget.h"

#include "..\Core\WorldCommand.h"

#include "../System/InlineProfiler.h"

#include "ImpulseBuffsController.h"

#ifndef VISUAL_CUTTED
#include "AdventureScreen.h"
#endif //VISUAL_CUTTED

#include "SessionEventType.h"

namespace
{
  bool g_enabledImpulsiveBuffs = false; // http://SITE
  bool g_disableZZBilling      = false;
  int  g_debugZZMoney          = 1e+6;
  int  g_forcedBuff            = -1;
  int  g_forceBuffRepeatCount  = 0;

  static float const GET_MONEY_INTERVAL = 60; //once per minute
  
}

namespace NWorld
{

#ifndef _SHIPPING

DEFINE_3_PARAM_CMD_CHECK( 0xF668B00, CmdUseImpulse, CPtr<PFBaseHero>, hero, NDb::ImpulseBuffs, impulseType, Target, target );

NCore::WorldCommand* CreateCmdUseImpulse( PFBaseHero * hero, NDb::ImpulseBuffs impulseType, Target const& target )
{
  // do not use target.IsValid(), because some impulses, such as Resurrection will not work!
  NI_VERIFY( target.IsPosition() || (target.IsObject() && IsValid( target.GetObject() ) ), "Invalid target!", return 0 );
  return new CmdUseImpulse( hero, impulseType, target );
}

bool CmdUseImpulse::CanExecute() const
{
  if ( hero )
    if ( const NWorld::PFPlayer * pPlayer = hero->GetPlayer() )
      if ( pPlayer->GetUserID() == GetId() || pPlayer->IsBot() )
        return true;
  return false;
}

void CmdUseImpulse::Execute( NCore::IWorldBase *pIWorld )
{
  NI_VERIFY(IsValid(hero), "target hero should be valid", return;)
  NGameX::IAdventureScreen * adventureScreen = hero->GetWorld()->GetIAdventureScreen();

  NI_VERIFY(IsValid(adventureScreen), "not valid advScreenInterface", return)
  if (adventureScreen->GetImpulseBuffsManager())
    adventureScreen->GetImpulseBuffsManager()->UseImpulse(hero, impulseType, target );
}
#endif

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// есть большой соблазн сделать юзание импульсов стейтом всегда,
// но на самом деле это далеко не очень хорошая идея. 
// ибо смена стейтов, которая может произойти далеко не всегда
// половину импульсов нам обломает или отложит на время, что выглядеть
// будет как явный баг
//////////////////////////////////////////////////////////////////////////

class PFUseImpulseState : public PFBaseHeroState
{
  WORLD_OBJECT_METHODS(0x2C742C40, PFUseImpulseState)

  explicit     PFUseImpulseState() {}
  virtual bool OnStep(float dt);
          bool IsBuffAbilityFinished() const;

  ZDATA_(PFBaseHeroState)
	NDb::Ptr<NDb::Ability> pBuff;
  bool                    isUsed;
  Target                  target;
  CObj<PFAbilityInstance> pAbilityInstance;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFBaseHeroState*)this); f.Add(2,&pBuff); f.Add(3,&isUsed); f.Add(4,&target); f.Add(5,&pAbilityInstance); return 0; }
  explicit PFUseImpulseState(CPtr<PFBaseHero> const& pOwner, NDb::Ptr<NDb::Ability> pBuff, Target target);
};

PFUseImpulseState::PFUseImpulseState(CPtr<PFBaseHero> const& pOwner, NDb::Ptr<NDb::Ability> pBuff, Target target)
  : PFBaseHeroState(pOwner)
  , pBuff(pBuff)
  , target(target)
  , isUsed(false)
{
}

bool PFUseImpulseState::OnStep(float dt)
{ 
  if( !IsUnitValid(pOwner) )
    return true;
  
  // yes! while 'ability end' problem is not fixed properly DO NOT TRY to do this in OnEnter
  if( !isUsed )
  {
    if( NULL != pOwner && NULL != pBuff)
      pAbilityInstance = pOwner->UseExternalAbility( pBuff, target );
    
    isUsed = true;
    return false;
  }
  
  return IsBuffAbilityFinished();
}

bool PFUseImpulseState::IsBuffAbilityFinished() const
{
  if (!pAbilityInstance)
    return true;

  bool isFinished  = pAbilityInstance->IsActivated();
  isFinished      &= !pOwner->IsInChannelling();

  return isFinished;
}

//////////////////////////////////////////////////////////////////////////
void ImpulsiveBuffsManager::CreateBuffs( vector<Impulse>* pResult)
{
  if( NULL == pResult )
    return;

  vector<NDb::ImpulsiveBuff> const& impulseBuffs = buffsDescriptions->buffs;
  NDb::BuyServicesContainer const* servicesCosts = buffsDescriptions->servicesCosts;

  NI_VERIFY(servicesCosts, "services costs are not filled!", return);

  vector<Impulse> buffs;
  
  for ( int i = 0; i< impulseBuffs.size(); i++)
  {
    NDb::ImpulsiveBuff ndbBuff = impulseBuffs[i];
    NI_VERIFY(ndbBuff.buffClass == NDb::IMPULSEBUFFCLASS_CLASS_BUFFHERO, "why do we have tower buff?", continue)
    
   Impulse & imp = pResult->push_back();

    imp.buff               = ndbBuff.buff;
    imp.goldCost           = servicesCosts->buffs[i].goldCost;
    imp.cooldownTime       = ndbBuff.cooldown;
    imp.priority           = ndbBuff.priority;
    imp.cooldown           = 0;
    imp.cooldownGroup      = ndbBuff.cooldownGroup;
    imp.canBeOfferedToDead = ndbBuff.canBeOfferedToDead;
    imp.offerTime          = ndbBuff.offerTime;
    imp.isSimple           = ndbBuff.isSimple;
    imp.impulseBuffIndex   = (NDb::ImpulseBuffs)i;
    imp.oncePerTeam        = ndbBuff.oncePerTeam;
    imp.accessInfo         = ndbBuff.accessInfo;
    imp.isForced           = false;
    
    for ( vector<NDb::Ptr<NDb::ImpulsiveEvent> >::const_iterator iEvt = ndbBuff.events.begin(), iEnd = ndbBuff.events.end(); iEvt != iEnd; ++iEvt )
    {
      if ( *iEvt )
        imp.events.push_back( (*iEvt)->Create(this) );
    }

  }
}

//////////////////////////////////////////////////////////////////////////
ImpulsiveBuffsManager::ImpulsiveBuffsManager(PFWorld* pWorld, PFPlayer * ourPlayer)
  : globalCooldown(0.0f)
  , accounting(NULL)
  , pWorld(pWorld)
  , player(ourPlayer)
  , timeSinceLastGetMoney(0)
{
  NI_ASSERT(IsValid(ourPlayer), "player should be valid");

  NI_PROFILE_FUNCTION

  billingResult = new BillingResult;

  for( vector<int>::iterator it = defaultCountingWeights.weights.begin(), end = defaultCountingWeights.weights.end(); it != end; ++it )
    *it = 1;

  buffsDescriptions = NDb::SessionRoot::GetRoot()->logicRoot->impulsiveBuffs;
  NI_VERIFY( buffsDescriptions, "Cannot retrieve impulsive buffs buffsDescriptions form file 'ImpulsiveBuffs/_.IBCN'!", return; );

  teamBuffAccessibilities.resize(buffsDescriptions->buffs.size());
  CreateBuffs(&impulseBuffs);
}

bool Impulse::IsEnabled(PFBaseHero* pUnit, NDb::ImpulsiveEventType const type, const Target& target) const
{
  if ( isForced )
  {
    return true;
  }

  for ( vector<CObj<ImpulsiveEvent>>::const_iterator iEvt = events.begin(), iEnd = events.end(); iEvt != iEnd; ++iEvt )
  {
    if( !(*iEvt) )
      return false;

    if( type == !(*iEvt)->GetType() ) 
      continue;

	Target notConstTarget = target;
    if( !(*iEvt)->IsEnabled(pUnit, notConstTarget) )
      return false; 
  }
  return true;
}

void ImpulsiveBuffsManager::Step(float dt)
{
  if( !g_enabledImpulsiveBuffs )
    return;
  
  // update buffs usage info
  for( THeroInfos::iterator hero_it = heroInfos.begin(), hero_end = heroInfos.end(); hero_it != hero_end; ++hero_it ) 
    for( TBuffUsageInfo::iterator it = hero_it->second.begin(), end = hero_it->second.end(); it != end; ++it )
      it->second += dt;
  
  struct Ticker 
  {
    Ticker(float dt) : dt(dt) {}
    void operator()(Impulse& data) 
    { 
      if (data.cooldown > 0) 
        data.cooldown = max( 0.0f, data.cooldown - dt );
      for( vector<CObj<ImpulsiveEvent>>::iterator it = data.events.begin(), end = data.events.end(); it != end; ++it)
        (*it)->Step( dt );
    }
    float dt;
  };
  for_each(impulseBuffs.begin(), impulseBuffs.end(), Ticker(dt));

  if ( globalCooldown > 0 )
    globalCooldown = max( 0.0f, globalCooldown - dt );
}

void ImpulsiveBuffsManager::Update(float dt )
{
  NI_PROFILE_FUNCTION

  NI_VERIFY( IsValid(GetHero()), "Invalid hero!", return; );

  if( !g_enabledImpulsiveBuffs || !buffsDescriptions )
    return;

  Step(dt);
  
  if( !accounting )
  {
    accounting = GetHero()->GetWorld()->GetAccounting();
    if( accounting && !g_disableZZBilling )
    {
      accounting->GetMoney( billingResult.Get(), &BillingResult::onGetMoneyCall);
      timeSinceLastGetMoney = 0;  
    }
  }
  
  if( !accounting && !g_disableZZBilling )
    return;
    
 
  if (!g_disableZZBilling && (timeSinceLastGetMoney+=dt) > GET_MONEY_INTERVAL && accounting)
  {
    accounting->GetMoney( billingResult.Get(), &BillingResult::onGetMoneyCall);
    timeSinceLastGetMoney = 0;
  }


  if ( ( globalCooldown > 0 ) && ( g_forcedBuff == -1 ))
    return;
  
  SuggestImpulses();
}


void ImpulsiveBuffsManager::SuggestImpulses()
{
  Target target;
  target.SetUnit( CPtr<PFBaseUnit>(GetHero()) );

  PFBaseHero * hero = GetHero();
  NI_VERIFY(IsValid(hero), "invalid hero for impulses", return);
  Impulse * impulseToSuggest = 0; 

  for(int i = 0; i<impulseBuffs.size(); i++)
  {
    Impulse * impulse = &impulseBuffs[i];

    // check cost
    int moneyNeeded = impulse->goldCost;

    int level      = impulse->accessInfo.level;
    int gamesLimit = GetGamesLimit( level );
    if ( ( GetMoney() < moneyNeeded ) || ( GetPoints( gamesLimit ) < GetPointsRequired( level ) ) )
    {
      continue;
    }

    if (!IsAccessibleToBuy(impulse, hero->GetFaction()))
      continue;

    // check cooldown
    if(impulse->cooldown > 0 || (hero->IsDead() && !impulse->canBeOfferedToDead ) )
      continue;

    if( !impulse->IsEnabled(hero, NDb::IMPULSIVEEVENTTYPE_HEROEVENT, target) )
      continue;

    if (!impulseToSuggest || impulseToSuggest->priority < impulse->priority )
      impulseToSuggest = impulse;
  }

  if( !impulseToSuggest && ( g_forcedBuff != -1 ) && ( g_forcedBuff < impulseBuffs.size() ) && ( g_forceBuffRepeatCount > 0 ) )
  {
    impulseToSuggest = &impulseBuffs[g_forcedBuff];
    impulseToSuggest->SetForced( true );
    if( 0 == -- g_forceBuffRepeatCount)
      g_forcedBuff = -1;

    systemLog( NLogg::LEVEL_MESSAGE ) << "Forced impulse:" << impulseToSuggest->buff->name.GetText() << endl;
  }

  if( impulseToSuggest && IsValid(impulseBuffsController))
  {
	  impulseBuffsController->SuggestImpulse(impulseToSuggest, target);
  }
}


void ImpulsiveBuffsManager::SetCooldown( const Impulse * impulse )
{
  vector<Impulse>::iterator const iEnd = impulseBuffs.end();
  for( vector<Impulse>::iterator iBuff = impulseBuffs.begin(); iBuff != iEnd; ++iBuff )
  {
    if( impulse->cooldownGroup == iBuff->cooldownGroup)
      iBuff->cooldown = impulse->cooldownTime;
  }

  globalCooldown = max(globalCooldown, buffsDescriptions->globalCooldown);
}

void ImpulsiveBuffsManager::ResetAllCooldowns()
{
  for( vector<Impulse>::iterator iBuff = impulseBuffs.begin(); iBuff != impulseBuffs.end(); ++iBuff )
  {
    iBuff->cooldown = 0.0f;
  }

  globalCooldown = 0.0f;
}


void ImpulsiveBuffsManager::RefuseFromImpulse( Impulse * impulse )
{
  SetCooldown(impulse);
}

void ImpulsiveBuffsManager::BuyImpulse(const Impulse *  impulse, Target& target )
{
#ifndef _SHIPPING
  // do not use target.IsValid(), because some impulses, such as Resurrection will not work!
  NI_VERIFY( target.IsPosition() || (target.IsObject() && IsValid( target.GetObject() ) ), "Invalid target!", return; );
  NI_VERIFY( impulse, "Wrong impulsive buff", return; );
  NI_VERIFY(IsValid(GetHero()), "hero is not setted", return;)
 

  if( GetHero()->IsDead() && !impulse->canBeOfferedToDead )
    return;

  if ( !impulse->IsEnabled( GetHero(), NDb::IMPULSIVEEVENTTYPE_HEROEVENT, target ) )
    return;

  if (!IsAccessibleToBuy(impulse, GetHero()->GetFaction()))
    return;

  int moneyNeeded = impulse->isForced ? 0 : impulse->goldCost;

  int level      = impulse->isForced ? 0 : impulse->accessInfo.level;
  int gamesLimit = GetGamesLimit( level );
  if ( ( GetMoney() >= moneyNeeded ) && ( GetPoints( gamesLimit ) >= GetPointsRequired( level ) ) )
  {
    NGameX::AdventureScreen::Instance()->SendGameCommand( CreateCmdUseImpulse( GetHero(), impulse->impulseBuffIndex, target ), true );
  }
  else
    return; // we can't afford this impulse

  //logging to player statistics
  GetHero()->LogSessionEvent(SessionEventType::ImpulsiveBuffUsed, impulse->buff);
  
  SetCooldown(impulse);
#endif
}


void ImpulsiveBuffsManager::UseImpulse(PFBaseHero * hero, NDb::ImpulseBuffs impulseType, Target const& target)
{
  // do not use target.IsValid(), because some impulses, such as Resurrection will not work!
  NI_VERIFY( target.IsPosition() || (target.IsObject() && IsValid( target.GetObject() ) ), "Invalid target!", return; );
  NI_VERIFY( impulseType >= 0 && impulseType < impulseBuffs.size(), "Wrong impulsive buff id!", return; );

  if( hero->IsDead() && !impulseBuffs[impulseType].canBeOfferedToDead )
    return;

  Impulse* pBuff = &impulseBuffs[impulseType];

  if (!IsAccessibleToBuy(pBuff, hero->GetFaction()))
    return;

  //TODO its kind of hack for NUM_TASK. we need to reduce money only in case of our hero.
  //should be changed quickly!!
  if (hero->IsLocal())
  {
    ReduceMoney( pBuff->goldCost, pBuff->impulseBuffIndex );
  }

  hero->GetProfile()->AddImpulsePoints( pBuff->accessInfo.points );

  if( pBuff->isSimple )
    hero->UseExternalAbility( pBuff->buff, target );
  else
    hero->EnqueueState(new PFUseImpulseState( hero, pBuff->buff, target ), true);

  int woID = hero->GetWOID();
  heroInfos[woID][impulseType] = 0.0f;

  CheckAccessible(pBuff, hero->GetFaction());
 
}

bool ImpulsiveBuffsManager::IsBuffUsed( const int buffId )const
{
  int woID = GetHero()->GetWOID();
  THeroInfos::const_iterator hero_it = heroInfos.find(woID);
  if( heroInfos.end() == hero_it)
    return false;

  TBuffUsageInfo::const_iterator it = hero_it->second.find(buffId);
  return hero_it->second.end() == it ? false : it->second < buffsDescriptions->buffUseEventLifeTime;
}


vector<int> ImpulsiveBuffsManager::GetCountingWeights( string const& setName) const
{
  if( buffsDescriptions )
  {
    for(vector<NDb::UnitCountingWeights>::const_iterator it = buffsDescriptions->unitCountingParams.begin(), 
      end = buffsDescriptions->unitCountingParams.end(); it != end; ++it )
      if( setName == it->setName )
        return it->weights;
  }

  return defaultCountingWeights.weights;
}

PFBaseHero * ImpulsiveBuffsManager::GetHero() const
{
  NI_ASSERT(IsValid(player), "have no player here?");
  PFBaseHero * hero = player->GetHero();
  NI_ASSERT(IsValid(hero), "hero is not attached to player at this point")
  return hero;
}

PFBetweenSessionsData* ImpulsiveBuffsManager::GetHeroProfile() const
{
  PFBetweenSessionsData* profile = GetHero()->GetProfile();
  NI_ASSERT( IsValid( profile ), "Hero profile is invalid!" );
  return profile;
}

int ImpulsiveBuffsManager::GetMoney() const
{
  return g_disableZZBilling? g_debugZZMoney: billingResult->GetCurrentMoney();
}


int ImpulsiveBuffsManager::GetPointsRequired( int impulseLevel ) const
{
  NI_VERIFY( impulseLevel >= 0, "Impulse level can't be negative!", return 0 );

  int tableSize = buffsDescriptions->accessLevelsCosts.size();

  if ( tableSize > 0 )
  {
    int level = min( impulseLevel, tableSize - 1 );
    return buffsDescriptions->accessLevelsCosts[level].impulsesPoints;
  }

  return 0;
}


int ImpulsiveBuffsManager::GetGamesLimit( int impulseLevel ) const
{
  NI_VERIFY( impulseLevel >= 0, "Impulse level can't be negative!", return 0 );

  int tableSize = buffsDescriptions->accessLevelsCosts.size();

  if ( tableSize > 0 )
  {
    int level = min( impulseLevel, tableSize - 1 );
    return buffsDescriptions->accessLevelsCosts[level].gamesLimit;
  }

  return 0;
}


int ImpulsiveBuffsManager::GetPoints( int gamesLimit ) const
{
  PFBetweenSessionsData* profile = GetHeroProfile();

  return profile ? profile->GetImpulsePoints( gamesLimit ) : 0;
}


void ImpulsiveBuffsManager::ReduceMoney( int amount, int id )
{
  if ( g_disableZZBilling )
  {
    g_debugZZMoney -= amount;
  }
  else
  {
    if ( accounting )
    {
      accounting->BuyService( id, billingResult.Get(), &BillingResult::onRemoveMoneyCall );
    }
  }
}

void ImpulsiveBuffsManager::BuyService( NDb::GeneralServices generalService )
{
  int id = generalService;
  if (CanBuyService(generalService))
    ReduceMoney(buffsDescriptions->servicesCosts->services[id].goldCost, NDb::KnownEnum<NDb::ImpulseBuffs>::sizeOf +  id);
}

bool ImpulsiveBuffsManager::CanBuyService( NDb::GeneralServices generalService )
{
  int id = generalService;
  int maxId = NDb::KnownEnum<NDb::GeneralServices>::sizeOf;
  NI_VERIFY(id>=0 && id<maxId, "wrong service", return false;)

  int cost = buffsDescriptions->servicesCosts->services[id].goldCost;
  return cost<=GetMoney();
}

bool ImpulsiveBuffsManager::IsAccessibleToBuy( const Impulse * impulse, NDb::EFaction faction )
{
  NI_VERIFY(impulse, "invalid impulse?!", return false;);
  
  TeamBuffAccessibility & accessibility = teamBuffAccessibilities[impulse->impulseBuffIndex];
  bool accessible = (faction ==  NDb::FACTION_BURN) ? accessibility.accessibleToBuyForBurn : accessibility.accessibleToBuyForFreeze;
  return impulse->oncePerTeam? accessible : true;
}

void ImpulsiveBuffsManager::CheckAccessible( const Impulse * impulse, NDb::EFaction faction )
{
   NI_VERIFY(impulse, "invalid impulse?!", return;)
  //mark that we already used this
  if (impulse->oncePerTeam)
  {
    TeamBuffAccessibility & accessibility = teamBuffAccessibilities[impulse->impulseBuffIndex];
    
    if (faction ==  NDb::FACTION_BURN)
      accessibility.accessibleToBuyForBurn = false;
    else
      accessibility.accessibleToBuyForFreeze = false;
  }
}

void ImpulsiveBuffsManager::SetImpulseBuffsController( NGameX::ImpulseBuffsController * impBuffsController )
{
	impulseBuffsController = impBuffsController;
}



bool ForceImpulsiveBuff(char const* name, vector<wstring> const& params )
{
  if( params.empty() )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: "<< name << "buff [repeatCount]" << endl;
    return true;
  }

  g_forcedBuff             = NStr::ToInt( params[0] );
  if( 1 < params.size() )
    g_forceBuffRepeatCount = NStr::ToInt( params[1] );
  
  g_forceBuffRepeatCount = max(1, g_forceBuffRepeatCount);

  return true;
}

} //namespace NWorld

REGISTER_DEV_VAR( "impulsiveBuffs",        g_enabledImpulsiveBuffs, STORAGE_NONE );
REGISTER_DEV_VAR( "impulses_useDebugGold", g_disableZZBilling,      STORAGE_NONE );
REGISTER_DEV_VAR( "impulses_goldQuantity", g_debugZZMoney,          STORAGE_NONE ); 
REGISTER_DEV_CMD( impulses_forceBuff, NWorld::ForceImpulsiveBuff );

REGISTER_WORLD_OBJECT_NM( PFUseImpulseState, NWorld )

#ifndef _SHIPPING
REGISTER_SAVELOAD_CLASS_NM( CmdUseImpulse, NWorld )
#endif

BASIC_REGISTER_CLASS(NWorld::ImpulsiveBuffsManager)