#include "stdafx.h"
#include "LogMonitorBuffer.h"


namespace logMonitor
{

const static unsigned  InternalFirecaseQueueLimit = 16384;



LogBuffer::LogBuffer() :
eventsSkipped( 0 )
{
}



//NLogg::INotifyCallback
void LogBuffer::OnLogEvent( const NLogg::SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  //ATTENTION!!!
  //NO ASSERTS OR LOGGING IN THIS CALLBACK!!

  switch ( entryInfo.level )
  {
    default:
      return;

    case NLogg::LEVEL_WARNING:
    case NLogg::LEVEL_ERROR:
    case NLogg::LEVEL_ASSERT:
    case NLogg::LEVEL_CRITICAL:
    {
      threading::MutexLock lock( mutex );

      if ( events.size() < InternalFirecaseQueueLimit )
        events.push_back( new BufferedEvent( entryInfo, textOnly ) );
      else
        ++eventsSkipped;

      return;
    }
  }
}



void LogBuffer::PopEvents( EventQueue & evt, unsigned & _eventsSkipped )
{
  threading::MutexLock lock( mutex );

  evt.swap( events );

  events.clear();
  _eventsSkipped = eventsSkipped;

  eventsSkipped = 0;
}


} //namespace logMonitor
