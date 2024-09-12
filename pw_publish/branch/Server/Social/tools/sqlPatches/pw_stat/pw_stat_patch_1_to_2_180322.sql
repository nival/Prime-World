use pw_stat;

drop procedure if exists ApplyPatch180322;

delimiter $$

create procedure ApplyPatch180322()
patch:begin
  declare schema_table int default 0;
  declare schema_version int default 0;

  -- Check version table existence
  select count(*) into schema_table from `information_schema`.`TABLES` where `TABLE_SCHEMA` = 'pw_stat' and `TABLE_NAME` = 'schema_version';
  if schema_table = 0 then
    create table `schema_version` (
      `schema` varchar(16) not null,
      `version` int not null default 0,
      primary key (`schema`)) engine=MyISAM default charset=utf8;
    insert into `schema_version` values("pw_stat", 1);
  end if;
  
  -- Check schema version
  select `version` into schema_version from `schema_version` where `schema` = 'pw_stat' limit 1;
  if schema_version != 1 then
    select "WARNING: Wrong schema version. Discarding patch." as `log`;
    leave patch;
  end if;
  
  -- Apply patch
  alter table `tbl_guild_rating`
    add column `prev_rating` float not null default 0.0 after `rating`,
    add column `prev_place` int not null default 0 after `prev_rating`,
    add column `current_event_id` bigint not null default 0,
    alter column `date` set default '1000-01-01';
  select "INFO: Added `prev_rating`, `prev_place` and `current_event_id` columns to `tbl_guild_rating`." as `log`;
  
  create table `tbl_guild_rating_history` (
    `id` bigint unsigned not null auto_increment,
    `guild_id` bigint unsigned not null default 0,
    `event_id` bigint unsigned not null default 0,
    `rating` float not null default 0.0,
    primary key(`id`),
    key `index_guild` (`guild_id`),
    key `index_event` (`event_id`),
    key `index_rating` (`rating`)
    ) engine=MyISAM default charset=utf8;
  select "INFO: Created `tbl_guild_rating_history` table." as `log`;

  -- Update version
  update `schema_version` set `version` = 2 where `schema` = 'pw_stat';
  select "INFO: Schema version updated to '2'." as `log`;
end$$

delimiter ;

call ApplyPatch180322();

drop procedure ApplyPatch180322;

/* Code for HARD revert
use `pw_stat`;
DROP TABLE IF EXISTS `tbl_guild_rating`;
CREATE TABLE `tbl_guild_rating` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `guild_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `rating` float NOT NULL DEFAULT '0',
  `guild_name` varchar(64) NOT NULL,
  `guild_short_name` varchar(8) NOT NULL,
  `fraction` smallint(6) NOT NULL DEFAULT '0',
  `num_members` smallint(6) NOT NULL DEFAULT '0',
  `max_members` smallint(6) NOT NULL DEFAULT '0',
  `timestamp` int(10) unsigned NOT NULL DEFAULT '0',
  `date` date NOT NULL DEFAULT '2000-01-01',
  `guild_exp` bigint(20) NOT NULL DEFAULT '0',
  `guild_level` int(11) NOT NULL DEFAULT '0' COMMENT 'level(guild_exp)',
  `level_percent` float NOT NULL DEFAULT '0' COMMENT 'percentage of exp between current and next guild_level',
  `position` int(11) NOT NULL DEFAULT '0' COMMENT 'current rating pos',
  `position_change` int(11) NOT NULL DEFAULT '0' COMMENT 'rating delta between today and yesterday',
  `max_position` int(11) NOT NULL DEFAULT '0' COMMENT 'maximum rating pos (all time)',
  `icon_revision` int(11) NOT NULL DEFAULT '0' COMMENT 'guild emblem revision',
  `lead_auid` bigint(20) unsigned NOT NULL DEFAULT '0',
  `shop_level` int(4) unsigned NOT NULL DEFAULT '0',
  `suzerain` bigint(20) NOT NULL DEFAULT '0',
  `suzerain_name` varchar(64) NOT NULL,
  `suzerain_short_name` varchar(8) NOT NULL,
  `suzerain_rating` float unsigned NOT NULL DEFAULT '0',
  `is_locked` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'bool',
  `siege_end_time` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `Index_guild_date` (`guild_id`,`date`),
  KEY `Index_guild_id` (`guild_id`),
  KEY `Index_rating` (`rating`),
  KEY `Index_lead` (`lead_auid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

drop table if exists `tbl_guild_rating_history`;
drop table if exists `schema_version`;
*/

/* Code for SOFT revert
use `pw_stat`;
alter table `tbl_guild_rating` drop column `prev_rating`, drop column `prev_place`, drop column `current_event_id`;
drop table if exists `tbl_guild_rating_history`;
update `schema_version` set `version` = 1 where `schema` = 'pw_stat';
*/