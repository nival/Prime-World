#include "stdafx.h"

#include "LogHelpers.h"

namespace NLogg
{

const char *MessageLevelToString( const ELevel eLevel )
{
  switch ( eLevel )
  {// request: shorten severity codes to 1 letter
    case LEVEL_MESSAGE:  return "m"; //"message";
    case LEVEL_DEBUG:    return "d"; //"debug";
    case LEVEL_WARNING:  return "W"; //"warning";
    case LEVEL_ERROR:    return "E"; //"error"
    case LEVEL_ASSERT:   return "A"; //"assert";
    case LEVEL_CRITICAL: return "C"; //"critical";
    default: return "";
  }
}


const char * MessageLevelToStringFull( const ELevel eLevel )
{
  switch ( eLevel )
  {
    case LEVEL_MESSAGE:  return "info";
    case LEVEL_DEBUG:    return "debug";
    case LEVEL_WARNING:  return "warning";
    case LEVEL_ERROR:    return "error";
    case LEVEL_ASSERT:   return "assert";
    case LEVEL_CRITICAL: return "critical";
    default: return "";
  }
}

}
