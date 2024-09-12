create or replace function incremental()
 returns void as
$MAIN$
declare
  ver integer;
begin
  raise notice 'updating database % ...', current_database();
  
  -- check for clean db without dbversion()
  if not exists 
    (select 1 from pg_proc where proname = 'dbversion')
  then
    create function dbversion()
      returns integer as 'begin return 0; end;'
      language plpgsql;
  end if;

  select dbversion() into ver;
  raise notice 'start version = %', ver;

  if ver = 0
  then
    GRANT ALL ON TABLE assist TO dbadminlogs;
    GRANT SELECT ON TABLE assist TO ro;
    GRANT SELECT, INSERT ON TABLE assist TO rw;

    GRANT ALL ON TABLE buildingdestroyed TO dbadminlogs;
    GRANT SELECT ON TABLE buildingdestroyed TO ro;
    GRANT SELECT, INSERT ON TABLE buildingdestroyed TO rw;

    GRANT ALL ON TABLE consumablebought TO dbadminlogs;
    GRANT SELECT ON TABLE consumablebought TO ro;
    GRANT SELECT, INSERT ON TABLE consumablebought TO rw;

    GRANT ALL ON TABLE consumableused TO dbadminlogs;
    GRANT SELECT ON TABLE consumableused TO ro;
    GRANT SELECT, INSERT ON TABLE consumableused TO rw;

    GRANT ALL ON TABLE death TO dbadminlogs;
    GRANT SELECT ON TABLE death TO ro;
    GRANT SELECT, INSERT ON TABLE death TO rw;

    GRANT ALL ON TABLE deed TO dbadminlogs;
    GRANT SELECT ON TABLE deed TO ro;
    GRANT SELECT, INSERT ON TABLE deed TO rw;

    GRANT ALL ON TABLE flag TO dbadminlogs;
    GRANT SELECT ON TABLE flag TO ro;
    GRANT SELECT, INSERT ON TABLE flag TO rw;

    GRANT ALL ON TABLE impulsivebuffused TO dbadminlogs;
    GRANT SELECT ON TABLE impulsivebuffused TO ro;
    GRANT SELECT, INSERT ON TABLE impulsivebuffused TO rw;

    GRANT ALL ON TABLE kill TO dbadminlogs;
    GRANT SELECT ON TABLE kill TO ro;
    GRANT SELECT, INSERT ON TABLE kill TO rw;

    GRANT ALL ON TABLE levelup TO dbadminlogs;
    GRANT SELECT ON TABLE levelup TO ro;
    GRANT SELECT, INSERT ON TABLE levelup TO rw;

    GRANT ALL ON TABLE levelup TO dbadminlogs;
    GRANT SELECT ON TABLE levelup TO ro;
    GRANT SELECT, INSERT ON TABLE levelup TO rw;

    GRANT ALL ON TABLE ressurection TO dbadminlogs;
    GRANT SELECT ON TABLE ressurection TO ro;
    GRANT SELECT, INSERT ON TABLE ressurection TO rw;

    GRANT ALL ON TABLE talentunlocked TO dbadminlogs;
    GRANT SELECT ON TABLE talentunlocked TO ro;
    GRANT SELECT, INSERT ON TABLE talentunlocked TO rw;

    GRANT ALL ON TABLE talentused TO dbadminlogs;
    GRANT SELECT ON TABLE talentused TO ro;
    GRANT SELECT, INSERT ON TABLE talentused TO rw;

    GRANT ALL ON TABLE timeslice TO dbadminlogs;
    GRANT SELECT ON TABLE timeslice TO ro;
    GRANT SELECT, INSERT ON TABLE timeslice TO rw;

    GRANT ALL ON TABLE mg2started TO dbadminlogs;
    GRANT SELECT ON TABLE mg2started TO ro;
    GRANT SELECT, INSERT ON TABLE mg2started TO rw;

    GRANT ALL ON TABLE mg2exit TO dbadminlogs;
    GRANT SELECT ON TABLE mg2exit TO ro;
    GRANT SELECT, INSERT ON TABLE mg2exit TO rw;

    GRANT ALL ON TABLE mg2levelstarted TO dbadminlogs;
    GRANT SELECT ON TABLE mg2levelstarted TO ro;
    GRANT SELECT, INSERT ON TABLE mg2levelstarted TO rw;

    GRANT ALL ON TABLE mg2levelwon TO dbadminlogs;
    GRANT SELECT ON TABLE mg2levelwon TO ro;
    GRANT SELECT, INSERT ON TABLE mg2levelwon TO rw;

    GRANT ALL ON TABLE mg2levelfailed TO dbadminlogs;
    GRANT SELECT ON TABLE mg2levelfailed TO ro;
    GRANT SELECT, INSERT ON TABLE mg2levelfailed TO rw;

    GRANT ALL ON TABLE mg2ballschanged TO dbadminlogs;
    GRANT SELECT ON TABLE mg2ballschanged TO ro;
    GRANT SELECT, INSERT ON TABLE mg2ballschanged TO rw;

    GRANT ALL ON TABLE mg2boostused TO dbadminlogs;
    GRANT SELECT ON TABLE mg2boostused TO ro;
    GRANT SELECT, INSERT ON TABLE mg2boostused TO rw;

    GRANT ALL ON TABLE mg2zzboostused TO dbadminlogs;
    GRANT SELECT ON TABLE mg2zzboostused TO ro;
    GRANT SELECT, INSERT ON TABLE mg2zzboostused TO rw;

    -- same shit with sequences    
    
    GRANT ALL ON TABLE assist_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE assist_id_seq TO ro;
    GRANT ALL ON TABLE assist_id_seq TO rw;

    GRANT ALL ON TABLE buildingdestroyed_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE buildingdestroyed_id_seq TO ro;
    GRANT ALL ON TABLE buildingdestroyed_id_seq TO rw;

    GRANT ALL ON TABLE consumablebought_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE consumablebought_id_seq TO ro;
    GRANT ALL ON TABLE consumablebought_id_seq TO rw;

    GRANT ALL ON TABLE consumableused_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE consumableused_id_seq TO ro;
    GRANT ALL ON TABLE consumableused_id_seq TO rw;

    GRANT ALL ON TABLE death_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE death_id_seq TO ro;
    GRANT ALL ON TABLE death_id_seq TO rw;

    GRANT ALL ON TABLE deed_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE deed_id_seq TO ro;
    GRANT ALL ON TABLE deed_id_seq TO rw;

    GRANT ALL ON TABLE flag_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE flag_id_seq TO ro;
    GRANT ALL ON TABLE flag_id_seq TO rw;

    GRANT ALL ON TABLE impulsivebuffused_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE impulsivebuffused_id_seq TO ro;
    GRANT ALL ON TABLE impulsivebuffused_id_seq TO rw;

    GRANT ALL ON TABLE kill_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE kill_id_seq TO ro;
    GRANT ALL ON TABLE kill_id_seq TO rw;

    GRANT ALL ON TABLE levelup_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE levelup_id_seq TO ro;
    GRANT ALL ON TABLE levelup_id_seq TO rw;

    GRANT ALL ON TABLE mg2ballschanged_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE mg2ballschanged_id_seq TO ro;
    GRANT ALL ON TABLE mg2ballschanged_id_seq TO rw;

    GRANT ALL ON TABLE mg2boostused_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE mg2boostused_id_seq TO ro;
    GRANT ALL ON TABLE mg2boostused_id_seq TO rw;

    GRANT ALL ON TABLE mg2exit_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE mg2exit_id_seq TO ro;
    GRANT ALL ON TABLE mg2exit_id_seq TO rw;

    GRANT ALL ON TABLE mg2levelfailed_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE mg2levelfailed_id_seq TO ro;
    GRANT ALL ON TABLE mg2levelfailed_id_seq TO rw;

    GRANT ALL ON TABLE mg2levelstarted_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE mg2levelstarted_id_seq TO ro;
    GRANT ALL ON TABLE mg2levelstarted_id_seq TO rw;

    GRANT ALL ON TABLE mg2levelwon_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE mg2levelwon_id_seq TO ro;
    GRANT ALL ON TABLE mg2levelwon_id_seq TO rw;

    GRANT ALL ON TABLE mg2started_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE mg2started_id_seq TO ro;
    GRANT ALL ON TABLE mg2started_id_seq TO rw;

    GRANT ALL ON TABLE mg2zzboostused_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE mg2zzboostused_id_seq TO ro;
    GRANT ALL ON TABLE mg2zzboostused_id_seq TO rw;

    GRANT ALL ON TABLE naftagained_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE naftagained_id_seq TO ro;
    GRANT ALL ON TABLE naftagained_id_seq TO rw;

    GRANT ALL ON TABLE ressurection_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE ressurection_id_seq TO ro;
    GRANT ALL ON TABLE ressurection_id_seq TO rw;

    GRANT ALL ON TABLE talentunlocked_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE talentunlocked_id_seq TO ro;
    GRANT ALL ON TABLE talentunlocked_id_seq TO rw;

    GRANT ALL ON TABLE talentused_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE talentused_id_seq TO ro;
    GRANT ALL ON TABLE talentused_id_seq TO rw;

    GRANT ALL ON TABLE timeslice_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE timeslice_id_seq TO ro;
    GRANT ALL ON TABLE timeslice_id_seq TO rw;
    
    select increment_version_to(1) into ver;
  end if;
  
  if ver = 1
  then
    CREATE TABLE naftaincome
    (
      id bigserial NOT NULL, sessionid integer NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, "login" character varying(255) NOT NULL,
      
      incomefrom integer,
      naftaForKill integer,
      naftaSpecForKill integer,
      teamNaftaForKill integer,
      nafta integer,
      CONSTRAINT naftaincome_pkey PRIMARY KEY (id)
    );
    ALTER TABLE naftaincome OWNER TO dbadminlogs;
    GRANT ALL ON TABLE naftaincome TO dbadminlogs;
    GRANT SELECT ON TABLE naftaincome TO ro;
    GRANT SELECT, INSERT ON TABLE naftaincome TO rw;

    GRANT ALL ON TABLE naftaincome_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE naftaincome_id_seq TO ro;
    GRANT ALL ON TABLE naftaincome_id_seq TO rw;
    
    select increment_version_to(2) into ver;
  end if;

  if ver = 2
  then
    ALTER TABLE timeslice ALTER COLUMN currentnafta DROP NOT NULL;
    ALTER TABLE timeslice ADD COLUMN salarynafta integer;
    
    select increment_version_to(3) into ver;
  end if;
  
  if ver = 3
  then
    CREATE TABLE damage
    (
      id bigserial NOT NULL,
      sessionid integer NOT NULL,
      step integer NOT NULL,
      "login" character varying(255) NOT NULL,
      dealt boolean,
      opponentId integer,
      unitType integer,
      talentId integer,
      physicalDamage real,
      magicalDamage real,
      pureDamage real,

      CONSTRAINT damage_pkey PRIMARY KEY (id)
    );
    ALTER TABLE damage OWNER TO dbadminlogs;
    GRANT ALL ON TABLE damage TO dbadminlogs;
    GRANT SELECT ON TABLE damage TO ro;
    GRANT SELECT, INSERT ON TABLE damage TO rw;

    GRANT ALL ON TABLE damage_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE damage_id_seq TO ro;
    GRANT ALL ON TABLE damage_id_seq TO rw;

    select increment_version_to(4) into ver;
  end if;
  
  if ver = 4
  then
    CREATE TABLE debugvar
    (
      id bigserial NOT NULL,
      sessionid integer NOT NULL,
      step integer NOT NULL,
      login character varying(255) NOT NULL,
      name character varying(255) NOT NULL,
      value character varying(255) NOT NULL,

      CONSTRAINT debugvar_pkey PRIMARY KEY (id)
    );
    ALTER TABLE debugvar OWNER TO dbadminlogs;
    GRANT ALL ON TABLE debugvar TO dbadminlogs;
    GRANT SELECT ON TABLE debugvar TO ro;
    GRANT SELECT, INSERT ON TABLE debugvar TO rw;

    GRANT ALL ON TABLE debugvar_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE debugvar_id_seq TO ro;
    GRANT ALL ON TABLE debugvar_id_seq TO rw;

    select increment_version_to(5) into ver;
  end if;
  
  if ver = 5
  then
    alter table buildingdestroyed add column buildingid integer;
    alter table buildingdestroyed alter column faction drop not null;
    alter table buildingdestroyed alter column route drop not null;
    alter table buildingdestroyed alter column routelevel drop not null;

    select increment_version_to(6) into ver;
  end if;

  if ver = 6
  then
    CREATE TABLE impulsivebuffsuggested
    (
      id bigserial NOT NULL, sessionid integer NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, "login" character varying(255) NOT NULL,
      
      impulsivebuffid integer NOT NULL,
      CONSTRAINT impulsivebuffsuggested_pkey PRIMARY KEY (id)
    );
    ALTER TABLE impulsivebuffsuggested OWNER TO dbadminlogs;
    GRANT ALL ON TABLE impulsivebuffsuggested TO dbadminlogs;
    GRANT SELECT ON TABLE impulsivebuffsuggested TO ro;
    GRANT SELECT, INSERT ON TABLE impulsivebuffsuggested TO rw;

    GRANT ALL ON TABLE impulsivebuffsuggested_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE impulsivebuffsuggested_id_seq TO ro;
    GRANT ALL ON TABLE impulsivebuffsuggested_id_seq TO rw;

    select increment_version_to(7) into ver;
  end if;

  if ver = 7
  then
    -- Buildings/A/Tower/Top
    update buildingdestroyed set buildingid = -1844987402 where faction = 1 and route = 0 and routelevel = 0; 
    update buildingdestroyed set buildingid = -1843034277 where faction = 1 and route = 0 and routelevel = 1;
    update buildingdestroyed set buildingid = -1841081152 where faction = 1 and route = 0 and routelevel = 2;
    -- Buildings/A/Tower/Center
    update buildingdestroyed set buildingid = 545136608 where faction = 1 and route = 1 and routelevel = 0;
    update buildingdestroyed set buildingid = 547089733 where faction = 1 and route = 1 and routelevel = 1;
    update buildingdestroyed set buildingid = 549042858 where faction = 1 and route = 1 and routelevel = 2;
    -- Buildings/A/Tower/Bottom
    update buildingdestroyed set buildingid = 171680944 where faction = 1 and route = 2 and routelevel = 0;
    update buildingdestroyed set buildingid = 173634069 where faction = 1 and route = 2 and routelevel = 1;
    update buildingdestroyed set buildingid = 175587194 where faction = 1 and route = 2 and routelevel = 2;
    -- Buildings/A/Barrack
    update buildingdestroyed set buildingid = 1421238854 where faction = 1 and route = 0 and routelevel = 3;
    update buildingdestroyed set buildingid = 49684408 where faction = 1 and route = 1 and routelevel = 3;
    update buildingdestroyed set buildingid = -884000184 where faction = 1 and route = 2 and routelevel = 3;
    -- Buildings/B/Tower/Top
    update buildingdestroyed set buildingid = 132812839 where faction = 2 and route = 0 and routelevel = 0;
    update buildingdestroyed set buildingid = 134765964 where faction = 2 and route = 0 and routelevel = 1;
    update buildingdestroyed set buildingid = 136719089 where faction = 2 and route = 0 and routelevel = 2;
    -- Buildings/B/Tower/Center
    update buildingdestroyed set buildingid = -1337936435 where faction = 2 and route = 1 and routelevel = 0;
    update buildingdestroyed set buildingid = -1335983310 where faction = 2 and route = 1 and routelevel = 1;
    update buildingdestroyed set buildingid = -1334030185 where faction = 2 and route = 1 and routelevel = 2;
    -- Buildings/B/Tower/Bottom
    update buildingdestroyed set buildingid = -1711392099 where faction = 2 and route = 2 and routelevel = 0;
    update buildingdestroyed set buildingid = -1709438974 where faction = 2 and route = 2 and routelevel = 1;
    update buildingdestroyed set buildingid = -1707485849 where faction = 2 and route = 2 and routelevel = 2;
    -- Buildings/B/Barrack
    update buildingdestroyed set buildingid = -673362673 where faction = 2 and route = 0 and routelevel = 3;
    update buildingdestroyed set buildingid = 217498589 where faction = 2 and route = 1 and routelevel = 3;
    update buildingdestroyed set buildingid = -716186003 where faction = 2 and route = 2 and routelevel = 3;
    
    alter table buildingdestroyed drop column faction;
    alter table buildingdestroyed drop column route;
    alter table buildingdestroyed drop column routelevel;
  
    select increment_version_to(8) into ver;
  end if;

  if ver = 8
  then
    alter table assist add column killerlogin character varying(255);
    alter table assist add column killercreatureid integer;
    
    select increment_version_to(9) into ver;
  end if;

  if ver = 9
  then
    CREATE TABLE talentswitchedoff
    (
      id bigserial NOT NULL, sessionid integer NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, "login" character varying(255) NOT NULL,
      
      talentid integer NOT NULL,
      CONSTRAINT talentswitchedoff_pkey PRIMARY KEY (id)
    );
    ALTER TABLE talentswitchedoff OWNER TO dbadminlogs;
    GRANT ALL ON TABLE talentswitchedoff TO dbadminlogs;
    GRANT SELECT ON TABLE talentswitchedoff TO ro;
    GRANT SELECT, INSERT ON TABLE talentswitchedoff TO rw;

    GRANT ALL ON TABLE talentswitchedoff_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE talentswitchedoff_id_seq TO ro;
    GRANT ALL ON TABLE talentswitchedoff_id_seq TO rw;

    select increment_version_to(10) into ver;
  end if;

  if ver = 10
  then
    ALTER TABLE sys_droppeddata RENAME sessionid  TO session_id;
    ALTER TABLE sys_droppeddata ADD COLUMN username character varying(255);
    
    DROP FUNCTION drop_everything(integer);
    CREATE FUNCTION drop_everything(
        sessionid integer,
        win_username character varying (255)
    ) RETURNS integer AS
    $$
    DECLARE
       cnt integer;
       totalcnt integer := 0;
       tab character varying(255);
       dat record;
    BEGIN
       for tab in
         select relname
         from pg_stat_user_tables
         where relname != 'sys_droppeddata'
         order by relname
       loop
       begin
         cnt := 0;
         for dat in
           execute 'select * from ' || tab ||
           ' where sessionid = $1' using sessionid
         loop
           insert into sys_droppeddata (operation_date, username, "session_id", "login", table_name, record_id)
           values (now(), win_username, dat.sessionid, dat.login, tab, dat.id);
           execute 'delete from ' || tab || ' where id = $1' using dat.id;
           cnt := cnt + 1;
         end loop;
         raise notice 'deleted % records from table %', cnt, tab;
         totalcnt := totalcnt + cnt;
       exception
         when syntax_error then
           raise notice 'processing error in table %', tab;
           continue;
       end;
       end loop;
       return totalcnt;
    END;
    $$ LANGUAGE plpgsql;

    select increment_version_to(11) into ver;
  end if;

  if ver = 11
  then
    CREATE TABLE cheatused
    (
      id bigserial NOT NULL, sessionid integer NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, "login" character varying(255) NOT NULL,
      
      command character varying(255),
      CONSTRAINT cheatused_pkey PRIMARY KEY (id)
    );
    ALTER TABLE cheatused OWNER TO dbadminlogs;
    GRANT ALL ON TABLE cheatused TO dbadminlogs;
    GRANT SELECT ON TABLE cheatused TO ro;
    GRANT SELECT, INSERT ON TABLE cheatused TO rw;

    GRANT ALL ON TABLE cheatused_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE cheatused_id_seq TO ro;
    GRANT ALL ON TABLE cheatused_id_seq TO rw;

    select increment_version_to(12) into ver;
  end if;

  if ver = 12
  then
    alter table debugvar add column eventtime timestamp without time zone;
    
    select increment_version_to(13) into ver;
  end if;

  if ver = 13
  then
    CREATE TABLE mg2zzboostsuggested
    (
      id bigserial NOT NULL, sessionid integer NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, "login" character varying(255) NOT NULL,
      
      CONSTRAINT mg2zzboostsuggested_pkey PRIMARY KEY (id)
    );
    ALTER TABLE mg2zzboostsuggested OWNER TO dbadminlogs;
    GRANT ALL ON TABLE mg2zzboostsuggested TO dbadminlogs;
    GRANT SELECT ON TABLE mg2zzboostsuggested TO ro;
    GRANT SELECT, INSERT ON TABLE mg2zzboostsuggested TO rw;

    GRANT ALL ON TABLE mg2zzboostsuggested_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE mg2zzboostsuggested_id_seq TO ro;
    GRANT ALL ON TABLE mg2zzboostsuggested_id_seq TO rw;
        
    select increment_version_to(14) into ver;
  end if;

  if ver = 14
  then
    ALTER TABLE deed RENAME TO achievement;
    ALTER TABLE achievement RENAME COLUMN deedid TO achievementid;
    ALTER TABLE deed_id_seq RENAME TO achievement_id_seq;

    select increment_version_to(15) into ver;
  end if;

  if ver = 15
  then
    -- new version incrementation process
    select increment_version_to(16) into ver;
  end if;
  
  if ver = 16
  then
    alter table achievement drop column "login";
    alter table assist drop column "login";
    alter table buildingdestroyed drop column "login";
    alter table consumablebought drop column "login";
    alter table consumableused drop column "login";
    alter table cheatused drop column "login";
    alter table damage drop column "login";
    alter table death drop column "login";
    alter table debugvar drop column "login";
    alter table flag drop column "login";
    alter table impulsivebuffused drop column "login";
    alter table impulsivebuffsuggested drop column "login";
    alter table kill drop column "login";
    alter table levelup drop column "login";
    alter table naftaincome drop column "login";
    alter table ressurection drop column "login";
    alter table talentunlocked drop column "login";
    alter table talentused drop column "login";
    alter table talentswitchedoff drop column "login";
    alter table timeslice drop column "login";
    alter table mg2started drop column "login";
    alter table mg2exit drop column "login";
    alter table mg2levelstarted drop column "login";
    alter table mg2levelwon drop column "login";
    alter table mg2levelfailed drop column "login";
    alter table mg2ballschanged drop column "login";
    alter table mg2boostused drop column "login";
    alter table mg2zzboostused drop column "login";
    alter table mg2zzboostsuggested drop column "login";

    alter table achievement add column playerid bigint NOT NULL default 0;
    alter table assist add column playerid bigint NOT NULL default 0;
    alter table buildingdestroyed add column playerid bigint NOT NULL default 0;
    alter table consumablebought add column playerid bigint NOT NULL default 0;
    alter table consumableused add column playerid bigint NOT NULL default 0;
    alter table cheatused add column playerid bigint NOT NULL default 0;
    alter table damage add column playerid bigint NOT NULL default 0;
    alter table death add column playerid bigint NOT NULL default 0;
    alter table debugvar add column playerid bigint NOT NULL default 0;
    alter table flag add column playerid bigint NOT NULL default 0;
    alter table impulsivebuffused add column playerid bigint NOT NULL default 0;
    alter table impulsivebuffsuggested add column playerid bigint NOT NULL default 0;
    alter table kill add column playerid bigint NOT NULL default 0;
    alter table levelup add column playerid bigint NOT NULL default 0;
    alter table naftaincome add column playerid bigint NOT NULL default 0;
    alter table ressurection add column playerid bigint NOT NULL default 0;
    alter table talentunlocked add column playerid bigint NOT NULL default 0;
    alter table talentused add column playerid bigint NOT NULL default 0;
    alter table talentswitchedoff add column playerid bigint NOT NULL default 0;
    alter table timeslice add column playerid bigint NOT NULL default 0;
    alter table mg2started add column playerid bigint NOT NULL default 0;
    alter table mg2exit add column playerid bigint NOT NULL default 0;
    alter table mg2levelstarted add column playerid bigint NOT NULL default 0;
    alter table mg2levelwon add column playerid bigint NOT NULL default 0;
    alter table mg2levelfailed add column playerid bigint NOT NULL default 0;
    alter table mg2ballschanged add column playerid bigint NOT NULL default 0;
    alter table mg2boostused add column playerid bigint NOT NULL default 0;
    alter table mg2zzboostused add column playerid bigint NOT NULL default 0;
    alter table mg2zzboostsuggested add column playerid bigint NOT NULL default 0;

    alter table assist drop column victimlogin; 
    alter table assist drop column killerlogin;
    alter table buildingdestroyed drop column destroyerlogin;
    alter table death drop column killerlogin; 
    alter table flag drop column activatorlogin;
    alter table kill drop column victimlogin;
    
    alter table assist add column victimid bigint NOT NULL default 0;
    alter table assist add column killerid bigint;
    alter table buildingdestroyed add column destroyerid bigint;
    alter table death add column killerid bigint;
    alter table flag add column activatorid bigint;
    alter table kill add column victimid bigint;
    
    select increment_version_to(17) into ver;
  end if;

  if ver = 17
  then
    CREATE TABLE exceedingsteptime
    (
      id bigserial NOT NULL,
      sessionid integer NOT NULL,
      playerid bigint NOT NULL,
      starttime timestamp without time zone,
      finishtime timestamp without time zone,
      stepcount integer,
      steptimemin integer,
      steptimemax integer,
      steptimeavg integer,
      worldrequest boolean,
      
      CONSTRAINT exceedingsteptime_pkey PRIMARY KEY (id)
    );
    ALTER TABLE exceedingsteptime OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE exceedingsteptime TO ro;
    GRANT SELECT, INSERT ON TABLE exceedingsteptime TO rw;

    GRANT ALL ON TABLE exceedingsteptime_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE exceedingsteptime_id_seq TO ro;
    GRANT ALL ON TABLE exceedingsteptime_id_seq TO rw;
        
    select increment_version_to(18) into ver;
  end if;

  if ver = 18
  then
    alter table exceedingsteptime drop column worldrequest;
    alter table exceedingsteptime add column worldrequeststep integer;
    alter table exceedingsteptime add column typeid integer;

    select increment_version_to(19) into ver;
  end if;

  if ver = 19
  then
    alter table exceedingsteptime add column startstep integer;
    alter table exceedingsteptime add column finishstep integer;

    select increment_version_to(20) into ver;
  end if;

  if ver = 20
  then
    CREATE TABLE sys_checks_scope
    (
      tablename character varying NOT NULL,
      lastchecked bigint,
      CONSTRAINT sys_checks_scope_pkey PRIMARY KEY (tablename)
    );
    ALTER TABLE sys_checks_scope OWNER TO dbadminlogs;
    GRANT ALL ON sys_checks_scope TO ro;
    GRANT ALL ON sys_checks_scope TO rw;

    select increment_version_to(21) into ver;
  end if;

  if ver = 21
  then
    DELETE FROM sys_checks_scope WHERE lastchecked IS NULL; 
    ALTER TABLE sys_checks_scope ALTER COLUMN lastchecked SET NOT NULL;
  
    CREATE TABLE sys_archive_info
    (
      tablename character varying NOT NULL,
      lastarchived bigint,
      CONSTRAINT sys_archive_info_pkey PRIMARY KEY (tablename)
    );
    ALTER TABLE sys_archive_info OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE sys_archive_info TO ro;
    GRANT SELECT ON TABLE sys_archive_info TO rw;

    CREATE TABLE sys_archive_current
    (
      tablename character varying,
      minid bigint,
      maxid bigint,
      minsessionid integer,
      maxsessionid integer,
      starttime timestamp without time zone
    );
    ALTER TABLE sys_archive_current OWNER TO dbadminlogs;
    
    -- Function: create_archive()

    CREATE OR REPLACE FUNCTION create_archive()
      RETURNS character varying AS
    $$
    declare
      c record;
      min_id integer;
      min_session_id integer;
      max_session_id integer;
      tmp integer;
      start_time timestamp;
    begin
      -- re-creating schema 'archive'
      if exists(select * from pg_namespace   where nspname = 'archive') then
        drop schema archive cascade;
      end if;
      create schema archive authorization dbadminlogs;

      -- clear current archive info
      truncate table sys_archive_current;
        
      -- get sessions range and archiving every table
      for c in select * from sys_checks_scope
      loop
        select lastarchived into min_id
        from sys_archive_info
        where tablename = c.tablename;
        if not found then 
          execute 'select min(id) from '||c.tablename 
          into min_id;
        end if;

        -- set start time
        start_time := now();

        execute 'select sessionid from '||c.tablename||' where id = '||min_id        into min_session_id;
        execute 'select sessionid from '||c.tablename||' where id = '||c.lastchecked into max_session_id;
        
        raise notice '% archiving table % [%,%]', localtime, c.tablename, min_id, c.lastchecked;
        
        execute 'create table archive.'||c.tablename||' as '||
                'select * from '||c.tablename||' where id > '||min_id||' and  id <= '||c.lastchecked;

        insert into sys_archive_current 
        values (c.tablename, min_id, c.lastchecked, min_session_id, max_session_id, start_time);
        
      end loop;

      if not exists (select * from sys_archive_current) then raise 'No data has been archived'; end if;
      select min(starttime) into start_time from sys_archive_current;
      select min(minsessionid) into min_session_id from sys_archive_current;
      select max(maxsessionid) into max_session_id from sys_archive_current;
      
      return to_char(start_time, 'YYMMDD-HH24MI')||'-sessions('||min_session_id||'-'||max_session_id||')';
      
    end;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION create_archive() OWNER TO dbadminlogs;

    -- Function: commit_archive()

    CREATE OR REPLACE FUNCTION commit_archive()
      RETURNS void AS
    $$
    declare
      a record;
    begin
      for a in select * from sys_archive_current
      loop
        if exists (select * from sys_archive_info where tablename = a.tablename) then
          update sys_archive_info set lastarchived = a.maxid where tablename = a.tablename;
        else
          insert into sys_archive_info values (a.tablename, a.maxid);
        end if;
        raise notice 'set lastarchived for table % = %', a.tablename, a.maxid;
      end loop;
      
      if exists(select * from pg_namespace   where nspname = 'archive') then
        drop schema archive cascade;
        truncate sys_archive_current;
      end if;
    end;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION commit_archive() OWNER TO dbadminlogs;

    -- Function: delete_archive()

    CREATE OR REPLACE FUNCTION delete_archive()
      RETURNS void AS
    $$
    declare
      a record;
    begin
      for a in select * from sys_archive_info
      loop
        raise notice 'delete from % where id <= %', a.tablename, a.lastarchived;
        execute 'delete from '||a.tablename||' where id <= '||a.lastarchived;
      end loop;
    end;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION delete_archive() OWNER TO dbadminlogs;

    select increment_version_to(22) into ver;
  end if;

  if ver = 22
  then
    CREATE TABLE disconnect
    (
      id bigserial NOT NULL,
      sessionid integer NOT NULL,
      playerid bigint NOT NULL,
      reason integer,
      "timestamp" timestamp without time zone,
      
      CONSTRAINT disconnect_pkey PRIMARY KEY (id)
    );
    ALTER TABLE disconnect OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE disconnect TO ro;
    GRANT SELECT, INSERT ON TABLE disconnect TO rw;

    GRANT ALL ON TABLE disconnect_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE disconnect_id_seq TO ro;
    GRANT ALL ON TABLE disconnect_id_seq TO rw;

    select increment_version_to(23) into ver;
  end if;

  if ver = 23
  then

    -- Table: launcherstart

    CREATE TABLE launcherstart
    (
      id bigserial NOT NULL,
      hostid character varying,
      version character varying,
      "timestamp" timestamp without time zone,
      CONSTRAINT launcherstart_pkey PRIMARY KEY (id)
    );
    ALTER TABLE launcherstart OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE launcherstart TO ro;
    GRANT SELECT, INSERT ON TABLE launcherstart TO rw;
    ALTER TABLE launcherstart_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE launcherstart_id_seq TO ro;
    GRANT ALL ON TABLE launcherstart_id_seq TO rw;

    -- Table: launcherdstart

    CREATE TABLE launcherdstart
    (
      id bigserial NOT NULL,
      hostid character varying,
      package character varying,
      version character varying,
      "timestamp" timestamp without time zone,
      CONSTRAINT launcherdstart_pkey PRIMARY KEY (id)
    );
    ALTER TABLE launcherdstart OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE launcherdstart TO ro;
    GRANT SELECT, INSERT ON TABLE launcherdstart TO rw;
    ALTER TABLE launcherdstart_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE launcherdstart_id_seq TO ro;
    GRANT ALL ON TABLE launcherdstart_id_seq TO rw;

    -- Table: launcherdend

    CREATE TABLE launcherdend
    (
      id bigserial NOT NULL,
      hostid character varying,
      package character varying,
      version character varying,
      status integer NOT NULL,
      "timestamp" timestamp without time zone,
      CONSTRAINT launcherdend_pkey PRIMARY KEY (id)
    );
    ALTER TABLE launcherdend OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE launcherdend TO ro;
    GRANT SELECT, INSERT ON TABLE launcherdend TO rw;
    ALTER TABLE launcherdend_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE launcherdend_id_seq TO ro;
    GRANT ALL ON TABLE launcherdend_id_seq TO rw;

    -- Table: socialregister

    CREATE TABLE socialregister
    (
      id bigserial NOT NULL,
      hostid character varying,
      playerid bigint,
      snid character varying,
      snuid character varying,
      "timestamp" timestamp without time zone,
      CONSTRAINT socialregister_pkey PRIMARY KEY (id)
    );
    ALTER TABLE socialregister OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE socialregister TO ro;
    GRANT SELECT, INSERT ON TABLE socialregister TO rw;
    ALTER TABLE socialregister_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE socialregister_id_seq TO ro;
    GRANT ALL ON TABLE socialregister_id_seq TO rw;

    -- Table: socialjoin

    CREATE TABLE socialjoin
    (
      id bigserial NOT NULL,
      playerid bigint,
      snid character varying,
      snuid character varying,
      "timestamp" timestamp without time zone,
      CONSTRAINT socialjoin_pkey PRIMARY KEY (id)
    );
    ALTER TABLE socialjoin OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE socialjoin TO ro;
    GRANT SELECT, INSERT ON TABLE socialjoin TO rw;
    ALTER TABLE socialjoin_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE socialjoin_id_seq TO ro;
    GRANT ALL ON TABLE socialjoin_id_seq TO rw;

    -- Table: socialmerge

    CREATE TABLE socialmerge
    (
      id bigserial NOT NULL,
      playerid1 bigint,
      playerid2 bigint,
      "timestamp" timestamp without time zone,
      CONSTRAINT socialmerge_pkey PRIMARY KEY (id)
    );
    ALTER TABLE socialmerge OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE socialmerge TO ro;
    GRANT SELECT, INSERT ON TABLE socialmerge TO rw;
    ALTER TABLE socialmerge_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE socialmerge_id_seq TO ro;
    GRANT ALL ON TABLE socialmerge_id_seq TO rw;

    select increment_version_to(24) into ver;
  end if;

  if ver = 24
  then
    if not exists (
      select * from pg_tables
      where tablename = 'exceedingpingtime' )
    then
      CREATE TABLE exceedingpingtime
      (
        id bigserial NOT NULL,
        sessionid integer NOT NULL,
        playerid bigint NOT NULL,
        typeid integer NOT NULL,
        starttime timestamp without time zone,
        finishtime timestamp without time zone,
        pingcount integer,
        pingtimemin integer,
        pingtimemax integer,
        pingtimeavg integer,
        CONSTRAINT exceedingpingtime_pkey PRIMARY KEY (id)
      );
      ALTER TABLE exceedingpingtime OWNER TO dbadminlogs;
      GRANT SELECT ON TABLE exceedingpingtime TO ro;
      GRANT SELECT, INSERT ON TABLE exceedingpingtime TO rw;

      GRANT ALL ON TABLE exceedingpingtime_id_seq TO dbadminlogs;
      GRANT SELECT, USAGE ON TABLE exceedingpingtime_id_seq TO ro;
      GRANT ALL ON TABLE exceedingpingtime_id_seq TO rw;
    end if;

    select increment_version_to(25) into ver;
  end if;

  if ver = 25
  then
    CREATE TABLE cheat
    (
      id bigserial NOT NULL,
      sessionid integer NOT NULL,
      playerid bigint NOT NULL,
      cheattype integer NOT NULL,
      clientip character varying NOT NULL,
      "timestamp" timestamp without time zone NOT NULL,
      CONSTRAINT cheat_pkey PRIMARY KEY (id)
    );
    ALTER TABLE cheat OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE cheat TO ro;
    GRANT SELECT, INSERT ON TABLE cheat TO rw;

    GRANT ALL ON TABLE cheat_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE cheat_id_seq TO ro;
    GRANT ALL ON TABLE cheat_id_seq TO rw;

    select increment_version_to(26) into ver;
  end if;

  if ver = 26
  then
    CREATE TABLE ignoreadd
    (
      id bigserial NOT NULL,
      playerid bigint NOT NULL,
      ignoredplayerid bigint NOT NULL,
      reason character varying,
      "timestamp" timestamp without time zone NOT NULL,
      CONSTRAINT ignoreadd_pkey PRIMARY KEY (id)
    );
    ALTER TABLE ignoreadd OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE ignoreadd TO ro;
    GRANT SELECT, INSERT ON TABLE ignoreadd TO rw;

    GRANT ALL ON TABLE ignoreadd_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE ignoreadd_id_seq TO ro;
    GRANT ALL ON TABLE ignoreadd_id_seq TO rw;

    CREATE TABLE ignoreremove
    (
      id bigserial NOT NULL,
      playerid bigint NOT NULL,
      ignoredplayerid bigint NOT NULL,
      "timestamp" timestamp without time zone NOT NULL,
      CONSTRAINT ignoreremove_pkey PRIMARY KEY (id)
    );
    ALTER TABLE ignoreremove OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE ignoreremove TO ro;
    GRANT SELECT, INSERT ON TABLE ignoreremove TO rw;

    GRANT ALL ON TABLE ignoreremove_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE ignoreremove_id_seq TO ro;
    GRANT ALL ON TABLE ignoreremove_id_seq TO rw;

    select increment_version_to(27) into ver;
  end if;

  if ver = 27
  then
    if not exists (
      select * from pg_attribute a join pg_class p on p.oid = attrelid
      where relname = 'exceedingsteptime' and attname = 'rpcping')
    then
      ALTER TABLE exceedingsteptime ADD COLUMN rpcping integer;
      ALTER TABLE exceedingsteptime ADD COLUMN transportping integer;
    end if;
    
    if not exists (
      select * from pg_attribute a join pg_class p on p.oid = attrelid
      where relname = 'exceedingpingtime' and attname = 'pinglcount')
    then
      ALTER TABLE exceedingpingtime ADD COLUMN pinglcount integer;
      ALTER TABLE exceedingpingtime ADD COLUMN pingltimemin integer;
      ALTER TABLE exceedingpingtime ADD COLUMN pingltimemax integer;
      ALTER TABLE exceedingpingtime ADD COLUMN pingltimeavg integer;
      ALTER TABLE exceedingpingtime ADD COLUMN pinghcount integer;
      ALTER TABLE exceedingpingtime ADD COLUMN pinghtimemin integer;
      ALTER TABLE exceedingpingtime ADD COLUMN pinghtimemax integer;
      ALTER TABLE exceedingpingtime ADD COLUMN pinghtimeavg integer;
    end if;

    select increment_version_to(28) into ver;
  end if;

  if ver = 28
  then
    DROP TABLE mg2zzboostsuggested;
    DROP TABLE mg2zzboostused;

    select increment_version_to(29) into ver;
  end if;

  if ver = 29
  then
    if not exists (
      select * from pg_tables
      where tablename = 'offlineevent' )
    then
      CREATE TABLE offlineevent
      (
        id bigserial NOT NULL,
        playerid bigint NOT NULL,
        persistentid bigint NOT NULL,
        code int NOT NULL,
        auxdata int NOT NULL,
        timestamp timestamp NOT NULL,
        CONSTRAINT offlineevent_pkey PRIMARY KEY (id)
      );
      ALTER TABLE offlineevent OWNER TO dbadminlogs;
      GRANT SELECT ON TABLE offlineevent TO ro;
      GRANT SELECT, INSERT ON TABLE offlineevent TO rw;

      GRANT ALL ON TABLE offlineevent_id_seq TO dbadminlogs;
      GRANT SELECT, USAGE ON TABLE offlineevent_id_seq TO ro;
      GRANT ALL ON TABLE offlineevent_id_seq TO rw;
    end if;
    
    select increment_version_to(30) into ver;
  end if;

  if ver = 30
  then
    if not exists (
      select * from pg_attribute a join pg_class p on p.oid = attrelid
      where relname = 'socialregister' and attname = 'muid')
    then
      ALTER TABLE socialregister ADD COLUMN muid character varying;
    end if;   

    select increment_version_to(31) into ver;
  end if;

  if ver = 31
  then
    if not exists (
      select * from pg_tables
      where tablename = 'launcherevents' )
    then
      CREATE TABLE launcherevents
      (
        id bigserial NOT NULL,
        playerid bigint,
        muid character varying,
        eventflags bigint,
        "timestamp" timestamp without time zone,
        CONSTRAINT launcherevents_pkey PRIMARY KEY (id)
      );
      ALTER TABLE launcherevents OWNER TO dbadminlogs;
      GRANT SELECT ON TABLE launcherevents TO ro;
      GRANT SELECT, INSERT ON TABLE launcherevents TO rw;
      ALTER TABLE launcherevents_id_seq OWNER TO dbadminlogs;
      GRANT SELECT, USAGE ON TABLE launcherevents_id_seq TO ro;
      GRANT ALL ON TABLE launcherevents_id_seq TO rw;
    end if;

    if not exists (
      select * from pg_attribute a join pg_class p on p.oid = attrelid
      where relname in ('launcherstart','launcherdstart','launcherdend') and attname = 'playerid')
    then
      ALTER TABLE launcherstart  ADD COLUMN playerid bigint;
      ALTER TABLE launcherdstart ADD COLUMN playerid bigint;
      ALTER TABLE launcherdend   ADD COLUMN playerid bigint;
    end if;

    select increment_version_to(32) into ver;
  end if;

  if ver = 32
  then
    CREATE SCHEMA etl AUTHORIZATION dbadminlogs;
    GRANT ALL ON SCHEMA etl TO ro;

    select increment_version_to(33) into ver;
  end if;

  if ver = 33
  then
    ALTER TABLE launcherstart ADD COLUMN clientip character varying;
    ALTER TABLE launcherstart ADD COLUMN location character varying;

    select increment_version_to(34) into ver;
  end if;

  if ver = 34
  then
    CREATE TABLE reconnect
    (
      id bigserial NOT NULL,
      sessionid integer NOT NULL,
      playerid bigint NOT NULL,
      step integer NOT NULL,
      type character varying NOT NULL,
      result character varying NOT NULL,
      "timestamp" timestamp without time zone,
      CONSTRAINT reconnect_pkey PRIMARY KEY (id)
    );
    ALTER TABLE reconnect OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE reconnect TO ro;
    GRANT SELECT, INSERT ON TABLE reconnect TO rw;

    GRANT ALL ON TABLE reconnect_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE reconnect_id_seq TO ro;
    GRANT ALL ON TABLE reconnect_id_seq TO rw;

    select increment_version_to(35) into ver;
  end if;

  if ver = 35
  then
    CREATE TABLE launcherdaction
    (
      id bigserial NOT NULL,
      action character varying NOT NULL,
      hostid character varying,
      version character varying,
      muid character varying,
      playerid bigint,
      speed real,
      avgspeed real,
      minspeed real,
      totalpatches integer,
      appliedpatches integer,
      totaldownload real,
      downloaded real,
      error character varying,
      needclose integer,
      geolocation character varying,
      clienttimestamp timestamp,
      servertimestamp timestamp,
      CONSTRAINT launcherdaction_pkey PRIMARY KEY (id)
    );
    ALTER TABLE launcherdaction OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE launcherdaction TO ro;
    GRANT SELECT, INSERT ON TABLE launcherdaction TO rw;
    ALTER TABLE launcherdaction_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE launcherdaction_id_seq TO ro;
    GRANT ALL ON TABLE launcherdaction_id_seq TO rw;

    DROP TABLE launcherdstart;
    DROP TABLE IF EXISTS etl.launcherdstart;
    DROP TABLE launcherdend;
    DROP TABLE IF EXISTS etl.launcherdend;

    select increment_version_to(36) into ver;
  end if;

  if ver = 36
  then
    CREATE TABLE exceedingserversteptime
    (
      id bigserial NOT NULL,
      sessionid integer NOT NULL,
      step integer,
      starttime timestamp without time zone,
      finishtime timestamp without time zone,
      stepcount integer,
      steptimemin integer,
      steptimemax integer,
      steptimeavg integer,
      CONSTRAINT exceedingserversteptime_pkey PRIMARY KEY (id)
    );
    ALTER TABLE exceedingserversteptime OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE exceedingserversteptime TO ro;
    GRANT SELECT, INSERT ON TABLE exceedingserversteptime TO rw;

    GRANT ALL ON TABLE exceedingserversteptime_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE exceedingserversteptime_id_seq TO ro;
    GRANT ALL ON TABLE exceedingserversteptime_id_seq TO rw;

    select increment_version_to(37) into ver;
  end if;

  if ver = 37
  then
    ALTER TABLE launcherevents RENAME timestamp to clienttimestamp;
    ALTER TABLE launcherevents ADD COLUMN servertimestamp timestamp;

    IF EXISTS(select 1 from pg_tables where schemaname = 'etl' and tablename = 'launcherevents') 
    THEN
      ALTER TABLE etl.launcherevents RENAME timestamp to clienttimestamp;
      ALTER TABLE etl.launcherevents ADD COLUMN servertimestamp timestamp;
    END IF;

    select increment_version_to(38) into ver;
  end if;

  if ver = 38
  then
    ALTER TABLE offlineevent ALTER COLUMN auxdata TYPE bigint;

    IF EXISTS(select 1 from pg_tables where schemaname = 'etl' and tablename = 'offlineevent') 
    THEN
      ALTER TABLE etl.offlineevent ALTER COLUMN auxdata TYPE bigint;
    END IF;

    select increment_version_to(39) into ver;
  end if;

  if ver = 39
  then
    CREATE TABLE gstraffic
    (
      id bigserial NOT NULL,
      sessionid integer NOT NULL,
      totalin integer,
      totalout integer,
      avgoutperstep real,
      maxoutperstep integer,
      totalinreconnect integer,
      totaloutreconnect integer,
      avgoutreconnect real,
      maxoutreconnect integer,
      avgcmdpersecond real,
      maxcmdpersecond integer,
      CONSTRAINT gstraffic_pkey PRIMARY KEY (id)
    );
    ALTER TABLE gstraffic OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE gstraffic TO ro;
    GRANT SELECT, INSERT ON TABLE gstraffic TO rw;

    GRANT ALL ON TABLE gstraffic_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE gstraffic_id_seq TO ro;
    GRANT ALL ON TABLE gstraffic_id_seq TO rw;

    select increment_version_to(40) into ver;
  end if;

  if ver = 40
  then
    ALTER TABLE launcherstart RENAME location TO geolocation;
    ALTER TABLE launcherstart ADD COLUMN locale varchar;
    ALTER TABLE launcherdaction ADD COLUMN locale varchar;
    ALTER TABLE launcherevents ADD COLUMN locale varchar;

    select increment_version_to(41) into ver;
  end if;

  if ver = 41
  then
    CREATE TABLE clientping
    (
      id bigserial NOT NULL,
      playerid bigint,
      srvlocation varchar,
      ping integer,
      timestamp timestamp,
      CONSTRAINT clientping_pkey PRIMARY KEY (id)
    );
    ALTER TABLE clientping OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE clientping TO ro;
    GRANT SELECT, INSERT ON TABLE clientping TO rw;
    ALTER TABLE clientping_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE clientping_id_seq TO ro;
    GRANT ALL ON TABLE clientping_id_seq TO rw;

    select increment_version_to(42) into ver;
  end if;

  if ver = 42
  then
    CREATE TABLE scriptevent
    (
      id bigserial NOT NULL,
      sessionid integer NOT NULL,
      step integer NOT NULL,
      playerid bigint NOT NULL,
      strparam1 varchar,
      strparam2 varchar,
      intparam1 integer,
      intparam2 integer,
      intparam3 integer,
      intparam4 integer,
      intparam5 integer,
      CONSTRAINT scriptevent_pkey PRIMARY KEY (id)
    );
    ALTER TABLE scriptevent OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE scriptevent TO ro;
    GRANT SELECT, INSERT ON TABLE scriptevent TO rw;

    GRANT ALL ON TABLE scriptevent_id_seq TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE scriptevent_id_seq TO ro;
    GRANT ALL ON TABLE scriptevent_id_seq TO rw;

    select increment_version_to(43) into ver;
  end if;

  if ver = 43
  then
    ALTER TABLE assist ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE buildingdestroyed ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE consumablebought ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE consumableused ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE cheatused ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE death ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE achievement ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE flag ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE impulsivebuffused ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE impulsivebuffsuggested ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE kill ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE levelup ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE naftaincome ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE ressurection ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE scriptevent ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE talentunlocked ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE talentused ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE talentswitchedoff ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE mg2started ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE mg2exit ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE mg2levelstarted ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE mg2levelwon ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE mg2levelfailed ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE mg2ballschanged ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE mg2boostused ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE damage ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE debugvar ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE exceedingserversteptime ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE exceedingsteptime ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE disconnect ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE reconnect ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE gstraffic ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE cheat ALTER COLUMN sessionid TYPE bigint;
    ALTER TABLE timeslice ALTER COLUMN sessionid TYPE bigint;

    DROP TABLE sys_checks_scope;
    DROP TABLE sys_archive_info;
    DROP TABLE sys_archive_current;
    DROP TABLE sys_droppeddata;

    DROP FUNCTION create_archive();
    DROP FUNCTION commit_archive();
    DROP FUNCTION delete_archive();
    DROP FUNCTION array_to_set(anyarray);
    DROP FUNCTION drop_everything(integer, character varying (255));

    select increment_version_to(44) into ver;
  end if;

  if ver = 44
  then

    CREATE TABLE ratingchange
    (
      id bigserial NOT NULL,
      type integer NOT NULL,
      player bigint NOT NULL,
      persistentid bigint,
      character integer,
      change integer,
      total bigint,
      "timestamp" timestamp NOT NULL,
      CONSTRAINT ratingchange_pkey PRIMARY KEY (id)
    );
    ALTER TABLE ratingchange OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE ratingchange TO ro;
    GRANT SELECT, INSERT ON TABLE ratingchange TO rw;
    ALTER TABLE ratingchange_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE ratingchange_id_seq TO ro;
    GRANT ALL ON TABLE ratingchange_id_seq TO rw;
    PERFORM setval('ratingchange_id_seq', 1000000000);

    CREATE TABLE talentjoinsession
    (
      id bigserial NOT NULL,
      player bigint NOT NULL,
      character bigint NOT NULL,
      persistentid bigint NOT NULL,
      talent integer NOT NULL,
      CONSTRAINT talentjoinsession_pkey PRIMARY KEY (id)
    );
    ALTER TABLE talentjoinsession OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE talentjoinsession TO ro;
    GRANT SELECT, INSERT ON TABLE talentjoinsession TO rw;
    ALTER TABLE talentjoinsession_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE talentjoinsession_id_seq TO ro;
    GRANT ALL ON TABLE talentjoinsession_id_seq TO rw;
    PERFORM setval('talentjoinsession_id_seq', 10000000000);

    select increment_version_to(45) into ver;
  end if;

  if ver = 45
  then

    CREATE TABLE guildbuffsession
    (
      id bigserial NOT NULL,
      type varchar NOT NULL,
      player bigint NOT NULL,
      persistentid bigint NOT NULL,
      guildbuff integer NOT NULL,
      CONSTRAINT guildbuffsession_pkey PRIMARY KEY (id)
    );
    ALTER TABLE guildbuffsession OWNER TO dbadminlogs;
    GRANT SELECT ON TABLE guildbuffsession TO ro;
    GRANT SELECT, INSERT ON TABLE guildbuffsession TO rw;
    ALTER TABLE guildbuffsession_id_seq OWNER TO dbadminlogs;
    GRANT SELECT, USAGE ON TABLE guildbuffsession_id_seq TO ro;
    GRANT ALL ON TABLE guildbuffsession_id_seq TO rw;

    select increment_version_to(46) into ver;
  end if;

  if ver = 46
  then

    
CREATE TABLE shopreroll
(
  id bigserial NOT NULL,
  auid bigint NOT NULL,
  itemId int NOT NULL,
  itemGroup int NOT NULL,
  itemPrice bigint not null,
  itemPriceType character varying,
  rerollCount int,
  slotType character varying,
  timestamp timestamp not null,
    CONSTRAINT shopreroll_pkey PRIMARY KEY (id)
);
ALTER TABLE shopreroll OWNER TO dbadminlogs;
GRANT SELECT ON TABLE shopreroll TO ro;
GRANT SELECT, INSERT ON TABLE shopreroll TO rw;
ALTER TABLE shopreroll_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE shopreroll_id_seq TO ro;
GRANT ALL ON TABLE shopreroll_id_seq TO rw;


    select increment_version_to(47) into ver;
  end if;

  raise notice 'updating % success!', current_database();
end;
$MAIN$
language plpgsql;

select incremental();