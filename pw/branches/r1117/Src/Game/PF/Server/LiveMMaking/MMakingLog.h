#ifndef QUICKMATCHERLOG_H_INCLUDED
#define QUICKMATCHERLOG_H_INCLUDED

#include "System/Thread.h"

namespace mmaking
{

namespace ELogLevel
{
  enum Enum
  {
    Critical = 0,
    Normal = 1,
    Verbose = 2
  };
}


class Loger : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( Loger, BaseObjectMT );

public:
  Loger( const char * suffix, const char * header );
  ~Loger();

  bool Poll( timer::Time simulationTime );

  void Log( ELogLevel::Enum level, const char * fmt, ... );

  void SetLogLevel( ELogLevel::Enum level ) { m_level = level; }
  void EnableTimestampLogging( bool logTime ) { m_logTime = logTime; }

  void EnableDebugOutput( bool enable ) { m_debugOutput = enable; }

private:
  void OpenFile();
  void CloseFile();
  void Write( const char * text );

  const string      m_suffix;
  const string      m_logHeader;
  bool              m_debugOutput;
  HANDLE            m_file;
  ELogLevel::Enum   m_level;
  timer::Time       m_simTime;
  int               m_prevDay;
  threading::Mutex  m_mutex;
  bool              m_logTime;
};

} //namespace mmaking

#endif //QUICKMATCHERLOG_H_INCLUDED
