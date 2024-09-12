ALTER TABLE `pw_stat`.`tbl_user_hero_stats` ADD COLUMN `locale` VARCHAR(4) DEFAULT NULL COMMENT 'user locale' AFTER `hero_last_played`;
