#include "stdafx.h"
#include "LogMonitorConfig.h"


namespace logMonitor
{

static SConfigData & Cfg()
{
  static SConfigData cfg;
  return cfg;
}


REGISTER_VAR( "log_monitor_on",                   Cfg().enabled, STORAGE_NONE );
REGISTER_VAR( "log_monitor_dest_url",             Cfg().destUrl, STORAGE_NONE );
REGISTER_VAR( "log_monitor_queue_limit",          Cfg().queueLimit, STORAGE_NONE );
REGISTER_VAR( "log_monitor_pack_size",            Cfg().sendPackSize, STORAGE_NONE );
REGISTER_VAR( "log_monitor_default_period",       Cfg().defaultPushPeriod, STORAGE_NONE );
REGISTER_VAR( "log_monitor_max_period",           Cfg().maxPushPeriod, STORAGE_NONE );


Strong<Config> CreateConfigFromStatics()
{
  return new Config( Cfg() );
}

} //namespace logMonitor
