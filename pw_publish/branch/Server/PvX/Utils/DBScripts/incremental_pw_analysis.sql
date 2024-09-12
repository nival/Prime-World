create or replace function incremental()
 returns void as
$MAIN$
declare
  ver integer;
  tmprow record;
  textarr text[];
  c varchar;
  i1 integer;
  i2 integer;
begin
  raise notice 'updating database % ...', current_database();
  
  -- check for clean db without dbversion()
  if not exists 
    (select 1 from pg_proc where proname = 'dbversion')
  then
    CREATE OR REPLACE FUNCTION dbversion()
      RETURNS integer AS
    $BODY$
    begin
      return 0;
    end;
    $BODY$
      LANGUAGE plpgsql VOLATILE
      COST 100;
    ALTER FUNCTION dbversion() OWNER TO dbadmin;
    GRANT EXECUTE ON FUNCTION dbversion() TO public;
  end if;

  select dbversion() into ver;
  raise notice 'start version = %', ver;
  
  if (ver = 0)
  then
    ALTER TABLE sessiontoplayer ADD COLUMN spring boolean NOT NULL DEFAULT false;
    
    update sessiontoplayer
    set spring = true
    where id in 
    ( select id
      from sessiontoplayer stp2
        join 
        ( select distinct stp.gamesession, stp.side
          from event_impulsivebuffused eib
            join sessiontoplayer stp on stp.id = eib.sessiontoplayerid
          where eib.impulsivebuffid = 1392511285
            and stp.side is not null) sq 
        on sq.gamesession = stp2.gamesession and sq.side = stp2.side);
    
    select increment_version_to(1) into ver;
  end if;

  if ver = 1
  then
    ALTER TABLE sessiontoplayer ADD COLUMN preferfaction character varying(32);
    
    select increment_version_to(2) into ver;
  end if;
  
  if ver = 2
  then
   
    ALTER TABLE "character" OWNER TO dbadmin;
    GRANT SELECT ON TABLE "character" TO ro;
    ALTER TABLE player OWNER TO dbadmin;
    GRANT SELECT ON TABLE player TO ro;
    ALTER TABLE playercharacter OWNER TO dbadmin;
    GRANT SELECT ON TABLE playercharacter TO ro;
    ALTER TABLE impulsivebuff OWNER TO dbadmin;
    GRANT SELECT ON TABLE impulsivebuff TO ro;
    ALTER TABLE mgboost OWNER TO dbadmin;
    GRANT SELECT ON TABLE mgboost TO ro;
    ALTER TABLE talent OWNER TO dbadmin;
    GRANT SELECT ON TABLE talent TO ro;
    ALTER TABLE gamesession OWNER TO dbadmin;
    GRANT SELECT ON TABLE gamesession TO ro;
    ALTER TABLE sessiontoplayer OWNER TO dbadmin;
    GRANT SELECT ON TABLE sessiontoplayer TO ro;
    ALTER TABLE event_talentused OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_talentused TO ro;
    ALTER TABLE event_talentunlocked OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_talentunlocked TO ro;
    ALTER TABLE event_timeslice OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_timeslice TO ro;
    ALTER TABLE event_ressurection OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_ressurection TO ro;
    ALTER TABLE event_levelup OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_levelup TO ro;
    ALTER TABLE event_impulsivebuffused OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_impulsivebuffused TO ro;
    ALTER TABLE event_buildingdestroyed OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_buildingdestroyed TO ro;
    ALTER TABLE event_flag OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_flag TO ro;
    ALTER TABLE event_kill OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_kill TO ro;
    ALTER TABLE event_assist OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_assist TO ro;
    ALTER TABLE event_death OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_death TO ro;
    ALTER TABLE event_mg_session OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_mg_session TO ro;
    ALTER TABLE event_mg_level OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_mg_level TO ro;
    ALTER TABLE event_mg_ballschanged OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_mg_ballschanged TO ro;
    ALTER TABLE event_mg_zzboostused OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_mg_zzboostused TO ro;
    ALTER TABLE event_mg_boostused OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_mg_boostused TO ro;
    ALTER TABLE datehierarchy OWNER TO dbadmin;
    GRANT SELECT ON TABLE datehierarchy TO ro;

    select increment_version_to(3) into ver;
  end if;
  
  if ver = 3
  then
    CREATE TABLE event_naftaincome
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      x real NOT NULL,
      y real NOT NULL,
      characterid integer,

      incomefrom integer NOT NULL,
      naftaforkill integer,
      naftaspecforkill integer,
      teamnaftaforkill integer,
      nafta integer,

      CONSTRAINT event_naftaincome_pkey PRIMARY KEY (id),
      CONSTRAINT event_naftaincome_characterid_fkey FOREIGN KEY (characterid)
          REFERENCES "character" (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_naftaincome_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid)
          REFERENCES sessiontoplayer (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE event_naftaincome OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_naftaincome TO ro;
    
    select increment_version_to(4) into ver;
  end if;
  
  if ver = 4
  then
    ALTER TABLE talent ADD COLUMN cooldown real;
    
    select increment_version_to(5) into ver;
  end if;  
    
  if ver = 5
  then
    CREATE TABLE creature
    (
      id integer NOT NULL,
      "name" character varying(255),
      CONSTRAINT creature_pkey PRIMARY KEY (id)
    );
    ALTER TABLE creature OWNER TO dbadmin;
    GRANT SELECT ON TABLE creature TO ro;

    CREATE TABLE building
    (
      id integer NOT NULL,
      "name" character varying(255),
      description character varying(1023),
      CONSTRAINT building_pkey PRIMARY KEY (id)
    );
    ALTER TABLE building OWNER TO dbadmin;
    GRANT SELECT ON TABLE building TO ro;
    
    select increment_version_to(6) into ver;
  end if;  

  if ver = 6
  then
    ALTER TABLE gamesession ADD COLUMN sessiontype integer NOT NULL DEFAULT 0;

    update gamesession
    set sessiontype = case mmaking when true then 2 else 1 end;

    ALTER TABLE gamesession DROP COLUMN mmaking;

    update gamesession
    set sessiontype = 3
    where id in (
      select gs.id
      from gamesession gs
        join sessiontoplayer stp on stp.gamesession = gs.id
      group by gs.id
      having count(*) = 1 );
    
    select increment_version_to(7) into ver;
  end if;  

  if ver = 7
  then
    ALTER TABLE event_timeslice ALTER COLUMN currentnafta DROP NOT NULL;
    ALTER TABLE event_timeslice ADD COLUMN salarynafta integer;
    
    select increment_version_to(8) into ver;
  end if;  
  
  if ver = 8
  then
    CREATE TABLE unittype
    (
      id integer NOT NULL,
      "name" character varying(256),
      CONSTRAINT unittype_pkey PRIMARY KEY (id)
    );
    ALTER TABLE unittype OWNER TO dbadmin;
    GRANT SELECT ON TABLE unittype TO ro;

    CREATE TABLE event_damage
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      characterid integer,

      dealt boolean,
      opponentid integer,
      unittype integer,
      talentid integer,
      physicaldamage real,
      magicaldamage real,
      puredamage real,

      CONSTRAINT event_damage_pkey PRIMARY KEY (id),
      CONSTRAINT event_damage_characterid_fkey FOREIGN KEY (characterid)
          REFERENCES "character" (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_damage_unittype_fkey FOREIGN KEY (unittype)
          REFERENCES unittype (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE event_damage OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage TO ro;
    
    select increment_version_to(9) into ver;
  end if;
    
  if ver = 9
  then
    CREATE TABLE event_debugvar
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,

      name character varying(255) NOT NULL,
      value character varying(255) NOT NULL,

      CONSTRAINT event_debugvar_pkey PRIMARY KEY (id),
      CONSTRAINT event_death_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid)
          REFERENCES sessiontoplayer (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE event_debugvar OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_debugvar TO ro;
    
    select increment_version_to(10) into ver;
  end if;
  
  if ver = 10
  then
    alter table event_buildingdestroyed add column buildingid integer;
    alter table event_buildingdestroyed add 
      CONSTRAINT event_buildingdestroyed_buildingid_fkey FOREIGN KEY (buildingid) 
      REFERENCES building (id) MATCH SIMPLE ON UPDATE NO ACTION ON DELETE NO ACTION;
    
    select increment_version_to(11) into ver;
  end if;
  
  if ver = 11
  then
    CREATE TABLE event_impulsivebuffsuggested
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      x real NOT NULL,
      y real NOT NULL,
      characterid integer,

      impulsivebuffid integer,

      CONSTRAINT event_impulsivebuffsuggested_pkey PRIMARY KEY (id),
      CONSTRAINT event_impulsivebuffsuggested_characterid_fkey FOREIGN KEY (characterid)
          REFERENCES "character" (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_impulsivebuffsuggested_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid)
          REFERENCES sessiontoplayer (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_impulsivebuffsuggested_impulsivebuffid_fkey FOREIGN KEY (impulsivebuffid)
          REFERENCES impulsivebuff (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE event_impulsivebuffsuggested OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_impulsivebuffsuggested TO ro;

    select increment_version_to(12) into ver;
  end if;

  if ver = 12
  then
    alter table player add column nival boolean not null default false;

    select increment_version_to(13) into ver;
  end if;

  if ver = 13
  then
    -- Buildings/A/Tower/Top
    update event_buildingdestroyed set buildingid = -1844987402 where faction = 1 and route = 0 and routelevel = 0; 
    update event_buildingdestroyed set buildingid = -1843034277 where faction = 1 and route = 0 and routelevel = 1;
    update event_buildingdestroyed set buildingid = -1841081152 where faction = 1 and route = 0 and routelevel = 2;
    -- Buildings/A/Tower/Center
    update event_buildingdestroyed set buildingid = 545136608 where faction = 1 and route = 1 and routelevel = 0;
    update event_buildingdestroyed set buildingid = 547089733 where faction = 1 and route = 1 and routelevel = 1;
    update event_buildingdestroyed set buildingid = 549042858 where faction = 1 and route = 1 and routelevel = 2;
    -- Buildings/A/Tower/Bottom
    update event_buildingdestroyed set buildingid = 171680944 where faction = 1 and route = 2 and routelevel = 0;
    update event_buildingdestroyed set buildingid = 173634069 where faction = 1 and route = 2 and routelevel = 1;
    update event_buildingdestroyed set buildingid = 175587194 where faction = 1 and route = 2 and routelevel = 2;
    -- Buildings/A/Barrack
    update event_buildingdestroyed set buildingid = 1421238854 where faction = 1 and route = 0 and routelevel = 3;
    update event_buildingdestroyed set buildingid = 49684408 where faction = 1 and route = 1 and routelevel = 3;
    update event_buildingdestroyed set buildingid = -884000184 where faction = 1 and route = 2 and routelevel = 3;
    -- Buildings/B/Tower/Top
    update event_buildingdestroyed set buildingid = 132812839 where faction = 2 and route = 0 and routelevel = 0;
    update event_buildingdestroyed set buildingid = 134765964 where faction = 2 and route = 0 and routelevel = 1;
    update event_buildingdestroyed set buildingid = 136719089 where faction = 2 and route = 0 and routelevel = 2;
    -- Buildings/B/Tower/Center
    update event_buildingdestroyed set buildingid = -1337936435 where faction = 2 and route = 1 and routelevel = 0;
    update event_buildingdestroyed set buildingid = -1335983310 where faction = 2 and route = 1 and routelevel = 1;
    update event_buildingdestroyed set buildingid = -1334030185 where faction = 2 and route = 1 and routelevel = 2;
    -- Buildings/B/Tower/Bottom
    update event_buildingdestroyed set buildingid = -1711392099 where faction = 2 and route = 2 and routelevel = 0;
    update event_buildingdestroyed set buildingid = -1709438974 where faction = 2 and route = 2 and routelevel = 1;
    update event_buildingdestroyed set buildingid = -1707485849 where faction = 2 and route = 2 and routelevel = 2;
    -- Buildings/B/Barrack
    update event_buildingdestroyed set buildingid = -673362673 where faction = 2 and route = 0 and routelevel = 3;
    update event_buildingdestroyed set buildingid = 217498589 where faction = 2 and route = 1 and routelevel = 3;
    update event_buildingdestroyed set buildingid = -716186003 where faction = 2 and route = 2 and routelevel = 3;
    
    alter table event_buildingdestroyed drop column faction;
    alter table event_buildingdestroyed drop column route;
    alter table event_buildingdestroyed drop column routelevel;

    select increment_version_to(14) into ver;
  end if;

  if ver = 14
  then
    alter table event_assist add column killerid integer;
    alter table event_assist add column killercreatureid integer;
    
    alter table event_assist add
      CONSTRAINT event_assist_killerid_fkey FOREIGN KEY (killerid)
      REFERENCES "character" (id) MATCH SIMPLE ON UPDATE NO ACTION ON DELETE NO ACTION;
    
    alter table event_assist add
      CONSTRAINT event_assist_killercreatureid_fkey FOREIGN KEY (killercreatureid)
      REFERENCES creature (id) MATCH SIMPLE ON UPDATE NO ACTION ON DELETE NO ACTION;
    
    select increment_version_to(15) into ver;
  end if;
  
  if ver = 15
  then
    CREATE TABLE abilitytype
    (
      id integer NOT NULL,
      "name" character varying(256),
      CONSTRAINT abilitytype_pkey PRIMARY KEY (id)
    );
    ALTER TABLE abilitytype OWNER TO dbadmin;
    GRANT SELECT ON TABLE abilitytype TO ro;

    ALTER TABLE talent ADD COLUMN abilitytype integer;
    ALTER TABLE talent DROP COLUMN usagemode;
    ALTER TABLE talent ADD
      CONSTRAINT talent_abilitytype_fkey FOREIGN KEY (abilitytype)
      REFERENCES abilitytype (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION;

    CREATE TABLE tmp_talentswitchedoff
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      x real NOT NULL,
      y real NOT NULL,
      characterid integer,
      talentid integer,
      CONSTRAINT talentswitchedoff_pkey PRIMARY KEY (id)
    );
    
    ALTER TABLE event_talentused ADD COLUMN duration real;
    
    CREATE OR REPLACE FUNCTION fill_talentswitchedoff()
      RETURNS void AS
    $BODY$
    DECLARE
        t_id bigint;
        duration integer;
        maincursor cursor for select * from tmp_talentswitchedoff order by sessiontoplayerid, step;
    BEGIN
        for e in maincursor loop        
            select t.id, e.step - t.step into t_id, duration
            from event_talentused t
            where t.sessiontoplayerid = e.sessiontoplayerid
              and t.talentid = e.talentid
              and t.step < e.step
            order by t.step desc;

            if not found then raise notice 'Not found event_talentused for event %', e; end if;

            execute ' update event_talentused set duration = ' || cast(duration as real)/10 ||
              ' where id = ' || t_id || ';';
        end loop;
    END;
    $BODY$
      LANGUAGE 'plpgsql' VOLATILE
      COST 100;
    ALTER FUNCTION fill_talentswitchedoff() OWNER TO dbadmin;
    
    select increment_version_to(16) into ver;
  end if;
    
    
  if ver = 16
  then
    CREATE TABLE sys_droppeddata
    (
      operation_date timestamp without time zone NOT NULL,
      username character varying(255),
      gamesessionid integer,
      sessiontoplayerid integer,
      table_name character varying(255),
      record_id integer
    )
    WITH (
      OIDS=FALSE
    );
    ALTER TABLE sys_droppeddata OWNER TO dbadmin;

    CREATE OR REPLACE FUNCTION array_to_set(
       arr anyarray
    ) RETURNS SETOF anyelement AS $$
    BEGIN
       FOR idx IN array_lower(arr, 1)..array_upper(arr, 1) LOOP
           RETURN NEXT arr[idx];
       END LOOP;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION array_to_set() OWNER TO dbadmin;
    
    CREATE OR REPLACE FUNCTION drop_everything(
        sessionid integer,
        win_username character varying (255)
    ) RETURNS integer AS
    $$
    DECLARE
       cnt integer;
       totalcnt integer := 0;
       tab character varying(255);
       dat record;
       --mgs record;
    BEGIN
       -- all event tables
       for tab in
         select relname
         from pg_stat_user_tables
         where (relname like 'event_%' or relname = 'tmp_talentswitchedoff')
           and relname not like 'event_mg_%'
         order by relname
       loop
       begin
         cnt := 0;
         for dat in
           execute 
           ' select e.*'
           ' from ' || tab || ' e'
           '   join sessiontoplayer stp on stp.id = e.sessiontoplayerid'
           ' where stp.gamesession = $1' using sessionid
         loop
           insert into sys_droppeddata (operation_date, username, gamesessionid, sessiontoplayerid, table_name, record_id)
           values (now(), win_username, sessionid, dat.sessiontoplayerid, tab, dat.id);
           execute 'delete from ' || tab || ' where id = $1' using dat.id;
           --raise notice '%', dat;
           cnt := cnt + 1;
         end loop;
         raise notice 'deleted % records from table %', cnt, tab;
         totalcnt := totalcnt + cnt;
       exception
         when syntax_error then
           raise notice 'syntax error while processing table %', tab;
           continue;
         when undefined_column then
           raise notice 'undefined column in table %', tab;
           continue;       
       end;
       end loop;

       -- minigame event tables
       for tab in
         select n from (values ('event_mg_ballschanged'),('event_mg_boostused'), ('event_mg_zzboostused')) as t(n)
       loop
       begin
         cnt := 0;
         for dat in
           execute
           ' select e.*, mgs.sessiontoplayerid' ||
           ' from ' || tab || ' e' ||
           '   join event_mg_level mgl on mgl.startid = e.mglevelid' ||
           '   join event_mg_session mgs on mgs.startid = mgl.mgsessionid' ||
           '   join sessiontoplayer stp on stp.id = mgs.sessiontoplayerid' ||
           ' where stp.gamesession = $1' using sessionid
         loop
           insert into sys_droppeddata (operation_date, username, gamesessionid, sessiontoplayerid, table_name, record_id)
           values (now(), win_username, sessionid, dat.sessiontoplayerid, tab, dat.id);
           execute 'delete from ' || tab || ' where id = $1' using dat.id;
           --raise notice '%', dat;
           cnt := cnt + 1;
         end loop;
         raise notice 'deleted % records from table %', cnt, tab;
         totalcnt := totalcnt + cnt;
       exception
         when syntax_error then
           raise notice 'syntax error while processing table %', tab;
           continue;
         when undefined_column then
           raise notice 'undefined column in table %', tab;
           continue;       
       end;
       end loop; 

       cnt := 0;
       for dat in
         select e.*, mgs.sessiontoplayerid
         from event_mg_level e
           join event_mg_session mgs on mgs.startid = e.mgsessionid
           join sessiontoplayer stp on stp.id = mgs.sessiontoplayerid
         where stp.gamesession = sessionid
       loop
         insert into sys_droppeddata (operation_date, username, gamesessionid, sessiontoplayerid, table_name, record_id)
         values (now(), win_username, sessionid, dat.sessiontoplayerid, 'event_mg_level', dat.startid);
         delete from event_mg_level where startid = dat.startid;
         --raise notice '%', dat;
         cnt := cnt + 1;
       end loop;
       raise notice 'deleted % records from table event_mg_level', cnt;
       totalcnt := totalcnt + cnt;
       
       cnt := 0;
       for dat in
         select e.*
         from event_mg_session e
           join sessiontoplayer stp on stp.id = e.sessiontoplayerid
         where stp.gamesession = sessionid
       loop
         insert into sys_droppeddata (operation_date, username, gamesessionid, sessiontoplayerid, table_name, record_id)
         values (now(), win_username, sessionid, dat.sessiontoplayerid, 'event_mg_session', dat.startid);
         delete from event_mg_session where startid = dat.startid;
         --raise notice '%', dat;
         cnt := cnt + 1;
       end loop;
       raise notice 'deleted % records from table event_mg_session', cnt;
       totalcnt := totalcnt + cnt;

       cnt := 0;
       for dat in
         select stp.*
         from sessiontoplayer stp
         where stp.gamesession = sessionid
       loop
         insert into sys_droppeddata (operation_date, username, gamesessionid, sessiontoplayerid, table_name, record_id)
         values (now(), win_username, sessionid, null, 'sessiontoplayer', dat.id);
         delete from sessiontoplayer where id = dat.id;
         --raise notice '%', dat;
         cnt := cnt + 1;
       end loop;
       raise notice 'deleted % records from table sessiontoplayer', cnt;
       totalcnt := totalcnt + cnt;

       cnt := 0;
       for dat in
         select gs.*
         from gamesession gs
         where gs.id = sessionid
       loop
         insert into sys_droppeddata (operation_date, username, gamesessionid, sessiontoplayerid, table_name, record_id)
         values (now(), win_username, sessionid, null, 'gamesession', dat.id);
         delete from gamesession where id = dat.id;
         --raise notice '%', dat;
         cnt := cnt + 1;
       end loop;
       raise notice 'deleted % records from table gamesession', cnt;
       totalcnt := totalcnt + cnt;

       raise notice 'total deleted % records', totalcnt;
       return totalcnt;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION drop_everything() OWNER TO dbadmin;

    select increment_version_to(17) into ver;
  end if;

  if ver = 17
  then
    CREATE TABLE event_cheatused
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      x real NOT NULL,
      y real NOT NULL,
      characterid integer,

      command character varying(255),

      CONSTRAINT event_cheatused_pkey PRIMARY KEY (id),
      CONSTRAINT event_cheatused_characterid_fkey FOREIGN KEY (characterid)
          REFERENCES "character" (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_cheatused_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid)
          REFERENCES sessiontoplayer (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE event_cheatused OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_cheatused TO ro;

    select increment_version_to(18) into ver;
  end if;

  if ver = 18
  then
    alter table abilitytype add column deleted boolean not null default false;
    alter table building add column deleted boolean not null default false;
    alter table "character" add column deleted boolean not null default false;
    alter table creature add column deleted boolean not null default false;
    alter table impulsivebuff add column deleted boolean not null default false;
    alter table mgboost add column deleted boolean not null default false;
    alter table talent add column deleted boolean not null default false;
    alter table unittype add column deleted boolean not null default false;

    select increment_version_to(19) into ver;
  end if;

  if ver = 19
  then
    ALTER TABLE player ADD COLUMN sex integer not null default 0;
    
    select increment_version_to(20) into ver;
  end if;

  if ver = 20
  then
    ALTER TABLE event_debugvar ADD COLUMN eventtime timestamp without time zone;
    
    select increment_version_to(21) into ver;
  end if;

  if ver = 21
  then
    CREATE INDEX idx_event_talentused_sessiontoplayerid
      ON event_talentused
      USING btree (sessiontoplayerid);
    
    select increment_version_to(22) into ver;
  end if;

  if ver = 22
  then
    ALTER TABLE datehierarchy ADD COLUMN push character varying(255);
    
    CREATE OR REPLACE FUNCTION set_push_dates(title character varying, startdate date, enddate date)
      RETURNS void AS
    $BODY$
      declare
        startid integer;
        endid integer;
      begin
        if title = '' then raise 'Title is empty'; end if;
        if startdate >= enddate then raise 'Incorrect dates'; end if;
        
        select min(id), max(id) into startid, endid
        from datehierarchy
        where id >= cast(to_char( startdate, 'YYYYMMDD') as integer)
          and id <= cast(to_char( enddate, 'YYYYMMDD') as integer);

        raise notice 'updatind datehierarchy on interval [%, %]', startid, endid;
        
        update datehierarchy
        set push = title
        where id >= startid
          and id <= endid;
      end;
    $BODY$
    LANGUAGE plpgsql;
    ALTER FUNCTION set_push_dates(character varying, date, date) OWNER TO dbadmin;
    
    perform set_push_dates('Alpha Push 1',   '2010-12-06', '2010-12-12');
    perform set_push_dates('Alpha Push 2',   '2011-01-13', '2011-01-20');
    perform set_push_dates('Alpha Push 2.1', '2011-01-27', '2011-02-02');
    perform set_push_dates('Alpha Push 3',   '2011-03-09', '2011-03-15');
    perform set_push_dates('Alpha Push 3.1', '2011-03-28', '2011-04-03');
    
    select increment_version_to(23) into ver;
  end if;

  if ver = 23
  then
    CREATE TABLE tmp_mg2zzboostsuggested
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      x real NOT NULL,
      y real NOT NULL,
      CONSTRAINT mg2zzboostsuggested_pkey PRIMARY KEY (id)
    );

    CREATE TABLE event_mg_zzboostsuggested
    (
      id bigint NOT NULL,
      mglevelid integer NOT NULL,
      step integer NOT NULL,

      CONSTRAINT event_mg_zzboostsuggested_pkey PRIMARY KEY (id),
      CONSTRAINT event_mg_zzboostsuggested_mglevelid_fkey FOREIGN KEY (mglevelid)
          REFERENCES event_mg_level (startid) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE event_mg_zzboostsuggested OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_mg_zzboostsuggested TO ro;
    
    CREATE OR REPLACE FUNCTION fill_mg_zzboostsuggested()
      RETURNS integer AS
    $BODY$
    DECLARE
        l_id bigint;
        eventcursor cursor for select * from tmp_mg2zzboostsuggested;
    BEGIN
        for e in eventcursor loop        
            --raise notice ' --- ';
            --raise notice '%', e;
            
            select l.startid into l_id
            from event_mg_level l
              join event_mg_session s on l.mgsessionid = s.startid
            where s.sessiontoplayerid = e.sessiontoplayerid
              and l.startstep < e.step
            order by l.startstep desc;

            if not found then raise exception 'Not found mg_level for event %', e; end if;

            execute 'insert into event_mg_zzboostsuggested (id, mglevelid, step) values (' 
            || e.id || ',' || l_id || ',' || e.step || ');';
            --raise notice '% % %', e.id, l_id, e.step;        
        end loop;
        return 0;
    END;
    $BODY$
      LANGUAGE 'plpgsql' VOLATILE
      COST 100;
    GRANT EXECUTE ON FUNCTION fill_mg_zzboostsuggested() TO public;
    
    select increment_version_to(24) into ver;
  end if;
  
  if ver = 24
  then

    CREATE TABLE achievement
    (
      id integer NOT NULL,
      "name" character varying(255),
      dbid character varying(1024),
      deleted boolean NOT NULL DEFAULT false,
      CONSTRAINT achievement_pkey PRIMARY KEY (id)
    );
    ALTER TABLE achievement OWNER TO dbadmin;
    GRANT SELECT ON TABLE achievement TO ro;

    CREATE TABLE consumable
    (
      id integer NOT NULL,
      "name" character varying(255),
      dbid character varying(1024),
      naftacost integer,
      deleted boolean NOT NULL DEFAULT false,
      CONSTRAINT consumable_pkey PRIMARY KEY (id)
    );
    ALTER TABLE consumable OWNER TO dbadmin;
    GRANT SELECT ON TABLE consumable TO ro;

    CREATE TABLE event_achievement
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      x real NOT NULL,
      y real NOT NULL,
      characterid integer,
      achievementid integer,
      CONSTRAINT event_achievement_pkey PRIMARY KEY (id),
      CONSTRAINT event_achievement_characterid_fkey FOREIGN KEY (characterid)
          REFERENCES "character" (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_achievement_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid)
          REFERENCES sessiontoplayer (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_achievement_achievementid_fkey FOREIGN KEY (achievementid)
          REFERENCES achievement (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE event_achievement OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_achievement TO ro;

    CREATE TABLE event_consumablebought
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      x real NOT NULL,
      y real NOT NULL,
      characterid integer,
      consumableid integer,
      nafta integer,
      CONSTRAINT event_consumablebought_pkey PRIMARY KEY (id),
      CONSTRAINT event_consumablebought_characterid_fkey FOREIGN KEY (characterid)
          REFERENCES "character" (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_consumablebought_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid)
          REFERENCES sessiontoplayer (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_consumablebought_consumableid_fkey FOREIGN KEY (consumableid)
          REFERENCES consumable (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE event_consumablebought OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_consumablebought TO ro;

    CREATE TABLE event_consumableused
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      x real NOT NULL,
      y real NOT NULL,
      characterid integer,
      consumableid integer,
      CONSTRAINT event_consumableused_pkey PRIMARY KEY (id),
      CONSTRAINT event_consumableused_characterid_fkey FOREIGN KEY (characterid)
          REFERENCES "character" (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_consumableused_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid)
          REFERENCES sessiontoplayer (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT event_consumableused_consumableid_fkey FOREIGN KEY (consumableid)
          REFERENCES consumable (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE event_consumableused OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_consumableused TO ro;
    
    ALTER TABLE consumable OWNER TO dbadmin;
    GRANT SELECT ON TABLE consumable TO ro;

    select increment_version_to(25) into ver;
  end if;

  if ver = 25
  then
    ALTER TABLE "character" ADD COLUMN dbid character varying(1024);
    ALTER TABLE impulsivebuff ADD COLUMN dbid character varying(1024);
    ALTER TABLE talent ADD COLUMN dbid character varying(1024);

    select increment_version_to(26) into ver;
  end if;

  if ver = 26
  then
    select increment_version_to(27) into ver;
  end if;

  if ver = 27
  then
    ALTER TABLE event_assist DROP CONSTRAINT event_assist_killercreatureid_fkey;
    
    select increment_version_to(28) into ver;
  end if;

  if ver = 28
  then
    CREATE OR REPLACE VIEW v_event_assist AS 
     SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.victimid, e.killerid, e.killercreatureid, 
            CASE
                WHEN c.name IS NOT NULL THEN 'hero'::text
                WHEN r.name IS NOT NULL THEN 'creature'::text
                WHEN b.name IS NOT NULL THEN 'building'::text
                ELSE NULL::text
            END AS killertype, COALESCE(c.name, r.name, b.name) AS killername
       FROM event_assist e
       LEFT JOIN "character" c ON c.id = e.killerid
       LEFT JOIN creature r ON r.id = e.killercreatureid
       LEFT JOIN building b ON b.id = e.killercreatureid;

    ALTER TABLE v_event_assist OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_assist TO ro;

    CREATE OR REPLACE VIEW v_event_buildingdestroyed AS 
     SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.destroyerid, e.destroyercreatureid, e.buildingid, 
            CASE
                WHEN c.name IS NOT NULL THEN 'hero'::text
                WHEN r.name IS NOT NULL THEN 'creature'::text
                WHEN b.name IS NOT NULL THEN 'building'::text
                ELSE NULL::text
            END AS destroyertype, COALESCE(c.name, r.name, b.name) AS destroyername
       FROM event_buildingdestroyed e
       LEFT JOIN "character" c ON c.id = e.destroyerid
       LEFT JOIN creature r ON r.id = e.destroyercreatureid
       LEFT JOIN building b ON b.id = e.destroyercreatureid;

    ALTER TABLE v_event_buildingdestroyed OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_buildingdestroyed TO ro;

    CREATE OR REPLACE VIEW v_event_damage AS 
     SELECT e.id, e.sessiontoplayerid, e.step, e.characterid, e.dealt, e.opponentid, e.unittype, e.talentid, e.physicaldamage, e.magicaldamage, e.puredamage, 
            CASE
                WHEN c.name IS NOT NULL THEN 'hero'::text
                WHEN r.name IS NOT NULL THEN 'creature'::text
                WHEN b.name IS NOT NULL THEN 'building'::text
                WHEN e.unittype = 17 THEN 'flagpole'::text
                ELSE NULL::text
            END AS opponenttype, ut.name AS opponentunittype, COALESCE(c.name, r.name, b.name, 'flagpole'::character varying(255)) AS opponentname
       FROM event_damage e
       JOIN unittype ut ON ut.id = e.unittype
       LEFT JOIN "character" c ON c.id = e.opponentid
       LEFT JOIN creature r ON r.id = e.opponentid
       LEFT JOIN building b ON b.id = e.opponentid;

    ALTER TABLE v_event_damage OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_damage TO ro;

    DROP VIEW v_event_death;

    CREATE OR REPLACE VIEW v_event_death AS 
     SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.killerid, e.killercreatureid, 
            CASE
                WHEN c.name IS NOT NULL THEN 'hero'::text
                WHEN r.name IS NOT NULL THEN 'creature'::text
                WHEN b.name IS NOT NULL THEN 'building'::text
                ELSE NULL::text
            END AS killertype, COALESCE(c.name, r.name, b.name) AS killername
       FROM event_death e
       LEFT JOIN "character" c ON c.id = e.killerid
       LEFT JOIN creature r ON r.id = e.killercreatureid
       LEFT JOIN building b ON b.id = e.killercreatureid;

    ALTER TABLE v_event_death OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_death TO ro;

    CREATE OR REPLACE VIEW v_event_flag AS 
     SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.raised, e.faction, e.road, e.segment, e.activatorid, e.activatorcreatureid, 
            CASE
                WHEN c.name IS NOT NULL THEN 'hero'::text
                WHEN r.name IS NOT NULL THEN 'creature'::text
                ELSE NULL::text
            END AS activatortype, COALESCE(c.name, r.name) AS activatorname
       FROM event_flag e
       LEFT JOIN "character" c ON c.id = e.activatorid
       LEFT JOIN creature r ON r.id = e.activatorcreatureid;

    ALTER TABLE v_event_flag OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_flag TO ro;

    DROP VIEW v_event_kill;

    CREATE OR REPLACE VIEW v_event_kill AS 
     SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.victimid, e.victimcreatureid, 
            CASE
                WHEN c.name IS NOT NULL THEN 'hero'::text
                WHEN r.name IS NOT NULL THEN 'creature'::text
                ELSE NULL::text
            END AS victimtype, COALESCE(c.name, r.name) AS victimname
       FROM event_kill e
       LEFT JOIN "character" c ON c.id = e.victimid
       LEFT JOIN creature r ON r.id = e.victimcreatureid;

    ALTER TABLE v_event_kill OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_kill TO ro;

    select increment_version_to(29) into ver;
  end if;

  if ver = 29
  then
    CREATE TABLE tag
    (
      "name" character varying(50) NOT NULL,
      description character varying(1024),
      CONSTRAINT tag_pkey PRIMARY KEY (name)
    );
    ALTER TABLE tag OWNER TO dbadmin;
    GRANT SELECT ON TABLE tag TO ro;

    CREATE TABLE player_tags
    (
      playerid integer NOT NULL,
      tag character varying(50) NOT NULL,
      CONSTRAINT player_tags_pkey PRIMARY KEY (playerid, tag),
      CONSTRAINT player_tags_playerid_fkey FOREIGN KEY (playerid)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT player_tags_tag_fkey FOREIGN KEY (tag)
          REFERENCES tag ("name") MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE player_tags OWNER TO dbadmin;
    GRANT SELECT ON TABLE player_tags TO ro;

    select increment_version_to(30) into ver;
  end if;

  if ver = 30
  then
    -- new version incrementation process
    select increment_version_to(31) into ver;
  end if;
  
  if ver = 31
  then
    CREATE TABLE sys_checks_missingrows
    (
      tablename character varying(100),
      id bigint,
      CONSTRAINT sys_checks_missingrows_tablename_key UNIQUE (tablename, id)
    );
    ALTER TABLE sys_checks_missingrows OWNER TO dbadmin;
  
    CREATE TABLE sys_checks_scope
    (
      tablename character varying(100) NOT NULL,
      lastchecked bigint,
      CONSTRAINT sys_checks_scope_pkey PRIMARY KEY (tablename)
    );
    ALTER TABLE sys_checks_scope OWNER TO dbadmin;
  
    CREATE OR REPLACE FUNCTION get_checks_min_id(character varying)
      RETURNS integer AS
    $BODY$
      DECLARE
        min_id bigint;
      BEGIN
        select coalesce(min(id),
                       (select lastchecked from sys_checks_scope where tablename = $1),
                       0) into min_id
        from sys_checks_missingrows
        where tablename = $1;

        return min_id;
      END;
    $BODY$
      LANGUAGE plpgsql VOLATILE;
    ALTER FUNCTION get_checks_min_id(character varying) OWNER TO dbadmin;

    select increment_version_to(32) into ver;
  end if;

  if ver = 32
  then
    CREATE OR REPLACE FUNCTION player_has_tag(_p character varying, _t character varying)
      RETURNS boolean AS
    $BODY$
      begin
        return exists (
          select 1 
          from player p
            join player_tags pt on pt.playerid = p.id
          where p.login = _p
            and pt.tag = _t
        );
      end;
    $BODY$
      LANGUAGE plpgsql VOLATILE
      COST 100;
    ALTER FUNCTION player_has_tag(character varying, character varying) OWNER TO dbadmin;
    GRANT EXECUTE ON FUNCTION player_has_tag(character varying, character varying) TO ro;

    -- new version incrementation process
    select increment_version_to(33) into ver;
  end if;

  if ver = 33
  then
    CREATE TABLE player_tags_generated
    (
      playerid integer,
      playerlogin character varying(255)
    );
    ALTER TABLE player_tags_generated OWNER TO dbadmin;
    GRANT SELECT ON TABLE player_tags_generated TO ro;
    
    CREATE OR REPLACE FUNCTION player_refresh_tags()
      RETURNS void AS
    $BODY$
      declare
        tagcursor cursor for select distinct lower(tag) as tag from player_tags order by 1;
        attcursor cursor for 
            select attname
            from pg_attribute, pg_class 
            where attrelid = pg_class.oid
              and relname = 'player_tags_generated'
              and attname not in ('playerid', 'playerlogin')
              and attnum > 0;    
        tag_exists boolean;
        _pt record;
      begin
        insert into player_tags_generated (playerid, playerlogin)
        select id, login from player
        where id not in ( select playerid from player_tags_generated );

        /* remove unused columns */
        for _a in attcursor
        loop
          if not exists (select 1 from player_tags where lower(tag) = _a.attname)
          then
            execute 'alter table player_tags_generated drop column '||_a.attname||';';
            raise notice 'dropped column % from table player_tags_generated', _a;
          end if;
        end loop;
        
        /* add new columns */
        for _t in tagcursor
        loop
          if not exists (
            select attname 
            from pg_attribute, pg_class 
            where attrelid = pg_class.oid
              and relname = 'player_tags_generated'
              and attnum > 0
              and attname = _t.tag ) 
          then
            execute 'alter table player_tags_generated add column '
              || _t.tag || ' boolean not null default false;';
            raise notice 'created column % in table player_tags_generated', _t;
          end if;
        end loop;

        /* update generated table */
        for _pt in select * from player_tags loop
          execute 'select ' || _pt.tag || ' from player_tags_generated ' ||
            'where playerid = ' || _pt.playerid into tag_exists;
          if not tag_exists then
            execute 'update player_tags_generated set ' || _pt.tag || ' = true ' ||
              'where playerid = ' || _pt.playerid;
            raise notice 'set tag % for player id = %', _pt.tag, _pt.playerid;
          end if;
        end loop;
        
      end;
    $BODY$
      LANGUAGE plpgsql VOLATILE;
    
    perform player_refresh_tags();
    
    CREATE OR REPLACE FUNCTION player_set_tag(_p character varying, character varying)
      RETURNS void  AS
    $BODY$
      declare 
       _t character varying;
      begin
        _t = lower($2);

        if not exists ( select 1 from tag where name = _t ) then
          insert into tag values (_t, null);
        end if;

        insert into player_tags 
        select p.id, _t
        from player p
        where p.login = _p;

        if not exists (
          select attname 
          from pg_attribute, pg_class 
          where attrelid = pg_class.oid
            and relname = 'player_tags_generated'
            and attnum > 0
            and attname = _t ) 
        then
          execute 'alter table player_tags_generated add column '
            || _t || ' boolean not null default false;';
          raise notice 'created column % in table player_tags_generated', _t;
        end if;

        execute 'update player_tags_generated set ' || _t || ' = true ' || 
          'where playerlogin = ''' || _p || '''';
        raise notice 'set tag % for player %', _t, _p;

      end;
    $BODY$
      LANGUAGE plpgsql VOLATILE;

    -- new version incrementation process
    select increment_version_to(34) into ver;
  end if;

  if ver = 34
  then
    CREATE TABLE socialsession
    (
      id integer NOT NULL,
      player integer NOT NULL,
      server character varying,
      "cluster" character varying,
      starttime timestamp without time zone NOT NULL,
      endtime timestamp without time zone,
      CONSTRAINT socialsession_pkey PRIMARY KEY (id),
      CONSTRAINT socialsession_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE socialsession OWNER TO dbadmin;
    GRANT SELECT ON TABLE socialsession TO ro;

    -- new version incrementation process
    select increment_version_to(35) into ver;
  end if;
  
  if ver = 35
  then
    ALTER TABLE player ALTER id TYPE bigint;
    ALTER TABLE player ALTER COLUMN "login" DROP NOT NULL;
    ALTER TABLE player ADD COLUMN nickname character varying(255);
    ALTER TABLE player ADD COLUMN faction integer NOT NULL DEFAULT -1;
  
    ALTER TABLE gamesession DROP COLUMN sidewon;
    ALTER TABLE gamesession ADD COLUMN sidewon integer NOT NULL DEFAULT -1;
    
    ALTER TABLE sessiontoplayer DROP COLUMN preferfaction;
    
    ALTER TABLE talent ADD COLUMN talentid character varying(1024);

    select increment_version_to(36) into ver;
  end if;

  if ver = 36
  then
    ALTER TABLE event_buildingdestroyed RENAME destroyerid TO destroyercharacterid;
    ALTER TABLE event_flag RENAME activatorid TO activatorcharacterid;
    ALTER TABLE event_kill RENAME victimid TO victimcharacterid;
    ALTER TABLE event_assist RENAME victimid TO victimcharacterid;
    ALTER TABLE event_assist RENAME killerid TO killercharacterid;
    ALTER TABLE event_death RENAME killerid TO killercharacterid;
    
    DROP VIEW v_event_kill;
    CREATE VIEW v_event_kill AS 
    SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.victimcharacterid, e.victimcreatureid, 
      CASE
        WHEN c.name IS NOT NULL THEN 'hero'::text
        WHEN r.name IS NOT NULL THEN 'creature'::text
        ELSE NULL::text
      END AS victimtype, COALESCE(c.name, r.name) AS victimname
    FROM event_kill e
    LEFT JOIN "character" c ON c.id = e.victimcharacterid
    LEFT JOIN creature r ON r.id = e.victimcreatureid;
    
    DROP VIEW v_event_assist;
    CREATE VIEW v_event_assist AS 
    SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.victimcharacterid, e.killercharacterid, e.killercreatureid, 
      CASE
        WHEN c.name IS NOT NULL THEN 'hero'::text
        WHEN r.name IS NOT NULL THEN 'creature'::text
        WHEN b.name IS NOT NULL THEN 'building'::text
        ELSE NULL::text
      END AS killertype, COALESCE(c.name, r.name, b.name) AS killername
    FROM event_assist e
    LEFT JOIN "character" c ON c.id = e.killercharacterid
    LEFT JOIN creature r ON r.id = e.killercreatureid
    LEFT JOIN building b ON b.id = e.killercreatureid;

    DROP VIEW v_event_death;
    CREATE VIEW v_event_death AS 
    SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.killercharacterid, e.killercreatureid, 
      CASE
        WHEN c.name IS NOT NULL THEN 'hero'::text
        WHEN r.name IS NOT NULL THEN 'creature'::text
        WHEN b.name IS NOT NULL THEN 'building'::text
        ELSE NULL::text
      END AS killertype, COALESCE(c.name, r.name, b.name) AS killername
    FROM event_death e
    LEFT JOIN "character" c ON c.id = e.killercharacterid
    LEFT JOIN creature r ON r.id = e.killercreatureid
    LEFT JOIN building b ON b.id = e.killercreatureid;
    
    DROP VIEW v_event_buildingdestroyed;
    CREATE VIEW v_event_buildingdestroyed AS 
    SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.destroyercharacterid, e.destroyercreatureid, e.buildingid, 
      CASE
        WHEN c.name IS NOT NULL THEN 'hero'::text
        WHEN r.name IS NOT NULL THEN 'creature'::text
        WHEN b.name IS NOT NULL THEN 'building'::text
        ELSE NULL::text
      END AS destroyertype, COALESCE(c.name, r.name, b.name) AS destroyername
    FROM event_buildingdestroyed e
    LEFT JOIN "character" c ON c.id = e.destroyercharacterid
    LEFT JOIN creature r ON r.id = e.destroyercreatureid
    LEFT JOIN building b ON b.id = e.destroyercreatureid;

    DROP VIEW v_event_flag;
    CREATE VIEW v_event_flag AS 
    SELECT e.id, e.sessiontoplayerid, e.step, e.x, e.y, e.characterid, e.raised, e.faction, e.road, e.segment, e.activatorcharacterid, e.activatorcreatureid, 
      CASE
        WHEN c.name IS NOT NULL THEN 'hero'::text
        WHEN r.name IS NOT NULL THEN 'creature'::text
        ELSE NULL::text
      END AS activatortype, COALESCE(c.name, r.name) AS activatorname
    FROM event_flag e
    LEFT JOIN "character" c ON c.id = e.activatorcharacterid
    LEFT JOIN creature r ON r.id = e.activatorcreatureid;

    ALTER TABLE v_event_kill OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_kill TO ro;
    ALTER TABLE v_event_assist OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_assist TO ro;
    ALTER TABLE v_event_death OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_death TO ro;
    ALTER TABLE v_event_buildingdestroyed OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_buildingdestroyed TO ro;
    ALTER TABLE v_event_flag OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_event_flag TO ro;

    select increment_version_to(37) into ver;
  end if;

  if ver = 37
  then
    CREATE TABLE gm_unlockcharacter
    (
      id integer NOT NULL,
      player integer NOT NULL,
      gmlogin character varying NOT NULL,
      character integer NOT NULL,
      operationdate timestamp without time zone NOT NULL,
      CONSTRAINT gm_unlockcharacter_pkey PRIMARY KEY (id),
      CONSTRAINT gm_unlockcharacter_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT gm_unlockcharacter_character_fkey FOREIGN KEY ("character")
      REFERENCES "character" (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE gm_unlockcharacter OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_unlockcharacter TO ro;
    
    CREATE TABLE gm_lockcharacter
    (
      id integer NOT NULL,
      player integer NOT NULL,
      gmlogin character varying NOT NULL,
      character integer NOT NULL,
      operationdate timestamp without time zone NOT NULL,
      CONSTRAINT gm_lockcharacter_pkey PRIMARY KEY (id),
      CONSTRAINT gm_lockcharacter_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT gm_lockcharacter_character_fkey FOREIGN KEY ("character")
      REFERENCES "character" (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE gm_lockcharacter OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_lockcharacter TO ro;

    select increment_version_to(38) into ver;
  end if;

  if ver = 38
  then
    ALTER TABLE gm_unlockcharacter ALTER player TYPE bigint;
    ALTER TABLE gm_lockcharacter ALTER player TYPE bigint;

    CREATE TABLE gm_addtalent
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      gmlogin character varying NOT NULL,
      talent integer NOT NULL,
      operationdate timestamp without time zone NOT NULL,
      CONSTRAINT gm_addtalent_pkey PRIMARY KEY (id),
      CONSTRAINT gm_addtalent_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT gm_addtalent_talent_fkey FOREIGN KEY (talent)
      REFERENCES talent (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE gm_addtalent OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_addtalent TO ro;

    CREATE TABLE gm_deletetalent
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      gmlogin character varying NOT NULL,
      talent integer NOT NULL,
      operationdate timestamp without time zone NOT NULL,
      CONSTRAINT gm_deletetalent_pkey PRIMARY KEY (id),
      CONSTRAINT gm_deletetalent_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT gm_deletetalent_talent_fkey FOREIGN KEY (talent)
      REFERENCES talent (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE gm_deletetalent OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_deletetalent TO ro;

    select increment_version_to(39) into ver;
  end if;

  if ver = 39
  then
    CREATE TABLE gm_banplayer
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      gmlogin character varying NOT NULL,
      minutes integer NOT NULL,
      reason character varying,
      operationdate timestamp without time zone NOT NULL,

      CONSTRAINT gm_banplayer_pkey PRIMARY KEY (id),
      CONSTRAINT gm_banplayer_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE gm_banplayer OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_banplayer TO ro;

    CREATE TABLE gm_unbanplayer
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      gmlogin character varying NOT NULL,
      operationdate timestamp without time zone NOT NULL,

      CONSTRAINT gm_unbanplayer_pkey PRIMARY KEY (id),
      CONSTRAINT gm_unbanplayer_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE gm_unbanplayer OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_unbanplayer TO ro;

    CREATE TABLE gm_muteplayer
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      gmlogin character varying NOT NULL,
      minutes integer NOT NULL,
      reason character varying,
      operationdate timestamp without time zone NOT NULL,

      CONSTRAINT gm_muteplayer_pkey PRIMARY KEY (id),
      CONSTRAINT gm_muteplayer_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE gm_muteplayer OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_muteplayer TO ro;

    CREATE TABLE gm_unmuteplayer
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      gmlogin character varying NOT NULL,
      operationdate timestamp without time zone NOT NULL,

      CONSTRAINT gm_unmuteplayer_pkey PRIMARY KEY (id),
      CONSTRAINT gm_unmuteplayer_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE gm_unmuteplayer OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_unmuteplayer TO ro;

    select increment_version_to(40) into ver;
  end if;
  
  if ver = 40
  then
    CREATE TABLE chat
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      "timestamp" timestamp without time zone NOT NULL,
      channel character varying NOT NULL,
      message character varying NOT NULL,

      CONSTRAINT chat_pkey PRIMARY KEY (id),
      CONSTRAINT chat_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE chat OWNER TO dbadmin;
    GRANT SELECT ON TABLE chat TO ro;

    select increment_version_to(41) into ver;
  end if;
  
  if ver = 41
  then
    CREATE TABLE gm_editplayer
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      gmlogin character varying NOT NULL,
      field character varying NOT NULL,
      oldvalue character varying NOT NULL,
      newvalue character varying NOT NULL,
      operationdate timestamp without time zone NOT NULL,

      CONSTRAINT gm_editplayer_pkey PRIMARY KEY (id),
      CONSTRAINT gm_editplayer_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE gm_editplayer OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_editplayer TO ro;

    select increment_version_to(42) into ver;
  end if;

  if ver = 42
  then
    alter table gamesession drop column sessionstatus;
    alter table gamesession add column sessionresult integer;
    update gamesession set sessionresult = 0;
    alter table gamesession alter column sessionresult set not null;
    
    select increment_version_to(43) into ver;
  end if;
  
  if ver = 43
  then
    alter table playercharacter add column locked boolean NOT NULL default false;
    alter table playercharacter add column unlockdate timestamp without time zone;
    
    CREATE TABLE characterunlock
    (
      id integer NOT NULL,
      playercharacter integer NOT NULL,
      silver integer NOT NULL,
      "timestamp" timestamp without time zone NOT NULL,

      CONSTRAINT characterunlock_pkey PRIMARY KEY (id),
      CONSTRAINT characterunlock_playercharacter_fkey FOREIGN KEY (playercharacter)
          REFERENCES playercharacter (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE characterunlock OWNER TO dbadmin;
    GRANT SELECT ON TABLE characterunlock TO ro;

    select increment_version_to(44) into ver;
  end if;
  
  if ver = 44
  then
    alter table player_tags alter playerid type bigint;
    alter table playercharacter alter player type bigint;
    alter table socialsession alter player type bigint;

    select increment_version_to(45) into ver;
  end if;

  if ver = 45
  then
    CREATE TABLE sys_checks_ignoredrows
    (
      tablename character varying not null,
      id bigint not null,
      comment character varying,
      constraint sys_shecks_ignoredrows_pkey primary key (tablename, id)
    );
    ALTER TABLE sys_checks_ignoredrows OWNER TO dbadmin;

    select increment_version_to(46) into ver;
  end if;

  if ver = 46
  then
    update player p
    set faction = 
      (select stp2.side::integer from sessiontoplayer stp2
       where stp2.id = 
         (select max(stp.id)
          from sessiontoplayer stp
            join playercharacter pc on pc.id = stp.playercharacter
          where pc.player = p.id));
  
    alter table talent add column tour integer;
    alter table talent add column rarity integer;
    alter table talent add column budget real;

    select increment_version_to(47) into ver;
  end if;

  if ver = 47
  then
    alter table player add lastmodified timestamp default '-infinity';
    alter table playercharacter add lastmodified timestamp default '-infinity';
    
    select increment_version_to(48) into ver;
  end if;

  if ver = 48
  then
    CREATE TABLE event_exceedingsteptime
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,

      starttime timestamp without time zone,
      finishtime timestamp without time zone,
      stepcount integer,
      steptimemin integer,
      steptimemax integer,
      steptimeavg integer,
      worldrequest boolean,
      
      CONSTRAINT event_exceedingsteptime_pkey PRIMARY KEY (id)
    );
    ALTER TABLE event_exceedingsteptime OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_exceedingsteptime TO ro;

    select increment_version_to(49) into ver;
  end if;

  if ver = 49
  then
    alter table event_exceedingsteptime drop column worldrequest;
    alter table event_exceedingsteptime add column worldrequeststep integer;
    alter table event_exceedingsteptime add column typeid integer;

    select increment_version_to(50) into ver;
  end if;

  if ver = 50
  then
    alter table character ADD COLUMN gender integer;
    update character set gender = 0;

    select increment_version_to(51) into ver;
  end if;

  if ver = 51
  then
    alter table event_exceedingsteptime add column startstep integer;
    alter table event_exceedingsteptime add column finishstep integer;

    select increment_version_to(52) into ver;
  end if;

  if ver = 52
  then
    DROP FUNCTION get_checks_min_id(character varying);

    select increment_version_to(53) into ver;
  end if;

  if ver = 53
  then
    create table mmakingsession
    (
      id bigint not null,
      persistentid bigint not null,
      status integer not null,
      "timestamp" timestamp without time zone,
      CONSTRAINT mmakingsession_pkey PRIMARY KEY (id),
      CONSTRAINT mmakingsession_unique_persistentid UNIQUE (persistentid)
    );
    ALTER TABLE mmakingsession OWNER TO dbadmin;
    GRANT SELECT ON TABLE mmakingsession TO ro;

    create table mmakingplayer
    (
      id bigint not null,
      mmakingsession bigint,
      playercharacter integer not null,
      faction integer not null,
      sex integer not null,
      rating integer not null,
      party integer not null,
      waitinterval real not null,
      lobbyreaction integer not null,

      CONSTRAINT mmakingplayer_pkey PRIMARY KEY (id),
      CONSTRAINT mmakingplayer_mmakingsession_fkey FOREIGN KEY (mmakingsession)
          REFERENCES mmakingsession (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION,
      CONSTRAINT mmakingplayer_playercharacter_fkey FOREIGN KEY (playercharacter)
          REFERENCES playercharacter (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE mmakingplayer OWNER TO dbadmin;
    GRANT SELECT ON TABLE mmakingplayer TO ro;

    alter table gamesession add column mmakingsession bigint;

    alter table gamesession add
      CONSTRAINT gamesession_mmakingsession_fkey FOREIGN KEY (mmakingsession)
      REFERENCES mmakingsession (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION;
      
    select increment_version_to(54) into ver;
  end if;

  if ver = 54
  then
    alter table player DROP COLUMN login;

    select increment_version_to(55) into ver;
  end if;

  if ver = 55
  then
    CREATE TABLE event_disconnect
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,

      reason integer,
      "timestamp" timestamp without time zone,
      
      CONSTRAINT disconnect_pkey PRIMARY KEY (id)
    );
    ALTER TABLE event_disconnect OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_disconnect TO ro;

    select increment_version_to(56) into ver;
  end if;

  if ver = 56
  then
    if not exists (
      select *
      from pg_attribute a
        join pg_class p on p.oid = attrelid
      where attname = 'persistentid'
        and relname = 'mmakingsession')
    then
      raise 'Before updating, please RUN FIX PWANALYSIS_PF-38922.SQL !';
    end if;

    select increment_version_to(57) into ver;
  end if;

  if ver = 57
  then
    CREATE TABLE movetobath
    (
      id integer NOT NULL,
      playercharacter integer NOT NULL,
      silver integer NOT NULL,
      minutes integer NOT NULL,
      "timestamp" timestamp without time zone NOT NULL,

      CONSTRAINT movetobath_pkey PRIMARY KEY (id),
      CONSTRAINT movetobath_playercharacter_fkey FOREIGN KEY (playercharacter)
          REFERENCES playercharacter (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE movetobath OWNER TO dbadmin;
    GRANT SELECT ON TABLE movetobath TO ro;

    select increment_version_to(58) into ver;
  end if;

  if ver = 58
  then
    alter table player add column rating integer;
    alter table player add column reliability integer;
    update player set rating = 0, reliability = 0;
    alter table player alter column rating set not null;
    alter table player alter column reliability set not null;

    alter table gamesession rename column mmakingsession to persistentid;
    alter table gamesession add  constraint gamesession_unique_persistentid unique (persistentid);
    alter table gamesession drop constraint gamesession_mmakingsession_fkey;

    alter table gamesession drop column sidearesult;
    alter table gamesession drop column sidebresult;

    alter table sessiontoplayer add column silverchange integer;
    alter table sessiontoplayer add column silvertotal integer;
    alter table sessiontoplayer add column ratingchange integer;
    alter table sessiontoplayer add column ratingtotal integer;
    alter table sessiontoplayer add column reliabilitychange integer;
    alter table sessiontoplayer add column reliabilitytotal integer;

    update sessiontoplayer
    set silverchange = 0, silvertotal = 0,
        ratingchange = 0, ratingtotal = 0,
        reliabilitychange = 0, reliabilitytotal = 0;

    select increment_version_to(59) into ver;
  end if;

  if ver = 59
  then
    alter table sessiontoplayer add column leaver boolean;
    alter table playercharacter add constraint playercharacter_unique_player_character UNIQUE (player, character);

    select increment_version_to(60) into ver;
  end if;

  if ver = 60
  then
    CREATE TABLE launcherstart
    (
      id bigint NOT NULL,
      hostid character varying,
      version character varying,
      "timestamp" timestamp without time zone,
      CONSTRAINT launcherstart_pkey PRIMARY KEY (id)
    );
    ALTER TABLE launcherstart OWNER TO dbadmin;
    GRANT SELECT ON TABLE launcherstart TO ro;

    CREATE TABLE launcherdstart
    (
      id bigint NOT NULL,
      hostid character varying,
      package character varying,
      version character varying,
      "timestamp" timestamp without time zone,
      CONSTRAINT launcherdstart_pkey PRIMARY KEY (id)
    );
    ALTER TABLE launcherdstart OWNER TO dbadmin;
    GRANT SELECT ON TABLE launcherdstart TO ro;

    CREATE TABLE launcherdend
    (
      id bigint NOT NULL,
      hostid character varying,
      package character varying,
      version character varying,
      status integer NOT NULL,
      "timestamp" timestamp without time zone,
      CONSTRAINT launcherdend_pkey PRIMARY KEY (id)
    );
    ALTER TABLE launcherdend OWNER TO dbadmin;
    GRANT SELECT ON TABLE launcherdend TO ro;

    CREATE TABLE socialregister
    (
      id bigint NOT NULL,
      hostid character varying,
      playerid bigint,
      snid character varying,
      snuid character varying,
      "timestamp" timestamp without time zone,
      CONSTRAINT socialregister_pkey PRIMARY KEY (id)
    );
    ALTER TABLE socialregister OWNER TO dbadmin;
    GRANT SELECT ON TABLE socialregister TO ro;

    CREATE TABLE socialjoin
    (
      id bigint NOT NULL,
      playerid bigint,
      snid character varying,
      snuid character varying,
      "timestamp" timestamp without time zone,
      CONSTRAINT socialjoin_pkey PRIMARY KEY (id)
    );
    ALTER TABLE socialjoin OWNER TO dbadmin;
    GRANT SELECT ON TABLE socialjoin TO ro;

    CREATE TABLE socialmerge
    (
      id bigint NOT NULL,
      playerid1 bigint,
      playerid2 bigint,
      "timestamp" timestamp without time zone,
      CONSTRAINT socialmerge_pkey PRIMARY KEY (id)
    );
    ALTER TABLE socialmerge OWNER TO dbadmin;
    GRANT SELECT ON TABLE socialmerge TO ro;

    select increment_version_to(61) into ver;
  end if;

  if ver = 61
  then
    if not exists (
      select * from pg_tables
      where tablename = 'event_exceedingpingtime' )
    then
      CREATE TABLE event_exceedingpingtime
      (
        id bigint NOT NULL,
        sessiontoplayerid integer NOT NULL,
        
        typeid integer,
        starttime timestamp without time zone,
        finishtime timestamp without time zone,
        pingcount integer,
        pingtimemin integer,
        pingtimemax integer,
        pingtimeavg integer,
        
        CONSTRAINT event_exceedingpingtime_pkey PRIMARY KEY (id)
      );
      ALTER TABLE event_exceedingpingtime OWNER TO dbadmin;
      GRANT SELECT ON TABLE event_exceedingpingtime TO ro;
    end if;

    select increment_version_to(62) into ver;
  end if;

  if ver = 62
  then
    create table resourcelog
    (
      srctable character varying NOT NULL,
      srcid bigint NOT NULL,
      type character varying NOT NULL,
      value integer NOT NULL,
      gain boolean NOT NULL,
      player bigint NOT NULL,
      "timestamp" timestamp without time zone,
      datehierarchy integer,

      CONSTRAINT resourcelog_pkey PRIMARY KEY (srctable, srcid),
      CONSTRAINT resourcelog_player_fkey FOREIGN KEY (player)
          REFERENCES player (id) MATCH SIMPLE
          ON UPDATE NO ACTION ON DELETE NO ACTION
    );
    ALTER TABLE resourcelog OWNER TO dbadmin;
    GRANT SELECT ON TABLE resourcelog TO ro;

    CREATE INDEX idx_resourcelog_timestamp
      ON resourcelog
      USING btree (timestamp);

    insert into resourcelog (srctable, srcid, type, value, gain, player, timestamp)
    select 'sessiontoplayer', stp.id, 'silver', stp.silverchange, true, pc.player, gs.endtime
    from sessiontoplayer stp
      join gamesession gs on gs.id = stp.gamesession
      join playercharacter pc on pc.id = stp.playercharacter
    where silverchange != 0;

    insert into resourcelog (srctable, srcid, type, value, gain, player, timestamp)
    select 'movetobath', m.id, 'silver', -m.silver, false, pc.player, m.timestamp
    from movetobath m
      join playercharacter pc on pc.id = m.playercharacter
    where silver != 0;

    insert into resourcelog (srctable, srcid, type, value, gain, player, timestamp)
    select 'characterunlock', cu.id, 'silver', -cu.silver, false, pc.player, cu.timestamp
    from characterunlock cu
      join playercharacter pc on pc.id = cu.playercharacter
    where silver != 0;

    select increment_version_to(63) into ver;
  end if;

  if ver = 63
  then
    DROP FUNCTION fill_datehierarchy();
    
    ALTER TABLE socialsession      ADD COLUMN datehierarchy integer;
    ALTER TABLE mmakingsession     ADD COLUMN datehierarchy integer;
    ALTER TABLE movetobath         ADD COLUMN datehierarchy integer;
    ALTER TABLE playercharacter    ADD COLUMN datehierarchy integer;
    ALTER TABLE launcherstart      ADD COLUMN datehierarchy integer;
    ALTER TABLE launcherdstart     ADD COLUMN datehierarchy integer;
    ALTER TABLE launcherdend       ADD COLUMN datehierarchy integer;
    ALTER TABLE socialregister     ADD COLUMN datehierarchy integer;
    ALTER TABLE socialjoin         ADD COLUMN datehierarchy integer;
    ALTER TABLE socialmerge        ADD COLUMN datehierarchy integer;
    ALTER TABLE gm_unlockcharacter ADD COLUMN datehierarchy integer;
    ALTER TABLE gm_lockcharacter   ADD COLUMN datehierarchy integer;
    ALTER TABLE gm_addtalent       ADD COLUMN datehierarchy integer;
    ALTER TABLE gm_deletetalent    ADD COLUMN datehierarchy integer;
    ALTER TABLE gm_banplayer       ADD COLUMN datehierarchy integer;
    ALTER TABLE gm_unbanplayer     ADD COLUMN datehierarchy integer;
    ALTER TABLE gm_muteplayer      ADD COLUMN datehierarchy integer;
    ALTER TABLE gm_unmuteplayer    ADD COLUMN datehierarchy integer;
    ALTER TABLE gm_editplayer      ADD COLUMN datehierarchy integer;

    update socialsession      set datehierarchy = to_char(starttime, 'YYYYMMDD')::integer;
    update mmakingsession     set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update movetobath         set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update playercharacter    set datehierarchy = to_char(unlockdate, 'YYYYMMDD')::integer;
    update launcherstart      set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update launcherdstart     set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update launcherdend       set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update socialregister     set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update socialjoin         set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update socialmerge        set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update gm_unlockcharacter set datehierarchy = to_char(operationdate, 'YYYYMMDD')::integer;
    update gm_lockcharacter   set datehierarchy = to_char(operationdate, 'YYYYMMDD')::integer;
    update gm_addtalent       set datehierarchy = to_char(operationdate, 'YYYYMMDD')::integer;
    update gm_deletetalent    set datehierarchy = to_char(operationdate, 'YYYYMMDD')::integer;
    update gm_banplayer       set datehierarchy = to_char(operationdate, 'YYYYMMDD')::integer;
    update gm_unbanplayer     set datehierarchy = to_char(operationdate, 'YYYYMMDD')::integer;
    update gm_muteplayer      set datehierarchy = to_char(operationdate, 'YYYYMMDD')::integer;
    update gm_unmuteplayer    set datehierarchy = to_char(operationdate, 'YYYYMMDD')::integer;
    update gm_editplayer      set datehierarchy = to_char(operationdate, 'YYYYMMDD')::integer;

    ALTER TABLE socialsession      ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE movetobath         ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE gm_unlockcharacter ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE gm_lockcharacter   ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE gm_addtalent       ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE gm_deletetalent    ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE gm_banplayer       ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE gm_unbanplayer     ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE gm_muteplayer      ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE gm_unmuteplayer    ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE gm_editplayer      ALTER COLUMN datehierarchy SET NOT NULL;

    ALTER TABLE datehierarchy add CONSTRAINT datehierarchy_pkey PRIMARY KEY (id);

    ALTER TABLE gamesession add CONSTRAINT gamesession_datehierarchy_fkey FOREIGN KEY (timehierarchyid) REFERENCES datehierarchy (id);
    ALTER TABLE socialsession add CONSTRAINT socialsession_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE mmakingsession add CONSTRAINT mmakingsession_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE playercharacter add CONSTRAINT playercharacter_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE launcherstart add CONSTRAINT launcherstart_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE launcherdstart add CONSTRAINT launcherdstart_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE launcherdend add CONSTRAINT launcherdend_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE socialregister add CONSTRAINT socialregister_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE socialjoin add CONSTRAINT socialjoin_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE socialmerge add CONSTRAINT socialmerge_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE gm_unlockcharacter add CONSTRAINT gm_unlockcharacter_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE gm_lockcharacter add CONSTRAINT gm_lockcharacter_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE gm_addtalent add CONSTRAINT gm_addtalent_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE gm_deletetalent add CONSTRAINT gm_deletetalent_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE gm_banplayer add CONSTRAINT gm_banplayer_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE gm_unbanplayer add CONSTRAINT gm_unbanplayer_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE gm_muteplayer add CONSTRAINT gm_muteplayer_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE gm_unmuteplayer add CONSTRAINT gm_unmuteplayer_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE gm_editplayer add CONSTRAINT gm_editplayer_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);

    select increment_version_to(64) into ver;
  end if;

  if ver = 64
  then
    CREATE TABLE event_cheat
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,

      cheattype integer NOT NULL,
      clientip character varying NOT NULL,
      "timestamp" timestamp without time zone NOT NULL,
      
      CONSTRAINT cheat_pkey PRIMARY KEY (id)
    );
    ALTER TABLE event_cheat OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_cheat TO ro;

    select increment_version_to(65) into ver;
  end if;

  if ver = 65
  then
    ALTER TABLE event_disconnect        ADD COLUMN datehierarchy integer;
    ALTER TABLE event_exceedingsteptime ADD COLUMN datehierarchy integer;
    ALTER TABLE event_exceedingpingtime ADD COLUMN datehierarchy integer;

    update resourcelog             set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update event_disconnect        set datehierarchy = to_char(timestamp, 'YYYYMMDD')::integer;
    update event_exceedingsteptime set datehierarchy = to_char(starttime, 'YYYYMMDD')::integer;
    update event_exceedingpingtime set datehierarchy = to_char(starttime, 'YYYYMMDD')::integer;

    ALTER TABLE movetobath add CONSTRAINT movetobath_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE resourcelog add CONSTRAINT socialsession_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE event_disconnect add CONSTRAINT event_disconnect_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE event_exceedingsteptime add CONSTRAINT event_exceedingsteptime_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE event_exceedingpingtime add CONSTRAINT event_exceedingpingtime_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);

    select increment_version_to(66) into ver;
  end if;

  if ver = 66
  then
    CREATE TABLE ignoreadd
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      ignoredplayer bigint NOT NULL,
      reason character varying,
      "timestamp" timestamp without time zone NOT NULL,
      CONSTRAINT ignoreadd_pkey PRIMARY KEY (id),
      CONSTRAINT ignoreadd_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT ignoreadd_ignoredplayer_fkey FOREIGN KEY (ignoredplayer) REFERENCES player (id)
    );
    ALTER TABLE ignoreadd OWNER TO dbadmin;
    GRANT SELECT ON TABLE ignoreadd TO ro;

    CREATE TABLE ignoreremove
    (
      id bigserial NOT NULL,
      player bigint NOT NULL,
      ignoredplayer bigint NOT NULL,
      "timestamp" timestamp without time zone NOT NULL,
      CONSTRAINT ignoreremove_pkey PRIMARY KEY (id),
      CONSTRAINT ignoreremove_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT ignoreremove_ignoredplayer_fkey FOREIGN KEY (ignoredplayer) REFERENCES player (id)
    );
    ALTER TABLE ignoreremove OWNER TO dbadmin;
    GRANT SELECT ON TABLE ignoreremove TO ro;

    select increment_version_to(67) into ver;
  end if;

  if ver = 67
  then
    CREATE TABLE talentroll
    (
      id bigint NOT NULL,
      sessiontoplayer integer NOT NULL,
      talent integer NOT NULL,
      CONSTRAINT talentroll_pkey PRIMARY KEY (id),
      CONSTRAINT talentroll_sessiontoplayer_fkey FOREIGN KEY (sessiontoplayer) REFERENCES sessiontoplayer (id),
      CONSTRAINT talentroll_talent_fkey FOREIGN KEY (talent) REFERENCES talent (id)
    );
    ALTER TABLE talentroll OWNER TO dbadmin;
    GRANT SELECT ON TABLE talentroll TO ro;

    update datehierarchy
    set weekinmonth = trunc((dayinmonth-1)/7)+1
    where id != 0;

    select increment_version_to(68) into ver;
  end if;

  if ver = 68
  then
    alter table player add column banneduntil timestamp without time zone;

    select increment_version_to(69) into ver;
  end if;

  if ver = 69
  then
    if not exists (
      select *
      from pg_attribute a
        join pg_class p on p.oid = attrelid
      where attname = 'playerip'
        and relname = 'socialsession')
    then
      alter table socialsession add column playerip character varying;
    end if;

    select increment_version_to(70) into ver;
  end if;

  if ver = 70
  then
    CREATE INDEX idx_gamesession_datehierarchy ON gamesession (timehierarchyid);
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_playercharacter_fkey
      FOREIGN KEY (playercharacter) REFERENCES playercharacter (id);
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_gamesession_fkey
      FOREIGN KEY (gamesession) REFERENCES gamesession (id);
    ALTER TABLE sessiontoplayer DROP CONSTRAINT fkdd15357a43eaf094;
    ALTER TABLE sessiontoplayer DROP CONSTRAINT fkdd15357a5a94f0ab;
    CREATE INDEX idx_sessiontoplayer_playercharacter ON sessiontoplayer (playercharacter);
    CREATE INDEX idx_sessiontoplayer_gamesession ON sessiontoplayer (gamesession);

    ALTER TABLE event_damage ADD CONSTRAINT event_damage_sessiontoplayerid_fkey
      FOREIGN KEY (sessiontoplayerid) REFERENCES sessiontoplayer (id);
    ALTER TABLE event_exceedingsteptime ADD CONSTRAINT event_exceedingsteptime_sessiontoplayerid_fkey
      FOREIGN KEY (sessiontoplayerid) REFERENCES sessiontoplayer (id);
    ALTER TABLE event_exceedingpingtime ADD CONSTRAINT event_exceedingpingtime_sessiontoplayerid_fkey
      FOREIGN KEY (sessiontoplayerid) REFERENCES sessiontoplayer (id);
    ALTER TABLE event_disconnect ADD CONSTRAINT event_disconnect_sessiontoplayerid_fkey
      FOREIGN KEY (sessiontoplayerid) REFERENCES sessiontoplayer (id);
    ALTER TABLE event_cheat ADD CONSTRAINT event_cheat_sessiontoplayerid_fkey
      FOREIGN KEY (sessiontoplayerid) REFERENCES sessiontoplayer (id);    

    if not exists (select * from pg_class where relname = 'idx_event_talentused_sessiontoplayerid') then
      CREATE INDEX idx_event_talentused_sessiontoplayerid ON event_talentused (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_talentunlocked_sessiontoplayerid') then
      CREATE INDEX idx_event_talentunlocked_sessiontoplayerid ON event_talentunlocked (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_timeslice_sessiontoplayerid') then
      CREATE INDEX idx_event_timeslice_sessiontoplayerid ON event_timeslice (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_ressurection_sessiontoplayerid') then
      CREATE INDEX idx_event_ressurection_sessiontoplayerid ON event_ressurection (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_levelup_sessiontoplayerid') then
      CREATE INDEX idx_event_levelup_sessiontoplayerid ON event_levelup (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_buildingdestroyed_sessiontoplayerid') then
      CREATE INDEX idx_event_buildingdestroyed_sessiontoplayerid ON event_buildingdestroyed (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_achievement_sessiontoplayerid') then
      CREATE INDEX idx_event_achievement_sessiontoplayerid ON event_achievement (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_consumablebought_sessiontoplayerid') then
      CREATE INDEX idx_event_consumablebought_sessiontoplayerid ON event_consumablebought (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_consumableused_sessiontoplayerid') then
      CREATE INDEX idx_event_consumableused_sessiontoplayerid ON event_consumableused (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_cheatused_sessiontoplayerid') then
      CREATE INDEX idx_event_cheatused_sessiontoplayerid ON event_cheatused (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_flag_sessiontoplayerid') then
      CREATE INDEX idx_event_flag_sessiontoplayerid ON event_flag (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_naftaincome_sessiontoplayerid') then
      CREATE INDEX idx_event_naftaincome_sessiontoplayerid ON event_naftaincome (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_kill_sessiontoplayerid') then
      CREATE INDEX idx_event_kill_sessiontoplayerid ON event_kill (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_assist_sessiontoplayerid') then
      CREATE INDEX idx_event_assist_sessiontoplayerid ON event_assist (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_death_sessiontoplayerid') then
      CREATE INDEX idx_event_death_sessiontoplayerid ON event_death (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_damage_sessiontoplayerid') then
      CREATE INDEX idx_event_damage_sessiontoplayerid ON event_damage (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_debugvar_sessiontoplayerid') then
      CREATE INDEX idx_event_debugvar_sessiontoplayerid ON event_debugvar (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_exceedingsteptime_sessiontoplayerid') then
      CREATE INDEX idx_event_exceedingsteptime_sessiontoplayerid ON event_exceedingsteptime (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_exceedingpingtime_sessiontoplayerid') then
      CREATE INDEX idx_event_exceedingpingtime_sessiontoplayerid ON event_exceedingpingtime (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_disconnect_sessiontoplayerid') then
      CREATE INDEX idx_event_disconnect_sessiontoplayerid ON event_disconnect (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_cheat_sessiontoplayerid') then
      CREATE INDEX idx_event_cheat_sessiontoplayerid ON event_cheat (sessiontoplayerid);
    end if;
    if not exists (select * from pg_class where relname = 'idx_event_mg_session_sessiontoplayerid') then
      CREATE INDEX idx_event_mg_session_sessiontoplayerid ON event_mg_session (sessiontoplayerid);
    end if;

    ALTER TABLE ignoreremove ALTER COLUMN id DROP DEFAULT;
    DROP SEQUENCE ignoreremove_id_seq;

    select increment_version_to(71) into ver;
  end if;

  if ver = 71
  then
    if not exists (
      select * from pg_attribute a join pg_class p on p.oid = attrelid
      where relname = 'event_exceedingsteptime' and attname = 'rpcping')
    then
      ALTER TABLE event_exceedingsteptime ADD COLUMN rpcping integer;
      ALTER TABLE event_exceedingsteptime ADD COLUMN transportping integer;
    end if;
    
    if not exists (
      select * from pg_attribute a join pg_class p on p.oid = attrelid
      where relname = 'event_exceedingpingtime' and attname = 'pinglcount')
    then
      ALTER TABLE event_exceedingpingtime ADD COLUMN pinglcount integer;
      ALTER TABLE event_exceedingpingtime ADD COLUMN pingltimemin integer;
      ALTER TABLE event_exceedingpingtime ADD COLUMN pingltimemax integer;
      ALTER TABLE event_exceedingpingtime ADD COLUMN pingltimeavg integer;
      ALTER TABLE event_exceedingpingtime ADD COLUMN pinghcount integer;
      ALTER TABLE event_exceedingpingtime ADD COLUMN pinghtimemin integer;
      ALTER TABLE event_exceedingpingtime ADD COLUMN pinghtimemax integer;
      ALTER TABLE event_exceedingpingtime ADD COLUMN pinghtimeavg integer;
    end if;

    select increment_version_to(72) into ver;
  end if;

  if ver = 72
  then
    DROP FUNCTION fill_mg_session();
    DROP FUNCTION fill_mg_level();
    DROP FUNCTION fill_mg_ballschanged();
    DROP FUNCTION fill_mg_boostused();
    DROP FUNCTION fill_mg_zzboostused();
    DROP FUNCTION fill_mg_zzboostsuggested();

    DROP TABLE event_mg_zzboostused;
    DROP TABLE event_mg_zzboostsuggested;
    DROP TABLE tmp_mg2started;
    DROP TABLE tmp_mg2exit;
    DROP TABLE tmp_mg2levelstarted;
    DROP TABLE tmp_mg2levelwon;
    DROP TABLE tmp_mg2levelfailed;
    DROP TABLE tmp_mg2boostused;
    DROP TABLE tmp_mg2ballschanged;
    DROP TABLE tmp_mg2zzboostsuggested;
    DROP TABLE tmp_mg2zzboostused;

    ALTER TABLE event_mg_level ALTER COLUMN mgsessionid TYPE bigint;
    ALTER TABLE event_mg_boostused ALTER COLUMN mglevelid TYPE bigint;
    ALTER TABLE event_mg_ballschanged DROP CONSTRAINT event_mg_ballschanged_mglevelid_fkey;
    ALTER TABLE event_mg_ballschanged RENAME mglevelid TO mgsessionid;
    ALTER TABLE event_mg_ballschanged ALTER COLUMN mgsessionid TYPE bigint;
    ALTER TABLE event_mg_ballschanged ALTER COLUMN mgsessionid DROP NOT NULL;
    UPDATE event_mg_ballschanged b
    SET mgsessionid = (SELECT l.mgsessionid FROM event_mg_level l WHERE l.startid = b.mgsessionid);
    if not exists (SELECT * FROM event_mg_level WHERE mgsessionid is null)
    then
      ALTER TABLE event_mg_ballschanged ALTER COLUMN mgsessionid SET NOT NULL;
    end if;
    ALTER TABLE event_mg_ballschanged ADD CONSTRAINT event_mg_ballschanged_mgsessionid_fkey
      FOREIGN KEY (mgsessionid) REFERENCES event_mg_session (startid);

    CREATE INDEX idx_event_mg_level_mgsessionid ON event_mg_level (mgsessionid);
    CREATE INDEX idx_event_mg_boostused_mgsessionid ON event_mg_boostused (mglevelid);
    CREATE INDEX idx_event_mg_ballschanged_mgsessionid ON event_mg_ballschanged (mgsessionid);

    select increment_version_to(73) into ver;
  end if;

  if ver = 73
  then
    DROP TABLE resourcelog;

    CREATE TABLE resourcelog
    (
      id bigint NOT NULL,
      source character varying NOT NULL,
      gain boolean NOT NULL,
      player bigint NOT NULL,
      goldchange integer NOT NULL DEFAULT 0,
      silverchange integer NOT NULL DEFAULT 0,
      perlchange integer NOT NULL DEFAULT 0,
      populationchange integer NOT NULL DEFAULT 0,
      resource1change integer NOT NULL DEFAULT 0,
      resource2change integer NOT NULL DEFAULT 0,
      resource3change integer NOT NULL DEFAULT 0,
      goldtotal integer NOT NULL DEFAULT 0,
      silvertotal integer NOT NULL DEFAULT 0,
      perltotal integer NOT NULL DEFAULT 0,
      populationtotal integer NOT NULL DEFAULT 0,
      resource1total integer NOT NULL DEFAULT 0,
      resource2total integer NOT NULL DEFAULT 0,
      resource3total integer NOT NULL DEFAULT 0,
      "timestamp" timestamp without time zone,
      datehierarchy integer,  
      CONSTRAINT resourcelog_pkey PRIMARY KEY (id),
      CONSTRAINT resourcelog_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT resourcelog_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE gamesession OWNER TO dbadmin;
    GRANT SELECT ON TABLE gamesession TO ro;

    ALTER TABLE sessiontoplayer ADD COLUMN resourcelog bigint;
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_resourcelog_fkey 
      FOREIGN KEY (resourcelog) REFERENCES resourcelog (id);
    ALTER TABLE sessiontoplayer DROP COLUMN silverchange;
    ALTER TABLE sessiontoplayer DROP COLUMN silvertotal;

    ALTER TABLE characterunlock ADD COLUMN resourcelog bigint;
    ALTER TABLE characterunlock ADD CONSTRAINT characterunlock_resourcelog_fkey
      FOREIGN KEY (resourcelog) REFERENCES resourcelog (id);
    ALTER TABLE characterunlock DROP COLUMN silver;

    ALTER TABLE movetobath ADD COLUMN resourcelog bigint;
    ALTER TABLE movetobath ADD CONSTRAINT movetobath_resourcelog_fkey
      FOREIGN KEY (resourcelog) REFERENCES resourcelog (id);
    ALTER TABLE movetobath DROP COLUMN silver;

    select increment_version_to(74) into ver;
  end if;

  if ver = 74
  then
    ALTER TABLE resourcelog ADD COLUMN buildingname character varying;

    select increment_version_to(75) into ver;
  end if;

  if ver = 75
  then
    ALTER TABLE event_damage ADD COLUMN datehierarchy integer NOT NULL DEFAULT 0;
    ALTER TABLE event_damage ALTER COLUMN datehierarchy DROP DEFAULT;
    ALTER TABLE event_damage ADD CONSTRAINT event_damage_datehierarchy_fkey
      FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    
    UPDATE event_damage e
    SET datehierarchy = (select gs.timehierarchyid
                         from gamesession gs join sessiontoplayer stp on stp.gamesession = gs.id
                         where stp.id = e.sessiontoplayerid);
    
    CREATE INDEX idx_event_damage_datehierarchy ON event_damage (datehierarchy);
    
    CREATE TABLE sys_aggregation_ranges
    (
      tablename character varying NOT NULL,
      lastid bigint,
      CONSTRAINT sys_aggregation_ranges_pkey PRIMARY KEY (tablename)
    );
    ALTER TABLE sys_aggregation_ranges OWNER to dbadmin;
    INSERT INTO sys_aggregation_ranges VALUES ('event_damage', 0);
    INSERT INTO sys_aggregation_ranges VALUES ('event_naftaincome', 0);
    INSERT INTO sys_aggregation_ranges VALUES ('event_talentused', 0);

    CREATE TABLE event_damage_agg_building
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      buildingid integer NOT NULL,
      dealt boolean NOT NULL,
      physicaldamage real,
      magicaldamage real,
      puredamage real,
      CONSTRAINT event_damage_agg_building_unique UNIQUE (datehierarchy, characterid, buildingid, dealt),
      CONSTRAINT event_damage_agg_building_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_damage_agg_building_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
      CONSTRAINT event_damage_agg_building_buildingid_fkey FOREIGN KEY (buildingid) REFERENCES building (id)
    );
    ALTER TABLE event_damage_agg_building OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage_agg_building TO ro;

    CREATE TABLE event_damage_agg_creature
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      creatureid integer NOT NULL,
      dealt boolean NOT NULL,
      physicaldamage real,
      magicaldamage real,
      puredamage real,
      CONSTRAINT event_damage_agg_creature_unique UNIQUE (datehierarchy, characterid, creatureid, dealt),
      CONSTRAINT event_damage_agg_creature_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_damage_agg_creature_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
      CONSTRAINT event_damage_agg_creature_creatureid_fkey FOREIGN KEY (creatureid) REFERENCES creature (id)
    );
    ALTER TABLE event_damage_agg_creature OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage_agg_creature TO ro;

    CREATE TABLE event_damage_agg_unittype
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      unittype integer NOT NULL,
      dealt boolean NOT NULL,
      physicaldamage real,
      magicaldamage real,
      puredamage real,
      CONSTRAINT event_damage_agg_unittype_unique UNIQUE (datehierarchy, characterid, unittype, dealt),
      CONSTRAINT event_damage_agg_unittype_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_damage_agg_unittype_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
      CONSTRAINT event_damage_agg_unittype_unittype_fkey FOREIGN KEY (unittype) REFERENCES unittype (id)
    );
    ALTER TABLE event_damage_agg_unittype OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage_agg_unittype TO ro;

    CREATE TABLE event_damage_agg_character
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      opponentcharacterid integer NOT NULL,
      dealt boolean NOT NULL,
      physicaldamage real,
      magicaldamage real,
      puredamage real,
      CONSTRAINT event_damage_agg_character_unique UNIQUE (datehierarchy, opponentcharacterid, characterid, dealt),
      CONSTRAINT event_damage_agg_character_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_damage_agg_character_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
      CONSTRAINT event_damage_agg_character_opponentcharacterid_fkey FOREIGN KEY (opponentcharacterid) REFERENCES character (id)
    );
    ALTER TABLE event_damage_agg_character OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage_agg_character TO ro;

    CREATE OR REPLACE FUNCTION aggregate_event_damage()
      RETURNS VOID AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      r RECORD;
      rowsbuffersize INTEGER := 100000;
      tmpid INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'event_damage';

      SELECT coalesce(max(id), 0) INTO finishid
      FROM event_damage;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;

      WHILE startid < finishid LOOP
        RAISE NOTICE 'aggregating % rows...',
          (SELECT COUNT(*) FROM event_damage WHERE id > startid AND id <= startid+rowsbuffersize);

        -- aggregate buildings
        FOR r IN (
          SELECT e.datehierarchy, e.characterid, e.opponentid, e.dealt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage e
            JOIN sessiontoplayer stp ON stp.id = e.sessiontoplayerid
            JOIN gamesession gs ON gs.id = stp.gamesession
          WHERE e.id > startid AND e.id <= startid + rowsbuffersize
            AND e.unittype in (6, 7, 8) -- Tower, Building, MainBuilding
            AND gs.sessiontype != 5
          GROUP BY e.datehierarchy, e.characterid, e.opponentid, e.dealt )
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_building e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.buildingid = r.opponentid
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_building e
            SET physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.buildingid = r.opponentid
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_building (datehierarchy, characterid, buildingid, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.characterid, r.opponentid, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        -- aggregate characters
        FOR r IN (
          SELECT e.datehierarchy, e.characterid, e.opponentid, e.dealt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage e
            JOIN sessiontoplayer stp ON stp.id = e.sessiontoplayerid
            JOIN gamesession gs ON gs.id = stp.gamesession
          WHERE e.id > startid AND e.id <= startid + rowsbuffersize
            AND unittype in (0, 1) -- HeroMale, HeroFemale
            AND gs.sessiontype != 5
          GROUP BY e.datehierarchy, e.characterid, e.opponentid, e.dealt )
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_character e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.opponentcharacterid = r.opponentid
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_character e
            SET physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.opponentcharacterid = r.opponentid
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_character (datehierarchy, characterid, opponentcharacterid, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.characterid, r.opponentid, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        -- aggregate creature
        FOR r IN (
          SELECT e.datehierarchy, e.characterid, e.opponentid, e.dealt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage e
            JOIN sessiontoplayer stp ON stp.id = e.sessiontoplayerid
            JOIN gamesession gs ON gs.id = stp.gamesession
          WHERE e.id > startid AND e.id <= startid + rowsbuffersize
            AND unittype in (2, 3, 4, 5, 18, 19) -- Summon, Creep, SiegeCreep, NeutralCreep, NeutralChampion, NeutralBoss
            AND gs.sessiontype != 5
          GROUP BY e.datehierarchy, e.characterid, e.opponentid, e.dealt )
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_creature e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.creatureid = r.opponentid
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_creature e
            SET physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.creatureid = r.opponentid
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_creature (datehierarchy, characterid, creatureid, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.characterid, r.opponentid, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        -- aggregate unittype
        FOR r IN (
          SELECT e.datehierarchy, e.characterid, e.unittype, e.dealt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage e
            JOIN sessiontoplayer stp ON stp.id = e.sessiontoplayerid
            JOIN gamesession gs ON gs.id = stp.gamesession
          WHERE e.id > startid AND e.id <= startid + rowsbuffersize
            AND gs.sessiontype != 5
          GROUP BY e.datehierarchy, e.characterid, e.unittype, e.dealt )
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_unittype e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.unittype = r.unittype
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_unittype e
            SET physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.unittype = r.unittype
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_unittype (datehierarchy, characterid, unittype, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.characterid, r.unittype, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        startid := startid + rowsbuffersize;
      END LOOP;

      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'event_damage';

      RAISE NOTICE 'finished!';
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_event_damage() OWNER TO dbadmin;

    -----------------------------------------------------------------------------------------
    ALTER TABLE event_naftaincome ADD COLUMN datehierarchy integer NOT NULL DEFAULT 0;
    ALTER TABLE event_naftaincome ALTER COLUMN datehierarchy DROP DEFAULT;
    ALTER TABLE event_naftaincome ADD CONSTRAINT event_naftaincome_datehierarchy_fkey
      FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);

    UPDATE event_naftaincome e
    SET datehierarchy = (select gs.timehierarchyid
                         from gamesession gs join sessiontoplayer stp on stp.gamesession = gs.id
                         where stp.id = e.sessiontoplayerid);

    CREATE INDEX idx_event_naftaincome_datehierarchy ON event_naftaincome (datehierarchy);

    CREATE TABLE event_naftaincome_agg_minute
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      incomefrom character varying NOT NULL,
      minute integer NOT NULL,
      naftaforkill integer,
      naftaspecforkill integer,
      teamnaftaforkill integer,
      nafta integer,
      CONSTRAINT event_naftaincome_agg_minute_unique UNIQUE (datehierarchy, characterid, incomefrom, minute),
      CONSTRAINT event_naftaincome_agg_minute_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_naftaincome_agg_minute_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id)
    );
    ALTER TABLE event_naftaincome_agg_minute OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_naftaincome_agg_minute TO ro;

    CREATE OR REPLACE FUNCTION aggregate_event_naftaincome()
      RETURNS VOID AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      r RECORD;
      rowsbuffersize INTEGER := 100000;
      tmpid INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'event_naftaincome';

      SELECT coalesce(max(id), 0) INTO finishid
      FROM event_naftaincome;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;

      WHILE startid < finishid LOOP
        RAISE NOTICE 'aggregating % rows...',
          (SELECT COUNT(*) FROM event_naftaincome WHERE id > startid AND id <= startid+rowsbuffersize);

        FOR r IN (
          SELECT e.datehierarchy, characterid, step/600+1 as minute,
                 CASE WHEN incomefrom = 0 THEN 'hero'
                      WHEN incomefrom = 1 THEN 'creature'
                      WHEN incomefrom = 2 THEN 'building'
                      WHEN incomefrom = 3 THEN 'talent'
                      WHEN incomefrom = 4 THEN 'impulsivebuff'
                      WHEN incomefrom = 5 THEN 'minigame'
                      ELSE 'undefined' END as strincomefrom,
                 SUM(naftaforkill) nfk, SUM(naftaspecforkill) nsfk, SUM(teamnaftaforkill) tnfk, SUM(nafta) n
          FROM event_naftaincome e
            JOIN sessiontoplayer stp ON stp.id = e.sessiontoplayerid
            JOIN gamesession gs ON gs.id = stp.gamesession       
          WHERE e.id > startid AND e.id <= startid + rowsbuffersize
            AND gs.sessiontype != 5
          GROUP BY e.datehierarchy, characterid, step/600+1,
                      CASE WHEN incomefrom = 0 THEN 'hero'
                      WHEN incomefrom = 1 THEN 'creature'
                      WHEN incomefrom = 2 THEN 'building'
                      WHEN incomefrom = 3 THEN 'talent'
                      WHEN incomefrom = 4 THEN 'impulsivebuff'
                      WHEN incomefrom = 5 THEN 'minigame'
                      ELSE 'undefined' END )
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_naftaincome_agg_minute e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.incomefrom = r.strincomefrom
              AND e.minute = r.minute )
          THEN
            UPDATE event_naftaincome_agg_minute e
            SET naftaforkill = naftaforkill + r.nfk,
                naftaspecforkill = naftaspecforkill + r.nsfk,
                teamnaftaforkill = teamnaftaforkill + r.tnfk,
                nafta = nafta + r.n
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.incomefrom = r.strincomefrom
              AND e.minute = r.minute;
          ELSE
            INSERT INTO event_naftaincome_agg_minute (datehierarchy, characterid, incomefrom, minute, naftaforkill, naftaspecforkill, teamnaftaforkill, nafta)
            VALUES (r.datehierarchy, r.characterid, r.strincomefrom, r.minute, r.nfk, r.nsfk, r.tnfk, r.n);
          END IF;
        END LOOP;

        startid := startid + rowsbuffersize;
      END LOOP;

      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'event_naftaincome';

      RAISE NOTICE 'finished!';
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_event_naftaincome() OWNER TO dbadmin;

    -----------------------------------------------------------------------------------------
    ALTER TABLE event_talentused ADD COLUMN datehierarchy integer NOT NULL DEFAULT 0;
    ALTER TABLE event_talentused ALTER COLUMN datehierarchy DROP DEFAULT;
    ALTER TABLE event_talentused ADD CONSTRAINT event_talentused_datehierarchy_fkey
      FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);

    UPDATE event_talentused e
    SET datehierarchy = (select gs.timehierarchyid
                         from gamesession gs join sessiontoplayer stp on stp.gamesession = gs.id
                         where stp.id = e.sessiontoplayerid);

    CREATE INDEX idx_event_talentused_datehierarchy ON event_talentused (datehierarchy);

    CREATE TABLE event_talentused_agg_talent
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      talentid integer NOT NULL,
      usagecount integer,
      CONSTRAINT event_talentused_agg_talent_unique UNIQUE (datehierarchy, characterid, talentid),
      CONSTRAINT event_talentused_agg_talent_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_talentused_agg_talent_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
      CONSTRAINT event_talentused_agg_talent_talentid_fkey FOREIGN KEY (talentid) REFERENCES talent (id)
    );
    ALTER TABLE event_talentused_agg_talent OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_talentused_agg_talent TO ro;

    CREATE OR REPLACE FUNCTION aggregate_event_talentused()
      RETURNS VOID AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      r RECORD;
      rowsbuffersize INTEGER := 100000;
      tmpid INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'event_talentused';

      SELECT coalesce(max(id), 0) INTO finishid
      FROM event_talentused;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;

      WHILE startid < finishid LOOP
        RAISE NOTICE 'aggregating % rows...',
          (SELECT COUNT(*) FROM event_talentused WHERE id > startid AND id <= startid+rowsbuffersize);

        FOR r IN (
          SELECT e.datehierarchy, characterid, talentid, count(*) as cnt
          FROM event_talentused e
            JOIN sessiontoplayer stp ON stp.id = e.sessiontoplayerid
            JOIN gamesession gs ON gs.id = stp.gamesession       
          WHERE e.id > startid AND e.id <= startid + rowsbuffersize
            AND gs.sessiontype != 5
          GROUP BY datehierarchy, characterid, talentid )
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_talentused_agg_talent e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.talentid = r.talentid)
          THEN
            UPDATE event_talentused_agg_talent e
            SET usagecount = usagecount + r.cnt
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.talentid = r.talentid;
          ELSE
            INSERT INTO event_talentused_agg_talent (datehierarchy, characterid, talentid, usagecount)
            VALUES (r.datehierarchy, r.characterid, r.talentid, r.cnt);
          END IF;
        END LOOP;

        startid := startid + rowsbuffersize;
      END LOOP;

      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'event_talentused';

      RAISE NOTICE 'finished!';
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_event_talentused() OWNER TO dbadmin;

    select increment_version_to(76) into ver;
  end if;

  if ver = 76
  then
    CREATE OR REPLACE FUNCTION update_mgsession(p_id bigint, p_step bigint, p_stpid bigint)
    RETURNS VOID AS 
    $$
    BEGIN
      UPDATE event_mg_session
      SET finishid = p_id,
          finishstep = p_step
      WHERE startid = ( SELECT MAX(startid) FROM event_mg_session
                        WHERE sessiontoplayerid = p_stpid
                          AND startstep <= p_step );
    END;
    $$ LANGUAGE plpgsql;

    CREATE OR REPLACE FUNCTION update_mglevel(p_id bigint, p_step bigint, p_stpid bigint, p_success boolean)
    RETURNS VOID AS 
    $$
    BEGIN
      UPDATE event_mg_level
      SET finishid = p_id,
          finishstep = p_step,
          success = p_success
      WHERE startid = (SELECT MAX(l.startid) FROM event_mg_level l
                         JOIN event_mg_session s ON s.startid = l.mgsessionid
                       WHERE s.sessiontoplayerid = p_stpid
                         AND s.startstep <= p_step 
                         AND l.startstep <= p_step );
    END;
    $$ LANGUAGE plpgsql;

    select increment_version_to(77) into ver;
  end if;

  if ver = 77 
  then
    ALTER TABLE playercharacter ADD COLUMN rating INTEGER;
    UPDATE playercharacter pc
    SET rating = COALESCE((SELECT ratingtotal FROM sessiontoplayer
                           WHERE id = (SELECT MAX(id) FROM sessiontoplayer
                                       WHERE playercharacter = pc.id AND ratingtotal > 0)), 0);
    ALTER TABLE playercharacter ALTER COLUMN rating SET NOT NULL;
    ALTER TABLE player DROP COLUMN rating;

    CREATE TABLE playercharacter_ratingbypush
    (
      playercharacter integer NOT NULL,
      push character varying NOT NULL,
      rating integer NOT NULL,
      reliability integer NOT NULL,
      CONSTRAINT playercharacter_ratingbypush_unique UNIQUE (playercharacter, push),
      CONSTRAINT playercharacter_ratingbypush_playercharacter FOREIGN KEY (playercharacter) REFERENCES playercharacter (id)
    );
    ALTER TABLE playercharacter_ratingbypush OWNER TO dbadmin;
    GRANT SELECT ON TABLE playercharacter_ratingbypush TO ro;

    CREATE OR REPLACE FUNCTION fill_playercharacter_ratingbypush(stpid integer)
      RETURNS VOID AS
    $$
    DECLARE
      p character varying;
      data record;
      mindh integer := 0;
    BEGIN
      IF EXISTS (SELECT 1 FROM sessiontoplayer where id = stpid )
      THEN 
        SELECT timehierarchyid INTO mindh
        FROM gamesession gs 
          JOIN sessiontoplayer stp ON stp.gamesession = gs.id
        WHERE stp.id = stpid;
      END IF;

      FOR p IN (SELECT DISTINCT d.push FROM datehierarchy d WHERE d.push IS NOT NULL AND d.id >= mindh)
      LOOP
        FOR data IN (
          SELECT stp.playercharacter as pc,
                 (SELECT stp2.ratingtotal FROM sessiontoplayer stp2 WHERE stp2.id = MAX(stp.id)) as rt,
                 (SELECT stp2.reliabilitytotal FROM sessiontoplayer stp2 WHERE stp2.id = MAX(stp.id)) as rl
          FROM sessiontoplayer stp
            JOIN gamesession gs on gs.id = stp.gamesession
            JOIN datehierarchy d on d.id = gs.timehierarchyid
          WHERE d.push = p
            AND stp.ratingtotal > 0
            AND stp.id >= stpid
          GROUP BY stp.playercharacter)
        LOOP
          IF EXISTS (SELECT 1 FROM playercharacter_ratingbypush WHERE playercharacter = data.pc AND push = p)
          THEN
            UPDATE playercharacter_ratingbypush
            SET rating = data.rt, reliability = data.rl
            WHERE playercharacter = data.pc AND push = p;
          ELSE
            INSERT INTO playercharacter_ratingbypush 
            VALUES (data.pc, p, data.rt, data.rl);
          END IF;
        END LOOP;
      END LOOP;
    END;
    $$ LANGUAGE plpgsql;

    PERFORM fill_playercharacter_ratingbypush(0);

    select increment_version_to(78) into ver;
  end if;

  if ver = 78
  then
    if not exists (
      select * from pg_tables
      where tablename = 'offlineevent' )
    then
      CREATE TABLE offlineevent
      (
        id bigint NOT NULL,
        playerid bigint NOT NULL,
        persistentid bigint NOT NULL,
        code int NOT NULL,
        auxdata int NOT NULL,
        timestamp timestamp NOT NULL,
        datehierarchy integer,
        CONSTRAINT offlineevent_pkey PRIMARY KEY (id),
        CONSTRAINT offlineevent_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
      );
      ALTER TABLE offlineevent OWNER TO dbadmin;
      GRANT SELECT ON TABLE offlineevent TO ro;

      CREATE INDEX idx_offlineevent_datehierarchy ON offlineevent (datehierarchy);
    end if;

    select increment_version_to(79) into ver;
  end if;

  if ver = 79
  then
    if not exists (
      select * from pg_attribute a join pg_class p on p.oid = attrelid
      where relname = 'socialregister' and attname = 'muid')
    then
      ALTER TABLE socialregister ADD COLUMN muid character varying;
    end if;   

    select increment_version_to(80) into ver;
  end if;

  if ver = 80
  then
    ALTER TABLE mmakingsession ADD COLUMN manoeuvresfaction INTEGER NOT NULL DEFAULT -1;
    ALTER TABLE mmakingsession ALTER COLUMN manoeuvresfaction DROP DEFAULT;

    select increment_version_to(81) into ver;
  end if;

  if ver = 81
  then
    if not exists (
      select * from pg_tables
      where tablename = 'launcherevents' )
    then
      CREATE TABLE launcherevents
      (
        id bigint NOT NULL,
        playerid bigint,
        muid character varying,
        eventflags bigint,
        "timestamp" timestamp without time zone,
        datehierarchy integer,
        CONSTRAINT launcherevents_pkey PRIMARY KEY (id),
        CONSTRAINT launcherevents_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
      );
      ALTER TABLE launcherevents OWNER TO dbadmin;
      GRANT SELECT ON TABLE launcherevents TO ro;
    end if;

    if not exists (
      select * from pg_attribute a join pg_class p on p.oid = attrelid
      where relname in ('launcherstart','launcherdstart','launcherdend') and attname = 'playerid')
    then
      ALTER TABLE launcherstart  ADD COLUMN playerid bigint;
      ALTER TABLE launcherdstart ADD COLUMN playerid bigint;
      ALTER TABLE launcherdend   ADD COLUMN playerid bigint;
    end if;

    select increment_version_to(82) into ver;
  end if;

  if ver = 82
  then
    ALTER TABLE mmakingplayer ADD COLUMN "timestamp" TIMESTAMP;
    ALTER TABLE mmakingplayer ADD COLUMN datehierarchy INTEGER;    

    UPDATE mmakingplayer mp
    SET timestamp = (SELECT timestamp FROM mmakingsession ms
                     WHERE ms.id = mp.mmakingsession)
    WHERE mp.mmakingsession IS NOT NULL;

    DO $$
    DECLARE
      t timestamp;
      r record;
    BEGIN
      SELECT min(timestamp) INTO t FROM mmakingsession;
      FOR r IN (SELECT * FROM mmakingplayer ORDER BY id)
      LOOP
        IF (r.mmakingsession IS NULL) THEN
          UPDATE mmakingplayer
          SET timestamp = t
          WHERE id = r.id;
        ELSE
          t := r.timestamp;
        END IF;
      END LOOP;
    END;
    $$ LANGUAGE plpgsql;

    UPDATE mmakingplayer mp
    SET datehierarchy = to_char(timestamp, 'YYYYMMDD')::INTEGER;

    ALTER TABLE mmakingplayer ALTER COLUMN "timestamp" SET NOT NULL;
    ALTER TABLE mmakingplayer ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE mmakingplayer ADD CONSTRAINT mmakingplayer_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);

    ALTER TABLE mmakingplayer ADD COLUMN force REAL NOT NULL DEFAULT 0;
    ALTER TABLE mmakingplayer ALTER COLUMN force DROP DEFAULT;
    ALTER TABLE playercharacter_ratingbypush ADD COLUMN force REAL NOT NULL DEFAULT 0;
    ALTER TABLE playercharacter_ratingbypush ALTER COLUMN force DROP DEFAULT;

    CREATE OR REPLACE FUNCTION fill_playercharacter_ratingbypush(stpid integer)
      RETURNS VOID AS
    $$
    DECLARE
      p character varying;
      data record;
      mindh integer := 0;
      rt integer;
      rl integer;
      f real;
    BEGIN
      IF EXISTS (SELECT 1 FROM sessiontoplayer where id = stpid )
      THEN 
        SELECT timehierarchyid INTO mindh
        FROM gamesession gs 
          JOIN sessiontoplayer stp ON stp.gamesession = gs.id
        WHERE stp.id = stpid;
      END IF;

      FOR p IN (SELECT DISTINCT d.push FROM datehierarchy d WHERE d.push IS NOT NULL AND d.id >= mindh)
      LOOP
        FOR data IN (
          SELECT stp.playercharacter as pc,
                 MAX(stp.id) as maxstpid,
                 (SELECT gs2.persistentid 
                  FROM sessiontoplayer stp2 JOIN gamesession gs2 on gs2.id = stp2.gamesession
                  WHERE stp2.id = MAX(stp.id)) as persistid
          FROM sessiontoplayer stp
            JOIN gamesession gs on gs.id = stp.gamesession
            JOIN datehierarchy d on d.id = gs.timehierarchyid
          WHERE d.push = p
            AND stp.ratingtotal > 0
            AND stp.id >= stpid
          GROUP BY stp.playercharacter)
        LOOP
          SELECT ratingtotal, reliabilitytotal INTO rt, rl
          FROM sessiontoplayer WHERE id = data.maxstpid;

          SELECT mp.force INTO f
          FROM mmakingsession ms 
            JOIN mmakingplayer mp on mp.mmakingsession = ms.id
          WHERE ms.persistentid = data.persistid
            AND mp.playercharacter = data.pc;
          IF NOT FOUND THEN f := 0; END IF;

          IF EXISTS (SELECT 1 FROM playercharacter_ratingbypush WHERE playercharacter = data.pc AND push = p)
          THEN
            UPDATE playercharacter_ratingbypush
            SET rating = rt, reliability = rl, force = f
            WHERE playercharacter = data.pc AND push = p;
          ELSE
            INSERT INTO playercharacter_ratingbypush 
            VALUES (data.pc, p, rt, rl, f);
          END IF;
        END LOOP;
      END LOOP;
    END;
    $$ LANGUAGE plpgsql;

    select increment_version_to(83) into ver;
  end if;

  if ver = 83
  then
    ALTER TABLE sessiontoplayer ADD COLUMN faction INTEGER;
    UPDATE sessiontoplayer SET faction = side::INTEGER;
    ALTER TABLE sessiontoplayer DROP COLUMN side;

    CREATE TABLE factionchange
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      oldfaction integer,
      newfaction integer,
      resourcelog bigint,
      "timestamp" timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT factionchange_pkey PRIMARY KEY (id),
      CONSTRAINT factionchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT factionchange_resourcelog_fkey FOREIGN KEY (resourcelog) REFERENCES resourcelog (id),
      CONSTRAINT factionchange_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE factionchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE factionchange TO ro;

    UPDATE resourcelog
    SET source = 'factionchange'
    WHERE source = 'changefraction';

    select increment_version_to(84) into ver;
  end if;

  if ver = 84
  then
    ALTER TABLE sessiontoplayer ADD COLUMN force REAL DEFAULT 0;
    ALTER TABLE sessiontoplayer ALTER COLUMN force DROP DEFAULT;

    select increment_version_to(85) into ver;
  end if;

  if ver = 85
  then
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_mmakingsession_datehierarchy') THEN
      CREATE INDEX idx_mmakingsession_datehierarchy ON mmakingsession (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_resourcelog_player') THEN
      CREATE INDEX idx_resourcelog_player ON resourcelog (player);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_resourcelog_datehierarchy') THEN
      CREATE INDEX idx_resourcelog_datehierarchy ON resourcelog (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_socialsession_player') THEN
      CREATE INDEX idx_socialsession_player  ON socialsession (player);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_socialsession_datehierarchy') THEN
      CREATE INDEX idx_socialsession_datehierarchy ON socialsession (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_launcherstart_datehierarchy') THEN
      CREATE INDEX idx_launcherstart_datehierarchy ON launcherstart (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_launcherdstart_datehierarchy') THEN
      CREATE INDEX idx_launcherdstart_datehierarchy ON launcherdstart (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_launcherdend_datehierarchy') THEN
      CREATE INDEX idx_launcherdend_datehierarchy ON launcherdend (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_socialregister_datehierarchy') THEN
      CREATE INDEX idx_socialregister_datehierarchy ON socialregister (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_socialjoin_datehierarchy') THEN
      CREATE INDEX idx_socialjoin_datehierarchy ON socialjoin (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_socialmerge_datehierarchy') THEN
      CREATE INDEX idx_socialmerge_datehierarchy ON socialmerge (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_gm_unlockcharacter_datehierarchy') THEN
      CREATE INDEX idx_gm_unlockcharacter_datehierarchy ON gm_unlockcharacter (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_gm_lockcharacter_datehierarchy') THEN
      CREATE INDEX idx_gm_lockcharacter_datehierarchy ON gm_lockcharacter (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_gm_addtalent_datehierarchy') THEN
      CREATE INDEX idx_gm_addtalent_datehierarchy ON gm_addtalent (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_gm_deletetalent_datehierarchy') THEN
      CREATE INDEX idx_gm_deletetalent_datehierarchy ON gm_deletetalent (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_gm_banplayer_datehierarchy') THEN
      CREATE INDEX idx_gm_banplayer_datehierarchy ON gm_banplayer (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_gm_unbanplayer_datehierarchy') THEN
      CREATE INDEX idx_gm_unbanplayer_datehierarchy ON gm_unbanplayer (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_gm_muteplayer_datehierarchy') THEN
      CREATE INDEX idx_gm_muteplayer_datehierarchy ON gm_muteplayer (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_gm_unmuteplayer_datehierarchy') THEN
      CREATE INDEX idx_gm_unmuteplayer_datehierarchy ON gm_unmuteplayer (datehierarchy);
    END IF;
    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_gm_editplayer_datehierarchy') THEN
      CREATE INDEX idx_gm_editplayer_datehierarchy ON gm_editplayer (datehierarchy);
    END IF;

    DROP TABLE player_tags;
    DROP TABLE player_tags_generated;
    DROP TABLE tag;
    DROP FUNCTION player_has_tag(character varying, character varying);
    DROP FUNCTION player_set_tag(character varying, character varying);
    DROP FUNCTION player_refresh_tags();

    select increment_version_to(86) into ver;
  end if;

  if ver = 86
  then
    ALTER TABLE mmakingplayer ADD COLUMN losestreak INTEGER NOT NULL DEFAULT 0;
    ALTER TABLE mmakingplayer ALTER COLUMN losestreak DROP DEFAULT;

    select increment_version_to(87) into ver;
  end if;

  if ver = 87
  then
    ALTER TABLE mmakingplayer ADD COLUMN famelevel INTEGER NOT NULL DEFAULT 0;
    ALTER TABLE mmakingplayer ALTER COLUMN famelevel DROP DEFAULT;

    select increment_version_to(88) into ver;
  end if;

  if ver = 88
  then
    CREATE TABLE quest
    (
      id integer NOT NULL,
      questid character varying NOT NULL,
      "name" character varying,
      deleted boolean NOT NULL DEFAULT false,
      CONSTRAINT quest_pkey PRIMARY KEY (id)
    );
    ALTER TABLE quest OWNER TO dbadmin;
    GRANT SELECT ON TABLE quest TO ro;

    CREATE TABLE questchange
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      quest integer NOT NULL,
      changetype integer NOT NULL,
      "timestamp" timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT questchange_pkey PRIMARY KEY (id),
      CONSTRAINT questchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT questchange_quest_fkey FOREIGN KEY (quest) REFERENCES quest (id),
      CONSTRAINT questchange_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE questchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE factionchange TO ro;

    select increment_version_to(89) into ver;
  end if;

  if ver = 89
  then
    ALTER TABLE gamesession ADD COLUMN surrendervote INTEGER NOT NULL DEFAULT 0;
    ALTER TABLE gamesession ALTER COLUMN surrendervote DROP DEFAULT;

    select increment_version_to(90) into ver;
  end if;

  if ver = 90
  then
    DELETE FROM talent WHERE name like 'Автоатака%';

    select increment_version_to(91) into ver;
  end if;

  if ver = 91
  then
    ALTER TABLE ignoreadd DROP CONSTRAINT ignoreadd_ignoredplayer_fkey;
    ALTER TABLE ignoreremove DROP CONSTRAINT ignoreremove_ignoredplayer_fkey;

    select increment_version_to(92) into ver;
  end if;

  if ver = 92
  then
    CREATE SCHEMA partitions AUTHORIZATION dbadmin;
    GRANT ALL ON SCHEMA partitions TO ro;

    CREATE OR REPLACE FUNCTION partition_every_day (parentoid oid, datehierarchy integer)
      RETURNS void AS
    $$
    DECLARE
      parent text = parentoid::regclass;
      child  text = parent||'_'||datehierarchy;
      script text;
      r record;
    BEGIN
      -- check if table already exists
      PERFORM ('partitions.'||child)::regclass;
      
    EXCEPTION
      WHEN undefined_table THEN
      
        -- create child table
        EXECUTE 
        'CREATE TABLE partitions.'||child||' '||
        '( CHECK (datehierarchy = '||datehierarchy||')) '||
        'INHERITS ('||parent||')';
        EXECUTE 'ALTER TABLE partitions.'||child||' OWNER TO dbadmin';
        EXECUTE 'GRANT SELECT ON TABLE partitions.'||child||' TO ro';
     
        -- copy constraints to child table
        FOR r IN
        ( SELECT conname as name, pg_get_constraintdef(oid) as definition
          FROM pg_constraint WHERE conrelid = parentoid)
        LOOP
          script = 'ALTER TABLE partitions.'||child||' ADD CONSTRAINT '||replace(r.name, parent, child)||' '||r.definition;
          BEGIN
            EXECUTE script;
          EXCEPTION
            WHEN duplicate_table THEN
          END;
        END LOOP;

        -- copy indexes to child table
        FOR r IN
        ( SELECT c.relname as name, pg_get_indexdef(idx.indexrelid) as definition
          FROM pg_index idx JOIN pg_class c ON c.oid = idx.indexrelid
          WHERE idx.indrelid = parentoid )
        LOOP
          script = replace(r.definition, 'INDEX '||r.name, 'INDEX '||replace(r.name, parent, child));
          script = replace(script, 'ON '||parent, 'ON partitions.'||child);
          BEGIN 
            EXECUTE script;
          EXCEPTION
            WHEN duplicate_table THEN
          END;
        END LOOP;
            
    END;
    $$
    LANGUAGE 'plpgsql';

    --------------------------------------------

    ALTER TABLE event_damage SET SCHEMA partitions;
    ALTER TABLE partitions.event_damage RENAME TO event_damage_0ld;

    CREATE TABLE event_damage
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      characterid integer,
      dealt boolean,
      opponentid integer,
      unittype integer,
      talentid integer,
      physicaldamage real,
      magicaldamage real,
      puredamage real,
      datehierarchy integer NOT NULL,
      CONSTRAINT event_damage_pkey PRIMARY KEY (id),
      CONSTRAINT event_damage_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
      CONSTRAINT event_damage_unittype_fkey FOREIGN KEY (unittype) REFERENCES unittype (id),
      CONSTRAINT event_damage_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid) REFERENCES sessiontoplayer (id),
      CONSTRAINT event_damage_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE event_damage OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage TO ro;

    CREATE INDEX idx_event_damage_sessiontoplayerid ON event_damage (sessiontoplayerid);

    CREATE OR REPLACE FUNCTION event_damage_insert_trigger()
      RETURNS TRIGGER AS $$
    DECLARE
      query text;
    BEGIN
      PERFORM partition_every_day (TG_RELID, NEW.datehierarchy);

      query = 'INSERT INTO partitions.event_damage_'||NEW.datehierarchy||' VALUES('||
        NEW.id||','||
        NEW.sessiontoplayerid||','||
        NEW.step||','||
        COALESCE(NEW.characterid::text,'null')||','||
        COALESCE(NEW.dealt::text,'null')||','||
        COALESCE(NEW.opponentid::text,'null')||','||
        COALESCE(NEW.unittype::text,'null')||','||
        COALESCE(NEW.talentid::text,'null')||','||
        COALESCE(NEW.physicaldamage::text,'null')||','||
        COALESCE(NEW.magicaldamage::text,'null')||','||
        COALESCE(NEW.puredamage::text,'null')||','||
        NEW.datehierarchy||')';

      EXECUTE query;

      RETURN NULL;
    END;
     $$ LANGUAGE plpgsql;

    CREATE TRIGGER tr_event_damage_partition BEFORE INSERT ON event_damage
      FOR EACH ROW EXECUTE PROCEDURE event_damage_insert_trigger();

    INSERT INTO event_damage
    SELECT * FROM partitions.event_damage_0ld
    ORDER BY id DESC LIMIT 1;

    --------------------------------------------

    ALTER TABLE event_naftaincome SET SCHEMA partitions;
    ALTER TABLE partitions.event_naftaincome RENAME TO event_naftaincome_0ld;

    CREATE TABLE event_naftaincome
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      x real NOT NULL,
      y real NOT NULL,
      characterid integer,
      incomefrom integer NOT NULL,
      naftaforkill integer,
      naftaspecforkill integer,
      teamnaftaforkill integer,
      nafta integer,
      datehierarchy integer NOT NULL,
      CONSTRAINT event_naftaincome_pkey PRIMARY KEY (id),
      CONSTRAINT event_naftaincome_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
      CONSTRAINT event_naftaincome_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid) REFERENCES sessiontoplayer (id),
      CONSTRAINT event_naftaincome_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE event_naftaincome OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_naftaincome TO ro;

    CREATE INDEX idx_event_naftaincome_sessiontoplayerid ON event_naftaincome (sessiontoplayerid);

    CREATE OR REPLACE FUNCTION event_naftaincome_insert_trigger()
      RETURNS TRIGGER AS $$
    DECLARE
      query text;
    BEGIN
      PERFORM partition_every_day (TG_RELID, NEW.datehierarchy);

      query = 'INSERT INTO partitions.event_naftaincome_'||NEW.datehierarchy||' VALUES('||
        NEW.id||','||
        NEW.sessiontoplayerid||','||
        NEW.step||','||
        NEW.x||','||
        NEW.y||','||
        COALESCE(NEW.characterid::text,'null')||','||
        NEW.incomefrom||','||
        COALESCE(NEW.naftaforkill::text,'null')||','||
        COALESCE(NEW.naftaspecforkill::text,'null')||','||
        COALESCE(NEW.teamnaftaforkill::text,'null')||','||
        COALESCE(NEW.nafta::text,'null')||','||
        NEW.datehierarchy||')';

      EXECUTE query;

      RETURN NULL;
    END;
     $$ LANGUAGE plpgsql;

    CREATE TRIGGER tr_event_naftaincome_partition BEFORE INSERT ON event_naftaincome
      FOR EACH ROW EXECUTE PROCEDURE event_naftaincome_insert_trigger();

    INSERT INTO event_naftaincome
    SELECT * FROM partitions.event_naftaincome_0ld
    ORDER BY id DESC LIMIT 1;

    select increment_version_to(93) into ver;
  end if;

  if ver = 93
  then
    ALTER TABLE launcherstart ADD COLUMN clientip character varying;
    ALTER TABLE launcherstart ADD COLUMN location character varying;

    select increment_version_to(94) into ver;
  end if;

  if ver = 94
  then
    ALTER TABLE ignoreadd ADD COLUMN datehierarchy integer;
    ALTER TABLE ignoreremove ADD COLUMN datehierarchy integer;
    UPDATE ignoreadd SET datehierarchy = to_char(timestamp, 'YYYYMMDD')::INTEGER;
    UPDATE ignoreremove SET datehierarchy = to_char(timestamp, 'YYYYMMDD')::INTEGER;
    ALTER TABLE ignoreadd ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE ignoreremove ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE ignoreadd ADD CONSTRAINT ignoreadd_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    ALTER TABLE ignoreremove ADD CONSTRAINT ignoreremove_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);

    select increment_version_to(95) into ver;
  end if;

  if ver = 95
  then
    ALTER TABLE mmakingsession ADD COLUMN basket INTEGER NOT NULL DEFAULT -1;
    ALTER TABLE mmakingsession ALTER COLUMN basket DROP DEFAULT;
    ALTER TABLE mmakingplayer ADD COLUMN basket INTEGER NOT NULL DEFAULT -1;
    ALTER TABLE mmakingplayer ALTER COLUMN basket DROP DEFAULT;

    select increment_version_to(96) into ver;
  end if;

  if ver = 96
  then
    ALTER TABLE characterunlock ADD COLUMN datehierarchy integer;
    UPDATE characterunlock SET datehierarchy = to_char(timestamp, 'YYYYMMDD')::INTEGER;
    ALTER TABLE characterunlock ALTER COLUMN datehierarchy SET NOT NULL;
    ALTER TABLE characterunlock ADD CONSTRAINT characterunlock_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    CREATE INDEX idx_characterunlock_datehierarchy ON characterunlock (datehierarchy);

    select increment_version_to(97) into ver;
  end if;

  if ver = 97
  then
    ALTER TABLE event_damage ADD COLUMN map character varying;
    ALTER TABLE event_damage ADD COLUMN sessiontype integer;
    ALTER TABLE event_naftaincome ADD COLUMN map character varying;
    ALTER TABLE event_naftaincome ADD COLUMN sessiontype integer;

    UPDATE event_damage e
    SET map = gs.map, sessiontype = gs.sessiontype
    FROM sessiontoplayer stp 
      JOIN gamesession gs ON gs.id = stp.gamesession
    WHERE e.sessiontoplayerid = stp.id;

    UPDATE event_naftaincome e
    SET map = gs.map, sessiontype = gs.sessiontype
    FROM sessiontoplayer stp 
      JOIN gamesession gs ON gs.id = stp.gamesession
    WHERE e.sessiontoplayerid = stp.id;

    ALTER TABLE event_damage ALTER COLUMN map SET NOT NULL;
    ALTER TABLE event_damage ALTER COLUMN sessiontype SET NOT NULL;
    ALTER TABLE event_naftaincome ALTER COLUMN map SET NOT NULL;
    ALTER TABLE event_naftaincome ALTER COLUMN sessiontype SET NOT NULL;

    CREATE OR REPLACE FUNCTION event_damage_insert_trigger()
      RETURNS TRIGGER AS $$
    DECLARE
      query text;
    BEGIN
      PERFORM partition_every_day (TG_RELID, NEW.datehierarchy);

      query = 'INSERT INTO partitions.event_damage_'||NEW.datehierarchy||
      ' (id,sessiontoplayerid,step,characterid,dealt,opponentid,unittype,talentid,'||
      '  physicaldamage,magicaldamage,puredamage,datehierarchy,map,sessiontype)'||
      ' VALUES('||
        NEW.id||','||
        NEW.sessiontoplayerid||','||
        NEW.step||','||
        COALESCE(NEW.characterid::text,'null')||','||
        COALESCE(NEW.dealt::text,'null')||','||
        COALESCE(NEW.opponentid::text,'null')||','||
        COALESCE(NEW.unittype::text,'null')||','||
        COALESCE(NEW.talentid::text,'null')||','||
        COALESCE(NEW.physicaldamage::text,'null')||','||
        COALESCE(NEW.magicaldamage::text,'null')||','||
        COALESCE(NEW.puredamage::text,'null')||','||
        NEW.datehierarchy||','||
        COALESCE(''''||NEW.map::text||'''','null')||','||
        COALESCE(NEW.sessiontype::text,'null')||')';

      EXECUTE query;

      RETURN NULL;
    END;
    $$ LANGUAGE plpgsql;

    CREATE OR REPLACE FUNCTION event_naftaincome_insert_trigger()
      RETURNS TRIGGER AS
    $$
    DECLARE
      query text;
    BEGIN
      PERFORM partition_every_day (TG_RELID, NEW.datehierarchy);

      query = 'INSERT INTO partitions.event_naftaincome_'||NEW.datehierarchy||
      '(id,sessiontoplayerid,step,x,y,characterid,incomefrom,naftaforkill,'||
      ' naftaspecforkill,teamnaftaforkill,nafta,datehierarchy,map,sessiontype)'||
      ' VALUES('||
        NEW.id||','||
        NEW.sessiontoplayerid||','||
        NEW.step||','||
        NEW.x||','||
        NEW.y||','||
        COALESCE(NEW.characterid::text,'null')||','||
        NEW.incomefrom||','||
        COALESCE(NEW.naftaforkill::text,'null')||','||
        COALESCE(NEW.naftaspecforkill::text,'null')||','||
        COALESCE(NEW.teamnaftaforkill::text,'null')||','||
        COALESCE(NEW.nafta::text,'null')||','||
        NEW.datehierarchy||','||
        COALESCE(''''||NEW.map::text||'''','null')||','||
        COALESCE(NEW.sessiontype::text,'null')||')';

      EXECUTE query;

      RETURN NULL;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION event_naftaincome_insert_trigger() OWNER TO dbadmin;

    DROP TABLE event_damage_agg_building;
    CREATE TABLE event_damage_agg_building
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      map character varying NOT NULL,
      sessiontype integer NOT NULL,
      sessioncount integer NOT NULL,
      buildingid integer NOT NULL,
      dealt boolean NOT NULL,
      physicaldamage real,
      magicaldamage real,
      puredamage real,
      CONSTRAINT event_damage_agg_building_unique UNIQUE (datehierarchy, characterid, map, sessiontype, buildingid, dealt),
      CONSTRAINT event_damage_agg_building_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_damage_agg_building_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
      CONSTRAINT event_damage_agg_building_buildingid_fkey FOREIGN KEY (buildingid) REFERENCES building (id)
    );
    ALTER TABLE event_damage_agg_building OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage_agg_building TO ro;

    DROP TABLE event_damage_agg_creature;
    CREATE TABLE event_damage_agg_creature
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      map character varying NOT NULL,
      sessiontype integer NOT NULL,
      sessioncount integer NOT NULL,
      creatureid integer NOT NULL,
      dealt boolean NOT NULL,
      physicaldamage real,
      magicaldamage real,
      puredamage real,
      CONSTRAINT event_damage_agg_creature_unique UNIQUE (datehierarchy, characterid, map, sessiontype, creatureid, dealt),
      CONSTRAINT event_damage_agg_creature_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_damage_agg_creature_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
      CONSTRAINT event_damage_agg_creature_creatureid_fkey FOREIGN KEY (creatureid) REFERENCES creature (id)
    );
    ALTER TABLE event_damage_agg_creature OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage_agg_creature TO ro;

    DROP TABLE event_damage_agg_unittype;
    CREATE TABLE event_damage_agg_unittype
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      map character varying NOT NULL,
      sessiontype integer NOT NULL,
      sessioncount integer NOT NULL,
      unittype integer NOT NULL,
      dealt boolean NOT NULL,
      physicaldamage real,
      magicaldamage real,
      puredamage real,
      CONSTRAINT event_damage_agg_unittype_unique UNIQUE (datehierarchy, characterid, map, sessiontype, unittype, dealt),
      CONSTRAINT event_damage_agg_unittype_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_damage_agg_unittype_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
      CONSTRAINT event_damage_agg_unittype_unittype_fkey FOREIGN KEY (unittype) REFERENCES unittype (id)
    );
    ALTER TABLE event_damage_agg_unittype OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage_agg_unittype TO ro;

    DROP TABLE event_damage_agg_character;
    CREATE TABLE event_damage_agg_character
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      map character varying NOT NULL,
      sessiontype integer NOT NULL,
      sessioncount integer NOT NULL,
      opponentcharacterid integer NOT NULL,
      dealt boolean NOT NULL,
      physicaldamage real,
      magicaldamage real,
      puredamage real,
      CONSTRAINT event_damage_agg_character_unique UNIQUE (datehierarchy, opponentcharacterid, map, sessiontype, characterid, dealt),
      CONSTRAINT event_damage_agg_character_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_damage_agg_character_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
      CONSTRAINT event_damage_agg_character_opponentcharacterid_fkey FOREIGN KEY (opponentcharacterid) REFERENCES character (id)
    );
    ALTER TABLE event_damage_agg_character OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_damage_agg_character TO ro;

    CREATE OR REPLACE FUNCTION aggregate_event_damage()
      RETURNS void AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      dh INTEGER;
      olddh INTEGER;
      r RECORD;
      cnt INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'event_damage';

      SELECT coalesce(max(id), 0) INTO finishid
      FROM event_damage;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;

      WHILE startid < finishid LOOP

        SELECT datehierarchy INTO olddh
        FROM event_damage
        WHERE id = startid;

        EXECUTE 'SELECT datehierarchy FROM partitions.event_damage_'||olddh||' '||
                'WHERE id > '||startid||' LIMIT 1' INTO dh;

        IF dh is null THEN

          SELECT min(substring(c.relname from E'........$')::integer) INTO dh
          FROM pg_inherits
            JOIN pg_class c ON (inhrelid=c.oid)
            JOIN pg_class p ON (inhparent=p.oid)
          WHERE p.relname = 'event_damage'
            AND substring(c.relname from E'........$')::integer > olddh;

          IF dh is null THEN RAISE 'cannot find partition'; END IF;
        END IF;

        -- determine current partition
    --        SELECT datehierarchy INTO dh
    --        FROM event_damage e
    --        WHERE id = (SELECT min(id) FROM event_damage WHERE id > startid);

        EXECUTE 'SELECT COUNT(*) FROM event_damage WHERE datehierarchy = '||dh INTO CNT;
        RAISE NOTICE '% aggregating % rows from partition % ...', clock_timestamp(), cnt, dh;

        -- aggregate buildings
        FOR r IN 
        EXECUTE  -- Tower, Building, MainBuilding
        ' SELECT datehierarchy, characterid, map, sessiontype, opponentid, dealt,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND unittype in (6, 7, 8) 
            AND sessiontype != 5
          GROUP BY datehierarchy, characterid, map, sessiontype, opponentid, dealt ' 
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_building e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.buildingid = r.opponentid
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_building e
            SET sessioncount = sessioncount + r.stpcnt,
                physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.buildingid = r.opponentid
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_building (datehierarchy, characterid, map, sessiontype, sessioncount, buildingid, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.characterid, r.map, r.sessiontype, r.stpcnt, r.opponentid, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        RAISE NOTICE '% buildings done', clock_timestamp();

        -- aggregate characters
        FOR r IN 
        EXECUTE  -- HeroMale, HeroFemale
        ' SELECT datehierarchy, characterid, map, sessiontype, opponentid, dealt,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND unittype in (0, 1) 
            AND sessiontype != 5
          GROUP BY datehierarchy, characterid, map, sessiontype, opponentid, dealt ' 
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_character e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.opponentcharacterid = r.opponentid
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_character e
            SET sessioncount = sessioncount + r.stpcnt,
                physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.opponentcharacterid = r.opponentid
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_character (datehierarchy, characterid, map, sessiontype, sessioncount, opponentcharacterid, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.characterid, r.map, r.sessiontype, r.stpcnt, r.opponentid, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        RAISE NOTICE '% characters done', clock_timestamp();
        
        -- aggregate creature
        FOR r IN 
        EXECUTE  -- Summon, Creep, SiegeCreep, NeutralCreep, NeutralChampion, NeutralBoss
        ' SELECT datehierarchy, characterid, map, sessiontype, opponentid, dealt,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND unittype in (2, 3, 4, 5, 18, 19) 
            AND sessiontype != 5
          GROUP BY datehierarchy, characterid, map, sessiontype, opponentid, dealt ' 
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_creature e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.creatureid = r.opponentid
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_creature e
            SET sessioncount = sessioncount + r.stpcnt,
                physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.creatureid = r.opponentid
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_creature (datehierarchy, characterid, map, sessiontype, sessioncount, creatureid, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.characterid, r.map, r.sessiontype, r.stpcnt, r.opponentid, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        RAISE NOTICE '% creatures done', clock_timestamp();
        
        -- aggregate unittype
        FOR r IN 
        EXECUTE
        ' SELECT datehierarchy, characterid, map, sessiontype, unittype, dealt,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND sessiontype != 5
          GROUP BY datehierarchy, characterid, map, sessiontype, unittype, dealt ' 
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_unittype e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.unittype = r.unittype
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_unittype e
            SET sessioncount = sessioncount + r.stpcnt,
                physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.unittype = r.unittype
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_unittype (datehierarchy, characterid, map, sessiontype, sessioncount, unittype, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.characterid, r.map, r.sessiontype, r.stpcnt, r.unittype, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        RAISE NOTICE '% unittypes done', clock_timestamp();
        
        RAISE NOTICE 'done...';
        EXECUTE 'SELECT max(id) FROM event_damage WHERE datehierarchy = '||dh INTO startid;
      END LOOP;

      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'event_damage';

      RAISE NOTICE '% finished!', clock_timestamp();
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_event_damage() OWNER TO dbadmin;

    DROP VIEW v_event_damage;

    DROP TABLE event_naftaincome_agg_minute;
    CREATE TABLE event_naftaincome_agg_minute
    (
      datehierarchy integer NOT NULL,
      characterid integer NOT NULL,
      map character varying NOT NULL,
      sessiontype integer NOT NULL,
      sessioncount integer NOT NULL,
      incomefrom character varying NOT NULL,
      minute integer NOT NULL,
      naftaforkill integer,
      naftaspecforkill integer,
      teamnaftaforkill integer,
      nafta integer,
      CONSTRAINT event_naftaincome_agg_minute_unique UNIQUE (datehierarchy, characterid, map, sessiontype, incomefrom, minute),
      CONSTRAINT event_naftaincome_agg_minute_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_naftaincome_agg_minute_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id)
    );
    ALTER TABLE event_naftaincome_agg_minute OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_naftaincome_agg_minute TO ro;

    CREATE OR REPLACE FUNCTION aggregate_event_naftaincome()
      RETURNS void AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      dh INTEGER;
      olddh INTEGER;
      r RECORD;
      cnt INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'event_naftaincome';

      SELECT coalesce(max(id), 0) INTO finishid
      FROM event_naftaincome;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;
      RAISE NOTICE 'startid = %, finishid = %', startid, finishid;

      WHILE startid < finishid LOOP

        SELECT datehierarchy INTO olddh
        FROM event_naftaincome
        WHERE id = startid;

        EXECUTE 'SELECT datehierarchy FROM partitions.event_naftaincome_'||olddh||' '||
                'WHERE id > '||startid||' LIMIT 1' INTO dh;

        IF dh is null THEN

          SELECT min(substring(c.relname from E'........$')::integer) INTO dh
          FROM pg_inherits
            JOIN pg_class c ON (inhrelid=c.oid)
            JOIN pg_class p ON (inhparent=p.oid)
          WHERE p.relname = 'event_naftaincome'
            AND substring(c.relname from E'........$')::integer > olddh;

          IF dh is null THEN RAISE 'cannot find partition'; END IF;
        END IF;

        -- determine current partition
    --        SELECT datehierarchy INTO dh
    --        FROM event_naftaincome e
    --        WHERE id = (SELECT min(id) FROM event_naftaincome WHERE id > startid);

        EXECUTE 'SELECT COUNT(*) FROM event_naftaincome WHERE datehierarchy = '||dh INTO CNT;
        RAISE NOTICE '% aggregating % rows from partition % ...', clock_timestamp(), cnt, dh;

        FOR r IN
        EXECUTE
        '  SELECT datehierarchy, characterid, map, sessiontype, step/600+1 as minute,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 CASE WHEN incomefrom = 0 THEN ''hero''
                      WHEN incomefrom = 1 THEN ''creature''
                      WHEN incomefrom = 2 THEN ''building''
                      WHEN incomefrom = 3 THEN ''talent''
                      WHEN incomefrom = 4 THEN ''impulsivebuff''
                      WHEN incomefrom = 5 THEN ''minigame''
                      ELSE ''undefined'' END as strincomefrom,
                 SUM(naftaforkill) nfk, SUM(naftaspecforkill) nsfk, SUM(teamnaftaforkill) tnfk, SUM(nafta) n
          FROM event_naftaincome
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND sessiontype != 5
          GROUP BY datehierarchy, characterid, map, sessiontype, step/600+1, strincomefrom '
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_naftaincome_agg_minute e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.incomefrom = r.strincomefrom
              AND e.minute = r.minute )
          THEN
            UPDATE event_naftaincome_agg_minute e
            SET sessioncount = sessioncount + r.stpcnt,
                naftaforkill = naftaforkill + r.nfk,
                naftaspecforkill = naftaspecforkill + r.nsfk,
                teamnaftaforkill = teamnaftaforkill + r.tnfk,
                nafta = nafta + r.n
            WHERE e.datehierarchy = r.datehierarchy
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.incomefrom = r.strincomefrom
              AND e.minute = r.minute;
          ELSE
            INSERT INTO event_naftaincome_agg_minute (datehierarchy, characterid, map, sessiontype, sessioncount, incomefrom, minute, naftaforkill, naftaspecforkill, teamnaftaforkill, nafta)
            VALUES (r.datehierarchy, r.characterid, r.map, r.sessiontype, r.stpcnt, r.strincomefrom, r.minute, r.nfk, r.nsfk, r.tnfk, r.n);
          END IF;
        END LOOP;

        RAISE NOTICE 'done...';
        EXECUTE 'SELECT max(id) FROM event_naftaincome WHERE datehierarchy = '||dh INTO startid;
      END LOOP;

      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'event_naftaincome';

      RAISE NOTICE '% finished!', clock_timestamp();
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_event_naftaincome() OWNER TO dbadmin;

    UPDATE sys_aggregation_ranges
    SET lastid = (SELECT min(id) FROM event_naftaincome)
    WHERE tablename = 'event_naftaincome';
    UPDATE sys_aggregation_ranges
    SET lastid = (SELECT min(id) FROM event_damage)
    WHERE tablename = 'event_damage';

    select increment_version_to(98) into ver;
  end if;

  if ver = 98
  then
    CREATE TABLE event_reconnect
    (
      id bigint NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      type character varying NOT NULL,
      result character varying NOT NULL,
      "timestamp" timestamp without time zone,
      datehierarchy integer,
      CONSTRAINT reconnect_pkey PRIMARY KEY (id),
      CONSTRAINT event_reconnect_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
      CONSTRAINT event_reconnect_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid) REFERENCES sessiontoplayer (id)
    );
    ALTER TABLE event_reconnect OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_reconnect TO ro;

    CREATE INDEX idx_event_reconnect_sessiontoplayerid ON event_reconnect (sessiontoplayerid);

    select increment_version_to(99) into ver;
  end if;

  if ver = 99
  then
    CREATE TABLE launcherdaction
    (
      id bigint NOT NULL,
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
      serverdatehierarchy integer,
      CONSTRAINT launcherdaction_pkey PRIMARY KEY (id),
      CONSTRAINT launcherdaction_serverdatehierarchy_fkey FOREIGN KEY (serverdatehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE launcherdaction OWNER TO dbadmin;
    GRANT SELECT ON TABLE launcherdaction TO ro;

    CREATE INDEX idx_launcherdaction_action ON launcherdaction (action);
    CREATE INDEX idx_launcherdaction_serverdatehierarchy ON launcherdaction (serverdatehierarchy);

    select increment_version_to(100) into ver;
  end if;

  if ver = 100
  then
    CREATE TABLE ratingchange
    (
      id integer NOT NULL,
      type integer NOT NULL,
      player bigint NOT NULL,
      persistentid bigint,
      character integer,
      change integer,
      total bigint,
      "timestamp" timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT ratingchange_pkey PRIMARY KEY (id),
      CONSTRAINT ratingchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT ratingchange_character_fkey FOREIGN KEY (character) REFERENCES character (id),
      CONSTRAINT ratingchange_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE ratingchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE ratingchange TO ro;
  
    ALTER TABLE player ADD COLUMN rating integer NOT NULL DEFAULT 0;
    ALTER TABLE player ALTER COLUMN rating DROP DEFAULT;

    select increment_version_to(101) into ver;
  end if;

  if ver = 101
  then
    CREATE TABLE exceedingserversteptime
    (
      id bigint NOT NULL,
      gamesessionid integer NOT NULL,
      step integer,
      starttime timestamp without time zone,
      finishtime timestamp without time zone,
      stepcount integer,
      steptimemin integer,
      steptimemax integer,
      steptimeavg integer,
      datehierarchy integer,
      CONSTRAINT exceedingserversteptime_pkey PRIMARY KEY (id),
      CONSTRAINT event_exceedingserversteptime_gamesessionid_fkey FOREIGN KEY (gamesessionid) REFERENCES gamesession (id),
      CONSTRAINT event_exceedingserversteptime_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE exceedingserversteptime OWNER TO dbadmin;
    GRANT SELECT ON TABLE exceedingserversteptime TO ro;

    CREATE INDEX idx_exceedingserversteptime_gamesessionid ON exceedingserversteptime (gamesessionid);

    select increment_version_to(102) into ver;
  end if;

  if ver = 102
  then
    CREATE INDEX idx_mmakingsession_persistentid ON mmakingsession (persistentid);
    
    ALTER TABLE mmakingplayer ADD COLUMN partymembers integer NOT NULL DEFAULT 0;
    UPDATE mmakingplayer m
    SET partymembers = (select count(*) from mmakingplayer m2
                        where m2.mmakingsession = m.mmakingsession
                          and m2.mmakingsession is not null
                          and m2.party = m.party
                          and m2.party != 0 )
    WHERE mmakingsession is not null;
    ALTER TABLE mmakingplayer ALTER COLUMN partymembers DROP DEFAULT;

    select increment_version_to(103) into ver;
  end if;

  if ver = 103
  then
    ALTER TABLE sessiontoplayer DROP CONSTRAINT IF EXISTS sessiontoplayer_resourcelog_fkey;
    ALTER TABLE factionchange DROP CONSTRAINT IF EXISTS factionchange_resourcelog_fkey;
    ALTER TABLE characterunlock DROP CONSTRAINT IF EXISTS characterunlock_resourcelog_fkey;
    ALTER TABLE movetobath DROP CONSTRAINT IF EXISTS movetobath_resourcelog_fkey;

    ----- 
    CREATE TABLE resourcelog_gold (LIKE resourcelog INCLUDING DEFAULTS);
    ALTER TABLE resourcelog_gold OWNER TO dbadmin;
    GRANT SELECT ON TABLE resourcelog_gold TO ro;

    ALTER TABLE resourcelog_gold ADD CONSTRAINT resourcelog_gold_pkey PRIMARY KEY (id);
    ALTER TABLE resourcelog_gold ADD CONSTRAINT resourcelog_gold_player_fkey FOREIGN KEY (player) REFERENCES player (id);
    ALTER TABLE resourcelog_gold ADD CONSTRAINT resourcelog_gold_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);

    CREATE INDEX idx_resourcelog_gold_player ON resourcelog_gold (player);
    CREATE INDEX idx_resourcelog_gold_datehierarchy ON resourcelog_gold (datehierarchy);

    INSERT INTO resourcelog_gold
    SELECT * FROM resourcelog
    WHERE goldchange != 0;

    -----
    ALTER TABLE resourcelog RENAME TO resourcelogold;

    CREATE TABLE resourcelog (LIKE resourcelogold INCLUDING DEFAULTS);
    ALTER TABLE resourcelog OWNER TO dbadmin;
    GRANT SELECT ON TABLE resourcelog TO ro;

    ALTER TABLE resourcelogold DROP CONSTRAINT resourcelog_pkey;
    ALTER TABLE resourcelogold DROP CONSTRAINT resourcelog_player_fkey;
    ALTER TABLE resourcelogold DROP CONSTRAINT resourcelog_datehierarchy_fkey;

    ALTER TABLE resourcelog ADD CONSTRAINT resourcelog_pkey PRIMARY KEY(id);
    ALTER TABLE resourcelog ADD CONSTRAINT resourcelog_player_fkey FOREIGN KEY (player) REFERENCES player (id);

    DROP INDEX idx_resourcelog_player;
    CREATE INDEX idx_resourcelog_player ON resourcelog (player);

    -----
    CREATE OR REPLACE FUNCTION resourcelog_insert_trigger()
      RETURNS TRIGGER AS $$
    DECLARE
      query text;
    BEGIN
      if NEW.datehierarchy is null then return NULL; end if;

      PERFORM partition_every_day (TG_RELID, NEW.datehierarchy);

      query = 'INSERT INTO partitions.resourcelog_'||NEW.datehierarchy||
      ' (id,source,buildingname,gain,player,'||
      '  goldchange,silverchange,perlchange,populationchange,resource1change,resource2change,resource3change,'||
      '  goldtotal,silvertotal,perltotal,populationtotal,resource1total,resource2total,resource3total,'||
      '  timestamp,datehierarchy)'||
      ' VALUES('||
        NEW.id||','||
        COALESCE(''''||NEW.source::text||'''','null')||','||
        COALESCE(''''||NEW.buildingname::text||'''','null')||','||
        NEW.gain||','||
        NEW.player||','||
        NEW.goldchange||','||
        NEW.silverchange||','||
        NEW.perlchange||','||
        NEW.populationchange||','||
        NEW.resource1change||','||
        NEW.resource2change||','||
        NEW.resource3change||','||
        NEW.goldtotal||','||
        NEW.silvertotal||','||
        NEW.perltotal||','||
        NEW.populationtotal||','||
        NEW.resource1total||','||
        NEW.resource2total||','||
        NEW.resource3total||','||
        COALESCE(''''||NEW.timestamp::text||'''','null')||','||
        NEW.datehierarchy||')';

      EXECUTE query;

      RETURN NULL;
    END;
    $$ LANGUAGE plpgsql;

    ALTER FUNCTION resourcelog_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_resourcelog_partition BEFORE INSERT ON resourcelog
      FOR EACH ROW EXECUTE PROCEDURE resourcelog_insert_trigger();

    INSERT INTO resourcelog
    SELECT * FROM resourcelogold;

    DROP TABLE resourcelogold;

    -----
    INSERT INTO sys_aggregation_ranges VALUES ('socialsession', 0);
    INSERT INTO sys_aggregation_ranges VALUES ('resourcelog', 0);

    -----
    CREATE TABLE socialsession_agg_dau
    (
      datehierarchy integer NOT NULL,
      dau integer NOT NULL,
      sessions integer NOT NULL,
      CONSTRAINT socialsession_agg_dau_pkey PRIMARY KEY (datehierarchy)
    );
    ALTER TABLE socialsession_agg_dau OWNER TO dbadmin;
    GRANT SELECT ON TABLE socialsession_agg_dau TO ro;

    CREATE OR REPLACE FUNCTION aggregate_socialsession()
      RETURNS void AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      r RECORD;
      dau2 INTEGER;
      sessions2 INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'socialsession';

      IF startid = 0
      THEN
        SELECT coalesce(min(id), 0) INTO startid
        FROM resourcelog;
      END IF;

      SELECT coalesce(max(id), 0) INTO finishid
      FROM socialsession;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;
      RAISE NOTICE 'startid = %, finishid = %', startid, finishid;

      FOR r IN (
        SELECT datehierarchy, count(distinct player) dau, count(*) sessions
        FROM socialsession
        WHERE id >  startid
          AND id <= finishid
        GROUP BY datehierarchy )
      LOOP
        RAISE NOTICE '%...', r.datehierarchy;    
        IF EXISTS (
          SELECT 1 FROM socialsession_agg_dau 
          WHERE datehierarchy = r.datehierarchy )
        THEN
          UPDATE socialsession_agg_dau
          SET dau = dau + r.dau,
              sessions = sessions + r.sessions
          WHERE datehierarchy = r.datehierarchy;
        ELSE
          SELECT count(distinct player), count(*) INTO dau2, sessions2
          FROM socialsession
          WHERE datehierarchy = to_char(to_date(r.datehierarchy::text,'yyyyMMdd')-interval '1 day','yyyyMMdd')::integer
            AND endtime >= to_date(r.datehierarchy::text,'yyyyMMdd');
          
          INSERT INTO socialsession_agg_dau (datehierarchy, dau, sessions) 
          VALUES (r.datehierarchy, r.dau, r.sessions);
        END IF;
      END LOOP;
      
      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'socialsession';

      RAISE NOTICE '% finished!', clock_timestamp();
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_socialsession() OWNER TO dbadmin;

    -----
    CREATE TABLE resourcelog_agg_source
    (
      datehierarchy integer NOT NULL,
      source character varying NOT NULL,
      buildingname character varying,  
      gain boolean NOT NULL,
      goldchange integer NOT NULL,
      silverchange integer NOT NULL,
      perlchange integer NOT NULL,
      populationchange integer NOT NULL,
      resource1change integer NOT NULL,
      resource2change integer NOT NULL,
      resource3change integer NOT NULL,
      CONSTRAINT resourcelog_agg_source_unique UNIQUE (datehierarchy, source, buildingname, gain)
    );
    ALTER TABLE resourcelog_agg_source OWNER TO dbadmin;
    GRANT SELECT ON TABLE resourcelog_agg_source TO ro;

    CREATE OR REPLACE FUNCTION aggregate_resourcelog()
      RETURNS void AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      dh INTEGER;
      olddh INTEGER;
      r RECORD;
      cnt INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'resourcelog';

      IF startid = 0
      THEN
        SELECT coalesce(min(id), 0) INTO startid
        FROM resourcelog;
      END IF;

      SELECT coalesce(max(id), 0) INTO finishid
      FROM resourcelog;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;
      RAISE NOTICE 'startid = %, finishid = %', startid, finishid;

      WHILE startid < finishid LOOP

        SELECT datehierarchy INTO olddh
        FROM resourcelog
        WHERE id = startid;

        EXECUTE 'SELECT datehierarchy FROM partitions.resourcelog_'||olddh||' '||
                'WHERE id > '||startid||' LIMIT 1' INTO dh;

        IF dh is null THEN

          SELECT min(substring(c.relname from E'........$')::integer) INTO dh
          FROM pg_inherits
            JOIN pg_class c ON (inhrelid=c.oid)
            JOIN pg_class p ON (inhparent=p.oid)
          WHERE p.relname = 'resourcelog'
            AND substring(c.relname from E'........$')::integer > olddh;

          IF dh is null THEN RAISE 'cannot find partition'; END IF;
        END IF;

        -- determine current partition
    --        SELECT datehierarchy INTO dh
    --        FROM resourcelog e
    --        WHERE id = (SELECT min(id) FROM resourcelog WHERE id > startid);

        EXECUTE 'SELECT COUNT(*) FROM resourcelog WHERE datehierarchy = '||dh INTO CNT;
        RAISE NOTICE '% aggregating % rows from partition % ...', clock_timestamp(), cnt, dh;

        FOR r IN
        EXECUTE
        ' SELECT datehierarchy, source, buildingname, gain,
                 SUM(goldchange) gld, SUM(silverchange) slv, SUM(perlchange) prl, SUM(populationchange) ppl,
                 SUM(resource1change) rs1, SUM(resource2change) rs2, SUM(resource3change) rs3
          FROM resourcelog
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
          GROUP BY datehierarchy, source, buildingname, gain '
        LOOP
          IF EXISTS (
            SELECT 1 FROM resourcelog_agg_source
            WHERE datehierarchy = r.datehierarchy
              AND source = r.source
              AND ((buildingname is null AND r.buildingname is null) OR buildingname = r.buildingname)
              AND gain = r.gain )
          THEN
            UPDATE resourcelog_agg_source
            SET goldchange = goldchange + r.gld,
                silverchange = silverchange + r.slv,
                perlchange = perlchange + r.prl,
                populationchange = populationchange + r.ppl,
                resource1change = resource1change + r.rs1,
                resource2change = resource2change + r.rs2,
                resource3change = resource3change + r.rs3
            WHERE datehierarchy = r.datehierarchy
              AND source = r.source
              AND ((buildingname is null AND r.buildingname is null) OR buildingname = r.buildingname)
              AND gain = r.gain;
          ELSE
            INSERT INTO resourcelog_agg_source (datehierarchy, source, buildingname, gain, goldchange, silverchange, perlchange, populationchange, resource1change, resource2change, resource3change)
            VALUES (r.datehierarchy, r.source, r.buildingname, r.gain, r.gld, r.slv, r.prl, r.ppl, r.rs1, r.rs2, r.rs3);
          END IF;
        END LOOP;

        RAISE NOTICE 'done...';
        EXECUTE 'SELECT max(id) FROM resourcelog WHERE datehierarchy = '||dh INTO startid;
      END LOOP;

      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'resourcelog';

      RAISE NOTICE '% finished!', clock_timestamp();
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_resourcelog() OWNER TO dbadmin;

    select increment_version_to(104) into ver;
  end if;

  if ver = 104
  then
    DROP TRIGGER tr_resourcelog_partition ON resourcelog;
    DROP TRIGGER tr_event_naftaincome_partition ON event_naftaincome;
    DROP TRIGGER tr_event_damage_partition ON event_damage;
    DROP FUNCTION resourcelog_insert_trigger();
    DROP FUNCTION event_naftaincome_insert_trigger();
    DROP FUNCTION event_damage_insert_trigger();

    CREATE OR REPLACE FUNCTION partition_every_day (parentoid oid, datehierarchy integer)
      RETURNS void AS
    $$
    DECLARE
      parent text = parentoid::regclass;
      child  text = parent||'_'||datehierarchy;
      script text;
      r record;
    BEGIN
      -- check if table already exists
      PERFORM ('partitions.'||child)::regclass;
      
    EXCEPTION
      WHEN undefined_table THEN
      
        -- create child table
        EXECUTE 
        'CREATE TABLE partitions.'||child||' '||
        '( CHECK (datehierarchy = '||datehierarchy||')) '||
        'INHERITS ('||parent||')';
        EXECUTE 'ALTER TABLE partitions.'||child||' OWNER TO dbadmin';
        EXECUTE 'GRANT SELECT ON TABLE partitions.'||child||' TO ro';
     
        -- copy constraints to child table
        FOR r IN
        ( SELECT conname as name, pg_get_constraintdef(oid) as definition
          FROM pg_constraint WHERE conrelid = parentoid)
        LOOP
          script = 'ALTER TABLE partitions.'||child||' ADD CONSTRAINT '||replace(r.name, parent, child)||' '||r.definition;
          BEGIN
            EXECUTE script;
          EXCEPTION
            WHEN duplicate_table THEN
          END;
        END LOOP;

        -- copy indexes to child table
        FOR r IN
        ( SELECT c.relname as name, pg_get_indexdef(idx.indexrelid) as definition
          FROM pg_index idx JOIN pg_class c ON c.oid = idx.indexrelid
          WHERE idx.indrelid = parentoid )
        LOOP
          script = replace(r.definition, 'INDEX '||r.name, 'INDEX '||replace(r.name, parent, child));
          script = replace(script, 'ON '||parent, 'ON partitions.'||child);
          BEGIN 
            EXECUTE script;
          EXCEPTION
            WHEN duplicate_table THEN
          END;
        END LOOP;
        
        -- create rule
        EXECUTE
        'CREATE RULE '||parent||'_insert_'||datehierarchy||' AS '||
        'ON INSERT TO '||parent||' WHERE (datehierarchy = '||datehierarchy||') '||
        'DO INSTEAD INSERT INTO partitions.'||child||' VALUES (NEW.*)';

    END;
    $$
    LANGUAGE 'plpgsql';

    CREATE OR REPLACE FUNCTION partitions_check (tablename character varying)
      RETURNS void AS
    $$
    DECLARE
      r record;
      dh integer;
      enddh integer;
    BEGIN
      SELECT COALESCE(max(substring(c.relname from E'........$')::integer),
                      to_char(now() - interval '1 day','yyyyMMdd')::integer) INTO dh
      FROM pg_inherits
        JOIN pg_class c ON (inhrelid=c.oid)
        JOIN pg_class p ON (inhparent=p.oid)
      WHERE p.relname = tablename;

      enddh = to_char(now() + interval '2 days','yyyyMMdd')::integer;

      FOR r IN (
        SELECT id FROM datehierarchy
        WHERE id > dh AND id <= enddh )
      LOOP
        RAISE NOTICE 'creating partition %_%', tablename, r.id;
        PERFORM partition_every_day (tablename::regclass, r.id);
      END LOOP;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION partitions_check(character varying) OWNER TO dbadmin;

    FOR tmprow IN (
      SELECT p.relname as parent, c.relname as child,
             substring(c.relname from E'........$')::integer as datehierarchy
      FROM pg_inherits
        JOIN pg_class c ON (inhrelid=c.oid)
        JOIN pg_class p ON (inhparent=p.oid)
      WHERE p.relname IN ('resourcelog', 'event_damage', 'event_naftaincome')
      ORDER BY 1 )
    LOOP
      EXECUTE
      'CREATE RULE '||tmprow.parent||'_insert_'||tmprow.datehierarchy||' AS '||
      'ON INSERT TO '||tmprow.parent||' WHERE (datehierarchy = '||tmprow.datehierarchy||') '||
      'DO INSTEAD INSERT INTO partitions.'||tmprow.child||' VALUES (NEW.*)';
    END LOOP;

    select increment_version_to(105) into ver;
  end if;

  if ver = 105
  then
    ALTER TABLE launcherstart RENAME location TO geolocation;

    -- adding "location" column and recreating indexes
    textarr = 
    '{characterunlock,chat,event_achievement,event_assist,event_buildingdestroyed,event_cheat,'||
    'event_cheatused,event_consumablebought,event_consumableused,event_damage,event_death,'||
    'event_debugvar,event_disconnect,event_exceedingpingtime,event_exceedingsteptime,event_flag,'||
    'event_kill,event_levelup,event_mg_ballschanged,'||
    'event_mg_boostused,event_naftaincome,event_reconnect,event_ressurection,event_talentunlocked,'||
    'event_talentused,event_timeslice,exceedingserversteptime,factionchange,gamesession,'||
    'gm_addtalent,gm_banplayer,gm_deletetalent,gm_editplayer,gm_lockcharacter,gm_muteplayer,'||
    'gm_unbanplayer,gm_unlockcharacter,gm_unmuteplayer,ignoreadd,ignoreremove,'||
    'launcherdaction,launcherdend,launcherdstart,launcherevents,launcherstart,mmakingplayer,'||
    'mmakingsession,movetobath,offlineevent,playercharacter,questchange,ratingchange,resourcelog,'||
    'resourcelog_gold,sessiontoplayer,socialjoin,socialmerge,socialregister,socialsession,'||
    'talentroll,tmp_talentswitchedoff}';
    FOR i IN array_lower(textarr,1)..array_upper(textarr,1)
    LOOP
      SELECT conname INTO c
      FROM pg_constraint
      WHERE contype = 'p'
        AND conrelid = textarr[i]::regclass;

      EXECUTE 'ALTER TABLE '||textarr[i]||' ADD COLUMN location varchar NOT NULL DEFAULT ''ru0'''; 
      EXECUTE 'ALTER TABLE '||textarr[i]||' ALTER COLUMN location DROP DEFAULT';
      EXECUTE 'ALTER TABLE '||textarr[i]||' DROP CONSTRAINT '||c||' CASCADE';
      EXECUTE 'ALTER TABLE '||textarr[i]||' ADD CONSTRAINT '||textarr[i]||'_pkey PRIMARY KEY (id,location)';
    END LOOP;

    -- same for partitions
    FOR tmprow IN (
      SELECT p.relname as parent, c.relname as child,
             substring(c.relname from E'........$')::integer as datehierarchy
      FROM pg_inherits
        JOIN pg_class c ON (inhrelid=c.oid)
        JOIN pg_class p ON (inhparent=p.oid)
      WHERE p.relname IN ('event_damage', 'event_naftaincome', 'resourcelog')
      ORDER BY 1 )
    LOOP
      SELECT conname INTO c
      FROM pg_constraint
      WHERE contype = 'p'
        AND conrelid = ('partitions.'||tmprow.child)::regclass;

      EXECUTE 'ALTER TABLE partitions.'||tmprow.child||' DROP CONSTRAINT '||c;
      EXECUTE 'ALTER TABLE partitions.'||tmprow.child||' ADD CONSTRAINT '||tmprow.child||'_pkey PRIMARY KEY (id,location)';

      EXECUTE 'DROP RULE '||tmprow.parent||'_insert_'||tmprow.datehierarchy||' ON '||tmprow.parent;
      EXECUTE
      'CREATE RULE '||tmprow.parent||'_insert_'||tmprow.datehierarchy||' AS '||
      'ON INSERT TO '||tmprow.parent||' WHERE (datehierarchy = '||tmprow.datehierarchy||') '||
      'DO INSTEAD INSERT INTO partitions.'||tmprow.child||' VALUES (NEW.*)';
    END LOOP;

    ALTER TABLE event_mg_session ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE event_mg_session ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE event_mg_session DROP CONSTRAINT event_mg_session_pkey CASCADE;
    ALTER TABLE event_mg_session ADD CONSTRAINT event_mg_session_pkey PRIMARY KEY (startid,location);

    ALTER TABLE event_mg_level ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE event_mg_level ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE event_mg_level DROP CONSTRAINT event_mg_level_pkey CASCADE;
    ALTER TABLE event_mg_level ADD CONSTRAINT event_mg_level_pkey PRIMARY KEY (startid,location);


    -- recreating cascade dropped constraints
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_gamesession_fkey 
      FOREIGN KEY (gamesession,location) REFERENCES gamesession (id,location);
    ALTER TABLE exceedingserversteptime ADD CONSTRAINT exceedingserversteptime_gamesessionid_fkey 
      FOREIGN KEY (gamesessionid,location) REFERENCES gamesession (id,location);

    ALTER TABLE mmakingplayer ADD CONSTRAINT mmakingplayer_mmakingsession_fkey 
      FOREIGN KEY (mmakingsession,location) REFERENCES mmakingsession (id,location);

    textarr = 
    '{characterunlock,mmakingplayer,movetobath,sessiontoplayer}';
    FOR i IN array_lower(textarr,1)..array_upper(textarr,1)
    LOOP
      EXECUTE 
      'ALTER TABLE '||textarr[i]||' ADD CONSTRAINT '||textarr[i]||'_playercharacter_fkey '||
      'FOREIGN KEY (playercharacter,location) REFERENCES playercharacter (id,location)';
    END LOOP;

    textarr = 
    '{event_achievement,event_assist,event_buildingdestroyed,event_cheat,event_cheatused,'||
    'event_consumablebought,event_consumableused,event_damage,event_death,event_debugvar,'||
    'event_disconnect,event_exceedingpingtime,event_exceedingsteptime,event_flag,event_kill,'||
    'event_levelup,event_mg_session,event_naftaincome,event_reconnect,event_ressurection,'||
    'event_talentunlocked,event_talentused,event_timeslice}';
    FOR i IN array_lower(textarr,1)..array_upper(textarr,1)
    LOOP
      EXECUTE 
      'ALTER TABLE '||textarr[i]||' ADD CONSTRAINT '||textarr[i]||'_sessiontoplayerid_fkey '||
      'FOREIGN KEY (sessiontoplayerid,location) REFERENCES sessiontoplayer (id,location)';
    END LOOP;
    ALTER TABLE talentroll ADD CONSTRAINT talentroll_sessiontoplayer_fkey
      FOREIGN KEY (sessiontoplayer,location) REFERENCES sessiontoplayer (id,location);

    FOR tmprow IN (
      SELECT c.relname as child
      FROM pg_inherits
        JOIN pg_class c ON (inhrelid=c.oid)
        JOIN pg_class p ON (inhparent=p.oid)
      WHERE p.relname IN ('event_damage', 'event_naftaincome')
      ORDER BY 1 )
    LOOP
      EXECUTE 
      'ALTER TABLE partitions.'||tmprow.child||' ADD CONSTRAINT '||tmprow.child||'_sessiontoplayerid_fkey '||
      'FOREIGN KEY (sessiontoplayerid,location) REFERENCES sessiontoplayer (id,location)';
    END LOOP;

    ALTER TABLE talentroll ADD CONSTRAINT talentroll_sessiontoplayerid_fkey
      FOREIGN KEY (sessiontoplayer,location) REFERENCES sessiontoplayer (id,location);

    ALTER TABLE event_mg_ballschanged ADD CONSTRAINT event_mg_ballschanged_mgsessionid_fkey
      FOREIGN KEY (mgsessionid,location) REFERENCES event_mg_session (startid,location);
    ALTER TABLE event_mg_level ADD CONSTRAINT event_mg_level_mgsessionid_fkey
      FOREIGN KEY (mgsessionid,location) REFERENCES event_mg_session (startid,location);

    ALTER TABLE event_mg_boostused ADD CONSTRAINT event_mg_boostused_mglevelid_fkey 
      FOREIGN KEY (mglevelid,location) REFERENCES event_mg_level (startid,location);

    ALTER TABLE playercharacter DROP CONSTRAINT playercharacter_unique_player_character;
    ALTER TABLE playercharacter ADD CONSTRAINT playercharacter_unique_player_character
      UNIQUE (player, character, location);
    
    -- fix functions and aggregate tables

    ALTER TABLE sys_aggregation_ranges ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE sys_aggregation_ranges ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE sys_aggregation_ranges DROP CONSTRAINT sys_aggregation_ranges_pkey;
    ALTER TABLE sys_aggregation_ranges ADD CONSTRAINT sys_aggregation_ranges_pkey 
      PRIMARY KEY (tablename, location);


    ALTER TABLE event_damage_agg_building ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE event_damage_agg_building ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE event_damage_agg_building DROP CONSTRAINT event_damage_agg_building_unique;
    ALTER TABLE event_damage_agg_building ADD CONSTRAINT event_damage_agg_building_pkey
      PRIMARY KEY (datehierarchy, location, characterid, map, sessiontype, buildingid, dealt);

    ALTER TABLE event_damage_agg_character ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE event_damage_agg_character ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE event_damage_agg_character DROP CONSTRAINT event_damage_agg_character_unique;
    ALTER TABLE event_damage_agg_character ADD CONSTRAINT event_damage_agg_character_pkey
      PRIMARY KEY (datehierarchy, location, opponentcharacterid, characterid, map, sessiontype, dealt);

    ALTER TABLE event_damage_agg_creature ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE event_damage_agg_creature ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE event_damage_agg_creature DROP CONSTRAINT event_damage_agg_creature_unique;
    ALTER TABLE event_damage_agg_creature ADD CONSTRAINT event_damage_agg_creature_pkey
      PRIMARY KEY (datehierarchy, location, characterid, map, sessiontype, creatureid, dealt);

    ALTER TABLE event_damage_agg_unittype ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE event_damage_agg_unittype ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE event_damage_agg_unittype DROP CONSTRAINT event_damage_agg_unittype_unique;
    ALTER TABLE event_damage_agg_unittype ADD CONSTRAINT event_damage_agg_unittype_pkey
      PRIMARY KEY (datehierarchy, location, characterid, map, sessiontype, unittype, dealt);


    DROP FUNCTION aggregate_event_damage();

    CREATE OR REPLACE FUNCTION aggregate_event_damage(p_location varchar)
      RETURNS void AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      dh INTEGER;
      olddh INTEGER;
      r RECORD;
      cnt INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'event_damage'
        AND location = p_location;

      SELECT coalesce(max(id), 0) INTO finishid
      FROM event_damage
      WHERE location = p_location;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;

      WHILE startid < finishid LOOP

        SELECT datehierarchy INTO olddh
        FROM event_damage
        WHERE id = startid
          AND location = p_location;

        EXECUTE 'SELECT datehierarchy FROM partitions.event_damage_'||olddh||' '||
                'WHERE id > '||startid||' AND location = '''||p_location||''' LIMIT 1' INTO dh;

        IF dh is null THEN

          SELECT min(substring(c.relname from E'........$')::integer) INTO dh
          FROM pg_inherits
            JOIN pg_class c ON (inhrelid=c.oid)
            JOIN pg_class p ON (inhparent=p.oid)
          WHERE p.relname = 'event_damage'
            AND substring(c.relname from E'........$')::integer > olddh;

          IF dh is null THEN RAISE 'cannot find partition'; END IF;
        END IF;

        -- determine current partition
    --        SELECT datehierarchy INTO dh
    --        FROM event_damage e
    --        WHERE id = (SELECT min(id) FROM event_damage WHERE id > startid);

        EXECUTE 'SELECT COUNT(*) FROM event_damage WHERE datehierarchy = '||dh||
                ' AND location = '''||p_location||'''' INTO cnt;
        RAISE NOTICE '% aggregating % rows from partition % ...', clock_timestamp(), cnt, dh;

        -- aggregate buildings
        FOR r IN 
        EXECUTE  -- Tower, Building, MainBuilding
        ' SELECT datehierarchy, location, characterid, map, sessiontype, opponentid, dealt,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND location = '''||p_location||'''
            AND unittype in (6, 7, 8) 
            AND sessiontype != 5
          GROUP BY datehierarchy, location, characterid, map, sessiontype, opponentid, dealt ' 
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_building e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.buildingid = r.opponentid
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_building e
            SET sessioncount = sessioncount + r.stpcnt,
                physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.buildingid = r.opponentid
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_building (datehierarchy, location, characterid, map, sessiontype, sessioncount, buildingid, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.location, r.characterid, r.map, r.sessiontype, r.stpcnt, r.opponentid, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        RAISE NOTICE '% buildings done', clock_timestamp();

        -- aggregate characters
        FOR r IN 
        EXECUTE  -- HeroMale, HeroFemale
        ' SELECT datehierarchy, location, characterid, map, sessiontype, opponentid, dealt,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND location = '''||p_location||'''
            AND unittype in (0, 1) 
            AND sessiontype != 5
          GROUP BY datehierarchy, location, characterid, map, sessiontype, opponentid, dealt ' 
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_character e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.opponentcharacterid = r.opponentid
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_character e
            SET sessioncount = sessioncount + r.stpcnt,
                physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.opponentcharacterid = r.opponentid
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_character (datehierarchy, location, characterid, map, sessiontype, sessioncount, opponentcharacterid, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.location, r.characterid, r.map, r.sessiontype, r.stpcnt, r.opponentid, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        RAISE NOTICE '% characters done', clock_timestamp();
        
        -- aggregate creature
        FOR r IN 
        EXECUTE  -- Summon, Creep, SiegeCreep, NeutralCreep, NeutralChampion, NeutralBoss
        ' SELECT datehierarchy, location, characterid, map, sessiontype, opponentid, dealt,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND location = '''||p_location||'''
            AND unittype in (2, 3, 4, 5, 18, 19) 
            AND sessiontype != 5
          GROUP BY datehierarchy, location, characterid, map, sessiontype, opponentid, dealt ' 
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_creature e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.creatureid = r.opponentid
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_creature e
            SET sessioncount = sessioncount + r.stpcnt,
                physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.creatureid = r.opponentid
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_creature (datehierarchy, location, characterid, map, sessiontype, sessioncount, creatureid, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.location, r.characterid, r.map, r.sessiontype, r.stpcnt, r.opponentid, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        RAISE NOTICE '% creatures done', clock_timestamp();
        
        -- aggregate unittype
        FOR r IN 
        EXECUTE
        ' SELECT datehierarchy, location, characterid, map, sessiontype, unittype, dealt,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 SUM(physicaldamage) pdmg, SUM(magicaldamage) mdmg, SUM(puredamage) dmg
          FROM event_damage
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND location = '''||p_location||'''
            AND sessiontype != 5
          GROUP BY datehierarchy, location, characterid, map, sessiontype, unittype, dealt ' 
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_damage_agg_unittype e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.unittype = r.unittype
              AND e.dealt = r.dealt )
          THEN
            UPDATE event_damage_agg_unittype e
            SET sessioncount = sessioncount + r.stpcnt,
                physicaldamage = physicaldamage + r.pdmg,
                magicaldamage = magicaldamage + r.mdmg,
                puredamage = puredamage + r.dmg
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.unittype = r.unittype
              AND e.dealt = r.dealt;
          ELSE
            INSERT INTO event_damage_agg_unittype (datehierarchy, location, characterid, map, sessiontype, sessioncount, unittype, dealt, physicaldamage, magicaldamage, puredamage)
            VALUES (r.datehierarchy, r.location, r.characterid, r.map, r.sessiontype, r.stpcnt, r.unittype, r.dealt, r.pdmg, r.mdmg, r.dmg);
          END IF;
        END LOOP;

        RAISE NOTICE '% unittypes done', clock_timestamp();
        
        RAISE NOTICE 'done...';
        EXECUTE 'SELECT max(id) FROM event_damage WHERE datehierarchy = '||dh|| 
                ' AND location = '''||p_location||'''' INTO startid;
      END LOOP;

      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'event_damage'
        AND location = p_location;

      RAISE NOTICE '% finished!', clock_timestamp();
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_event_damage(varchar) OWNER TO dbadmin;


    ALTER TABLE event_naftaincome_agg_minute ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE event_naftaincome_agg_minute ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE event_naftaincome_agg_minute DROP CONSTRAINT event_naftaincome_agg_minute_unique;
    ALTER TABLE event_naftaincome_agg_minute ADD CONSTRAINT event_naftaincome_agg_minute_pkey
      PRIMARY KEY (datehierarchy, location, characterid, map, sessiontype, incomefrom, minute);

    DROP FUNCTION aggregate_event_naftaincome();

    CREATE OR REPLACE FUNCTION aggregate_event_naftaincome(p_location varchar)
      RETURNS void AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      dh INTEGER;
      olddh INTEGER;
      r RECORD;
      cnt INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'event_naftaincome'
        AND location = p_location;

      SELECT coalesce(max(id), 0) INTO finishid
      FROM event_naftaincome
      WHERE location = p_location;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;
      RAISE NOTICE 'startid = %, finishid = %', startid, finishid;

      WHILE startid < finishid LOOP

        SELECT datehierarchy INTO olddh
        FROM event_naftaincome
        WHERE id = startid
          AND location = p_location;

        EXECUTE 'SELECT datehierarchy FROM partitions.event_naftaincome_'||olddh||' '||
                'WHERE id > '||startid||' AND location = '''||p_location||''' LIMIT 1' INTO dh;

        IF dh is null THEN

          SELECT min(substring(c.relname from E'........$')::integer) INTO dh
          FROM pg_inherits
            JOIN pg_class c ON (inhrelid=c.oid)
            JOIN pg_class p ON (inhparent=p.oid)
          WHERE p.relname = 'event_naftaincome'
            AND substring(c.relname from E'........$')::integer > olddh;

          IF dh is null THEN RAISE 'cannot find partition'; END IF;
        END IF;

        -- determine current partition
    --        SELECT datehierarchy INTO dh
    --        FROM event_naftaincome e
    --        WHERE id = (SELECT min(id) FROM event_naftaincome WHERE id > startid);

        EXECUTE 'SELECT COUNT(*) FROM event_naftaincome WHERE datehierarchy = '||dh||
                'AND location = '''||p_location||'''' INTO cnt;
        RAISE NOTICE '% aggregating % rows from partition % ...', clock_timestamp(), cnt, dh;

        FOR r IN
        EXECUTE
        '  SELECT datehierarchy, location, characterid, map, sessiontype, step/600+1 as minute,
                 COUNT(distinct sessiontoplayerid) as stpcnt,
                 CASE WHEN incomefrom = 0 THEN ''hero''
                      WHEN incomefrom = 1 THEN ''creature''
                      WHEN incomefrom = 2 THEN ''building''
                      WHEN incomefrom = 3 THEN ''talent''
                      WHEN incomefrom = 4 THEN ''impulsivebuff''
                      WHEN incomefrom = 5 THEN ''minigame''
                      ELSE ''undefined'' END as strincomefrom,
                 SUM(naftaforkill) nfk, SUM(naftaspecforkill) nsfk, SUM(teamnaftaforkill) tnfk, SUM(nafta) n
          FROM event_naftaincome
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND location = '''||p_location||'''
            AND sessiontype != 5
          GROUP BY datehierarchy, location, characterid, map, sessiontype, step/600+1, strincomefrom '
        LOOP
          IF EXISTS (
            SELECT 1 FROM event_naftaincome_agg_minute e
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.incomefrom = r.strincomefrom
              AND e.minute = r.minute )
          THEN
            UPDATE event_naftaincome_agg_minute e
            SET sessioncount = sessioncount + r.stpcnt,
                naftaforkill = naftaforkill + r.nfk,
                naftaspecforkill = naftaspecforkill + r.nsfk,
                teamnaftaforkill = teamnaftaforkill + r.tnfk,
                nafta = nafta + r.n
            WHERE e.datehierarchy = r.datehierarchy
              AND e.location = r.location
              AND e.characterid = r.characterid
              AND e.map = r.map
              AND e.sessiontype = r.sessiontype
              AND e.incomefrom = r.strincomefrom
              AND e.minute = r.minute;
          ELSE
            INSERT INTO event_naftaincome_agg_minute (datehierarchy, location, characterid, map, sessiontype, sessioncount, incomefrom, minute, naftaforkill, naftaspecforkill, teamnaftaforkill, nafta)
            VALUES (r.datehierarchy, r.location, r.characterid, r.map, r.sessiontype, r.stpcnt, r.strincomefrom, r.minute, r.nfk, r.nsfk, r.tnfk, r.n);
          END IF;
        END LOOP;

        RAISE NOTICE 'done...';
        EXECUTE 'SELECT max(id) FROM event_naftaincome WHERE datehierarchy = '||dh||
                ' AND location = '''||p_location||'''' INTO startid;
      END LOOP;

      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'event_naftaincome'
        AND location = p_location;

      RAISE NOTICE '% finished!', clock_timestamp();
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_event_naftaincome(varchar) OWNER TO dbadmin;


    ALTER TABLE resourcelog_agg_source ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE resourcelog_agg_source ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE resourcelog_agg_source DROP CONSTRAINT resourcelog_agg_source_unique;
    ALTER TABLE resourcelog_agg_source ADD CONSTRAINT resourcelog_agg_source_unique
      UNIQUE (datehierarchy, location, source, buildingname, gain);

    DROP FUNCTION aggregate_resourcelog();

    CREATE OR REPLACE FUNCTION aggregate_resourcelog(p_location varchar)
      RETURNS void AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      dh INTEGER;
      olddh INTEGER;
      r RECORD;
      cnt INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'resourcelog'
        AND location = p_location;

      IF startid = 0
      THEN
        SELECT coalesce(min(id), 0) INTO startid
        FROM resourcelog
        WHERE location = p_location;
      END IF;

      SELECT coalesce(max(id), 0) INTO finishid
      FROM resourcelog
      WHERE location = p_location;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;
      RAISE NOTICE 'startid = %, finishid = %', startid, finishid;

      WHILE startid < finishid LOOP

        SELECT datehierarchy INTO olddh
        FROM resourcelog
        WHERE id = startid
          AND location = p_location;

        EXECUTE 'SELECT datehierarchy FROM partitions.resourcelog_'||olddh||' '||
                'WHERE id > '||startid||' AND location = '''||p_location||''' LIMIT 1' INTO dh;

        IF dh is null THEN

          SELECT min(substring(c.relname from E'........$')::integer) INTO dh
          FROM pg_inherits
            JOIN pg_class c ON (inhrelid=c.oid)
            JOIN pg_class p ON (inhparent=p.oid)
          WHERE p.relname = 'resourcelog'
            AND substring(c.relname from E'........$')::integer > olddh;

          IF dh is null THEN RAISE 'cannot find partition'; END IF;
        END IF;

        -- determine current partition
    --        SELECT datehierarchy INTO dh
    --        FROM resourcelog e
    --        WHERE id = (SELECT min(id) FROM resourcelog WHERE id > startid);

        EXECUTE 'SELECT COUNT(*) FROM resourcelog WHERE datehierarchy = '||dh||
                ' AND location = '''||p_location||'''' INTO cnt;
        RAISE NOTICE '% aggregating % rows from partition % ...', clock_timestamp(), cnt, dh;

        FOR r IN
        EXECUTE
        ' SELECT datehierarchy, location, source, buildingname, gain,
                 SUM(goldchange) gld, SUM(silverchange) slv, SUM(perlchange) prl, SUM(populationchange) ppl,
                 SUM(resource1change) rs1, SUM(resource2change) rs2, SUM(resource3change) rs3
          FROM resourcelog
          WHERE datehierarchy = '||dh||'
            AND id > '||startid||'
            AND location = '''||p_location||'''
          GROUP BY datehierarchy, location, source, buildingname, gain '
        LOOP
          IF EXISTS (
            SELECT 1 FROM resourcelog_agg_source
            WHERE datehierarchy = r.datehierarchy
              AND location = r.location
              AND source = r.source
              AND ((buildingname is null AND r.buildingname is null) OR buildingname = r.buildingname)
              AND gain = r.gain )
          THEN
            UPDATE resourcelog_agg_source
            SET goldchange = goldchange + r.gld,
                silverchange = silverchange + r.slv,
                perlchange = perlchange + r.prl,
                populationchange = populationchange + r.ppl,
                resource1change = resource1change + r.rs1,
                resource2change = resource2change + r.rs2,
                resource3change = resource3change + r.rs3
            WHERE datehierarchy = r.datehierarchy
              AND location = r.location
              AND source = r.source
              AND ((buildingname is null AND r.buildingname is null) OR buildingname = r.buildingname)
              AND gain = r.gain;
          ELSE
            INSERT INTO resourcelog_agg_source (datehierarchy, location, source, buildingname, gain, goldchange, silverchange, perlchange, populationchange, resource1change, resource2change, resource3change)
            VALUES (r.datehierarchy, r.location, r.source, r.buildingname, r.gain, r.gld, r.slv, r.prl, r.ppl, r.rs1, r.rs2, r.rs3);
          END IF;
        END LOOP;

        RAISE NOTICE 'done...';
        EXECUTE 'SELECT max(id) FROM resourcelog WHERE datehierarchy = '||dh||
                ' AND location = '''||p_location||'''' INTO startid;
      END LOOP;

      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'resourcelog'
        AND location = p_location;

      RAISE NOTICE '% finished!', clock_timestamp();
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_resourcelog(varchar) OWNER TO dbadmin;


    ALTER TABLE socialsession_agg_dau ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE socialsession_agg_dau ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE socialsession_agg_dau DROP CONSTRAINT socialsession_agg_dau_pkey;
    ALTER TABLE socialsession_agg_dau ADD CONSTRAINT socialsession_agg_dau_pkey
      PRIMARY KEY (datehierarchy, location);

    DROP FUNCTION aggregate_socialsession();

    CREATE OR REPLACE FUNCTION aggregate_socialsession(p_location varchar)
      RETURNS void AS
    $$
    DECLARE
      startid BIGINT;
      finishid BIGINT;
      r RECORD;
      dau2 INTEGER;
      sessions2 INTEGER;
    BEGIN
      SELECT lastid INTO startid
      FROM sys_aggregation_ranges
      WHERE tablename = 'socialsession'
        AND location = p_location;

      IF startid = 0
      THEN
        SELECT coalesce(min(id), 0) INTO startid
        FROM resourcelog
        WHERE location = p_location;
      END IF;

      SELECT coalesce(max(id), 0) INTO finishid
      FROM socialsession
      WHERE location = p_location;

      IF startid >= finishid
      THEN
        RAISE NOTICE 'Incorrect ids range: % <= %', startid, finishid;
        EXIT;
      END IF;
      RAISE NOTICE 'startid = %, finishid = %', startid, finishid;

      FOR r IN (
        SELECT datehierarchy, location, count(distinct player) dau, count(*) sessions
        FROM socialsession
        WHERE id >  startid
          AND id <= finishid
          AND location = p_location
        GROUP BY datehierarchy, location )
      LOOP
        RAISE NOTICE '%...', r.datehierarchy;    
        IF EXISTS (
          SELECT 1 FROM socialsession_agg_dau 
          WHERE datehierarchy = r.datehierarchy
            AND location = p_location )
        THEN
          UPDATE socialsession_agg_dau
          SET dau = dau + r.dau,
              sessions = sessions + r.sessions
          WHERE datehierarchy = r.datehierarchy
            AND location = p_location;
        ELSE
          SELECT count(distinct player), count(*) INTO dau2, sessions2
          FROM socialsession
          WHERE datehierarchy = to_char(to_date(r.datehierarchy::text,'yyyyMMdd')-interval '1 day','yyyyMMdd')::integer
            AND endtime >= to_date(r.datehierarchy::text,'yyyyMMdd')
            AND location = p_location;
          
          INSERT INTO socialsession_agg_dau (datehierarchy, location, dau, sessions) 
          VALUES (r.datehierarchy, r.location, r.dau, r.sessions);
        END IF;
      END LOOP;
      
      UPDATE sys_aggregation_ranges
      SET lastid = finishid
      WHERE tablename = 'socialsession'
        AND location = p_location;

      RAISE NOTICE '% finished!', clock_timestamp();
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION aggregate_socialsession(varchar) OWNER TO dbadmin;    


    ALTER TABLE playercharacter_ratingbypush ADD COLUMN location varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE playercharacter_ratingbypush ALTER COLUMN location DROP DEFAULT;
    ALTER TABLE playercharacter_ratingbypush DROP CONSTRAINT playercharacter_ratingbypush_unique;
    ALTER TABLE playercharacter_ratingbypush ADD CONSTRAINT playercharacter_ratingbypush_pkey
      PRIMARY KEY (playercharacter, push, location);


    DROP FUNCTION fill_playercharacter_ratingbypush(integer);

    CREATE OR REPLACE FUNCTION fill_playercharacter_ratingbypush(p_stpid integer, p_location varchar)
      RETURNS VOID AS
    $$
    DECLARE
      p character varying;
      data record;
      mindh integer := 0;
      rt integer;
      rl integer;
      f real;
    BEGIN
      IF EXISTS (SELECT 1 FROM sessiontoplayer where id = p_stpid )
      THEN 
        SELECT timehierarchyid INTO mindh
        FROM gamesession gs 
          JOIN sessiontoplayer stp ON stp.gamesession = gs.id AND stp.location = gs.location
        WHERE stp.id = p_stpid
          AND stp.location = p_location;
      END IF;

      FOR p IN (SELECT DISTINCT d.push FROM datehierarchy d WHERE d.push IS NOT NULL AND d.id >= mindh)
      LOOP
        FOR data IN (
          SELECT stp.playercharacter as pc,
                 MAX(stp.id) as maxstpid,
                 (SELECT gs2.persistentid 
                  FROM sessiontoplayer stp2 JOIN gamesession gs2 on gs2.id = stp2.gamesession
                  WHERE stp2.id = MAX(stp.id)) as persistid
          FROM sessiontoplayer stp
            JOIN gamesession gs on gs.id = stp.gamesession AND stp.location = gs.location
            JOIN datehierarchy d on d.id = gs.timehierarchyid
          WHERE d.push = p
            AND stp.ratingtotal > 0
            AND stp.id >= p_stpid
            AND stp.location = p_location
          GROUP BY stp.playercharacter)
        LOOP
          SELECT ratingtotal, reliabilitytotal INTO rt, rl
          FROM sessiontoplayer WHERE id = data.maxstpid AND location = p_location;

          SELECT mp.force INTO f
          FROM mmakingsession ms 
            JOIN mmakingplayer mp on mp.mmakingsession = ms.id AND mp.location = ms.location
          WHERE ms.persistentid = data.persistid
            AND mp.playercharacter = data.pc
            AND ms.location = p_location;
          IF NOT FOUND THEN f := 0; END IF;

          IF EXISTS (SELECT 1 FROM playercharacter_ratingbypush 
                     WHERE playercharacter = data.pc AND push = p AND location = p_location)
          THEN
            UPDATE playercharacter_ratingbypush
            SET rating = rt, reliability = rl, force = f
            WHERE playercharacter = data.pc 
              AND push = p
              AND location = p_location;
          ELSE
            INSERT INTO playercharacter_ratingbypush 
            VALUES (data.pc, p_location, p, rt, rl, f);
          END IF;
        END LOOP;
      END LOOP;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION fill_playercharacter_ratingbypush(integer, varchar) OWNER TO dbadmin;


    DROP FUNCTION fill_talentswitchedoff();

    CREATE OR REPLACE FUNCTION fill_talentswitchedoff(p_location varchar)
      RETURNS void AS
    $$
    DECLARE
      t_id bigint;
      duration integer;
      r record;
    BEGIN
      for r in (
        select * from tmp_talentswitchedoff 
        where location = p_location 
        order by sessiontoplayerid, step )
      loop        
        select t.id, r.step - t.step into t_id, duration
        from event_talentused t
        where t.sessiontoplayerid = r.sessiontoplayerid
          and t.talentid = r.talentid
          and t.step < r.step
          and t.location = p_location
        order by t.step desc;

        if not found then raise notice 'Not found event_talentused for event %', r; end if;

        execute 
        'update event_talentused set duration = ' || cast(duration as real)/10 ||' '||
        'where id = ' || t_id || ' and location = '''||p_location||'''';
      end loop;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION fill_talentswitchedoff(varchar) OWNER TO dbadmin;


    DROP FUNCTION update_mgsession(bigint, bigint, bigint);

    CREATE OR REPLACE FUNCTION update_mgsession(p_id bigint, p_step bigint, p_stpid bigint, p_location varchar)
    RETURNS VOID AS 
    $$
    BEGIN
      UPDATE event_mg_session
      SET finishid = p_id,
          finishstep = p_step
      WHERE startid = ( SELECT MAX(startid) FROM event_mg_session
                        WHERE sessiontoplayerid = p_stpid
                          AND startstep <= p_step
                          AND location = p_location )
        AND location = p_location;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION update_mgsession(bigint, bigint, bigint, varchar) OWNER TO dbadmin;


    DROP FUNCTION update_mglevel(bigint, bigint, bigint, boolean);

    CREATE OR REPLACE FUNCTION update_mglevel(p_id bigint, p_step bigint, p_stpid bigint, p_success boolean, p_location varchar)
    RETURNS VOID AS 
    $$
    BEGIN
      UPDATE event_mg_level
      SET finishid = p_id,
          finishstep = p_step,
          success = p_success
      WHERE startid = (SELECT MAX(l.startid) FROM event_mg_level l
                         JOIN event_mg_session s ON s.startid = l.mgsessionid AND s.location = l.location
                       WHERE s.sessiontoplayerid = p_stpid
                         AND s.startstep <= p_step 
                         AND l.startstep <= p_step )
        AND location = p_location;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION update_mglevel(bigint, bigint, bigint, boolean, varchar) OWNER TO dbadmin;


    select increment_version_to(106) into ver;
  end if;

  if ver = 106
  then
    ALTER TABLE launcherevents RENAME timestamp to clienttimestamp;
    ALTER TABLE launcherevents ADD COLUMN servertimestamp timestamp;

    select increment_version_to(107) into ver;
  end if;

  if ver = 107
  then
    ALTER TABLE player ADD COLUMN locale character varying NOT NULL DEFAULT 'RU';
    ALTER TABLE player ALTER COLUMN locale DROP DEFAULT;

    select increment_version_to(108) into ver;
  end if;

  if ver = 108
  then
    ALTER TABLE gamesession DROP CONSTRAINT gamesession_unique_persistentid;

    UPDATE gamesession
    SET persistentid = idclient
    WHERE persistentid IS NULL;

    ALTER TABLE gamesession ALTER COLUMN persistentid SET NOT NULL;
    ALTER TABLE gamesession DROP COLUMN idclient;

    CREATE INDEX idx_gamesession_persistentid ON gamesession (persistentid);

    ALTER TABLE offlineevent ALTER COLUMN auxdata TYPE bigint;

    select increment_version_to(109) into ver;
  end if;

  if ver = 109
  then
    CREATE TABLE gstraffic
    (
      id bigint NOT NULL,
      location varchar NOT NULL,
      gamesessionid integer NOT NULL,
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
      CONSTRAINT gstraffic_pkey PRIMARY KEY (id, location),
      CONSTRAINT gstraffic_gamesessionid_fkey FOREIGN KEY (gamesessionid, location) REFERENCES gamesession (id, location)
    );
    ALTER TABLE gstraffic OWNER TO dbadmin;
    GRANT SELECT ON TABLE gstraffic TO ro;

    CREATE INDEX idx_gstraffic_gamesessionid ON gstraffic (gamesessionid);

    select increment_version_to(110) into ver;
  end if;

  if ver = 110
  then
    ALTER TABLE sessiontoplayer ADD COLUMN relayaddress varchar;
    ALTER TABLE sessiontoplayer DROP COLUMN spring;

    select increment_version_to(111) into ver;
  end if;

  if ver = 111
  then
    ALTER TABLE player ADD COLUMN syncwith varchar NOT NULL DEFAULT 'ru0';
    ALTER TABLE player ALTER COLUMN syncwith DROP DEFAULT;

    select increment_version_to(112) into ver;
  end if;

  if ver = 112
  then
    ALTER TABLE resourcelog ADD COLUMN persistentid bigint;

    select increment_version_to(113) into ver;
  end if;

  if ver = 113
  then
    ALTER TABLE playercharacter ADD COLUMN analysisid serial;
    ALTER TABLE playercharacter ADD CONSTRAINT playercharacter_unique_analysisid UNIQUE (analysisid);
    ALTER TABLE gamesession ADD COLUMN analysisid serial;
    ALTER TABLE gamesession ADD CONSTRAINT gamesession_unique_analysisid UNIQUE (analysisid);
    ALTER TABLE sessiontoplayer ADD COLUMN analysisid serial;
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_unique_analysisid UNIQUE (analysisid);

    ALTER TABLE sessiontoplayer ADD COLUMN playercharacter_analysisid integer;
    ALTER TABLE sessiontoplayer ADD COLUMN gamesession_analysisid integer;
    
    UPDATE sessiontoplayer stp
    SET playercharacter_analysisid = pc.analysisid,
        gamesession_analysisid = gs.analysisid
    FROM playercharacter pc, gamesession gs
    WHERE pc.id = stp.playercharacter AND pc.location = stp.location
      AND gs.id = stp.gamesession AND gs.location = stp.location;

    ALTER TABLE sessiontoplayer ALTER COLUMN playercharacter_analysisid SET NOT NULL;
    ALTER TABLE sessiontoplayer ALTER COLUMN gamesession_analysisid SET NOT NULL;
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_playercharacter_analysisid_fkey
      FOREIGN KEY (playercharacter_analysisid) REFERENCES playercharacter (analysisid);
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_gamesession_analysisid_fkey
      FOREIGN KEY (gamesession_analysisid) REFERENCES gamesession (analysisid);
    CREATE INDEX idx_sessiontoplayer_playercharacter_analysisid ON sessiontoplayer (playercharacter_analysisid);
    CREATE INDEX idx_sessiontoplayer_gamesession_analysisid ON sessiontoplayer (gamesession_analysisid);

    ALTER TABLE characterunlock ADD COLUMN playercharacter_analysisid integer;

    UPDATE characterunlock cu
    SET playercharacter_analysisid = pc.analysisid
    FROM playercharacter pc
    WHERE pc.id = cu.playercharacter
      AND pc.location = cu.location;

    ALTER TABLE characterunlock ALTER COLUMN playercharacter_analysisid SET NOT NULL;
    ALTER TABLE characterunlock ADD CONSTRAINT characterunlock_playercharacter_analysisid_fkey 
      FOREIGN KEY (playercharacter_analysisid) REFERENCES playercharacter (analysisid);
    CREATE INDEX idx_characterunlock_playercharacter_analysisid ON characterunlock (playercharacter_analysisid);

    ALTER TABLE event_kill ADD COLUMN sessiontoplayer_analysisid integer;
    UPDATE event_kill e SET sessiontoplayer_analysisid = stp.analysisid
    FROM sessiontoplayer stp WHERE stp.id = e.sessiontoplayerid AND stp.location = e.location;
    ALTER TABLE event_kill ALTER COLUMN sessiontoplayer_analysisid SET NOT NULL;
    ALTER TABLE event_kill ADD CONSTRAINT event_kill_sessiontoplayer_analysisid_fkey 
      FOREIGN KEY (sessiontoplayer_analysisid) REFERENCES sessiontoplayer (analysisid);
    CREATE INDEX idx_event_kill_sessiontoplayer_analysisid ON event_kill (sessiontoplayer_analysisid);

    ALTER TABLE event_assist ADD COLUMN sessiontoplayer_analysisid integer;
    UPDATE event_assist e SET sessiontoplayer_analysisid = stp.analysisid
    FROM sessiontoplayer stp WHERE stp.id = e.sessiontoplayerid AND stp.location = e.location;
    ALTER TABLE event_assist ALTER COLUMN sessiontoplayer_analysisid SET NOT NULL;
    ALTER TABLE event_assist ADD CONSTRAINT event_assist_sessiontoplayer_analysisid_fkey 
      FOREIGN KEY (sessiontoplayer_analysisid) REFERENCES sessiontoplayer (analysisid);
    CREATE INDEX idx_event_assist_sessiontoplayer_analysisid ON event_assist (sessiontoplayer_analysisid);

    ALTER TABLE event_death ADD COLUMN sessiontoplayer_analysisid integer;
    UPDATE event_death e SET sessiontoplayer_analysisid = stp.analysisid
    FROM sessiontoplayer stp WHERE stp.id = e.sessiontoplayerid AND stp.location = e.location;
    ALTER TABLE event_death ALTER COLUMN sessiontoplayer_analysisid SET NOT NULL;
    ALTER TABLE event_death ADD CONSTRAINT event_death_sessiontoplayer_analysisid_fkey 
      FOREIGN KEY (sessiontoplayer_analysisid) REFERENCES sessiontoplayer (analysisid);
    CREATE INDEX idx_event_death_sessiontoplayer_analysisid ON event_death (sessiontoplayer_analysisid);

    select increment_version_to(114) into ver;
  end if;

  if ver = 114
  then
    CREATE TABLE talentjoinsession
    (
      id bigint NOT NULL,
      location varchar NOT NULL,
      player bigint NOT NULL,
      character integer NOT NULL,
      sessiontoplayer integer NOT NULL,
      talent integer NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT talentjoinsession_pkey PRIMARY KEY (id, location),
      CONSTRAINT talentjoinsession_sessiontoplayer_fkey FOREIGN KEY (sessiontoplayer, location) REFERENCES sessiontoplayer (id, location),
      CONSTRAINT talentjoinsession_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT talentjoinsession_character_fkey FOREIGN KEY (character) REFERENCES character (id),
      CONSTRAINT talentjoinsession_talent_fkey FOREIGN KEY (talent) REFERENCES talent (id),
      CONSTRAINT talentjoinsession_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE talentjoinsession OWNER TO dbadmin;
    GRANT SELECT ON TABLE talentjoinsession TO ro;

    CREATE INDEX idx_talentjoinsession_datehierarchy ON talentjoinsession (datehierarchy);
    CREATE INDEX idx_talentjoinsession_sessiontoplayer ON talentjoinsession (sessiontoplayer);
    CREATE INDEX idx_talentjoinsession_character ON talentjoinsession (character);

    select increment_version_to(115) into ver;
  end if;

  if ver = 115
  then
    ALTER TABLE talentroll DROP CONSTRAINT talentroll_sessiontoplayer_fkey;
    ALTER TABLE talentroll DROP CONSTRAINT talentroll_sessiontoplayerid_fkey;

    ALTER TABLE talentroll ADD COLUMN stplocation character varying;
    UPDATE talentroll SET stplocation = location;
    ALTER TABLE talentroll ALTER COLUMN stplocation SET NOT NULL;

    ALTER TABLE talentroll ADD CONSTRAINT talentroll_sessiontoplayer_fkey 
      FOREIGN KEY (sessiontoplayer, stplocation) REFERENCES sessiontoplayer (id, location);

    ALTER TABLE sessiontoplayer ADD COLUMN rloglocation character varying;
    UPDATE sessiontoplayer SET rloglocation = location WHERE resourcelog is not null;

    select increment_version_to(116) into ver;
  end if;

  if ver = 116
  then
    ALTER TABLE mmakingplayer DROP COLUMN partymembers;
    ALTER TABLE sessiontoplayer ADD COLUMN partymembers integer;

    FOR tmprow IN (
      SELECT stp.id AS stpid, gs.persistentid, stp.playercharacter
      FROM sessiontoplayer stp
        JOIN gamesession gs ON gs.id = stp.gamesession AND gs.location = stp.location
      WHERE gs.timehierarchyid >= to_char(now()-interval'1month','yyyyMMdd')::integer
        AND stp.location = 'ru0' )
    LOOP
      SELECT mp.party into i1
      FROM mmakingplayer mp
        JOIN mmakingsession ms ON ms.id = mp.mmakingsession AND ms.location = mp.location
      WHERE ms.persistentid = tmprow.persistentid
        AND mp.playercharacter = tmprow.playercharacter
        AND mp.party != 0;

      IF FOUND 
      THEN 
        SELECT count(*) into i2
        FROM mmakingplayer mp
          JOIN mmakingsession ms ON ms.id = mp.mmakingsession AND ms.location = mp.location
        WHERE ms.persistentid = tmprow.persistentid
          AND mp.party = i1;

        UPDATE sessiontoplayer SET partymembers = i2
        WHERE id = r.stpid;
      END IF;
    END LOOP;
    
    select increment_version_to(117) into ver;
  end if;

  if ver = 117
  then
    CREATE TABLE guild 
    (
      id bigint NOT NULL,
      shortname varchar,
      fullname varchar,
      faction integer NOT NULL,
      creator bigint NOT NULL,
      creationdate timestamp NOT NULL,
      disbandingdate timestamp,
      resourcelog bigint,
      lastmodified timestamp NOT NULL,
      CONSTRAINT guild_pkey PRIMARY KEY (id),
      CONSTRAINT guild_player_fkey FOREIGN KEY (creator) REFERENCES player (id)
    );
    ALTER TABLE guild OWNER TO dbadmin;
    GRANT SELECT ON TABLE guild TO ro;

    CREATE INDEX idx_guild_lastmodified ON guild (lastmodified);

    ALTER TABLE player ADD COLUMN guild bigint;

    CREATE TABLE guildmembership
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      guild bigint NOT NULL,
      joindate timestamp NOT NULL,
      leavedate timestamp,
      kicked boolean,
      lastmodified timestamp NOT NULL,
      CONSTRAINT guildmembership_pkey PRIMARY KEY (id),
      CONSTRAINT guildmembership_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT guildmembership_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id)
    );
    ALTER TABLE guildmembership OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildmembership TO ro;

    CREATE INDEX idx_guildmembership_lastmodified ON guildmembership (lastmodified);

    select increment_version_to(118) into ver;
  end if;

  if ver = 118
  then
    ALTER TABLE launcherstart ADD COLUMN locale varchar;
    ALTER TABLE launcherdaction ADD COLUMN locale varchar;
    ALTER TABLE launcherevents ADD COLUMN locale varchar;

    select increment_version_to(119) into ver;
  end if;

  if ver = 119
  then
    -- drop all rules
    FOR tmprow IN (SELECT * FROM pg_rules WHERE tablename in ('resourcelog','event_naftaincome','event_damage'))
    LOOP
      EXECUTE 'DROP RULE '||tmprow.rulename||' ON '||tmprow.tablename;
    END LOOP;

    -- replace them by triggers
    CREATE OR REPLACE FUNCTION resourcelog_insert_trigger()
      RETURNS trigger AS
    $$
      BEGIN
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the resourcelog_insert_trigger() function!';
        RETURN NULL;
      END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION resourcelog_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_resourcelog_partition BEFORE INSERT ON resourcelog
      FOR EACH ROW EXECUTE PROCEDURE resourcelog_insert_trigger();

    CREATE OR REPLACE FUNCTION event_naftaincome_insert_trigger()
      RETURNS trigger AS
    $$
      BEGIN
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_naftaincome_insert_trigger() function!';
        RETURN NULL;
      END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION event_naftaincome_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_event_naftaincome_partition BEFORE INSERT ON event_naftaincome
      FOR EACH ROW EXECUTE PROCEDURE event_naftaincome_insert_trigger();

    CREATE OR REPLACE FUNCTION event_damage_insert_trigger()
      RETURNS trigger AS
    $$
      BEGIN
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_damage_insert_trigger() function!';
        RETURN NULL;
      END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION event_damage_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_event_damage_partition BEFORE INSERT ON event_damage
      FOR EACH ROW EXECUTE PROCEDURE event_damage_insert_trigger();

    -- new version of partitions checking
    CREATE OR REPLACE FUNCTION partitions_check(tablename character varying)
      RETURNS void AS
    $$
    DECLARE
      r record;
      startdh integer;
      dh integer;
      elsifs text;
    BEGIN
      startdh = to_char(now()-interval'14days','yyyyMMdd')::integer;
      EXECUTE 'select datehierarchy from '||tablename||' where id = '||
              '(select max(id) from '||tablename||')' INTO dh;
      IF (dh < startdh) THEN startdh = dh; END IF;

      elsifs = '';
      FOR r IN (
        SELECT id FROM datehierarchy
        WHERE id >= startdh
          AND id <= to_char(now()+interval'1days','yyyyMMdd')::integer 
        ORDER BY id DESC )
      LOOP
        RAISE NOTICE 'creating partition %_%', tablename, r.id;
        PERFORM partition_every_day(tablename::regclass, r.id);

        elsifs = elsifs||'
        ELSIF ( NEW.datehierarchy = '||r.id||' ) THEN
          INSERT INTO partitions.'||tablename||'_'||r.id||' VALUES (NEW.*); ';
      END LOOP;

      -- replace insert trigger
      EXECUTE '
      CREATE OR REPLACE FUNCTION '||tablename||'_insert_trigger()
      RETURNS TRIGGER AS $CODE$
      BEGIN
        IF ( false ) THEN RAISE;'||elsifs||'
        ELSE
          RAISE EXCEPTION ''Unexpected datehierarchy value. Fix the '||tablename||'_insert_trigger() function!'';
        END IF;
        RETURN NULL;
      END;
      $CODE$ LANGUAGE plpgsql;';
      
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION partitions_check(character varying) OWNER TO dbadmin;

    select increment_version_to(120) into ver;
  end if;

  if ver = 120
  then
    IF NOT EXISTS (SELECT * FROM pg_tables WHERE tablename = 'billing_operationtypes' )
    THEN
      CREATE TABLE billing_operationtypes
      (
        id integer NOT NULL,
        name varchar NOT NULL,
        CONSTRAINT billing_operationtypes_pkey PRIMARY KEY (id)
      );
      ALTER TABLE billing_operationtypes OWNER TO dbadmin;
      GRANT SELECT ON TABLE billing_operationtypes TO ro;

      CREATE TABLE billing_paymentsystems
      (
        id integer NOT NULL,
        name varchar NOT NULL,
        priority integer NOT NULL,
        description varchar NOT NULL,
        CONSTRAINT billing_paymentsystems_pkey PRIMARY KEY (id)
      );
      ALTER TABLE billing_paymentsystems OWNER TO dbadmin;
      GRANT SELECT ON TABLE billing_paymentsystems TO ro;

      CREATE TABLE billing_operations
      (
        id integer NOT NULL,
        player bigint NOT NULL,
        type int NOT NULL,
        systemid integer,
        servicename varchar,
        userid integer NOT NULL,
        reason varchar,
        amount integer,
        timestamp timestamp,
        CONSTRAINT billing_operations_pkey PRIMARY KEY (id),
        CONSTRAINT billing_operations_type_fkey FOREIGN KEY (type) REFERENCES billing_operationtypes (id),
        CONSTRAINT billing_operations_systemid_fkey FOREIGN KEY (systemid) REFERENCES billing_paymentsystems (id)
      );
      ALTER TABLE billing_operations OWNER TO dbadmin;
      GRANT SELECT ON TABLE billing_operations TO ro;

      CREATE INDEX idx_billing_operations_timestamp ON billing_operations (timestamp);

      CREATE TABLE billing_writeoffs
      (
        operationid integer NOT NULL,
        systemid integer NOT NULL,
        amount integer NOT NULL,
        CONSTRAINT billing_writeoffs_operationid_fkey FOREIGN KEY (operationid) REFERENCES billing_operations (id),
        CONSTRAINT billing_writeoffs_systemid_fkey FOREIGN KEY (systemid) REFERENCES billing_paymentsystems (id)
      );
      ALTER TABLE billing_writeoffs OWNER TO dbadmin;
      GRANT SELECT ON TABLE billing_writeoffs TO ro;

      CREATE INDEX idx_billing_writeoffs_operationid ON billing_writeoffs (operationid);
    END IF;

    select increment_version_to(121) into ver;
  end if;

  if ver = 121
  then
    CREATE TABLE clientping
    (
      id bigserial NOT NULL,
      location varchar NOT NULL,
      playerid bigint,
      srvlocation varchar,
      ping integer NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT clientping_pkey PRIMARY KEY (id,location),
      CONSTRAINT clientping_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE clientping OWNER TO dbadmin;
    GRANT SELECT ON TABLE clientping TO ro;

    CREATE INDEX idx_clientping_datehierarchy ON clientping (datehierarchy);

    select increment_version_to(122) into ver;
  end if;

  if ver = 122
  then

    IF NOT EXISTS (SELECT 1 FROM pg_proc WHERE proname = 'event_exceedingsteptime_insert_trigger')
    THEN
      TRUNCATE TABLE event_exceedingsteptime;
      CREATE OR REPLACE FUNCTION event_exceedingsteptime_insert_trigger()
        RETURNS trigger AS $$
      BEGIN
        IF ( false ) THEN RAISE;
        ELSE
          RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_exceedingsteptime_insert_trigger() function!';
        END IF;
        RETURN NULL;
      END;
      $$ LANGUAGE plpgsql;
      ALTER FUNCTION event_exceedingsteptime_insert_trigger() OWNER TO dbadmin;
      PERFORM partitions_check('event_exceedingsteptime');
      CREATE TRIGGER tr_event_exceedingsteptime_partition BEFORE INSERT ON event_exceedingsteptime
        FOR EACH ROW EXECUTE PROCEDURE event_exceedingsteptime_insert_trigger();
    END IF;

    IF NOT EXISTS (SELECT 1 FROM pg_proc WHERE proname = 'talentjoinsession_insert_trigger')
    THEN
      TRUNCATE TABLE talentjoinsession;
      CREATE OR REPLACE FUNCTION talentjoinsession_insert_trigger()
        RETURNS trigger AS $$
      BEGIN
        IF ( false ) THEN RAISE;
        ELSE
          RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the talentjoinsession_insert_trigger() function!';
        END IF;
        RETURN NULL;
      END;
      $$ LANGUAGE plpgsql;
      ALTER FUNCTION talentjoinsession_insert_trigger() OWNER TO dbadmin;
      PERFORM partitions_check('talentjoinsession');
      CREATE TRIGGER tr_talentjoinsession_partition BEFORE INSERT ON talentjoinsession
        FOR EACH ROW EXECUTE PROCEDURE talentjoinsession_insert_trigger();
    END IF;

    IF NOT EXISTS (SELECT 1 FROM pg_proc WHERE proname = 'event_timeslice_insert_trigger')
    THEN
      TRUNCATE TABLE event_timeslice;
      ALTER TABLE event_timeslice ADD COLUMN datehierarchy integer NOT NULL;
      ALTER TABLE event_timeslice ADD CONSTRAINT event_timeslice_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
      CREATE INDEX idx_event_timeslice_datehierarchy ON event_timeslice (datehierarchy);
      CREATE OR REPLACE FUNCTION event_timeslice_insert_trigger()
        RETURNS trigger AS $$
      BEGIN
        IF ( false ) THEN RAISE;
        ELSE
          RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_timeslice_insert_trigger() function!';
        END IF;
        RETURN NULL;
      END;
      $$ LANGUAGE plpgsql;
      ALTER FUNCTION event_timeslice_insert_trigger() OWNER TO dbadmin;
      PERFORM partitions_check('event_timeslice');
      CREATE TRIGGER tr_event_timeslice_partition BEFORE INSERT ON event_timeslice
        FOR EACH ROW EXECUTE PROCEDURE event_timeslice_insert_trigger();
    END IF;

    IF NOT EXISTS (SELECT 1 FROM pg_proc WHERE proname = 'event_kill_insert_trigger')
    THEN
      TRUNCATE TABLE event_kill;
      ALTER TABLE event_kill ADD COLUMN datehierarchy integer NOT NULL;
      ALTER TABLE event_kill ADD CONSTRAINT event_kill_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
      CREATE INDEX idx_event_kill_datehierarchy ON event_kill (datehierarchy);
      CREATE OR REPLACE FUNCTION event_kill_insert_trigger()
        RETURNS trigger AS $$
      BEGIN
        IF ( false ) THEN RAISE;
        ELSE
          RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_kill_insert_trigger() function!';
        END IF;
        RETURN NULL;
      END;
      $$ LANGUAGE plpgsql;
      ALTER FUNCTION event_kill_insert_trigger() OWNER TO dbadmin;
      PERFORM partitions_check('event_kill');
      CREATE TRIGGER tr_event_kill_partition BEFORE INSERT ON event_kill
        FOR EACH ROW EXECUTE PROCEDURE event_kill_insert_trigger();
    END IF;

    IF NOT EXISTS (SELECT 1 FROM pg_proc WHERE proname = 'event_assist_insert_trigger')
    THEN
      TRUNCATE TABLE event_assist;
      ALTER TABLE event_assist ADD COLUMN datehierarchy integer NOT NULL;
      ALTER TABLE event_assist ADD CONSTRAINT event_assist_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
      CREATE INDEX idx_event_assist_datehierarchy ON event_assist (datehierarchy);
      CREATE OR REPLACE FUNCTION event_assist_insert_trigger()
        RETURNS trigger AS $$
      BEGIN
        IF ( false ) THEN RAISE;
        ELSE
          RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_assist_insert_trigger() function!';
        END IF;
        RETURN NULL;
      END;
      $$ LANGUAGE plpgsql;
      ALTER FUNCTION event_assist_insert_trigger() OWNER TO dbadmin;
      PERFORM partitions_check('event_assist');
      CREATE TRIGGER tr_event_assist_partition BEFORE INSERT ON event_assist
        FOR EACH ROW EXECUTE PROCEDURE event_assist_insert_trigger();
    END IF;

    IF NOT EXISTS (SELECT 1 FROM pg_proc WHERE proname = 'event_death_insert_trigger')
    THEN
      TRUNCATE TABLE event_death;
      ALTER TABLE event_death ADD COLUMN datehierarchy integer NOT NULL;
      ALTER TABLE event_death ADD CONSTRAINT event_death_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
      CREATE INDEX idx_event_death_datehierarchy ON event_death (datehierarchy);
      CREATE OR REPLACE FUNCTION event_death_insert_trigger()
        RETURNS trigger AS $$
      BEGIN
        IF ( false ) THEN RAISE;
        ELSE
          RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_death_insert_trigger() function!';
        END IF;
        RETURN NULL;
      END;
      $$ LANGUAGE plpgsql;
      ALTER FUNCTION event_death_insert_trigger() OWNER TO dbadmin;
      PERFORM partitions_check('event_death');
      CREATE TRIGGER tr_event_death_partition BEFORE INSERT ON event_death
        FOR EACH ROW EXECUTE PROCEDURE event_death_insert_trigger();
    END IF;

    select increment_version_to(123) into ver;
  end if;

  if ver = 123
  then

    CREATE TABLE rune
    (
      id integer NOT NULL,
      "name" varchar NOT NULL,
      deleted boolean NOT NULL,
      CONSTRAINT rune_pkey PRIMARY KEY (id)
    );
    ALTER TABLE rune OWNER TO dbadmin;
    GRANT SELECT ON TABLE rune TO ro;


    CREATE TABLE runeroll
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      persistentid bigint NOT NULL,
      rune integer NOT NULL,
      CONSTRAINT runeroll_pkey PRIMARY KEY (id),
      CONSTRAINT runeroll_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT runeroll_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id)
    );
    ALTER TABLE runeroll OWNER TO dbadmin;
    GRANT SELECT ON TABLE runeroll TO ro;

    CREATE INDEX idx_runeroll_persistentid ON runeroll (persistentid);
    CREATE INDEX idx_runeroll_player ON runeroll (player);


    CREATE TABLE runereplenish
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      rune integer NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT runereplenish_pkey PRIMARY KEY (id),
      CONSTRAINT runereplenish_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT runereplenish_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id),
      CONSTRAINT runereplenish_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE runereplenish OWNER TO dbadmin;
    GRANT SELECT ON TABLE runereplenish TO ro;

    CREATE INDEX idx_runereplenish_datehierarchy ON runereplenish (datehierarchy);
    CREATE INDEX idx_runereplenish_player ON runereplenish (player);


    CREATE TABLE runeunsoulbound
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      rune integer NOT NULL,
      talent integer NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT runeunsoulbound_pkey PRIMARY KEY (id),
      CONSTRAINT runeunsoulbound_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT runeunsoulbound_talent_fkey FOREIGN KEY (talent) REFERENCES talent (id),
      CONSTRAINT runeunsoulbound_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id),
      CONSTRAINT runeunsoulbound_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE runeunsoulbound OWNER TO dbadmin;
    GRANT SELECT ON TABLE runeunsoulbound TO ro;

    CREATE INDEX idx_runeunsoulbound_datehierarchy ON runeunsoulbound (datehierarchy);
    CREATE INDEX idx_runeunsoulbound_player ON runeunsoulbound (player);


    CREATE TABLE runeexpire
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      rune integer NOT NULL,
      transactionsleft integer NOT NULL,
      bonusleft integer NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT runeexpire_pkey PRIMARY KEY (id),
      CONSTRAINT runeexpire_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT runeexpire_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id),
      CONSTRAINT runeexpire_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE runeexpire OWNER TO dbadmin;
    GRANT SELECT ON TABLE runeexpire TO ro;

    CREATE INDEX idx_runeexpire_datehierarchy ON runeexpire (datehierarchy);
    CREATE INDEX idx_runeexpire_player ON runeexpire (player);


    select increment_version_to(124) into ver;
  end if;

  if ver = 124
  then

    ALTER TABLE runeroll ADD COLUMN timestamp timestamp;
    ALTER TABLE runeroll ADD COLUMN datehierarchy integer;
    ALTER TABLE runeroll ADD CONSTRAINT runeroll_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);
    CREATE INDEX idx_runeroll_datehierarchy ON runeroll (datehierarchy);

    select increment_version_to(125) into ver;
  end if;

  if ver = 125
  then

    CREATE INDEX idx_gamesession_location ON gamesession (location);
    CREATE INDEX idx_sessiontoplayer_location ON sessiontoplayer (location);

    select increment_version_to(126) into ver;
  end if;

  if ver = 126
  then
    ALTER TABLE talentjoinsession RENAME location TO sessiontoplayer_location;
    ALTER TABLE talentjoinsession DROP CONSTRAINT talentjoinsession_pkey;
    ALTER TABLE talentjoinsession ADD CONSTRAINT talentjoinsession_pkey PRIMARY KEY (id);

    ALTER TABLE talentjoinsession ADD COLUMN sessiontoplayer_analysisid integer;
    ALTER TABLE talentjoinsession ADD CONSTRAINT talentjoinsession_sessiontoplayer_analysisid_fkey
      FOREIGN KEY (sessiontoplayer_analysisid) REFERENCES sessiontoplayer (analysisid);

    CREATE INDEX idx_talentjoinsession_sessiontoplayer_analysisid 
      ON talentjoinsession (sessiontoplayer_analysisid);

    UPDATE talentjoinsession t
    SET sessiontoplayer_analysisid = stp.analysisid
    FROM sessiontoplayer stp
    WHERE stp.id = t.sessiontoplayer
      AND stp.location = t.sessiontoplayer_location;

    select increment_version_to(127) into ver;
  end if;

  if ver = 127
  then

    CREATE OR REPLACE FUNCTION update_stp_rating(p_persistentid bigint, p_player bigint, p_rchange bigint, p_rtotal bigint)
      RETURNS boolean AS
    $$
    BEGIN
      UPDATE sessiontoplayer stp
      SET ratingchange = p_rchange, ratingtotal = p_rtotal
      FROM gamesession gs, playercharacter pc
      WHERE gs.id = stp.gamesession AND gs.location = stp.location
        AND pc.id = stp.playercharacter AND pc.location = stp.location
        AND gs.persistentid = p_persistentid
        AND pc.player = p_player;

      RETURN true;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION update_stp_rating(bigint, bigint, bigint, bigint) OWNER TO dbadmin;

    select increment_version_to(128) into ver;
  end if;

  if ver = 128
  then
    DROP TABLE IF EXISTS sys_checks_missingrows;
    DROP TABLE IF EXISTS sys_checks_ignoredrows;
    DROP TABLE IF EXISTS sys_checks_scope;
    DROP TABLE IF EXISTS sys_droppeddata;
    DROP FUNCTION drop_everything(integer, character varying); -- what the irony
    DROP FUNCTION array_to_set(anyarray);

    CREATE TABLE pentaho_map
    (
      map character varying(255) NOT NULL,
      CONSTRAINT pentaho_map_pkey PRIMARY KEY (map)
    );
    ALTER TABLE pentaho_map OWNER TO dbadmin;
    GRANT SELECT ON TABLE pentaho_map TO ro;

    CREATE OR REPLACE VIEW v_sessiontoplayer_joined AS 
    SELECT stp.id AS stpid, 
           stp.location,
           stp.ratingtotal, 
           CASE
             WHEN stp.ratingtotal >= 2000 THEN '2000+'
             WHEN stp.ratingtotal < 1550 THEN '<1550'
             WHEN stp.ratingtotal >= 1550 AND stp.ratingtotal < 1750 THEN '1550-1750'
             WHEN stp.ratingtotal >= 1750 AND stp.ratingtotal < 2000 THEN '1750-2000'
             ELSE 'null'
           END AS ratinginterval, 
           CASE
             WHEN gs.sidewon = (-1) THEN 'None'
             WHEN stp.faction = gs.sidewon THEN 'Win'
             ELSE 'Lose'
           END AS result, 
           stp.faction, 
           COALESCE(stp.partymembers, 1) AS partymembers, 
           stp.kills, 
           stp.deaths, 
           stp.assists, 
           gs.id AS gsid, 
           gs.persistentid, 
           gs.timehierarchyid AS datehierarchy,
           gs.map, 
           pc.id AS pcid,
           pc.player, 
           pc.character
    FROM sessiontoplayer stp
      JOIN gamesession gs ON gs.id = stp.gamesession AND gs.location = stp.location
      JOIN playercharacter pc ON pc.id = stp.playercharacter AND pc.location = stp.location
    WHERE gs.sessiontype = 4;

    ALTER TABLE v_sessiontoplayer_joined OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_sessiontoplayer_joined TO ro;

    select increment_version_to(129) into ver;
  end if;

  if ver = 129
  then

    ALTER TABLE mmakingplayer ADD COLUMN lobbyreactiontime real;

    select increment_version_to(130) into ver;
  end if;

  if ver = 130
  then
    CREATE OR REPLACE VIEW v_pentaho_datehierarchy AS 
    SELECT dh.id, dh.year, dh.quarter, dh.month, dh.weekinmonth, dh.dayinmonth, dh.push, 
           ( SELECT min(dh2.id) AS min
             FROM datehierarchy dh2
             WHERE dh2.push::text = dh.push::text) AS startid
    FROM datehierarchy dh
    WHERE dh.push IS NOT NULL
    ORDER BY dh.id;

    ALTER TABLE v_pentaho_datehierarchy OWNER TO dbadmin;
    GRANT SELECT ON TABLE v_pentaho_datehierarchy TO ro;

    select increment_version_to(131) into ver;
  end if;

  if ver = 131
  then
    ALTER TABLE resourcelog_agg_source ALTER COLUMN goldchange TYPE bigint;
    ALTER TABLE resourcelog_agg_source ALTER COLUMN silverchange TYPE bigint;
    ALTER TABLE resourcelog_agg_source ALTER COLUMN perlchange TYPE bigint;
    ALTER TABLE resourcelog_agg_source ALTER COLUMN populationchange TYPE bigint;
    ALTER TABLE resourcelog_agg_source ALTER COLUMN resource1change TYPE bigint;
    ALTER TABLE resourcelog_agg_source ALTER COLUMN resource2change TYPE bigint;
    ALTER TABLE resourcelog_agg_source ALTER COLUMN resource3change TYPE bigint;

    select increment_version_to(132) into ver;
  end if;

  if ver = 132
  then
    CREATE TABLE castlebuilding
    (
      id integer NOT NULL,
      "name" varchar,
      description varchar,
      maxlevel integer,
      deleted boolean not null default false,
      CONSTRAINT castlebuilding_pkey PRIMARY KEY (id)
    );
    ALTER TABLE castlebuilding OWNER TO dbadmin;
    GRANT SELECT ON TABLE castlebuilding TO ro;

    select increment_version_to(133) into ver;
  end if;

  if ver = 133
  then

    ALTER TABLE mmakingplayer ADD COLUMN playerrating integer;
    ALTER TABLE mmakingsession ADD COLUMN map varchar;
    
    select increment_version_to(134) into ver;
  end if; 

  if ver = 134
  then

    CREATE TABLE event_scriptevent
    (
      id bigint NOT NULL,
      location varchar NOT NULL,
      sessiontoplayerid integer NOT NULL,
      step integer NOT NULL,
      strparam1 varchar,
      strparam2 varchar,
      intparam1 integer,
      intparam2 integer,
      intparam3 integer,
      intparam4 integer,
      intparam5 integer,
      datehierarchy integer NOT NULL,
      CONSTRAINT event_scriptevent_pkey PRIMARY KEY (id, location),
      CONSTRAINT event_scriptevent_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
      CONSTRAINT event_scriptevent_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE event_scriptevent OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_scriptevent TO ro;

    CREATE INDEX idx_event_scriptevent_sessiontoplayerid ON event_scriptevent (sessiontoplayerid);

    select increment_version_to(135) into ver;
  end if; 

  if ver = 135
  then

    CREATE TABLE gm_useroperation 
    (
      id integer NOT NULL,
      type integer NOT NULL,
      player bigint NOT NULL,
      minutes integer NOT NULL,
      reason varchar,
      gmlogin varchar NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT gm_useroperation_pkey PRIMARY KEY (id),
      CONSTRAINT gm_useroperation_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT gm_useroperation_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE gm_useroperation OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_useroperation TO ro;

    CREATE INDEX idx_gm_useroperation_datehierarchy ON gm_useroperation (datehierarchy);

    DROP TABLE gm_banplayer;
    DROP TABLE gm_muteplayer;
    DROP TABLE gm_unbanplayer;
    DROP TABLE gm_unmuteplayer;

    CREATE TABLE claim
    (
      id integer NOT NULL,
      fromplayer bigint NOT NULL,
      toplayer bigint NOT NULL,
      source integer NOT NULL,
      category integer NOT NULL,
      comment varchar,
      chatlog varchar,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      persistentid bigint,
      kills integer,
      deaths integer,
      assists integer,
      points integer,
      prime integer,
      distance integer,
      afks integer,
      connstatus integer,
      gmuseroperation integer,
      lastmodified timestamp NOT NULL,
      CONSTRAINT claim_pkey PRIMARY KEY (id),
      CONSTRAINT claim_fromplayer_fkey FOREIGN KEY (fromplayer) REFERENCES player (id),
      CONSTRAINT claim_toplayer_fkey FOREIGN KEY (toplayer) REFERENCES player (id),
      CONSTRAINT claim_gmuseroperation_fkey FOREIGN KEY (gmuseroperation) REFERENCES gm_useroperation (id),
      CONSTRAINT claim_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE claim OWNER TO dbadmin;
    GRANT SELECT ON TABLE claim TO ro;

    CREATE INDEX idx_claim_lastmodified ON claim (lastmodified);

    ALTER TABLE player DROP COLUMN banneduntil;

    select increment_version_to(136) into ver;
  end if; 

  if ver = 136
  then

    DROP FUNCTION update_stp_rating(bigint, bigint, bigint, bigint);

    select increment_version_to(137) into ver;
  end if; 

  if ver = 137
  then

    ALTER TABLE sessiontoplayer DROP COLUMN ratingchange;
    ALTER TABLE sessiontoplayer ADD COLUMN force real;

    CREATE INDEX idx_mmakingplayer_datehierarchy ON mmakingplayer (datehierarchy);
    CREATE INDEX idx_mmakingplayer_mmakingsession ON mmakingplayer (mmakingsession);
    CREATE INDEX idx_mmakingplayer_playercharacter ON mmakingplayer (playercharacter);

    select increment_version_to(138) into ver;
  end if;

  if ver = 138
  then

    ALTER TABLE player ALTER COLUMN rating DROP NOT NULL;
    ALTER TABLE playercharacter ALTER COLUMN rating DROP NOT NULL;

    CREATE OR REPLACE FUNCTION partitions_check(tablename character varying)
      RETURNS void AS
    $$
    DECLARE
      r record;
      startdh integer;
      dh integer;
      elsifs text;
    BEGIN
      startdh = to_char(now()-interval'30days','yyyyMMdd')::integer;
      EXECUTE 'select datehierarchy from '||tablename||' where id = '||
              '(select max(id) from '||tablename||')' INTO dh;
      IF (dh < startdh) THEN startdh = dh; END IF;

      elsifs = '';
      FOR r IN (
        SELECT id FROM datehierarchy
        WHERE id >= startdh
          AND id <= to_char(now()+interval'1days','yyyyMMdd')::integer 
        ORDER BY id DESC )
      LOOP
        RAISE NOTICE 'creating partition %_%', tablename, r.id;
        PERFORM partition_every_day(tablename::regclass, r.id);

        elsifs = elsifs||'
        ELSIF ( NEW.datehierarchy = '||r.id||' ) THEN
          INSERT INTO partitions.'||tablename||'_'||r.id||' VALUES (NEW.*); ';
      END LOOP;

      -- replace insert trigger
      EXECUTE '
      CREATE OR REPLACE FUNCTION '||tablename||'_insert_trigger()
      RETURNS TRIGGER AS $CODE$
      BEGIN
        IF ( false ) THEN RAISE;'||elsifs||'
        ELSE
          RAISE EXCEPTION ''Unexpected datehierarchy value. Fix the '||tablename||'_insert_trigger() function!'';
        END IF;
        RETURN NULL;
      END;
      $CODE$ LANGUAGE plpgsql;';
      
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION partitions_check(character varying) OWNER TO dbadmin;

    select increment_version_to(139) into ver;
  end if;

  if ver = 139
  then

    IF NOT EXISTS (
      SELECT * FROM pg_attribute a JOIN pg_class p ON p.oid = attrelid
      WHERE attname = 'locale' AND relname = 'claim')
    THEN
      ALTER TABLE claim ADD COLUMN locale character varying NOT NULL DEFAULT 'RU';
      ALTER TABLE claim ALTER COLUMN locale DROP DEFAULT;
    END IF;

    select increment_version_to(140) into ver;
  end if;

  if ver = 140
  then

    CREATE TABLE talentlog
    (
      id bigint NOT NULL,
      operation varchar NOT NULL,
      player bigint NOT NULL,
      talent integer NOT NULL,
      talentinstanceid bigint NOT NULL,
      character integer,
      persistentid bigint,
      timestamp timestamp,
      datehierarchy integer,
      CONSTRAINT talentlog_pkey PRIMARY KEY (id),
      CONSTRAINT talentlog_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT talentlog_talent_fkey FOREIGN KEY (talent) REFERENCES talent (id),
      CONSTRAINT talentlog_character_fkey FOREIGN KEY (character) REFERENCES character (id),
      CONSTRAINT talentlog_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE talentlog OWNER TO dbadmin;
    GRANT SELECT ON TABLE talentlog TO ro;

    CREATE INDEX idx_talentlog_player ON talentlog (player);
    CREATE INDEX idx_talentlog_timestamp ON talentlog (timestamp);

    DROP TABLE talentroll CASCADE;

    select increment_version_to(141) into ver;
  end if;

  if ver = 141
  then

    CREATE TABLE event_exceedingsteptime_agg_report
    (
      datehierarchy integer,
      relayaddress varchar,
      stpid integer,
      typeid bit(8),
      total_evt integer,
      jitter_100_evt integer,
      jitter_200_evt integer,
      jitter_300_evt integer,
      jitter_400_evt integer,
      jitter_500_evt integer,
      lag_100_evt integer,
      lag_200_evt integer,
      lag_300_evt integer,
      lag_400_evt integer,
      lag_500_evt integer,
      jitter_100_timemax integer,
      jitter_200_timemax integer,
      jitter_300_timemax integer,
      jitter_400_timemax integer,
      jitter_500_timemax integer,
      lag_100_timemax integer,
      lag_200_timemax integer,
      lag_300_timemax integer,
      lag_400_timemax integer,
      lag_500_timemax integer,
      cluster varchar,
      locale varchar NOT NULL
    );
    ALTER TABLE event_exceedingsteptime_agg_report OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_exceedingsteptime_agg_report TO ro;

    CREATE OR REPLACE FUNCTION event_exceedingsteptime_agg_report_insert_trigger()
      RETURNS trigger AS $$
    BEGIN
      IF ( false ) THEN RAISE;
      ELSE
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_exceedingsteptime_agg_report_insert_trigger() function!';
      END IF;
      RETURN NULL;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION event_exceedingsteptime_agg_report_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_event_exceedingsteptime_agg_report_partition BEFORE INSERT ON event_exceedingsteptime_agg_report
      FOR EACH ROW EXECUTE PROCEDURE event_exceedingsteptime_agg_report_insert_trigger();


    CREATE TABLE sys_cluster_info (
      name varchar NOT NULL,
      ipmask varchar NOT NULL
    );
    ALTER TABLE sys_cluster_info OWNER TO dbadmin;
    GRANT SELECT ON TABLE sys_cluster_info TO ro;


    create or replace function aggregate_event_exceedingsteptime (dh integer)
      returns void as
    $$
    declare
      date1 timestamp = to_date(dh::text, 'yyyyMMdd');
      date2 timestamp = date1+interval'1day'-interval'1second';
      evt integer;
      expectedevt integer;
      diff float;
    begin
      perform partitions_check('event_exceedingsteptime_agg_report');

      select coalesce(sum(total_evt),0) into evt
      from event_exceedingsteptime_agg_report where datehierarchy = dh;

      if (evt > 0)
      then
        raise notice 'executing check...';
       
        select count(e.id) into expectedevt
        from sessiontoplayer stp
          join gamesession gs on gs.id = stp.gamesession
            and gs.location = stp.location
          join event_exceedingsteptime e on e.sessiontoplayerid = stp.id
            and stp.location = e.location 
        where gs.timehierarchyid = dh
          and e.datehierarchy = dh
          and gs.starttime between date1 and date2
          and gs.sessiontype = 4;

        diff = abs(expectedevt-evt)::float/evt;
        if (diff < 0.01) then
          raise notice 'aggregating data is OK for % (diff = %)', dh, diff;
          return;
        else
          raise notice 'delete aggregated data for % (evt=%, expectedevt=%)', dh, evt, expectedevt;
          execute 'truncate table partitions.event_exceedingsteptime_agg_report_'||dh;
        end if;
      end if;

      raise notice 'building aggregated data for %', dh;
     
      insert into event_exceedingsteptime_agg_report
      select e.datehierarchy, substring(stp.relayaddress from '^[\d\.]+'), stp.id, typeid::bit(8),
             count(*) total_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax < 200 then 1 else null end ) as jitter_100_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 200 and steptimemax < 300 then 1 else null end ) as jitter_200_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 300 and steptimemax < 400 then 1 else null end ) as jitter_300_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 400 and steptimemax < 500 then 1 else null end ) as jitter_400_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 500 then 1 else null end ) as jitter_500_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax < 200 then 1 else null end ) as lag_100_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 200 and steptimemax < 300 then 1 else null end ) as lag_200_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 300 and steptimemax < 400 then 1 else null end ) as lag_300_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 400 and steptimemax < 500 then 1 else null end ) as lag_400_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 500 then 1 else null end ) as lag_500_evt,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax < 200 then steptimemax else null end)) as jitter_100_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 200 and steptimemax < 300 then steptimemax else null end)) as jitter_200_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 300 and steptimemax < 400 then steptimemax else null end)) as jitter_300_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 400 and steptimemax < 500 then steptimemax else null end)) as jitter_400_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 500 then steptimemax else null end)) as jitter_500_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax < 200 then steptimemax else null end)) as lag_100_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 200 and steptimemax < 300 then steptimemax else null end)) as lag_200_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 300 and steptimemax < 400 then steptimemax else null end)) as lag_300_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 400 and steptimemax < 500 then steptimemax else null end)) as lag_400_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 500 then steptimemax else null end)) as lag_500_timemax,
             case when substring(stp.relayaddress from '^[\d\.]+') is null then null
                  else coalesce(sys.name, 'UNKNOWN')
             end,
             p.locale
      from event_exceedingsteptime e
        join sessiontoplayer stp on stp.id = e.sessiontoplayerid and stp.location = e.location
        join gamesession gs on gs.id = stp.gamesession and gs.location = stp.location
        join playercharacter pc on pc.id = stp.playercharacter and pc.location = stp.location
        join player p on p.id = pc.player
        left join sys_cluster_info sys on substring(stp.relayaddress from '^[\d\.]+') like ipmask||'%'
      where e.datehierarchy = dh
        and gs.timehierarchyid = dh
        and gs.starttime between date1 and date2
        and gs.sessiontype = 4
      group by 1,2,3,4,sys.name,p.locale
      order by 1,2,3,4;
    end;
    $$ language plpgsql;


    CREATE OR REPLACE FUNCTION partitions_check(tablename character varying)
      RETURNS void AS
    $$
    DECLARE
      r record;
      startdh integer;
      dh integer;
      elsifs text;
    BEGIN
      startdh = to_char(now()-interval'30days','yyyyMMdd')::integer;
      SELECT coalesce(max(substring(c.relname from '\d+$')::integer),startdh) INTO dh
      FROM pg_inherits 
        JOIN pg_class AS c ON (inhrelid=c.oid)
        JOIN pg_class as p ON (inhparent=p.oid)
      WHERE p.relname = tablename;
      IF (dh < startdh) THEN startdh = dh; END IF;

      elsifs = '';
      FOR r IN (
        SELECT id FROM datehierarchy
        WHERE id >= startdh
          AND id <= to_char(now()+interval'1days','yyyyMMdd')::integer 
        ORDER BY id DESC )
      LOOP
        PERFORM partition_every_day(tablename::regclass, r.id);

        elsifs = elsifs||'
        ELSIF ( NEW.datehierarchy = '||r.id||' ) THEN
          INSERT INTO partitions.'||tablename||'_'||r.id||' VALUES (NEW.*); ';
      END LOOP;

      -- replace insert trigger
      EXECUTE '
      CREATE OR REPLACE FUNCTION '||tablename||'_insert_trigger()
      RETURNS TRIGGER AS $CODE$
      BEGIN
        IF ( false ) THEN RAISE;'||elsifs||'
        ELSE
          RAISE EXCEPTION ''Unexpected datehierarchy value. Fix the '||tablename||'_insert_trigger() function!'';
        END IF;
        RETURN NULL;
      END;
      $CODE$ LANGUAGE plpgsql;';
      
    END;
    $$ LANGUAGE plpgsql;


    select increment_version_to(142) into ver;
  end if;

  if ver = 142
  then

    CREATE SCHEMA reports AUTHORIZATION dbadmin;

    CREATE TABLE reports.ad_cost (
      id serial NOT NULL PRIMARY KEY,
      date_from date NOT NULL,
      date_to date NOT NULL,
      locale varchar(2) NOT NULL,
      cost numeric(20, 2) NOT NULL,
      clicks integer NOT NULL,
      cpc numeric(20, 2) NOT NULL,
      installs integer NOT NULL,
      regs integer NOT NULL,
      nu integer NOT NULL
    );
    ALTER TABLE reports.ad_cost OWNER TO dbadmin;
    GRANT SELECT ON TABLE reports.ad_cost TO ro;

    select increment_version_to(143) into ver;
  end if;

  if ver = 143
  then

    ALTER TABLE claim ADD COLUMN muid varchar;

    select increment_version_to(144) into ver;
  end if;

  if ver = 144
  then

    CREATE TABLE sys_event_exceedingsteptime_agg_report_ids
    (
      datehierarchy integer NOT NULL,
      lastid bigint NOT NULL,
      count integer NOT NULL,
      CONSTRAINT sys_event_exceedingsteptime_agg_report_ids_pkey PRIMARY KEY (datehierarchy)
    );
    ALTER TABLE sys_event_exceedingsteptime_agg_report_ids OWNER TO dbadmin;

    create or replace function aggregate_event_exceedingsteptime (dh integer)
      returns void as
    $$
    declare
      date1 timestamp = to_date(dh::text, 'yyyyMMdd');
      date2 timestamp = date1+interval'1day'-interval'1second';
      evt integer;
      startid bigint;
      diff float;
    begin
      perform partitions_check('event_exceedingsteptime_agg_report');

      select count, lastid into evt, startid
      from sys_event_exceedingsteptime_agg_report_ids where datehierarchy = dh;

      if (found)
      then
        raise notice 'executing check...';
       
        select count(*)::float/evt into diff
        from event_exceedingsteptime 
        where datehierarchy = dh
          and id > startid;

        raise notice 'check aggregated data for % (evt = %, diff = %)', dh, evt, diff;
        if (diff < 0.05) then
          raise notice 'aggregated data is OK';
          return;
        end if;
      else
        if exists (select 1 from event_exceedingsteptime_agg_report where datehierarchy = dh limit 1) then
          raise notice 'NO INFO about %', dh;
          return;
        end if;
        startid = 0;
      end if;

      raise notice 'building aggregated data for % (started from id=%)', dh, startid;
     
      insert into event_exceedingsteptime_agg_report
      select e.datehierarchy, substring(stp.relayaddress from '^[\d\.]+'), stp.id, typeid::bit(8),
             count(*) total_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax < 200 then 1 else null end ) as jitter_100_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 200 and steptimemax < 300 then 1 else null end ) as jitter_200_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 300 and steptimemax < 400 then 1 else null end ) as jitter_300_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 400 and steptimemax < 500 then 1 else null end ) as jitter_400_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 500 then 1 else null end ) as jitter_500_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax < 200 then 1 else null end ) as lag_100_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 200 and steptimemax < 300 then 1 else null end ) as lag_200_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 300 and steptimemax < 400 then 1 else null end ) as lag_300_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 400 and steptimemax < 500 then 1 else null end ) as lag_400_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 500 then 1 else null end ) as lag_500_evt,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax < 200 then steptimemax else null end)) as jitter_100_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 200 and steptimemax < 300 then steptimemax else null end)) as jitter_200_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 300 and steptimemax < 400 then steptimemax else null end)) as jitter_300_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 400 and steptimemax < 500 then steptimemax else null end)) as jitter_400_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 500 then steptimemax else null end)) as jitter_500_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax < 200 then steptimemax else null end)) as lag_100_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 200 and steptimemax < 300 then steptimemax else null end)) as lag_200_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 300 and steptimemax < 400 then steptimemax else null end)) as lag_300_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 400 and steptimemax < 500 then steptimemax else null end)) as lag_400_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 500 then steptimemax else null end)) as lag_500_timemax,
             case when substring(stp.relayaddress from '^[\d\.]+') is null then null
                  else coalesce(sys.name, 'UNKNOWN')
             end,
             p.locale
      from event_exceedingsteptime e
        join sessiontoplayer stp on stp.id = e.sessiontoplayerid and stp.location = e.location
        join gamesession gs on gs.id = stp.gamesession and gs.location = stp.location
        join playercharacter pc on pc.id = stp.playercharacter and pc.location = stp.location
        join player p on p.id = pc.player
        left join sys_cluster_info sys on substring(stp.relayaddress from '^[\d\.]+') like ipmask||'%'
      where e.datehierarchy = dh
        and gs.timehierarchyid = dh
        and gs.starttime between date1 and date2
        and gs.sessiontype = 4
        and e.id > startid
      group by 1,2,3,4,sys.name,p.locale
      order by 1,2,3,4;

      delete from sys_event_exceedingsteptime_agg_report_ids
      where datehierarchy = dh;

      insert into sys_event_exceedingsteptime_agg_report_ids (datehierarchy, lastid, count)
      select dh, max(id), count(*)
      from event_exceedingsteptime
      where datehierarchy = dh;
    end;
    $$ language plpgsql;

    select increment_version_to(145) into ver;
  end if;

  if ver = 145
  then

    CREATE TABLE gm_operation
    (
      id integer NOT NULL,
      type varchar NOT NULL,
      player bigint NOT NULL,
      data varchar,
      gmlogin varchar NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT gm_operation_pkey PRIMARY KEY (id),
      CONSTRAINT gm_operation_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT gm_operation_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE gm_operation OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_operation TO ro;

    CREATE INDEX idx_gm_operation_datehierarchy ON gm_operation (datehierarchy);

    DROP TABLE gm_addtalent;
    DROP TABLE gm_deletetalent;
    DROP TABLE gm_lockcharacter;
    DROP TABLE gm_unlockcharacter;
    DROP TABLE gm_editplayer;

    DROP TABLE chat;

    select increment_version_to(146) into ver;
  end if;

  if ver = 146
  then

    ALTER TABLE gamesession ADD COLUMN serveraddress varchar;
    ALTER TABLE gamesession ADD COLUMN cluster varchar;
    ALTER TABLE sessiontoplayer ALTER COLUMN gamesession_analysisid DROP NOT NULL;
    ALTER TABLE sessiontoplayer ALTER COLUMN playercharacter_analysisid DROP NOT NULL;

    select increment_version_to(147) into ver;
  end if;

  if ver = 147
  then

    ALTER TABLE talentlog ADD COLUMN data varchar;

    select increment_version_to(148) into ver;
  end if;

  if ver = 148
  then

    CREATE TABLE event_disconnect_agg_report
    (
      id bigint,
      player bigint,
      gsid integer,
      stpid integer,
      leaver boolean,
      firstleaver boolean,
      type integer,
      offid bigint,
      offtype integer,
      timestamp timestamp,
      relayaddress varchar,
      cluster varchar,
      locale varchar NOT NULL,
      datehierarchy integer,
      constraint event_disconnect_agg_report_pkey primary key (id)
    );
    ALTER TABLE event_disconnect_agg_report OWNER TO dbadmin;
    GRANT SELECT ON TABLE event_disconnect_agg_report TO ro;

    CREATE INDEX idx_event_disconnect_agg_report_gsid on event_disconnect_agg_report (gsid);

    CREATE OR REPLACE FUNCTION event_disconnect_agg_report_insert_trigger()
      RETURNS trigger AS $$
    BEGIN
      IF ( false ) THEN RAISE;
      ELSE
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_disconnect_agg_report_insert_trigger() function!';
      END IF;
      RETURN NULL;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION event_disconnect_agg_report_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_event_disconnect_agg_report_partition BEFORE INSERT ON event_disconnect_agg_report
      FOR EACH ROW EXECUTE PROCEDURE event_disconnect_agg_report_insert_trigger();


    create or replace function aggregate_event_disconnect (dh integer)
      returns void as
    $$
    declare
      date1 timestamp = to_date(dh::text, 'yyyyMMdd');
      date2 timestamp = date1+interval'1day'-interval'1second';
      evt integer;
      startid bigint;
      diff float;
    begin
      raise notice '% script started', clock_timestamp();
      perform partitions_check('event_disconnect_agg_report');

      select count(*), max(id) into evt, startid
      from event_disconnect_agg_report 
      where datehierarchy = dh;

      if (evt > 0)
      then
        raise notice '% executing check...', clock_timestamp();
        
        select count(*)::float/evt into diff
        from event_disconnect 
        where datehierarchy = dh
          and id > startid;

        raise notice '% check aggregated data for % (evt = %, diff = %)', clock_timestamp(), dh, evt, diff;
        if (diff < 0.05) then
          raise notice '% aggregated data is OK', clock_timestamp();
          return;
        end if;
      else
        startid = 0;
      end if;

      raise notice '% building aggregated data for % (started from id=%)', clock_timestamp(), dh, startid;

      raise notice '% insert data', clock_timestamp();
      insert into event_disconnect_agg_report
      select e.id, p.id, gs.id, stp.id, stp.leaver, null /*firstleaver*/, 
             e.reason, null /*offid*/, null /*offtype*/, e.timestamp, stp.relayaddress,
             case when substring(stp.relayaddress from '^[\d\.]+') is null then null
                  else coalesce(sys.name, 'UNKNOWN')
             end,
             p.locale, gs.timehierarchyid
      from event_disconnect e
        join sessiontoplayer stp on stp.id = e.sessiontoplayerid and stp.location = e.location
        join gamesession gs on gs.id = stp.gamesession and gs.location = stp.location
        join playercharacter pc on pc.id = stp.playercharacter and pc.location = stp.location
        join player p on p.id = pc.player
        left join sys_cluster_info sys on substring(stp.relayaddress from '^[\d\.]+') like ipmask||'%'
      where e.datehierarchy >= dh
        and gs.timehierarchyid = dh
        and gs.starttime between date1 and date2
        and gs.sessiontype = 4
        and e.id > startid
      order by e.id;

      raise notice '% update first leaver', clock_timestamp();
      update event_disconnect_agg_report r1
      set firstleaver = not exists (
        select 1 from event_disconnect_agg_report r2
        where r2.gsid = r1.gsid
          and r2.datehierarchy = r1.datehierarchy
          and ( r2.timestamp < r1.timestamp
                or (r2.timestamp = r1.timestamp and r2.id < r1.id) ) )
      where r1.datehierarchy = dh
        and r1.id > startid;

      raise notice '% update client event', clock_timestamp();
      update event_disconnect_agg_report r
      set offid = o.id, offtype = o.code
      from offlineevent o
      where r.datehierarchy = dh
        and r.id > startid
        and o.datehierarchy = dh
        and o.playerid = r.player
        and o.code in (2,4,7)
        and r.type = 4
        and o.timestamp = (
          select o2.timestamp
          from offlineevent o2
          where o2.datehierarchy = dh
            and o2.playerid = r.player
            and o2.code in (2,4,7)
          order by case when o2.timestamp >= r.timestamp 
                        then o2.timestamp - r.timestamp 
                        else r.timestamp - o2.timestamp end
          limit 1
        );

      raise notice '% script finished', clock_timestamp();
    end;
    $$ language plpgsql;

    select increment_version_to(149) into ver;
  end if;

  if ver = 149
  then

    create or replace function aggregate_event_exceedingsteptime (dh integer)
      returns void as
    $$
    declare
      date1 timestamp = to_date(dh::text, 'yyyyMMdd');
      date2 timestamp = date1+interval'1day'-interval'1second';
      evt integer;
      startid bigint;
      diff float;
    begin
      perform partitions_check('event_exceedingsteptime_agg_report');

      select count, lastid into evt, startid
      from sys_event_exceedingsteptime_agg_report_ids where datehierarchy = dh;

      if (found)
      then
        raise notice 'executing check...';
       
        select count(*)::float/evt into diff
        from event_exceedingsteptime 
        where datehierarchy = dh
          and id > startid;

        raise notice 'check aggregated data for % (evt = %, diff = %)', dh, evt, diff;
        if (diff < 0.05) then
          raise notice 'aggregated data is OK';
          return;
        end if;
      else
        if exists (select 1 from event_exceedingsteptime_agg_report where datehierarchy = dh limit 1) then
          raise notice 'NO INFO about %', dh;
          return;
        end if;
        startid = 0;
      end if;

      raise notice 'building aggregated data for % (started from id=%)', dh, startid;
     
      insert into event_exceedingsteptime_agg_report
      select e.datehierarchy, substring(stp.relayaddress from '^[\d\.]+'), stp.id, typeid::bit(8),
             count(*) total_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax < 200 then 1 else null end ) as jitter_100_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 200 and steptimemax < 300 then 1 else null end ) as jitter_200_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 300 and steptimemax < 400 then 1 else null end ) as jitter_300_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 400 and steptimemax < 500 then 1 else null end ) as jitter_400_evt,
             count(case when abs(steptimeavg-100) <= 2 and steptimemax >= 500 then 1 else null end ) as jitter_500_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax < 200 then 1 else null end ) as lag_100_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 200 and steptimemax < 300 then 1 else null end ) as lag_200_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 300 and steptimemax < 400 then 1 else null end ) as lag_300_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 400 and steptimemax < 500 then 1 else null end ) as lag_400_evt,
             count(case when abs(steptimeavg-100) > 2 and steptimemax >= 500 then 1 else null end ) as lag_500_evt,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax < 200 then steptimemax else null end)) as jitter_100_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 200 and steptimemax < 300 then steptimemax else null end)) as jitter_200_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 300 and steptimemax < 400 then steptimemax else null end)) as jitter_300_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 400 and steptimemax < 500 then steptimemax else null end)) as jitter_400_timemax,
             round(avg(case when abs(steptimeavg-100) <= 2 and steptimemax >= 500 then steptimemax else null end)) as jitter_500_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax < 200 then steptimemax else null end)) as lag_100_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 200 and steptimemax < 300 then steptimemax else null end)) as lag_200_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 300 and steptimemax < 400 then steptimemax else null end)) as lag_300_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 400 and steptimemax < 500 then steptimemax else null end)) as lag_400_timemax,
             round(avg(case when abs(steptimeavg-100) > 2 and steptimemax >= 500 then steptimemax else null end)) as lag_500_timemax,
             coalesce(upper(gs.cluster), 'NOINFO'),
             p.locale
      from event_exceedingsteptime e
        join sessiontoplayer stp on stp.id = e.sessiontoplayerid and stp.location = e.location
        join gamesession gs on gs.id = stp.gamesession and gs.location = stp.location
        join playercharacter pc on pc.id = stp.playercharacter and pc.location = stp.location
        join player p on p.id = pc.player
      where e.datehierarchy = dh
        and gs.timehierarchyid = dh
        and gs.starttime between date1 and date2
        and gs.sessiontype = 4
        and e.id > startid
      group by 1,2,3,4,gs.cluster,p.locale
      order by 1,2,3,4;

      delete from sys_event_exceedingsteptime_agg_report_ids
      where datehierarchy = dh;

      insert into sys_event_exceedingsteptime_agg_report_ids (datehierarchy, lastid, count)
      select dh, max(id), count(*)
      from event_exceedingsteptime
      where datehierarchy = dh;
    end;
    $$ language plpgsql;

    create or replace function aggregate_event_disconnect (dh integer)
      returns void as
    $$
    declare
      date1 timestamp = to_date(dh::text, 'yyyyMMdd');
      date2 timestamp = date1+interval'1day'-interval'1second';
      evt integer;
      startid bigint;
      diff float;
    begin
      raise notice '% script started', clock_timestamp();
      perform partitions_check('event_disconnect_agg_report');

      select count(*), max(id) into evt, startid
      from event_disconnect_agg_report 
      where datehierarchy = dh;

      if (evt > 0)
      then
        raise notice '% executing check...', clock_timestamp();
        
        select count(*)::float/evt into diff
        from event_disconnect 
        where datehierarchy = dh
          and id > startid;

        raise notice '% check aggregated data for % (evt = %, diff = %)', clock_timestamp(), dh, evt, diff;
        if (diff < 0.05) then
          raise notice '% aggregated data is OK', clock_timestamp();
          return;
        end if;
      else
        startid = 0;
      end if;

      raise notice '% building aggregated data for % (started from id=%)', clock_timestamp(), dh, startid;

      raise notice '% insert data', clock_timestamp();
      insert into event_disconnect_agg_report
      select e.id, p.id, gs.id, stp.id, stp.leaver, null /*firstleaver*/, 
             e.reason, null /*offid*/, null /*offtype*/, e.timestamp, stp.relayaddress,
             coalesce(upper(gs.cluster), 'NOINFO'),
             p.locale, gs.timehierarchyid
      from event_disconnect e
        join sessiontoplayer stp on stp.id = e.sessiontoplayerid and stp.location = e.location
        join gamesession gs on gs.id = stp.gamesession and gs.location = stp.location
        join playercharacter pc on pc.id = stp.playercharacter and pc.location = stp.location
        join player p on p.id = pc.player
      where e.datehierarchy >= dh
        and gs.timehierarchyid = dh
        and gs.starttime between date1 and date2
        and gs.sessiontype = 4
        and e.id > startid
      order by e.id;

      raise notice '% update first leaver', clock_timestamp();
      update event_disconnect_agg_report r1
      set firstleaver = not exists (
        select 1 from event_disconnect_agg_report r2
        where r2.gsid = r1.gsid
          and r2.datehierarchy = r1.datehierarchy
          and ( r2.timestamp < r1.timestamp
                or (r2.timestamp = r1.timestamp and r2.id < r1.id) ) )
      where r1.datehierarchy = dh
        and r1.id > startid;

      raise notice '% update client event', clock_timestamp();
      update event_disconnect_agg_report r
      set offid = o.id, offtype = o.code
      from offlineevent o
      where r.datehierarchy = dh
        and r.id > startid
        and o.datehierarchy = dh
        and o.playerid = r.player
        and o.code in (2,4,7)
        and r.type = 4
        and o.timestamp = (
          select o2.timestamp
          from offlineevent o2
          where o2.datehierarchy = dh
            and o2.playerid = r.player
            and o2.code in (2,4,7)
          order by case when o2.timestamp >= r.timestamp 
                        then o2.timestamp - r.timestamp 
                        else r.timestamp - o2.timestamp end
          limit 1
        );

      raise notice '% script finished', clock_timestamp();
    end;
    $$ language plpgsql;

    DROP TABLE sys_cluster_info;

    select increment_version_to(150) into ver;
  end if;


  if ver = 150
  then
    DROP TABLE socialsession_agg_dau;
    DROP FUNCTION aggregate_socialsession(varchar);

    DELETE FROM sys_aggregation_ranges WHERE tablename = 'socialsession';
    INSERT INTO sys_aggregation_ranges (tablename, location, lastid) VALUES ('launcherevents', '', 0);
    INSERT INTO sys_aggregation_ranges (tablename, location, lastid) VALUES ('socialsession', '', 0);

    CREATE TABLE player_conversion (
      auid integer not null,
      locale varchar not null,
      firstevent timestamp,
      downloading timestamp,
      readyplay timestamp,
      startplay timestamp,
      castlelogin timestamp,
      constraint player_conversion_pkey primary key (auid) 
    );
    ALTER TABLE player_conversion OWNER TO dbadmin;
    GRANT SELECT ON TABLE player_conversion TO ro;

    create or replace function aggregate_launcherevents()
      returns void as
    $$
    declare
      r record;
      p record;
      inserted integer;
      updated integer;
      startts timestamp;
      m_id bigint;
      l_id bigint;
    begin
      select max(id) into m_id 
      from launcherevents;
      
      select lastid into l_id
      from sys_aggregation_ranges
      where tablename = 'launcherevents';

      if l_id = m_id then return; end if;
      raise notice 'aggregation: ids range [%..%]', l_id, m_id;

      inserted = 0;
      updated = 0;
      startts = clock_timestamp();
      for r in (
        select playerid as auid,
               min(coalesce(locale,'RU')) as locale,
               min(coalesce(servertimestamp, clienttimestamp)) as firstevent, 
               min(case when eventflags::bit(8)&'00001000'::bit(8) = '00001000' then coalesce(servertimestamp, clienttimestamp) else null end) as downloading,
               min(case when eventflags::bit(8)&'01000000'::bit(8) = '01000000' then coalesce(servertimestamp, clienttimestamp) else null end) as readyplay,
               min(case when eventflags::bit(8)&'10000000'::bit(8) = '10000000' then coalesce(servertimestamp, clienttimestamp) else null end) as startplay
        from launcherevents
        where id between l_id and m_id
          and playerid != 0
        group by playerid )
        
      loop
        select * into p 
        from player_conversion 
        where auid = r.auid;
        
        if not found 
        then 
          insert into player_conversion (auid, locale, firstevent, downloading, readyplay, startplay)
          values (r.auid, r.locale, r.firstevent, r.downloading, r.readyplay, r.startplay);
          inserted = inserted + 1;

        elsif (p.firstevent is null and r.firstevent is not null) or
              (p.downloading is null and r.downloading is not null) or
              (p.readyplay is null and r.readyplay is not null) or
              (p.startplay is null and r.startplay is not null)
        then
          update player_conversion
          set firstevent = least(firstevent, r.firstevent),
              downloading = least(downloading, r.downloading),
              readyplay = least(readyplay, r.readyplay),
              startplay = least(startplay, r.startplay)
          where auid = r.auid;
          updated = updated + 1;
        end if;
        
      end loop;

      update sys_aggregation_ranges
      set lastid = m_id
      where tablename = 'launcherevents';

      raise notice 'script finished in %, inserted % rows, updated % rows', clock_timestamp() - startts, inserted, updated;
    end;
    $$ language plpgsql;
    ALTER FUNCTION aggregate_launcherevents() OWNER TO dbadmin;


    create or replace function aggregate_socialsession_conversion()
      returns void as 
    $$
    declare
      r record;
      p record;
      inserted integer;
      updated integer;
      startts timestamp;
      m_id bigint;
      l_id bigint;
    begin
      select max(id) into m_id 
      from socialsession;
      
      select lastid into l_id
      from sys_aggregation_ranges
      where tablename = 'socialsession';

      if l_id = m_id then return; end if;
      raise notice 'aggregation: ids range [%..%]', l_id, m_id;

      inserted = 0;
      updated = 0;
      startts = clock_timestamp();
      for r in (
        select pl.id as auid, min(pl.locale) as locale, min(starttime) as castlelogin
        from socialsession ss join player pl on pl.id = ss.player
        where ss.id between l_id and m_id 
        group by pl.id )

      loop
        select * into p 
        from player_conversion 
        where auid = r.auid;

        if not found 
        then
          insert into player_conversion (auid, locale, castlelogin)
          values (r.auid, r.locale, r.castlelogin);
          inserted = inserted + 1;

        elsif p.castlelogin is null and r.castlelogin is not null
        then
          update player_conversion
          set castlelogin = least(castlelogin, r.castlelogin)
          where auid = r.auid;
          updated = updated + 1;
        end if;
        
      end loop;

      update sys_aggregation_ranges
      set lastid = m_id
      where tablename = 'socialsession';

      raise notice 'script finished in %, inserted % rows, updated % rows', clock_timestamp() - startts, inserted, updated;
    end;
    $$ language plpgsql;
    ALTER FUNCTION aggregate_socialsession_conversion() OWNER TO dbadmin;

    select increment_version_to(151) into ver;
  end if;

  if ver = 151
  then

    CREATE TABLE dynamicquestchange
    (
      id integer NOT NULL,
      player bigint NOT NULL,
      questindex integer NOT NULL,
      questname varchar NOT NULL,
      changetype integer NOT NULL,
      "timestamp" timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT dynamicquestchange_pkey PRIMARY KEY (id),
      CONSTRAINT dynamicquestchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT dynamicquestchange_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE dynamicquestchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE dynamicquestchange TO ro;

    select increment_version_to(152) into ver;
  end if;

  if ver = 152
  then

    CREATE TABLE guildshopitem
    (
      id integer NOT NULL,
      name varchar NOT NULL,
      dbid varchar NOT NULL,
      description varchar NOT NULL,
      deleted boolean NOT NULL,
      CONSTRAINT guildshopitem_pkey PRIMARY KEY (id)
    );
    ALTER TABLE guildshopitem OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildshopitem TO ro;

    CREATE TABLE guildbuff
    (
      id integer NOT NULL,
      name varchar NOT NULL,
      dbid varchar NOT NULL,
      deleted boolean NOT NULL,
      CONSTRAINT guildbuff_pkey PRIMARY KEY (id)
    );
    ALTER TABLE guildbuff OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildbuff TO ro;

    ALTER TABLE sessiontoplayer ADD COLUMN guild bigint;

    ALTER TABLE guild ADD COLUMN memberscount integer NOT NULL DEFAULT (0);
    ALTER TABLE guild ALTER COLUMN memberscount DROP DEFAULT;
    ALTER TABLE guild DROP COLUMN faction;
    ALTER TABLE guild ALTER COLUMN creator DROP NOT NULL;

    CREATE TABLE guildshopbuy
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      guild bigint NOT NULL,
      hassuzerain boolean NOT NULL,
      guildshopitem integer NOT NULL,
      shoplevel integer NOT NULL,
      guildpointsprice integer NOT NULL,
      playerpointsprice integer NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT guildshopbuy_pkey PRIMARY KEY (id),
      CONSTRAINT guildshopbuy_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT guildshopbuy_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guildshopbuy_guildshopitem_fkey FOREIGN KEY (guildshopitem) REFERENCES guildshopitem (id),
      CONSTRAINT guildshopbuy_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE guildshopbuy OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildshopbuy TO ro;

    CREATE INDEX idx_guildshopbuy_player ON guildshopbuy (player);
    CREATE INDEX idx_guildshopbuy_timestamp ON guildshopbuy (timestamp);

    CREATE OR REPLACE FUNCTION guildshopbuy_insert_trigger()
      RETURNS trigger AS
    $$
      BEGIN
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the guildshopbuy_insert_trigger() function!';
        RETURN NULL;
      END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION guildshopbuy_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_guildshopbuy_partition BEFORE INSERT ON guildshopbuy
      FOR EACH ROW EXECUTE PROCEDURE guildshopbuy_insert_trigger();

    CREATE TABLE guildsiege
    (
      id bigint NOT NULL,
      guild bigint NOT NULL,
      rating integer NOT NULL,
      targetguild bigint NOT NULL,
      targetrating integer NOT NULL,
      targetsuzerainguild bigint,
      targetsuzerainrating integer,
      guildpointsprice integer NOT NULL,
      starttime timestamp NOT NULL,
      endtime timestamp NOT NULL,
      winner bigint NOT NULL,
      analysisid bigint NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT guildsiege_pkey PRIMARY KEY (id),
      CONSTRAINT guildsiege_guild1_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guildsiege_guild2_fkey FOREIGN KEY (targetguild) REFERENCES guild (id),
      CONSTRAINT guildsiege_guild3_fkey FOREIGN KEY (targetsuzerainguild) REFERENCES guild (id),
      CONSTRAINT guildsiege_guild4_fkey FOREIGN KEY (winner) REFERENCES guild (id),
      CONSTRAINT guildsiege_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)  
    );
    ALTER TABLE guildsiege OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildsiege TO ro;

    CREATE INDEX idx_guildsiege_guild ON guildsiege (guild);
    CREATE INDEX idx_guildsiege_starttime ON guildsiege (starttime);
    CREATE INDEX idx_guildsiege_analysisid ON guildsiege (analysisid);

    CREATE TABLE guildsiegeparticipant
    (
      id bigint NOT NULL,
      guildsiege bigint NOT NULL,
      guild bigint NOT NULL,
      rating integer NOT NULL,
      siegepoints integer NOT NULL,
      guildpointsprice integer NOT NULL,
      starttime timestamp NOT NULL,
      endtime timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT guildsiegeparticipant_pkey PRIMARY KEY (id),
      CONSTRAINT guildsiegeparticipant_siege_fkey FOREIGN KEY (guildsiege) REFERENCES guildsiege (id),
      CONSTRAINT guildsiegeparticipant_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guildsiegeparticipant_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE guildsiegeparticipant OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildsiegeparticipant TO ro;

    CREATE INDEX idx_guildsiegeparticipant_siege ON guildsiegeparticipant (guildsiege);
    CREATE INDEX idx_guildsiegeparticipant_guild ON guildsiegeparticipant (guild);
    CREATE INDEX idx_guildsiegeparticipant_starttime ON guildsiegeparticipant (starttime);

    CREATE OR REPLACE FUNCTION guildsiegeparticipant_insert_trigger()
      RETURNS trigger AS
    $$
      BEGIN
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the guildsiegeparticipant_insert_trigger() function!';
        RETURN NULL;
      END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION guildsiegeparticipant_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_guildshopbuy_partition BEFORE INSERT ON guildsiegeparticipant
      FOR EACH ROW EXECUTE PROCEDURE guildsiegeparticipant_insert_trigger();

    CREATE TABLE guilddailystats
    (
      id bigint NOT NULL,
      guild bigint NOT NULL,
      rating integer NOT NULL,
      guildpoints integer NOT NULL,
      guildpointstoday integer NOT NULL,
      rank integer NOT NULL,
      vassalscount integer NOT NULL,
      vassalspoints integer NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT guilddailystats_pkey PRIMARY KEY (id),
      CONSTRAINT guilddailystats_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guilddailystats_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE guilddailystats OWNER TO dbadmin;
    GRANT SELECT ON TABLE guilddailystats TO ro;

    CREATE INDEX idx_guilddailystats_guild ON guilddailystats (guild);
    CREATE INDEX idx_guilddailystats_timestamp ON guilddailystats (timestamp);

    CREATE OR REPLACE FUNCTION guilddailystats_insert_trigger()
      RETURNS trigger AS
    $$
      BEGIN
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the guilddailystats_insert_trigger() function!';
        RETURN NULL;
      END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION guilddailystats_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_guildshopbuy_partition BEFORE INSERT ON guilddailystats
      FOR EACH ROW EXECUTE PROCEDURE guilddailystats_insert_trigger();

    CREATE TABLE guildinteraction
    (
      id bigint NOT NULL,
      guild bigint NOT NULL,
      targetguild bigint NOT NULL,
      type varchar NOT NULL,
      guildsiege bigint,
      waitingtime integer NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT guildinteraction_pkey PRIMARY KEY (id),
      CONSTRAINT guildinteraction_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guildinteraction_targetguild_fkey FOREIGN KEY (targetguild) REFERENCES guild (id),
      CONSTRAINT guildinteraction_siege_fkey FOREIGN KEY (guildsiege) REFERENCES guildsiege (id),
      CONSTRAINT guildinteraction_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE guildinteraction OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildinteraction TO ro;

    CREATE INDEX idx_guildinteraction_guild ON guildinteraction (guild);
    CREATE INDEX idx_guildinteraction_targetguild ON guildinteraction (targetguild);
    CREATE INDEX idx_guildinteraction_timestamp ON guildinteraction (timestamp);

    CREATE OR REPLACE FUNCTION guildinteraction_insert_trigger()
      RETURNS trigger AS
    $$
      BEGIN
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the guildinteraction_insert_trigger() function!';
        RETURN NULL;
      END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION guildinteraction_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_guildshopbuy_partition BEFORE INSERT ON guildinteraction
      FOR EACH ROW EXECUTE PROCEDURE guildinteraction_insert_trigger();

    select increment_version_to(153) into ver;
  end if;

  if ver = 153
  then

    CREATE TABLE guildpointslog
    (
      id bigint NOT NULL,
      type varchar NOT NULL,
      guild bigint NOT NULL,
      player bigint,
      guildpointschange integer NOT NULL,
      playerpointschange integer NOT NULL,
      guildpointstotal integer NOT NULL,
      playerpointstotal integer NOT NULL,
      persistentid bigint,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT guildpointslog_pkey PRIMARY KEY (id),
      CONSTRAINT guildpointslog_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guildpointslog_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT guildpointslog_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE guildpointslog OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildpointslog TO ro;

    CREATE INDEX idx_guildpointslog_guild ON guildpointslog (guild);
    CREATE INDEX idx_guildpointslog_player ON guildpointslog (player);
    CREATE INDEX idx_guildpointslog_timestamp ON guildpointslog (timestamp);

    truncate guildshopbuy cascade;
    truncate guildsiege cascade;
    truncate guildsiegeparticipant cascade;

    ALTER TABLE guildshopbuy DROP COLUMN guildpointsprice;
    ALTER TABLE guildshopbuy DROP COLUMN playerpointsprice;
    ALTER TABLE guildshopbuy ADD COLUMN guildpointslog bigint NOT NULL;
    ALTER TABLE guildshopbuy ADD CONSTRAINT guildshopbuy_guildpointslog_fkey FOREIGN KEY (guildpointslog) REFERENCES guildpointslog (id);

    ALTER TABLE guildsiege DROP COLUMN guildpointsprice;
    ALTER TABLE guildsiege ADD COLUMN guildpointslog bigint NOT NULL;
    ALTER TABLE guildsiege ADD CONSTRAINT guildsiege_guildpointslog_fkey FOREIGN KEY (guildpointslog) REFERENCES guildpointslog (id);

    ALTER TABLE guildsiegeparticipant DROP COLUMN guildpointsprice;
    ALTER TABLE guildsiegeparticipant ADD COLUMN guildpointslog bigint NOT NULL;
    ALTER TABLE guildsiegeparticipant ADD CONSTRAINT guildsiegeparticipant_guildpointslog_fkey FOREIGN KEY (guildpointslog) REFERENCES guildpointslog (id);

    select increment_version_to(154) into ver;
  end if;

  if ver = 154
  then
    CREATE TABLE guildbuffsession
    (
      id bigint NOT NULL,
      type varchar NOT NULL,
      player bigint NOT NULL,
      persistentid bigint NOT NULL,
      sessiontoplayer integer NOT NULL,
      sessiontoplayer_location varchar NOT NULL,
      guildbuff integer NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT guildbuffsession_pkey PRIMARY KEY (id),
      CONSTRAINT guildbuffsession_sessiontoplayer_fkey FOREIGN KEY (sessiontoplayer, sessiontoplayer_location) REFERENCES sessiontoplayer (id, location),
      CONSTRAINT guildbuffsession_guildbuff_fkey FOREIGN KEY (guildbuff) REFERENCES guildbuff (id),
      CONSTRAINT guildbuffsession_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE guildbuffsession OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildbuffsession TO ro;

    CREATE INDEX idx_guildbuffsession_sessiontoplayer ON guildbuffsession (sessiontoplayer);
    CREATE INDEX idx_guildbuffsession_guildbuff ON guildbuffsession (guildbuff);


    CREATE OR REPLACE FUNCTION guildbuffsession_insert_trigger()
      RETURNS trigger AS $$
    BEGIN
      IF ( false ) THEN RAISE;
      ELSE
        RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the guildbuffsession_insert_trigger() function!';
      END IF;
      RETURN NULL;
    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION guildbuffsession_insert_trigger() OWNER TO dbadmin;

    PERFORM partitions_check('guildbuffsession');

    CREATE TRIGGER tr_guildbuffsession_partition BEFORE INSERT ON guildbuffsession
      FOR EACH ROW EXECUTE PROCEDURE guildbuffsession_insert_trigger();

    select increment_version_to(155) into ver;
  end if;

  if ver = 155
  then
    alter table socialsession alter column id type bigint;
    alter table questchange alter column id type bigint;
    alter table dynamicquestchange alter column id type bigint;

    select increment_version_to(156) into ver;
  end if;

  if ver = 156
  then

    CREATE TABLE afterparty
    (
      id bigint NOT NULL,
      persistentid bigint NOT NULL,
      mmstarted boolean NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT afterparty_pkey PRIMARY KEY (id),
      CONSTRAINT afterparty_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE afterparty OWNER TO dbadmin;
    GRANT SELECT, UPDATE, INSERT ON TABLE afterparty TO rw;

    CREATE INDEX idx_afterparty_datehierarchy ON afterparty (datehierarchy);

    CREATE TABLE afterpartymember
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      afterparty bigint NOT NULL,
      persistentid bigint,
      kicked boolean NOT NULL,
      leaved boolean NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT afterpartymember_pkey PRIMARY KEY (id),
      CONSTRAINT afterpartymember_afterparty_fkey FOREIGN KEY (afterparty) REFERENCES afterparty (id),
      CONSTRAINT afterpartymember_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT afterparty_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE afterpartymember OWNER TO dbadmin;
    GRANT SELECT, UPDATE, INSERT ON TABLE afterpartymember TO rw;

    CREATE INDEX idx_afterpartymember_datehierarchy ON afterpartymember (datehierarchy);
    CREATE INDEX idx_afterpartymember_afterparty ON afterpartymember (afterparty);

    select increment_version_to(157) into ver;
  end if;


  if ver = 157
  then

    CREATE TABLE leaverpointslog
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      persistentid bigint NOT NULL,
      leaverpointschange integer NOT NULL,
      leaverpointstotal integer NOT NULL,
      isleaverchanged boolean NOT NULL,
      isleaver boolean NOT NULL,
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT leaverpointslog_pkey PRIMARY KEY (id),
      CONSTRAINT leaverpointslog_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT leaverpointslog_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE leaverpointslog OWNER TO dbadmin;
    GRANT SELECT ON TABLE leaverpointslog TO ro;

    CREATE INDEX idx_leaverpointslog_player ON leaverpointslog (player);
    CREATE INDEX idx_leaverpointslog_datehierarchy ON leaverpointslog (datehierarchy);

    select increment_version_to(158) into ver;
  end if;


  if ver = 158
  then

    ALTER TABLE player ADD COLUMN leavercount integer;
    ALTER TABLE player ADD COLUMN leavergmcount integer;

    ALTER TABLE gm_useroperation ADD COLUMN points integer;
    
    ALTER TABLE leaverpointslog ADD COLUMN type varchar;    
    ALTER TABLE leaverpointslog ADD COLUMN isbadbehaviour boolean;
    UPDATE leaverpointslog SET isbadbehaviour = false;
    ALTER TABLE leaverpointslog ALTER COLUMN isbadbehaviour SET NOT NULL;
    ALTER TABLE leaverpointslog ALTER COLUMN persistentid DROP NOT NULL;

    select increment_version_to(159) into ver;
  end if;


  if ver = 159
  then

    ALTER TABLE runeroll ADD COLUMN source varchar DEFAULT 'SessionDrop';
    ALTER TABLE runeroll ALTER COLUMN source DROP DEFAULT;

    ALTER TABLE rune ADD COLUMN percent integer DEFAULT 0;
    ALTER TABLE rune ALTER COLUMN percent DROP DEFAULT;

    select increment_version_to(160) into ver;
  end if;
  
  if ver = 160
  then

    ALTER TABLE resourcelog ADD COLUMN redperlchange integer;    
    ALTER TABLE resourcelog ADD COLUMN redperltotal integer;    
  
    ALTER TABLE resourcelog_gold ADD COLUMN redperlchange integer;    
    ALTER TABLE resourcelog_gold ADD COLUMN redperltotal integer;    
  
    ALTER TABLE resourcelog_agg_source ADD COLUMN redperlchange integer;


    select increment_version_to(161) into ver;
  end if;


  if ver = 161
  then

    ALTER TABLE player ADD COLUMN leaverpoints integer NOT NULL DEFAULT 0;
    ALTER TABLE player ALTER COLUMN leaverpoints DROP DEFAULT;
    ALTER TABLE player ADD COLUMN isleaver boolean NOT NULL DEFAULT false;
    ALTER TABLE player ALTER COLUMN isleaver DROP DEFAULT;

    select increment_version_to(162) into ver;
  end if;

    if ver = 162
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
  datehierarchy integer NOT NULL,
    CONSTRAINT shopreroll_pkey PRIMARY KEY (id),
	CONSTRAINT shopreroll_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE shopreroll OWNER TO dbadmin;
GRANT SELECT ON TABLE shopreroll TO ro;

CREATE INDEX idx_shopreroll_datehierarchy ON shopreroll (datehierarchy);

    select increment_version_to(163) into ver;
  end if;
  
  if ver = 163
  then
	ALTER TABLE dynamicquestchange ADD COLUMN alternativeline boolean NOT NULL DEFAULT false;
    ALTER TABLE dynamicquestchange ALTER COLUMN alternativeline DROP DEFAULT;

    select increment_version_to(164) into ver;
  end if;
  
  if ver = 164
  then

    CREATE TABLE tournamentquestchange
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      questindex integer NOT NULL,
      questname varchar NOT NULL,
      completetype integer NOT NULL,
      "timestamp" timestamp NOT NULL,
      datehierarchy integer NOT NULL,
	  alternativeline boolean NOT NULL,
      CONSTRAINT tournamentquestchange_pkey PRIMARY KEY (id),
      CONSTRAINT tournamentquestchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT tournamentquestchange_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE tournamentquestchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE tournamentquestchange TO ro;

    select increment_version_to(165) into ver;
  end if;

  if ver = 165
  then

    ALTER TABLE resourcelog ADD COLUMN shardchange integer;    
    ALTER TABLE resourcelog ADD COLUMN shardtotal integer;    
  
    ALTER TABLE resourcelog_gold ADD COLUMN shardchange integer;    
    ALTER TABLE resourcelog_gold ADD COLUMN shardtotal integer;    
  
    ALTER TABLE resourcelog_agg_source ADD COLUMN shardchange integer;

    select increment_version_to(166) into ver;
  end if;

  if ver = 166
  then

    ALTER TABLE resourcelog ADD COLUMN currencychange character varying;    
    ALTER TABLE resourcelog ADD COLUMN currencytotal character varying;    
  
    ALTER TABLE resourcelog_gold ADD COLUMN currencychange character varying;    
    ALTER TABLE resourcelog_gold ADD COLUMN currencytotal character varying;    
  
    ALTER TABLE resourcelog_agg_source ADD COLUMN currencychange character varying;

    select increment_version_to(167) into ver;
  end if;

   if ver = 167
  then

    ALTER TABLE resourcelog ADD COLUMN currencychangevalue integer;    
    ALTER TABLE resourcelog ADD COLUMN currencytotalvalue integer;    
  
    ALTER TABLE resourcelog_gold ADD COLUMN currencychangevalue integer;    
    ALTER TABLE resourcelog_gold ADD COLUMN currencytotalvalue integer;    
  
    ALTER TABLE resourcelog_agg_source ADD COLUMN currencychangevalue integer;

    select increment_version_to(168) into ver;
  end if;

  if ver = 168
  then
    CREATE TABLE runeheroapply
    (
      id bigint NOT NULL,
      player bigint NOT NULL,
      rune integer NOT NULL,
      hero varchar NOT NULL DEFAULT 'unknownhero',
      timestamp timestamp NOT NULL,
      datehierarchy integer NOT NULL,
      CONSTRAINT runeheroapply_pkey PRIMARY KEY (id),
      CONSTRAINT runeheroapply_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT runeheroapply_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id),
      CONSTRAINT runeheroapply_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
    );
    ALTER TABLE runeheroapply OWNER TO dbadmin;
    GRANT SELECT ON TABLE runeheroapply TO ro;

    CREATE INDEX idx_runeheroapply_datehierarchy ON runeheroapply (datehierarchy);
    CREATE INDEX idx_runeheroapply_player ON runeheroapply (player);

    ALTER TABLE runeroll ADD COLUMN runescountold integer;
    ALTER TABLE runeroll ADD COLUMN runescountnew integer;

    select increment_version_to(169) into ver;
  end if;

  if ver = 169
  then
    CREATE TABLE gwevents
      (
        id bigint NOT NULL,
        mongoid varchar NOT NULL,
        eventidx integer NOT NULL,
        enabled boolean NOT NULL,
        points integer NOT NULL,
        endtime timestamp NOT NULL,
        limitt integer NOT NULL,
        CONSTRAINT gwevents_pkey PRIMARY KEY (id)
      );
    ALTER TABLE gwevents OWNER TO dbadmin;
    GRANT SELECT ON TABLE gwevents TO ro;

    select increment_version_to(170) into ver;
  end if;

  if ver = 170
  then
    
    ALTER TABLE guildbuffsession ADD COLUMN guildwareventpass integer NOT NULL DEFAULT -1;

    select increment_version_to(171) into ver;
  end if;

/*
  if ver = 
  then

    select increment_version_to() into ver;
  end if;
*/


  raise notice 'updating % success!', current_database();
end;
$MAIN$ 
language plpgsql;
alter function incremental() owner to dbadmin;

select incremental();