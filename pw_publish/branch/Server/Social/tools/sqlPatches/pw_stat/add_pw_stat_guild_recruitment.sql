ALTER TABLE `pw_stat`.`tbl_guild_rating` ADD COLUMN `max_members` smallint(6) NOT NULL DEFAULT '0' AFTER `num_members`;

DROP TABLE IF EXISTS `pw_stat`.`tbl_guild_recruitment`;
CREATE TABLE  `pw_stat`.`tbl_guild_recruitment` (
  `guild_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `message` varchar(512) NOT NULL,
  `locale` varchar(2) NOT NULL,
  `min_rating` int(11) NOT NULL DEFAULT '1000', 
  PRIMARY KEY (`guild_id`),
  KEY `Index_guild_id` (`guild_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;