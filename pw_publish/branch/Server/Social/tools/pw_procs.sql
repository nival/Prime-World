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


