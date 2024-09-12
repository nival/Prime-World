ALTER TABLE `pw_stat`.`tbl_seasons_league` ADD `season` BIGINT(20) NOT NULL DEFAULT '1929947588';
ALTER TABLE `pw_stat`.`tbl_seasons_league` ADD INDEX (`season`);
 
DELIMITER $$

DROP PROCEDURE IF EXISTS `pw_stat`.`update_league_info`$$
CREATE PROCEDURE `pw_stat`.`update_league_info`( auid bigint, ahero_id bigint, arating float, anickname varchar(32), aseason bigint )
BEGIN
  DECLARE dataId BIGINT DEFAULT 0;

  SELECT `id` INTO dataId FROM tbl_seasons_league WHERE uid = auid AND hero_id = ahero_id AND season = aseason;

  DROP temporary table IF EXISTS temp_table_cur_places;
  create temporary table temp_table_cur_places SELECT  l.id, @curRow := @curRow + 1 AS league_place
  FROM    tbl_seasons_league l
  JOIN    (SELECT @curRow := 0) r
  WHERE hero_id = ahero_id AND season = aseason
  ORDER BY rating DESC;

  IF dataId != 0 THEN
    UPDATE tbl_seasons_league
    SET rating = arating, nickname = anickname, season = aseason
    WHERE id = dataId;
    SELECT LAST_INSERT_ID() as ok;
  ELSE
    INSERT INTO tbl_seasons_league (`uid`, `hero_id`, `rating`, `nickname`, `prev_league_place`, `season`) VALUES (auid, ahero_id, arating, anickname, -1, aseason);
    SELECT LAST_INSERT_ID() as ok;
  END IF;

  DROP temporary table IF EXISTS temp_table_new_places;
  create temporary table temp_table_new_places SELECT  l.id, @curRow := @curRow + 1 AS league_place
  FROM    tbl_seasons_league l
  JOIN    (SELECT @curRow := 0) r
  WHERE hero_id = ahero_id and season = aseason
  ORDER BY rating DESC;

  UPDATE tbl_seasons_league dest, (select * from temp_table_cur_places) last_rating, (select * from temp_table_new_places) new_rating
  SET dest.prev_league_place = last_rating.league_place WHERE dest.id = last_rating.id AND last_rating.league_place <> new_rating.league_place AND dest.season = aseason;

  DROP temporary table temp_table_new_places;
  DROP temporary table temp_table_cur_places;

END $$

DELIMITER ;