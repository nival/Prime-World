#include "stdafx.h"
#include "Replay.h"
#include "Transceiver.h"
#include "WorldCommand.h"
#include "System/LogFileName.h"
#include "System/BSUtil.h"
#include "MemoryLib/newdelete.h"
#include "System/BinChunkSerializer.h"


#define   REPLAY_SIGN   0x4C504552
#define   REPLAY_COMMAND_BUFFER_SIZE (16 * 1024)

#define   REPLAY_BUFFER_SIZE      (1024 * 16)


namespace
{
  bool ignoreReplayVersion = false;
  int  maxReplaySegments   = 72000; // 2 hours
}

namespace NCore
{

ReplayBufferManager  *ReplayBufferManager::s_instanceRepBuf = NULL;
static  char          s_replayFileName[250];




void  _exceptionCallback(void)
{
  ReplayBufferManager *repBuffer = ReplayBufferManager::GetInstance();
  if (!repBuffer)
    return;
  repBuffer->Flush(REPLAY_BS_SYNC);
}



ReplayBufferManager::ReplayBufferManager(ReplayBufferMode mode, const char *fileName)
{
  m_mode = mode;
  NStr::Copy(s_replayFileName, fileName, 250);
  if (mode == REPLAY_BUFFER_WRITE)
    m_handle = CreateFile( 
                            fileName, 
                            GENERIC_WRITE, 
                            FILE_SHARE_READ,
                            NULL,                                 // no securty attribute
                            CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,
                            NULL                                  // template
                          );
  else                          
    m_handle = CreateFile( 
                            fileName, 
                            GENERIC_READ, 
                            FILE_SHARE_READ, 
                            NULL,                                 // no securty attribute
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,
                            NULL                                  // template
                          );
  m_buffer[0] = (unsigned char*)Aligned_MAlloc(REPLAY_BUFFER_SIZE, 8192);
  m_buffer[1] = (unsigned char*)Aligned_MAlloc(REPLAY_BUFFER_SIZE, 8192);
  
  s_instanceRepBuf          = this;
  
  m_bufferOffset            = 0;
  m_bufferWriteIndex        = 0;
  m_error                   = REPLAY_ERROR_OK;
  m_fileSize                = 0;
  m_bufferStartFileOffset   = 0;
  m_bufferReadTo            = 0;
  m_bufferReadFrom          = 0;
  m_writeCompleted          = true;

  m_numReplaySegments       = 0;
  m_gameLength              = 0.0f;
  m_curReplaySegment        = 0;
  
  
  // for Ex write/read functions
  memset( &m_overlappedStruct, 0, sizeof(m_overlappedStruct) );
  
  if (m_handle == INVALID_HANDLE_VALUE)
  {
    SetError(REPLAY_ERROR_FILE_CANT_OPEN);
    return;
  }
  
  if (mode == REPLAY_BUFFER_READ)
  {
    DWORD fsHigh;
    m_fileSize = (int)GetFileSize(m_handle, &fsHigh);
    ReadNumberOfSegments(); // replay specific
    ReadInitial();
    ReadHeader();
  }
  if (mode == REPLAY_BUFFER_WRITE)
  {
    WriteHeader();
  }
  NBSU::SetExceptionCallback(_exceptionCallback);
}



ReplayBufferManager::ReplayBufferManager()
{
  m_mode    = REPLAY_BUFFER_WRITE;
  m_bufferOffset        = 0;
  m_bufferWriteIndex    = 0;
  m_error               = REPLAY_ERROR_OK;
  m_numReplaySegments   = 0;
  m_gameLength          = 0.0f;
  m_curReplaySegment    = 0;
}



ReplayBufferManager::~ReplayBufferManager()
{
  Flush();
  
  if (m_handle != (HANDLE)-1)
    CloseHandle(m_handle);
  m_handle = (HANDLE)-1;    
  
  Aligned_Free(m_buffer[0]);
  Aligned_Free(m_buffer[1]);
}



// Header functions
bool ReplayBufferManager::WriteHeader()
{
  int   num = 0;
 
  if (m_handle == INVALID_HANDLE_VALUE)
    return false;
  const char  *productName =  NDebug::GetProductName();
  
  // write SIGN
  num = REPLAY_SIGN;
  WriteBuf( &num, sizeof(num) );
  
  // write product name
  num   = strlen(productName);
  WriteBuf( &num, sizeof(num) );
  WriteBuf( (void*)productName, num );

  return true;
}



bool ReplayBufferManager::ReadHeader()
{
  int num;
  
  if (m_handle == INVALID_HANDLE_VALUE)
    return false;

  // Read SIGN
  ReadBuf( &num, sizeof(num) );
  if (num != REPLAY_SIGN)
  {
    SetError(REPLAY_ERROR_BAD_FILE_SIGN);
    return false;
  }  
  // Read product name    
  ReadBuf( &num, sizeof(num) );
  char *productName = new char[num + 4];
  ReadBuf( (void*)productName, num );
  productName[num] = 0;
  
  // check header string with some pattern
  const char  *curGameVersion = NDebug::GetProductName();
  if (strcmp(productName, curGameVersion) != 0 && !ignoreReplayVersion)
  {
    SetError(REPLAY_ERROR_BAD_PRODUCT_VER);
    delete productName;
    return false;
  }
  // Free memory
  delete[] productName;
  return true;
}



bool ReplayBufferManager::WriteChunk( const char * buffer, int bufSize )
{
  NI_VERIFY( m_mode == REPLAY_BUFFER_WRITE, "Flush should be in write mode", return false );
  if ( m_handle == INVALID_HANDLE_VALUE )
    return false;

  bool ret = true;
  if ( !WriteBuf( &bufSize, sizeof( bufSize ) ) )
    ret = false;
  if ( !WriteBuf( buffer, bufSize ) )
    ret = false;

  return ret;
}



bool ReplayBufferManager::WriteSegment( const char * buffer, int bufSize, float deltaTime )
{
  m_numReplaySegments++;
  m_gameLength += deltaTime;

  return WriteChunk( buffer, bufSize );
}



bool ReplayBufferManager::Flush(ReplayBufferSync bs)
{
  if (m_mode == REPLAY_BUFFER_WRITE)
  {
    if (m_handle == INVALID_HANDLE_VALUE)
      return false;

    // Write number of segments and game len to the end of replay file    
    WriteBuf( &m_numReplaySegments, sizeof(m_numReplaySegments) );
    WriteBuf( &m_gameLength, sizeof(m_gameLength) );
    
    WriteCurrentBuffer(bs, REPLAY_BW_CLOSE);
  }
  
  // close file
  if (m_handle != INVALID_HANDLE_VALUE)
    CloseHandle(m_handle);
  m_handle = INVALID_HANDLE_VALUE;

  return true;
}



bool ReplayBufferManager::WriteBuf( const void * buf, int bufSize )
{
  unsigned char   *src, *dst;
  int             i, bufPartSize;
  
  src = (unsigned char *)buf;
  dst = m_buffer[m_bufferWriteIndex] + m_bufferOffset;
  if (m_bufferOffset + bufSize <= REPLAY_BUFFER_SIZE)
  {
    for (i = 0; i < bufSize; i++)
    {
      *dst = *src;
      src++; dst++;
    }
    m_bufferOffset += bufSize;
    if (m_bufferOffset == REPLAY_BUFFER_SIZE)
    {
      m_bufferOffset = 0;
      WriteCurrentBuffer(REPLAY_BS_ASYNC, REPLAY_BW_CONTINUE);  
      m_bufferWriteIndex = (m_bufferWriteIndex + 1) & 1;
    }
  }
  else
  {
    while (true)
    {
      // data is crosses 2 buffer border
      bufPartSize = REPLAY_BUFFER_SIZE - m_bufferOffset;
      for (i = 0; i < bufPartSize; i++)
      {
        *dst = *src;
        src++; dst++;
      }
      bufSize = bufSize - bufPartSize;

      WriteCurrentBuffer(REPLAY_BS_ASYNC, REPLAY_BW_CONTINUE);
      //SleepEx(10, TRUE);
      m_bufferOffset = 0;
      m_bufferWriteIndex = (m_bufferWriteIndex + 1) & 1;
      dst = m_buffer[m_bufferWriteIndex] + m_bufferOffset;
      if (bufSize < REPLAY_BUFFER_SIZE)
        break;
    }
    // write rest of buffer
    for (i = 0; i < bufSize; i++)
    {
      *dst = *src;
      src++; dst++;
    }
    m_bufferOffset = i;
  }
  
  return true;
}



VOID CALLBACK _writeCompletedCallback( DWORD errorCode, DWORD numberOfBytesTransfered, LPOVERLAPPED  overlStru )
{
  ReplayBufferManager *repBufManager = ReplayBufferManager::GetInstance();
  if (errorCode != 0)
  {
    repBufManager->SetError(REPLAY_ERROR_WRITE_SYSTEM);
  }
  repBufManager->SetWriteCompleted(true);
}



bool ReplayBufferManager::WriteCurrentBuffer(ReplayBufferSync bs, ReplayBufferWrite bw)
{
  BOOL  res;
  DWORD err;
  
  if (m_handle == INVALID_HANDLE_VALUE)
    return false;
  unsigned char  *buffer = m_buffer[m_bufferWriteIndex];
  /*
  // compress buffer
  uLong   lengthCompressed = compressBound(REPLAY_BUFFER_SIZE);
  Bytef   *bufferCompressed = new Bytef[lengthCompressed];
  int     compressionLevel = 4;
  
  int compres = compress2(bufferCompressed, &lengthCompressed, (Bytef*)buffer, REPLAY_BUFFER_SIZE, compressionLevel);
  if (compres != Z_OK)
    compres = 3;
  */

  if (bs == REPLAY_BS_ASYNC)
  {
    if (!m_writeCompleted)
    {
      // prev write is not performed actually => give some small time for OS to complete async processes
      SleepEx(100, TRUE);
    }
    m_writeCompleted = false;
    m_overlappedStruct.Offset = m_fileSize;
    res = WriteFileEx(m_handle, buffer, REPLAY_BUFFER_SIZE, &m_overlappedStruct, _writeCompletedCallback);
    if (bw == REPLAY_BW_CLOSE)
      SleepEx(1000, TRUE);
    if (res == 0)
    {
      err = GetLastError();
      SetError(REPLAY_ERROR_WRITE_SYSTEM);
    } 
    else
    {
      // no error
      if (bw == REPLAY_BW_CLOSE)
      {
        m_fileSize += m_bufferOffset;
        SetFilePointer(m_handle, m_fileSize, NULL, FILE_BEGIN);
        SetEndOfFile(m_handle);
      }
      else
        m_fileSize += REPLAY_BUFFER_SIZE;
    }
  }
  
  if (bs == REPLAY_BS_SYNC)
  {
    CloseHandle(m_handle);

    m_handle = CreateFile( 
      s_replayFileName, 
      GENERIC_WRITE, 
      0,                        // no share
      NULL,                     // no security attribute
      OPEN_ALWAYS,
      FILE_ATTRIBUTE_NORMAL,
      NULL                      // template
      );
    unsigned char   *buffer = m_buffer[m_bufferWriteIndex];
    DWORD           written;
    SetFilePointer(m_handle, 0, NULL, FILE_END);
    WriteFile(m_handle, buffer, m_bufferOffset, &written, NULL);
  }
  return true;
}



// ******************************************************************************************
// Read functions
// ******************************************************************************************

#ifdef _DEBUG
static char *_getReplayErrorString(ReplayBufferError err)
{
  switch (err)
  {
    case REPLAY_ERROR_FILE_CANT_OPEN:
      return "Cant open replay file for read or write";

    case REPLAY_ERROR_BAD_FILE_SIGN:
      return "Replay file format error: corrupted 1st word";

    case REPLAY_ERROR_BAD_PRODUCT_VER:
      return "Current replay file is not fit to current game version";

    case REPLAY_ERROR_BAD_NUM_SEGMENTS:
      return "Replay file content is corrupted: bad number of segments";

    case REPLAY_ERROR_BAD_GAME_LENGTH:
      return "Replay file content is corrupted: bad game length";

    case REPLAY_ERROR_INVALID_GAME_INIT:
      return "Replay file content is corrupted: bad game init record";

    case REPLAY_ERROR_INVALID_SEGMENT:
      return "Replay file content is corrupted: bad segment found";

    case REPLAY_ERROR_READ_SYSTEM:
      return "Replay report OS file read error";

    case REPLAY_ERROR_WRITE_SYSTEM:
      return "Replay report OS file write error";

    default:
      return "";
  }
}
#endif



void        ReplayBufferManager::SetError(ReplayBufferError  err)
{
  m_error = err;
#ifdef _DEBUG  
  if (err != REPLAY_ERROR_OK)
    DebugTrace("REPLAY Error: %s", _getReplayErrorString(err) );
#endif    
}



bool        ReplayBufferManager::ReadBuf(void *bufDest, int bufSize)
{
  unsigned char *src, *dst;
  int           i, bufPartSize;

  //
  // m_overlappedStruct.Offset points to current file pointer
  //
  
  int numBytesInBuffer = m_fileSize - m_bufferStartFileOffset;
  if (m_bufferOffset + bufSize > numBytesInBuffer)
    return false; // try to read after end of file

  src = m_buffer[m_bufferReadFrom] + m_bufferOffset;
  dst = (unsigned char*)bufDest;
  if (m_bufferOffset + bufSize < REPLAY_BUFFER_SIZE)
  {
    for (i = 0; i < bufSize; i++)
    {
      *dst = *src;
      dst++; src++;
    }
    m_bufferOffset += bufSize;
  }
  else
  {
    // partially read
    bufPartSize = REPLAY_BUFFER_SIZE - m_bufferOffset;
    for (i = 0; i < bufPartSize; i++)
    {
      *dst = *src;
      dst++; src++;
    }
    bufSize = bufSize - bufPartSize;
    while (1)
    {
      m_bufferOffset = 0;
      m_bufferReadFrom = (m_bufferReadFrom + 1) & 1;
      src = m_buffer[m_bufferReadFrom] + m_bufferOffset;

      m_bufferStartFileOffset += REPLAY_BUFFER_SIZE;
      m_bufferReadTo = (m_bufferReadTo + 1) & 1;
      ReadCurrentBuffer();
      
      int copySize = (bufSize <= REPLAY_BUFFER_SIZE)? bufSize: REPLAY_BUFFER_SIZE;
      for (i = 0; i < copySize; i++)
      {
        *dst = *src;
        dst++; src++;
      }
      if (bufSize <= REPLAY_BUFFER_SIZE)
        break;
      bufSize = bufSize - copySize;        
    }
    m_bufferOffset += bufSize;
  }
  return true;
}



VOID  CALLBACK _readCompletedCallback(
                                       DWORD         errorCode,
                                       DWORD         numberOfBytesTransfered,
                                       LPOVERLAPPED  overlStru
                                       )
{
  ReplayBufferManager *repBufManager = ReplayBufferManager::GetInstance();
  if (errorCode != 0)
  {
    repBufManager->SetError(REPLAY_ERROR_READ_SYSTEM);
  }
}



bool ReplayBufferManager::ReadCurrentBuffer(bool needSync)
{
  BOOL  res;
  DWORD err;
  
  if (m_handle == INVALID_HANDLE_VALUE)
    return false;
  if (m_overlappedStruct.Offset >= m_fileSize)
    return false;
  
  unsigned char *buffer = m_buffer[m_bufferReadTo];
  res = ReadFileEx(m_handle, buffer, REPLAY_BUFFER_SIZE, &m_overlappedStruct, _readCompletedCallback);
  if (needSync)
    SleepEx(1000, TRUE);
  if (res == 0)
  {
    err = GetLastError();
    SetError(REPLAY_ERROR_READ_SYSTEM);
  } 
  else
  {
    m_overlappedStruct.Offset += REPLAY_BUFFER_SIZE;
  }
  return true;
}



bool ReplayBufferManager::ReadInitial()
{
  SetFilePointer(m_handle, 0, NULL, FILE_BEGIN);
  m_bufferStartFileOffset   = 0;
  m_overlappedStruct.Offset = 0;
  m_bufferReadFrom          = 0;
  m_bufferReadTo            = 0;
  ReadCurrentBuffer( true );  // need sync
  if (m_overlappedStruct.Offset < m_fileSize)
  {
    m_bufferReadTo = (m_bufferReadTo + 1) & 1;
    ReadCurrentBuffer( true );  // need sync
  }

  return true;
}



bool ReplayBufferManager::ReadNumberOfSegments()
{

  int numBufs = m_fileSize / REPLAY_BUFFER_SIZE;
  m_overlappedStruct.Offset = numBufs * REPLAY_BUFFER_SIZE;
  int numBytesInBuffer = m_fileSize - m_overlappedStruct.Offset;

  m_bufferReadFrom          = 0;
  m_bufferReadTo            = 0;
  
  SetFilePointer(m_handle, m_overlappedStruct.Offset, NULL, FILE_BEGIN);
  ReadCurrentBuffer( true );  // need sync

  unsigned char *buffer = m_buffer[m_bufferReadFrom] + numBytesInBuffer - 8;
  m_numReplaySegments = *((int*)buffer); buffer += 4;
  m_gameLength        = *((float*)buffer); buffer += 4;
  
  if (m_numReplaySegments < 0 || m_numReplaySegments > maxReplaySegments)
  {
    SetError(REPLAY_ERROR_BAD_NUM_SEGMENTS);
    return false;
  }
  if (m_gameLength < 0.0f || m_gameLength > maxReplaySegments/10.0f)
  {
    SetError(REPLAY_ERROR_BAD_GAME_LENGTH);
    return false;
  }
  return true;
}



bool ReplayBufferManager::GetNextChunk( char * buffer, int bufMaxSize, int * bufActualSize )
{
  NI_VERIFY( m_mode == REPLAY_BUFFER_READ, "GetSegment should be in read mode", return false );

  if ( !ReadBuf( bufActualSize, sizeof(int) ) )
    return false;

  if ( ( *bufActualSize < 0 ) || ( *bufActualSize > bufMaxSize ) )
  {
    NI_ALWAYS_ASSERT( "Command is larger than buffer size" )
    SetError(REPLAY_ERROR_INVALID_SEGMENT);
    return false;
  }

  if ( !ReadBuf( buffer, (*bufActualSize) ) )
    return false;

  return true;
}



bool ReplayBufferManager::GetHeader( char * buffer, int bufMaxSize, int * bufActualSize )
{
  m_curReplaySegment = 0;
  return GetNextChunk( buffer, bufMaxSize, bufActualSize );
}



bool ReplayBufferManager::GetNextSegment( char * buffer, int bufMaxSize, int * bufActualSize )
{
  if (m_curReplaySegment >= m_numReplaySegments)
  {
    SetError(REPLAY_ERROR_OK);
    return false;
  }

  m_curReplaySegment++;

  return GetNextChunk( buffer, bufMaxSize, bufActualSize );
}









ReplayStorage::ReplayStorage( ReplayBufferMode mode, const char *fileName )
: m_buffer(mode, fileName)
 ,m_memoryStream(REPLAY_COMMAND_BUFFER_SIZE)
 , isFinished(false)
{
}



ReplayStorage::ReplayStorage()
: m_buffer(REPLAY_BUFFER_WRITE, NULL)
,m_memoryStream(REPLAY_COMMAND_BUFFER_SIZE)
, isFinished(false)
{
}


ReplayStorage::~ReplayStorage()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Write functions
/////////////////////////////////////////////////////////////////////////////////////////////

bool ReplayStorage::WriteHeader( const MapStartInfo & info )
{
  m_memoryStream.Seek(0, SEEKORIGIN_BEGIN);
  m_memoryStream.SetSize(0);

  CObj<IBinSaver> pSaver = CreateWriteBinSaver( &m_memoryStream, 0, false );
  const_cast<MapStartInfo&>( info ).operator &( *pSaver );
  pSaver = 0;
  
  return m_buffer.WriteChunk( m_memoryStream.GetBuffer(), m_memoryStream.GetPosition() );
}



bool ReplayStorage::WriteSegment( ReplaySegment& seg )
{
  m_memoryStream.Seek(0, SEEKORIGIN_BEGIN);
  m_memoryStream.SetSize(0);
  CObj<IBinSaver> pSaver = CreateWriteBinSaver(&m_memoryStream, 0, false);
  
  seg.operator &(*pSaver);
  pSaver = NULL;

  bool ret = false;
  ret = m_buffer.WriteSegment( m_memoryStream.GetBuffer(), m_memoryStream.GetPosition(), seg.deltaTime );
  return ret;
}



bool ReplayStorage::Flush()
{
  bool ret = m_buffer.Flush();
  return ret;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Read functions
/////////////////////////////////////////////////////////////////////////////////////////////

bool ReplayStorage::GetHeader( MapStartInfo * info, int * clientId, int * stepLength, ClientSettings * clientSettings, lobby::SGameParameters* gameParams )
{
  int actualSize = 0;
  if ( !m_buffer.GetHeader( m_memoryStream.GetBuffer(), m_memoryStream.GetSize(), &actualSize) )
    return false;

  m_memoryStream.Seek(0, SEEKORIGIN_BEGIN);
  CObj<IBinSaver> pSaver = CreateReadBinSaver(&m_memoryStream, 0);
  info->operator &( *pSaver );

  *clientId = 0;
  *stepLength = DEFAULT_GAME_STEP_LENGTH;

  return true;
}



bool ReplayStorage::GetNextSegment( ReplaySegment& segOut )
{
  int   actualSize = 0;

  if (isFinished)
    return false;

  isFinished = !m_buffer.GetNextSegment( m_memoryStream.GetBuffer(), m_memoryStream.GetSize(), &actualSize);

  if (isFinished)
    return false;
  
  m_memoryStream.Seek(0, SEEKORIGIN_BEGIN);

  CObj<IBinSaver> pSaver = CreateReadBinSaver(&m_memoryStream, 0);
  segOut.operator &(*pSaver);
  pSaver = NULL;
  
  return true;
}


} //namespace NCore

REGISTER_VAR( "ignore_replay_version", ignoreReplayVersion, STORAGE_NONE );
REGISTER_DEV_VAR( "max_replay_segments", maxReplaySegments, STORAGE_NONE );
