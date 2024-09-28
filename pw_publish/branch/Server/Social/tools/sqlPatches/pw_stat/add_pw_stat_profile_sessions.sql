ALTER TABLE `pw_stat`.`tbl_user_profile` 
 ADD COLUMN `dt_birth` INTEGER NOT NULL DEFAULT 0 COMMENT 'unixtime birthdate' AFTER `age`,
 ADD COLUMN `dt_pay` INTEGER NOT NULL DEFAULT 0 COMMENT 'unixtime last payment' AFTER `dt_logout`,
 ADD COLUMN `sessions` INTEGER NOT NULL DEFAULT 0 COMMENT 'pvx sessions played' AFTER `dt_pay`,
 ADD COLUMN `silver` BIGINT NOT NULL DEFAULT 0 AFTER `realname`,
 ADD COLUMN `gold` INTEGER NOT NULL DEFAULT 0 AFTER `silver`,
 ADD COLUMN `perl` INTEGER NOT NULL DEFAULT 0 AFTER `gold`,
 ADD COLUMN `resource1` INTEGER NOT NULL DEFAULT 0 AFTER `perl`,
 ADD COLUMN `resource2` INTEGER NOT NULL DEFAULT 0 AFTER `resource1`,
 ADD COLUMN `resource3` INTEGER NOT NULL DEFAULT 0 AFTER `resource2`,
 ADD COLUMN `population` INTEGER NOT NULL DEFAULT 0 AFTER `resource3`
;

ALTER TABLE `pw_stat`.`tbl_guild_rating` 
 ADD COLUMN `guild_exp` INTEGER NOT NULL DEFAULT 0 AFTER `date`
;
