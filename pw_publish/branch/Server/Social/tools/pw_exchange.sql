set sql_mode="NO_AUTO_CREATE_USER";
DROP DATABASE IF EXISTS `se1`;
CREATE database `se1` character set utf8 collate utf8_general_ci;

-- DELETE USER IF EXIST workaround
-- http://stackoverflow.com/questions/598190/mysql-check-if-the-user-exists-and-drop-it
-- http://bugs.mysql.com/bug.php?id=7000
GRANT USAGE ON *.* TO se@localhost identified BY "x";
DROP user se@localhost;

CREATE USER se@localhost;
GRANT ALL ON se1.* TO se@localhost identified BY "sedata";

USE se1;

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
  `name` varchar(8) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_name` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `tbl_message`;
CREATE TABLE  `tbl_message` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `uid` bigint(20) unsigned NOT NULL COMMENT 'user uid in tbl_login',
  `to` varchar(24) NOT NULL COMMENT 'recipient project:auid',
  `expire` int(10) unsigned NOT NULL COMMENT 'expiration timestamp (unixtime)',
  `type` varchar(16) NOT NULL COMMENT 'message type',
  `msg` varchar(16384) DEFAULT NULL COMMENT 'message body (JSON)',
  PRIMARY KEY (`id`),
  KEY `Index_uid` (`uid`),
  KEY `Index_to` (`to`),
  KEY `Index_expire` (`expire`)
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

