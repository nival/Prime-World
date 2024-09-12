use pw_stat;

drop procedure if exists ApplyPatch180327;

delimiter $$

create procedure ApplyPatch180327()
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
  if schema_version != 2 then
    select "ERROR: Wrong schema version. Discarding patch." as `log`;
    leave patch;
  end if;
  
  -- Apply patch
  select count(*) into currency_field from `information_schema`.`COLUMNS`
      where `TABLE_SCHEMA` = 'pw_stat' 
      and `TABLE_NAME` = 'tbl_user_profile'
      and `COLUMN_NAME` = 'currency';
  if currency_field = 0 then
    alter table `tbl_user_profile`
        add column `currency` varchar(255) not null default '' after `resource3`;
    select "INFO: Added `currency` column to `tbl_user_profile`." as `log`;
  else
    alter table `tbl_user_profile`
        alter column `currency` set default '';
    select "INFO: Set default value for `currency` column in `tbl_user_profile`." as `log`;
  end if;

  -- Update version
  update `schema_version` set `version` = 3 where `schema` = 'pw_stat';
  select "INFO: Schema version updated to '3'." as `log`;
end$$

delimiter ;

call ApplyPatch180327();

drop procedure ApplyPatch180327;

/* Code for HARD revert
use `pw_stat`;
alter table `tbl_user_profile` drop column `currency`;
update `schema_version` set `version` = 2 where `schema` = 'pw_stat';
*/

/* Code for SOFT revert
use `pw_stat`;
alter table `tbl_user_profile` alter column `currency` drop default;
update `schema_version` set `version` = 2 where `schema` = 'pw_stat';
*/