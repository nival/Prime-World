#ifndef EVENTFILELOGGER_H_5ECF324E_0C6F
#define EVENTFILELOGGER_H_5ECF324E_0C6F

#include "Events.h"
#include "FileSystem/WinFileUnbuffered.h"
#include "FixedMemoryStream.h"
#include "FileSystem/FileUtils.h"
#include "VMem.h"
#include "get_tick_count.h"

namespace Events
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
// file format:
// header (LogFileHeader) 
// далее повторяются блоки:
// <event_size(2 bytes)> { if event_size != 0: <event_time(4 bytes)> <event_type(4 bytes)> <event_data(event_size bytes)> - сообщение с типом event_type
//                       { if event_size == 0: <event_type(4 bytes)> { if event_type != 0 : <event_name(zero terminated)> - имя сообщения с типом event_type 
//                                                                   { if event_type == 0 :                               - конец данных
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const uint EventFileLoggerVersion = 0x0101;
#pragma pack( push, 1 )
struct LogFileHeader
{
  short headerSize; // size of this structure (=offset to first event)
  uint version;
  uint callCtackSize;
  LogFileHeader() : headerSize(0), version(0), callCtackSize(0) {} 
};
#pragma pack( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EventFileLogger : public IEventLogger, public CObjectBase 
{
public:

  EventFileLogger( const char* fileName, int expectedFileSize, int _bufferSize )
    : pBuffer0(0), pBuffer1(0), bufferSize(_bufferSize)
  {
    string fullFileName;
    NFile::GetFullName( &fullFileName, fileName );
    file = new WinFileUnbuffered( fullFileName.c_str(), expectedFileSize );
    const int pg = WinFileUnbuffered::GetPageSize();
    bufferSize = ( (bufferSize - 1) / pg + 1 ) * pg; 
    // pBuffer0 = VirtualAlloc( 0, bufferSize, MEM_COMMIT, PAGE_READWRITE );
    pBuffer0 = nival::VMemAlloc( bufferSize, nival::READ_WRITE );
    // pBuffer1 = VirtualAlloc( 0, bufferSize, MEM_COMMIT, PAGE_READWRITE );
    pBuffer1 = nival::VMemAlloc( bufferSize, nival::READ_WRITE );
    hasCompletionData = false;
    stream = new FixedMemoryStream( pBuffer0, bufferSize );
    // timeStarted = GetTickCount();
    timeStarted = nival::get_tick_count();

    LogFileHeader header;
    header.headerSize = sizeof( LogFileHeader );
    header.version = EventFileLoggerVersion;
    header.callCtackSize = EVENT_CALLSTACK_SIZE;
    LogData( &header, header.headerSize );
  }
  ~EventFileLogger()
  {
    Events::TEventLength noLength = 0;
    Events::TEventId noCode = 0;
    LogData( (void*)&noLength, sizeof( Events::TEventLength ) );
    LogData( (void*)&noCode, sizeof( Events::TEventId ) );

    StreamBuffer( stream->GetBuffer() );
    file->HasOperationCompleted( completionData, true );
    file = 0;

    if ( pBuffer0 )
      // ::VirtualFree( pBuffer0, 0, MEM_RELEASE );
      nival::VMemFree( pBuffer0 );
    pBuffer0 = 0;
    if ( pBuffer1 )
      // ::VirtualFree( pBuffer1, 0, MEM_RELEASE );
      nival::VMemFree( pBuffer1 );
    pBuffer1 = 0;
  }

  virtual void LogEventName( Events::TEventId eventId, const char* str )
  {
    Events::TEventLength noLength = 0;
    LogData( (void*)&noLength, sizeof( Events::TEventLength ) );
    LogData( (void*)&eventId, sizeof( Events::TEventId ) );
    LogData( (void*)str, strlen( str ) + 1 );
  }
  virtual void Log( const EventBase& event, int eventSize )
  {
    if ( enabledEvents.count( event.typeId ) == 0 )
      return;
    DWORD evTime = GetTickCount() - timeStarted;
    Events::TEventLength evSize = eventSize;
    LogData( (void*)&evSize, sizeof( Events::TEventLength ) );
    LogData( (void*)&evTime, sizeof( evTime ) );
    LogData( ((char*)&event), eventSize );
  }

  virtual void EnableEvent( TEventId eventId ) 
  {
    enabledEvents.insert( eventId );

  }
  virtual void DisableEvent( TEventId eventId ) 
  {
    enabledEvents.erase( eventId );
  }
private:
  EventFileLogger() : pBuffer0(0), pBuffer1(0), bufferSize(0), hasCompletionData(false) {} 
  CObj<WinFileUnbuffered> file;
  bool hasCompletionData;
  WinFileUnbuffered::WriteStruct completionData;
  void* pBuffer0;
  void* pBuffer1;
  int bufferSize;
  DWORD timeStarted;
  CObj<FixedMemoryStream> stream;
  set<Events::TEventId> enabledEvents;

  void StreamBuffer( void* pBuffer )
  {
    if ( hasCompletionData )
    {
      bool bCompleted = file->HasOperationCompleted( completionData, true );
      NI_VERIFY( bCompleted, "We waited and still not completed....", return );
    }

    file->Write( pBuffer, bufferSize, completionData );
    hasCompletionData = true;
  }

  void LogData( const void* data, int size )
  {
    int freeMem = bufferSize - stream->GetPosition();
    if ( size > freeMem )
    {
      if( freeMem > 0 )
        stream->Write( data, freeMem );

      StreamBuffer( stream->GetBuffer() );
      if ( stream->GetBuffer() == pBuffer0 )
        stream->SetBuffer( pBuffer1, bufferSize );
      else
        stream->SetBuffer( pBuffer0, bufferSize );

      stream->Write( (char*)data + freeMem, size - freeMem );
    }
    else
    {
      stream->Write( (void*)data, size );
    }
  }

  OBJECT_BASIC_METHODS(EventFileLogger)
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif //#define EVENTFILELOGGER_H_5ECF324E_0C6F
