use pw_stat;

drop procedure if exists ApplyPatch190314;

delimiter $$

create procedure ApplyPatch190314()
patch:begin
  declare schema_table int default 0;
  declare schema_version int default 0;
  declare currency_field int default 0;

  -- Check version table existence
  select count(*) into schema_table from `information_schema`.`TABLES` where `TABLE_SCHEMA` = 'pw_stat' and `TABLE_NAME` = 'schema_version';
  if schema_table = 0 then
    select "ERROR: No schema version. Discarding patch." as `log`;
    leave patch;
  end if;
  
  -- Check schema version
  select `version` into schema_version from `schema_version` where `schema` = 'pw_stat' limit 1;
  if schema_version != 4 then
    select "ERROR: Wrong schema version. Discarding patch." as `log`;
    leave patch;
  end if;
  
  -- Apply patch
  drop table if exists `tbl_seasonevent_progresses`;
  create table `tbl_seasonevent_progresses` (
    `id` bigint unsigned not null auto_increment,
    `auid` int unsigned not null default 0,
    `event_id` int unsigned not null default 0,
    `progress` int unsigned not null default 0,
    primary key(`id`),
    key `index_auid` (`auid`),
    key `index_event` (`event_id`),
    key `index_progress` (`progress`)
    ) engine=MyISAM default charset=utf8;

  -- Update progress
  update `schema_version` set `version` = 5 where `schema` = 'pw_stat';
  select "INFO: Schema version updated to '5'." as `log`;
end$$

-- create procedures to tbl_seasonevent_progresses
-- insert/update data procedure
DROP PROCEDURE IF EXISTS `pw_stat`.`add_seasonevent_progress`$$
CREATE PROCEDURE `pw_stat`.`add_seasonevent_progress`(auid bigint, event_id bigint, progress bigint)
BEGIN

IF EXISTS(SELECT * FROM `tbl_seasonevent_progresses` WHERE `tbl_seasonevent_progresses`.`auid`=auid AND `tbl_seasonevent_progresses`.`event_id`=event_id) THEN
   UPDATE `tbl_seasonevent_progresses` SET `tbl_seasonevent_progresses`.`progress`=progress WHERE `tbl_seasonevent_progresses`.`auid`=auid AND `tbl_seasonevent_progresses`.`event_id`=event_id;
ELSE
   INSERT INTO `tbl_seasonevent_progresses` (`tbl_seasonevent_progresses`.`auid`, `tbl_seasonevent_progresses`.`event_id`, `tbl_seasonevent_progresses`.`progress`) VALUES (auid, event_id, progress);
END IF;
    
END$$

DROP PROCEDURE IF EXISTS `pw_stat`.`get_seasonevent_place`$$
CREATE PROCEDURE `pw_stat`.`get_seasonevent_place`(aauid int, eevent_id int, llimit int)
BEGIN

set @curRow = 0; 
select place, progress from (SELECT auid, @curRow := @curRow + 1 AS place, progress from (SELECT auid, progress
                    FROM pw_stat.tbl_seasonevent_progresses 
                    where `event_id` = eevent_id
                    order by progress desc 
                    limit llimit) as x) as q where `auid` = aauid;
    
END$$

delimiter ;

call ApplyPatch190314();

drop procedure ApplyPatch190314;

