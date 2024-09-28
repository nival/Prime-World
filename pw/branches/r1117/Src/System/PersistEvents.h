#ifndef SYSTEM_PERSISTEVENTS_H_INCLUDED
#define SYSTEM_PERSISTEVENTS_H_INCLUDED

namespace persistentEvents
{

namespace EEvent
{
  enum Enum {
    None,
    ClientLaunched,
    ClientCrash,
    LoginFailed,
    Disconnect,
    DisconnectCorruptData,
    ConnectionFailed,
    DisconnectInFR, //During fast reconnect
    LoginFailedInFR, //During fast reconnect
  };
}



struct EventId
{
  unsigned  timestamp; //Application start timestamp
  unsigned  index;

  EventId() :
  timestamp( 0 ), index( 0 )
  {}
};


typedef unsigned __int64 TAuxParam;

struct Event
{
  // Avoid padding here, so MD5 will work properly on this structure
  TAuxParam       aux;
  EventId         id;
  EEvent::Enum    code;
  unsigned        eventTimestamp;

  Event() :
  id(), code( EEvent::None ), aux( 0 ), eventTimestamp( 0 )
  {}
};


class Events : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( Events, BaseObjectMT );

public:
  Events( const char * path );
  ~Events();

  void CheckUnfinishedSessions();
  void Open();
  void Close();

  Event WriteEvent( EEvent::Enum event, TAuxParam auxParam );
  Event WriteEvent( EEvent::Enum event, TAuxParam auxParam, unsigned timestamp );
  void CollectEvents( vector<Event> & buffer );
  void EraseEvents( const vector<Event> & events );

  static unsigned GetTimestamp();

private:
  string    _path;
  unsigned  _startTimeSec, _indexMask;
  unsigned  _nextIdx;
  Event     _launchEvent;

  void CollectEventsImpl( vector<Event> & buffer, EEvent::Enum ignoreEventType );
  void EraseEvent( const Event & event );
  string GenerateFilename( const EventId & id );
  EventId GenerateId();
  string EventKey( const Event & event );
};



void CreateSingleton( const char * path );
void CleanupSingleton();
Events * GetSingleton(); //do not want

class AutoClose {
public:
  AutoClose() {}
  ~AutoClose() {
    if( persistentEvents::GetSingleton() ) {
      persistentEvents::GetSingleton()->Close();
      persistentEvents::CleanupSingleton();
    }
  }
};

} //namespace persistentEvents

#endif SYSTEM_PERSISTEVENTS_H_INCLUDED
