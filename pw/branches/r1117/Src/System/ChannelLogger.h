// Intermediate logger class, supports multiple logging channels
// (addressed by name, each with its own log-level mask and own set of mappable dumpers)
#ifndef CHANNEL_LOGGER_H__
#define CHANNEL_LOGGER_H__

#include "Logger.h"
#include "Dumper.h"
#include "nstring.h"
#include "nvector.h"
#include "nmap.h"


namespace NLogg
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A logging channel (with name, logging levels and its own set of dumpers assigned.
struct SLoggingChannel : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( SLoggingChannel, BaseObjectST );

  string              name;
  unsigned            levelFilter; // by default -- inherited from common CChannelLogger::dwLevelFilter
  CLogger::TDumpers   dumpers; // NULL == default context (use all possible dumpers, from CLogger::dumpers)

  SLoggingChannel( const char * _name, const CLogger::TDumpers & _dumpers, unsigned _levelFilter = LEVEL_INHERIT ) :
  name( _name ),
  levelFilter( _levelFilter ),
  dumpers( _dumpers )
  {}
}; 



struct SCounters
{
  LONG  warnings;
  LONG  errors;
  LONG  asserts;
  LONG  criticals;

  SCounters() : warnings( 0 ), errors( 0 ), asserts( 0 ), criticals( 0 ) {}
  SCounters( const SCounters & _data ) :
  warnings( _data.warnings ), errors( _data.errors ), asserts( _data.asserts ), criticals( _data.criticals ) {}
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Logger class, supports multiple logging channels
// Channels are addressed by name, each with its own log-level mask and own set of mappable dumpers.
class CChannelLogger : public CLogger
{
public:
  CChannelLogger( const char *szName ) :
  CLogger( szName ), dwLevelFilter( LEVEL_ALL )
  {}

  virtual ~CChannelLogger();

  bool IsChannelPresent( const char *szChannelName ) const; 

  bool AddChannel( const char * name, CDumper * dumper1, unsigned levelFilter = LEVEL_INHERIT );
  bool AddChannel( const char * name, CDumper * dumper1, CDumper * dumper2, unsigned levelFilter = LEVEL_INHERIT );
  bool AddChannel( const char * name, CDumper * dumper1, CDumper * dumper2, CDumper * dumper3, unsigned levelFilter = LEVEL_INHERIT );
  bool AddChannel( const char * name, CDumper * dumper1, CDumper * dumper2, CDumper * dumper3, CDumper * dumper4, unsigned levelFilter = LEVEL_INHERIT );

  void ClearAllDumpers(); //hides CLogger::ClearAllDumpers()

  // returns false if no such channel present
  bool RemoveChannel( const char* szChannelName );

  virtual void Log( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

  // set new filter mask for a given channel (szChannelName) or for default "all-dumpers" logging (szChannelName == NULL)
  bool SetChannelLevelFilter( const char* szChannelName, unsigned long dwNewLevelFilter);
  // helper for channel filter:
  bool SetChannelMinLevelFilter( const char* szChannelName, const ELevel eLevel ) { return SetChannelLevelFilter( szChannelName, NLogg::GetFromMinLevelMask(eLevel) ); }
  // helper for default (channel=NULL) filter:
  bool SetDefaultMinLevelFilter( const ELevel eLevel ) { return SetChannelLevelFilter( NULL, NLogg::GetFromMinLevelMask(eLevel) ); }

  void TEST_LOG( const char *szFileName, const unsigned long dwLine, const ELevel eLevel, const char *szMessage, 
                 const char *szChannelName=NULL );

  void DUMP_CHANNELS() const;

  SCounters GetCounters();

private:
  typedef nstl::map<string, Strong<SLoggingChannel> > TChannels;

  TChannels   channels;
  unsigned    dwLevelFilter;

  volatile SCounters counters;

  bool AddChannel( const char * _name, const TDumpers & _dumpers, unsigned _levelFilter );

  void UpdateCounters( const SEntryInfo & entryInfo );

  // choose, to which dumpers should we log
  // NB!
  // 1) if channel name is NULL, we return DEFAULT dump context == ptr to full list of base CLogger::dumpers
  // 2) if there's NO channel with given non-null name, we retun NULL (no dumps to do)
  // 3) if there IS such a channel, but it doesn't take messages with eLevel severity, we return NULL (no dumps to do)
  // => so we can live without pre-allocated "default channel": if there's no channels, we just use default dumpers list (base CLogger way)
  const TDumpers* GetDumpContext( const char *szChannelName, const ELevel eLevel ) const; 
};

} // namespace NLogg


#endif // CHANNEL_LOGGER_H__
