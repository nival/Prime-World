#ifndef LOGMONITORBUFFER_H_INCLUDED
#define LOGMONITORBUFFER_H_INCLUDED

#include <list>

namespace logMonitor
{

class BufferedEvent : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( BufferedEvent, BaseObjectMT );
public:
  BufferedEvent( const NLogg::SEntryInfo & _entryInfo, const char * _text ) :
  entryInfo( _entryInfo ),
  text( _text )
  {}

  const NLogg::SEntryInfo & EntryInfo() const { return entryInfo; }
  const string & Text() const { return text; }

private:
  const NLogg::SEntryInfo entryInfo;
  const string text;
};



typedef std::list<StrongMT<BufferedEvent> >  EventQueue;


class LogBuffer : public NLogg::INotifyCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( LogBuffer, NLogg::INotifyCallback, BaseObjectMT );

public:
  LogBuffer();

  void PopEvents( EventQueue & evt, unsigned & _eventsSkipped );

private:
  threading::Mutex  mutex;
  EventQueue        events;
  unsigned          eventsSkipped;

  //NLogg::INotifyCallback
  virtual void OnLogEvent( const NLogg::SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );
};


} //namespace logMonitor

#endif //LOGMONITORBUFFER_H_INCLUDED
