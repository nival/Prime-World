#include "stdafx.h"

#include "ServerStdOutDumper.h"
#include "LogHelpers.h"
#include "MemoryBlockPool.h"
#include "System/InlineProfiler.h"
#include <vector>

namespace NLogg
{

class CServerStdOutDumper::Job : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Job, threading::IThreadJob, BaseObjectMT );

public:
  Job() :
  maxLineLen( 256 ),
  activeLine( 0 ),
  memoryPool( 7, maxLineLen, 32 )
  {
    for ( int i = 0; i < 2; ++i )
      lines[i].reserve( maxLineLen + 1 );
  }

  ~Job()
  {
    for ( int j = 0; j < 2; ++j )
      for ( size_t i = 0; i < lines[j].size(); ++i )
        memoryPool.FreeBlock( lines[j][i].textMemBlock );
  }

  void PushMessage( NLogg::ELevel level, const char * text )
  {
    NI_PROFILE_HEAVY_FUNCTION;

    threading::MutexLock guard( mutex );

    std::vector<SLogItem> & target = lines[activeLine];

    if ( target.size() == maxLineLen ) {
      level = NLogg::LEVEL_ERROR;
      text = "Console buffer overflowed!\r\n";
    }
    else if ( target.size() > maxLineLen )
      return;

    int textLen = Min( (int)strlen( text ) + 1, 2048 );

    target.push_back( SLogItem() );
    SLogItem & item = target.back();
    item.level = level;

    memoryPool.AllocBlock( item.textMemBlock, textLen );
    memcpy( item.textMemBlock.buffer(), text, textLen - 1 );
    item.textMemBlock.buffer()[textLen - 1] = 0;
  }

private:
  struct SLogItem {
    NLogg::ELevel         level;
    memory::MemoryBlock   textMemBlock;
    SLogItem() : level( LEVEL_UNDEFINED ) {}
  };

  const size_t maxLineLen;

  threading::Mutex              mutex;
  std::vector<SLogItem>         lines[2];
  int                           activeLine;
  memory::MemoryBlockPool       memoryPool;

  virtual void Work( volatile bool & isRunning )
  {
    NI_PROFILE_THREAD;

    bool sleep = true;
    while ( isRunning )
    {
      if ( sleep ) {
        NI_PROFILE_BLOCK( "Sleep" );
        threading::Sleep( 1 );
      }

      NI_PROFILE_BLOCK( "Work" );
      int readLine = activeLine ? 0 : 1;
      std::vector<SLogItem> & source = lines[readLine];

      for ( size_t i = 0; i < source.size(); ++i )
        PrintMsg( source[i].level, (const char *)source[i].textMemBlock.buffer() );

      NI_PROFILE_BLOCK( "Swap" );
      threading::MutexLock guard( mutex );

      for ( size_t i = 0; i < source.size(); ++i )
        memoryPool.FreeBlock( source[i].textMemBlock );
      source.clear();

      activeLine = readLine;

      //Sleep only if next read line is empty
      int newReadLine = activeLine ? 0 : 1;
      sleep = lines[newReadLine].empty();
    }
  }

  void PrintMsg( NLogg::ELevel level, const char * text )
  {
    NI_PROFILE_HEAVY_FUNCTION;

#if defined( NV_WIN_PLATFORM )

    HANDLE hConsole = NULL;
    DWORD prevAttr = 15;  //  white by default
    {
      NI_PROFILE_HEAVY_BLOCK( "Getting color" );

      hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
      CONSOLE_SCREEN_BUFFER_INFO cinfo;
      if ( GetConsoleScreenBufferInfo( hConsole, &cinfo ) )
        prevAttr = cinfo.wAttributes;
    }

    {
      NI_PROFILE_HEAVY_BLOCK( "Setting color" );
      switch( level )
      {
      case LEVEL_ASSERT:
      case LEVEL_CRITICAL:
        SetConsoleTextAttribute( hConsole, FOREGROUND_RED );
        break;
      case LEVEL_WARNING:
        SetConsoleTextAttribute( hConsole, FOREGROUND_GREEN );
        break;
      case LEVEL_ERROR:
        SetConsoleTextAttribute( hConsole, 14 ); //  yellow
        break;
      }
    }

    {
      NI_PROFILE_HEAVY_BLOCK( "printf" );
      printf( "%s", text );
    }

    {
      NI_PROFILE_HEAVY_BLOCK( "Restoring color" );
      SetConsoleTextAttribute(hConsole, prevAttr);
    }
#elif defined( NV_LINUX_PLATFORM )
    const char * colorCode = "";
    const char * colorEnd = "\033[0m";
    {
      NI_PROFILE_HEAVY_BLOCK( "Setting color" );
      switch( level )
      {
      case LEVEL_ASSERT:
      case LEVEL_CRITICAL:
        // SetConsoleTextAttribute( hConsole, FOREGROUND_RED );
        colorCode = "\033[31m";
        break;
      case LEVEL_WARNING:
        // SetConsoleTextAttribute( hConsole, FOREGROUND_GREEN );
        colorCode = "\033[32m";
        break;
      case LEVEL_ERROR:
        // SetConsoleTextAttribute( hConsole, 14 ); //  yellow
        colorCode = "\033[33m";
        break;
      default:
        colorEnd = "";
      }
    }

    {
      NI_PROFILE_HEAVY_BLOCK( "printf" );
      string fmt = string( colorCode ) + string( "%s" ) + string( colorEnd );
      printf( fmt.c_str(), text );
    }
#endif  // !defined( NV_LINUX_PLATFORM )

  }
};


void CServerStdOutDumper::Launch()
{
  job = new Job;
  thread = new threading::JobThread( job, "StdOutDumper" );
}



void CServerStdOutDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  NI_PROFILE_HEAVY_FUNCTION;

  job->PushMessage( entryInfo.level, headerAndText );
}



CServerStdOutDumper::~CServerStdOutDumper()
{
  //Harmless hack: Let the console messages be printed
  threading::Sleep( 100 );
}

} //namespace NLogg

NI_DEFINE_REFCOUNT( NLogg::CServerStdOutDumper::Job );
