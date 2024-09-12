#include "stdafx.h"

#include "EventDumper.h"
#include "LogHelpers.h"

#include "Events.h"

namespace NLogg
{

DECLARE_EVENT_3_PARAM( 0x9A6BF4C0, SystemLogEvent, FixedString<1024>, message, int, time, FixedString<32>, level );

void CEventDumper::OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  threading::MutexLock guard( mutex );

  //TODO: здесь вместо 0 передавалось скал€рное врем€ в секундах
  SystemLogEvent::Log( textOnly, 0, MessageLevelToString( entryInfo.level ) );
}
	
}
REGISTER_EVENT_NS( NLogg, SystemLogEvent )
