#pragma once

#include "PFBaseAIController.h"

namespace NWorld
{
  class AIBaseState;
  class ControllerPart;

  enum ESeriesAIBehavior
  { 
    BEHAVIOR_SUPPORT,
    BEHAVIOR_PUSH_PATH,
    BEHAVIOR_GUARD_POINT,
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct GlyphPart
  {
    GlyphPart( int _useDelay ) : useDelay(_useDelay), useTimeLeft(0), inactiveTimeLeft(0)
    {}
    bool TryUseGlyphs( PFAIHelper &aiHelper );
    float EstimateLifeRestorer( PFAIHelper & aiHelper );
    void GetHumanHeroesNear( vector<PFBaseHero*>* humanHeroes, PFAIHelper & aiHelper );
  private:
    int useDelay;
    int useTimeLeft;
    int inactiveTimeLeft;
  };

  struct SignalPart
  {
    SignalPart( int _useDelay ): useDelay(_useDelay), active(false), useTimeLeft(0) 
    {
    }
    bool IsActive() const { return active; }

    void Activate( PFAIHelper &aiHelper, const Target& target );
    void Step( PFAIHelper &aiHelper, TalentPart& talents );
    void Cleanup() { active = false; target.SetPosition(VNULL3); }
  private:
    int useDelay;
    int useTimeLeft;
    bool active;
    bool movingTo;
    CVec3 lastStopPos;
    Target target;
#ifndef _SHIPPING
    string debugName;

#endif

    bool IsEnemiesNear( PFBaseMaleHero* pUnit );
    bool ConsiderUsePortal( PFBaseMaleHero* pUnit );
    PFBaseUnit* FindEnemyNear( PFBaseMaleHero* pUnit );
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFSeriesAIController : public PFBaseAIController, public IPFSeriesAIController
  {
    OBJECT_BASIC_METHODS(PFSeriesAIController);

  public:
    PFSeriesAIController( PFBaseHero* unit, NCore::ITransceiver* pTransceiver);
    PFSeriesAIController( PFBaseHero* unit, NCore::ITransceiver* pTransceiver, bool DoNotLevelUp);

    /////////////////////////////////////////////////////////////////////////////
    virtual void Step( float timeDelta );
    virtual void OnDie();
    virtual void OnRespawn();
    virtual bool OnMinimapSignal( const Target& target, bool dedicated );
    /////////////////////////////////////////////////////////////////////////////

    void StartPushPath( const vector<CVec2>& path );
    void StartSupport( PFBaseUnit* pMaster );
    void StartGuardPoint( const CVec2& point, float radius, float lookToAreaRadius );
    void EnableMinimapSignal( bool enable ) { signalsEnabled = enable; }

    ESeriesAIBehavior  GetBehavior() { return behavior; }

    /////////////////////////////////////////////////////////////////////////////

    TalentPart talents;
    GlyphPart glyphs;

  private:
    PFSeriesAIController() : talents(0,0), glyphs(0), signals(0) {}
    virtual ~PFSeriesAIController() 
    {
      Cleanup();
    }

    AutoPtr<ControllerPart> currentPart;
    bool signalsEnabled;
    SignalPart signals;
    bool  isLvlUpAvailable;
    ESeriesAIBehavior behavior;
  };

  class ControllerPart
  {
  public:
    ControllerPart(PFSeriesAIController* _owner) : owner(_owner) {}

    virtual void Restart() = 0;
    virtual void Step() = 0;
    virtual bool CanReactToSignal( const Target& target ) { return true; }
  protected:
    PFSeriesAIController* owner;
  };
  /////////////////////////////////////////////////////////////////////////////
  class PushLineControllerPart : public ControllerPart
  {
  public:
    PushLineControllerPart(PFSeriesAIController* _owner, const vector<CVec2>& _path ) 
      : ControllerPart(_owner)
      , path(_path)
      , active(false)
    {}

    virtual void Restart();
    virtual void Step();
  protected:
    vector<CVec2> path;
    bool active;
  };
  /////////////////////////////////////////////////////////////////////////////
  class SupportControllerPart : public ControllerPart
  {
  public:
    SupportControllerPart(PFSeriesAIController* _owner, PFBaseUnit* _pMaster ) 
      : ControllerPart(_owner)
      , pMaster(_pMaster)
      , active(false)
    {}

    virtual void Restart();
    virtual void Step();
  protected:
    PFBaseUnit* pMaster;
    bool active;
  };
  /////////////////////////////////////////////////////////////////////////////
  class GuardControllerPart : public ControllerPart
  {
  public:
    GuardControllerPart(PFSeriesAIController* _owner, const CVec2 &_point, float _radius, float _lookToAreaRadius ) 
      : ControllerPart(_owner)
      , point(_point)
      , radius(_radius)
      , lookToAreaRadius(_lookToAreaRadius)
      , active(false)
      , commandDelay(0)
      , returnDelay(0)
    {}

    virtual void Restart();
    virtual void Step();

  protected:
    CVec2 point;
    float radius;
    float lookToAreaRadius;
    bool active;
    int commandDelay;
    int returnDelay;

    PFBaseUnit* FindTargetInGuardArea( PFAIWorld * pAIWorld, PFBaseMaleHero * pHero );
  };

/////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////