DROP TABLE IF EXISTS `tbl_user_restrictions`;
CREATE TABLE  `tbl_user_restrictions` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(32) NOT NULL COMMENT 'social requisites, "<snid>:<snuid>" form',
  `timestamp` int(10) DEFAULT 0 COMMENT 'creation unixtime',
  `key` varchar(32) COMMENT 'access key used for creation',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_login` (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
