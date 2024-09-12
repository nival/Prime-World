namespace csharp MonitoringService

struct MonitoringInfo {
  1: i32 game_ccu,
  2: i32 bld_ccu,
  3: i32 dwd_ccu,
  4: i32 ner_ccu,
  5: i32 ops_ccu,
  6: i32 trn_ccu,
  7: i32 tut_ccu,
  8: i32 oth_ccu,
  9: i32 socialccu,
  10: i32 mmakingusers,
  11: i32 begin_delivery_awards_count,
  12: i32 begin_delivery_guild_awards_count,
  13: i32 awards_delivered_count,
  14: i32 awards_failed_count,
  15: i32 awards_line_size,
  16: i32 awards_in_line_time
}

service MonitoringSummary {
  i32 GetGameClusterCCU(),
  i32 GetSocialClusterCCU(),
  i32 GetNumberOfMatchmakingUsers(),

  i32 GetMonitoringCounter(1: string name),

  MonitoringInfo GetFullMonitoringInfo()
}