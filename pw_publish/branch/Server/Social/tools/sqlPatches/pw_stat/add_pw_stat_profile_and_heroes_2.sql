DROP TABLE IF EXISTS `pw_stat`.`tbl_user_profile`;
CREATE TABLE  `pw_stat`.`tbl_user_profile` (
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'unixtime',
  `nickname` varchar(32) NOT NULL COMMENT 'utf8 encoding',
  `snid` varchar(4) NOT NULL COMMENT 'social network type',
  `snuid` varchar(20) NOT NULL COMMENT 'social network user id',
  `age` int(11) NOT NULL DEFAULT '0',
  `locale` varchar(4) DEFAULT NULL COMMENT 'user locale',
  `fraction` smallint(5) unsigned DEFAULT '0',
  `reliability` int(11) DEFAULT '0',
  `dt_register` int(11) NOT NULL DEFAULT '0',
  `dt_login` int(11) NOT NULL DEFAULT '0',
  `dt_logout` int(11) NOT NULL DEFAULT '0',
  `gender` smallint(5) unsigned NOT NULL DEFAULT '0',
  `lord_level` smallint(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `pw_stat`.`tbl_user_hero_stats_2`;
CREATE TABLE  `pw_stat`.`tbl_user_hero_stats_2` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL COMMENT 'aggregator uid',
  `hero_id` int(10) unsigned NOT NULL,
  `hero_crc` int(11) NOT NULL DEFAULT '0' COMMENT 'crc32(hero_classname)',
  `hero_rating` int(11) NOT NULL DEFAULT '0',
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'unixtime',
  `hero_force` float NOT NULL DEFAULT '0',
  `hero_last_played` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'timestamp of last award',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`),
  KEY `Index_hero_crc` (`hero_crc`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

