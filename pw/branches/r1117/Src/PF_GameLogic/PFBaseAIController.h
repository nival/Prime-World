#ifndef PFBASEAICONTROLLER_H_2FF5F6F0_C3
#define PFBASEAICONTROLLER_H_2FF5F6F0_C3

#include "PFAIControllerInterfaces.h"
#include "PFAIHelper.h"
#include "PFFsm.h"

namespace NCore
{
class ITransceiver;
}

namespace NWorld
{

class AIBaseState;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseAIController : public CObjectBase, public PFFsm, public IPFAIController
{
public:
  PFBaseAIController() : isDead(true) {}
  PFBaseAIController(PFBaseHero * _hero, NCore::ITransceiver * transceiver);

  virtual int GetStackSize() const { return PFFsm::GetStackSize(); }
  virtual const char* GetCurrentStateName();
  virtual void Step( float timeDelta );
  virtual void OnDie() {}
  virtual void OnRespawn() {}
  virtual void StopHero() { aiHelper.Stop(); }
  virtual int GetLineNumber() const { return RANDOM_LINE; }
  virtual PFBaseMaleHero * GetHero() const { return hero; }
  virtual bool OnMinimapSignal( const Target& target, bool dedicated ) { return false; }

  AIBaseState * CurrentState();
  bool IsDumpStates() const { return false; }
  PFAIHelper & GetHelper() { return aiHelper; }
  bool IsDead() const { return isDead; }
  void SetDead(bool _isDead) { isDead = _isDead; }
  PFWorld * GetWorld();

private:
  CPtr<PFBaseMaleHero>  hero;
  PFAIHelper  aiHelper;
  bool  isDead;
};

} // namespace NWorld

#endif //#define PFBASEAICONTROLLER_H_2FF5F6F0_C3
