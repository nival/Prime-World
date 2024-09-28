ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD COLUMN `hero_health` int(5) AFTER `hero_last_played`;
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD COLUMN `hero_mana` int(5) AFTER `hero_health`;
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD COLUMN `hero_strength` int(4) AFTER `hero_mana`;
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD COLUMN `hero_intellect` int(4) AFTER `hero_strength`;
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD COLUMN `hero_agility` int(4) AFTER `hero_intellect`;
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD COLUMN `hero_cunning` int(4) AFTER `hero_agility`;
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD COLUMN `hero_fortitude` int(4) AFTER `hero_cunning`;
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` ADD COLUMN `hero_will` int(4) AFTER `hero_fortitude`;
ALTER TABLE `pw_stat`.`tbl_user_hero_stats_2` CHANGE COLUMN `hero_attack_type` `hero_attack_type` varchar(11) NOT NULL;