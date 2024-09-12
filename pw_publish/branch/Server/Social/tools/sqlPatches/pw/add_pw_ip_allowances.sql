DROP TABLE IF EXISTS `tbl_ip_allowances`;
CREATE TABLE  `tbl_ip_allowances` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ip` varchar(32) NOT NULL COMMENT 'allowed ips',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_ip` (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
