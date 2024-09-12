ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD INDEX `Index_hero_id` (`hero_id`);
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD INDEX `Index_hero_last_played` (`hero_last_played`);
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD INDEX `Index_hero_rating` (`hero_rating`);
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD INDEX `Index_merge` (`hero_crc`,`hero_rating`) USING BTREE;