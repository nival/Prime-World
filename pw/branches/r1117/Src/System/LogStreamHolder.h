#pragma once
#include <System/ChannelLogger.h>
#include <System/TextFileDumper.h>

namespace NLogg
{
/// »спользуетс€ дл€ контрол€ времени жизни Logger'а и его dumper'ов
class StreamHolder : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( StreamHolder, BaseObjectMT );

public:
  StreamHolder(NLogg::CChannelLogger* _logStream, NLogg::CDumper* _logDumper1, NLogg::CDumper* _logDumper2 = 0, NLogg::CDumper* _logDumper3 = 0);
  ~StreamHolder();

public:
  NLogg::CChannelLogger*  logStream() const { return logStream_; }

private:
  CChannelLogger *    logStream_;
  StrongMT<CDumper>   logDumper1_;
  StrongMT<CDumper>   logDumper2_;
  StrongMT<CDumper>   logDumper3_;
};

}
