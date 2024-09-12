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
