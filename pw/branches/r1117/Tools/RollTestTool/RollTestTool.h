
#pragma once;

nstl::string buffs_internal_[17] = {

  //35-37 ресурсы
  "Items/GuildBuffs/B035_allresources_cw.xdb",
  "Items/GuildBuffs/B036_allresources_cw.xdb",
  "Items/GuildBuffs/B037_allresources_cw.xdb",
  
  //38-40 серебро
  "Items/GuildBuffs/B038_silver_cw.xdb",
  "Items/GuildBuffs/B039_silver_cw.xdb",
  "Items/GuildBuffs/B040_silver_cw.xdb",
  
  //56-58 кристаллы
  "Items/GuildBuffs/B056_crystal.xdb",
  "Items/GuildBuffs/B057_crystal.xdb",
  "Items/GuildBuffs/B058_crystal.xdb",

  //59-63 таланты
  "Items/GuildBuffs/B059_talent.xdb",
  "Items/GuildBuffs/B060_talent.xdb",
  "Items/GuildBuffs/B061_talent.xdb",
  "Items/GuildBuffs/B062_talent.xdb",
  "Items/GuildBuffs/B063_talent.xdb",
  
  //81 очки тактики
  "Items/GuildBuffs/B081_player_points.xdb",

  "Items/GuildBuffs/B103_Points1_24h.xdb",
  "Items/GuildBuffs/B105_Points2_24h.xdb",
};

vector<nstl::string> buffs(buffs_internal_, buffs_internal_ + 17); 