#include "HybridServerDumpers.h"
#include "System/FileSystem/FileWriteAsynchronousStream.h"
#include "System/FileSystem/FilePath.h"
#include "System/LogFileName.h"
#include "Server/RPC/RPC.h"
#include "BlockHistory.h"
#include "ClientHolder.h"


namespace HybridServer
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimpleCrcDumper::SimpleCrcDumper(NLogg::CChannelLogger* _logStream)
  : logStream(_logStream)
{
  path = NFile::Combine( NDebug::GetWorkDir(), "asyncs" );
  NFile::CreatePath(path);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TODO: in this simple implementation the dump isn't really asynchronous...
void SimpleCrcDumper::OnCrcDump(Peered::TSessionId serverId, int clientId, int step, void * data, int size)
{
  nstl::string file;

  file = NDebug::GenerateDebugFileName(NI_STRFMT("session_%016x_client_%d_step_%d", serverId, clientId, step), "bin", path.c_str());

  // Create an asynchronous file writer stream with preallocated buffer and file
  CObj<Stream> storage = new FileWriteAsynchronousStream( file, size, size );
  if (!storage->IsOk())
  {
    storage = 0;
    localLog(logStream, NLogg::LEVEL_WARNING).Trace(
      "HybridServerDispencer: Failed to open file for CRC dump (sid=%016x cid=%d step=%d size=%d file=%s)",
        serverId, clientId, step, size, file.c_str());
    return;
  }

  storage->Write(data, size);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DummyCommandsLog::OnCommandsDump(Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses)
{
  localLog(logStream, NLogg::LEVEL_DEBUG ).Trace(
    "HybridServer: Logging steps (sid=%016x steps=%d-%d)", serverId, startStep, endStep);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimpleFileCommandsLog::SimpleFileCommandsLog(NLogg::CChannelLogger* _logStream, Peered::TSessionId serverId, int bufferSize, int fileSize)
  : logStream(_logStream)
  , isHeaderDumped(false)
{
  path = NFile::Combine( NDebug::GetWorkDir(), "replays" );

  NFile::CreatePath(path);

  // NUM_TASK представление sessionID в имени реплея в 10-чной системе
  path = NDebug::GenerateDebugFileName(NI_STRFMT("session_%llu", serverId), "replay", path.c_str());

  // Create an asynchronous file writer stream with preallocated buffer and file
  storage = new FileWriteAsynchronousStream( path, bufferSize, fileSize );
  if (!storage->IsOk())
  {
    storage = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimpleFileCommandsLog::SimpleFileCommandsLog(NLogg::CChannelLogger* _logStream, Peered::TSessionId serverId, const nstl::string& category, int bufferSize, int fileSize)
  : logStream(_logStream)
  , isHeaderDumped(false)
{
  path = NFile::Combine( NDebug::GetWorkDir(), "replays" );

  if (!category.empty())
    path = NFile::Combine( path, category );

  NFile::CreatePath(path);

  // NUM_TASK представление sessionID в имени реплея в 10-чной системе
  path = NDebug::GenerateDebugFileName(NI_STRFMT("session_%llu", serverId), "replay", path.c_str());

  // Create an asynchronous file writer stream with preallocated buffer and file
  storage = new FileWriteAsynchronousStream( path, bufferSize, fileSize );
  if (!storage->IsOk())
  {
    storage = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimpleFileCommandsLog::OnCommandsDump(Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses)
{
  if ( !storage )
  {
    localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: File \"%s\" missing", path.c_str());
    return;
  }

  int writtenBytes = 0;
  
  // Finish previous flush. Shouldn't really wait, because we have enough time between dumps,
  // but it must be called to prepare buffer!
  storage->FinishFlush();

  if (!isHeaderDumped)
  {
    const int header = 'LPER';
    writtenBytes += storage->Write(&header, sizeof(int));
    isHeaderDumped = true;
  }

  nstl::vector<rpc::MemoryBlock> stepCommands;

  for (int i=startStep;i<=endStep;++i)
  {
    stepCommands.clear();
    commands.CopyStep(i, stepCommands);
    if (stepCommands.size() > 0)
    {
      const byte stepSign = 0;
      writtenBytes += storage->Write(&stepSign, sizeof(byte));

      writtenBytes += storage->Write(&i, sizeof(int));

      ushort commandsCountShort = ushort(stepCommands.size());
      writtenBytes += storage->Write(&commandsCountShort, sizeof(ushort));

      for (int j=0;j<stepCommands.size();++j)
      {
        rpc::MemoryBlock& block = stepCommands[j];
        ushort blockSize = ushort(block.size);
        writtenBytes += storage->Write(&blockSize, sizeof(ushort));
        writtenBytes += storage->Write(block.memory, block.size);
      }
    }
  }

  // Dump buffer to disc asynchronously
  storage->Flush();

  localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: Logging steps (sid=%016x steps=%d-%d bytes=%d)", serverId, startStep, endStep, writtenBytes);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BdsCommandsLog::OnHeaderDump(const Peered::SchedulerData & data, const lobby::TGameLineUp * _gameLineUp, const lobby::SGameParameters * _gameParams, const vector<Peered::ClientInfo> * _clientInfos)
{
  if (!replayDataFlow.Get())
  {
    localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: OnHeaderDump: no data flow to write the replay");
    return;
  }

  if (!_gameLineUp || !_gameParams || !_clientInfos)
  {
    localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: OnHeaderDump: Missing parameters");
    return;
  }

  replayBuffer.Clear();

  header.SetSize(1<<16);
  CObj<IBinSaver> pSaver = CreateChunklessSaver( &header, 0, false );

  int clientId = 0; // None is a local player for server replay
  int simulationStep = data.sessionSettings.simulationStep;
  NCore::ClientSettings * clientSettings = const_cast<NCore::ClientSettings *>(&data.clientSettings);
  lobby::TGameLineUp * gameLineUp = const_cast<lobby::TGameLineUp *>(_gameLineUp);
  lobby::SGameParameters * gameParams = const_cast<lobby::SGameParameters *>(_gameParams);
  vector<Peered::ClientInfo> * clientInfos = const_cast<vector<Peered::ClientInfo> *>(_clientInfos);

  pSaver->Add( 2, &clientId );
  pSaver->Add( 3, gameLineUp );
  pSaver->Add( 4, gameParams );
  pSaver->Add( 5, &simulationStep );
  pSaver->Add( 6, clientSettings );
  pSaver->Add( 7, clientInfos );

  pSaver = 0;

  // We just save and don't write the header here because we still 
  // don't have clients version which should be written first
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BdsCommandsLog::OnStartGame(Peered::TSessionId serverId, const Login::ClientVersion & _clientVersion, int step)
{
  if (!replayDataFlow.Get())
  {
    localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: no data flow to write the replay");
    return;
  }

  // Here we write full header structure:
  // [ marker | client version | local client ID | all initial data | starting step ]

  replayBuffer.Clear();

  const int marker = 'PRWP';
  replayBuffer << marker;

  MemoryStream ms(16);
  CObj<IBinSaver> pSaver = CreateChunklessSaver( &ms, 0, false );
  Login::ClientVersion * clientVersion = const_cast<Login::ClientVersion *>(&_clientVersion);
  pSaver->Add( 1, clientVersion );
  pSaver = 0;
  replayBuffer.Write(ms.GetBuffer(), ms.GetPosition());

  if (header.GetPosition() > 0)
    replayBuffer.Write(header.GetBuffer(), header.GetPosition());

  replayBuffer << step;

  if ( replayBuffer.GetSize() )
    replayDataFlow->StoreBinaryData( 0, replayBuffer.GetData(), replayBuffer.GetSize() );

  header.SetSize(0);

  localLog(logStream, NLogg::LEVEL_DEBUG ).Trace(
    "HybridServer: Logging replay header (sid=%016x bytes=%d step=%d)", serverId, replayBuffer.GetSize(), step );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BdsCommandsLog::OnCommandsDump(Peered::TSessionId serverId, int startStep, int endStep, Peered::BlockHistory& commands, Peered::BlockHistory& statuses)
{
  if (!replayDataFlow.Get())
  {
    localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: no data flow to write the replay");
    return;
  }

  replayBuffer.Clear();

  nstl::vector< rpc::MemoryBlock > stepCommands;
  nstl::vector< rpc::MemoryBlock > stepStatuses;
  for (int i = commands.GetStartStep(); i <= endStep; ++i)
  {
    stepCommands.clear();
    stepStatuses.clear();
    commands.CopyStep(i, stepCommands);
    statuses.CopyStep(i, stepStatuses);
    if (stepCommands.size() > 0 || stepStatuses.size() > 0)
    {
      replayBuffer
          << i                              // step
          << ushort( stepCommands.size() )  // commandsCount
          << ushort( stepStatuses.size() ); // statusesCount

      for (int j = 0; j < stepCommands.size(); ++j)
      {
        rpc::MemoryBlock& block = stepCommands[j];

        replayBuffer << ushort( block.size );
        replayBuffer.Write( block.memory, block.size );
      }

      for (int j = 0; j < stepStatuses.size(); ++j)
      {
        rpc::MemoryBlock& block = stepStatuses[j];

        replayBuffer << ushort( block.size );
        replayBuffer.Write( block.memory, block.size );
      }
    }
  }

  if ( replayBuffer.GetSize() )
    replayDataFlow->StoreBinaryData( 0, replayBuffer.GetData(), replayBuffer.GetSize() );

  localLog(logStream, NLogg::LEVEL_DEBUG ).Trace(
    "HybridServer: Logging steps (sid=%016x steps=%d-%d bytes=%d)", 
      serverId, startStep, endStep, replayBuffer.GetSize() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BdsCommandsLog::OnFinishGame(Peered::TSessionId serverId, int step)
{
  if (!replayDataFlow.Get())
  {
    localLog(logStream, NLogg::LEVEL_DEBUG ).Trace("HybridServer: no data flow to write the replay");
    return;
  }

  replayBuffer.Clear();

  // Just write an empty step. The client will play back up to this pseudo-step and then finish.
  // Without it the client will finish after last step, contained commands or statuses (we don't store empty steps).

  replayBuffer
    << step         // step
    << ushort( 0 )  // commandsCount
    << ushort( 0 ); // statusesCount

  if ( replayBuffer.GetSize() )
    replayDataFlow->StoreBinaryData( 0, replayBuffer.GetData(), replayBuffer.GetSize() );

  localLog(logStream, NLogg::LEVEL_DEBUG ).Trace(
    "HybridServer: Logging game finish (sid=%016x step=%d)", serverId, step );
}

} // namespace HybridServer
