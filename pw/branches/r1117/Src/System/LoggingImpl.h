#ifndef LOGGINGIMPL_H_INCLUDED
#define LOGGINGIMPL_H_INCLUDED

#include "Logging.h"

namespace ni_log
{

class Channel : public IWriter, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Channel, IWriter, BaseObjectMT );

public:
  Channel();

protected:
  //IWriter
  virtual void Write( const NLogg::SEntryInfo & _info, const char * _text );
};




class Main : public IMain, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( Main, IMain, BaseObjectMT );

public:
  Main();

protected:
  //IMain
  virtual Handle * GetHandle( const char * _channel );
  virtual IWriter * GetChannelWriter( const char * _channel );

private:
  typedef map<string, StrongMT<Channel> > Channels;
  StrongMT<Channel>   defaultChannel;
  Channels  channels;
};


} //namespace ni_log

#endif //LOGGINGIMPL_H_INCLUDED
