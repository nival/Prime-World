set sql_mode="NO_AUTO_CREATE_USER";
DROP DATABASE IF EXISTS `pw_mirror`;
CREATE database pw_mirror;

-- DELETE USER IF EXIST workaround
-- http://stackoverflow.com/questions/598190/mysql-check-if-the-user-exists-and-drop-it
-- http://bugs.mysql.com/bug.php?id=7000
GRANT USAGE ON *.* TO pwm@localhost identified BY "x";
DROP user pwm@localhost;

CREATE USER pwm@localhost;
GRANT ALL ON pw_mirror.* TO pwm@localhost identified BY "pwmdata";

USE `pw_mirror`;

DROP TABLE IF EXISTS `pw_mirror`.`tbl_queue`;
CREATE TABLE  `pw_mirror`.`tbl_queue` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `data_type` smallint(6) NOT NULL DEFAULT '0' COMMENT 'various data input types (ModelData, GuildData etc)',
  `data_id` bigint(20) NOT NULL DEFAULT '0' COMMENT 'key id for data retrieval (auid, guild_id etc)',
  `handler_id` int(11) NOT NULL DEFAULT '0' COMMENT 'handler daemon id',
  `_status` smallint(6) NOT NULL DEFAULT '0' COMMENT 'new, handled etc.',
  `timestamp` int(11) NOT NULL DEFAULT '0' COMMENT 'unixtime of last operation',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_type_id` (`data_type`,`data_id`),
  KEY `Index_type_handler` (`data_type`,`handler_id`),
  KEY `Index_timestamp` (`timestamp`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_get_requests` $$
CREATE PROCEDURE `sp_get_requests` ( adata_type SMALLINT, arequest_type SMALLINT, aservice_count SMALLINT, acount INTEGER, ahandler_id INTEGER )
BEGIN
	# workaround for "LIMIT const" usage
  SET @v_data_type = adata_type;
  SET @v_request_type = arequest_type;
	SET @v_service_count = aservice_count;
  SET @v_handler_id = ahandler_id;
  SET @v_count = acount;
  SET @v_timestamp = UNIX_TIMESTAMP();
  SET @v_query = 'UPDATE tbl_queue
    SET handler_id = ?,
        _status = 1,
        timestamp = ?
    WHERE data_type = ?
      AND _status = 0 AND MOD(id, ?)= ?
    ORDER BY `id` ASC
    LIMIT ?';
  PREPARE v_query FROM @v_query;
  EXECUTE v_query USING @v_handler_id, @v_timestamp, @v_data_type, @v_service_count, @v_request_type, @v_count;

  SELECT * FROM tbl_queue
    WHERE data_type = adata_type AND MOD(id, aservice_count) = arequest_type AND _status = 1;
END $$

DELIMITER ;
