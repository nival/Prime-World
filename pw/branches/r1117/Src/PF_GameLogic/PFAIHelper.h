#pragma once
#include "PFUniTarget.h"
#include "AdventureScreen.h"

//#define LOG_AI							1
//#define LOG_AI_MOVE					1

#if LOG_AI
#  define DBG(...)		DebugTrace("AI: " __VA_ARGS__)
#else
#  define DBG(...)
#endif

#if LOG_AI_MOVE
#  define DBGM(...)		DebugTrace("AIM: " __VA_ARGS__)
#else
#  define DBGM(...)
#endif

struct AiConst;
static Weak<AiConst> s_aiConstInstance;

struct AiConst
{
private:
  AiConst();
  AiConst(AiConst&);
  AiConst& operator=(const AiConst&);

public:
  static const AiConst* Instace()
  {
    if(!s_aiConstInstance)
      s_aiConstInstance = new AiConst();
    return s_aiConstInstance;
  }

  //scale steps count by step length
  //step = 100ms => 10 tick
  //step = 50ms => 20 tick

  static const int TICK()
  {
    int defStepLength = DEFAULT_GAME_STEP_LENGTH;
    if(IsValid(NGameX::AdventureScreen::Instance()->GetWorld()))
      defStepLength = NGameX::AdventureScreen::Instance()->GetWorld()->GetStepLength();

    return round(100.f * (10.f / defStepLength ));
  };

  // All delays are in Step() units 
  static const int		ASYNC_DELAY(){return TICK();};
  static const int		MOVE_START_DELAY(){return ASYNC_DELAY() + 2;};
  static const int		USE_CONSUMABLE_DELAY(){return 1 * TICK();};
  static const int		USE_POTION_DELAY(){return 3 * TICK();};
  static const int		ACTIVATE_TALENT_DELAY(){return 1 * TICK();};
  static const int		USE_TALENT_DELAY(){return 1 * TICK();};
  static const int		ABANDON_HEALING_DELAY(){return 7 * TICK();};
  static const int		FIND_FLAG_DELAY(){return MOVE_START_DELAY();};

  static const float	MOVE_BY_LINE_SENS(){return 1.0f;};
  static const float	MOVE_TO_FLAG_SENS(){return 3.0f;};

};

namespace NWorld
{
  class PFBaseMaleHero;
  class PFShop;
  class PFTalent;
  class PFBaseUnit;
  class PFBaseHero;
  class PFAIHelper;
  class PFPickupableObjectBase;
  class PFFlagpole;

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // EConsumableType & IdentifyConsumable
  enum EConsumableType
  {
    OBJECT_UNKNOWN,
    OBJECT_HEALING_POTION,
    OBJECT_ENERGY_POTION,
    OBJECT_TELEPORT_SCROLL
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class TalentWrapper
  {
    int level;
    int slot;
    CPtr<PFBaseMaleHero> pUnit;
    CPtr<PFTalent> pTalent;

  public:
    TalentWrapper( CPtr<PFBaseMaleHero> _pUnit, int _level, int _slot );
    TalentWrapper();

    const PFTalent* GetTalent() { return pTalent; }

    int  GetPriority()    const;

    bool IsActive()       const;
    bool IsActivated()    const;
    bool CanBeUsed()      const;
    bool CanBeActivated() const;
    bool IsValid() const { return ::IsValid(pTalent); }

    int GetLevel() const { return level; }
    int GetSlot()  const { return slot; }

    string GetName() const;

    bool operator<( const TalentWrapper& other ) const;
    bool operator!=( const TalentWrapper& other ) const;
    TalentWrapper operator++();

    bool IsPreferable( const TalentWrapper& other ) const;
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFAIHelper
  {
  public:
    PFAIHelper( PFBaseHero* unit, NCore::ITransceiver* pTransceiver );
    PFAIHelper() {}
    CPtr<PFBaseMaleHero>			pUnit;
    NDb::Ptr<NDb::BotsSettings> pDBBots;

    PFWorld* GetWorld();
    /////////////////////////////////////////////////////////////////////////////
    // wrappers around pUnit
    /////////////////////////////////////////////////////////////////////////////
    bool IsMoving() const;
    bool IsHolding() const;
    void GetLife( float& current, float& maximal );
    void GetMana( float& current, float& maximal );

    /////////////////////////////////////////////////////////////////////////////
    // low level commands (wrappers around HeroActions.cpp CreateCmd...())
    /////////////////////////////////////////////////////////////////////////////

    void MoveTo(       const CVec2& pos );
    void CombatMoveTo( const CVec2& pos );
    void Stop();
    void Follow( PFBaseUnit* target, float followRange, float forceFollowRange );
    void Attack( PFBaseUnit* target );
    void ActivateTalent( int level, int slot );
    void ActivateTalent( const TalentWrapper& iTalent );

    void UseTalent( int level, int slot, const Target& target );
    void UseTalent( const TalentWrapper& iTalent, const Target& target );

    void BuyConsumable( PFShop* pShop, int index );
    void UseConsumable( int slot, const Target& target );
    void UsePortal( const Target& target );

    void PickupObject( PFPickupableObjectBase* pObject );
    void RaiseFlag( PFFlagpole* pFlagpole );

    int HasConsumable( EConsumableType type, int* firstIndex = NULL );
    /////////////////////////////////////////////////////////////////////////////
    // higher level functions
    /////////////////////////////////////////////////////////////////////////////

    void ResetHeal() { needResetHealing = true; } 
    bool CheckResetHealing() { bool ret = needResetHealing; needResetHealing = false; return ret;  }
    PFBaseUnit* FindEnemyNear();

  private:
    Weak<NCore::ITransceiver>	transceiver;
    bool needResetHealing;

    void SendGameCommand( NCore::WorldCommand* pCommands );
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct TalentPart
  {
    TalentPart( int _activateDelay, int _useDelay ) : activateDelay(_activateDelay),useDelay(_useDelay), activateTimeLeft(0), useTimeLeft(0)
    {}
    void ActivateTalents( PFAIHelper &aiHelper );
    void UseTalents( PFAIHelper &aiHelper );
  private:
    int activateDelay;
    int useDelay;
    int activateTimeLeft;
    int useTimeLeft;
    TalentWrapper GetFirstTalent(PFAIHelper &aiHelper);
    TalentWrapper GetLastTalent(PFAIHelper &aiHelper);
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool GetRoute( PFWorld* pWorld, NDb::EFaction faction, int roadIndex, vector<CVec2>& road );
  int GetNextRoutePoint( const vector<CVec2>& road, const CVec2& unitPos );
  bool CompareRoutePoints( const vector<CVec2>& road, const CVec2& pos1, const CVec2& pos2 );
  EConsumableType IdentifyConsumable( const NDb::Consumable* pConsumable );
  // Shift a waypoint to some specific distance, perpendicularly to the line between
  // the given waypoint an the reference (next) waypoint. Shifted to different side,
  // according to the "shift" flag.
  void ShiftWaypoint(CVec2 &wayPoint, CVec2 &refferenceWayPoint, int shift, float shiftDistance);
}