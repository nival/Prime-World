#pragma once

#include "DBImpulsiveBuffs.h"
#include "PFUniTarget.h"
#include "Server/Accounting/LobbyAccountingStructs.h"


#include <RPC/RPC.h>
#include <RPC/P2PNode.h>

namespace NDb
{
  enum ImpulseBuffs;
  enum GeneralServices;
}

namespace NGameX
{
	class ImpulseBuffsController;
}

namespace NWorld
{

class PFWorld;
class PFPlayer;
class PFBaseHero;
class PFBetweenSessionsData;
class PFTower;

class ImpulsiveBuffsManager;

//////////////////////////////////////////////////////////////////////////
class ImpulsiveEvent : public IObjectBase
{
public:
  ImpulsiveEvent() : suggestTarget(), type() {}

  ImpulsiveEvent( NDb::ImpulsiveEvent const& dbEvt, ImpulsiveBuffsManager * _buffsManager ) :
  suggestTarget(dbEvt.suggestTarget),
  type(dbEvt.eventType),
  buffsManager(_buffsManager)
  {}

  NDb::ImpulsiveEventType GetType() const { return type; }
  virtual bool IsEnabled(PFBaseHero* pHero, Target& suggestedTarget )const = 0;
  virtual void Step( const float /*dt*/) {}

protected:
  bool suggestTarget;
  NDb::ImpulsiveEventType type;
  CPtr<ImpulsiveBuffsManager> buffsManager;
};


//TODO: we dont need Lobby::BuyResult at all. remove second callback etc
//////////////////////////////////////////////////////////////////////////
struct BillingResult : BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(BillingResult, BaseObjectMT);
  BillingResult() : money(0) {}

  int GetCurrentMoney() const { return money; }

  void onGetMoneyCall( int _result )
  {
    money = _result;
  }
  
  void onRemoveMoneyCall( Lobby::BuyResult _result )
  {
    money = _result.currentAmount;
  }

private:
  int money;
};


//////////////////////////////////////////////////////////////////////////
struct Impulse
{
  bool IsEnabled(PFBaseHero* pUnit, NDb::ImpulsiveEventType const type, const Target& target) const;
  void SetForced( bool forced ) { isForced = forced; }
  // ~~~
  NDb::Ptr<NDb::Ability> buff;
  vector<CObj<ImpulsiveEvent>> events;
  int   goldCost;
  float cooldown;
  float cooldownTime;
  string cooldownGroup;
  float priority;
  bool  canBeOfferedToDead;
  float offerTime;
  bool  isSimple;
  bool oncePerTeam;
  bool isForced;
  NDb::ImpulseBuffs impulseBuffIndex;
  NDb::AccessInfo accessInfo;
};


//////////////////////////////////////////////////////////////////////////
class ImpulsiveBuffsManager : public CObjectBase
{
  OBJECT_METHODS( 0x8B78DAC0, ImpulsiveBuffsManager );
  ImpulsiveBuffsManager() {}
public:
  ImpulsiveBuffsManager( PFWorld* pWorld, PFPlayer * ourPlayer);

  void        Update(float dt );
  
  bool        CanBuyService(NDb::GeneralServices generalService);
  int         GetMoney() const;

  int         GetGamesLimit(     int impulseLevel ) const;
  int         GetPointsRequired( int impulseLevel ) const;
  int         GetPoints(         int gamesLimit   ) const;

  void        RefuseFromImpulse(Impulse *  impulse);
  void        BuyImpulse(const Impulse *  impulse, Target& target );
  void        BuyService(NDb::GeneralServices generalService);
  void		  SetImpulseBuffsController(NGameX::ImpulseBuffsController * impBuffsController);

  // Use only in world command context!
  void        UseImpulse(PFBaseHero * hero, NDb::ImpulseBuffs impulseType, Target const& target);

  bool        IsBuffUsed(const int buffId) const;
  float       GetPriestessEventsLifeTime() const { return buffsDescriptions ? buffsDescriptions->priestessEventsLifeTime : 0.0f; }
  vector<int> GetCountingWeights( string const& setName) const;

  void ResetAllCooldowns();

private:
  void Step( float dt );
  void CreateBuffs(vector<Impulse> * pResult);
  void SuggestImpulses();
  bool IsAccessibleToBuy(const Impulse *  impulse, NDb::EFaction faction);
  void CheckAccessible(const Impulse *  impulse, NDb::EFaction faction);
  void ReduceMoney( int amount, int id );

  void SetCooldown(const Impulse *  impulse);

  PFBaseHero* GetHero() const;
  PFBetweenSessionsData* GetHeroProfile() const;

  CPtr<PFWorld> pWorld;
  CPtr<PFPlayer> player;
  Weak<NGameX::ImpulseBuffsController> impulseBuffsController;

  vector<Impulse> impulseBuffs;

  struct TeamBuffAccessibility
  {
    bool accessibleToBuyForBurn;
    bool accessibleToBuyForFreeze;
    TeamBuffAccessibility() : accessibleToBuyForBurn(true), accessibleToBuyForFreeze(true) {}
  };

  vector<TeamBuffAccessibility> teamBuffAccessibilities;
  
  typedef map<int, float> TBuffUsageInfo;
  typedef map<int, TBuffUsageInfo> THeroInfos;

  THeroInfos heroInfos;

  NDb::UnitCountingWeights defaultCountingWeights;
  NDb::Ptr<NDb::ImpulsiveBuffsContainer> buffsDescriptions;
  float globalCooldown;
 
  PFBaseUnit *pCurrentOwner;

  //billing
  StrongMT<BillingResult> billingResult;

  float timeSinceLastGetMoney;

  
  lobby::AccountingGadget * accounting;
};

bool ForceImpulsiveBuff(char const* name, vector<wstring> const& params );

} //namespace NWorld