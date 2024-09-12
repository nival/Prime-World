ALTER TABLE `pw_stat`.`tbl_guild_rating` ADD COLUMN `lead_auid` BIGINT(20) UNSIGNED NOT NULL DEFAULT '0',
  ADD INDEX `Index_lead` (`lead_auid`);