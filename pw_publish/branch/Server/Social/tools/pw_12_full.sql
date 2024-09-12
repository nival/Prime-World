set sql_mode="NO_AUTO_CREATE_USER";
DROP DATABASE IF EXISTS `pw1`;
CREATE database pw1 character set utf8 collate utf8_general_ci;

DROP DATABASE IF EXISTS `pw2`;
CREATE database pw2 character set utf8 collate utf8_general_ci;

-- DELETE USER IF EXIST workaround
-- http://stackoverflow.com/questions/598190/mysql-check-if-the-user-exists-and-drop-it
-- http://bugs.mysql.com/bug.php?id=7000
GRANT USAGE ON *.* TO pw@localhost identified BY "x";
DROP user pw@localhost;

CREATE USER pw@localhost;
GRANT ALL ON pw1.* TO pw@localhost identified BY "pwdata";
GRANT ALL ON pw2.* TO pw@localhost identified BY "pwdata";
GRANT ALL ON pw1.* TO pw@195.128.95.36 identified BY "pwdata";
GRANT ALL ON pw2.* TO pw@195.128.95.36 identified BY "pwdata";

USE pw1;

DROP TABLE IF EXISTS `tbl_brick`;
CREATE TABLE  `tbl_brick` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `key` varchar(32) NOT NULL,
  `data` text,
  `stamp` bigint(20) DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_key` (`key`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `tbl_log`;
CREATE TABLE  `tbl_log` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `server_id` bigint(20) NOT NULL DEFAULT '0',
  `time` int(10) unsigned NOT NULL DEFAULT '0',
  `msg` varchar(45) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_login`;
CREATE TABLE  `tbl_login` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(40) NOT NULL,
  `pwd_md5` varchar(32) DEFAULT NULL,
  `server_id` bigint(20) NOT NULL DEFAULT '0',
  `admin` smallint(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_login` (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_servers`;
CREATE TABLE  `tbl_servers` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_name` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_nick`;
CREATE TABLE  `tbl_nick` (
  `id` bigint(20) unsigned NOT NULL,
  `nick` varchar(40) NOT NULL COMMENT 'The real limit for nick length is 32, as in `sp_nick_add` and in the castle client',
  PRIMARY KEY (`id`),
  KEY `Index_nick` (`nick`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_broadcast`;
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
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_user_restrictions`;
CREATE TABLE  `tbl_user_restrictions` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(32) NOT NULL COMMENT 'social requisites, "<snid>:<snuid>" form',
  `timestamp` int(10) DEFAULT 0 COMMENT 'creation unixtime',
  `key` varchar(32) COMMENT 'access key used for creation',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_login` (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_ip_allowances`;
CREATE TABLE  `tbl_ip_allowances` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `ip` varchar(32) NOT NULL COMMENT 'allowed ips',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_ip` (`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_admin_messages`;
CREATE TABLE  `tbl_admin_messages` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(32) NOT NULL COMMENT 'social requisites, "<snid>#<snuid>" form',
  `instance_id` int(10) unsigned NOT NULL COMMENT 'message id in ModelData Keeper',
  `title` VARCHAR(128) COMMENT 'message title',
  `message` VARCHAR(2048) NOT NULL COMMENT 'message text',
  `gmlogin` varchar(32) NOT NULL COMMENT 'gmAccount that added this message',
  `timestamp` int(10) DEFAULT 0 COMMENT 'creation unixtime',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_login`$$
CREATE PROCEDURE  `sp_login`( alogin VARCHAR(40), aserver_id BIGINT )
BEGIN
  # old server_id must be 0 or "dead server", not present in active tbl_servers list
  # new aserver_id must be present in active tbl_servers list
  UPDATE tbl_login
  SET server_id = aserver_id
    WHERE login = alogin
      AND ( server_id = 0
            OR NOT EXISTS (SELECT id FROM tbl_servers WHERE id = server_id)
      )
      AND EXISTS (SELECT id FROM tbl_servers WHERE id = aserver_id)
      ;

  SELECT id, login, pwd_md5 AS pwd, server_id AS ws, `admin`
    FROM tbl_login
      WHERE login = alogin;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_logout`$$
CREATE PROCEDURE  `sp_logout`( alogin VARCHAR(40), aserver_id BIGINT )
BEGIN
  UPDATE tbl_login
  SET server_id = 0
    WHERE login = alogin
      AND server_id = aserver_id;

  SELECT id, login, server_id AS ws
    FROM tbl_login
      WHERE login = alogin;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_load_data`$$
CREATE PROCEDURE `sp_load_data`( aData_key VARCHAR(32), aStamp BIGINT )
BEGIN
  UPDATE tbl_brick
    SET `stamp` = aStamp
    WHERE `key` = aData_key
      AND (@d := `data`) IS NOT NULL;

  SELECT @d as `data`;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_save_data`$$
CREATE PROCEDURE `sp_save_data`( aData_key VARCHAR(32), aStamp BIGINT, aData TEXT )
BEGIN
  DECLARE dataId BIGINT DEFAULT 0;
  DECLARE dataStamp BIGINT DEFAULT 0;

  SELECT `id`,`stamp` INTO dataId, dataStamp FROM tbl_brick WHERE `key` = aData_key;

  IF dataId != 0 THEN
    IF dataStamp = aStamp THEN
      # key exists, stamp ok
      UPDATE tbl_brick SET `data` = aData
        WHERE id = dataId;
      SELECT 1 as ok;

    ELSE
      # bad stamp
       SELECT 0 as ok;
    END IF;

  ELSE
    # no such key: insert new row
    INSERT INTO tbl_brick (`key`,`stamp`,`data`) VALUES (aData_key, aStamp, aData);
    SELECT LAST_INSERT_ID() as ok;
  END IF;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_nick_add` $$
CREATE PROCEDURE `sp_nick_add`( anick VARCHAR(32), aid BIGINT )
BEGIN
  DECLARE dataId BIGINT DEFAULT 0;

  # is there such nick in table?
  SELECT `id` INTO dataId FROM tbl_nick WHERE `nick` = anick;

  IF dataId != 0 THEN
    IF dataId = aid THEN
      # same nick, same id: allow
      SELECT dataId as idok;
    ELSE
      # same nick, different id: fail
      SELECT 0 as idok;
    END IF;

  ELSE
    # no such nick
    INSERT INTO tbl_nick (`id`,`nick`) VALUES (aid, anick)
      ON DUPLICATE KEY UPDATE nick=anick;
    SELECT aid as idok;
  END IF;
END $$

DELIMITER ;

USE pw2;

DROP TABLE IF EXISTS `tbl_brick`;
CREATE TABLE  `tbl_brick` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `key` varchar(32) NOT NULL,
  `data` text,
  `stamp` bigint(20) DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_key` (`key`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;


DROP TABLE IF EXISTS `tbl_log`;
CREATE TABLE  `tbl_log` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `server_id` bigint(20) NOT NULL DEFAULT '0',
  `time` int(10) unsigned NOT NULL DEFAULT '0',
  `msg` varchar(45) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_login`;
CREATE TABLE  `tbl_login` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(40) NOT NULL,
  `pwd_md5` varchar(32) DEFAULT NULL,
  `server_id` bigint(20) NOT NULL DEFAULT '0',
  `admin` smallint(5) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_login` (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_servers`;
CREATE TABLE  `tbl_servers` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_name` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_nick`;
CREATE TABLE  `tbl_nick` (
  `id` bigint(20) unsigned NOT NULL,
  `nick` varchar(40) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `Index_nick` (`nick`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_broadcast`;
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
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_user_restrictions`;
CREATE TABLE  `tbl_user_restrictions` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(32) NOT NULL COMMENT 'social requisites, "<snid>:<snuid>" form',
  `timestamp` int(10) DEFAULT 0 COMMENT 'creation unixtime',
  `key` varchar(32) COMMENT 'access key used for creation',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_login` (`login`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_admin_messages`;
CREATE TABLE  `tbl_admin_messages` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `login` varchar(32) NOT NULL COMMENT 'social requisites, "<snid>#<snuid>" form',
  `instance_id` int(10) unsigned NOT NULL COMMENT 'message id in ModelData Keeper',
  `title` VARCHAR(128) COMMENT 'message title',
  `message` VARCHAR(2048) NOT NULL COMMENT 'message text',
  `gmlogin` varchar(32) NOT NULL COMMENT 'gmAccount that added this message',
  `timestamp` int(10) DEFAULT 0 COMMENT 'creation unixtime',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_login`$$
CREATE PROCEDURE  `sp_login`( alogin VARCHAR(40), aserver_id BIGINT )
BEGIN
  # old server_id must be 0 or "dead server", not present in active tbl_servers list
  # new aserver_id must be present in active tbl_servers list
  UPDATE tbl_login
  SET server_id = aserver_id
    WHERE login = alogin
      AND ( server_id = 0
            OR NOT EXISTS (SELECT id FROM tbl_servers WHERE id = server_id)
      )
      AND EXISTS (SELECT id FROM tbl_servers WHERE id = aserver_id)
      ;

  SELECT id, login, pwd_md5 AS pwd, server_id AS ws, `admin`
    FROM tbl_login
      WHERE login = alogin;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_logout`$$
CREATE PROCEDURE  `sp_logout`( alogin VARCHAR(40), aserver_id BIGINT )
BEGIN
  UPDATE tbl_login
  SET server_id = 0
    WHERE login = alogin
      AND server_id = aserver_id;

  SELECT id, login, server_id AS ws
    FROM tbl_login
      WHERE login = alogin;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_load_data`$$
CREATE PROCEDURE `sp_load_data`( aData_key VARCHAR(32), aStamp BIGINT )
BEGIN
  UPDATE tbl_brick
    SET `stamp` = aStamp
    WHERE `key` = aData_key
      AND (@d := `data`) IS NOT NULL;

  SELECT @d as `data`;
END $$

DELIMITER ;

DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_save_data`$$
CREATE PROCEDURE `sp_save_data`( aData_key VARCHAR(32), aStamp BIGINT, aData TEXT )
BEGIN
  DECLARE dataId BIGINT DEFAULT 0;
  DECLARE dataStamp BIGINT DEFAULT 0;

  SELECT `id`,`stamp` INTO dataId, dataStamp FROM tbl_brick WHERE `key` = aData_key;

  IF dataId != 0 THEN
    IF dataStamp = aStamp THEN
      # key exists, stamp ok
      UPDATE tbl_brick SET `data` = aData
        WHERE id = dataId;
      SELECT 1 as ok;

    ELSE
      # bad stamp
       SELECT 0 as ok;
    END IF;

  ELSE
    # no such key: insert new row
    INSERT INTO tbl_brick (`key`,`stamp`,`data`) VALUES (aData_key, aStamp, aData);
    SELECT LAST_INSERT_ID() as ok;
  END IF;
END $$

DELIMITER ;


DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_nick_add` $$
CREATE PROCEDURE `sp_nick_add`( anick VARCHAR(32), aid BIGINT )
BEGIN
  DECLARE dataId BIGINT DEFAULT 0;

  # is there such nick in table?
  SELECT `id` INTO dataId FROM tbl_nick WHERE `nick` = anick;

  IF dataId != 0 THEN
    IF dataId = aid THEN
      # same nick, same id: allow
      SELECT dataId as idok;
    ELSE
      # same nick, different id: fail
      SELECT 0 as idok;
    END IF;

  ELSE
    # no such nick
    INSERT INTO tbl_nick (`id`,`nick`) VALUES (aid, anick)
      ON DUPLICATE KEY UPDATE nick=anick;
    SELECT aid as idok;
  END IF;
END $$

DELIMITER ;



