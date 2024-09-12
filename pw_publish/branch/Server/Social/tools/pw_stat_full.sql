set sql_mode="NO_AUTO_CREATE_USER";
DROP DATABASE IF EXISTS `pw_stat`;
CREATE database pw_stat;

-- DELETE USER IF EXIST workaround
-- http://stackoverflow.com/questions/598190/mysql-check-if-the-user-exists-and-drop-it
-- http://bugs.mysql.com/bug.php?id=7000
GRANT USAGE ON *.* TO pws@localhost identified BY "x";
DROP user pws@localhost;

CREATE USER pws@localhost;
GRANT ALL ON pw_stat.* TO pws@localhost identified BY "pwsdata";

DROP TABLE IF EXISTS `pw_stat`.`tbl_user_hero_stats`;
CREATE TABLE  `pw_stat`.`tbl_user_hero_stats` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `hero_id` int(10) unsigned NOT NULL,
  `hero_crc` int(11) NOT NULL DEFAULT '0' COMMENT 'crc32(hero_classname)',
  `hero_rating` int(11) NOT NULL DEFAULT '0',
  `reliability` int(11) NOT NULL DEFAULT '0',
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'unixtime',
  `nickname` varchar(32) NOT NULL COMMENT 'utf8 encoding',
  `snid` varchar(4) NOT NULL COMMENT 'social network type',
  `snuid` varchar(20) NOT NULL COMMENT 'social network user id',
  `fraction` varchar(1) DEFAULT NULL,
  `hero_force` float NOT NULL DEFAULT '0',
  `hero_last_played` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'timestamp of last award',
  `locale` varchar(4) DEFAULT NULL COMMENT 'user locale',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`),
  KEY `Index_hero_crc` (`hero_crc`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_user_build_stats`;
CREATE TABLE  `pw_stat`.`tbl_user_build_stats` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `build_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'id in ModelData',
  `build_crc` int(11) NOT NULL DEFAULT '0' COMMENT 'crc32 == PersistentId',
  `build_level` int(11) NOT NULL DEFAULT '0',
  `timestamp` int(11) NOT NULL DEFAULT '0' COMMENT 'unix timestamp',
  `in_pocket` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'bool',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`),
  KEY `Index_crc` (`build_crc`)
)
ENGINE = MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_guild_rating`;
CREATE TABLE  `pw_stat`.`tbl_guild_rating` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `guild_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `rating` float NOT NULL DEFAULT '0',
  `prev_rating` float NOT NULL DEFAULT '0',
  `prev_place` int(11) NOT NULL DEFAULT '0',
  `guild_name` varchar(64) NOT NULL,
  `guild_short_name` varchar(8) NOT NULL,
  `fraction` smallint(6) NOT NULL DEFAULT '0',
  `num_members` smallint(6) NOT NULL DEFAULT '0',
  `max_members` smallint(6) NOT NULL DEFAULT '0',
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0',
  `date` date NOT NULL DEFAULT '1000-01-01',
  `guild_exp` bigint(20) NOT NULL DEFAULT '0',
  `guild_level` int(11) NOT NULL DEFAULT '0' COMMENT 'level(guild_exp)',
  `level_percent` float NOT NULL DEFAULT '0' COMMENT 'percentage of exp between current and next guild_level',
  `position` int(11) NOT NULL DEFAULT '0' COMMENT 'current rating pos',
  `position_change` int(11) NOT NULL DEFAULT '0' COMMENT 'rating delta between today and yesterday',
  `max_position` int(11) NOT NULL DEFAULT '0' COMMENT 'maximum rating pos (all time)',
  `icon_revision` int(11) NOT NULL DEFAULT '0' COMMENT 'guild emblem revision',
  `lead_auid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `shop_level` int(4) unsigned NOT NULL DEFAULT '0',
  `suzerain` bigint(20) NOT NULL DEFAULT '0',
  `suzerain_name` varchar(64) NOT NULL,
  `suzerain_short_name` varchar(8) NOT NULL,
  `suzerain_rating` float unsigned NOT NULL DEFAULT '0',
  `is_locked` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'bool',
  `siege_end_time` int(10) unsigned NOT NULL DEFAULT '0',
  `current_event_id` bigint(20) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_guild_date` (`guild_id`,`date`),
  KEY `Index_guild_id` (`guild_id`),
  KEY `Index_rating` (`rating`),
  KEY `Index_lead` (`lead_auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_guild_rating_history`;
CREATE TABLE `pw_stat`.`tbl_guild_rating_history` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `guild_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `event_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `rating` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `index_guild` (`guild_id`),
  KEY `index_event` (`event_id`),
  KEY `index_rating` (`rating`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_guild_recruitment`;
CREATE TABLE  `pw_stat`.`tbl_guild_recruitment` (
  `guild_id` bigint(20) unsigned NOT NULL,
  `message` varchar(512) NOT NULL DEFAULT '',
  `locale` varchar(2) NOT NULL,
  `min_rating` int(11) NOT NULL DEFAULT '1000',
  PRIMARY KEY (`guild_id`),
  KEY `Index_rating_locale` (`min_rating`,`locale`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_user_profile`;
CREATE TABLE  `pw_stat`.`tbl_user_profile` (
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'unixtime',
  `nickname` varchar(32) NOT NULL COMMENT 'utf8 encoding',
  `snid` varchar(4) NOT NULL COMMENT 'social network type',
  `snuid` varchar(512) NOT NULL COMMENT 'social network user id',
  `age` int(11) NOT NULL DEFAULT '0',
  `dt_birth` int(11) NOT NULL DEFAULT '0' COMMENT 'unixtime birthdate',
  `locale` varchar(4) DEFAULT NULL COMMENT 'user locale',
  `geo_country` VARCHAR(2) DEFAULT NULL COMMENT 'user country, 2-chars ISO code, by geo-ip' ,
  `geo_region` VARCHAR(2) DEFAULT NULL COMMENT 'user region, 2-char code, by geo-ip',
  `geo_city` VARCHAR(40) DEFAULT NULL COMMENT 'user city, by geo-ip',
  `geo_rating_enabled` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'user agrees to be shown in a local rating',
  `fraction` smallint(5) unsigned DEFAULT '0',
  `reliability` int(11) DEFAULT '0',
  `dt_register` int(11) NOT NULL DEFAULT '0',
  `dt_login` int(11) NOT NULL DEFAULT '0',
  `dt_logout` int(11) NOT NULL DEFAULT '0',
  `dt_pay` int(11) NOT NULL DEFAULT '0' COMMENT 'unixtime last payment',
  `sessions` int(11) NOT NULL DEFAULT '0' COMMENT 'pvx sessions played',
  `gender` smallint(5) unsigned NOT NULL DEFAULT '0',
  `lord_level` smallint(5) unsigned NOT NULL DEFAULT '0',
  `email` varchar(45) DEFAULT NULL,
  `realname` varchar(45) DEFAULT NULL,
  `silver` BIGINT NOT NULL DEFAULT 0,
  `gold` INTEGER NOT NULL DEFAULT 0,
  `perl` INTEGER NOT NULL DEFAULT 0,
  `red_perl` INTEGER NOT NULL DEFAULT 0,
  `resource1` INTEGER NOT NULL DEFAULT 0,
  `resource2` INTEGER NOT NULL DEFAULT 0,
  `resource3` INTEGER NOT NULL DEFAULT 0,
  `currency` varchar(255) NOT NULL DEFAULT '',
  `shard` INTEGER NOT NULL DEFAULT 0,
  `population` INTEGER NOT NULL DEFAULT 0,
  `is_developer` tinyint(4) NOT NULL DEFAULT '0',
  `is_spectator` tinyint(4) NOT NULL DEFAULT '0',
  `is_leaver` tinyint(4) NOT NULL DEFAULT '0',
  `leaver_points` int(11) NOT NULL DEFAULT '0',
  `bad_behaviour_reason` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_user_hero_stats_2`;
CREATE TABLE  `pw_stat`.`tbl_user_hero_stats_2` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `hero_id` int(10) unsigned NOT NULL,
  `hero_ts_id` int(1) unsigned NOT NULL,
  `hero_crc` int(11) NOT NULL DEFAULT '0' COMMENT 'crc32(hero_classname)',
  `hero_rating` int(11) NOT NULL DEFAULT '0',
  `hero_class` varchar(15) NOT NULL DEFAULT '',
  `hero_skin` int(11) NOT NULL DEFAULT '0' COMMENT 'crc32(current hero skin)',
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'unixtime',
  `hero_force` float NOT NULL DEFAULT '0',
  `hero_level` int(3) NOT NULL DEFAULT '0',
  `hero_last_played` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'timestamp of last award',
  `hero_health` int(5) NOT NULL DEFAULT '0',
  `hero_mana` int(5) NOT NULL DEFAULT '0',
  `hero_strength` int(4) NOT NULL DEFAULT '0',
  `hero_intellect` int(4) NOT NULL DEFAULT '0',
  `hero_agility` int(4) NOT NULL DEFAULT '0',
  `hero_cunning` int(4) NOT NULL DEFAULT '0',
  `hero_fortitude` int(4) NOT NULL DEFAULT '0',
  `hero_will` int(4) NOT NULL DEFAULT '0',
  `hero_attack_type` varchar(11) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`),
  KEY `Index_hero_crc` (`hero_crc`),
  KEY `Index_hero_last_played` (`hero_last_played`),
  KEY `Index_hero_rating` (`hero_rating`),
  KEY `Index_merge` (`hero_crc`,`hero_rating`) USING BTREE,
  KEY `Index_hero_id` (`hero_id`),
  KEY `Index_talentset_id` (`hero_ts_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tournaments`;
CREATE TABLE  `pw_stat`.`tournaments` (
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `ticket_id` varchar(255) NOT NULL DEFAULT '' COMMENT 'ticket id, identifies a tournament',
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `bought_type` tinyint unsigned NOT NULL DEFAULT 0 COMMENT 'code, saying how the ticket was bought',
  `state` tinyint unsigned NOT NULL DEFAULT 0 COMMENT 'is ticket new, in tournamant or lost already',
  `wins` smallint unsigned NOT NULL DEFAULT 0 COMMENT 'number of player wins in this tournament',
  `losses` smallint unsigned NOT NULL DEFAULT 0 COMMENT 'number of player losses in this tournament',
  `gold` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'gold earned for wins',
  `max_duration` float NOT NULL DEFAULT 0.0 COMMENT 'maximum battle duration',
  PRIMARY KEY (`auid`, `ticket_id`),
  KEY `Index_time` (`timestamp`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_user_hero_talentset`;
CREATE TABLE  `pw_stat`.`tbl_user_hero_talentset` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `hero_id` bigint(20) unsigned NOT NULL COMMENT 'id from tbl_user_hero_stats_2',
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `timestamp` int(10) unsigned NOT NULL DEFAULT 0 COMMENT 'unixtime',
  `talent1` varchar(20) NOT NULL DEFAULT '0',
  `talent2` varchar(20) NOT NULL DEFAULT '0',
  `talent3` varchar(20) NOT NULL DEFAULT '0',
  `talent4` varchar(20) NOT NULL DEFAULT '0',
  `talent5` varchar(20) NOT NULL DEFAULT '0',
  `talent6` varchar(20) NOT NULL DEFAULT '0',
  `talent7` varchar(20) NOT NULL DEFAULT '0',
  `talent8` varchar(20) NOT NULL DEFAULT '0',
  `talent9` varchar(20) NOT NULL DEFAULT '0',
  `talent10` varchar(20) NOT NULL DEFAULT '0',
  `talent11` varchar(20) NOT NULL DEFAULT '0',
  `talent12` varchar(20) NOT NULL DEFAULT '0',
  `talent13` varchar(20) NOT NULL DEFAULT '0',
  `talent14` varchar(20) NOT NULL DEFAULT '0',
  `talent15` varchar(20) NOT NULL DEFAULT '0',
  `talent16` varchar(20) NOT NULL DEFAULT '0',
  `talent17` varchar(20) NOT NULL DEFAULT '0',
  `talent18` varchar(20) NOT NULL DEFAULT '0',
  `talent19` varchar(20) NOT NULL DEFAULT '0',
  `talent20` varchar(20) NOT NULL DEFAULT '0',
  `talent21` varchar(20) NOT NULL DEFAULT '0',
  `talent22` varchar(20) NOT NULL DEFAULT '0',
  `talent23` varchar(20) NOT NULL DEFAULT '0',
  `talent24` varchar(20) NOT NULL DEFAULT '0',
  `talent25` varchar(20) NOT NULL DEFAULT '0',
  `talent26` varchar(20) NOT NULL DEFAULT '0',
  `talent27` varchar(20) NOT NULL DEFAULT '0',
  `talent28` varchar(20) NOT NULL DEFAULT '0',
  `talent29` varchar(20) NOT NULL DEFAULT '0',
  `talent30` varchar(20) NOT NULL DEFAULT '0',
  `talent31` varchar(20) NOT NULL DEFAULT '0',
  `talent32` varchar(20) NOT NULL DEFAULT '0',
  `talent33` varchar(20) NOT NULL DEFAULT '0',
  `talent34` varchar(20) NOT NULL DEFAULT '0',
  `talent35` varchar(20) NOT NULL DEFAULT '0',
  `talent36` varchar(20) NOT NULL DEFAULT '0',
  `talentset_id` int(1) unsigned NOT NULL DEFAULT 0 COMMENT 'talentset id',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`),
  KEY `Index_hero_id` (`hero_id`),
  KEY `Index_talentset_id` (`talentset_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

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

DROP TABLE IF EXISTS `pw_stat`.`tbl_seasons_league`;
CREATE TABLE `pw_stat`.`tbl_seasons_league` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `uid` bigint(20) NOT NULL COMMENT 'user uid in tbl_login',
  `hero_id` bigint(20) NOT NULL COMMENT 'user uid in tbl_login',
  `rating` float COMMENT 'user rating',
  `nickname` varchar(32) COMMENT 'user nickname',
  `prev_league_place` bigint(20) DEFAULT 0 COMMENT 'last rating value',
  PRIMARY KEY (`id`),
  KEY `Index_uid` (`uid`),
  KEY `Index_hero_id` (`hero_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`schema_version`;
CREATE TABLE `pw_stat`.`schema_version` (
  `schema` varchar(16) NOT NULL,
  `version` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`schema`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
INSERT INTO `pw_stat`.`schema_version` VALUES("pw_stat", 1);

DELIMITER $$

DROP PROCEDURE IF EXISTS `pw_stat`.`update_league_info`$$
CREATE PROCEDURE `pw_stat`.`update_league_info`( auid bigint, ahero_id bigint, arating float, anickname varchar(32) )
BEGIN
  DECLARE dataId BIGINT DEFAULT 0;

  SELECT `id` INTO dataId FROM tbl_seasons_league WHERE uid = auid AND hero_id = ahero_id;

  DROP temporary table IF EXISTS temp_table_cur_places;
  create temporary table temp_table_cur_places SELECT  l.id, @curRow := @curRow + 1 AS league_place
  FROM    tbl_seasons_league l
  JOIN    (SELECT @curRow := 0) r
  WHERE hero_id = ahero_id
  ORDER BY rating DESC;

  IF dataId != 0 THEN
    UPDATE tbl_seasons_league
    SET rating = arating, nickname = anickname
    WHERE id = dataId;
    SELECT LAST_INSERT_ID() as ok;
  ELSE
    INSERT INTO tbl_seasons_league (`uid`, `hero_id`, `rating`, `nickname`, `prev_league_place`) VALUES (auid, ahero_id, arating, anickname, -1);
    SELECT LAST_INSERT_ID() as ok;
  END IF;

  DROP temporary table IF EXISTS temp_table_new_places;
  create temporary table temp_table_new_places SELECT  l.id, @curRow := @curRow + 1 AS league_place
  FROM    tbl_seasons_league l
  JOIN    (SELECT @curRow := 0) r
  WHERE hero_id = ahero_id
  ORDER BY rating DESC;

  UPDATE tbl_seasons_league dest, (select * from temp_table_cur_places) last_rating, (select * from temp_table_new_places) new_rating
  SET dest.prev_league_place = last_rating.league_place WHERE dest.id = last_rating.id AND last_rating.league_place <> new_rating.league_place;

  DROP temporary table temp_table_new_places;
  DROP temporary table temp_table_cur_places;

END $$

DELIMITER ;

