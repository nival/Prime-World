-----------------------------------------------------------------------------------------
DO $$ 
BEGIN
  IF NOT EXISTS (SELECT 1 FROM pg_language WHERE lanname = 'plpgsql') THEN
    CREATE LANGUAGE plpgsql;
  END IF;
END $$;

-----------------------------------------------------------------------------------------
CREATE OR REPLACE FUNCTION update_timestamp()
  RETURNS TRIGGER as
$$
BEGIN
  NEW.lastmodified = current_timestamp at time zone 'utc';
  RETURN NEW;
END;
$$
LANGUAGE PLPGSQL;
ALTER FUNCTION update_timestamp() OWNER TO dbadmin;
GRANT EXECUTE ON FUNCTION update_timestamp() TO rw;

-----------------------------------------------------------------------------------------
CREATE TABLE player
(
  id bigint NOT NULL,
  nickname character varying(255),
  nival boolean not null default false,
  sex integer not null default 0,
  faction integer not null default -1,
  guild bigint,
  reliability integer not null,
  locale character varying NOT NULL,
  leavercount integer,
  leavergmcount integer,
  leaverpoints integer NOT NULL,
  isleaver bool NOT NULL,
  lastmodified timestamp NOT NULL,
  CONSTRAINT player_pkey PRIMARY KEY (id)
--CONSTRAINT player_guild_fkey ... look for definition below
);
ALTER TABLE player OWNER TO dbadmin;
GRANT SELECT ON TABLE player TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE player TO rw;

CREATE TRIGGER update_player_lastmodified BEFORE INSERT OR UPDATE 
  ON player FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

CREATE INDEX idx_player_lastmodified ON player (lastmodified);

-----------------------------------------------------------------------------------------
CREATE TABLE "character"
(
  id integer NOT NULL,
  "name" character varying(255),
  dbid character varying(1024),
  description character varying(1023),
  gender integer,
  deleted boolean not null default false,
  CONSTRAINT character_pkey PRIMARY KEY (id)
);
ALTER TABLE "character" OWNER TO dbadmin;
GRANT SELECT ON TABLE "character" TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE "character" TO rw;

-----------------------------------------------------------------------------------------
CREATE SEQUENCE playercharacter_id_sequence;
ALTER TABLE playercharacter_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE playercharacter_id_sequence TO ro;
GRANT ALL ON TABLE playercharacter_id_sequence TO rw;

CREATE TABLE playercharacter
(
  id integer NOT NULL DEFAULT nextval('playercharacter_id_sequence'::regclass),
  "character" integer NOT NULL,
  player bigint NOT NULL,
  locked boolean NOT NULL default false,
  unlockdate timestamp without time zone,
  lastmodified timestamp NOT NULL,
  CONSTRAINT playercharacter_pkey PRIMARY KEY (id),
  CONSTRAINT playercharacter_unique_player_character UNIQUE (player, character),
  CONSTRAINT fke03456c98c205aa FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT fke03456c9f7af6777 FOREIGN KEY ("character") REFERENCES "character" (id)
);
ALTER TABLE playercharacter OWNER TO dbadmin;
GRANT SELECT ON TABLE playercharacter TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE playercharacter TO rw;

CREATE TRIGGER update_playercharacter_lastmodified BEFORE INSERT OR UPDATE 
  ON playercharacter FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

CREATE INDEX idx_playercharacter_lastmodified ON playercharacter (lastmodified);

-----------------------------------------------------------------------------------------
CREATE SEQUENCE mmakingsession_id_sequence;
ALTER TABLE mmakingsession_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE mmakingsession_id_sequence TO ro;
GRANT ALL ON TABLE mmakingsession_id_sequence TO rw;

create table mmakingsession
(
  id bigint not null not null DEFAULT nextval('mmakingsession_id_sequence'::regclass),
  persistentid bigint not null,
  status integer not null,
  manoeuvresfaction integer not null,
  basket integer not null,
  map varchar not null,
  "timestamp" timestamp without time zone,
  CONSTRAINT mmakingsession_pkey PRIMARY KEY (id),
  CONSTRAINT mmakingsession_unique_persistentid UNIQUE (persistentid)
);
ALTER TABLE mmakingsession OWNER TO dbadmin;
GRANT SELECT ON TABLE mmakingsession TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE mmakingsession TO rw;

CREATE OR REPLACE FUNCTION mmakingsession_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION mmakingsession_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_mmakingsession_partition BEFORE INSERT ON mmakingsession 
  FOR EACH ROW EXECUTE PROCEDURE mmakingsession_insert_trigger();


-----------------------------------------------------------------------------------------
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
  playerrating integer not null,
  force real not null,
  party integer not null,
  waitinterval real not null,
  losestreak integer not null,
  famelevel integer not null,
  basket integer not null,
  lobbyreaction integer not null,
  lobbyreactiontime real,
  "timestamp" timestamp not null,
  CONSTRAINT mmakingplayer_pkey PRIMARY KEY (id),
  CONSTRAINT mmakingplayer_mmakingsession_fkey FOREIGN KEY (mmakingsession) REFERENCES mmakingsession (id),
  CONSTRAINT mmakingplayer_playercharacter_fkey FOREIGN KEY (playercharacter) REFERENCES playercharacter (id)
);
ALTER TABLE mmakingplayer OWNER TO dbadmin;
GRANT SELECT ON TABLE mmakingplayer TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE mmakingplayer TO rw;

CREATE OR REPLACE FUNCTION mmakingplayer_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION mmakingplayer_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_mmakingplayer_partition BEFORE INSERT ON mmakingplayer 
  FOR EACH ROW EXECUTE PROCEDURE mmakingplayer_insert_trigger();


-----------------------------------------------------------------------------------------
CREATE SEQUENCE resourcelog_id_sequence;
ALTER TABLE resourcelog_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE resourcelog_id_sequence TO ro;
GRANT ALL ON TABLE resourcelog_id_sequence TO rw;

CREATE TABLE resourcelog
(
  id bigint NOT NULL DEFAULT nextval('resourcelog_id_sequence'::regclass),
  source character varying NOT NULL,
  buildingname character varying,
  persistentid bigint,
  gain boolean NOT NULL,
  player bigint NOT NULL,
  goldchange integer NOT NULL DEFAULT 0,
  silverchange integer NOT NULL DEFAULT 0,
  perlchange integer NOT NULL DEFAULT 0,
  redperlchange integer NOT NULL DEFAULT 0,
  populationchange integer NOT NULL DEFAULT 0,
  resource1change integer NOT NULL DEFAULT 0,
  resource2change integer NOT NULL DEFAULT 0,
  resource3change integer NOT NULL DEFAULT 0,
  shardchange integer NOT NULL DEFAULT 0,
  currencychange character varying NOT NULL,
  currencychangevalue integer NOT NULL DEFAULT 0,
  goldtotal integer NOT NULL DEFAULT 0,
  silvertotal integer NOT NULL DEFAULT 0,
  perltotal integer NOT NULL DEFAULT 0,
  redperltotal integer NOT NULL DEFAULT 0,
  populationtotal integer NOT NULL DEFAULT 0,
  resource1total integer NOT NULL DEFAULT 0,
  resource2total integer NOT NULL DEFAULT 0,
  resource3total integer NOT NULL DEFAULT 0,
  shardtotal integer NOT NULL DEFAULT 0,
  currencytotal character varying NOT NULL,
  currencytotalvalue integer NOT NULL DEFAULT 0,
  "timestamp" timestamp without time zone,
  CONSTRAINT resourcelog_pkey PRIMARY KEY (id),
  CONSTRAINT resourcelog_player_fkey FOREIGN KEY (player) REFERENCES player (id)
);
ALTER TABLE resourcelog OWNER TO dbadmin;
GRANT SELECT ON TABLE resourcelog TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE resourcelog TO rw;

CREATE INDEX idx_resourcelog_timestamp ON resourcelog (timestamp);
CREATE INDEX idx_resourcelog_player ON resourcelog (player);

CREATE OR REPLACE FUNCTION resourcelog_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION resourcelog_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_resourcelog_partition BEFORE INSERT ON resourcelog 
  FOR EACH ROW EXECUTE PROCEDURE resourcelog_insert_trigger();


-----------------------------------------------------------------------------------------
CREATE SEQUENCE gamesession_id_sequence;
ALTER TABLE gamesession_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE gamesession_id_sequence TO ro;
GRANT ALL ON TABLE gamesession_id_sequence TO rw;

CREATE TABLE gamesession
(
  id integer NOT NULL DEFAULT nextval('gamesession_id_sequence'::regclass),
  persistentid bigint NOT NULL,
  server character varying(255) NOT NULL,
  serveraddress varchar,
  cluster varchar,
  map character varying(255) NOT NULL,
  starttime timestamp without time zone NOT NULL,
  endtime timestamp without time zone,
  sidewon integer,
  surrendervote integer NOT NULL,
  sessionresult integer NOT NULL,
  sessiontype integer NOT NULL DEFAULT 0,
  CONSTRAINT gamesession_pkey PRIMARY KEY (id)
);
ALTER TABLE gamesession OWNER TO dbadmin;
GRANT SELECT ON TABLE gamesession TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE gamesession TO rw;

CREATE INDEX idx_gamesession_persistentid ON gamesession (persistentid);

CREATE OR REPLACE FUNCTION gamesession_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION gamesession_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_gamesession_partition BEFORE INSERT ON gamesession 
  FOR EACH ROW EXECUTE PROCEDURE gamesession_insert_trigger();


-----------------------------------------------------------------------------------------
CREATE SEQUENCE sessiontoplayer_id_sequence;
ALTER TABLE sessiontoplayer_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE sessiontoplayer_id_sequence TO ro;
GRANT ALL ON TABLE sessiontoplayer_id_sequence TO rw;

CREATE TABLE sessiontoplayer
(
  id integer NOT NULL DEFAULT nextval('sessiontoplayer_id_sequence'::regclass),
  playercharacter integer NOT NULL,
  gamesession integer NOT NULL,
  finallevel integer,
  maxlevelreached integer,
  leaver boolean,
  faction integer,
  score integer,
  kills integer,
  deaths integer,
  assists integer,
  enemycreepskilled integer,
  neutralcreepskilled integer,
  relayaddress varchar,
  starttime timestamp,
  guild bigint,
  CONSTRAINT sessiontoplayer_pkey PRIMARY KEY (id),
  CONSTRAINT sessiontoplayer_playercharacter_fkey FOREIGN KEY (playercharacter) REFERENCES playercharacter (id),
  CONSTRAINT sessiontoplayer_gamesession_fkey FOREIGN KEY (gamesession) REFERENCES gamesession (id)
  --CONSTRAINT sessiontoplayer_guild_fkey ...
);
ALTER TABLE sessiontoplayer OWNER TO dbadmin;
GRANT SELECT ON TABLE sessiontoplayer TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE sessiontoplayer TO rw;

CREATE INDEX idx_sessiontoplayer_playercharacter ON sessiontoplayer (playercharacter);
CREATE INDEX idx_sessiontoplayer_gamesession ON sessiontoplayer (gamesession);

CREATE OR REPLACE FUNCTION sessiontoplayer_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION sessiontoplayer_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_sessiontoplayer_partition BEFORE INSERT ON sessiontoplayer 
  FOR EACH ROW EXECUTE PROCEDURE sessiontoplayer_insert_trigger();


-----------------------------------------------------------------------------------------
CREATE SEQUENCE socialsession_id_sequence;
ALTER TABLE socialsession_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE socialsession_id_sequence TO ro;
GRANT ALL ON TABLE socialsession_id_sequence TO rw;

CREATE TABLE socialsession
(
  id bigint NOT NULL DEFAULT nextval('socialsession_id_sequence'::regclass),
  player bigint NOT NULL,
  playerip character varying,
  server character varying,
  "cluster" character varying,
  starttime timestamp without time zone NOT NULL,
  endtime timestamp without time zone,
  CONSTRAINT socialsession_pkey PRIMARY KEY (id),
  CONSTRAINT socialsession_player_fkey FOREIGN KEY (player) REFERENCES player (id)
);
ALTER TABLE socialsession OWNER TO dbadmin;
GRANT SELECT ON TABLE socialsession TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE socialsession TO rw;

CREATE INDEX idx_socialsession_player ON socialsession (player);

CREATE OR REPLACE FUNCTION socialsession_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION socialsession_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_socialsession_partition BEFORE INSERT ON socialsession 
  FOR EACH ROW EXECUTE PROCEDURE socialsession_insert_trigger();

-----------------------------------------------------------------------------------------
CREATE TABLE guild 
(
  id bigint NOT NULL,
  shortname varchar,
  fullname varchar,
  creator bigint,
  creationdate timestamp NOT NULL,
  disbandingdate timestamp,
  resourcelog bigint,
  memberscount integer NOT NULL,
  lastmodified timestamp NOT NULL,
  CONSTRAINT guild_pkey PRIMARY KEY (id),
  CONSTRAINT guild_player_fkey FOREIGN KEY (creator) REFERENCES player (id)
);
ALTER TABLE guild OWNER TO dbadmin;
GRANT SELECT ON TABLE guild TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE guild TO rw;

CREATE TRIGGER update_guild_lastmodified BEFORE INSERT OR UPDATE
  ON guild FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

CREATE INDEX idx_guild_lastmodified ON guild (lastmodified);

-- CONSTRAINT for player
ALTER TABLE player ADD CONSTRAINT player_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id);

-- CONSTRAINT for sessiontoplayer
ALTER TABLE sessiontoplayer ADD CONSTRAINT sessiontoplayer_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id);

-----------------------------------------------------------------------------------------
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

CREATE INDEX idx_guildmembership_lastmodified ON guildmembership (lastmodified);

CREATE TRIGGER update_guildmembership_lastmodified BEFORE INSERT OR UPDATE
  ON guildmembership FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

-----------------------------------------------------------------------------------------
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
  CONSTRAINT factionchange_player_fkey FOREIGN KEY (player) REFERENCES player (id)
);
ALTER TABLE factionchange OWNER TO dbadmin;
GRANT SELECT ON TABLE factionchange TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE factionchange TO rw;

-----------------------------------------------------------------------------------------
CREATE TABLE impulsivebuff
(
  id integer NOT NULL,
  "name" character varying(1023),
  dbid character varying(1024),
  deleted boolean not null default false,
  CONSTRAINT impulsivebuff_pkey PRIMARY KEY (id)
);
ALTER TABLE impulsivebuff OWNER TO dbadmin;
GRANT SELECT ON TABLE impulsivebuff TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE impulsivebuff TO rw;

-- Table: mgboost

CREATE TABLE mgboost
(
  id integer NOT NULL,
  "name" character varying(256),
  deleted boolean not null default false,
  CONSTRAINT mgboost_pkey PRIMARY KEY (id)
);
ALTER TABLE mgboost OWNER TO dbadmin;
GRANT SELECT ON TABLE mgboost TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE mgboost TO rw;

-- Table: unittype

CREATE TABLE unittype
(
  id integer NOT NULL,
  "name" character varying(256),
  deleted boolean not null default false,
  CONSTRAINT unittype_pkey PRIMARY KEY (id)
);
ALTER TABLE unittype OWNER TO dbadmin;
GRANT SELECT ON TABLE unittype TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE unittype TO rw;

-- Table: abilitytype

CREATE TABLE abilitytype
(
  id integer NOT NULL,
  "name" character varying(256),
  deleted boolean not null default false,
  CONSTRAINT abilitytype_pkey PRIMARY KEY (id)
);
ALTER TABLE abilitytype OWNER TO dbadmin;
GRANT SELECT ON TABLE abilitytype TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE abilitytype TO rw;

-- Table: talent

CREATE TABLE talent
(
  id integer NOT NULL,
  talentid character varying(1024),
  "name" character varying(255),
  dbid character varying(1024),
  description character varying(1023),
  abilitytype integer,
  cooldown real,
  tour integer,
  rarity integer,
  budget real,
  deleted boolean not null default false,
  CONSTRAINT talent_pkey PRIMARY KEY (id),
  CONSTRAINT talent_abilitytype_fkey FOREIGN KEY (abilitytype)
      REFERENCES abilitytype (id) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
);
ALTER TABLE talent OWNER TO dbadmin;
GRANT SELECT ON TABLE talent TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE talent TO rw;

-- Table: Creature

CREATE TABLE creature
(
  id integer NOT NULL,
  "name" character varying(255),
  deleted boolean not null default false,
  CONSTRAINT creature_pkey PRIMARY KEY (id)
);
ALTER TABLE creature OWNER TO dbadmin;
GRANT SELECT ON TABLE creature TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE creature TO rw;

-- Table: Building

CREATE TABLE building
(
  id integer NOT NULL,
  "name" character varying(255),
  description character varying(1023),
  deleted boolean not null default false,
  CONSTRAINT building_pkey PRIMARY KEY (id)
);
ALTER TABLE building OWNER TO dbadmin;
GRANT SELECT ON TABLE building TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE building TO rw;

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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
GRANT SELECT, UPDATE, INSERT ON TABLE achievement TO rw;

-- Table: Consumable

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
GRANT SELECT, UPDATE, INSERT ON TABLE consumable TO rw;

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE SEQUENCE questchange_id_sequence;
ALTER TABLE questchange_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE questchange_id_sequence TO ro;
GRANT ALL ON TABLE questchange_id_sequence TO rw;

CREATE TABLE questchange
(
  id bigint NOT NULL DEFAULT nextval('questchange_id_sequence'::regclass),
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

CREATE OR REPLACE FUNCTION questchange_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION questchange_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_questchange_partition BEFORE INSERT ON questchange 
  FOR EACH ROW EXECUTE PROCEDURE questchange_insert_trigger();


-----------------------------------------------------------------------------------------
CREATE SEQUENCE dynamicquestchange_id_sequence;
ALTER TABLE dynamicquestchange_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE dynamicquestchange_id_sequence TO ro;
GRANT ALL ON TABLE dynamicquestchange_id_sequence TO rw;

CREATE TABLE dynamicquestchange
(
  id bigint NOT NULL DEFAULT nextval('dynamicquestchange_id_sequence'::regclass),
  player bigint NOT NULL,
  questindex integer NOT NULL,
  questname varchar NOT NULL,
  changetype integer NOT NULL,
  "timestamp" timestamp NOT NULL,
  alternativeline boolean NOT NULL,
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


-----------------------------------------------------------------------------------------
CREATE TABLE rune
(
  id integer NOT NULL,
  "name" varchar NOT NULL,
  percent integer NOT NULL,
  deleted boolean NOT NULL,
  CONSTRAINT rune_pkey PRIMARY KEY (id)
);
ALTER TABLE rune OWNER TO dbadmin;
GRANT SELECT ON TABLE rune TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE rune TO rw;


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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
  points integer,
  reason varchar,
  gmlogin varchar NOT NULL,
  timestamp timestamp NOT NULL,
  CONSTRAINT gm_useroperation_pkey PRIMARY KEY (id),
  CONSTRAINT gm_useroperation_player_fkey FOREIGN KEY (player) REFERENCES player (id)
);
ALTER TABLE gm_useroperation OWNER TO dbadmin;
GRANT SELECT ON TABLE gm_useroperation TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE gm_useroperation TO rw;

CREATE INDEX idx_gmuseroperation_player on gm_useroperation (player);


-----------------------------------------------------------------------------------------
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
  locale varchar NOT NULL,
  muid varchar,
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

CREATE TRIGGER first_tr_claim_lastmodified BEFORE INSERT OR UPDATE 
  ON claim FOR EACH ROW EXECUTE PROCEDURE update_timestamp();

CREATE INDEX idx_claim_lastmodified ON claim (lastmodified);
CREATE INDEX idx_claim_timestamp ON claim (timestamp);
CREATE INDEX idx_claim_toplayer on claim (toplayer);
CREATE INDEX idx_claim_gmuseroperation on claim (gmuseroperation);

CREATE OR REPLACE FUNCTION claim_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION claim_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_claim_partition BEFORE INSERT ON claim 
  FOR EACH ROW EXECUTE PROCEDURE claim_insert_trigger();


-----------------------------------------------------------------------------------------
CREATE SEQUENCE characterunlock_id_sequence;
ALTER TABLE characterunlock_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE characterunlock_id_sequence TO ro;
GRANT ALL ON TABLE characterunlock_id_sequence TO rw;

CREATE TABLE characterunlock
(
  id integer NOT NULL DEFAULT nextval('characterunlock_id_sequence'::regclass),
  playercharacter integer NOT NULL,
  resourcelog bigint,
  "timestamp" timestamp without time zone NOT NULL,
  CONSTRAINT characterunlock_pkey PRIMARY KEY (id),
  CONSTRAINT characterunlock_playercharacter_fkey FOREIGN KEY (playercharacter) REFERENCES playercharacter (id)
);
ALTER TABLE characterunlock OWNER TO dbadmin;
GRANT SELECT ON TABLE characterunlock TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE characterunlock TO rw;

CREATE OR REPLACE FUNCTION characterunlock_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION characterunlock_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_characterunlock_partition BEFORE INSERT ON characterunlock 
  FOR EACH ROW EXECUTE PROCEDURE characterunlock_insert_trigger();


-----------------------------------------------------------------------------------------
CREATE SEQUENCE movetobath_id_sequence;
ALTER TABLE movetobath_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE movetobath_id_sequence TO ro;
GRANT ALL ON TABLE movetobath_id_sequence TO rw;

CREATE TABLE movetobath
(
  id integer NOT NULL DEFAULT nextval('movetobath_id_sequence'::regclass),
  playercharacter integer NOT NULL,
  resourcelog bigint,
  minutes integer NOT NULL,
  "timestamp" timestamp without time zone NOT NULL,
  CONSTRAINT movetobath_pkey PRIMARY KEY (id),
  CONSTRAINT movetobath_playercharacter_fkey FOREIGN KEY (playercharacter) REFERENCES playercharacter (id)
);
ALTER TABLE movetobath OWNER TO dbadmin;
GRANT SELECT ON TABLE movetobath TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE movetobath TO rw;

CREATE OR REPLACE FUNCTION movetobath_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION movetobath_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_movetobath_partition BEFORE INSERT ON movetobath 
  FOR EACH ROW EXECUTE PROCEDURE movetobath_insert_trigger();


-----------------------------------------------------------------------------------------
CREATE SEQUENCE monitoring_results_id_sequence;
ALTER TABLE monitoring_results_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE monitoring_results_id_sequence TO ro;
GRANT ALL ON TABLE monitoring_results_id_sequence TO rw;

-- Table: monitoring_results

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

-- Index
CREATE INDEX idx_monitoring_results_property
  ON monitoring_results 
  USING btree (property);

-----------------------------------------------------------------------------------------
CREATE SEQUENCE runeroll_id_sequence;
ALTER TABLE runeroll_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE runeroll_id_sequence TO ro;
GRANT ALL ON TABLE runeroll_id_sequence TO rw;

CREATE TABLE runeroll
(
  id bigint NOT NULL DEFAULT nextval('runeroll_id_sequence'::regclass),
  player bigint NOT NULL,
  source varchar NOT NULL,
  persistentid bigint NOT NULL,
  rune integer NOT NULL,
  runescountold integer NOT NULL,
  runescountnew integer NOT NULL,
  timestamp timestamp,
  CONSTRAINT runeroll_pkey PRIMARY KEY (id),
  CONSTRAINT runeroll_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT runeroll_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id)
);
ALTER TABLE runeroll OWNER TO dbadmin;
GRANT SELECT ON TABLE runeroll TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE runeroll TO rw;

-----------------------------------------------------------------------------------------
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
-----------------------------------------------------------------------------------------
CREATE TABLE gwevents
      (
        id bigint NOT NULL,
        mongoid varchar NOT NULL,
        eventidx integer NOT NULL,
        enabled boolean NOT NULL,
        points integer NOT NULL,
        endtime timestamp NOT NULL,
        limitt integer NOT NULL,
        CONSTRAINT gwevents_pkey PRIMARY KEY (id),
      );
    ALTER TABLE gwevents OWNER TO dbadmin;
      GRANT SELECT ON TABLE gwevents TO ro;
      GRANT SELECT, UPDATE, INSERT ON TABLE gwevents TO rw;
-----------------------------------------------------------------------------------------
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


CREATE TABLE gweventslog
      (
        id bigint NOT NULL,
        gweventmid varchar NOT NULL,
        guildid bigint NOT NULL,
        lastpoints integer NOT NULL,
        currentpoints integer NOT NULL,
        auid integer NOT NULL,
        timestamp timestamp NOT NULL,
        CONSTRAINT gweventslog_pkey PRIMARY KEY (id)
      );
    ALTER TABLE gweventslog OWNER TO dbadmin;
      GRANT SELECT ON TABLE gweventslog TO ro;
      GRANT SELECT, UPDATE, INSERT ON TABLE gweventslog TO rw;
-----------------------------------------------------------------------------------------

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

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
CREATE SEQUENCE talentlog_id_sequence;
ALTER TABLE talentlog_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE talentlog_id_sequence TO ro;
GRANT ALL ON TABLE talentlog_id_sequence TO rw;

CREATE TABLE talentlog
(
  id bigint NOT NULL DEFAULT nextval('talentlog_id_sequence'::regclass),
  operation varchar NOT NULL,
  data varchar,
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

CREATE OR REPLACE FUNCTION talentlog_insert_trigger()
RETURNS TRIGGER AS $$ BEGIN RETURN NULL; END; $$ LANGUAGE plpgsql;
ALTER FUNCTION talentlog_insert_trigger() OWNER TO dbadmin;

CREATE TRIGGER tr_talentlog_partition BEFORE INSERT ON talentlog 
  FOR EACH ROW EXECUTE PROCEDURE talentlog_insert_trigger();


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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
  guildpointslog bigint NOT NULL,
  timestamp timestamp NOT NULL,
  CONSTRAINT guildshopbuy_pkey PRIMARY KEY (id),
  CONSTRAINT guildshopbuy_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT guildshopbuy_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
  CONSTRAINT guildshopbuy_guildshopitem_fkey FOREIGN KEY (guildshopitem) REFERENCES guildshopitem (id),
  CONSTRAINT guildshopbuy_guildpointslog_fkey FOREIGN KEY (guildpointslog) REFERENCES guildpointslog (id)
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


-----------------------------------------------------------------------------------------
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
  guildpointslog bigint NOT NULL,
  starttime timestamp NOT NULL,
  endtime timestamp NOT NULL,
  winner bigint NOT NULL,
  analysisid bigint NOT NULL DEFAULT nextval('guildsiege_analysisid_sequence'::regclass),
  CONSTRAINT guildsiege_pkey PRIMARY KEY (id),
  CONSTRAINT guildsiege_guild1_fkey FOREIGN KEY (guild) REFERENCES guild (id),
  CONSTRAINT guildsiege_guild2_fkey FOREIGN KEY (targetguild) REFERENCES guild (id),
  CONSTRAINT guildsiege_guild3_fkey FOREIGN KEY (targetsuzerainguild) REFERENCES guild (id),
  CONSTRAINT guildsiege_guild4_fkey FOREIGN KEY (winner) REFERENCES guild (id),
  CONSTRAINT guildsiege_guildpointslog_fkey FOREIGN KEY (guildpointslog) REFERENCES guildpointslog (id)
);
ALTER TABLE guildsiege OWNER TO dbadmin;
GRANT SELECT ON TABLE guildsiege TO ro;
GRANT SELECT, UPDATE, INSERT ON TABLE guildsiege TO rw;

CREATE INDEX idx_guildsiege_guild ON guildsiege (guild);
CREATE INDEX idx_guildsiege_timestamp ON guildsiege (starttime);
CREATE INDEX idx_guildsiege_analysisid ON guildsiege (analysisid);


-----------------------------------------------------------------------------------------
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
  guildpointslog bigint NOT NULL,
  starttime timestamp NOT NULL,
  endtime timestamp NOT NULL,
  CONSTRAINT guildsiegeparticipant_pkey PRIMARY KEY (id),
  CONSTRAINT guildsiegeparticipant_siege_fkey FOREIGN KEY (guildsiege) REFERENCES guildsiege (id),
  CONSTRAINT guildsiegeparticipant_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
  CONSTRAINT guildsiegeparticipant_guildpointslog_fkey FOREIGN KEY (guildpointslog) REFERENCES guildpointslog (id)
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
CREATE SEQUENCE leaverpointslog_id_sequence;
ALTER TABLE leaverpointslog_id_sequence OWNER TO dbadmin;
GRANT SELECT, USAGE ON TABLE leaverpointslog_id_sequence TO ro;
GRANT ALL ON TABLE leaverpointslog_id_sequence TO rw;

CREATE TABLE leaverpointslog
(
  id bigint NOT NULL DEFAULT nextval('leaverpointslog_id_sequence'::regclass),
  player bigint NOT NULL,
  persistentid bigint,
  type varchar,
  leaverpointschange integer NOT NULL,
  leaverpointstotal integer NOT NULL,
  isleaverchanged boolean NOT NULL,
  isleaver boolean NOT NULL,
  isbadbehaviour boolean NOT NULL,
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


-----------------------------------------------------------------------------------------

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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
-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------
CREATE SCHEMA partitions AUTHORIZATION dbadmin;
GRANT ALL ON SCHEMA partitions TO rw;
GRANT ALL ON SCHEMA partitions TO ro;

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE FUNCTION dbversion()
  RETURNS integer AS
$BODY$
begin
  return 91;
end;
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION dbversion() OWNER TO dbadmin;
GRANT EXECUTE ON FUNCTION dbversion() TO public;

-- Function: increment_version_to(integer)

CREATE OR REPLACE FUNCTION increment_version_to(ver integer)
  RETURNS integer AS
$BODY$
declare 
  dbver integer;
begin
  select dbversion() into dbver;
  if (ver != dbver + 1) then
    raise 'Version % cannot be incremented to %', dbver, ver;
  end if;

  execute('CREATE OR REPLACE FUNCTION dbversion() RETURNS integer AS
  $BODY2$ begin return ' || ver || '; end; $BODY2$ LANGUAGE plpgsql;');

  raise notice '% update % -> %', current_database(), dbver, ver;
  return ver;
  end;
$BODY$
  LANGUAGE plpgsql;
ALTER FUNCTION increment_version_to(integer) OWNER TO dbadmin;
GRANT EXECUTE ON FUNCTION increment_version_to(integer) TO public;
