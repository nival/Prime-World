ALTER TABLE `pw_stat`.`tbl_guild_rating` 
 ADD COLUMN `guild_level` INTEGER NOT NULL DEFAULT 0 COMMENT 'level(guild_exp)' AFTER `guild_exp`,
 ADD COLUMN `level_percent` FLOAT NOT NULL DEFAULT 0 COMMENT 'percentage of exp ' AFTER `guild_level`,
 ADD COLUMN `position` INTEGER NOT NULL DEFAULT 0 COMMENT 'current rating pos' AFTER `level_percent`,
 ADD COLUMN `max_position` INTEGER NOT NULL DEFAULT 0 COMMENT 'maximum rating pos (all time)' AFTER `position`,
 ADD COLUMN `icon_revision` INTEGER NOT NULL DEFAULT 0 COMMENT 'guild emblem revision' AFTER `max_position`;
