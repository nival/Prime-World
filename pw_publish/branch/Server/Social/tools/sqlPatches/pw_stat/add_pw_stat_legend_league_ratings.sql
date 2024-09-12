DROP TABLE IF EXISTS `pw_stat`.`tbl_seasons_league`;
CREATE TABLE `pw_stat`.`tbl_seasons_league` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `uid` bigint(20) NOT NULL COMMENT 'user uid in tbl_login',
  `hero_id` bigint(20) NOT NULL COMMENT 'user uid in tbl_login',
  `rating` float COMMENT 'user rating',
  `nickname` varchar(32) COMMENT 'user nickname',
  `prev_league_place` bigint(20) DEFAULT 0 COMMENT 'last rating value',
  PRIMARY KEY (`id`),
  KEY `Index_uid` (`uid`),
  KEY `Index_hero_id` (`hero_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DELIMITER $$

DROP PROCEDURE IF EXISTS `pw_stat`.`update_league_info`$$
CREATE PROCEDURE `pw_stat`.`update_league_info`( auid bigint, ahero_id bigint, arating float, anickname varchar(32) )
BEGIN
  DECLARE dataId BIGINT DEFAULT 0;

  SELECT `id` INTO dataId FROM tbl_seasons_league WHERE uid = auid AND hero_id = ahero_id;

  DROP temporary table IF EXISTS temp_table_cur_places;
  create temporary table temp_table_cur_places SELECT  l.id, @curRow := @curRow + 1 AS league_place
  FROM    tbl_seasons_league l
  JOIN    (SELECT @curRow := 0) r
  WHERE hero_id = ahero_id
  ORDER BY rating DESC;

  IF dataId != 0 THEN
    UPDATE tbl_seasons_league
    SET rating = arating, nickname = anickname
    WHERE id = dataId;
    SELECT LAST_INSERT_ID() as ok;
  ELSE
    INSERT INTO tbl_seasons_league (`uid`, `hero_id`, `rating`, `nickname`, `prev_league_place`) VALUES (auid, ahero_id, arating, anickname, -1);
    SELECT LAST_INSERT_ID() as ok;
  END IF;

  DROP temporary table IF EXISTS temp_table_new_places;
  create temporary table temp_table_new_places SELECT  l.id, @curRow := @curRow + 1 AS league_place
  FROM    tbl_seasons_league l
  JOIN    (SELECT @curRow := 0) r
  WHERE hero_id = ahero_id
  ORDER BY rating DESC;

  UPDATE tbl_seasons_league dest, (select * from temp_table_cur_places) last_rating, (select * from temp_table_new_places) new_rating
  SET dest.prev_league_place = last_rating.league_place WHERE dest.id = last_rating.id AND last_rating.league_place <> new_rating.league_place;

  DROP temporary table temp_table_new_places;
  DROP temporary table temp_table_cur_places;

END $$

DELIMITER ;