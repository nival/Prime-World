#pragma once

#include "HybridServerDumpersIfaces.h"
#include "System/BlockData/BlockData.h"


namespace HybridServer
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SimpleCrcDumper : public ICrcDumper, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(SimpleCrcDumper, ICrcDumper, BaseObjectMT);

public:
  SimpleCrcDumper(NLogg::CChannelLogger* _logStream);

  //TODO: in this simple implementation the dump isn't really asynchronous...
  virtual void OnCrcDump(Peered::TSessionId serverId, int clientId, int step, void * data, int size);

private:
  NLogg::CChannelLogger* logStream;
  nstl::string path;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DummyCommandsLog : public ICommandsLog, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(DummyCommandsLog, ICommandsLog, BaseObjectMT);

public:
  DummyCommandsLog(NLogg::CChannelLogger* _logStream) : logStream(_logStream) {}

  virtual void OnHeaderDump(const Peered::SchedulerData & data, const lobby::TGameLineUp * gameLineUp, const lobby::SGameParameters * gameParams, const vector<Peered::ClientInfo> * clientInfos) {};
  virtual void OnStartGame(Peered::TSessionId serverId, const Login::ClientVersion & clientVersion, int step) {};
  virtual void OnCommandsDump(Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses);
  virtual void OnFinishGame(Peered::TSessionId serverId, int step) {};

private:
  NLogg::CChannelLogger* logStream;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SimpleFileCommandsLog : public ICommandsLog, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(SimpleFileCommandsLog, ICommandsLog, BaseObjectMT);

public:
  SimpleFileCommandsLog(NLogg::CChannelLogger* _logStream, Peered::TSessionId serverId, int bufferSize, int fileSize);
  SimpleFileCommandsLog(NLogg::CChannelLogger* _logStream, Peered::TSessionId serverId, const nstl::string& category, int bufferSize, int fileSize);

  virtual void OnHeaderDump(const Peered::SchedulerData & data, const lobby::TGameLineUp * gameLineUp, const lobby::SGameParameters * gameParams, const vector<Peered::ClientInfo> * clientInfos) {};
  virtual void OnStartGame(Peered::TSessionId serverId, const Login::ClientVersion & clientVersion, int step) {};
  virtual void OnCommandsDump(Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses);
  virtual void OnFinishGame(Peered::TSessionId serverId, int step) {};

private:
  NLogg::CChannelLogger* logStream;
  bool isHeaderDumped;
  CObj<Stream> storage;
  nstl::string path;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BdsCommandsLog : public ICommandsLog, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(BdsCommandsLog, ICommandsLog, BaseObjectMT);

public:
  BdsCommandsLog(NLogg::CChannelLogger* _logStream, nvl::IDataFlow * _replayDataFlow)
    : logStream(_logStream), replayDataFlow(_replayDataFlow) {}

  virtual void OnHeaderDump(const Peered::SchedulerData & data, const lobby::TGameLineUp * gameLineUp, const lobby::SGameParameters * gameParams, const vector<Peered::ClientInfo> * clientInfos);
  virtual void OnStartGame(Peered::TSessionId serverId, const Login::ClientVersion & clientVersion, int step);
  virtual void OnCommandsDump(Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses);
  virtual void OnFinishGame(Peered::TSessionId serverId, int step);

private:
  NLogg::CChannelLogger* logStream;
  nvl::CPtr< nvl::IDataFlow > replayDataFlow;
  nvl::CBinaryBuffer replayBuffer;
  MemoryStream header;
};

} // namespace HybridServer
