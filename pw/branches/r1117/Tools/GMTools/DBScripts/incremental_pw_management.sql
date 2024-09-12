create or replace function incremental()
 returns void as
$MAIN$

declare
  ver integer;
  tmprow record;
  txt1 varchar;
  txt2 varchar;

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
    GRANT ALL ON TABLE player TO dbadmin;
    GRANT SELECT ON TABLE player TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE player TO rw;
    
    GRANT ALL ON TABLE "character" TO dbadmin;
    GRANT SELECT ON TABLE "character" TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE "character" TO rw;
    
    GRANT ALL ON TABLE playercharacter TO dbadmin;
    GRANT SELECT ON TABLE playercharacter TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE playercharacter TO rw;
    
    GRANT ALL ON TABLE sessionsideresult TO dbadmin;
    GRANT SELECT ON TABLE sessionsideresult TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE sessionsideresult TO rw;
    
    GRANT ALL ON TABLE gamesession TO dbadmin;
    GRANT SELECT ON TABLE gamesession TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE gamesession TO rw;
    
    GRANT ALL ON TABLE sessiontoplayer TO dbadmin;
    GRANT SELECT ON TABLE sessiontoplayer TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE sessiontoplayer TO rw;
    
    GRANT ALL ON TABLE impulsivebuff TO dbadmin;
    GRANT SELECT ON TABLE impulsivebuff TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE impulsivebuff TO rw;
    
    GRANT ALL ON TABLE mgboost TO dbadmin;
    GRANT SELECT ON TABLE mgboost TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE mgboost TO rw;

    GRANT ALL ON TABLE talent TO dbadmin;
    GRANT SELECT ON TABLE talent TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE talent TO rw;

    select increment_version_to(1) into ver;
  end if;

  if ver = 1
  then
    ALTER TABLE sessiontoplayer ADD COLUMN preferfaction character varying(32);
    
    select increment_version_to(2) into ver;
  end if;

  if ver = 2
  then
    ALTER TABLE talent ADD COLUMN cooldown real;
    
    select increment_version_to(3) into ver;
  end if;
  
  if ver = 3
  then
    CREATE TABLE creature
    (
      id integer NOT NULL,
      "name" character varying(255),
      CONSTRAINT creature_pkey PRIMARY KEY (id)
    );
    ALTER TABLE creature OWNER TO dbadmin;
    GRANT ALL ON TABLE creature TO dbadmin;
    GRANT SELECT ON TABLE creature TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE creature TO rw;

    CREATE TABLE building
    (
      id integer NOT NULL,
      "name" character varying(255),
      description character varying(1023),
      CONSTRAINT building_pkey PRIMARY KEY (id)
    );
    ALTER TABLE building OWNER TO dbadmin;
    GRANT ALL ON TABLE building TO dbadmin;
    GRANT SELECT ON TABLE building TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE building TO rw;

    select increment_version_to(4) into ver;
  end if;

  if ver = 4
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
  
    select increment_version_to(5) into ver;
  end if;

  if ver = 5
  then
    CREATE TABLE unittype
    (
      id integer NOT NULL,
      "name" character varying(256),
      CONSTRAINT unittype_pkey PRIMARY KEY (id)
    );
    ALTER TABLE unittype OWNER TO dbadmin;
    GRANT ALL ON TABLE unittype TO dbadmin;
    GRANT SELECT ON TABLE unittype TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE unittype TO rw;

    select increment_version_to(6) into ver;
  end if;
  
  if ver = 6
  then
    alter table player add column nival boolean not null default false;

    select increment_version_to(7) into ver;
  end if;
    
  if ver = 7
  then
    CREATE TABLE abilitytype
    (
      id integer NOT NULL,
      "name" character varying(256),
      CONSTRAINT abilitytype_pkey PRIMARY KEY (id)
    );
    ALTER TABLE abilitytype OWNER TO dbadmin;
    GRANT ALL ON TABLE abilitytype TO dbadmin;
    GRANT SELECT ON TABLE abilitytype TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE abilitytype TO rw;

    ALTER TABLE talent ADD COLUMN abilitytype integer;
    ALTER TABLE talent DROP COLUMN usagemode;
    ALTER TABLE talent ADD
      CONSTRAINT talent_abilitytype_fkey FOREIGN KEY (abilitytype)
      REFERENCES abilitytype (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION;

    select increment_version_to(8) into ver;
  end if;
  
  if ver = 8
  then
    alter table abilitytype add column deleted boolean not null default false;
    alter table building add column deleted boolean not null default false;
    alter table "character" add column deleted boolean not null default false;
    alter table creature add column deleted boolean not null default false;
    alter table impulsivebuff add column deleted boolean not null default false;
    alter table mgboost add column deleted boolean not null default false;
    alter table talent add column deleted boolean not null default false;
    alter table unittype add column deleted boolean not null default false;
    
    select increment_version_to(9) into ver;
  end if;
  
  if ver = 9
  then
    GRANT SELECT, USAGE ON TABLE gamesession_id_sequence TO GROUP ro;
    GRANT SELECT, USAGE ON TABLE player_id_sequence TO GROUP ro;
    GRANT SELECT, USAGE ON TABLE playercharacter_id_sequence TO GROUP ro;
    GRANT SELECT, USAGE ON TABLE sessionsideresult_id_sequence TO GROUP ro;
    GRANT SELECT, USAGE ON TABLE sessiontoplayer_id_sequence TO GROUP ro;
    GRANT ALL ON TABLE gamesession_id_sequence TO GROUP rw;
    GRANT ALL ON TABLE player_id_sequence TO GROUP rw;
    GRANT ALL ON TABLE playercharacter_id_sequence TO GROUP rw;
    GRANT ALL ON TABLE sessionsideresult_id_sequence TO GROUP rw;
    GRANT ALL ON TABLE sessiontoplayer_id_sequence TO GROUP rw;
    
    select increment_version_to(10) into ver;
  end if;

  if ver = 10
  then
    ALTER TABLE player ADD COLUMN sex integer not null default 0;
    
    select increment_version_to(11) into ver;
  end if;
  
  if ver = 11
  then
    ALTER TABLE character ADD COLUMN dbid character varying(255);
    ALTER TABLE talent ADD COLUMN dbid character varying(255);
    ALTER TABLE impulsivebuff ADD COLUMN dbid character varying(255);
    
    select increment_version_to(12) into ver;
  end if;

  if ver = 12
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
    GRANT ALL ON TABLE achievement TO dbadmin;
    GRANT SELECT ON TABLE achievement TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE achievement TO rw;
      
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
    GRANT ALL ON TABLE consumable TO dbadmin;
    GRANT SELECT ON TABLE consumable TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE consumable TO rw;
  
    select increment_version_to(13) into ver;
  end if;

  if ver = 13
  then
    ALTER TABLE "character" ALTER dbid TYPE character varying(1024);
    ALTER TABLE impulsivebuff ALTER dbid TYPE character varying(1024);
    ALTER TABLE talent ALTER dbid TYPE character varying(1024);
  
    select increment_version_to(14) into ver;
  end if;

  if ver = 14
  then
    CREATE TABLE tag
    (
      "name" character varying(50) NOT NULL,
      description character varying(1024),
      CONSTRAINT tag_pkey PRIMARY KEY (name)
    );
    ALTER TABLE tag OWNER TO dbadmin;
    GRANT ALL ON TABLE tag TO dbadmin;
    GRANT SELECT ON TABLE tag TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE tag TO rw;

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
    GRANT ALL ON TABLE player_tags TO dbadmin;
    GRANT SELECT ON TABLE player_tags TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE player_tags TO rw;

    select increment_version_to(15) into ver;
  end if;

  if ver = 15
  then
    -- new version incrementation process
    select increment_version_to(16) into ver;
  end if;

  if ver = 16
  then
    CREATE SEQUENCE socialsession_id_sequence;
    ALTER TABLE socialsession_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE socialsession_id_sequence TO ro;
    GRANT ALL ON TABLE socialsession_id_sequence TO rw;

    CREATE TABLE socialsession
    (
      id integer NOT NULL DEFAULT nextval('socialsession_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE socialsession TO rw;

    select increment_version_to(17) into ver;
  end if;

  if ver = 17
  then
    ALTER TABLE player ALTER id TYPE bigint;
    ALTER TABLE player ALTER COLUMN id DROP DEFAULT;
    ALTER TABLE player ALTER COLUMN "login" DROP NOT NULL;
    ALTER TABLE player ADD COLUMN nickname character varying(255);
    ALTER TABLE player ADD COLUMN faction integer NOT NULL DEFAULT -1;
    DROP SEQUENCE player_id_sequence;
  
    ALTER TABLE gamesession DROP COLUMN sidewon;
    ALTER TABLE gamesession ADD COLUMN sidewon integer NOT NULL DEFAULT -1;
    
    ALTER TABLE sessiontoplayer DROP COLUMN preferfaction;
    
    ALTER TABLE talent ADD COLUMN talentid character varying(1024);
    
    select increment_version_to(18) into ver;
  end if;

  if ver = 18
  then
    CREATE SEQUENCE gm_unlockcharacter_id_sequence;
    ALTER TABLE gm_unlockcharacter_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_unlockcharacter_id_sequence TO ro;
    GRANT ALL ON TABLE gm_unlockcharacter_id_sequence TO rw;
  
    CREATE TABLE gm_unlockcharacter
    (
      id integer NOT NULL DEFAULT nextval('gm_unlockcharacter_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_unlockcharacter TO rw;
    
    CREATE SEQUENCE gm_lockcharacter_id_sequence;
    ALTER TABLE gm_lockcharacter_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_lockcharacter_id_sequence TO ro;
    GRANT ALL ON TABLE gm_lockcharacter_id_sequence TO rw;

    CREATE TABLE gm_lockcharacter
    (
      id integer NOT NULL DEFAULT nextval('gm_lockcharacter_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_lockcharacter TO rw;
    
    select increment_version_to(19) into ver;
  end if;
  
  if ver = 19
  then
    ALTER TABLE gm_unlockcharacter ALTER player TYPE bigint;
    ALTER TABLE gm_lockcharacter ALTER player TYPE bigint;

    CREATE SEQUENCE gm_addtalent_id_sequence;
    ALTER TABLE gm_addtalent_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_addtalent_id_sequence TO ro;
    GRANT ALL ON TABLE gm_addtalent_id_sequence TO rw;

    CREATE TABLE gm_addtalent
    (
      id integer NOT NULL DEFAULT nextval('gm_addtalent_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_addtalent TO rw;

    CREATE SEQUENCE gm_deletetalent_id_sequence;
    ALTER TABLE gm_deletetalent_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_deletetalent_id_sequence TO ro;
    GRANT ALL ON TABLE gm_deletetalent_id_sequence TO rw;

    CREATE TABLE gm_deletetalent
    (
      id integer NOT NULL DEFAULT nextval('gm_deletetalent_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_deletetalent TO rw;

    select increment_version_to(20) into ver;
  end if;

  if ver = 20
  then
    CREATE SEQUENCE gm_banplayer_id_sequence;
    ALTER TABLE gm_banplayer_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_banplayer_id_sequence TO ro;
    GRANT ALL ON TABLE gm_banplayer_id_sequence TO rw;

    CREATE TABLE gm_banplayer
    (
      id integer NOT NULL DEFAULT nextval('gm_banplayer_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_banplayer TO rw;

    CREATE SEQUENCE gm_unbanplayer_id_sequence;
    ALTER TABLE gm_unbanplayer_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_unbanplayer_id_sequence TO ro;
    GRANT ALL ON TABLE gm_unbanplayer_id_sequence TO rw;

    CREATE TABLE gm_unbanplayer
    (
      id integer NOT NULL DEFAULT nextval('gm_unbanplayer_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_unbanplayer TO rw;


    CREATE SEQUENCE gm_muteplayer_id_sequence;
    ALTER TABLE gm_muteplayer_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_muteplayer_id_sequence TO ro;
    GRANT ALL ON TABLE gm_muteplayer_id_sequence TO rw;

    CREATE TABLE gm_muteplayer
    (
      id integer NOT NULL DEFAULT nextval('gm_muteplayer_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_muteplayer TO rw;

    CREATE SEQUENCE gm_unmuteplayer_id_sequence;
    ALTER TABLE gm_unmuteplayer_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_unmuteplayer_id_sequence TO ro;
    GRANT ALL ON TABLE gm_unmuteplayer_id_sequence TO rw;

    CREATE TABLE gm_unmuteplayer
    (
      id integer NOT NULL DEFAULT nextval('gm_unmuteplayer_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_unmuteplayer TO rw;

    select increment_version_to(21) into ver;
  end if;
  
  if ver = 21
  then
    CREATE SEQUENCE chat_id_sequence;
    ALTER TABLE chat_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE chat_id_sequence TO ro;
    GRANT ALL ON TABLE chat_id_sequence TO rw;

    CREATE TABLE chat
    (
      id integer NOT NULL DEFAULT nextval('chat_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE chat TO rw;

    select increment_version_to(22) into ver;
  end if;
  
  if ver = 22
  then
    CREATE SEQUENCE gm_editplayer_id_sequence;
    ALTER TABLE gm_editplayer_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_editplayer_id_sequence TO ro;
    GRANT ALL ON TABLE gm_editplayer_id_sequence TO rw;

    CREATE TABLE gm_editplayer
    (
      id integer NOT NULL DEFAULT nextval('gm_editplayer_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_editplayer TO rw;

    select increment_version_to(23) into ver;
  end if;

  if ver = 23
  then
    alter table gamesession drop column sessionstatus;
    alter table gamesession add column sessionresult integer;
    update gamesession set sessionresult = 0;
    alter table gamesession alter column sessionresult set not null;

    select increment_version_to(24) into ver;
  end if;
  
  if ver = 24
  then
    alter table playercharacter add column locked boolean NOT NULL default false;
    alter table playercharacter add column unlockdate timestamp without time zone;
    
    CREATE SEQUENCE characterunlock_id_sequence;
    ALTER TABLE characterunlock_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE characterunlock_id_sequence TO ro;
    GRANT ALL ON TABLE characterunlock_id_sequence TO rw;

    CREATE TABLE characterunlock
    (
      id integer NOT NULL DEFAULT nextval('characterunlock_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE characterunlock TO rw;

    select increment_version_to(25) into ver;
  end if;

  if ver = 25
  then
    alter table player_tags alter playerid type bigint;
    alter table playercharacter alter player type bigint;
    alter table socialsession alter player type bigint;

    select increment_version_to(26) into ver;
  end if;

  if ver = 26
  then
    update player p
    set faction = coalesce
     ((select stp2.side::integer from sessiontoplayer stp2
       where stp2.id = 
         (select max(stp.id)
          from sessiontoplayer stp
            join playercharacter pc on pc.id = stp.playercharacter
          where pc.player = p.id)),
      p.faction);
  
    alter table talent add column tour integer;
    alter table talent add column rarity integer;
    alter table talent add column budget real;
    
    select increment_version_to(27) into ver;
  end if;

  if ver = 27
  then
    CREATE SEQUENCE monitoring_results_id_sequence;
    ALTER TABLE monitoring_results_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE monitoring_results_id_sequence TO ro;
    GRANT ALL ON TABLE monitoring_results_id_sequence TO rw;

    CREATE TABLE monitoring_results
    (
      id integer NOT NULL DEFAULT nextval('monitoring_results_id_sequence'::regclass),
      property varchar NOT NULL,
      counter varchar NOT NULL,
      "value" integer,
      "timestamp" timestamp without time zone NOT NULL,

      CONSTRAINT monitoring_results_pkey PRIMARY KEY (id)
    );
    ALTER TABLE monitoring_results OWNER TO dbadmin;
    GRANT SELECT ON TABLE monitoring_results TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE monitoring_results TO rw;
  
    -- whoa! first index
    CREATE INDEX idx_monitoring_results_property
      ON monitoring_results 
      USING btree (property);
  
    select increment_version_to(28) into ver;
  end if;

  if ver = 28
  then
    alter table player add lastmodified timestamp default current_timestamp;
    alter table playercharacter add lastmodified timestamp default current_timestamp;
    
    create or replace function update_timestamp()
    returns trigger as
    $func$
    begin
      NEW.lastmodified = now();
      return NEW;
    end;
    $func$
    language plpgsql;
    
    create trigger update_player_lastmodified before update 
    on player for each row execute procedure update_timestamp();

    create trigger update_playercharacter_lastmodified before update 
    on playercharacter for each row execute procedure update_timestamp();
    
    select increment_version_to(29) into ver;
  end if;

  if ver = 29
  then
    alter table character ADD COLUMN gender integer;
    update character set gender = 0;

    select increment_version_to(30) into ver;
  end if;
  
  if ver = 30
  then
    CREATE SEQUENCE mmakingsession_id_sequence;
    ALTER TABLE mmakingsession_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE mmakingsession_id_sequence TO ro;
    GRANT ALL ON TABLE mmakingsession_id_sequence TO rw;

    create table mmakingsession
    (
      id bigint not null not null DEFAULT nextval('mmakingsession_id_sequence'::regclass),
      persistentid bigint not null,
      status integer not null,
      "timestamp" timestamp without time zone,
      CONSTRAINT mmakingsession_pkey PRIMARY KEY (id),
      CONSTRAINT mmakingsession_unique_persistentid UNIQUE (persistentid)
    );
    ALTER TABLE mmakingsession OWNER TO dbadmin;
    GRANT SELECT ON TABLE mmakingsession TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE mmakingsession TO rw;

    CREATE SEQUENCE mmakingplayer_id_sequence;
    ALTER TABLE mmakingplayer_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE mmakingplayer_id_sequence TO ro;
    GRANT ALL ON TABLE mmakingplayer_id_sequence TO rw;
        
    create table mmakingplayer
    (
      id bigint not null DEFAULT nextval('mmakingplayer_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE mmakingplayer TO rw;

    alter table gamesession add column mmakingsession bigint;

    select increment_version_to(31) into ver;
  end if;

  if ver = 31
  then
    alter table player DROP COLUMN login;

    select increment_version_to(32) into ver;
  end if;

  if ver = 32
  then
    if not exists (
      select *
      from pg_attribute a
        join pg_class p on p.oid = attrelid
      where attname = 'persistentid'
        and relname = 'mmakingsession')
    then
      raise 'Before updating, please RUN FIX PWMANAGEMENT_NUM_TASK.SQL !';
    end if;

    select increment_version_to(33) into ver;
  end if;
  
  if ver = 33
  then
    CREATE SEQUENCE movetobath_id_sequence;
    ALTER TABLE movetobath_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE movetobath_id_sequence TO ro;
    GRANT ALL ON TABLE movetobath_id_sequence TO rw;

    CREATE TABLE movetobath
    (
      id integer NOT NULL DEFAULT nextval('movetobath_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE movetobath TO rw;

    select increment_version_to(34) into ver;
  end if;
  
  if ver = 34
  then
    alter table player add column rating integer;
    alter table player add column reliability integer;
    update player set rating = 0, reliability = 0;
    alter table player alter column rating set not null;
    alter table player alter column reliability set not null;

    alter table gamesession rename column mmakingsession to persistentid;
    alter table gamesession add constraint gamesession_unique_persistentid unique (persistentid);
    alter table gamesession drop constraint fkb7c2a5614245b9e4;
    alter table gamesession drop constraint fkb7c2a5614245be4b;

    alter table gamesession drop column sidearesult;
    alter table gamesession drop column sidebresult;

    drop table sessionsideresult;
    drop sequence sessionsideresult_id_sequence;

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

    select increment_version_to(35) into ver;
  end if;

  if ver = 35
  then
    alter table sessiontoplayer add column leaver boolean;
    alter table playercharacter add constraint playercharacter_unique_player_character UNIQUE (player, character);

    select increment_version_to(36) into ver;
  end if;
  
  if ver = 36
  then
    CREATE SEQUENCE talentroll_id_sequence;
    ALTER TABLE talentroll_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE talentroll_id_sequence TO ro;
    GRANT ALL ON TABLE talentroll_id_sequence TO rw;

    CREATE TABLE talentroll
    (
      id bigint NOT NULL DEFAULT nextval('talentroll_id_sequence'::regclass),
      sessiontoplayer integer NOT NULL,
      talent integer NOT NULL,
      CONSTRAINT talentroll_pkey PRIMARY KEY (id),
      CONSTRAINT talentroll_sessiontoplayer_fkey FOREIGN KEY (sessiontoplayer) REFERENCES sessiontoplayer (id),
      CONSTRAINT talentroll_talent_fkey FOREIGN KEY (talent) REFERENCES talent (id)
    );
    ALTER TABLE talentroll OWNER TO dbadmin;
    GRANT SELECT ON TABLE talentroll TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE talentroll TO rw;

    select increment_version_to(37) into ver;
  end if;

  if ver = 37
  then
    alter table player add column banneduntil timestamp without time zone;

    select increment_version_to(38) into ver;
  end if;

  if ver = 38
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

    select increment_version_to(39) into ver;
  end if;

  if ver = 39
  then
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_playercharacter_fkey
      FOREIGN KEY (playercharacter) REFERENCES playercharacter (id);
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_gamesession_fkey
      FOREIGN KEY (gamesession) REFERENCES gamesession (id);
    ALTER TABLE sessiontoplayer DROP CONSTRAINT fkdd15357a43eaf094;
    ALTER TABLE sessiontoplayer DROP CONSTRAINT fkdd15357a5a94f0ab;
    CREATE INDEX idx_sessiontoplayer_playercharacter ON sessiontoplayer (playercharacter);
    CREATE INDEX idx_sessiontoplayer_gamesession ON sessiontoplayer (gamesession);
    CREATE INDEX idx_socialsession_player ON player (id);

    select increment_version_to(40) into ver;
  end if;

  if ver = 40
  then
    create or replace function update_timestamp()
    returns trigger as
    $body$
    begin
      NEW.lastmodified = current_timestamp at time zone 'utc';
      return NEW;
    end;
    $body$ language plpgsql;

    select increment_version_to(41) into ver;
  end if;

  if ver = 41
  then
    CREATE SEQUENCE resourcelog_id_sequence;
    ALTER TABLE resourcelog_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE resourcelog_id_sequence TO ro;
    GRANT ALL ON TABLE resourcelog_id_sequence TO rw;

    CREATE TABLE resourcelog
    (
      id bigint NOT NULL DEFAULT nextval('resourcelog_id_sequence'::regclass),
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
      CONSTRAINT resourcelog_pkey PRIMARY KEY (id),
      CONSTRAINT resourcelog_player_fkey FOREIGN KEY (player) REFERENCES player (id)
    );
    ALTER TABLE resourcelog OWNER TO dbadmin;
    GRANT SELECT ON TABLE resourcelog TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE resourcelog TO rw;
    
    ALTER TABLE sessiontoplayer ADD COLUMN resourcelog bigint;
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_resourcelog_fkey
      FOREIGN KEY (resourcelog) REFERENCES resourcelog (id);

    for tmprow in (
      SELECT stp.id, stp.silverchange, stp.silvertotal, pc.player, gs.endtime
      FROM sessiontoplayer stp
        JOIN gamesession gs on gs.id = stp.gamesession
        JOIN playercharacter pc on pc.id = stp.playercharacter
      WHERE stp.silverchange > 0 )
    loop
      INSERT INTO resourcelog (source, gain, player, silverchange, silvertotal, timestamp)
        VALUES ('session', true, tmprow.player, tmprow.silverchange, tmprow.silvertotal, tmprow.endtime);
      UPDATE sessiontoplayer
      SET resourcelog = (select last_value from resourcelog_id_sequence)
      WHERE id = tmprow.id;
    end loop;

    ALTER TABLE sessiontoplayer DROP COLUMN silverchange;
    ALTER TABLE sessiontoplayer DROP COLUMN silvertotal;

    ALTER TABLE characterunlock ADD COLUMN resourcelog bigint;
    ALTER TABLE characterunlock ADD CONSTRAINT characterunlock_resourcelog_fkey
      FOREIGN KEY (resourcelog) REFERENCES resourcelog (id);

    for tmprow in (
      SELECT cu.id, pc.player, cu.silver, cu.timestamp
      FROM characterunlock cu
        JOIN playercharacter pc on pc.id = cu.playercharacter )
    loop
      INSERT INTO resourcelog (source, gain, player, silverchange, timestamp)
        VALUES ('characterunlock', false, tmprow.player, -tmprow.silver, tmprow.timestamp);
      UPDATE characterunlock
      SET resourcelog = (select last_value from resourcelog_id_sequence)
      WHERE id = tmprow.id;
    end loop;

    ALTER TABLE characterunlock DROP COLUMN silver;

    ALTER TABLE movetobath ADD COLUMN resourcelog bigint;
    ALTER TABLE movetobath ADD CONSTRAINT movetobath_resourcelog_fkey
      FOREIGN KEY (resourcelog) REFERENCES resourcelog (id);
    ALTER TABLE movetobath DROP COLUMN silver;

    select increment_version_to(42) into ver;
  end if;

  if ver = 42
  then
    ALTER TABLE resourcelog ADD COLUMN buildingname character varying;

    select increment_version_to(43) into ver;
  end if;

  if ver = 43
  then
    ALTER TABLE player ALTER COLUMN lastmodified DROP DEFAULT;
    ALTER TABLE playercharacter ALTER COLUMN lastmodified DROP DEFAULT;

    select increment_version_to(44) into ver;
  end if;

  if ver = 44
  then
    UPDATE player
    SET lastmodified = CURRENT_TIMESTAMP AT TIME ZONE 'UTC'
    WHERE lastmodified IS NULL;

    UPDATE playercharacter
    SET lastmodified = CURRENT_TIMESTAMP AT TIME ZONE 'UTC'
    WHERE lastmodified IS NULL;

    ALTER TABLE player ALTER COLUMN lastmodified SET NOT NULL;
    ALTER TABLE playercharacter ALTER COLUMN lastmodified SET NOT NULL;

    DROP TRIGGER update_player_lastmodified ON player;
    CREATE TRIGGER update_player_lastmodified BEFORE INSERT OR UPDATE 
      ON player FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

    DROP TRIGGER update_playercharacter_lastmodified ON playercharacter;
    CREATE TRIGGER update_playercharacter_lastmodified BEFORE INSERT OR UPDATE 
      ON playercharacter FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

    select increment_version_to(45) into ver;
  end if;

  if ver = 45
  then
    ALTER TABLE playercharacter ADD COLUMN rating INTEGER;
    UPDATE playercharacter pc
    SET rating = COALESCE((SELECT ratingtotal FROM sessiontoplayer
                           WHERE id = (SELECT MAX(id) FROM sessiontoplayer
                                       WHERE playercharacter = pc.id AND ratingtotal > 0)), 0);
    ALTER TABLE playercharacter ALTER COLUMN rating SET NOT NULL;
    ALTER TABLE player DROP COLUMN rating;

    select increment_version_to(46) into ver;
  end if;

  if ver = 46
  then
    ALTER TABLE mmakingsession ADD COLUMN manoeuvresfaction INTEGER NOT NULL DEFAULT -1;
    ALTER TABLE mmakingsession ALTER COLUMN manoeuvresfaction DROP DEFAULT;

    select increment_version_to(47) into ver;
  end if;

  if ver = 47
  then
    ALTER TABLE mmakingplayer ADD COLUMN "timestamp" TIMESTAMP;

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

    ALTER TABLE mmakingplayer ALTER COLUMN "timestamp" SET NOT NULL;

    ALTER TABLE mmakingplayer ADD COLUMN force REAL NOT NULL DEFAULT 0;
    ALTER TABLE mmakingplayer ALTER COLUMN force DROP DEFAULT;

    select increment_version_to(48) into ver;
  end if;

  if ver = 48
  then
    ALTER TABLE sessiontoplayer ADD COLUMN faction INTEGER;
    UPDATE sessiontoplayer SET faction = side::INTEGER;
    ALTER TABLE sessiontoplayer DROP COLUMN side;

    CREATE SEQUENCE factionchange_id_sequence;
    ALTER TABLE factionchange_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE factionchange_id_sequence TO ro;
    GRANT ALL ON TABLE factionchange_id_sequence TO rw;

    CREATE TABLE factionchange
    (
      id integer NOT NULL DEFAULT nextval('factionchange_id_sequence'::regclass),
      player bigint NOT NULL,
      oldfaction integer,
      newfaction integer,
      resourcelog bigint,
      "timestamp" timestamp NOT NULL,
      CONSTRAINT factionchange_pkey PRIMARY KEY (id),
      CONSTRAINT factionchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT factionchange_resourcelog_fkey FOREIGN KEY (resourcelog) REFERENCES resourcelog (id)
    );
    ALTER TABLE factionchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE factionchange TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE factionchange TO rw;

    CREATE INDEX idx_factionchange_player ON player (id);

    UPDATE resourcelog
    SET source = 'factionchange'
    WHERE source = 'changefraction';

    select increment_version_to(49) into ver;
  end if;

  if ver = 49
  then
    ALTER TABLE sessiontoplayer ADD COLUMN force REAL DEFAULT 0;
    ALTER TABLE sessiontoplayer ALTER COLUMN force DROP DEFAULT;

    select increment_version_to(50) into ver;
  end if;

  if ver = 50
  then
    ALTER TABLE mmakingplayer ADD COLUMN losestreak INTEGER NOT NULL DEFAULT 0;
    ALTER TABLE mmakingplayer ALTER COLUMN losestreak DROP DEFAULT;

    select increment_version_to(51) into ver;
  end if;

  if ver = 51
  then
    ALTER TABLE mmakingplayer ADD COLUMN famelevel INTEGER NOT NULL DEFAULT 0;
    ALTER TABLE mmakingplayer ALTER COLUMN famelevel DROP DEFAULT;

    select increment_version_to(52) into ver;
  end if;

  if ver = 52
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
    GRANT SELECT, UPDATE, INSERT ON TABLE quest TO rw;

    CREATE SEQUENCE questchange_id_sequence;
    ALTER TABLE questchange_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE questchange_id_sequence TO ro;
    GRANT ALL ON TABLE questchange_id_sequence TO rw;

    CREATE TABLE questchange
    (
      id integer NOT NULL DEFAULT nextval('questchange_id_sequence'::regclass),
      player bigint NOT NULL,
      quest integer NOT NULL,
      changetype integer NOT NULL,
      "timestamp" timestamp NOT NULL,
      CONSTRAINT questchange_pkey PRIMARY KEY (id),
      CONSTRAINT questchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT questchange_quest_fkey FOREIGN KEY (quest) REFERENCES quest (id)
    );
    ALTER TABLE questchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE questchange TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE questchange TO rw;

    DROP TABLE player_tags;
    DROP TABLE tag;

    select increment_version_to(53) into ver;
  end if;

  if ver = 53
  then
    ALTER TABLE gamesession ADD COLUMN surrendervote INTEGER NOT NULL DEFAULT 0;
    ALTER TABLE gamesession ALTER COLUMN surrendervote DROP DEFAULT;

    select increment_version_to(54) into ver;
  end if;

  if ver = 54
  then
    DELETE FROM talent WHERE name like 'Автоатака%';

    select increment_version_to(55) into ver;
  end if;

  if ver = 55
  then
    CREATE INDEX idx_player_lastmodified ON player (lastmodified);
    CREATE INDEX idx_playercharacter_lastmodified ON playercharacter (lastmodified);

    select increment_version_to(56) into ver;
  end if;

  if ver = 56
  then
    ALTER TABLE mmakingsession ADD COLUMN basket INTEGER NOT NULL DEFAULT -1;
    ALTER TABLE mmakingsession ALTER COLUMN basket DROP DEFAULT;
    ALTER TABLE mmakingplayer ADD COLUMN basket INTEGER NOT NULL DEFAULT -1;
    ALTER TABLE mmakingplayer ALTER COLUMN basket DROP DEFAULT;

    select increment_version_to(57) into ver;
  end if;

  if ver = 57
  then
    CREATE SEQUENCE ratingchange_id_sequence;
    ALTER TABLE ratingchange_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE ratingchange_id_sequence TO ro;
    GRANT ALL ON TABLE ratingchange_id_sequence TO rw;

    CREATE TABLE ratingchange
    (
      id integer NOT NULL DEFAULT nextval('ratingchange_id_sequence'::regclass),
      type integer NOT NULL,
      player bigint NOT NULL,
      persistentid bigint,
      character integer,
      change integer,
      total bigint,
      "timestamp" timestamp NOT NULL,
      CONSTRAINT ratingchange_pkey PRIMARY KEY (id),
      CONSTRAINT ratingchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT ratingchange_character_fkey FOREIGN KEY (character) REFERENCES character (id)
    );
    ALTER TABLE ratingchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE ratingchange TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE ratingchange TO rw;

    ALTER TABLE player ADD COLUMN rating integer NOT NULL DEFAULT 0;
    ALTER TABLE player ALTER COLUMN rating DROP DEFAULT;

    select increment_version_to(58) into ver;
  end if;

  if ver = 58
  then
    CREATE INDEX idx_resourcelog_timestamp ON resourcelog (timestamp);

    ALTER TABLE sessiontoplayer DROP CONSTRAINT IF EXISTS sessiontoplayer_resourcelog_fkey;
    ALTER TABLE factionchange DROP CONSTRAINT IF EXISTS factionchange_resourcelog_fkey;
    ALTER TABLE characterunlock DROP CONSTRAINT IF EXISTS characterunlock_resourcelog_fkey;
    ALTER TABLE movetobath DROP CONSTRAINT IF EXISTS movetobath_resourcelog_fkey;

    select increment_version_to(59) into ver;
  end if;

  if ver = 59
  then
    ALTER TABLE player ADD COLUMN locale character varying NOT NULL DEFAULT 'RU';
    ALTER TABLE player ALTER COLUMN locale DROP DEFAULT;

    select increment_version_to(60) into ver;
  end if;

  if ver = 60
  then
    ALTER TABLE gamesession DROP CONSTRAINT gamesession_unique_persistentid;

    UPDATE gamesession
    SET persistentid = idclient
    WHERE persistentid IS NULL;

    ALTER TABLE gamesession ALTER COLUMN persistentid SET NOT NULL;
    ALTER TABLE gamesession DROP COLUMN idclient;

    CREATE INDEX idx_gamesession_persistentid ON gamesession (persistentid);

    select increment_version_to(61) into ver;
  end if;

  if ver = 61
  then
    ALTER TABLE sessiontoplayer ADD COLUMN relayaddress varchar;

    select increment_version_to(62) into ver;
  end if;

  if ver = 62
  then
    DROP INDEX IF EXISTS idx_factionchange_player;
    DROP INDEX IF EXISTS idx_socialsession_player;
    CREATE INDEX idx_socialsession_player ON socialsession (player);

    ALTER TABLE resourcelog ADD COLUMN persistentid bigint;

    ALTER TABLE sessiontoplayer DROP COLUMN ratingchange;
    ALTER TABLE sessiontoplayer DROP COLUMN ratingtotal;
    ALTER TABLE sessiontoplayer DROP COLUMN reliabilitychange;
    ALTER TABLE sessiontoplayer DROP COLUMN reliabilitytotal;
    ALTER TABLE sessiontoplayer DROP COLUMN force;

    ALTER TABLE talentroll ALTER COLUMN sessiontoplayer DROP NOT NULL;
    ALTER TABLE talentroll DROP CONSTRAINT talentroll_sessiontoplayer_fkey;
    ALTER TABLE talentroll ADD COLUMN player bigint;       -- should be NOT NULL
    ALTER TABLE talentroll ADD COLUMN persistentid bigint; -- should be NOT NULL
    ALTER TABLE talentroll ADD CONSTRAINT talentroll_player_fkey FOREIGN KEY (player) REFERENCES player (id);

    RAISE NOTICE '-----------------------------------------------------';
    RAISE NOTICE '---  RUN UPDATE SCRIPT ATTACHED TO TASK NUM_TASK  ---';
    RAISE NOTICE '-----------------------------------------------------';

    select increment_version_to(63) into ver;
  end if;

  if ver = 63
  then
    CREATE SEQUENCE talentjoinsession_id_sequence;
    ALTER TABLE talentjoinsession_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE talentjoinsession_id_sequence TO ro;
    GRANT ALL ON TABLE talentjoinsession_id_sequence TO rw;

    CREATE TABLE talentjoinsession
    (
      id bigint NOT NULL DEFAULT nextval('talentjoinsession_id_sequence'::regclass),
      player bigint NOT NULL,
      character bigint NOT NULL,
      persistentid bigint NOT NULL,
      talent integer NOT NULL,
      CONSTRAINT talentjoinsession_pkey PRIMARY KEY (id),
      CONSTRAINT talentjoinsession_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT talentjoinsession_character_fkey FOREIGN KEY (character) REFERENCES character (id),
      CONSTRAINT talentjoinsession_talent_fkey FOREIGN KEY (talent) REFERENCES talent (id)
    );
    ALTER TABLE talentjoinsession OWNER TO dbadmin;
    GRANT SELECT ON TABLE talentjoinsession TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE talentjoinsession TO rw;

    select increment_version_to(64) into ver;
  end if;

  if ver = 64
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
    GRANT SELECT, UPDATE, INSERT ON TABLE guild TO rw;

    CREATE TRIGGER update_guild_lastmodified BEFORE INSERT OR UPDATE
      ON guild FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

    ALTER TABLE player ADD COLUMN guild bigint;
    ALTER TABLE player ADD CONSTRAINT player_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id);

    CREATE SEQUENCE guildmembership_id_sequence;
    ALTER TABLE guildmembership_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE guildmembership_id_sequence TO ro;
    GRANT ALL ON TABLE guildmembership_id_sequence TO rw;

    CREATE TABLE guildmembership
    (
      id integer NOT NULL DEFAULT nextval('guildmembership_id_sequence'::regclass),
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
    GRANT SELECT, UPDATE, INSERT ON TABLE guildmembership TO rw;    

    CREATE TRIGGER update_guildmembership_lastmodified BEFORE INSERT OR UPDATE
      ON guildmembership FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

    select increment_version_to(65) into ver;
  end if;

  if ver = 65
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
    GRANT SELECT, UPDATE, INSERT ON TABLE rune TO rw;


    CREATE SEQUENCE runeroll_id_sequence;
    ALTER TABLE runeroll_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE runeroll_id_sequence TO ro;
    GRANT ALL ON TABLE runeroll_id_sequence TO rw;

    CREATE TABLE runeroll
    (
      id bigint NOT NULL DEFAULT nextval('runeroll_id_sequence'::regclass),
      player bigint NOT NULL,
      persistentid bigint NOT NULL,
      rune integer NOT NULL,
      CONSTRAINT runeroll_pkey PRIMARY KEY (id),
      CONSTRAINT runeroll_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT runeroll_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id)
    );
    ALTER TABLE runeroll OWNER TO dbadmin;
    GRANT SELECT ON TABLE runeroll TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE runeroll TO rw;

    CREATE SEQUENCE runereplenish_id_sequence;
    ALTER TABLE runereplenish_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE runereplenish_id_sequence TO ro;
    GRANT ALL ON TABLE runereplenish_id_sequence TO rw;

    CREATE TABLE runereplenish
    (
      id bigint NOT NULL DEFAULT nextval('runereplenish_id_sequence'::regclass),
      player bigint NOT NULL,
      rune integer NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT runereplenish_pkey PRIMARY KEY (id),
      CONSTRAINT runereplenish_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT runereplenish_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id)
    );
    ALTER TABLE runereplenish OWNER TO dbadmin;
    GRANT SELECT ON TABLE runereplenish TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE runereplenish TO rw;

    CREATE SEQUENCE runeunsoulbound_id_sequence;
    ALTER TABLE runeunsoulbound_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE runeunsoulbound_id_sequence TO ro;
    GRANT ALL ON TABLE runeunsoulbound_id_sequence TO rw;

    CREATE TABLE runeunsoulbound
    (
      id bigint NOT NULL DEFAULT nextval('runeunsoulbound_id_sequence'::regclass),
      player bigint NOT NULL,
      rune integer NOT NULL,
      talent integer NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT runeunsoulbound_pkey PRIMARY KEY (id),
      CONSTRAINT runeunsoulbound_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT runeunsoulbound_talent_fkey FOREIGN KEY (talent) REFERENCES talent (id),
      CONSTRAINT runeunsoulbound_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id)
    );
    ALTER TABLE runeunsoulbound OWNER TO dbadmin;
    GRANT SELECT ON TABLE runeunsoulbound TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE runeunsoulbound TO rw;

    CREATE SEQUENCE runeexpire_id_sequence;
    ALTER TABLE runeexpire_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE runeexpire_id_sequence TO ro;
    GRANT ALL ON TABLE runeexpire_id_sequence TO rw;

    CREATE TABLE runeexpire
    (
      id bigint NOT NULL DEFAULT nextval('runeexpire_id_sequence'::regclass),
      player bigint NOT NULL,
      rune integer NOT NULL,
      transactionsleft integer NOT NULL,
      bonusleft integer NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT runeexpire_pkey PRIMARY KEY (id),
      CONSTRAINT runeexpire_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT runeexpire_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id)
    );
    ALTER TABLE runeexpire OWNER TO dbadmin;
    GRANT SELECT ON TABLE runeexpire TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE runeexpire TO rw;

    select increment_version_to(66) into ver;
  end if; 

  if ver = 66
  then

    ALTER TABLE runeroll ADD COLUMN timestamp timestamp;

    select increment_version_to(67) into ver;
  end if; 

  if ver = 67
  then

    ALTER TABLE mmakingplayer ADD COLUMN lobbyreactiontime real;

    select increment_version_to(68) into ver;
  end if; 

  if ver = 68
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
    GRANT SELECT, UPDATE, INSERT ON TABLE castlebuilding TO rw;

    select increment_version_to(69) into ver;
  end if; 

  if ver = 69
  then

    ALTER TABLE mmakingplayer ADD COLUMN playerrating integer;
    ALTER TABLE mmakingsession ADD COLUMN map varchar;

    select increment_version_to(70) into ver;
  end if; 

  if ver = 70
  then

    CREATE SEQUENCE gm_useroperation_id_sequence;
    ALTER TABLE gm_useroperation_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_useroperation_id_sequence TO ro;
    GRANT ALL ON TABLE gm_useroperation_id_sequence TO rw;

    CREATE TABLE gm_useroperation
    (
      id integer NOT NULL DEFAULT nextval('gm_useroperation_id_sequence'::regclass),
      type integer NOT NULL,
      player bigint NOT NULL,
      minutes integer NOT NULL,
      reason varchar,
      gmlogin varchar NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT gm_useroperation_pkey PRIMARY KEY (id),
      CONSTRAINT gm_useroperation_player_fkey FOREIGN KEY (player) REFERENCES player (id)
    );
    ALTER TABLE gm_useroperation OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_useroperation TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_useroperation TO rw;

    INSERT INTO gm_useroperation 
    (type,player,minutes,reason,gmlogin,timestamp)
    SELECT 0,player,minutes,reason,gmlogin,operationdate 
    FROM gm_banplayer
    UNION ALL
    SELECT 1,player,minutes,reason,gmlogin,operationdate 
    FROM gm_muteplayer
    UNION ALL
    SELECT 2,player,0,null,gmlogin,operationdate 
    FROM gm_unbanplayer
    UNION ALL
    SELECT 3,player,0,null,gmlogin,operationdate 
    FROM gm_unmuteplayer
    ORDER BY operationdate;

    DROP TABLE gm_banplayer;
    DROP TABLE gm_muteplayer;
    DROP TABLE gm_unbanplayer;
    DROP TABLE gm_unmuteplayer;

    CREATE SEQUENCE claim_id_sequence;
    ALTER TABLE claim_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE claim_id_sequence TO ro;
    GRANT ALL ON TABLE claim_id_sequence TO rw;

    CREATE TABLE claim
    (
      id integer NOT NULL DEFAULT nextval('claim_id_sequence'::regclass),
      fromplayer bigint NOT NULL,
      toplayer bigint NOT NULL,
      source integer NOT NULL,
      category integer NOT NULL,
      comment varchar,
      chatlog varchar,
      timestamp timestamp NOT NULL,
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
      CONSTRAINT claim_gmuseroperation_fkey FOREIGN KEY (gmuseroperation) REFERENCES gm_useroperation (id)
    );
    ALTER TABLE claim OWNER TO dbadmin;
    GRANT SELECT ON TABLE claim TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE claim TO rw;

    CREATE TRIGGER update_claim_lastmodified BEFORE INSERT OR UPDATE 
      ON claim FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

    CREATE INDEX idx_claim_lastmodified ON claim (lastmodified);
    CREATE INDEX idx_claim_timestamp ON claim (timestamp);

    ALTER TABLE player DROP COLUMN banneduntil;

    select increment_version_to(71) into ver;
  end if; 

  if ver = 71
  then

    CREATE SCHEMA partitions AUTHORIZATION dbadmin;
    GRANT ALL ON SCHEMA partitions TO rw;
    GRANT ALL ON SCHEMA partitions TO ro;

    ALTER TABLE player DROP COLUMN rating;
    ALTER TABLE playercharacter DROP COLUMN rating;

    ALTER TABLE sessiontoplayer ADD COLUMN starttime timestamp;
    ALTER TABLE talentroll ADD COLUMN timestamp timestamp;


    CREATE OR REPLACE FUNCTION mmakingsession_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION mmakingsession_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_mmakingsession_partition BEFORE INSERT ON mmakingsession 
      FOR EACH ROW EXECUTE PROCEDURE mmakingsession_insert_trigger();

    CREATE OR REPLACE FUNCTION mmakingplayer_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION mmakingplayer_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_mmakingplayer_partition BEFORE INSERT ON mmakingplayer 
      FOR EACH ROW EXECUTE PROCEDURE mmakingplayer_insert_trigger();

    CREATE OR REPLACE FUNCTION resourcelog_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION resourcelog_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_resourcelog_partition BEFORE INSERT ON resourcelog 
      FOR EACH ROW EXECUTE PROCEDURE resourcelog_insert_trigger();

    CREATE OR REPLACE FUNCTION gamesession_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION gamesession_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_gamesession_partition BEFORE INSERT ON gamesession 
      FOR EACH ROW EXECUTE PROCEDURE gamesession_insert_trigger();

    CREATE OR REPLACE FUNCTION sessiontoplayer_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION sessiontoplayer_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_sessiontoplayer_partition BEFORE INSERT ON sessiontoplayer 
      FOR EACH ROW EXECUTE PROCEDURE sessiontoplayer_insert_trigger();

    CREATE OR REPLACE FUNCTION socialsession_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION socialsession_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_socialsession_partition BEFORE INSERT ON socialsession 
      FOR EACH ROW EXECUTE PROCEDURE socialsession_insert_trigger();

    CREATE OR REPLACE FUNCTION questchange_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION questchange_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_questchange_partition BEFORE INSERT ON questchange 
      FOR EACH ROW EXECUTE PROCEDURE questchange_insert_trigger();

    DROP TRIGGER update_claim_lastmodified ON claim;
    CREATE TRIGGER first_tr_claim_lastmodified BEFORE INSERT OR UPDATE 
      ON claim FOR EACH ROW EXECUTE PROCEDURE update_timestamp();
    CREATE OR REPLACE FUNCTION claim_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION claim_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_claim_partition BEFORE INSERT ON claim 
      FOR EACH ROW EXECUTE PROCEDURE claim_insert_trigger();

    CREATE OR REPLACE FUNCTION characterunlock_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION characterunlock_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_characterunlock_partition BEFORE INSERT ON characterunlock 
      FOR EACH ROW EXECUTE PROCEDURE characterunlock_insert_trigger();

    CREATE OR REPLACE FUNCTION movetobath_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION movetobath_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_movetobath_partition BEFORE INSERT ON movetobath 
      FOR EACH ROW EXECUTE PROCEDURE movetobath_insert_trigger();

    CREATE OR REPLACE FUNCTION talentroll_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION talentroll_insert_trigger() OWNER TO dbadmin;
    CREATE TRIGGER tr_talentroll_partition BEFORE INSERT ON talentroll 
      FOR EACH ROW EXECUTE PROCEDURE talentroll_insert_trigger();

    /*
    DROP TABLE talentjoinsession;
    DROP TABLE ratingchange;
    */

    CREATE OR REPLACE FUNCTION create_partition(parent varchar, col varchar)
      RETURNS void AS
    $$
    DECLARE
      date1 timestamp;
      d timestamp;
      
      parentoid regclass;
      child varchar;
      suffix varchar;
      
      script varchar;
      elsifs varchar = '';
      r record;

    BEGIN
      parentoid = parent::regclass;
      date1 = date_trunc('month', now());

      FOR d IN (select unnest(('{'''||date1||''','''||(date1+interval'1month')||'''}')::text[])) LOOP
      BEGIN
        suffix = to_char(d, 'yyyyMM');
        child = parent||'_'||suffix;

        elsifs = elsifs||'
          ELSIF (NEW.'||col||' >= '''||d||''' and NEW.'||col||' < '''||(d+interval'1month')||''') THEN
            INSERT INTO partitions.'||child||' VALUES (NEW.*);';
        
        -- check if table already exists
        PERFORM ('partitions.'||child)::regclass;
        
      EXCEPTION
      WHEN undefined_table THEN
        -- create child table
        EXECUTE 
        'CREATE TABLE partitions.'||child||' '||
        '( CHECK ('||col||' >= '''||d||''' and '||col||' < '''||(d+interval'1month')||''')) '||
        'INHERITS ('||parent||')';
        EXECUTE 'ALTER TABLE partitions.'||child||' OWNER TO dbadmin';
        EXECUTE 'GRANT SELECT ON TABLE partitions.'||child||' TO ro';
        EXECUTE 'GRANT SELECT, UPDATE, INSERT ON TABLE partitions.'||child||' TO rw';

        IF (parent = 'sessiontoplayer') THEN
          EXECUTE 
            'ALTER TABLE partitions.'||child||' ADD CONSTRAINT '||child||'_pkey 
             PRIMARY KEY (id)';
          EXECUTE 
            'ALTER TABLE partitions.'||child||' ADD CONSTRAINT '||child||'_playercharacter_fkey
             FOREIGN KEY (playercharacter) REFERENCES playercharacter (id)';
          EXECUTE 
            'ALTER TABLE partitions.'||child||' ADD CONSTRAINT '||child||'_gamesession_fkey
             FOREIGN KEY (gamesession) REFERENCES partitions.gamesession_'||suffix||' (id)';
             
        ELSIF (parent = 'mmakingplayer') THEN
          EXECUTE 
            'ALTER TABLE partitions.'||child||' ADD CONSTRAINT '||child||'_pkey 
             PRIMARY KEY (id)';
          EXECUTE 
            'ALTER TABLE partitions.'||child||' ADD CONSTRAINT '||child||'_playercharacter_fkey
             FOREIGN KEY (playercharacter) REFERENCES playercharacter (id)';
          EXECUTE 
            'ALTER TABLE partitions.'||child||' ADD CONSTRAINT '||child||'_mmakingsession_fkey
             FOREIGN KEY (mmakingsession) REFERENCES partitions.mmakingsession_'||suffix||' (id)';

        ELSE
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
        END IF;
        
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
      END LOOP;

      -- replace insert trigger
      EXECUTE '
        CREATE OR REPLACE FUNCTION '||parent||'_insert_trigger()
        RETURNS TRIGGER AS $CODE$
        BEGIN
          IF ( false ) THEN RAISE;'||elsifs||'
          ELSE
            RAISE EXCEPTION ''Unexpected '||col||' value. Fix the '||parent||'_insert_trigger() function!'';
          END IF;
          RETURN NULL;
        END;
        $CODE$ LANGUAGE plpgsql;
        ALTER FUNCTION '||parent||'_insert_trigger() OWNER TO dbadmin;
        GRANT EXECUTE ON FUNCTION '||parent||'_insert_trigger() TO rw;
        ';

    END;
    $$ LANGUAGE plpgsql;
    ALTER FUNCTION create_partition(varchar, varchar) OWNER TO dbadmin;

    select increment_version_to(72) into ver;
  end if; 

  if ver = 72
  then

    IF NOT EXISTS (SELECT * FROM pg_class WHERE relname = 'idx_resourcelog_player') THEN
      CREATE INDEX idx_resourcelog_player ON resourcelog (player);
    END IF;    

    select increment_version_to(73) into ver;
  end if;

  if ver = 73
  then

    IF NOT EXISTS (
      SELECT * FROM pg_attribute a JOIN pg_class p ON p.oid = attrelid
      WHERE attname = 'locale' AND relname = 'claim')
    THEN
      ALTER TABLE claim ADD COLUMN locale character varying NOT NULL DEFAULT 'RU';
      ALTER TABLE claim ALTER COLUMN locale DROP DEFAULT;
    END IF;

    select increment_version_to(74) into ver;
  end if;

  if ver = 74
  then

    CREATE SEQUENCE talentlog_id_sequence;
    ALTER TABLE talentlog_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE talentlog_id_sequence TO ro;
    GRANT ALL ON TABLE talentlog_id_sequence TO rw;

    CREATE TABLE talentlog
    (
      id bigint NOT NULL DEFAULT nextval('talentlog_id_sequence'::regclass),
      operation varchar NOT NULL,
      player bigint NOT NULL,
      talent integer NOT NULL,
      talentinstanceid bigint NOT NULL,
      character integer,
      persistentid bigint,
      timestamp timestamp,
      CONSTRAINT talentlog_pkey PRIMARY KEY (id),
      CONSTRAINT talentlog_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT talentlog_talent_fkey FOREIGN KEY (talent) REFERENCES talent (id),
      CONSTRAINT talentlog_character_fkey FOREIGN KEY (character) REFERENCES character (id)
    );
    ALTER TABLE talentlog OWNER TO dbadmin;
    GRANT SELECT ON TABLE talentlog TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE talentlog TO rw;

    CREATE INDEX idx_talentlog_player ON talentlog (player);
    CREATE INDEX idx_talentlog_timestamp ON talentlog (timestamp);

    INSERT INTO talentlog (operation, player, talent, talentinstanceid, timestamp)
    SELECT 'gm_add', player, talent, 0, operationdate 
    FROM gm_addtalent;

    INSERT INTO talentlog (operation, player, talent, talentinstanceid, timestamp)
    SELECT 'gm_delete', player, talent, 0, operationdate 
    FROM gm_deletetalent;

    CREATE OR REPLACE FUNCTION talentlog_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION talentlog_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_talentlog_partition BEFORE INSERT ON talentlog 
      FOR EACH ROW EXECUTE PROCEDURE talentlog_insert_trigger();

    DROP TABLE talentroll CASCADE;

    select increment_version_to(75) into ver;
  end if;

  if ver = 75
  then

    ALTER TABLE claim ADD COLUMN muid varchar;

    select increment_version_to(76) into ver;
  end if;

  if ver = 76
  then

    CREATE SEQUENCE gm_operation_id_sequence;
    ALTER TABLE gm_operation_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE gm_operation_id_sequence TO ro;
    GRANT ALL ON TABLE gm_operation_id_sequence TO rw;

    CREATE TABLE gm_operation
    (
      id integer NOT NULL DEFAULT nextval('gm_operation_id_sequence'::regclass),
      type varchar NOT NULL,
      player bigint NOT NULL,
      data varchar,
      gmlogin varchar NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT gm_operation_pkey PRIMARY KEY (id),
      CONSTRAINT gm_operation_player_fkey FOREIGN KEY (player) REFERENCES player (id)
    );
    ALTER TABLE gm_operation OWNER TO dbadmin;
    GRANT SELECT ON TABLE gm_operation TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE gm_operation TO rw;

    INSERT INTO gm_operation (type, player, data, gmlogin, timestamp)
    SELECT 'TalentAdd', player, talent::varchar, gmlogin, operationdate
    FROM gm_addtalent;

    INSERT INTO gm_operation (type, player, data, gmlogin, timestamp)
    SELECT 'TalentDelete', player, talent::varchar, gmlogin, operationdate
    FROM gm_deletetalent;

    INSERT INTO gm_operation (type, player, data, gmlogin, timestamp)
    SELECT 'HeroLock', player, character::varchar, gmlogin, operationdate
    FROM gm_lockcharacter;

    INSERT INTO gm_operation (type, player, data, gmlogin, timestamp)
    SELECT 'HeroUnlock', player, character::varchar, gmlogin, operationdate
    FROM gm_unlockcharacter;

    INSERT INTO gm_operation (type, player, data, gmlogin, timestamp)
    SELECT 'PlayerEdit', player, field||': old='''||oldvalue||''', new='''||newvalue||'''', gmlogin, operationdate
    FROM gm_editplayer;

    DROP TABLE gm_addtalent;
    DROP TABLE gm_deletetalent;
    DROP TABLE gm_lockcharacter;
    DROP TABLE gm_unlockcharacter;
    DROP TABLE gm_editplayer;

    DROP TABLE chat;

    select increment_version_to(77) into ver;
  end if;

  if ver = 77
  then

    ALTER TABLE gamesession ADD COLUMN serveraddress varchar;
    ALTER TABLE gamesession ADD COLUMN cluster varchar;

    select increment_version_to(78) into ver;
  end if;

  if ver = 78
  then

    ALTER TABLE talentlog ADD COLUMN data varchar;

    select increment_version_to(79) into ver;
  end if;

  if ver = 79
  then

    CREATE SEQUENCE dynamicquestchange_id_sequence;
    ALTER TABLE dynamicquestchange_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE dynamicquestchange_id_sequence TO ro;
    GRANT ALL ON TABLE dynamicquestchange_id_sequence TO rw;

    CREATE TABLE dynamicquestchange
    (
      id integer NOT NULL DEFAULT nextval('dynamicquestchange_id_sequence'::regclass),
      player bigint NOT NULL,
      questindex integer NOT NULL,
      questname varchar NOT NULL,
      changetype integer NOT NULL,
      "timestamp" timestamp NOT NULL,
      CONSTRAINT dynamicquestchange_pkey PRIMARY KEY (id),
      CONSTRAINT dynamicquestchange_player_fkey FOREIGN KEY (player) REFERENCES player (id)
    );
    ALTER TABLE dynamicquestchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE dynamicquestchange TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE dynamicquestchange TO rw;

    CREATE OR REPLACE FUNCTION dynamicquestchange_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION dynamicquestchange_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_dynamicquestchange_partition BEFORE INSERT ON dynamicquestchange 
      FOR EACH ROW EXECUTE PROCEDURE dynamicquestchange_insert_trigger();

    select increment_version_to(80) into ver;
  end if;

  if ver = 80
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
    GRANT SELECT, UPDATE, INSERT ON TABLE guildshopitem TO rw;

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
    GRANT SELECT, UPDATE, INSERT ON TABLE guildbuff TO rw;

    ALTER TABLE sessiontoplayer ADD COLUMN guild bigint;
    ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id);

    ALTER TABLE guild ADD COLUMN memberscount integer NOT NULL DEFAULT (0);
    ALTER TABLE guild ALTER COLUMN memberscount DROP DEFAULT;
    ALTER TABLE guild DROP COLUMN faction;
    ALTER TABLE guild ALTER COLUMN creator DROP NOT NULL;


    CREATE SEQUENCE guildshopbuy_id_sequence;
    ALTER TABLE guildshopbuy_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE guildshopbuy_id_sequence TO ro;
    GRANT ALL ON TABLE guildshopbuy_id_sequence TO rw;

    CREATE TABLE guildshopbuy
    (
      id bigint NOT NULL DEFAULT nextval('guildshopbuy_id_sequence'::regclass),
      player bigint NOT NULL,
      guild bigint NOT NULL,
      hassuzerain boolean NOT NULL,
      guildshopitem integer NOT NULL,
      shoplevel integer NOT NULL,
      guildpointsprice integer NOT NULL,
      playerpointsprice integer NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT guildshopbuy_pkey PRIMARY KEY (id),
      CONSTRAINT guildshopbuy_player_fkey FOREIGN KEY (player) REFERENCES player (id),
      CONSTRAINT guildshopbuy_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guildshopbuy_guildshopitem_fkey FOREIGN KEY (guildshopitem) REFERENCES guildshopitem (id)
    );
    ALTER TABLE guildshopbuy OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildshopbuy TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE guildshopbuy TO rw;

    CREATE INDEX idx_guildshopbuy_player ON guildshopbuy (player);
    CREATE INDEX idx_guildshopbuy_timestamp ON guildshopbuy (timestamp);

    CREATE OR REPLACE FUNCTION guildshopbuy_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION guildshopbuy_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_guildshopbuy_partition BEFORE INSERT ON guildshopbuy 
      FOR EACH ROW EXECUTE PROCEDURE guildshopbuy_insert_trigger();


    CREATE SEQUENCE guildsiege_analysisid_sequence;
    ALTER TABLE guildsiege_analysisid_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE guildsiege_analysisid_sequence TO ro;
    GRANT ALL ON TABLE guildsiege_analysisid_sequence TO rw;

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
      analysisid bigint NOT NULL DEFAULT nextval('guildsiege_analysisid_sequence'::regclass),
      CONSTRAINT guildsiege_pkey PRIMARY KEY (id),
      CONSTRAINT guildsiege_guild1_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guildsiege_guild2_fkey FOREIGN KEY (targetguild) REFERENCES guild (id),
      CONSTRAINT guildsiege_guild3_fkey FOREIGN KEY (targetsuzerainguild) REFERENCES guild (id),
      CONSTRAINT guildsiege_guild4_fkey FOREIGN KEY (winner) REFERENCES guild (id)
    );
    ALTER TABLE guildsiege OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildsiege TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE guildsiege TO rw;

    CREATE INDEX idx_guildsiege_guild ON guildsiege (guild);
    CREATE INDEX idx_guildsiege_timestamp ON guildsiege (starttime);
    CREATE INDEX idx_guildsiege_analysisid ON guildsiege (analysisid);


    CREATE SEQUENCE guildsiegeparticipant_id_sequence;
    ALTER TABLE guildsiegeparticipant_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE guildsiegeparticipant_id_sequence TO ro;
    GRANT ALL ON TABLE guildsiegeparticipant_id_sequence TO rw;

    CREATE TABLE guildsiegeparticipant
    (
      id bigint NOT NULL DEFAULT nextval('guildsiegeparticipant_id_sequence'::regclass),
      guildsiege bigint NOT NULL,
      guild bigint NOT NULL,
      rating integer NOT NULL,
      siegepoints integer NOT NULL,
      guildpointsprice integer NOT NULL,
      starttime timestamp NOT NULL,
      endtime timestamp NOT NULL,
      CONSTRAINT guildsiegeparticipant_pkey PRIMARY KEY (id),
      CONSTRAINT guildsiegeparticipant_siege_fkey FOREIGN KEY (guildsiege) REFERENCES guildsiege (id),
      CONSTRAINT guildsiegeparticipant_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id)
    );
    ALTER TABLE guildsiegeparticipant OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildsiegeparticipant TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE guildsiegeparticipant TO rw;

    CREATE INDEX idx_guildsiegeparticipant_siege ON guildsiegeparticipant (guildsiege);
    CREATE INDEX idx_guildsiegeparticipant_guild ON guildsiegeparticipant (guild);
    CREATE INDEX idx_guildsiegeparticipant_timestamp ON guildsiegeparticipant (starttime);

    CREATE OR REPLACE FUNCTION guildsiegeparticipant_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION guildsiegeparticipant_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_guildsiegeparticipant_partition BEFORE INSERT ON guildsiegeparticipant 
      FOR EACH ROW EXECUTE PROCEDURE guildsiegeparticipant_insert_trigger();


    CREATE SEQUENCE guilddailystats_id_sequence;
    ALTER TABLE guilddailystats_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE guilddailystats_id_sequence TO ro;
    GRANT ALL ON TABLE guilddailystats_id_sequence TO rw;

    CREATE TABLE guilddailystats
    (
      id bigint NOT NULL DEFAULT nextval('guilddailystats_id_sequence'::regclass),
      guild bigint NOT NULL,
      rating integer NOT NULL,
      guildpoints integer NOT NULL,
      guildpointstoday integer NOT NULL,
      rank integer NOT NULL,
      vassalscount integer NOT NULL,
      vassalspoints integer NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT guilddailystats_pkey PRIMARY KEY (id),
      CONSTRAINT guilddailystats_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id)
    );
    ALTER TABLE guilddailystats OWNER TO dbadmin;
    GRANT SELECT ON TABLE guilddailystats TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE guilddailystats TO rw;

    CREATE INDEX idx_guilddailystats_guild ON guilddailystats (guild);
    CREATE INDEX idx_guilddailystats_timestamp ON guilddailystats (timestamp);

    CREATE OR REPLACE FUNCTION guilddailystats_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION guilddailystats_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_guilddailystats_partition BEFORE INSERT ON guilddailystats 
      FOR EACH ROW EXECUTE PROCEDURE guilddailystats_insert_trigger();


    CREATE SEQUENCE guildinteraction_id_sequence;
    ALTER TABLE guildinteraction_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE guildinteraction_id_sequence TO ro;
    GRANT ALL ON TABLE guildinteraction_id_sequence TO rw;

    CREATE TABLE guildinteraction
    (
      id bigint NOT NULL DEFAULT nextval('guildinteraction_id_sequence'::regclass),
      guild bigint NOT NULL,
      targetguild bigint NOT NULL,
      type varchar NOT NULL,
      guildsiege bigint,
      waitingtime integer NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT guildinteraction_pkey PRIMARY KEY (id),
      CONSTRAINT guildinteraction_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guildinteraction_targetguild_fkey FOREIGN KEY (targetguild) REFERENCES guild (id),
      CONSTRAINT guildinteraction_siege_fkey FOREIGN KEY (guildsiege) REFERENCES guildsiege (id)
    );
    ALTER TABLE guildinteraction OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildinteraction TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE guildinteraction TO rw;


    CREATE INDEX idx_guildinteraction_guild ON guildinteraction (guild);
    CREATE INDEX idx_guildinteraction_targetguild ON guildinteraction (targetguild);
    CREATE INDEX idx_guildinteraction_timestamp ON guildinteraction (timestamp);

    CREATE OR REPLACE FUNCTION guildinteraction_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION guildinteraction_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_guildinteraction_partition BEFORE INSERT ON guildinteraction 
      FOR EACH ROW EXECUTE PROCEDURE guildinteraction_insert_trigger();

    select increment_version_to(81) into ver;
  end if;


  if ver = 81
  then

    CREATE SEQUENCE guildpointslog_id_sequence;
    ALTER TABLE guildpointslog_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE guildpointslog_id_sequence TO ro;
    GRANT ALL ON TABLE guildpointslog_id_sequence TO rw;

    CREATE TABLE guildpointslog
    (
      id bigint NOT NULL DEFAULT nextval('guildpointslog_id_sequence'::regclass),
      type varchar NOT NULL,
      guild bigint NOT NULL,
      player bigint,
      guildpointschange integer NOT NULL,
      playerpointschange integer NOT NULL,
      guildpointstotal integer NOT NULL,
      playerpointstotal integer NOT NULL,
      persistentid bigint,
      timestamp timestamp NOT NULL,
      CONSTRAINT guildpointslog_pkey PRIMARY KEY (id),
      CONSTRAINT guildpointslog_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
      CONSTRAINT guildpointslog_player_fkey FOREIGN KEY (player) REFERENCES player (id)
    );
    ALTER TABLE guildpointslog OWNER TO dbadmin;
    GRANT SELECT ON TABLE guildpointslog TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE guildpointslog TO rw;

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

    select increment_version_to(82) into ver;
  end if;

  if ver = 82
  then

    CREATE INDEX idx_gmuseroperation_player on gm_useroperation (player);
    CREATE INDEX idx_claim_toplayer on claim (toplayer);
    CREATE INDEX idx_claim_gmuseroperation on claim (gmuseroperation);

    FOR txt1 IN ( 
      SELECT c.relname
      FROM pg_inherits 
        JOIN pg_class AS c ON (inhrelid=c.oid)
        JOIN pg_class as p ON (inhparent=p.oid)
      WHERE p.relname = 'claim' )
    LOOP
      FOR tmprow IN
      ( SELECT c.relname as name, pg_get_indexdef(idx.indexrelid) as definition
        FROM pg_index idx JOIN pg_class c ON c.oid = idx.indexrelid
        WHERE idx.indrelid = 'claim'::regclass )
      LOOP
        txt2 = replace(tmprow.definition, 'INDEX '||tmprow.name, 'INDEX '||replace(tmprow.name, 'claim', txt1));
        txt2 = replace(txt2, 'ON claim', 'ON partitions.'||txt1);
        BEGIN
          EXECUTE txt2;
        EXCEPTION
          WHEN duplicate_table THEN
        END;
      END LOOP;
    END LOOP;

    select increment_version_to(83) into ver;
  end if;

  if ver = 83
  then
    alter table socialsession alter column id type bigint;
    alter table questchange alter column id type bigint;
    alter table dynamicquestchange alter column id type bigint;

    select increment_version_to(84) into ver;
  end if;

  if ver = 84
  then

    CREATE SEQUENCE afterparty_id_sequence;
    ALTER TABLE afterparty_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE afterparty_id_sequence TO ro;
    GRANT ALL ON TABLE afterparty_id_sequence TO rw;

    CREATE TABLE afterparty
    (
      id bigint NOT NULL DEFAULT nextval('afterparty_id_sequence'::regclass),
      persistentid bigint NOT NULL,
      mmstarted boolean NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT afterparty_pkey PRIMARY KEY (id)
    );
    ALTER TABLE afterparty OWNER TO dbadmin;
    GRANT SELECT ON TABLE afterparty TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE afterparty TO rw;

    CREATE SEQUENCE afterpartymember_id_sequence;
    ALTER TABLE afterpartymember_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE afterpartymember_id_sequence TO ro;
    GRANT ALL ON TABLE afterpartymember_id_sequence TO rw;

    CREATE TABLE afterpartymember
    (
      id bigint NOT NULL DEFAULT nextval('afterpartymember_id_sequence'::regclass),
      player bigint NOT NULL,
      afterparty bigint NOT NULL,
      persistentid bigint,
      kicked boolean NOT NULL,
      leaved boolean NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT afterpartymember_pkey PRIMARY KEY (id),
      CONSTRAINT afterpartymember_afterparty_fkey FOREIGN KEY (afterparty) REFERENCES afterparty (id),
      CONSTRAINT afterpartymember_player_fkey FOREIGN KEY (player) REFERENCES player (id)
    );
    ALTER TABLE afterpartymember OWNER TO dbadmin;
    GRANT SELECT ON TABLE afterpartymember TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE afterpartymember TO rw;

    select increment_version_to(85) into ver;
  end if;


  if ver = 85
  then

    CREATE SEQUENCE leaverpointslog_id_sequence;
    ALTER TABLE leaverpointslog_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE leaverpointslog_id_sequence TO ro;
    GRANT ALL ON TABLE leaverpointslog_id_sequence TO rw;

    CREATE TABLE leaverpointslog
    (
      id bigint NOT NULL DEFAULT nextval('leaverpointslog_id_sequence'::regclass),
      player bigint NOT NULL,
      persistentid bigint NOT NULL,
      leaverpointschange integer NOT NULL,
      leaverpointstotal integer NOT NULL,
      isleaverchanged boolean NOT NULL,
      isleaver boolean NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT leaverpointslog_pkey PRIMARY KEY (id),
      CONSTRAINT leaverpointslog_player_fkey FOREIGN KEY (player) REFERENCES player (id)
    );
    ALTER TABLE leaverpointslog OWNER TO dbadmin;
    GRANT SELECT ON TABLE leaverpointslog TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE leaverpointslog TO rw;

    CREATE INDEX idx_leaverpointslog_player ON leaverpointslog (player);
    CREATE INDEX idx_leaverpointslog_timestamp ON leaverpointslog (timestamp);

    CREATE OR REPLACE FUNCTION leaverpointslog_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION leaverpointslog_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_leaverpointslog_partition BEFORE INSERT ON leaverpointslog 
      FOR EACH ROW EXECUTE PROCEDURE leaverpointslog_insert_trigger();

    select increment_version_to(86) into ver;
  end if;


  if ver = 86
  then

    ALTER TABLE player ADD COLUMN leavercount integer;
    ALTER TABLE player ADD COLUMN leavergmcount integer;

    ALTER TABLE gm_useroperation ADD COLUMN points integer;

    ALTER TABLE leaverpointslog ADD COLUMN type varchar;    
    ALTER TABLE leaverpointslog ADD COLUMN isbadbehaviour boolean;
    UPDATE leaverpointslog SET isbadbehaviour = false;
    ALTER TABLE leaverpointslog ALTER COLUMN isbadbehaviour SET NOT NULL;
    ALTER TABLE leaverpointslog ALTER COLUMN persistentid DROP NOT NULL;

    UPDATE player p
    SET leavercount = sq.c
    FROM (
      SELECT player, count(*) c
      FROM leaverpointslog
      WHERE isleaver 
        AND isleaverchanged
      GROUP BY player
    ) sq
    WHERE sq.player = p.id;

    select increment_version_to(87) into ver;
  end if;


  if ver = 87
  then

    ALTER TABLE runeroll ADD COLUMN source varchar DEFAULT 'SessionDrop';
    ALTER TABLE runeroll ALTER COLUMN source DROP DEFAULT;

    ALTER TABLE rune ADD COLUMN percent integer DEFAULT 0;
    ALTER TABLE rune ALTER COLUMN percent DROP DEFAULT;

    select increment_version_to(88) into ver;
  end if;
  
  if ver = 88
  then

    ALTER TABLE resourcelog ADD COLUMN redperlchange integer;    
    ALTER TABLE resourcelog ADD COLUMN redperltotal integer;

    select increment_version_to(89) into ver;
  end if;


  if ver = 89
  then

    IF NOT EXISTS (
      SELECT * FROM pg_attribute a JOIN pg_class p ON p.oid = attrelid
      WHERE attname = 'leaverpoints' AND relname = 'player')
    THEN
      ALTER TABLE player ADD COLUMN leaverpoints integer NOT NULL DEFAULT 0;
      ALTER TABLE player ALTER COLUMN leaverpoints DROP DEFAULT;
      ALTER TABLE player ADD COLUMN isleaver boolean NOT NULL DEFAULT false;
      ALTER TABLE player ALTER COLUMN isleaver DROP DEFAULT;
    END IF;

    select increment_version_to(90) into ver;
  end if;

  
  if ver = 90
  then
	CREATE SEQUENCE rerollshoplog_id_sequence;
	ALTER TABLE rerollshoplog_id_sequence OWNER TO dbadmin;
	GRANT SELECT, USAGE ON TABLE rerollshoplog_id_sequence TO ro;
	GRANT ALL ON TABLE rerollshoplog_id_sequence TO rw;

	CREATE TABLE rerollshoplog
	(
	  id bigint NOT NULL DEFAULT nextval('rerollshoplog_id_sequence'::regclass),
	  player bigint NOT NULL,
	  itemId int NOT NULL,
	  itemGroup int NOT NULL,
	  itemPrice bigint not null,
	  itemPriceType character varying,
	  rerollCount int,
	  slotType character varying,
	  timestamp timestamp not null,
      CONSTRAINT rerollshoplog_pkey PRIMARY KEY (id),
	  CONSTRAINT rerollshoplog_player_fkey FOREIGN KEY (player) REFERENCES player (id)
	);

	ALTER TABLE rerollshoplog OWNER TO dbadmin;
	GRANT SELECT ON TABLE rerollshoplog TO ro;
	GRANT SELECT, UPDATE, INSERT ON TABLE rerollshoplog TO rw;

	CREATE INDEX idx_rerollshoplog_player ON rerollshoplog (player);
	CREATE INDEX idx_rerollshoplog_timestamp ON rerollshoplog (timestamp);

	CREATE OR REPLACE FUNCTION rerollshoplog_insert_trigger()
	RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
	ALTER FUNCTION rerollshoplog_insert_trigger() OWNER TO dbadmin;

	CREATE TRIGGER tr_rerollshoplog_partition BEFORE INSERT ON rerollshoplog 
	  FOR EACH ROW EXECUTE PROCEDURE rerollshoplog_insert_trigger();
	  
    select increment_version_to(91) into ver;
  end if;
  
  if ver = 91
  then
	ALTER TABLE dynamicquestchange ADD COLUMN alternativeline boolean NOT NULL DEFAULT false;
    ALTER TABLE dynamicquestchange ALTER COLUMN alternativeline DROP DEFAULT;

    select increment_version_to(92) into ver;
  end if;
  
  if ver = 92
  then

    CREATE SEQUENCE tournamentquestchange_id_sequence;
    ALTER TABLE tournamentquestchange_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE tournamentquestchange_id_sequence TO ro;
    GRANT ALL ON TABLE tournamentquestchange_id_sequence TO rw;

    CREATE TABLE tournamentquestchange
    (
      id bigint NOT NULL DEFAULT nextval('tournamentquestchange_id_sequence'::regclass),
      player bigint NOT NULL,
      questindex integer NOT NULL,
      questname varchar NOT NULL,
      completetype integer NOT NULL,
      "timestamp" timestamp NOT NULL,
	  alternativeline boolean NOT NULL,
      CONSTRAINT tournamentquestchange_pkey PRIMARY KEY (id),
      CONSTRAINT tournamentquestchange_player_fkey FOREIGN KEY (player) REFERENCES player (id)
    );
    ALTER TABLE tournamentquestchange OWNER TO dbadmin;
    GRANT SELECT ON TABLE tournamentquestchange TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE tournamentquestchange TO rw;

    CREATE OR REPLACE FUNCTION tournamentquestchange_insert_trigger()
    RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
    ALTER FUNCTION tournamentquestchange_insert_trigger() OWNER TO dbadmin;

    CREATE TRIGGER tr_tournamentquestchange_partition BEFORE INSERT ON tournamentquestchange 
      FOR EACH ROW EXECUTE PROCEDURE tournamentquestchange_insert_trigger();

    select increment_version_to(93) into ver;
  end if;

  if ver = 93
  then
      ALTER TABLE resourcelog ADD COLUMN shardchange integer;    
      ALTER TABLE resourcelog ADD COLUMN shardtotal integer;

      select increment_version_to(94) into ver;
  end if;

  if ver = 94
  then
      ALTER TABLE resourcelog ADD COLUMN currencychange character varying;    
      ALTER TABLE resourcelog ADD COLUMN currencytotal character varying;

      select increment_version_to(95) into ver;
  end if;

  if ver = 95
  then
      ALTER TABLE resourcelog ADD COLUMN currencychangevalue integer;    
      ALTER TABLE resourcelog ADD COLUMN currencytotalvalue integer;

      select increment_version_to(96) into ver;
  end if;

  if ver = 96
  then 
      CREATE SEQUENCE runeheroapply_id_sequence;
      ALTER TABLE runeheroapply_id_sequence OWNER TO dbadmin;
      GRANT SELECT, USAGE ON TABLE runeheroapply_id_sequence TO ro;
      GRANT ALL ON TABLE runeheroapply_id_sequence TO rw;

      CREATE TABLE runeheroapply
      (
        id bigint NOT NULL DEFAULT nextval('runeheroapply_id_sequence'::regclass),
        player bigint NOT NULL,
        rune integer NOT NULL,
        hero varchar NOT NULL DEFAULT 'unknownhero',
        timestamp timestamp NOT NULL,
        CONSTRAINT runeheroapply_pkey PRIMARY KEY (id),
        CONSTRAINT runeheroapply_player_fkey FOREIGN KEY (player) REFERENCES player (id),
        CONSTRAINT runeheroapply_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id)
      );
      ALTER TABLE runeheroapply OWNER TO dbadmin;
      GRANT SELECT ON TABLE runeheroapply TO ro;
      GRANT SELECT, UPDATE, INSERT ON TABLE runeheroapply TO rw;

      ALTER TABLE runeroll ADD COLUMN runescountold integer;
      ALTER TABLE runeroll ADD COLUMN runescountnew integer;

      select increment_version_to(97) into ver;
  end if;

  if ver = 97
  then 
      CREATE SEQUENCE gwevents_id_sequence;
      ALTER TABLE gwevents_id_sequence OWNER TO dbadmin;
      GRANT SELECT, USAGE ON TABLE gwevents_id_sequence TO ro;
      GRANT ALL ON TABLE gwevents_id_sequence TO rw;

      CREATE TABLE gwevents
      (
        id bigint NOT NULL DEFAULT nextval('gwevents_id_sequence'::regclass),
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
      GRANT SELECT, UPDATE, INSERT ON TABLE gwevents TO rw;

      select increment_version_to(98) into ver;
  end if;

  if ver = 98
  then 
      CREATE SEQUENCE gweventslog_id_sequence;
      ALTER TABLE gweventslog_id_sequence OWNER TO dbadmin;
      GRANT SELECT, USAGE ON TABLE gweventslog_id_sequence TO ro;
      GRANT ALL ON TABLE gweventslog_id_sequence TO rw;

      CREATE TABLE gweventslog
      (
        id bigint NOT NULL DEFAULT nextval('gweventslog_id_sequence'::regclass),
        gweventmid varchar NOT NULL,
        guildid integer NOT NULL,
        lastpoints integer NOT NULL,
        currentpoints integer NOT NULL,
        timestamp timestamp NOT NULL,
        CONSTRAINT gweventslog_pkey PRIMARY KEY (id)
      );
      ALTER TABLE gweventslog OWNER TO dbadmin;
      GRANT SELECT ON TABLE gweventslog TO ro;
      GRANT SELECT, UPDATE, INSERT ON TABLE gweventslog TO rw;

      select increment_version_to(99) into ver;
  end if;

  if ver = 99
  then
    ALTER TABLE gweventslog ALTER COLUMN guildid TYPE bigint using guildid::integer;

    select increment_version_to(100) into ver;
  end if;

  if ver = 100
  then
    ALTER TABLE gweventslog ADD COLUMN auid integer;

    select increment_version_to(101) into ver;
  end if;


  if ver = 101
  then
    
    CREATE SEQUENCE questeventsstageslog_id_sequence;
    ALTER TABLE questeventsstageslog_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE questeventsstageslog_id_sequence TO ro;
    GRANT ALL ON TABLE questeventsstageslog_id_sequence TO rw;

    CREATE TABLE questeventsstageslog
    (
      id bigint NOT NULL DEFAULT nextval('questeventsstageslog_id_sequence'::regclass),
      tostagechange integer NOT NULL,
      auid integer NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT questeventsstageslog_pkey PRIMARY KEY (id)
    );
    ALTER TABLE questeventsstageslog OWNER TO dbadmin;
    GRANT SELECT ON TABLE questeventsstageslog TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE questeventsstageslog TO rw;

    CREATE SEQUENCE questeventsstepslog_id_sequence;
    ALTER TABLE questeventsstepslog_id_sequence OWNER TO dbadmin;
    GRANT SELECT, USAGE ON TABLE questeventsstepslog_id_sequence TO ro;
    GRANT ALL ON TABLE questeventsstepslog_id_sequence TO rw;

    CREATE TABLE questeventsstepslog
    (
      id bigint NOT NULL DEFAULT nextval('questeventsstepslog_id_sequence'::regclass),
      tostepchange integer NOT NULL,
      stage integer NOT NULL,
      auid integer NOT NULL,
      timestamp timestamp NOT NULL,
      CONSTRAINT questeventsstepslog_pkey PRIMARY KEY (id)
    );
    ALTER TABLE questeventsstepslog OWNER TO dbadmin;
    GRANT SELECT ON TABLE questeventsstepslog TO ro;
    GRANT SELECT, UPDATE, INSERT ON TABLE questeventsstepslog TO rw;

    select increment_version_to(102) into ver;
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

select incremental();

select create_partition('gamesession', 'starttime');
select create_partition('sessiontoplayer', 'starttime');
select create_partition('mmakingsession', 'timestamp');
select create_partition('mmakingplayer', 'timestamp');
select create_partition('socialsession', 'starttime');
select create_partition('resourcelog', 'timestamp');
select create_partition('claim', 'timestamp');
select create_partition('questchange', 'timestamp');
select create_partition('dynamicquestchange', 'timestamp');
select create_partition('talentlog', 'timestamp');
select create_partition('movetobath', 'timestamp');
select create_partition('characterunlock', 'timestamp');
select create_partition('guildshopbuy', 'timestamp');
select create_partition('guildsiegeparticipant', 'starttime');
select create_partition('guilddailystats', 'timestamp');
select create_partition('guildinteraction', 'timestamp');
select create_partition('leaverpointslog', 'timestamp');
select create_partition('rerollshoplog', 'timestamp');
select create_partition('tournamentquestchange', 'timestamp');