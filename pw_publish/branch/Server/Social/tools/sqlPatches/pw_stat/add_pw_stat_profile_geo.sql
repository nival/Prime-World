ALTER TABLE `pw_stat`.`tbl_user_profile` ADD COLUMN `geo_country` VARCHAR(2) DEFAULT NULL COMMENT 'user country, 2-char ISO code, by geo-ip' AFTER `locale`;
ALTER TABLE `pw_stat`.`tbl_user_profile` ADD COLUMN `geo_region` VARCHAR(2) DEFAULT NULL COMMENT 'user region, 2-char code, by geo-ip' AFTER `geo_country`;
ALTER TABLE `pw_stat`.`tbl_user_profile` ADD COLUMN `geo_city` VARCHAR(40) DEFAULT NULL COMMENT 'user city, by geo-ip' AFTER `geo_region`;
ALTER TABLE `pw_stat`.`tbl_user_profile` ADD COLUMN `geo_rating_enabled` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'user agrees to be shown in a local rating' AFTER `geo_city`;

