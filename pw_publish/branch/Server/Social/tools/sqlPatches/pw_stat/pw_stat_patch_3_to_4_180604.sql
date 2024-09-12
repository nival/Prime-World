use pw_stat;

drop procedure if exists ApplyPatch180604;

delimiter $$

create procedure ApplyPatch180604()
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
  if schema_version != 3 then
    select "ERROR: Wrong schema version. Discarding patch." as `log`;
    leave patch;
  end if;
  
  -- Apply patch
  drop table if exists `tbl_tradeevent_exps`;
  create table `tbl_tradeevent_exps` (
    `id` bigint unsigned not null auto_increment,
    `auid` int unsigned not null default 0,
    `event_id` int unsigned not null default 0,
    `experience` int unsigned not null default 0,
    primary key(`id`),
    key `index_auid` (`auid`),
    key `index_event` (`event_id`),
    key `index_experience` (`experience`)
    ) engine=MyISAM default charset=utf8;

  -- Update version
  update `schema_version` set `version` = 4 where `schema` = 'pw_stat';
  select "INFO: Schema version updated to '4'." as `log`;
end$$

-- create procedures to tbl_tradeevent_exps
-- insert/update data procedure
DROP PROCEDURE IF EXISTS `pw_stat`.`add_tradeevent_experience`$$
CREATE PROCEDURE `pw_stat`.`add_tradeevent_experience`(auid bigint, event_id bigint, experience bigint)
BEGIN

IF EXISTS(SELECT * FROM `tbl_tradeevent_exps` WHERE `tbl_tradeevent_exps`.`auid`=auid AND `tbl_tradeevent_exps`.`event_id`=event_id) THEN
   UPDATE `tbl_tradeevent_exps` SET `tbl_tradeevent_exps`.`experience`=experience WHERE `tbl_tradeevent_exps`.`auid`=auid AND `tbl_tradeevent_exps`.`event_id`=event_id;
ELSE
   INSERT INTO `tbl_tradeevent_exps` (`tbl_tradeevent_exps`.`auid`, `tbl_tradeevent_exps`.`event_id`, `tbl_tradeevent_exps`.`experience`) VALUES (auid, event_id, experience);
END IF;
    
END$$

DROP PROCEDURE IF EXISTS `pw_stat`.`get_tradeevent_place`$$
CREATE PROCEDURE `pw_stat`.`get_tradeevent_place`(aauid int, eevent_id int, llimit int)
BEGIN

set @curRow = 0; 
select place, experience from (SELECT auid, @curRow := @curRow + 1 AS place, experience from (SELECT auid, experience
                    FROM pw_stat.tbl_tradeevent_exps 
                    where `event_id` = eevent_id
                    order by experience desc 
                    limit llimit) as x) as q where `auid` = aauid;
    
END$$

delimiter ;

call ApplyPatch180604();

drop procedure ApplyPatch180604;

