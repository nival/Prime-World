#include "stdafx.h"
#include "LoggingImpl.h"

namespace ni_log
{

  
Channel::Channel()
{
}



void Channel::Write( const NLogg::SEntryInfo & _info, const char * _text )
{
  //TODO
}









Main::Main()
{
  //TEMP
  defaultChannel = new Channel;
  channels["test"] = new Channel;
}



Handle * Main::GetHandle( const char * _channel )
{
  return new Handle( GetChannelWriter( _channel ) );
}



IWriter * Main::GetChannelWriter( const char * _channel )
{
  if ( !_channel || !_channel[0] )
    return defaultChannel;

  //TODO: put mutex lock here

  Channels::iterator it = channels.find( _channel );
  if ( it != channels.end() )
    return it->second;

  return defaultChannel;
}

} //namespace ni_log
