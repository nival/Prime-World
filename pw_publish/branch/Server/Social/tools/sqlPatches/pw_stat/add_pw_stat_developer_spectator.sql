ALTER TABLE `pw_stat`.`tbl_user_profile` 
 ADD COLUMN `is_developer` TINYINT NOT NULL DEFAULT 0 AFTER `population`,
 ADD COLUMN `is_spectator` TINYINT NOT NULL DEFAULT 0 AFTER `is_developer`;
