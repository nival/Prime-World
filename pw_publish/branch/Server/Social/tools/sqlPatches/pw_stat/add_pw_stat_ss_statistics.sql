DROP TABLE IF EXISTS `pw_stat`.`tbl_user_statistics`;
DROP TABLE IF EXISTS `pw_stat`.`tbl_full_user_statistics`;
CREATE TABLE  `pw_stat`.`tbl_full_user_statistics` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `kills` int(11) NOT NULL DEFAULT '0',
  `deaths` int(11) NOT NULL DEFAULT '0',
  `assists` int(11) NOT NULL DEFAULT '0',
  `damage_dealed_total` bigint(20) unsigned NOT NULL DEFAULT '0',
  `neutral_creeps_killed` int(11) NOT NULL DEFAULT '0',
  `enemy_creeps_killed` int(11) NOT NULL DEFAULT '0',
  `total_num_towers_killed` int(11) NOT NULL DEFAULT '0',
  `total_num_quarters_destroyed` int(11) NOT NULL DEFAULT '0',
  `main_buildings_destroyed` int(11) NOT NULL DEFAULT '0',
  `dragon_killed` int(11) NOT NULL DEFAULT '0',
  `cat_killed` int(11) NOT NULL DEFAULT '0',
  `hero_score` int(11) NOT NULL DEFAULT '0',
  `money` bigint(20) unsigned NOT NULL DEFAULT '0',
  `damage_received` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_current_user_statistics`;
CREATE TABLE  `pw_stat`.`tbl_current_user_statistics` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `kills` int(11) NOT NULL DEFAULT '0',
  `deaths` int(11) NOT NULL DEFAULT '0',
  `assists` int(11) NOT NULL DEFAULT '0',
  `damage_dealed_total` bigint(20) unsigned NOT NULL DEFAULT '0',
  `neutral_creeps_killed` int(11) NOT NULL DEFAULT '0',
  `enemy_creeps_killed` int(11) NOT NULL DEFAULT '0',
  `total_num_towers_killed` int(11) NOT NULL DEFAULT '0',
  `total_num_quarters_destroyed` int(11) NOT NULL DEFAULT '0',
  `main_buildings_destroyed` int(11) NOT NULL DEFAULT '0',
  `dragon_killed` int(11) NOT NULL DEFAULT '0',
  `cat_killed` int(11) NOT NULL DEFAULT '0',
  `hero_score` int(11) NOT NULL DEFAULT '0',
  `money` bigint(20) unsigned NOT NULL DEFAULT '0',
  `damage_received` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_max_user_statistics`;
CREATE TABLE  `pw_stat`.`tbl_max_user_statistics` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `kills` int(11) NOT NULL DEFAULT '0',
  `damage_dealed_total` bigint(20) unsigned NOT NULL DEFAULT '0',
  `max_crit_damage` int(5) NOT NULL DEFAULT '0',
  `damage_received` bigint(20) unsigned NOT NULL DEFAULT '0',
  `hero_score` int(11) NOT NULL DEFAULT '0',
  `prime_per_minute` bigint(20) unsigned NOT NULL DEFAULT '0',
  `money` bigint(20) unsigned NOT NULL DEFAULT '0',
  `deaths` int(11) NOT NULL DEFAULT '0',
  `assists` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_user_friends`;
CREATE TABLE  `pw_stat`.`tbl_user_friends` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `friend_auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `nickname` varchar(32) NOT NULL DEFAULT '0',
  `guild_tag` varchar(5) NOT NULL DEFAULT '0',
  `games_together` int(4) NOT NULL DEFAULT '0',
  `winrate` int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;