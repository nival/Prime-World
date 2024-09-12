#ifndef PF_GL_GAMECONTROL_H_INCLUDED
#define PF_GL_GAMECONTROL_H_INCLUDED

#include "ReplayInfo.h"

namespace NCore
{
  _interface IWorldBase;
  class WorldCommand;
}



namespace NDb
{
  enum EFaction;
}


namespace StatisticService
{
  namespace RPC
  {
    struct SessionClientResults;
  }
}

namespace NGameX
{

_interface IGameControl : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(IGameControl, IBaseInterfaceMT);
  virtual void OnCombatScreenStarted( NCore::IWorldBase * _world, const NGameX::ReplayInfo & _replayInfo ) = 0;
  virtual void OnVictory( const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo ) = 0;
  virtual void LeaveGame() = 0;
  virtual bool IsGameReady() = 0;
  virtual bool IsWaitingLeaveAck() = 0;
  virtual void DispatchPlaySameTeamDecision(const bool agreed) = 0;
  virtual void DispatchBadBehaviourComplaint(const int userId, const int reportItemId) = 0;
  virtual void OnProtectionError() = 0;
  virtual void SetTimeScale(float timescale) = 0;
};

}

#endif //PF_GL_GAMECONTROL_H_INCLUDED
