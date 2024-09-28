#include "TamarinPCH.h"

#include "TestingFacility.h"

namespace avmplus
{
avmplus::AvmBox TestingFacilityClass::AssertImpl( bool expression, AvmString msg )
{
  StUTF8String message(msg);
  NI_ASSERT(expression, message.c_str());
  SwfDebugLog::CallLog("AssertPassed", message.c_str());
  return (AvmBox)0;
}
} 