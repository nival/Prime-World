DROP TABLE IF EXISTS `tbl_nick`;
CREATE TABLE  `tbl_nick` (
  `id` bigint(20) unsigned NOT NULL,
  `nick` varchar(40) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `Index_nick` (`nick`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

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

