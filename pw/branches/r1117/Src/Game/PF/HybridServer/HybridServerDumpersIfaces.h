#pragma once

#include "PeeredTypes.h"
#include "Network/LoginClientVersion.h"

namespace Peered
{
  class BlockHistory;
  struct SchedulerData;
}


namespace HybridServer
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ICommandsLog : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(ICommandsLog, IBaseInterfaceMT);

public:
  virtual void OnHeaderDump(const Peered::SchedulerData & data, const lobby::TGameLineUp * gameLineUp, const lobby::SGameParameters * gameParams, const vector<Peered::ClientInfo> * clientInfos) = 0;
  virtual void OnStartGame(Peered::TSessionId serverId, const Login::ClientVersion & clientVersion, int step) = 0;
  virtual void OnCommandsDump(Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses) = 0;
  virtual void OnFinishGame(Peered::TSessionId serverId, int step) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ICrcDumper : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1(ICrcDumper, IBaseInterfaceMT);

public:
  virtual void OnCrcDump(Peered::TSessionId serverId, int clientId, int step, void * data, int size) = 0;
};

} // namespace HybridServer
