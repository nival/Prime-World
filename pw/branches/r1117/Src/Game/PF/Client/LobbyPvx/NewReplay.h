#pragma once
#include "PW_Client/GameStatistics.h"
#include "PF_GameLogic/ReplayInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace Login
{
  struct ClientVersion;
}

namespace Peered
{
  struct BlockHistory;
  struct BriefClientInfo;
  struct ClientInfo;
  typedef long long TSessionId;
}

namespace lobby
{
  struct SGameParameters;
  struct SGameMember;
  typedef vector<SGameMember>  TGameLineUp;
}

namespace rpc
{
  struct MemoryBlock;
}

namespace Transport
{
  typedef int TClientId;
}

struct IBinSaver;
class MemoryStream;
class FileWriteAsynchronousStream;


namespace NCore
{
struct ClientSettings;
struct MapStartInfo;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: This class should be united with server's replay writer NUM_TASK
class ReplayWriter : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( ReplayWriter, BaseObjectMT );
public:

  ReplayWriter();

  // Methods below appear in a right order of replay format writing

  void WriteVersion(const Login::ClientVersion & _clientVersion);
  void WriteLobbyData(Transport::TClientId clientId, const lobby::TGameLineUp & _gameLineUp, const lobby::SGameParameters & _gameParams);
  void WriteGSData(int stepLength, const ClientSettings & clientSettings, const vector<Peered::ClientInfo> & clientInfos);
  void WriteStartGame(Peered::TSessionId serverId, int step);
  void WriteStepData(int step, const nstl::vector<rpc::MemoryBlock> & commands, const vector<Peered::BriefClientInfo> & statuses);
  void WriteStartGameInfo(const NGameX::ReplayInfo & _replayInfo);
  void WriteFinishGame(int step, const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo);
  void WriteSessionInfoToFile(const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo);

private:
  bool versionWritten;
  bool lobbyDataWritten;
  bool gsDataWritten;
  bool headerWritten;
  bool infoheaderWritten;

  CObj<IBinSaver> saver;
  CObj<MemoryStream> header;
  CObj<FileWriteAsynchronousStream> replayFile;
  string informationFileName;
  string replaysFolderPath;
  string replayFilePath;
  std::string separator;
};

} // namespace NCore
