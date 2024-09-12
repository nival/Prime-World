#pragma once

#include "../System/NameMap.h"
#include "../PF_Core/WorldObject.h"
#include "LuxDef.h"

namespace NDb
{
  enum EBoostType;
  enum EBoostUsage;
  enum EColor;
}

namespace PF_Minigames
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EEaselBoostFireMode
{
  enum Enum { Activated, WaitingActivation };
}


class Easel;
class EaselNotifier;
class LuxGameLogic;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LuxBoost : public PF_Core::WorldObjectBase
{
  OBJECT_METHODS(0x9D8AF480, LuxBoost);

public:

  LuxBoost(   PF_Core::IWorld* _pWorld, Easel * _easel, NDb::EBoostType _type, const nstl::string & _refstrName,
              long _cooldown, int _accessLevel, int _price );
  virtual ~LuxBoost();

  // checkers
  bool IsCoolingDown() const { return coolingDownNow; };
  bool IsCanAccess() const   { return canAccess; };
  virtual bool IsCanBuy() const      { return canBuy; };
  bool IsWaitingActivation() const { return waiting; }

  // getters
  NDb::EBoostType     GetBoostType()  const { return boostType;  };
  const nstl::string& GetName()       const { return boostName; };

  long GetCurrentCooldown() const;;
  void ResetCooldown();
  void StartCooldown();

  long  GetCooldown() const;
  int   GetPrice() const;

  int   GetPathID() const { return pathID; }
  void  SetPathID( int _pathID ) { pathID = _pathID; }

  void  FireBoost( LuxGameLogic* _gameLogic );
  void  CompleteBoostFire(); //For post-activated boosts

  void  ProcessStep( int _deltaTime, int _gamelevel, int _priestessgold, LuxGameLogic* _gameLogic );

  virtual EEaselBoostFireMode::Enum vFireBoost( LuxGameLogic* _gameLogic ) { return EEaselBoostFireMode::Activated; }
  virtual void vProcessStep( int deltaTime,  LuxGameLogic* _gameLogic ) {}
  virtual bool ProcessInput( const SEaselMouseInput & mouseInput, LuxGameLogic* _gameLogic ) { return false; }

  virtual bool IsActive() const { return false; }
  virtual float ActivityProgress() const { return 0.f; }

  virtual void Abort() {}

  virtual void OnUnusedPaint( LuxGameLogic* _gameLogic, const SVector& explosionPoint, NDb::EColor explosionColor, int explodedBallsNum ) {}

private:
  // cooldown operations
  void IncrementCurrentCooldown(long _incCooldown);

  ZDATA_(PF_Core::WorldObjectBase)
  // internal boost data
  NDb::EBoostType  boostType;
  nstl::string     boostName;
  
  long            boostCooldown;
  int             boostPrice;

  int             pathID;

  long cooldownCurrent;
  bool coolingDownNow;
  bool canAccess;
  bool canBuy;
  bool waiting;

protected:
  CPtr<Easel>     easel;

  CPtr<EaselNotifier> notifier;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PF_Core::WorldObjectBase*)this); f.Add(2,&boostType); f.Add(3,&boostName); f.Add(4,&boostCooldown); f.Add(5,&boostPrice); f.Add(6,&pathID); f.Add(7,&cooldownCurrent); f.Add(8,&coolingDownNow); f.Add(9,&canAccess); f.Add(10,&canBuy); f.Add(11,&waiting); f.Add(12,&easel); f.Add(13,&notifier); return 0; }

protected:
  LuxBoost() {}

  virtual void WriteOffFee();
};

typedef nstl::vector<CObj<LuxBoost>> Boosts;

//////////////////////////////////////////////////////////////////////////
//TODO: Think of joinin this functionality with 'LuxBoost' itself
class LuxBoostNameMapProxy : public NNameMap::IMap, public BaseObjectST
{
  NAMEMAP_DECLARE;
  NI_DECLARE_REFCOUNT_CLASS_2( LuxBoostNameMapProxy, NNameMap::IMap, BaseObjectST );

public:
  LuxBoostNameMapProxy() {}
  LuxBoostNameMapProxy( int _price ) : price( _price ) {}
  ~LuxBoostNameMapProxy() {}

  const int & GetPrice() const { return price; }

private:

  int price;
};

}