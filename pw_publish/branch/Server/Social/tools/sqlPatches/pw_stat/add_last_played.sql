ALTER TABLE `tbl_user_hero_stats` ADD COLUMN `hero_last_played` INTEGER UNSIGNED NOT NULL DEFAULT 0 COMMENT 'timestamp of last award' AFTER `hero_force`;
