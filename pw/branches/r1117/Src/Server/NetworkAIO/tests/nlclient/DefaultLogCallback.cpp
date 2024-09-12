#include "stdafx.h"
#include "DefaultLogCallback.h"
#include <ace/Log_Record.h>

  LogCallback::LogCallback(NLogg::CChannelLogger & logstrm)
    :logstrm_(logstrm)
  {
  }

  void LogCallback::log(ACE_Log_Record & record)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    unsigned long msg_severity = record.type();
    ACE_Log_Priority prio = ACE_static_cast (ACE_Log_Priority, msg_severity);
    //const ACE_TCHAR *prio_name = ACE_Log_Record::priority_name (prio);

    NLogg::ELevel level = NLogg::LEVEL_MESSAGE;
    if (prio <= LM_DEBUG)
      level = NLogg::LEVEL_DEBUG;
    else
    if (prio <= LM_INFO)
      level = NLogg::LEVEL_MESSAGE;
    else
    if (prio <= LM_STARTUP) //  LM_WARNING & LM_STARTUP
      level = NLogg::LEVEL_WARNING;
    else
    if (prio <= LM_ERROR)
      level = NLogg::LEVEL_ERROR;
    else
      level = NLogg::LEVEL_CRITICAL;

    ( NLogg::StreamBuffer(logstrm_, NLogg::SEntryInfo( level, DEBUG_FILE_LINE_PARAMS ) ) ) << record.msg_data();
  }
