ALTER TABLE `pw_stat`.`tbl_user_profile` ADD COLUMN `bad_behaviour_reason` tinyint(4) NOT NULL DEFAULT '0' AFTER `leaver_points`;
