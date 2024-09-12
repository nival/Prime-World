#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

namespace ni_log
{

class PrintfFormatterStaticBufferPolicy
{
public:
  typedef text::StaticBuffer<1024> StaticBufferType;

protected:
  PrintfFormatterStaticBufferPolicy() {}

  void InitFormatBuffer( StaticBufferType & _buffer ) {}

  static inline text::IBuffer * ConvertBufferToPointer( StaticBufferType & _buffer ) { return &_buffer; }

  void OnFormatFinished( const StaticBufferType & _buffer ) {
    Write( _buffer.c_str() );
  }

  virtual void Write( const char * _text ) = 0;
};



class IProxy : public text::PrintfFormatter<PrintfFormatterStaticBufferPolicy::StaticBufferType, PrintfFormatterStaticBufferPolicy>
{
public:
};



class IWriter : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IWriter, IBaseInterfaceMT );

public:
  virtual void Write( const NLogg::SEntryInfo & _info, const char * _text ) = 0; //Заголовок будет формироваться позже, на основе настроек в конфиге
};




class LogLevelProxy : public IProxy, public NonCopyable
{
public:
  LogLevelProxy( IWriter * _writer, NLogg::ELevel _lvl ) :
  writer( _writer ),
  level( _lvl )
  {}

protected:
  virtual void Write( const char * _text );

private:
  NLogg::ELevel level;
  StrongMT<IWriter> writer;
};



class Handle : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( Handle, BaseObjectMT );

public:
  Handle( IWriter * _writer );

  LogLevelProxy   dbg;
  LogLevelProxy   info;
  LogLevelProxy   warning;
  LogLevelProxy   error;
  LogLevelProxy   crit;
};



class IMain : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IMain, IBaseInterfaceMT );

public:
  virtual Handle * GetHandle( const char * _channel = 0 ) = 0; 
  virtual IWriter * GetChannelWriter( const char * _channel = 0 ) = 0; //For obsolette static logging
};

} //namespace ni_log

#endif //LOGGING_H_INCLUDED
