ALTER TABLE `pw_stat`.`tbl_guild_recruitment` DROP INDEX `Index_guild_id`;
ALTER TABLE `pw_stat`.`tbl_guild_recruitment` ADD INDEX `Index_rating_locale` (`min_rating`,`locale`);
ALTER TABLE `pw_stat`.`tbl_guild_recruitment` MODIFY `message` varchar(512) NOT NULL DEFAULT '';
ALTER TABLE `pw_stat`.`tbl_guild_recruitment` MODIFY `guild_id` bigint(20) unsigned NOT NULL;
