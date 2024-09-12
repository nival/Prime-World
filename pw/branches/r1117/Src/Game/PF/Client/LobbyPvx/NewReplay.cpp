#include "stdafx.h"
#include <vector>
#include "NewReplay.h"
#include <iostream>
#include <fstream>
#include "base64.h"

#include <time.h>

#include <Windows.h>

#include "Network/LoginClientVersion.h"
#include "System/FileSystem/FileWriteAsynchronousStream.h"
#include "System/FileSystem/FileUtils.h"
#include "System/ChunklessSaver.h"
#include "System/LogFileName.h"
#include "System/ProfileManager.h"
#include "HybridServer/Peered.h"
#include "HybridServer/PeeredTypes.h"
#include "Core/GameTypes.h"
#include "PW_Client/GameStatistics.h"
#include "System/SystemLog.h"

namespace
{
	bool OpenReplayFileStream(CObj<FileWriteAsynchronousStream>& stream, string &replaysFolderPath, string &replayFilePath, string &informationFileName, const Peered::TSessionId serverId)
  {
    replaysFolderPath = GetFullFolderPath(NProfile::FOLDER_REPLAYS);
    if (!NFile::DoesFolderExist(replaysFolderPath))
      NFile::CreatePath(replaysFolderPath);

    string replayFileName;

    {  
      replayFileName = NDebug::GenerateDebugFileName(NStr::StrFmt("%016llx", serverId), "pwrp", 0, false);
      replayFilePath = NFile::Combine(replaysFolderPath, replayFileName);

      if (!NFile::DoesFileExist(replayFilePath))
      {
        stream->Open(replayFilePath);

        if (stream->IsOk())
          return true;
      }
    }

    for (unsigned index = 1; index < 10; ++index)
    {
      replayFileName = NDebug::GenerateDebugFileName(NStr::StrFmt("%016llx-%u", serverId, index), "pwrp", 0, false);
      replayFilePath = NFile::Combine(replaysFolderPath, replayFileName);

      if (!NFile::DoesFileExist(replayFilePath))
      {
        stream->Open(replayFilePath);

        if (stream->IsOk())
          return true;
      }
    }

    NI_ALWAYS_ASSERT(NStr::StrFmt("Failed to open replay file %s!", replayFileName));

    stream = NULL;

    return false;
  }
	
	// Convert an ASCII string to a Unicode String
	std::wstring utf8_decode(const std::string &str)
	{	
		std::wstring wstrTo;
		wchar_t *wszTo = new wchar_t[str.length() + 1];
		wszTo[str.size()] = L'\0';
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wszTo, (int)str.length());
		wstrTo = wszTo;
		delete[] wszTo;
		return wstrTo;
	}

  // Convert an Unicode string to a ASCII String
  const std::string utf8_encode(const std::wstring &wstr)
	{
		if (wstr.empty()) return std::string();
		int sz = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), 0, 0, 0, 0);
		std::string res(sz, 0);
		WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &res[0], sz, 0, 0);
		return res;
	}
	
	// Get current date/time, format 
	const std::string currentDateTime() 
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%d %m %Y %H:%M", &tstruct);

		return buf;
	}
}

namespace NCore
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ReplayWriter::ReplayWriter()
: versionWritten(false)
, lobbyDataWritten(false)
, gsDataWritten(false)
, headerWritten(false)
, infoheaderWritten(false)
, replaysFolderPath("")
, replayFilePath("")
, separator(";")
{
  header = new MemoryStream(1<<16);
  const int marker = 'PRWP';
  header->Write(&marker, sizeof(marker));
  saver = CreateChunklessSaver(header, 0, false);
  replayFile = new FileWriteAsynchronousStream();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayWriter::WriteVersion(const Login::ClientVersion & _clientVersion)
{
  MessageTrace( "replay_writer.WriteVersion: start");
  NI_VERIFY(header->GetPosition() == 4, "Wrong replay's header writing order", return;);

  Login::ClientVersion * clientVersion = const_cast<Login::ClientVersion *>(&_clientVersion);
  saver->Add(1, clientVersion);

  versionWritten = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayWriter::WriteLobbyData(Transport::TClientId clientId, 
                                  const lobby::TGameLineUp & _gameLineUp, 
                                  const lobby::SGameParameters & _gameParams)
{
  NI_VERIFY(versionWritten, "Wrong replay's header writing order", return;);
  NI_VERIFY(!lobbyDataWritten, "Lobby data is already written to replay", return;);

  lobby::TGameLineUp * gameLineUp = const_cast<lobby::TGameLineUp *>(&_gameLineUp);
  lobby::SGameParameters * gameParams = const_cast<lobby::SGameParameters *>(&_gameParams);
  saver->Add(2, &clientId);
  saver->Add(3, gameLineUp);
  saver->Add(4, gameParams);

  lobbyDataWritten = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayWriter::WriteGSData(int stepLength, 
                               const ClientSettings & _clientSettings, 
                               const vector<Peered::ClientInfo> & _clientInfos)
{
  NI_VERIFY(lobbyDataWritten, "Wrong replay's header writing order", return;);
  NI_VERIFY(!gsDataWritten, "GS data is already written to replay", return;);

  NCore::ClientSettings * clientSettings = const_cast<ClientSettings *>(&_clientSettings);
  vector<Peered::ClientInfo> * clientInfos = const_cast<vector<Peered::ClientInfo> *>(&_clientInfos);
  saver->Add(5, &stepLength);
  saver->Add(6, clientSettings);
  saver->Add(7, clientInfos);

  gsDataWritten = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayWriter::WriteStartGame(Peered::TSessionId serverId, int step)
{
  MessageTrace( "replay_writer.WriteStartGame: start");
  NI_PROFILE_FUNCTION;

  NI_VERIFY(gsDataWritten, "Wrong replay's header writing order", return;);
  NI_VERIFY(!headerWritten, "Header is already written to replay", return;);

  if (!OpenReplayFileStream(replayFile, replaysFolderPath, replayFilePath, informationFileName, serverId))
    return;

  //add replay file path to replays info (if started from castle)
  if (infoheaderWritten)
  {
    std::ofstream infoFileWriter;
    std::string infoFileNameStr(informationFileName.c_str());
    std::wstring convertedToUtf8InfoFileName = utf8_decode(infoFileNameStr);
    infoFileWriter.open(convertedToUtf8InfoFileName.c_str(), std::ios_base::app | std::ios_base::out);

    const std::string replayFilePathEnc(replayFilePath.c_str()); 
    infoFileWriter << utf8_encode(utf8_decode(replayFilePathEnc));

    infoFileWriter.close();
    MessageTrace( "replay_writer.WriteStartGameInfo: writed replayFilePath %s", replayFilePath);
  }
  ///
  
  replayFile->Write(header->GetBuffer(), header->GetPosition());
  replayFile->Write(&step, sizeof(step));
  replayFile->Flush();

  headerWritten = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayWriter::WriteStepData(int step, 
                                 const nstl::vector<rpc::MemoryBlock> & commands, 
                                 const vector<Peered::BriefClientInfo> & statuses)
{
  NI_PROFILE_FUNCTION;

  if (!replayFile) // Possible in case we have failed to open the file
    return;

  NI_VERIFY(headerWritten, "Replay header wasn't written", return;);

  replayFile->FinishFlush();
  replayFile->Write(&step, sizeof(step));
  unsigned short commandsCount = commands.size();
  unsigned short statusesCount = statuses.size();
  replayFile->Write(&commandsCount, sizeof(commandsCount));
  replayFile->Write(&statusesCount, sizeof(statusesCount));

  for (int i = 0; i < commands.size(); ++i)
  {
    const rpc::MemoryBlock & block = commands[i];
    unsigned short size = block.size;
    replayFile->Write(&size, sizeof(size));
    replayFile->Write(block.memory, block.size);
  }

  for (int i = 0; i < statuses.size(); ++i)
  {
    const Peered::BriefClientInfo & status = statuses[i];
    unsigned short size = sizeof(status);
    replayFile->Write(&size, sizeof(size));
    replayFile->Write(&status, sizeof(status));
  }

  replayFile->Flush();
}


void ReplayWriter::WriteStartGameInfo(const NGameX::ReplayInfo & _replayInfo)
{
  //set replaysFolderPath If null (this case if game started from castle)
  if (!headerWritten)
  {
    replaysFolderPath = GetFullFolderPath(NProfile::FOLDER_REPLAYS);
    if (!NFile::DoesFolderExist(replaysFolderPath))
      NFile::CreatePath(replaysFolderPath);
  }

  MessageTrace( "replay_writer.WriteStartGameInfo: start");
  informationFileName = NFile::Combine(replaysFolderPath, NStr::StrFmt("replaysinfo-%d.castle", _replayInfo.auid));
  MessageTrace( "replay_writer.WriteStartGameInfo: %s", informationFileName);
  //_replayInfo.auid
  //infoFile - CheckIsExist

  const std::string infoFileNameStr(informationFileName.c_str());
  const std::wstring convertedToUtf8InfoFileName = utf8_decode(infoFileNameStr);
  std::ifstream infoFileReader(convertedToUtf8InfoFileName.c_str());
  bool isExist = false;
  if (infoFileReader.is_open())
    isExist = infoFileReader.peek() != -1;
  infoFileReader.close();

  MessageTrace( "replay_writer.WriteStartGameInfo: reader closed... start writer");
  std::ofstream infoFileWriter;
  infoFileWriter.open(convertedToUtf8InfoFileName.c_str(), std::ios_base::app | std::ios_base::out);
  
  //set utf8 if file is not exist
  if (!isExist)
  {
    const unsigned char bom[] = { 0xEF,0xBB,0xBF };
    infoFileWriter.write((char*)bom, sizeof(bom));
    MessageTrace( "replay_writer.WriteStartGameInfo: file does not exist - creating new");
  }
  else
  {
    MessageTrace( "replay_writer.WriteStartGameInfo: file is exist - adding line");
    infoFileWriter << "\n";
  }
    
  const std::string replayDataToEnc = 
	  _replayInfo.mapName + separator +
	  _replayInfo.heroId + separator +
	  currentDateTime();

  infoFileWriter << base64_encode(reinterpret_cast<const unsigned char*>(replayDataToEnc.c_str()), replayDataToEnc.length());
  infoFileWriter << separator;
  
  //if local game started (don`t from castle)
  if (headerWritten)
  {
    const std::string replayFilePathEnc(replayFilePath.c_str()); 
    infoFileWriter << utf8_encode(utf8_decode(replayFilePathEnc));
  }
    

  infoFileWriter.close();
  infoheaderWritten = true;
  MessageTrace( "replay_writer.WriteStartGameInfo: completed");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReplayWriter::WriteFinishGame(int step, const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo)
{
  NI_PROFILE_FUNCTION;

  if (!replayFile) // Possible in case we have failed to open the file
    return;

  NI_VERIFY(headerWritten, "Replay header wasn't written", return;);

  replayFile->FinishFlush();
  replayFile->Write(&step, sizeof(step));
  unsigned short commandsCount = 0;
  unsigned short statusesCount = 0;
  replayFile->Write(&commandsCount, sizeof(commandsCount));
  replayFile->Write(&statusesCount, sizeof(statusesCount));
  replayFile->Flush();

  //write information
  WriteSessionInfoToFile(_sessionResults, _replayInfo);
}

//////////////
void ReplayWriter::WriteSessionInfoToFile(const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo) {
  MessageTrace( "replay_writer.WriteSessionInfoToFile: start");

  const std::string infoFileNameStr(informationFileName.c_str());
  const std::wstring convertedToUtf8InfoFileName = utf8_decode(infoFileNameStr);

  //append win info to last line
  const std::string win_info = (_replayInfo.isWon ? "1" : "0");
  MessageTrace( "replay_writer.WriteSessionInfoToFile: start appending");
  std::ofstream infoFile;
  infoFile.open(convertedToUtf8InfoFileName.c_str(), std::ios_base::app | std::ios_base::out);
  
  const std::string statsStr = NStr::StrFmt("%d,%d,%d", _replayInfo.kills, _replayInfo.assists, _replayInfo.deaths);
  
  infoFile << separator << win_info;
  infoFile << separator << base64_encode(reinterpret_cast<const unsigned char*>(statsStr.c_str()), statsStr.length());
  infoFile << '\n';
  infoFile.close();
  
  MessageTrace( "replay_writer.WriteSessionInfoToFile: has appending completed");
}

} // namespace NCore


NI_DEFINE_REFCOUNT( NCore::ReplayWriter );

