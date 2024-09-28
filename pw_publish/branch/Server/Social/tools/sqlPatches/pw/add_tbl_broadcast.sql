CREATE TABLE `tbl_broadcast` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT COMMENT 'msgId',
  `title` VARCHAR(128) COMMENT 'message title',
  `message` VARCHAR(2048) NOT NULL COMMENT 'message text',
  `tstart` BIGINT UNSIGNED NOT NULL COMMENT 'rotation start timestamp',
  `tfin` BIGINT UNSIGNED NOT NULL COMMENT 'rotation end timestamp',
  `interval` INTEGER UNSIGNED NOT NULL DEFAULT 0 COMMENT 'seconds between rotation',
  `enabled` INTEGER UNSIGNED NOT NULL DEFAULT 0 COMMENT 'not used',
  `tlastsent` INTEGER UNSIGNED NOT NULL DEFAULT 0 COMMENT 'timestamp of last actual broadcast by server',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
