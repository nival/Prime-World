#pragma once

#include "PFDispatch.h"
#include "PFDispatchStrike1.h"

namespace NGameX
{
  class PFDispatchCursorClient;
}

namespace NWorld
{

class PFDispatchCursor : public DBLinker<PFDispatchContinuous, NDb::DispatchCursor>
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x8D85DC40, PFDispatchCursor, NGameX::PFDispatchCursorClient)
public:
  seDECLARE_CPTRRING( PFDispatchCursor, unitDispatchesPart, UnitDispatchesRing );

  PFDispatchCursor(CreateParams const &cp);
  virtual void CreateClientDispatch();
  virtual void Reset();

  CVec2 const &GetCurPos() const {return curPos;}
  float GetSpeed() const { return speed; } 
  float GetMaxSpeed() const { return maxSpeed; }
  float GetStartTime() const {return m_startTime;}

  virtual void OnStart();
  virtual CVec3 GetCurrentPosition() const { return CVec3(curPos.x, curPos.y, 0.f); }

  void UpdateCursorPos( CVec2 pos );

protected:
  PFDispatchCursor() {}
  ~PFDispatchCursor() { UnitDispatchesRing::safeRemove(this); }
  virtual void OnDie() { UnitDispatchesRing::safeRemove(this); PFDispatchContinuous::OnDie(); }

private:
  virtual bool Step(float dtInSeconds);
  void UpdatePersistentApplicatorsPosition();

  ZDATA_(DBLinker)
protected:
  CVec2 curPos;
  CVec2 lastTargetPos;
  float speed;
  float m_startTime;
  CVec2 originalSenderPos;
  float duration;
  float maxSpeed;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&curPos); f.Add(3,&lastTargetPos); f.Add(4,&speed); f.Add(5,&m_startTime); f.Add(6,&originalSenderPos); f.Add(7,&duration); f.Add(8,&maxSpeed); return 0; }
};

NCore::WorldCommand* CreateCmdUpdateCursorPos( PFDispatchCursor *pDispatch, CVec2 pos);
}