-----------------------------------------------------------------------------------------
DO $$ 
BEGIN
  IF NOT EXISTS (SELECT 1 FROM pg_language WHERE lanname = 'plpgsql') THEN
    CREATE LANGUAGE plpgsql;
  END IF;
END $$;

-----------------------------------------------------------------------------------------
CREATE TABLE datehierarchy
(
  id integer NOT NULL,
  "year" integer NOT NULL,
  quarter integer NOT NULL,
  "month" integer NOT NULL,
  weekinmonth integer NOT NULL,
  dayinmonth integer NOT NULL,
  push character varying(255),
  CONSTRAINT datehierarchy_pkey PRIMARY KEY (id)
);
ALTER TABLE datehierarchy OWNER TO dbadmin;
GRANT SELECT ON TABLE datehierarchy TO ro;

CREATE OR REPLACE FUNCTION fill_datehierarchy()
  RETURNS void AS $$
DECLARE 
  d Date := '2010-09-01';
BEGIN
  insert into datehierarchy (id, year, quarter, month, weekinmonth, dayinmonth)
  values(0, 0, 0, 0, 0, 0);

  WHILE d < '2030-09-01' LOOP
    insert into datehierarchy (id, year, quarter, month, weekinmonth, dayinmonth)
    values (to_char(d, 'YYYYMMDD')::integer, date_part('year', d), date_part('quarter', d), 
            date_part('month', d), trunc((date_part('day', d)-1)/7) + 1, date_part('day', d));
    d := d + interval '1 day';
  END LOOP;
END;
$$ LANGUAGE plpgsql;

select fill_datehierarchy();
drop function fill_datehierarchy();

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
  rating integer,
  locale character varying NOT NULL,
  leavercount integer,
  leavergmcount integer,
  leaverpoints integer NOT NULL,
  isleaver bool NOT NULL,
  lastmodified timestamp not null,
  syncwith varchar NOT NULL,
  CONSTRAINT player_pkey PRIMARY KEY (id)
);
ALTER TABLE player OWNER TO dbadmin;
GRANT SELECT ON TABLE player TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE playercharacter
(
  id integer NOT NULL,
  location varchar NOT NULL,
  "character" integer NOT NULL,
  player bigint NOT NULL,
  rating integer,
  locked boolean NOT NULL default false,
  unlockdate timestamp without time zone,
  lastmodified timestamp not null,
  datehierarchy integer,
  analysisid serial NOT NULL,
  CONSTRAINT playercharacter_pkey PRIMARY KEY (id, location),
  CONSTRAINT playercharacter_unique_player_character UNIQUE (player, character, location),
  CONSTRAINT fke03456c98c205aa FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT fke03456c9f7af6777 FOREIGN KEY ("character") REFERENCES "character" (id),
  CONSTRAINT playercharacter_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT playercharacter_unique_analysisid UNIQUE (analysisid)
);
ALTER TABLE playercharacter OWNER TO dbadmin;
GRANT SELECT ON TABLE playercharacter TO ro;

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

-----------------------------------------------------------------------------------------
CREATE TABLE mgboost
(
  id integer NOT NULL,
  "name" character varying(1023),
  deleted boolean not null default false,
  CONSTRAINT mgboost_pkey PRIMARY KEY (id)
);
ALTER TABLE mgboost OWNER TO dbadmin;
GRANT SELECT ON TABLE mgboost TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE unittype
(
  id integer NOT NULL,
  "name" character varying(256),
  deleted boolean not null default false,
  CONSTRAINT unittype_pkey PRIMARY KEY (id)
);
ALTER TABLE unittype OWNER TO dbadmin;
GRANT SELECT ON TABLE unittype TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE abilitytype
(
  id integer NOT NULL,
  "name" character varying(256),
  deleted boolean not null default false,
  CONSTRAINT abilitytype_pkey PRIMARY KEY (id)
);
ALTER TABLE abilitytype OWNER TO dbadmin;
GRANT SELECT ON TABLE abilitytype TO ro;

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE TABLE creature
(
  id integer NOT NULL,
  "name" character varying(255),
  deleted boolean not null default false,
  CONSTRAINT creature_pkey PRIMARY KEY (id)
);
ALTER TABLE creature OWNER TO dbadmin;
GRANT SELECT ON TABLE creature TO ro;

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------
create table mmakingsession
(
  id bigint not null,
  location varchar not null,
  persistentid bigint not null,
  status integer not null,
  manoeuvresfaction integer not null,
  basket integer not null,
  map varchar,
  "timestamp" timestamp without time zone,
  datehierarchy integer,
  CONSTRAINT mmakingsession_pkey PRIMARY KEY (id, location),
  CONSTRAINT mmakingsession_unique_persistentid UNIQUE (persistentid),
  CONSTRAINT mmakingsession_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE mmakingsession OWNER TO dbadmin;
GRANT SELECT ON TABLE mmakingsession TO ro;

CREATE INDEX idx_mmakingsession_datehierarchy ON mmakingsession (datehierarchy);
CREATE INDEX idx_mmakingsession_persistentid ON mmakingsession (persistentid);

-----------------------------------------------------------------------------------------
create table mmakingplayer
(
  id bigint not null,
  location varchar not null,
  mmakingsession bigint,
  playercharacter integer not null,
  faction integer not null,
  sex integer not null,
  rating integer not null,
  playerrating integer,
  force real not null,
  party integer not null,
  waitinterval real not null,
  losestreak integer not null,
  famelevel integer not null,
  basket integer not null,
  lobbyreaction integer not null,
  lobbyreactiontime real,
  "timestamp" timestamp,
  datehierarchy integer,
  CONSTRAINT mmakingplayer_pkey PRIMARY KEY (id, location),
  CONSTRAINT mmakingplayer_mmakingsession_fkey FOREIGN KEY (mmakingsession, location) REFERENCES mmakingsession (id, location),
  CONSTRAINT mmakingplayer_playercharacter_fkey FOREIGN KEY (playercharacter, location) REFERENCES playercharacter (id, location)
);
ALTER TABLE mmakingplayer OWNER TO dbadmin;
GRANT SELECT ON TABLE mmakingplayer TO ro;

CREATE INDEX idx_mmakingplayer_datehierarchy ON mmakingplayer (datehierarchy);
CREATE INDEX idx_mmakingplayer_mmakingsession ON mmakingplayer (mmakingsession);
CREATE INDEX idx_mmakingplayer_playercharacter ON mmakingplayer (playercharacter);

-----------------------------------------------------------------------------------------
CREATE TABLE gamesession
(
  id integer NOT NULL,
  location varchar NOT NULL,
  persistentid bigint NOT NULL,
  server character varying(255),
  serveraddress varchar,
  cluster varchar,
  map character varying(255),
  sessiontype integer NOT NULL DEFAULT 0,
  starttime timestamp without time zone NOT NULL,
  endtime timestamp without time zone,
  sidewon integer,
  surrendervote integer NOT NULL,
  sessionresult integer NOT NULL,
  timehierarchyid integer,
  analysisid serial NOT NULL,
  CONSTRAINT gamesession_pkey PRIMARY KEY (id, location),
  CONSTRAINT gamesession_datehierarchy_fkey FOREIGN KEY (timehierarchyid) REFERENCES datehierarchy (id),
  CONSTRAINT gamesession_unique_analysisid UNIQUE (analysisid)
);
ALTER TABLE gamesession OWNER TO dbadmin;
GRANT SELECT ON TABLE gamesession TO ro;

CREATE INDEX idx_gamesession_datehierarchy ON gamesession (timehierarchyid);
CREATE INDEX idx_gamesession_persistentid ON gamesession (persistentid);
CREATE INDEX idx_gamesession_location ON gamesession (location);

-----------------------------------------------------------------------------------------
CREATE TABLE resourcelog
(
  id bigint NOT NULL,
  location varchar NOT NULL,
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
  datehierarchy integer,
  CONSTRAINT resourcelog_pkey PRIMARY KEY (id, location),
  CONSTRAINT resourcelog_player_fkey FOREIGN KEY (player) REFERENCES player (id)
);
ALTER TABLE resourcelog OWNER TO dbadmin;
GRANT SELECT ON TABLE resourcelog TO ro;

CREATE INDEX idx_resourcelog_player  ON resourcelog (player);

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

-----------------------------------------------------------------------------------------
CREATE TABLE resourcelog_gold (LIKE resourcelog INCLUDING DEFAULTS);
ALTER TABLE resourcelog_gold OWNER TO dbadmin;
GRANT SELECT ON TABLE resourcelog_gold TO ro;

ALTER TABLE resourcelog_gold ADD CONSTRAINT resourcelog_gold_pkey PRIMARY KEY (id, location);
ALTER TABLE resourcelog_gold ADD CONSTRAINT resourcelog_gold_player_fkey FOREIGN KEY (player) REFERENCES player (id);
ALTER TABLE resourcelog_gold ADD CONSTRAINT resourcelog_gold_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id);

CREATE INDEX idx_resourcelog_gold_player ON resourcelog (player);
CREATE INDEX idx_resourcelog_gold_datehierarchy ON resourcelog (datehierarchy);

-----------------------------------------------------------------------------------------
CREATE TABLE resourcelog_agg_source
(
  datehierarchy integer NOT NULL,
  location varchar NOT NULL,
  source character varying NOT NULL,
  buildingname character varying,  
  gain boolean NOT NULL,
  goldchange bigint NOT NULL,
  silverchange bigint NOT NULL,
  perlchange bigint NOT NULL,
  redperlchange bigint NOT NULL,
  populationchange bigint NOT NULL,
  resource1change bigint NOT NULL,
  resource2change bigint NOT NULL,
  resource3change bigint NOT NULL,
  shardchange bigint NOT NULL,
  currencychange character varying NOT NULL,
  currencychangevalue bigint NOT NULL,
  CONSTRAINT resourcelog_agg_source_unique UNIQUE (datehierarchy, location, source, buildingname, gain)
);
ALTER TABLE resourcelog_agg_source OWNER TO dbadmin;
GRANT SELECT ON TABLE resourcelog_agg_source TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE sessiontoplayer
(
  id integer NOT NULL,
  location varchar NOT NULL,
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
  resourcelog bigint,
  rloglocation bigint,
  ratingtotal integer,
  force real,
  relayaddress varchar,
  partymembers integer,
  guild bigint,
  analysisid serial NOT NULL,
  playercharacter_analysisid integer,
  gamesession_analysisid integer,
  CONSTRAINT sessiontoplayer_pkey PRIMARY KEY (id, location),
  CONSTRAINT sessiontoplayer_playercharacter_fkey FOREIGN KEY (playercharacter, location) REFERENCES playercharacter (id, location),
  CONSTRAINT sessiontoplayer_gamesession_fkey FOREIGN KEY (gamesession, location) REFERENCES gamesession (id, location),
  CONSTRAINT sessiontoplayer_unique_analysisid UNIQUE (analysisid),
  CONSTRAINT sessiontoplayer_playercharacter_analysisid_fkey FOREIGN KEY (playercharacter_analysisid) REFERENCES playercharacter (analysisid),
  CONSTRAINT sessiontoplayer_gamesession_analysisid_fkey FOREIGN KEY (gamesession_analysisid) REFERENCES gamesession (analysisid)
);
ALTER TABLE sessiontoplayer OWNER TO dbadmin;
GRANT SELECT ON TABLE sessiontoplayer TO ro;

CREATE INDEX idx_sessiontoplayer_playercharacter ON sessiontoplayer (playercharacter);
CREATE INDEX idx_sessiontoplayer_gamesession ON sessiontoplayer (gamesession);
CREATE INDEX idx_sessiontoplayer_location ON sessiontoplayer (location);

CREATE INDEX idx_sessiontoplayer_playercharacter_analysisid ON sessiontoplayer (playercharacter_analysisid);
CREATE INDEX idx_sessiontoplayer_gamesession_analysisid ON sessiontoplayer (gamesession_analysisid);

-----------------------------------------------------------------------------------------
CREATE TABLE socialsession
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  player bigint NOT NULL,
  playerip character varying,
  server character varying,
  "cluster" character varying,
  starttime timestamp without time zone NOT NULL,
  endtime timestamp without time zone,
  datehierarchy integer NOT NULL,
  CONSTRAINT socialsession_pkey PRIMARY KEY (id, location),
  CONSTRAINT socialsession_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT socialsession_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE socialsession OWNER TO dbadmin;
GRANT SELECT ON TABLE socialsession TO ro;

CREATE INDEX idx_socialsession_player  ON socialsession (player);
CREATE INDEX idx_socialsession_datehierarchy ON socialsession (datehierarchy);


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

CREATE INDEX idx_guild_lastmodified ON guild (lastmodified);

-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
CREATE TABLE guildshopbuy
(
  id bigint NOT NULL,
  player bigint NOT NULL,
  guild bigint NOT NULL,
  hassuzerain boolean NOT NULL,
  guildshopitem integer NOT NULL,
  shoplevel integer NOT NULL,
  guildpointslog bigint NOT NULL,
  timestamp timestamp NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT guildshopbuy_pkey PRIMARY KEY (id),
  CONSTRAINT guildshopbuy_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT guildshopbuy_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
  CONSTRAINT guildshopbuy_guildshopitem_fkey FOREIGN KEY (guildshopitem) REFERENCES guildshopitem (id),
  CONSTRAINT guildshopbuy_guildpointslog_fkey FOREIGN KEY (guildpointslog) REFERENCES guildpointslog (id),
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

-----------------------------------------------------------------------------------------
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
  analysisid bigint NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT guildsiege_pkey PRIMARY KEY (id),
  CONSTRAINT guildsiege_guild1_fkey FOREIGN KEY (guild) REFERENCES guild (id),
  CONSTRAINT guildsiege_guild2_fkey FOREIGN KEY (targetguild) REFERENCES guild (id),
  CONSTRAINT guildsiege_guild3_fkey FOREIGN KEY (targetsuzerainguild) REFERENCES guild (id),
  CONSTRAINT guildsiege_guild4_fkey FOREIGN KEY (winner) REFERENCES guild (id),
  CONSTRAINT guildsiege_guildpointslog_fkey FOREIGN KEY (guildpointslog) REFERENCES guildpointslog (id),
  CONSTRAINT guildsiege_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)  
);
ALTER TABLE guildsiege OWNER TO dbadmin;
GRANT SELECT ON TABLE guildsiege TO ro;

CREATE INDEX idx_guildsiege_guild ON guildsiege (guild);
CREATE INDEX idx_guildsiege_starttime ON guildsiege (starttime);
CREATE INDEX idx_guildsiege_analysisid ON guildsiege (analysisid);


-----------------------------------------------------------------------------------------
CREATE TABLE guildsiegeparticipant
(
  id bigint NOT NULL,
  guildsiege bigint NOT NULL,
  guild bigint NOT NULL,
  rating integer NOT NULL,
  siegepoints integer NOT NULL,
  guildpointslog bigint NOT NULL,
  starttime timestamp NOT NULL,
  endtime timestamp NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT guildsiegeparticipant_pkey PRIMARY KEY (id),
  CONSTRAINT guildsiegeparticipant_siege_fkey FOREIGN KEY (guildsiege) REFERENCES guildsiege (id),
  CONSTRAINT guildsiegeparticipant_guild_fkey FOREIGN KEY (guild) REFERENCES guild (id),
  CONSTRAINT guildsiegeparticipant_guildpointslog_fkey FOREIGN KEY (guildpointslog) REFERENCES guildpointslog (id),
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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



-----------------------------------------------------------------------------------------
CREATE TABLE factionchange
(
  id integer NOT NULL,
  location varchar NOT NULL,
  player bigint NOT NULL,
  oldfaction integer,
  newfaction integer,
  resourcelog bigint,
  "timestamp" timestamp NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT factionchange_pkey PRIMARY KEY (id, location),
  CONSTRAINT factionchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT factionchange_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE factionchange OWNER TO dbadmin;
GRANT SELECT ON TABLE factionchange TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE questchange
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  player bigint NOT NULL,
  quest integer NOT NULL,
  changetype integer NOT NULL,
  "timestamp" timestamp NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT questchange_pkey PRIMARY KEY (id, location),
  CONSTRAINT questchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT questchange_quest_fkey FOREIGN KEY (quest) REFERENCES quest (id),
  CONSTRAINT questchange_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE questchange OWNER TO dbadmin;
GRANT SELECT ON TABLE questchange TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE dynamicquestchange
(
  id bigint NOT NULL,
  player bigint NOT NULL,
  questindex integer NOT NULL,
  questname varchar NOT NULL,
  changetype integer NOT NULL,
  "timestamp" timestamp NOT NULL,
  datehierarchy integer NOT NULL,
  alternativeline boolean NOT NULL,
  CONSTRAINT dynamicquestchange_pkey PRIMARY KEY (id),
  CONSTRAINT dynamicquestchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT dynamicquestchange_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE dynamicquestchange OWNER TO dbadmin;
GRANT SELECT ON TABLE dynamicquestchange TO ro;

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE TABLE ratingchange
(
  id integer NOT NULL,
  location varchar NOT NULL,
  type integer NOT NULL,
  player bigint NOT NULL,
  persistentid bigint,
  character integer,
  change integer,
  total bigint,
  "timestamp" timestamp NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT ratingchange_pkey PRIMARY KEY (id, location),
  CONSTRAINT ratingchange_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT ratingchange_character_fkey FOREIGN KEY (character) REFERENCES character (id),
  CONSTRAINT ratingchange_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE ratingchange OWNER TO dbadmin;
GRANT SELECT ON TABLE ratingchange TO ro;


-----------------------------------------------------------------------------------------
CREATE TABLE leaverpointslog
(
  id bigint NOT NULL,
  player bigint NOT NULL,
  persistentid bigint,
  type varchar,
  leaverpointschange integer NOT NULL,
  leaverpointstotal integer NOT NULL,
  isleaverchanged boolean NOT NULL,
  isleaver boolean NOT NULL,
  isbadbehaviour boolean NOT NULL,
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


-----------------------------------------------------------------------------------------
------------ event tables ---------------------------------------------------------------
-----------------------------------------------------------------------------------------

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
ALTER FUNCTION partition_every_day(oid, integer) OWNER TO dbadmin;

-----------------------------------------------------------------------------------------
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
ALTER FUNCTION partitions_check(character varying) OWNER TO dbadmin;

-----------------------------------------------------------------------------------------
CREATE TABLE event_talentused
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  talentid integer,
  duration real,
  datehierarchy integer NOT NULL,
  CONSTRAINT talentused_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_talentused_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_talentused_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_talentused_talentid_fkey FOREIGN KEY (talentid) REFERENCES talent (id),
  CONSTRAINT event_talentused_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE event_talentused OWNER TO dbadmin;
GRANT SELECT ON TABLE event_talentused TO ro;

CREATE INDEX idx_event_talentused_sessiontoplayerid ON event_talentused (sessiontoplayerid);
CREATE INDEX idx_event_talentused_datehierarchy ON event_talentused (datehierarchy);

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE TABLE event_talentunlocked
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  talentid integer,
  nafta integer,
  CONSTRAINT event_talentunlocked_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_talentunlocked_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_talentunlocked_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_talentunlocked_talentid_fkey FOREIGN KEY (talentid) REFERENCES talent (id)
);
ALTER TABLE event_talentunlocked OWNER TO dbadmin;
GRANT SELECT ON TABLE event_talentunlocked TO ro;

CREATE INDEX idx_event_talentunlocked_sessiontoplayerid ON event_talentunlocked (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_timeslice
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  slice integer,
  "level" integer,
  currentnafta integer,
  totalnafta integer,
  salarynafta integer,
  datehierarchy integer NOT NULL,
  CONSTRAINT event_timeslice_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_timeslice_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_timeslice_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_timeslice_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE event_timeslice OWNER TO dbadmin;
GRANT SELECT ON TABLE event_timeslice TO ro;

CREATE INDEX idx_event_timeslice_sessiontoplayerid ON event_timeslice (sessiontoplayerid);
CREATE INDEX idx_event_timeslice_datehierarchy     ON event_timeslice (datehierarchy);

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

SELECT partitions_check('event_timeslice');

CREATE TRIGGER tr_event_timeslice_partition BEFORE INSERT ON event_timeslice
  FOR EACH ROW EXECUTE PROCEDURE event_timeslice_insert_trigger();

-----------------------------------------------------------------------------------------
CREATE TABLE event_ressurection
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  CONSTRAINT event_ressurection_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_ressurection_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_ressurection_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_ressurection OWNER TO dbadmin;
GRANT SELECT ON TABLE event_ressurection TO ro;

CREATE INDEX idx_event_ressurection_sessiontoplayerid ON event_ressurection (sessiontoplayerid);

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE TABLE event_levelup
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  "level" integer,
  CONSTRAINT event_levelup_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_levelup_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_levelup_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_levelup OWNER TO dbadmin;
GRANT SELECT ON TABLE event_levelup TO ro;

CREATE INDEX idx_event_levelup_sessiontoplayerid ON event_levelup (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_impulsivebuffused
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  impulsivebuffid integer,
  CONSTRAINT event_impulsivebuffused_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_impulsivebuffused_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_impulsivebuffused_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_impulsivebuffused_impulsivebuffid_fkey FOREIGN KEY (impulsivebuffid) REFERENCES impulsivebuff (id)
);
ALTER TABLE event_impulsivebuffused OWNER TO dbadmin;
GRANT SELECT ON TABLE event_impulsivebuffused TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE event_impulsivebuffsuggested
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  impulsivebuffid integer,
  CONSTRAINT event_impulsivebuffsuggested_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_impulsivebuffsuggested_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_impulsivebuffsuggested_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_impulsivebuffsuggested_impulsivebuffid_fkey FOREIGN KEY (impulsivebuffid) REFERENCES impulsivebuff (id)
);
ALTER TABLE event_impulsivebuffsuggested OWNER TO dbadmin;
GRANT SELECT ON TABLE event_impulsivebuffsuggested TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE event_buildingdestroyed
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  buildingid integer,
  destroyercharacterid integer,
  destroyercreatureid integer,
  CONSTRAINT event_buildingdestroyed_pkey PRIMARY KEY (id),
  CONSTRAINT event_buildingdestroyed_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_buildingdestroyed_destroyercharacterid_fkey FOREIGN KEY (destroyercharacterid) REFERENCES "character" (id),
  CONSTRAINT event_buildingdestroyed_buildingid_fkey FOREIGN KEY (buildingid) REFERENCES building (id),
  CONSTRAINT event_buildingdestroyed_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_buildingdestroyed OWNER TO dbadmin;
GRANT SELECT ON TABLE event_buildingdestroyed TO ro;

CREATE INDEX idx_event_buildingdestroyed_sessiontoplayerid ON event_buildingdestroyed (sessiontoplayerid);

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

ALTER TABLE v_event_buildingdestroyed OWNER TO dbadmin;
GRANT SELECT ON TABLE v_event_buildingdestroyed TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE event_achievement
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  achievementid integer,
  CONSTRAINT event_achievement_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_achievement_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_achievement_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_achievement_achievementid_fkey FOREIGN KEY (achievementid) REFERENCES achievement (id)
);
ALTER TABLE event_achievement OWNER TO dbadmin;
GRANT SELECT ON TABLE event_achievement TO ro;

CREATE INDEX idx_event_achievement_sessiontoplayerid ON event_achievement (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_consumablebought
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  consumableid integer,
  nafta integer,
  CONSTRAINT event_consumablebought_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_consumablebought_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_consumablebought_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_consumablebought_consumableid_fkey FOREIGN KEY (consumableid) REFERENCES consumable (id)
);
ALTER TABLE event_consumablebought OWNER TO dbadmin;
GRANT SELECT ON TABLE event_consumablebought TO ro;

CREATE INDEX idx_event_consumablebought_sessiontoplayerid ON event_consumablebought (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_consumableused
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  consumableid integer,
  CONSTRAINT event_consumableused_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_consumableused_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_consumableused_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_consumableused_consumableid_fkey FOREIGN KEY (consumableid) REFERENCES consumable (id)
);
ALTER TABLE event_consumableused OWNER TO dbadmin;
GRANT SELECT ON TABLE event_consumableused TO ro;

CREATE INDEX idx_event_consumableused_sessiontoplayerid ON event_consumableused (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_cheatused
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  command character varying(255),
  CONSTRAINT event_cheatused_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_cheatused_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_cheatused_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_cheatused OWNER TO dbadmin;
GRANT SELECT ON TABLE event_cheatused TO ro;

CREATE INDEX idx_event_cheatused_sessiontoplayerid ON event_cheatused (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_flag
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  raised boolean,
  faction integer,
  road integer,
  segment integer,
  activatorcharacterid integer,
  activatorcreatureid integer,
  CONSTRAINT event_flag_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_flag_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_flag_activatorcharacterid_fkey FOREIGN KEY (activatorcharacterid) REFERENCES "character" (id),
  CONSTRAINT event_flag_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_flag OWNER TO dbadmin;
GRANT SELECT ON TABLE event_flag TO ro;

CREATE INDEX idx_event_flag_sessiontoplayerid ON event_flag (sessiontoplayerid);

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

ALTER TABLE v_event_flag OWNER TO dbadmin;
GRANT SELECT ON TABLE v_event_flag TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE event_naftaincome
(
  id bigint NOT NULL,
  location varchar NOT NULL,
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
  map character varying NOT NULL,
  sessiontype integer NOT NULL,
  CONSTRAINT event_naftaincome_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_naftaincome_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_naftaincome_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_naftaincome_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE event_naftaincome OWNER TO dbadmin;
GRANT SELECT ON TABLE event_naftaincome TO ro;

CREATE INDEX idx_event_naftaincome_sessiontoplayerid ON event_naftaincome (sessiontoplayerid);

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

-----------------------------------------------------------------------------------------
CREATE TABLE event_naftaincome_agg_minute
(
  datehierarchy integer NOT NULL,
  location varchar NOT NULL,
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
  CONSTRAINT event_naftaincome_agg_minute_pkey PRIMARY KEY (datehierarchy, location, characterid, map, sessiontype, incomefrom, minute),
  CONSTRAINT event_naftaincome_agg_minute_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT event_naftaincome_agg_minute_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id)
);
ALTER TABLE event_naftaincome_agg_minute OWNER TO dbadmin;
GRANT SELECT ON TABLE event_naftaincome_agg_minute TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE event_kill
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  victimcharacterid integer,
  victimcreatureid integer,
  sessiontoplayer_analysisid integer NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT event_kill_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_kill_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_kill_victimcharacterid_fkey FOREIGN KEY (victimcharacterid) REFERENCES "character" (id),
  CONSTRAINT event_kill_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_kill_sessiontoplayer_analysisid_fkey FOREIGN KEY (sessiontoplayer_analysisid) REFERENCES sessiontoplayer (analysisid),
  CONSTRAINT event_kill_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE event_kill OWNER TO dbadmin;
GRANT SELECT ON TABLE event_kill TO ro;

CREATE INDEX idx_event_kill_sessiontoplayerid          ON event_kill (sessiontoplayerid);
CREATE INDEX idx_event_kill_sessiontoplayer_analysisid ON event_kill (sessiontoplayer_analysisid);
CREATE INDEX idx_event_kill_datehierarchy              ON event_kill (datehierarchy);

CREATE OR REPLACE FUNCTION event_kill_insert_trigger()
  RETURNS trigger AS $$
BEGIN
  IF (false) THEN RAISE;
  ELSE
    RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_kill_insert_trigger() function!';
  END IF;
  RETURN NULL;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION event_kill_insert_trigger() OWNER TO dbadmin;

SELECT partitions_check('event_kill');

CREATE TRIGGER tr_event_kill_partition
  BEFORE INSERT ON event_kill FOR EACH ROW
  EXECUTE PROCEDURE event_kill_insert_trigger();

-----------------------------------------------------------------------------------------
CREATE TABLE event_assist
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  victimcharacterid integer,
  killercharacterid integer,
  killercreatureid integer,
  sessiontoplayer_analysisid integer NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT event_assist_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_assist_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_assist_victimid_fkey FOREIGN KEY (victimcharacterid) REFERENCES "character" (id),
  CONSTRAINT event_assist_killerid_fkey FOREIGN KEY (killercharacterid) REFERENCES "character" (id),
  CONSTRAINT event_assist_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_assist_sessiontoplayer_analysisid_fkey FOREIGN KEY (sessiontoplayer_analysisid) REFERENCES sessiontoplayer (analysisid),
  CONSTRAINT event_assist_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE event_assist OWNER TO dbadmin;
GRANT SELECT ON TABLE event_assist TO ro;

CREATE INDEX idx_event_assist_sessiontoplayerid          ON event_assist (sessiontoplayerid);
CREATE INDEX idx_event_assist_sessiontoplayer_analysisid ON event_assist (sessiontoplayer_analysisid);
CREATE INDEX idx_event_assist_datehierarchy              ON event_assist (datehierarchy);

CREATE OR REPLACE FUNCTION event_assist_insert_trigger()
  RETURNS trigger AS $$
BEGIN
  IF (false) THEN RAISE;
  ELSE
    RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_assist_insert_trigger() function!';
  END IF;
  RETURN NULL;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION event_assist_insert_trigger() OWNER TO dbadmin;

SELECT partitions_check('event_assist');

CREATE TRIGGER tr_event_assist_partition
  BEFORE INSERT ON event_assist FOR EACH ROW
  EXECUTE PROCEDURE event_assist_insert_trigger();

-----------------------------------------------------------------------------------------
CREATE TABLE event_death
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  killercharacterid integer,
  killercreatureid integer,
  sessiontoplayer_analysisid integer NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT event_death_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_death_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_death_killercharacterid_fkey FOREIGN KEY (killercharacterid) REFERENCES "character" (id),
  CONSTRAINT event_death_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_death_sessiontoplayer_analysisid_fkey FOREIGN KEY (sessiontoplayer_analysisid) REFERENCES sessiontoplayer (analysisid),
  CONSTRAINT event_death_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE event_death OWNER TO dbadmin;
GRANT SELECT ON TABLE event_death TO ro;

CREATE INDEX idx_event_death_sessiontoplayerid          ON event_death (sessiontoplayerid);
CREATE INDEX idx_event_death_sessiontoplayer_analysisid ON event_death (sessiontoplayer_analysisid);
CREATE INDEX idx_event_death_datehierarchy              ON event_death (datehierarchy);

CREATE OR REPLACE FUNCTION event_death_insert_trigger()
  RETURNS trigger AS $$
BEGIN
  IF (false) THEN RAISE;
  ELSE
    RAISE EXCEPTION 'Unexpected datehierarchy value. Fix the event_death_insert_trigger() function!';
  END IF;
  RETURN NULL;
END;
$$ LANGUAGE plpgsql;
ALTER FUNCTION event_death_insert_trigger() OWNER TO dbadmin;

select partitions_check('event_death');

CREATE TRIGGER tr_event_death_partition
  BEFORE INSERT ON event_death FOR EACH ROW
  EXECUTE PROCEDURE event_death_insert_trigger();

-----------------------------------------------------------------------------------------
CREATE TABLE event_damage
(
  id bigint NOT NULL,
  location varchar NOT NULL,
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
  map character varying NOT NULL,
  sessiontype integer NOT NULL,
  CONSTRAINT event_damage_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_damage_characterid_fkey FOREIGN KEY (characterid) REFERENCES "character" (id),
  CONSTRAINT event_damage_unittype_fkey FOREIGN KEY (unittype) REFERENCES unittype (id),
  CONSTRAINT event_damage_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT event_damage_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE event_damage OWNER TO dbadmin;
GRANT SELECT ON TABLE event_damage TO ro;

CREATE INDEX idx_event_damage_sessiontoplayerid ON event_damage (sessiontoplayerid);

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

-----------------------------------------------------------------------------------------
CREATE TABLE event_damage_agg_building
(
  datehierarchy integer NOT NULL,
  location varchar NOT NULL,
  characterid integer NOT NULL,
  map character varying NOT NULL,
  sessiontype integer NOT NULL,
  sessioncount integer NOT NULL,
  buildingid integer NOT NULL,
  dealt boolean NOT NULL,
  physicaldamage real,
  magicaldamage real,
  puredamage real,
  CONSTRAINT event_damage_agg_building_pkey PRIMARY KEY (datehierarchy, location, characterid, map, sessiontype, buildingid, dealt),
  CONSTRAINT event_damage_agg_building_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT event_damage_agg_building_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
  CONSTRAINT event_damage_agg_building_buildingid_fkey FOREIGN KEY (buildingid) REFERENCES building (id)
);
ALTER TABLE event_damage_agg_building OWNER TO dbadmin;
GRANT SELECT ON TABLE event_damage_agg_building TO ro;

CREATE TABLE event_damage_agg_creature
(
  datehierarchy integer NOT NULL,
  location varchar NOT NULL,
  characterid integer NOT NULL,
  map character varying NOT NULL,
  sessiontype integer NOT NULL,
  sessioncount integer NOT NULL,
  creatureid integer NOT NULL,
  dealt boolean NOT NULL,
  physicaldamage real,
  magicaldamage real,
  puredamage real,
  CONSTRAINT event_damage_agg_creature_pkey PRIMARY KEY (datehierarchy, location, characterid, map, sessiontype, creatureid, dealt),
  CONSTRAINT event_damage_agg_creature_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT event_damage_agg_creature_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
  CONSTRAINT event_damage_agg_creature_creatureid_fkey FOREIGN KEY (creatureid) REFERENCES creature (id)
);
ALTER TABLE event_damage_agg_creature OWNER TO dbadmin;
GRANT SELECT ON TABLE event_damage_agg_creature TO ro;

CREATE TABLE event_damage_agg_unittype
(
  datehierarchy integer NOT NULL,
  location varchar NOT NULL,
  characterid integer NOT NULL,
  map character varying NOT NULL,
  sessiontype integer NOT NULL,
  sessioncount integer NOT NULL,
  unittype integer NOT NULL,
  dealt boolean NOT NULL,
  physicaldamage real,
  magicaldamage real,
  puredamage real,
  CONSTRAINT event_damage_agg_unittype_pkey PRIMARY KEY (datehierarchy, location, characterid, map, sessiontype, unittype, dealt),
  CONSTRAINT event_damage_agg_unittype_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT event_damage_agg_unittype_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
  CONSTRAINT event_damage_agg_unittype_unittype_fkey FOREIGN KEY (unittype) REFERENCES unittype (id)
);
ALTER TABLE event_damage_agg_unittype OWNER TO dbadmin;
GRANT SELECT ON TABLE event_damage_agg_unittype TO ro;

CREATE TABLE event_damage_agg_character
(
  datehierarchy integer NOT NULL,
  location varchar NOT NULL,
  characterid integer NOT NULL,
  map character varying NOT NULL,
  sessiontype integer NOT NULL,
  sessioncount integer NOT NULL,
  opponentcharacterid integer NOT NULL,
  dealt boolean NOT NULL,
  physicaldamage real,
  magicaldamage real,
  puredamage real,
  CONSTRAINT event_damage_agg_character_pkey PRIMARY KEY (datehierarchy, location, opponentcharacterid, characterid, map, sessiontype, dealt),
  CONSTRAINT event_damage_agg_character_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT event_damage_agg_character_characterid_fkey FOREIGN KEY (characterid) REFERENCES character (id),
  CONSTRAINT event_damage_agg_character_opponentcharacterid_fkey FOREIGN KEY (opponentcharacterid) REFERENCES character (id)
);
ALTER TABLE event_damage_agg_character OWNER TO dbadmin;
GRANT SELECT ON TABLE event_damage_agg_character TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE event_debugvar
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  eventtime timestamp without time zone,
  name character varying(255) NOT NULL,
  value character varying(255) NOT NULL,
  CONSTRAINT event_debugvar_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_debugvar_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_debugvar OWNER TO dbadmin;
GRANT SELECT ON TABLE event_debugvar TO ro;

CREATE INDEX idx_event_debugvar_sessiontoplayerid ON event_debugvar (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE exceedingserversteptime
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  gamesessionid integer NOT NULL,
  step integer,
  starttime timestamp without time zone,
  finishtime timestamp without time zone,
  stepcount integer,
  steptimemin integer,
  steptimemax integer,
  steptimeavg integer,
  datehierarchy integer,
  CONSTRAINT exceedingserversteptime_pkey PRIMARY KEY (id, location),
  CONSTRAINT exceedingserversteptime_gamesessionid_fkey FOREIGN KEY (gamesessionid, location) REFERENCES gamesession (id, location),
  CONSTRAINT exceedingserversteptime_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE exceedingserversteptime OWNER TO dbadmin;
GRANT SELECT ON TABLE exceedingserversteptime TO ro;

CREATE INDEX idx_exceedingserversteptime_gamesessionid ON exceedingserversteptime (gamesessionid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_exceedingsteptime
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,  
  typeid integer,
  startstep integer,
  finishstep integer,
  starttime timestamp without time zone,
  finishtime timestamp without time zone,
  stepcount integer,
  steptimemin integer,
  steptimemax integer,
  steptimeavg integer,
  worldrequeststep integer,
  rpcping integer,
  transportping integer,
  datehierarchy integer,
  CONSTRAINT event_exceedingsteptime_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_exceedingsteptime_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT event_exceedingsteptime_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_exceedingsteptime OWNER TO dbadmin;
GRANT SELECT ON TABLE event_exceedingsteptime TO ro;

CREATE INDEX idx_event_exceedingsteptime_sessiontoplayerid ON event_exceedingsteptime (sessiontoplayerid);

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

SELECT partitions_check('event_exceedingsteptime');

CREATE TRIGGER tr_event_exceedingsteptime_partition BEFORE INSERT ON event_exceedingsteptime
  FOR EACH ROW EXECUTE PROCEDURE event_exceedingsteptime_insert_trigger();

-----------------------------------------------------------------------------------------
CREATE TABLE event_exceedingpingtime
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,  
  typeid integer,
  starttime timestamp without time zone,
  finishtime timestamp without time zone,
  pinglcount integer,
  pingltimemin integer,
  pingltimemax integer,
  pingltimeavg integer,
  pinghcount integer,
  pinghtimemin integer,
  pinghtimemax integer,
  pinghtimeavg integer,
  datehierarchy integer,  
  CONSTRAINT event_exceedingpingtime_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_exceedingpingtime_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT event_exceedingpingtime_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_exceedingpingtime OWNER TO dbadmin;
GRANT SELECT ON TABLE event_exceedingpingtime TO ro;

CREATE INDEX idx_event_exceedingpingtime_sessiontoplayerid ON event_exceedingpingtime (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE offlineevent
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  playerid bigint NOT NULL,
  persistentid bigint NOT NULL,
  code int NOT NULL,
  auxdata bigint NOT NULL,
  timestamp timestamp NOT NULL,
  datehierarchy integer,
  CONSTRAINT offlineevent_pkey PRIMARY KEY (id),
  CONSTRAINT offlineevent_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE offlineevent OWNER TO dbadmin;
GRANT SELECT ON TABLE offlineevent TO ro;

CREATE INDEX idx_offlineevent_datehierarchy ON offlineevent (datehierarchy);

-----------------------------------------------------------------------------------------
CREATE TABLE event_disconnect
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  reason integer,
  "timestamp" timestamp without time zone,
  datehierarchy integer,  
  CONSTRAINT disconnect_pkey PRIMARY KEY (id),
  CONSTRAINT event_disconnect_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT event_disconnect_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_disconnect OWNER TO dbadmin;
GRANT SELECT ON TABLE event_disconnect TO ro;

CREATE INDEX idx_event_disconnect_sessiontoplayerid ON event_disconnect (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_reconnect
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  type character varying NOT NULL,
  result character varying NOT NULL,
  "timestamp" timestamp without time zone,
  datehierarchy integer,
  CONSTRAINT event_reconnect_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_reconnect_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT event_reconnect_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_reconnect OWNER TO dbadmin;
GRANT SELECT ON TABLE event_reconnect TO ro;

CREATE INDEX idx_event_reconnect_sessiontoplayerid ON event_reconnect (sessiontoplayerid);

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE TABLE event_cheat
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  cheattype integer NOT NULL,
  clientip character varying NOT NULL,
  "timestamp" timestamp without time zone NOT NULL,  
  CONSTRAINT event_cheat_pkey PRIMARY KEY (id),
  CONSTRAINT event_cheat_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_cheat OWNER TO dbadmin;
GRANT SELECT ON TABLE event_cheat TO ro;

CREATE INDEX idx_event_cheat_sessiontoplayerid ON event_cheat (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_mg_session
(
  startid bigint NOT NULL,
  finishid bigint,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  startstep integer NOT NULL,
  finishstep integer,
  x real NOT NULL,
  y real NOT NULL,
  CONSTRAINT event_mg_session_pkey PRIMARY KEY (startid, location),
  CONSTRAINT event_mg_session_sessiontoplayerid_fkey FOREIGN KEY (sessiontoplayerid, location) REFERENCES sessiontoplayer (id, location)
);
ALTER TABLE event_mg_session OWNER TO dbadmin;
GRANT SELECT ON TABLE event_mg_session TO ro;

CREATE INDEX idx_event_mg_session_sessiontoplayerid ON event_mg_session (sessiontoplayerid);

-----------------------------------------------------------------------------------------
CREATE FUNCTION update_mgsession(p_id bigint, p_step bigint, p_stpid bigint, p_location varchar)
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

-----------------------------------------------------------------------------------------
CREATE TABLE event_mg_level
(
  startid bigint NOT NULL,
  finishid bigint,
  location varchar NOT NULL,
  mgsessionid bigint NOT NULL,
  startstep integer NOT NULL,
  finishstep integer,
  success boolean NOT NULL,
  "level" integer NOT NULL,
  paint integer NOT NULL,
  CONSTRAINT event_mg_level_pkey PRIMARY KEY (startid, location),
  CONSTRAINT event_mg_level_mgsessionid_fkey FOREIGN KEY (mgsessionid, location) REFERENCES event_mg_session (startid, location)
);
ALTER TABLE event_mg_level OWNER TO dbadmin;
GRANT SELECT ON TABLE event_mg_level TO ro;

CREATE INDEX idx_event_mg_level_mgsessionid ON event_mg_level (mgsessionid);

-----------------------------------------------------------------------------------------
CREATE FUNCTION update_mglevel(p_id bigint, p_step bigint, p_stpid bigint, p_success boolean, p_location varchar)
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

-----------------------------------------------------------------------------------------
CREATE TABLE event_mg_ballschanged
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  mgsessionid bigint NOT NULL,
  step integer NOT NULL,
  CONSTRAINT event_mg_ballschanged_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_mg_ballschanged_mgsessionid_fkey FOREIGN KEY (mgsessionid, location) REFERENCES event_mg_session (startid, location)
);
ALTER TABLE event_mg_ballschanged OWNER TO dbadmin;
GRANT SELECT ON TABLE event_mg_ballschanged TO ro;

CREATE INDEX idx_event_mg_ballschanged_mgsessionid ON event_mg_ballschanged (mgsessionid);

-----------------------------------------------------------------------------------------
CREATE TABLE event_mg_boostused
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  mglevelid bigint NOT NULL,
  step integer NOT NULL,
  boostid integer NOT NULL,
  CONSTRAINT event_mg_boostused_pkey PRIMARY KEY (id, location),
  CONSTRAINT event_mg_boostused_mglevelid_fkey FOREIGN KEY (mglevelid, location) REFERENCES event_mg_level (startid, location),
  CONSTRAINT event_mg_boostused_boostid_fkey FOREIGN KEY (boostid) REFERENCES mgboost (id)
);
ALTER TABLE event_mg_boostused OWNER TO dbadmin;
GRANT SELECT ON TABLE event_mg_boostused TO ro;

CREATE INDEX idx_event_mg_boostused_mgsessionid ON event_mg_boostused (mglevelid);

-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------
CREATE TABLE launcherstart
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  hostid character varying,
  version character varying,
  playerid bigint,
  clientip character varying,
  geolocation character varying,
  locale character varying,
  "timestamp" timestamp without time zone,
  datehierarchy integer,
  CONSTRAINT launcherstart_pkey PRIMARY KEY (id, location),
  CONSTRAINT launcherstart_datehierarchy_fkey
      FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE launcherstart OWNER TO dbadmin;
GRANT SELECT ON TABLE launcherstart TO ro;

CREATE INDEX idx_launcherstart_datehierarchy ON launcherstart (datehierarchy);

-----------------------------------------------------------------------------------------
CREATE TABLE launcherdstart
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  hostid character varying,
  package character varying,
  version character varying,
  playerid bigint,
  locale character varying,
  "timestamp" timestamp without time zone,
  datehierarchy integer,
  CONSTRAINT launcherdstart_pkey PRIMARY KEY (id, location),
  CONSTRAINT launcherdstart_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE launcherdstart OWNER TO dbadmin;
GRANT SELECT ON TABLE launcherdstart TO ro;

CREATE INDEX idx_launcherdstart_datehierarchy ON launcherdstart (datehierarchy);

-----------------------------------------------------------------------------------------
CREATE TABLE launcherdend
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  hostid character varying,
  package character varying,
  version character varying,
  playerid bigint,
  status integer NOT NULL,
  locale character varying,
  "timestamp" timestamp without time zone,
  datehierarchy integer,
  CONSTRAINT launcherdend_pkey PRIMARY KEY (id, location),
  CONSTRAINT launcherdend_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE launcherdend OWNER TO dbadmin;
GRANT SELECT ON TABLE launcherdend TO ro;

CREATE INDEX idx_launcherdend_datehierarchy ON launcherdend (datehierarchy);

-----------------------------------------------------------------------------------------
CREATE TABLE launcherevents
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  playerid bigint,
  muid character varying,
  eventflags bigint,
  locale character varying,
  clienttimestamp timestamp,
  servertimestamp timestamp,
  datehierarchy integer,
  CONSTRAINT launcherevents_pkey PRIMARY KEY (id, location),
  CONSTRAINT launcherevents_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE launcherevents OWNER TO dbadmin;
GRANT SELECT ON TABLE launcherevents TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE launcherdaction
(
  id bigint NOT NULL,
  location varchar NOT NULL,
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
  locale character varying,
  clienttimestamp timestamp,
  servertimestamp timestamp,
  serverdatehierarchy integer,
  CONSTRAINT launcherdaction_pkey PRIMARY KEY (id, location),
  CONSTRAINT launcherdaction_serverdatehierarchy_fkey FOREIGN KEY (serverdatehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE launcherdaction OWNER TO dbadmin;
GRANT SELECT ON TABLE launcherdaction TO ro;

CREATE INDEX idx_launcherdaction_action ON launcherdaction (action);
CREATE INDEX idx_launcherdaction_serverdatehierarchy ON launcherdaction (serverdatehierarchy);

-----------------------------------------------------------------------------------------
CREATE TABLE socialregister
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  hostid character varying,
  playerid bigint,
  snid character varying,
  snuid character varying,
  muid character varying,
  "timestamp" timestamp without time zone,
  datehierarchy integer,
  CONSTRAINT socialregister_pkey PRIMARY KEY (id, location),
  CONSTRAINT socialregister_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE socialregister OWNER TO dbadmin;
GRANT SELECT ON TABLE socialregister TO ro;

CREATE INDEX idx_socialregister_datehierarchy ON socialregister (datehierarchy);

-----------------------------------------------------------------------------------------
CREATE TABLE socialjoin
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  playerid bigint,
  snid character varying,
  snuid character varying,
  "timestamp" timestamp without time zone,
  datehierarchy integer,
  CONSTRAINT socialjoin_pkey PRIMARY KEY (id, location),
  CONSTRAINT socialjoin_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE socialjoin OWNER TO dbadmin;
GRANT SELECT ON TABLE socialjoin TO ro;

CREATE INDEX idx_socialjoin_datehierarchy ON socialjoin (datehierarchy);

-----------------------------------------------------------------------------------------
CREATE TABLE socialmerge
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  playerid1 bigint,
  playerid2 bigint,
  "timestamp" timestamp without time zone,
  datehierarchy integer,
  CONSTRAINT socialmerge_pkey PRIMARY KEY (id, location),
  CONSTRAINT socialmerge_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE socialmerge OWNER TO dbadmin;
GRANT SELECT ON TABLE socialmerge TO ro;

CREATE INDEX idx_socialmerge_datehierarchy ON socialmerge (datehierarchy);

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE TABLE gm_useroperation 
(
  id integer NOT NULL,
  type integer NOT NULL,
  player bigint NOT NULL,
  minutes integer NOT NULL,
  points integer,
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

-----------------------------------------------------------------------------------------
CREATE TABLE claim
(
  id integer NOT NULL,
  fromplayer bigint NOT NULL,
  toplayer bigint NOT NULL,
  source integer NOT NULL,
  category integer NOT NULL,
  locale varchar NOT NULL,
  muid varchar,
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

-----------------------------------------------------------------------------------------
CREATE TABLE characterunlock
(
  id integer NOT NULL,
  location varchar NOT NULL,
  playercharacter integer NOT NULL,
  resourcelog bigint,
  "timestamp" timestamp without time zone NOT NULL,
  datehierarchy integer NOT NULL,
  playercharacter_analysisid integer NOT NULL,
  CONSTRAINT characterunlock_pkey PRIMARY KEY (id, location),
  CONSTRAINT characterunlock_playercharacter_fkey FOREIGN KEY (playercharacter, location) REFERENCES playercharacter (id, location),
  CONSTRAINT characterunlock_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id),
  CONSTRAINT characterunlock_playercharacter_analysisid_fkey FOREIGN KEY (playercharacter_analysisid) REFERENCES playercharacter (analysisid)
);
ALTER TABLE characterunlock OWNER TO dbadmin;
GRANT SELECT ON TABLE characterunlock TO ro;

CREATE INDEX idx_characterunlock_datehierarchy ON characterunlock (datehierarchy);
CREATE INDEX idx_characterunlock_playercharacter_analysisid ON characterunlock (playercharacter_analysisid);

-----------------------------------------------------------------------------------------
CREATE TABLE movetobath
(
  id integer NOT NULL,
  location varchar NOT NULL,
  playercharacter integer NOT NULL,
  resourcelog bigint,
  minutes integer NOT NULL,
  "timestamp" timestamp without time zone NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT movetobath_pkey PRIMARY KEY (id, location),
  CONSTRAINT movetobath_playercharacter_fkey FOREIGN KEY (playercharacter, location) REFERENCES playercharacter (id, location),
  CONSTRAINT movetobath_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE movetobath OWNER TO dbadmin;
GRANT SELECT ON TABLE movetobath TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE ignoreadd
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  player bigint NOT NULL,
  ignoredplayer bigint NOT NULL,
  reason character varying,
  "timestamp" timestamp without time zone NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT ignoreadd_pkey PRIMARY KEY (id, location),
  CONSTRAINT ignoreadd_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT ignoreadd_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE ignoreadd OWNER TO dbadmin;
GRANT SELECT ON TABLE ignoreadd TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE ignoreremove
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  player bigint NOT NULL,
  ignoredplayer bigint NOT NULL,
  "timestamp" timestamp without time zone NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT ignoreremove_pkey PRIMARY KEY (id, location),
  CONSTRAINT ignoreremove_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT ignoreremove_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE ignoreremove OWNER TO dbadmin;
GRANT SELECT ON TABLE ignoreremove TO ro;

-----------------------------------------------------------------------------------------
CREATE TABLE runeroll
(
  id bigint NOT NULL,
  player bigint NOT NULL,
  source varchar NOT NULL,
  persistentid bigint NOT NULL,
  rune integer NOT NULL,
  runescountold integer NOT NULL,
  runescountnew integer NOT NULL,
  timestamp timestamp NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT runeroll_pkey PRIMARY KEY (id),
  CONSTRAINT runeroll_player_fkey FOREIGN KEY (player) REFERENCES player (id),
  CONSTRAINT runeroll_rune_fkey FOREIGN KEY (rune) REFERENCES rune (id),
  CONSTRAINT runeroll_datehierarchy_fkey FOREIGN KEY (datehierarchy) REFERENCES datehierarchy (id)
);
ALTER TABLE runeroll OWNER TO dbadmin;
GRANT SELECT ON TABLE runeroll TO ro;

CREATE INDEX idx_runeroll_persistentid ON runeroll (persistentid);
CREATE INDEX idx_runeroll_player ON runeroll (player);
CREATE INDEX idx_runeroll_datehierarchy ON runeroll (datehierarchy);

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
      CONSTRAINT gwevents_pkey PRIMARY KEY (id)
    );
    ALTER TABLE gwevents OWNER TO dbadmin;
    GRANT SELECT ON TABLE gwevents TO ro;

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE TABLE talentlog
(
  id bigint NOT NULL,
  operation varchar NOT NULL,
  data varchar,
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

-----------------------------------------------------------------------------------------
CREATE TABLE talentjoinsession
(
  id bigint NOT NULL,
  player bigint NOT NULL,
  character integer NOT NULL,
  sessiontoplayer integer NOT NULL,
  sessiontoplayer_location varchar NOT NULL,
  sessiontoplayer_analysisid integer NOT NULL,
  talent integer NOT NULL,
  datehierarchy integer NOT NULL,
  CONSTRAINT talentjoinsession_pkey PRIMARY KEY (id),
  CONSTRAINT talentjoinsession_sessiontoplayer_fkey FOREIGN KEY (sessiontoplayer, sessiontoplayer_location) REFERENCES sessiontoplayer (id, location),
  CONSTRAINT talentjoinsession_sessiontoplayer_analysisid_fkey FOREIGN KEY (sessiontoplayer_analysisid) REFERENCES sessiontoplayer (analysisid),
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

SELECT partitions_check('talentjoinsession');

CREATE TRIGGER tr_talentjoinsession_partition BEFORE INSERT ON talentjoinsession
  FOR EACH ROW EXECUTE PROCEDURE talentjoinsession_insert_trigger();

-----------------------------------------------------------------------------------------
CREATE TABLE guildbuffsession
(
  id bigint NOT NULL,
  type varchar NOT NULL,
  player bigint NOT NULL,
  persistentid bigint NOT NULL,
  sessiontoplayer integer NOT NULL,
  sessiontoplayer_location varchar NOT NULL,
  guildbuff integer NOT NULL,
  guildwareventpass integer NOT NULL DEFAULT -1,
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

SELECT partitions_check('guildbuffsession');

CREATE TRIGGER tr_guildbuffsession_partition BEFORE INSERT ON guildbuffsession
  FOR EACH ROW EXECUTE PROCEDURE guildbuffsession_insert_trigger();

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE TABLE tmp_talentswitchedoff
(
  id bigint NOT NULL,
  location varchar NOT NULL,
  sessiontoplayerid integer NOT NULL,
  step integer NOT NULL,
  x real NOT NULL,
  y real NOT NULL,
  characterid integer,
  talentid integer,
  CONSTRAINT talentswitchedoff_pkey PRIMARY KEY (id, location)
);
ALTER TABLE tmp_talentswitchedoff OWNER TO dbadmin;

-----------------------------------------------------------------------------------------
CREATE TABLE clientping
(
  id bigint NOT NULL,
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
CREATE TABLE playercharacter_ratingbypush
(
  playercharacter integer NOT NULL,
  location varchar NOT NULL,
  push character varying NOT NULL,
  rating integer NOT NULL,
  reliability integer NOT NULL,
  force real NOT NULL,
  CONSTRAINT playercharacter_ratingbypush_unique UNIQUE (playercharacter, push),
  CONSTRAINT playercharacter_ratingbypush_playercharacter FOREIGN KEY (playercharacter, location) REFERENCES playercharacter (id, location)
);
ALTER TABLE playercharacter_ratingbypush OWNER TO dbadmin;
GRANT SELECT ON TABLE playercharacter_ratingbypush TO ro;

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
---------------- utility objects for data aggregations ----------------------------------

CREATE TABLE sys_aggregation_ranges
(
  tablename character varying NOT NULL,
  location varchar NOT NULL,
  lastid bigint,
  CONSTRAINT sys_aggregation_ranges_pkey PRIMARY KEY (tablename, location)
);
ALTER TABLE sys_aggregation_ranges OWNER to dbadmin;
INSERT INTO sys_aggregation_ranges VALUES ('socialsession', '', 0);
INSERT INTO sys_aggregation_ranges VALUES ('event_damage', 'ru0', 0);
INSERT INTO sys_aggregation_ranges VALUES ('event_naftaincome', 'ru0', 0);
INSERT INTO sys_aggregation_ranges VALUES ('event_talentused', 'ru0', 0);
INSERT INTO sys_aggregation_ranges VALUES ('resourcelog', 'ru0', 0);
INSERT INTO sys_aggregation_ranges VALUES ('launcherevents', '', 0);

-----------------------------------------------------------------------------------------
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
    RETURN;
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

-----------------------------------------------------------------------------------------
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
    RETURN;
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

-----------------------------------------------------------------------------------------
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
    RETURN;
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


-----------------------------------------------------------------------------------------
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
    RETURN;
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
             SUM(goldchange) gld, SUM(silverchange) slv, SUM(perlchange) prl, SUM(redperlchange) rpl, SUM(populationchange) ppl,
             SUM(resource1change) rs1, SUM(resource2change) rs2, SUM(resource3change) rs3, SUM(shardchange) shd, currencychange, SUM(currencychangevalue) crncval
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
            redperlchange = redperlchange + r.rpl,
            populationchange = populationchange + r.ppl,
            resource1change = resource1change + r.rs1,
            resource2change = resource2change + r.rs2,
            resource3change = resource3change + r.rs3,
            shardchange = shardchange + r.shd,
            currencychange = r.currencychange,
            currencychangevalue = currencychangevalue + r.crncval
        WHERE datehierarchy = r.datehierarchy
          AND location = r.location
          AND source = r.source
          AND ((buildingname is null AND r.buildingname is null) OR buildingname = r.buildingname)
          AND gain = r.gain;
      ELSE
        INSERT INTO resourcelog_agg_source (datehierarchy, location, source, buildingname, gain, goldchange, silverchange, perlchange, redperlchange, populationchange, resource1change, resource2change, resource3change, shardchange, currencychange, currencychangevalue)
        VALUES (r.datehierarchy, r.location, r.source, r.buildingname, r.gain, r.gld, r.slv, r.prl, r.rpl, r.ppl, r.rs1, r.rs2, r.rs3, r.shd, r.currencychange, r.crncval);
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


-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
CREATE TABLE sys_cluster_info (
  name varchar NOT NULL,
  ipmask varchar NOT NULL
);
ALTER TABLE sys_cluster_info OWNER TO dbadmin;
GRANT SELECT ON TABLE sys_cluster_info TO ro;


-----------------------------------------------------------------------------------------
CREATE TABLE sys_event_exceedingsteptime_agg_report_ids
(
  datehierarchy integer NOT NULL,
  lastid bigint NOT NULL,
  count integer NOT NULL,
  CONSTRAINT sys_event_exceedingsteptime_agg_report_ids_pkey PRIMARY KEY (datehierarchy)
);
ALTER TABLE sys_event_exceedingsteptime_agg_report_ids OWNER TO dbadmin;


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------
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
  lastid bigint;
  diff float;
begin
  raise notice '% script started', clock_timestamp();
  perform partitions_check('event_disconnect_agg_report');

  select count(*), max(id) into evt, lastid
  from event_disconnect_agg_report 
  where datehierarchy = dh;

  if (evt > 0)
  then
    raise notice '% executing check...', clock_timestamp();
    
    select count(*)::float/evt into diff
    from event_disconnect 
    where datehierarchy = dh
      and id > lastid;

    raise notice '% check aggregated data for % (evt = %, diff = %)', clock_timestamp(), dh, evt, diff;
    if (diff < 0.05) then
      raise notice '% aggregated data is OK', clock_timestamp();
      return;
    end if;
  end if;

  raise notice '% delete aggregated data %', clock_timestamp(), dh;

  delete from event_disconnect_agg_report
  where datehierarchy = dh;

  raise notice '% building aggregated data for %', clock_timestamp(), dh;

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
  order by e.id;

  raise notice '% update first leaver', clock_timestamp();
  update event_disconnect_agg_report r1
  set firstleaver = not exists (
    select 1 from event_disconnect_agg_report r2
    where r2.gsid = r1.gsid
      and r2.datehierarchy = r1.datehierarchy
      and ( r2.timestamp < r1.timestamp
            or (r2.timestamp = r1.timestamp and r2.id < r1.id) ) )
  where r1.datehierarchy = dh;

  raise notice '% update client event', clock_timestamp();
  update event_disconnect_agg_report r
  set offid = o.id, offtype = o.code
  from offlineevent o
  where r.datehierarchy = dh
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
ALTER FUNCTION aggregate_event_disconnect(integer) OWNER TO dbadmin;


-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------
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



-----------------------------------------------------------------------------------------
-------- tables for import data from billing --------------------------------------------

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

-----------------------------------------------------------------------------------------
---------- PENTAHO OBJECTS --------------------------------------------------------------

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

-----------------------------------------------------------------------------------------

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


-----------------------------------------------------------------------------------------
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


-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------
CREATE FUNCTION dbversion()
  RETURNS integer AS
$BODY$
begin
  return 163;
end;
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION dbversion() OWNER TO dbadmin;
GRANT EXECUTE ON FUNCTION dbversion() TO public;

-----------------------------------------------------------------------------------------
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
