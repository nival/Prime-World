#include "stdafx.h"
#include "LogStreamHolder.h"

namespace NLogg
{

StreamHolder::StreamHolder(NLogg::CChannelLogger* _logStream, 
                           NLogg::CDumper* _logDumper1, NLogg::CDumper* _logDumper2, NLogg::CDumper* _logDumper3)
  :logStream_(_logStream),
  logDumper1_(_logDumper1),
  logDumper2_(_logDumper2),
  logDumper3_(_logDumper3)
{
}

StreamHolder::~StreamHolder()
{
  if (logStream_)
  {
    logStream_->ClearAllDumpers();

    delete logStream_;
    logStream_ = 0;
  }
}

}
