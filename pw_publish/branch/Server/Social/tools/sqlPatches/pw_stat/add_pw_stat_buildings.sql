DROP TABLE IF EXISTS `pw_stat`.`tbl_user_build_stats`;
CREATE TABLE  `pw_stat`.`tbl_user_build_stats` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `auid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `build_id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'id in ModelData',
  `build_crc` int(11) NOT NULL DEFAULT '0' COMMENT 'crc32 == PersistentId',
  `build_level` int(11) NOT NULL DEFAULT '0',
  `timestamp` int(11) NOT NULL DEFAULT '0' COMMENT 'unix timestamp',
  `in_pocket` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'bool',
  PRIMARY KEY (`id`),
  KEY `Index_auid` (`auid`),
  KEY `Index_crc` (`build_crc`)
) 
ENGINE = MyISAM DEFAULT CHARSET=utf8;
