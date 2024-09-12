DROP TABLE IF EXISTS `tbl_pwconnect`;
CREATE TABLE `tbl_pwconnect` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `email` varchar(64) NOT NULL COMMENT 'email address (unique)',
  `email_md5` varchar(32) NOT NULL COMMENT 'md5(email) hex digest',
  `pwc_snuid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'pwc snuid (given by social server)',
  `pwd_md5` varchar(32) DEFAULT NULL COMMENT 'md5(password) hex digest',
  `gender` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'account gender',
  `birthdate` int(10) NOT NULL DEFAULT '0' COMMENT 'birthdate timestamp',
  `ip` varchar(15) DEFAULT NULL COMMENT 'registration IP',
  `ts_create` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'account creation timestamp',
  `auid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `confirm` varchar(32) DEFAULT NULL COMMENT 'random hex digest',
  `ts_confirm` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'timestamp of last confirm token email sent',
  `active` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'activation state',
  `ts_active` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'activation timestamp',
  `ts_resend` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'last resend_confirm timestamp',
  `ts_reset_pwd` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'last reset pwd request timestamp',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_email` (`email`),
  UNIQUE KEY `Index_email_md5` (`email_md5`),
  UNIQUE KEY `Index_pwc_snuid` (`pwc_snuid`)
) 
ENGINE = MyISAM;
