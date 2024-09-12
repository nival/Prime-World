-- 1. создаем таблицу для хранения ауидов
-- формат имени таблицы - temp.{название таска}_actionstream_{диапазон выборки данные (только дни)}_{названиевкладки}_auids
-- вообще этого можно не придерживаться, я лишь описал как называл эти таблицы сам

CREATE TABLE temp.pf89663_actionstream_2908_survey_auids ( auid bigint );

-- 1а. загружаем в эту таблицу список ауидов из выданного эксельника
-- (для каждой вкладки должна быть своя таблица)


-- 2. пересоздание таблицы для данных
-- название таблицы такое же как в п1 только без суффикса _auids

DROP TABLE IF EXISTS temp.pf89663_actionstream_2908_survey;
CREATE TABLE temp.pf89663_actionstream_2908_survey
(
  "timestamp" timestamp not null,
  playerid bigint,
  action varchar not null,
  result varchar,
  id BIGINT
);


-- 3. собираем информацию о логинах
-- проставить нужные даты в datehierarchy

INSERT INTO temp.pf89663_actionstream_2908_survey
SELECT starttime, player, 'login', null, id
FROM socialsession
WHERE player IN (SELECT auid FROM temp.pf89663_actionstream_2908_survey_auids)
  AND datehierarchy BETWEEN 20140529 and 20140608;


-- 4. собираем сессии
-- проставить даты в datehierarchy и starttime (3 места итого)

INSERT INTO temp.pf89663_actionstream_2908_survey
SELECT gs.starttime, pc.player,
       CASE WHEN gs.sessiontype = 4
              THEN (CASE WHEN gs.map = 'Maps/Multiplayer/MOBA/_.ADMPDSCR.xdb' THEN 'pvp'
                         WHEN gs.map = 'Maps/Multiplayer/CTE/PVP.ADMPDSCR.xdb' THEN 'dragonwald'
                         WHEN gs.map = 'Maps/Multiplayer/MidOnly/_.ADMPDSCR.xdb' THEN 'outpost'
                         WHEN gs.map = 'Maps/Multiplayer/MOBA/Mod1/_.ADMPDSCR.xdb' THEN 'native_earth'
                         WHEN gs.map = 'Maps/Multiplayer/MOBA/Mod2/_.ADMPDSCR.xdb' THEN 'zombieland'
                         WHEN gs.map = 'Maps/Multiplayer/MOBA/Mod3/_.ADMPDSCR.xdb' THEN 'shuffle'
                         ELSE gs.map END)
            WHEN gs.sessiontype = 5 THEN 'training'
            WHEN gs.sessiontype = 6 THEN 'tutorial'
            WHEN gs.sessiontype = 7 THEN 'pve_single'
            WHEN gs.sessiontype = 8 THEN 'pve_coop'
            WHEN gs.sessiontype = 9 THEN 'custom'
            WHEN gs.sessiontype = 10 THEN 'custom_bots'
            ELSE 'WTF sessiontype='||gs.sessiontype 
       END,
       CASE WHEN gs.sidewon = -1 THEN 'failed'
            WHEN not leaver AND gs.sidewon = stp.faction THEN 'won' 
            WHEN not leaver AND gs.sidewon != stp.faction THEN 'lose'
            WHEN leaver AND EXISTS 
              ( select 1 from event_disconnect e
                where e.sessiontoplayerid = stp.id and e.location = stp.location
                  and e.reason in (8,11) and datehierarchy between 20140529 and 20140608) THEN 'ileave'
            WHEN leaver THEN 'leave'
            ELSE 'WTF' END,
       gs.id
FROM gamesession gs
  JOIN sessiontoplayer stp ON stp.gamesession = gs.id and stp.location = gs.location
  JOIN playercharacter pc ON pc.id = stp.playercharacter and pc.location = stp.location
  JOIN temp.pf89663_actionstream_2908_survey_auids t on t.auid = pc.player
WHERE gs.timehierarchyid between 20140529 and 20140608
  AND gs.starttime between '2014-05-29' and '2014-06-08 23:59:59'
order by 2,1;



-- 5. Статистика по другим шагам
-- пока не используем, но оставляем, авось пригодится.


/*
  RAISE NOTICE 'resource...';
  -- получение ресурсов
  INSERT INTO actionstream
  SELECT timestamp, player, 'resource',
         CASE WHEN gain THEN 'income' ELSE 'expence' END params,
         max(id)
  FROM resourcelog
  WHERE player IN (SELECT auid FROM tmp_reg_players)
    AND datehierarchy >= 20130501 --startdh
    AND source != 'session'
  GROUP BY timestamp, player, params;

  RAISE NOTICE 'mmaking start...';
  -- старт матчмейкинга
  INSERT INTO actionstream
  SELECT timestamp, pc.player, 'mm_start', null, mp.id
  FROM mmakingplayer mp
    JOIN playercharacter pc on pc.id = mp.playercharacter AND pc.location = mp.location 
  WHERE pc.player IN (SELECT auid FROM tmp_reg_players)
    AND mp.datehierarchy >= 20130401 --startdh
  ORDER BY mp.id;

  RAISE NOTICE 'mmaking end...';
  -- конец матчмейкинга
  INSERT INTO actionstream
  SELECT mp.timestamp, pc.player, 'mm_end',
         CASE WHEN mp.mmakingsession IS NULL THEN 2 -- не дождался
              WHEN ms.status = 1 THEN 0             -- всё ок
              ELSE 1                                -- сессия развалилась
         END,
         mp.id
  FROM mmakingplayer mp
    JOIN playercharacter pc on pc.id = mp.playercharacter AND pc.location = mp.location
    LEFT JOIN mmakingsession ms on ms.id = mp.mmakingsession
  WHERE pc.player IN (SELECT auid FROM tmp_reg_players)
    AND mp.datehierarchy >= 20130401
    AND ms.datehierarchy >= 20130401
  ORDER BY mp.id;
*/

/*
select extract(epoch from timestamp), playerid, action, params from tmp_actionstream_85482 order by 1
*/
