#ifndef LOGGER_H__
#define LOGGER_H__

#include "Thread.h"
#include "LogLevel.h"
#include "HPTimer.h"
#include "MultiReaderLock.h"
#include "Pointers/Pointers.h"
#include "Pointers/Strong.h"

#include "nlist.h"
#include "nset.h"

namespace NLogg
{

namespace EHeaderFormat
{
  enum Enum
  {
    ThreadId        = 1,
    Timestamp       = 2,
    ChannelName     = 4,
    Severity        = 8,
    Default = ThreadId | Timestamp | ChannelName | Severity,
  };
}



class CDumper;

struct SEntryInfo
{
  ELevel              level;
  const char *        filename; //Pointer to static string!
  int                 line;
  timer::DecodedTime  time;
  DWORD               threadId;
  const char *        channel; //Pointer to static string!

  SEntryInfo() : level(), filename( 0 ), line( 0 ), time(), threadId( 0 ), channel( 0 ) {}

  SEntryInfo( ELevel lvl, const char * _filename, int _line, const char * _channel ) :
#if defined( NV_WIN_PLATFORM )
    level( lvl ), filename( _filename ), line( _line ), threadId( ::GetCurrentThreadId() ), channel( _channel )
#elif defined( NV_LINUX_PLATFORM )
    level( lvl ), filename( _filename ), line( _line ), threadId( ::pthread_self() ), channel( _channel )
#endif
  {
    timer::UtcDecodedTime( time );
  }

  SEntryInfo( ELevel lvl, const char * _filename, int _line ) :
#if defined( NV_WIN_PLATFORM )
  level( lvl ), filename( _filename ), line( _line ), threadId( ::GetCurrentThreadId() ), channel( 0 )
#elif defined( NV_LINUX_PLATFORM )
  level( lvl ), filename( _filename ), line( _line ), threadId( ::pthread_self() ), channel( 0 )
#endif
  {
    timer::UtcDecodedTime( time );
  }
};



class INotifyCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( INotifyCallback, IBaseInterfaceMT );

public:
  virtual void OnLogEvent( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly ) = 0;
};



class CLogger
{
public:
  typedef nstl::list<StrongMT<CDumper> > TDumpers;

  CLogger( const char * szName );
  virtual ~CLogger();

  const bool AddDumper( CDumper *pDumper ); //returns false if dumper already linked to this logger or its parents
  const bool RemoveDumper( CDumper *pDumper );
  void ClearAllDumpers();
  StrongMT<CDumper> FindDumperByName( const char* szName ) const; 

  const char * GetName() const { return szName; }

  void SetHeaderFormat( unsigned _headerFormat = EHeaderFormat::Default ) { headerFormat = _headerFormat; }  
  unsigned HeaderFormat() const { return headerFormat; }

  virtual void Log( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

  void AddNotifyCallback( INotifyCallback * filter );
  void RemoveNotifyCallback( INotifyCallback * filter );

protected:
  // CChannelLogger will use our dumpers[] as a default dumpers set, and our Log mechanism as a fallback
  threading::MultiReaderLock  mutex;
  TDumpers                    dumpers;

  //Warning! No locks inside this function
  void Notify( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly ) const;

private:
  typedef set<StrongMT<INotifyCallback> > NotifyCallbacks;

  const char *    szName;
  unsigned        headerFormat;
  NotifyCallbacks notifyCallbacks;

  const bool IsDumperPresent( const CDumper * pDumper ) const;
};

} //namespace NLogg

#endif //LOGGER_H__
