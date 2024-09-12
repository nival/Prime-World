#include "stdafx.h"
#include "CensorSettings.h"

namespace censorship
{

SettingsStruct::SettingsStruct() :
cleanSpeakUrl( "http://localhost:8001/content/item.xml" ),
cleanSpeakRequest( "contentItem.type=text&filter.operation=replace&filter.blacklist.enabled=true&filter.blacklist.severity=high&filter.replaceString=%2A%2A%2A" ),
queueLimit( 256 ),
queueTimelimit( 5.0f ),
outQueueLimit( 1024 ),
workers( 2 )
{}


static SettingsStruct sett;

REGISTER_VAR( "censor_clean_speak_url",     sett.cleanSpeakUrl, STORAGE_NONE );
REGISTER_VAR( "censor_clean_speak_request", sett.cleanSpeakRequest, STORAGE_NONE );
REGISTER_VAR( "censor_queue_limit",         sett.queueLimit, STORAGE_NONE );
REGISTER_VAR( "censor_queue_timelimit",     sett.queueTimelimit, STORAGE_NONE );
REGISTER_VAR( "censor_out_queue_limit",     sett.outQueueLimit, STORAGE_NONE );
REGISTER_VAR( "censor_workers",             sett.workers, STORAGE_NONE );



Settings::Settings( const SettingsStruct & structSett ) :
SettingsStruct( structSett )
{
}

StrongMT<Settings> CreateSettingsFromConfig()
{
  return new Settings( sett );
}

} //namespace censorship