ALTER TABLE `pw_stat`.`tbl_guild_rating` MODIFY COLUMN `guild_id` BIGINT(20) UNSIGNED NOT NULL DEFAULT 0,
 ADD COLUMN `timestamp` INTEGER UNSIGNED NOT NULL DEFAULT 0 AFTER `num_members`,
 ADD COLUMN `date` DATETIME NOT NULL DEFAULT 0 AFTER `timestamp`,
 ADD UNIQUE INDEX `Index_guild_date`(`guild_id`, `date`);
