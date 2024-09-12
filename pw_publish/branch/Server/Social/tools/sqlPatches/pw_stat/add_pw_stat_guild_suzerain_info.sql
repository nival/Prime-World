ALTER TABLE `pw_stat`.`tbl_guild_rating` ADD COLUMN `suzerain_name` varchar(64) NOT NULL DEFAULT '0' AFTER `suzerain`;
ALTER TABLE `pw_stat`.`tbl_guild_rating` ADD COLUMN `suzerain_short_name` varchar(8) NOT NULL DEFAULT '0' AFTER `suzerain_name`;
ALTER TABLE `pw_stat`.`tbl_guild_rating` ADD COLUMN `suzerain_rating` float NOT NULL DEFAULT '0' AFTER `suzerain_short_name`;
ALTER TABLE `pw_stat`.`tbl_guild_rating` ADD COLUMN `in_siege` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'bool' AFTER `suzerain_rating`;
ALTER TABLE `pw_stat`.`tbl_guild_rating` ADD COLUMN `siege_end_time` int(10) unsigned NOT NULL DEFAULT '0' AFTER `in_siege`;