DROP TABLE IF EXISTS `pw_stat`.`tbl_pvx_hero_stats`;
CREATE TABLE  `pw_stat`.`tbl_pvx_hero_stats` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `hero_crc` int(11) NOT NULL DEFAULT '0' COMMENT 'crc32(hero_classname)',
  `games_total` int(7) NOT NULL DEFAULT '0',
  `borderlands_games` int(7) NOT NULL DEFAULT '0',
  `winrate_total` int(4) NOT NULL DEFAULT '0',
  `winrate_curent` int(4) NOT NULL DEFAULT '0',
  `kda_total` varchar(10) NOT NULL DEFAULT '',
  `kda_current` varchar(10) NOT NULL DEFAULT '',
  `prime_per_minute_total` int(5) NOT NULL DEFAULT '0',
  `prime_per_minute_current` int(5) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`),
  KEY `Index_hero_crc` (`hero_crc`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_pvx_user_statistics`;
CREATE TABLE  `pw_stat`.`tbl_pvx_user_statistics` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `session_id` bigint(20) unsigned NOT NULL,
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `borderlands_games` int(11) NOT NULL DEFAULT '0',
  `borderlands_alone` int(11) NOT NULL DEFAULT '0',
  `borderlands_party` int(11) NOT NULL DEFAULT '0',
  `traning_games` int(11) NOT NULL DEFAULT '0',
  `fixed_games` int(11) NOT NULL DEFAULT '0',
  `guild_games` int(11) NOT NULL DEFAULT '0',
  `native_terrain_games` int(11) NOT NULL DEFAULT '0',
  `mid_only_games` int(11) NOT NULL DEFAULT '0',
  `dragonvald_games` int(11) NOT NULL DEFAULT '0',
  `leapfrog_games` int(11) NOT NULL DEFAULT '0',
  `zombie_games` int(11) NOT NULL DEFAULT '0',
  `pve_games` int(11) NOT NULL DEFAULT '0',
  `winrate` int(4) NOT NULL DEFAULT '0',
  `winrate_alone` int(4) NOT NULL DEFAULT '0',
  `winrate_party` int(4) NOT NULL DEFAULT '0',
  `winstrike`int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_pvx_session_results`;
CREATE TABLE  `pw_stat`.`tbl_pvx_session_results` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `session_id` bigint(20) unsigned NOT NULL,
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `native_ground1` int(4) NOT NULL DEFAULT '0',
  `native_ground2` int(4) NOT NULL DEFAULT '0',
  `common_kills1` int(4) NOT NULL DEFAULT '0',
  `common_kills2` int(4) NOT NULL DEFAULT '0',
  `common_prime1` int(4) NOT NULL DEFAULT '0',
  `common_prime2` int(4) NOT NULL DEFAULT '0',
  `time_spent` int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `Index_session_id` (`session_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_pvx_session_to_hero_results`;
CREATE TABLE  `pw_stat`.`tbl_pvx_session_to_hero_results` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `session_id` bigint(20) unsigned NOT NULL,
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `hero_crc` int(11) NOT NULL DEFAULT '0' COMMENT 'crc32(hero_classname)',
  `hero_rating` int(11) NOT NULL DEFAULT '0',
  `hero_level` int(11) NOT NULL DEFAULT '0',
  `hero_kills` int(11) NOT NULL DEFAULT '0',
  `hero_deaths` int(11) NOT NULL DEFAULT '0',
  `hero_assists` int(11) NOT NULL DEFAULT '0',
  `hero_score` int(11) NOT NULL DEFAULT '0',
  `hero_prime` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `Index_session_id` (`session_id`),
  KEY `Index_auid` (`auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;