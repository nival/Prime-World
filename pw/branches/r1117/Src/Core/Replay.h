#ifndef _REPLAY_H_
#define _REPLAY_H_

/////////////////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////////////////

#include "GameCommand.h"
#include "GameTypes.h"
#include "Scheduler.h"
#include "../System/MemoryStream.h"
#include "../System/ChunklessSaver.h"

namespace lobby
{
struct SGameParameters;
}

namespace NCore
{

class PackedWorldCommand;

struct ReplaySegment
{
  typedef vector<CObj<PackedWorldCommand> > Commands;
  ZDATA
  Commands seg;
  float deltaTime;
  unsigned long crc;

  ZEND int operator&( IBinSaver &f ) { f.Add(2,&seg); f.Add(3,&deltaTime); f.Add(4,&crc); return 0; }

  ReplaySegment() {}
};



enum ReplayBufferMode
{
  REPLAY_BUFFER_WRITE     = 0,
  REPLAY_BUFFER_READ      = 1,
};



enum ReplayBufferWrite
{
  REPLAY_BW_CLOSE         = 0,
  REPLAY_BW_CONTINUE      = 1,
};



enum ReplayBufferSync
{
  REPLAY_BS_ASYNC         = 0,
  REPLAY_BS_SYNC          = 1,
};



enum ReplayBufferError
{
  REPLAY_ERROR_OK               = 0,
  REPLAY_ERROR_FILE_CANT_OPEN   = 1,
  REPLAY_ERROR_BAD_FILE_SIGN    = 2,
  REPLAY_ERROR_BAD_PRODUCT_VER  = 3,
  REPLAY_ERROR_BAD_NUM_SEGMENTS = 4,
  REPLAY_ERROR_BAD_GAME_LENGTH  = 5,
  REPLAY_ERROR_INVALID_GAME_INIT= 6,
  REPLAY_ERROR_INVALID_SEGMENT  = 7,
  REPLAY_ERROR_READ_SYSTEM      = 8,
  REPLAY_ERROR_WRITE_SYSTEM     = 9,
};



//FIXME: Переписать бы весь этот индокитайский кот, да некогда!!! 
class ReplayBufferManager : public CObjectBase
{
  OBJECT_BASIC_METHODS(ReplayBufferManager)
public:
  ReplayBufferManager(ReplayBufferMode mode, const char *fileName);
  ReplayBufferManager();
 ~ReplayBufferManager();

  static ReplayBufferManager  *GetInstance()
  {
    NI_ASSERT(s_instanceRepBuf, "Replay buffer is not created yet.");
    return s_instanceRepBuf;
  }
  ReplayBufferMode    GetMode()   { return m_mode;          }

  // Write functions
  bool        WriteChunk( const char * buffer, int bufSize );
  bool        WriteSegment( const char * buffer, int bufSize, float deltaTime );
  bool        Flush(ReplayBufferSync bs = REPLAY_BS_SYNC);

  // Read functions
  bool        GetNextChunk( char * buffer, int bufMaxSize, int * bufActualSize );
  bool        GetHeader( char * buffer, int bufMaxSize, int * bufActualSize );
  bool        GetNextSegment( char * buffer, int bufMaxSize, int * bufActualSize );
  float       GetGameLength()               { return m_gameLength;          }
  int         GetNumberOfSegments()         { return  m_numReplaySegments;  }
  bool        IsEof()                       { return (m_curReplaySegment >= m_numReplaySegments); }
  void        SetWriteCompleted(bool c)     { m_writeCompleted = c;         }

  // Internal func
  void        SetError(ReplayBufferError  err);
  ReplayBufferError   GetError()            { return m_error;               }

private:
  bool        WriteBuf( const void *buf, int bufSize );
  bool        ReadBuf(void *buf, int bufSize);
  bool        WriteCurrentBuffer(ReplayBufferSync bs = REPLAY_BS_ASYNC, ReplayBufferWrite bw = REPLAY_BW_CONTINUE);
  bool        ReadCurrentBuffer(bool needSync = false);

  bool        ReadNumberOfSegments();
  bool        WriteHeader();
  bool        ReadHeader();
  bool        ReadInitial();

private:
  ReplayBufferMode    m_mode;                   // tread or write mode
  HANDLE              m_handle;                 // file handle
  unsigned char      *m_buffer[2];              // 2 buffers for write
  int                 m_bufferWriteIndex;       // current write buffer index (0 or 1)
  bool                m_writeCompleted;         // if async write is not completed

  int                 m_bufferReadTo;           // buffer indices
  int                 m_bufferReadFrom;

  int                 m_bufferOffset;           // current buffer offset
  int                 m_bufferStartFileOffset;  // corresponding file offset for current buffer
  DWORD               m_fileSize;               // const for read, increasing for write mode

  int                 m_numReplaySegments;  // number of replay segments written
  int                 m_curReplaySegment;   // curent readed replay segment
  float               m_gameLength;

  OVERLAPPED          m_overlappedStruct; // for async write func. Store file offset here
  static ReplayBufferManager  *s_instanceRepBuf;
  ReplayBufferError   m_error;
};


class IReplayStorage: public CObjectBase
{
public:
  virtual bool GetNextSegment( ReplaySegment & segOut ) = 0;
  virtual bool GetNextSegment( SyncSegment & segOut ) = 0;
  virtual bool GetHeader( MapStartInfo * info, int * clientId, int * stepLength, ClientSettings * clientSettings, lobby::SGameParameters* gameParams ) = 0;
  virtual bool IsOk() = 0;
};


class ReplayStorage: public IReplayStorage
{
  OBJECT_BASIC_METHODS(ReplayStorage)
public:
  ReplayStorage(ReplayBufferMode mode, const char *fileName);
  ReplayStorage();
 ~ReplayStorage();

 // Write functions
 bool        WriteSegment( ReplaySegment& seg );
 bool        Flush();
 bool        WriteHeader( const MapStartInfo & info );

 // Read functions
 bool       GetNextSegment( ReplaySegment& segOut );
 bool       GetNextSegment( SyncSegment & segOut ) { return false; };
 bool       GetHeader( MapStartInfo * info, int * clientId, int * stepLength, ClientSettings * clientSettings, lobby::SGameParameters* gameParams );
 float      GetGameLength()         { return m_buffer.GetGameLength();        }
 int        GetNumberOfSegments()   { return m_buffer.GetNumberOfSegments();  }
 bool       IsEof()                 { return m_buffer.IsEof();                }

 ReplayBufferManager * GetManager() { return &m_buffer; } // от псевдо-синглтона при рефакторинге надо будет избавиться 
  virtual bool IsOk() { return (m_buffer.GetError() == NCore::REPLAY_ERROR_OK); };

private:
  ReplayBufferManager   m_buffer;
  MemoryStream          m_memoryStream;
  bool isFinished;
};


} //namespace NCore

#endif
