
#include "RollTestToolStorage.h"
#include "System/BinChunkSerializer.h"

RollTestToolStorage::RollTestToolStorage()
: lastflag(ROLLTESTTOOLSTORAGEFLAGS_DATAERROR) {}

RollTestToolStorage::~RollTestToolStorage(void)
{
}

void RollTestToolStorage::GetRollResultForMap( vector<roll::SUserAward>& prevRollResult, nstl::string mapDesc )
{

  if(lastflag == ROLLTESTTOOLSTORAGEFLAGS_ERROR || lastflag ==  ROLLTESTTOOLSTORAGEFLAGS_EMPTY)
  {
    lastflag = ROLLTESTTOOLSTORAGEFLAGS_OK;
    return;
  }

  lastflag = ROLLTESTTOOLSTORAGEFLAGS_OK;

  if(!mapDesc.length())
  {
    lastflag = ROLLTESTTOOLSTORAGEFLAGS_DATAERROR;
    return;
  }

  vector<RollTestToolStorageEntry>::iterator iter = entries.begin();

  for(;iter != entries.end();++iter)
  {
    if(mapDesc.compare(iter->mapDesc) == 0)
    {
      iter->toSUserAwards(prevRollResult);
      return;
    }
  }
}

void RollTestToolStorage::Flush()
{
  SaveToFile(storageFileName);
}

int RollTestToolStorage::GetLastFlag()
{
  return lastflag;
}

void RollTestToolStorage::FindEntityByMapDescription(RollTestToolStorageEntry* rttsEntry, string mapDesc)
{
  lastflag = ROLLTESTTOOLSTORAGEFLAGS_OK;

  vector<RollTestToolStorageEntry>::iterator iter = entries.begin();

  for(;iter != entries.end();++iter)
  {
    if(mapDesc.compare(iter->mapDesc) == 0)
    {
      rttsEntry = iter;
      return;
    }
  }

  rttsEntry = NULL;
  lastflag = ROLLTESTTOOLSTORAGEFLAGS_DATAERROR;
}


void RollTestToolStorage::AddRollResultForMap( vector<roll::SUserAward>& rollResult, nstl::string mapDesc )
{
  if(!mapDesc.length() || !rollResult.size())
  {
    lastflag = ROLLTESTTOOLSTORAGEFLAGS_DATAERROR;
    return;
  }

  RollTestToolStorageEntry* rttsEntry = NULL;
  
  FindEntityByMapDescription(rttsEntry, mapDesc);

  if(rttsEntry && IsOk()){
    //update existing entry
    rttsEntry->fromSUserAwards(rollResult);
  }
  else
  {
    //add new
    RollTestToolStorageEntry& newEntry = entries.push_back();
    newEntry.mapDesc = mapDesc;
    newEntry.fromSUserAwards(rollResult);
  }

  lastflag = ROLLTESTTOOLSTORAGEFLAGS_OK;
}

int RollTestToolStorage::GetSize()
{
  return entries.size();
}

void RollTestToolStorage::LoadFromFile(const nstl::string &fileName)
{
  lastflag = ROLLTESTTOOLSTORAGEFLAGS_OK;

  CObj<Stream> stream = new FileStream(fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );

  if ( !stream || !stream->IsOk() || !stream->GetSize() )
  {
    lastflag = ROLLTESTTOOLSTORAGEFLAGS_DATAERROR;
    return ;
  }

  MemoryStream memoryStream;
  memoryStream.SetSize(MEMORY_BUFFER_SIZE);

  stream->Read(memoryStream.GetBuffer(), memoryStream.GetSize());
  stream->Close();

  memoryStream.Seek(0, SEEKORIGIN_BEGIN);
  CObj<IBinSaver> pSaver = CreateReadBinSaver( &memoryStream, 0 );

  int serialEntryCount = 0;

  pSaver->Add( 1, &serialEntryCount);

  if(!serialEntryCount)
  {
    pSaver = 0;
    lastflag = ROLLTESTTOOLSTORAGEFLAGS_DATAERROR;
    return ;
  }

  int chunkNumber = 1;

  entries.clear();

  for(int i = 0; i < serialEntryCount; ++i)
  {
    RollTestToolStorageEntry& newEntry = entries.push_back();
    pSaver->Add(2, &newEntry, chunkNumber++);
  }

  pSaver = 0;
}

bool RollTestToolStorage::Init(const nstl::string &fileName)
{
  storageFileName = fileName;
  entries.clear();

  LoadFromFile(storageFileName);

  return IsOk();
}

void RollTestToolStorage::SaveToFile(const nstl::string &fileName)
{
  lastflag = ROLLTESTTOOLSTORAGEFLAGS_OK;


  CObj<FileStream> stream = new FileStream(fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );

  if ( !stream || !stream->IsOk() )
  {
    lastflag = ROLLTESTTOOLSTORAGEFLAGS_ERROR;
    return ;
  }

  MemoryStream memoryStream;
  nstl::vector<RollTestToolStorageEntry>::iterator iter = entries.begin();

  int serialRollCacheSize = GetSize();

  if(!serialRollCacheSize)
  {
    lastflag = ROLLTESTTOOLSTORAGEFLAGS_DATAERROR;
    return ;
  }

  CObj<IBinSaver> pSaver = CreateWriteBinSaver( &memoryStream, 0, false );

  int serialEntryCount = GetSize();

  //read entities counter
  pSaver->Add( 1, &serialEntryCount);

  int chunkNumber = 1;

  for(;iter != entries.end();++iter)
  {
    pSaver->Add(2, iter, chunkNumber++);
  }

  pSaver = 0;

  stream->Write(memoryStream.GetBuffer(), memoryStream.GetSize());
  stream->Close();
}

bool RollTestToolStorage::IsOk()
{

  if(lastflag == ROLLTESTTOOLSTORAGEFLAGS_OK)
    return true;

  return false;
}

bool RollTestToolStorage::IsDataError()
{

  if(lastflag == ROLLTESTTOOLSTORAGEFLAGS_DATAERROR)
    return true;

  return false;
}

