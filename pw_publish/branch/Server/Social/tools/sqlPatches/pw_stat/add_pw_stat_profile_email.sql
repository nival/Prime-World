ALTER TABLE `pw_stat`.`tbl_user_profile` ADD COLUMN `email` VARCHAR(45) AFTER `lord_level`;
ALTER TABLE `pw_stat`.`tbl_user_profile` ADD COLUMN `realname` VARCHAR(45) AFTER `email`;

