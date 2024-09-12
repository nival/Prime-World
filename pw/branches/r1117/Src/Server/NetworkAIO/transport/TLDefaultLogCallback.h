#pragma once
#include <ace/Log_Msg_Callback.h>

namespace TransportLayer
{
  class LogCallback : public ACE_Log_Msg_Callback
  {
  public:
    LogCallback(NLogg::CChannelLogger & logstrm);

  public:
    void log(ACE_Log_Record &log_record);

  private:
    NLogg::CChannelLogger & logstrm_;
  };
}
