-----------------------------------------------------------------------------------------
DO $$ 
BEGIN
  IF NOT EXISTS (SELECT 1 FROM pg_language WHERE lanname = 'plpgsql') THEN
    CREATE LANGUAGE plpgsql;
  END IF;
END $$;

-----------------------------------------------------------------------------------------
CREATE TABLE assist
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  victimid bigint NOT NULL,
  killerid bigint,
  killercreatureid integer,  
  CONSTRAINT assist_pkey PRIMARY KEY (id)
);
ALTER TABLE assist OWNER TO dbadminlogs;
GRANT SELECT ON TABLE assist TO ro;
GRANT SELECT, INSERT ON TABLE assist TO rw;

ALTER TABLE assist_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE assist_id_seq TO ro;
GRANT ALL ON TABLE assist_id_seq TO rw;

-- Name: buildingdestroyed; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE buildingdestroyed
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  buildingid integer,
  destroyerid bigint,
  destroyercreatureid integer,
  CONSTRAINT buildingdestroyed_pkey PRIMARY KEY (id)
);
ALTER TABLE buildingdestroyed OWNER TO dbadminlogs;
GRANT SELECT ON TABLE buildingdestroyed TO ro;
GRANT SELECT, INSERT ON TABLE buildingdestroyed TO rw;

ALTER TABLE buildingdestroyed_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE buildingdestroyed_id_seq TO ro;
GRANT ALL ON TABLE buildingdestroyed_id_seq TO rw;

-- Name: consumablebought; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE consumablebought
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  consumableid integer NOT NULL,
  nafta integer NOT NULL,
  CONSTRAINT consumablebought_pkey PRIMARY KEY (id)
);
ALTER TABLE consumablebought OWNER TO dbadminlogs;
GRANT SELECT ON TABLE consumablebought TO ro;
GRANT SELECT, INSERT ON TABLE consumablebought TO rw;

ALTER TABLE consumablebought_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE consumablebought_id_seq TO ro;
GRANT ALL ON TABLE consumablebought_id_seq TO rw;

-- Name: consumableused; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE consumableused
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  consumableid integer NOT NULL,
  CONSTRAINT consumableused_pkey PRIMARY KEY (id)
);
ALTER TABLE consumableused OWNER TO dbadminlogs;
GRANT SELECT ON TABLE consumableused TO ro;
GRANT SELECT, INSERT ON TABLE consumableused TO rw;

ALTER TABLE consumableused_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE consumableused_id_seq TO ro;
GRANT ALL ON TABLE consumableused_id_seq TO rw;

-- Name: cheatused; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE cheatused
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  command character varying(255),
  CONSTRAINT cheatused_pkey PRIMARY KEY (id)
);
ALTER TABLE cheatused OWNER TO dbadminlogs;
GRANT SELECT ON TABLE cheatused TO ro;
GRANT SELECT, INSERT ON TABLE cheatused TO rw;

ALTER TABLE cheatused_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE cheatused_id_seq TO ro;
GRANT ALL ON TABLE cheatused_id_seq TO rw;

-- Name: death; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE death
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  killerid bigint,
  killercreatureid integer,
  CONSTRAINT death_pkey PRIMARY KEY (id)
);
ALTER TABLE death OWNER TO dbadminlogs;
GRANT SELECT ON TABLE death TO ro;
GRANT SELECT, INSERT ON TABLE death TO rw;

ALTER TABLE death_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE death_id_seq TO ro;
GRANT ALL ON TABLE death_id_seq TO rw;

-- Name: achievement; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE achievement
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  achievementid integer NOT NULL,
  CONSTRAINT achievement_pkey PRIMARY KEY (id)
);
ALTER TABLE achievement OWNER TO dbadminlogs;
GRANT SELECT ON TABLE achievement TO ro;
GRANT SELECT, INSERT ON TABLE achievement TO rw;

ALTER TABLE achievement_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE achievement_id_seq TO ro;
GRANT ALL ON TABLE achievement_id_seq TO rw;

-- Name: flag; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE flag
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  raised boolean NOT NULL,
  faction integer NOT NULL,
  road integer NOT NULL,
  segment integer NOT NULL,
  activatorid bigint,
  activatorcreatureid integer,
  CONSTRAINT flag_pkey PRIMARY KEY (id)
);
ALTER TABLE flag OWNER TO dbadminlogs;
GRANT SELECT ON TABLE flag TO ro;
GRANT SELECT, INSERT ON TABLE flag TO rw;

GRANT ALL ON TABLE flag_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE flag_id_seq TO ro;
GRANT ALL ON TABLE flag_id_seq TO rw;

-- Name: impulsivebuffused; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE impulsivebuffused
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  impulsivebuffid integer NOT NULL,
  CONSTRAINT impulsivebuffused_pkey PRIMARY KEY (id)
);
ALTER TABLE impulsivebuffused OWNER TO dbadminlogs;
GRANT SELECT ON TABLE impulsivebuffused TO ro;
GRANT SELECT, INSERT ON TABLE impulsivebuffused TO rw;

GRANT ALL ON TABLE impulsivebuffused_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE impulsivebuffused_id_seq TO ro;
GRANT ALL ON TABLE impulsivebuffused_id_seq TO rw;

-- Name: impulsivebuffsuggested; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE impulsivebuffsuggested
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  impulsivebuffid integer NOT NULL,
  CONSTRAINT impulsivebuffsuggested_pkey PRIMARY KEY (id)
);
ALTER TABLE impulsivebuffsuggested OWNER TO dbadminlogs;
GRANT SELECT ON TABLE impulsivebuffsuggested TO ro;
GRANT SELECT, INSERT ON TABLE impulsivebuffsuggested TO rw;

ALTER TABLE impulsivebuffsuggested_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE impulsivebuffsuggested_id_seq TO ro;
GRANT ALL ON TABLE impulsivebuffsuggested_id_seq TO rw;

-- Name: kill; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE kill
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  victimid bigint,
  victimcreatureid integer,
  CONSTRAINT kill_pkey PRIMARY KEY (id)
);
ALTER TABLE kill OWNER TO dbadminlogs;
GRANT SELECT ON TABLE kill TO ro;
GRANT SELECT, INSERT ON TABLE kill TO rw;

GRANT ALL ON TABLE kill_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE kill_id_seq TO ro;
GRANT ALL ON TABLE kill_id_seq TO rw;

-- Name: levelup; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE levelup
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  "level" integer NOT NULL,
  CONSTRAINT levelup_pkey PRIMARY KEY (id)
);
ALTER TABLE levelup OWNER TO dbadminlogs;
GRANT SELECT ON TABLE levelup TO ro;
GRANT SELECT, INSERT ON TABLE levelup TO rw;

GRANT ALL ON TABLE levelup_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE levelup_id_seq TO ro;
GRANT ALL ON TABLE levelup_id_seq TO rw;

-- Name: naftaincome; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE naftaincome
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  incomefrom integer,
  naftaForKill integer,
  naftaSpecForKill integer,
  teamNaftaForKill integer,
  nafta integer,
  CONSTRAINT naftaincome_pkey PRIMARY KEY (id)
);
ALTER TABLE naftaincome OWNER TO dbadminlogs;
GRANT SELECT ON TABLE naftaincome TO ro;
GRANT SELECT, INSERT ON TABLE naftaincome TO rw;

GRANT ALL ON TABLE naftaincome_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE naftaincome_id_seq TO ro;
GRANT ALL ON TABLE naftaincome_id_seq TO rw;

-- Name: ressurection; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE ressurection
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  CONSTRAINT ressurection_pkey PRIMARY KEY (id)
);
ALTER TABLE ressurection OWNER TO dbadminlogs;
GRANT SELECT ON TABLE ressurection TO ro;
GRANT SELECT, INSERT ON TABLE ressurection TO rw;

ALTER TABLE ressurection_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE ressurection_id_seq TO ro;
GRANT ALL ON TABLE ressurection_id_seq TO rw;

-----------------------------------------------------------------------------------------
CREATE TABLE scriptevent
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
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

-----------------------------------------------------------------------------------------
CREATE TABLE talentunlocked
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  talentid integer NOT NULL,
  nafta integer NOT NULL,
  CONSTRAINT talentunlocked_pkey PRIMARY KEY (id)
);
ALTER TABLE talentunlocked OWNER TO dbadminlogs;
GRANT SELECT ON TABLE talentunlocked TO ro;
GRANT SELECT, INSERT ON TABLE talentunlocked TO rw;

GRANT ALL ON TABLE talentunlocked_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE talentunlocked_id_seq TO ro;
GRANT ALL ON TABLE talentunlocked_id_seq TO rw;

-- Name: talentused; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE talentused
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  talentid integer NOT NULL,
  CONSTRAINT talentused_pkey PRIMARY KEY (id)
);
ALTER TABLE talentused OWNER TO dbadminlogs;
GRANT SELECT ON TABLE talentused TO ro;
GRANT SELECT, INSERT ON TABLE talentused TO rw;

GRANT ALL ON TABLE talentused_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE talentused_id_seq TO ro;
GRANT ALL ON TABLE talentused_id_seq TO rw;

-- Name: talentswitchedoff; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE talentswitchedoff
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  talentid integer NOT NULL,
  CONSTRAINT talentswitchedoff_pkey PRIMARY KEY (id)
);
ALTER TABLE talentswitchedoff OWNER TO dbadminlogs;
GRANT SELECT ON TABLE talentswitchedoff TO ro;
GRANT SELECT, INSERT ON TABLE talentswitchedoff TO rw;

GRANT ALL ON TABLE talentswitchedoff_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE talentswitchedoff_id_seq TO ro;
GRANT ALL ON TABLE talentswitchedoff_id_seq TO rw;

-- Name: timeslice; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE timeslice
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  slice integer NOT NULL,
  "level" integer NOT NULL,
  currentnafta integer,  
  totalnafta integer NOT NULL,
  salarynafta integer,
  CONSTRAINT timeslice_pkey PRIMARY KEY (id)
);
ALTER TABLE timeslice OWNER TO dbadminlogs;
GRANT SELECT ON TABLE timeslice TO ro;
GRANT SELECT, INSERT ON TABLE timeslice TO rw;

GRANT ALL ON TABLE timeslice_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE timeslice_id_seq TO ro;
GRANT ALL ON TABLE timeslice_id_seq TO rw;

-- Name: mg2started; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE mg2started
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  CONSTRAINT mg2started_pkey PRIMARY KEY (id)
);
ALTER TABLE mg2started OWNER TO dbadminlogs;
GRANT SELECT ON TABLE mg2started TO ro;
GRANT SELECT, INSERT ON TABLE mg2started TO rw;

GRANT ALL ON TABLE mg2started_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE mg2started_id_seq TO ro;
GRANT ALL ON TABLE mg2started_id_seq TO rw;

-- Name: mg2exit; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE mg2exit
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  CONSTRAINT mg2exit_pkey PRIMARY KEY (id)
);
ALTER TABLE mg2exit OWNER TO dbadminlogs;
GRANT SELECT ON TABLE mg2exit TO ro;
GRANT SELECT, INSERT ON TABLE mg2exit TO rw;

GRANT ALL ON TABLE mg2exit_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE mg2exit_id_seq TO ro;
GRANT ALL ON TABLE mg2exit_id_seq TO rw;

-- Name: mg2levelstarted; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE mg2levelstarted
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,

  level integer NOT NULL,
  paint integer NOT NULL,
  
  CONSTRAINT mg2levelstarted_pkey PRIMARY KEY (id)
);
ALTER TABLE mg2levelstarted OWNER TO dbadminlogs;
GRANT SELECT ON TABLE mg2levelstarted TO ro;
GRANT SELECT, INSERT ON TABLE mg2levelstarted TO rw;

GRANT ALL ON TABLE mg2levelstarted_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE mg2levelstarted_id_seq TO ro;
GRANT ALL ON TABLE mg2levelstarted_id_seq TO rw;

-- Name: mg2levelwon; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE mg2levelwon
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,

  level integer NOT NULL,
  paint integer NOT NULL,
  
  CONSTRAINT mg2levelwon_pkey PRIMARY KEY (id)
);
ALTER TABLE mg2levelwon OWNER TO dbadminlogs;
GRANT SELECT ON TABLE mg2levelwon TO ro;
GRANT SELECT, INSERT ON TABLE mg2levelwon TO rw;

GRANT ALL ON TABLE mg2levelwon_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE mg2levelwon_id_seq TO ro;
GRANT ALL ON TABLE mg2levelwon_id_seq TO rw;

-- Name: mg2levelfailed; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE mg2levelfailed
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,

  level integer NOT NULL,
  paint integer NOT NULL,
  
  CONSTRAINT mg2levelfailed_pkey PRIMARY KEY (id)
);
ALTER TABLE mg2levelfailed OWNER TO dbadminlogs;
GRANT SELECT ON TABLE mg2levelfailed TO ro;
GRANT SELECT, INSERT ON TABLE mg2levelfailed TO rw;

GRANT ALL ON TABLE mg2levelfailed_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE mg2levelfailed_id_seq TO ro;
GRANT ALL ON TABLE mg2levelfailed_id_seq TO rw;

-- Name: mg2ballschanged; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE mg2ballschanged
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,
  
  CONSTRAINT mg2ballschanged_pkey PRIMARY KEY (id)
);
ALTER TABLE mg2ballschanged OWNER TO dbadminlogs;
GRANT SELECT ON TABLE mg2ballschanged TO ro;
GRANT SELECT, INSERT ON TABLE mg2ballschanged TO rw;

GRANT ALL ON TABLE mg2ballschanged_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE mg2ballschanged_id_seq TO ro;
GRANT ALL ON TABLE mg2ballschanged_id_seq TO rw;

-- Name: mg2boostused; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE mg2boostused
(
  id bigserial NOT NULL, sessionid bigint NOT NULL, step integer NOT NULL, x real NOT NULL, y real NOT NULL, playerid bigint NOT NULL,

  boostid integer NOT NULL,
  
  CONSTRAINT mg2boostused_pkey PRIMARY KEY (id)
);
ALTER TABLE mg2boostused OWNER TO dbadminlogs;
GRANT SELECT ON TABLE mg2boostused TO ro;
GRANT SELECT, INSERT ON TABLE mg2boostused TO rw;

ALTER TABLE mg2boostused_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE mg2boostused_id_seq TO ro;
GRANT ALL ON TABLE mg2boostused_id_seq TO rw;

-- Name: damage; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE damage
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
  step integer NOT NULL,
  playerid bigint NOT NULL,
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
GRANT SELECT ON TABLE damage TO ro;
GRANT SELECT, INSERT ON TABLE damage TO rw;

GRANT ALL ON TABLE damage_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE damage_id_seq TO ro;
GRANT ALL ON TABLE damage_id_seq TO rw;

-- Name: debugvar; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE debugvar
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
  step integer NOT NULL,
  eventtime timestamp without time zone,
  playerid bigint NOT NULL,
  name character varying(255) NOT NULL,
  value character varying(255) NOT NULL,

  CONSTRAINT debugvar_pkey PRIMARY KEY (id)
);
ALTER TABLE debugvar OWNER TO dbadminlogs;
GRANT SELECT ON TABLE debugvar TO ro;
GRANT SELECT, INSERT ON TABLE debugvar TO rw;

GRANT ALL ON TABLE debugvar_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE debugvar_id_seq TO ro;
GRANT ALL ON TABLE debugvar_id_seq TO rw;

-----------------------------------------------------------------------------------------
CREATE TABLE exceedingserversteptime
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
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

-----------------------------------------------------------------------------------------
CREATE TABLE exceedingsteptime
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
  playerid bigint NOT NULL,
  typeid integer NOT NULL,
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
  
  CONSTRAINT exceedingsteptime_pkey PRIMARY KEY (id)
);
ALTER TABLE exceedingsteptime OWNER TO dbadminlogs;
GRANT SELECT ON TABLE exceedingsteptime TO ro;
GRANT SELECT, INSERT ON TABLE exceedingsteptime TO rw;

GRANT ALL ON TABLE exceedingsteptime_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE exceedingsteptime_id_seq TO ro;
GRANT ALL ON TABLE exceedingsteptime_id_seq TO rw;

-- Name: exceedingpingtime; Type: TABLE; Schema: public; Owner: dbadminlogs; Tablespace: 

CREATE TABLE exceedingpingtime
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
  playerid bigint NOT NULL,
  typeid integer NOT NULL,
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
  
  CONSTRAINT exceedingpingtime_pkey PRIMARY KEY (id)
);
ALTER TABLE exceedingpingtime OWNER TO dbadminlogs;
GRANT SELECT ON TABLE exceedingpingtime TO ro;
GRANT SELECT, INSERT ON TABLE exceedingpingtime TO rw;

GRANT ALL ON TABLE exceedingpingtime_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE exceedingpingtime_id_seq TO ro;
GRANT ALL ON TABLE exceedingpingtime_id_seq TO rw;

-----------------------------------------------------------------------------------------
CREATE TABLE offlineevent
(
  id bigserial NOT NULL,
  playerid bigint NOT NULL,
  persistentid bigint NOT NULL,
  code int NOT NULL,
  auxdata bigint NOT NULL,
  timestamp timestamp NOT NULL,
  CONSTRAINT offlineevent_pkey PRIMARY KEY (id)
);
ALTER TABLE offlineevent OWNER TO dbadminlogs;
GRANT SELECT ON TABLE offlineevent TO ro;
GRANT SELECT, INSERT ON TABLE offlineevent TO rw;

GRANT ALL ON TABLE offlineevent_id_seq TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE offlineevent_id_seq TO ro;
GRANT ALL ON TABLE offlineevent_id_seq TO rw;

-----------------------------------------------------------------------------------------
CREATE TABLE disconnect
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
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

-----------------------------------------------------------------------------------------
CREATE TABLE reconnect
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
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

-----------------------------------------------------------------------------------------
CREATE TABLE gstraffic
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
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

-----------------------------------------------------------------------------------------
CREATE TABLE cheat
(
  id bigserial NOT NULL,
  sessionid bigint NOT NULL,
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

-- Table: ignoreadd

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

-- Table: ignoreadd

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

-----------------------------------------------------------------------------------------
CREATE TABLE launcherstart
(
  id bigserial NOT NULL,
  hostid character varying,
  version character varying,
  playerid bigint,
  clientip character varying,
  geolocation character varying,
  locale character varying,
  "timestamp" timestamp without time zone,
  CONSTRAINT launcherstart_pkey PRIMARY KEY (id)
);
ALTER TABLE launcherstart OWNER TO dbadminlogs;
GRANT SELECT ON TABLE launcherstart TO ro;
GRANT SELECT, INSERT ON TABLE launcherstart TO rw;
ALTER TABLE launcherstart_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE launcherstart_id_seq TO ro;
GRANT ALL ON TABLE launcherstart_id_seq TO rw;

-----------------------------------------------------------------------------------------
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
  locale character varying,
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

-----------------------------------------------------------------------------------------
CREATE TABLE launcherevents
(
  id bigserial NOT NULL,
  playerid bigint,
  muid character varying,
  eventflags bigint,
  locale character varying,
  clienttimestamp timestamp,
  servertimestamp timestamp,
  CONSTRAINT launcherevents_pkey PRIMARY KEY (id)
);
ALTER TABLE launcherevents OWNER TO dbadminlogs;
GRANT SELECT ON TABLE launcherevents TO ro;
GRANT SELECT, INSERT ON TABLE launcherevents TO rw;
ALTER TABLE launcherevents_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE launcherevents_id_seq TO ro;
GRANT ALL ON TABLE launcherevents_id_seq TO rw;

-----------------------------------------------------------------------------------------
CREATE TABLE socialregister
(
  id bigserial NOT NULL,
  hostid character varying,
  playerid bigint,
  snid character varying,
  snuid character varying,
  muid character varying,
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

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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

-----------------------------------------------------------------------------------------
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
    CONSTRAINT shopreroll_pkey PRIMARY KEY (id)
);
ALTER TABLE shopreroll OWNER TO dbadminlogs;
GRANT SELECT ON TABLE shopreroll TO ro;
GRANT SELECT, INSERT ON TABLE shopreroll TO rw;
ALTER TABLE shopreroll_id_seq OWNER TO dbadminlogs;
GRANT SELECT, USAGE ON TABLE shopreroll_id_seq TO ro;
GRANT ALL ON TABLE shopreroll_id_seq TO rw;

-----------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------
CREATE SCHEMA etl AUTHORIZATION dbadminlogs;
GRANT ALL ON SCHEMA etl TO ro;
GRANT ALL ON SCHEMA etl TO rw;

-----------------------------------------------------------------------------------------
CREATE FUNCTION dbversion()
  RETURNS integer AS
$BODY$
begin
  return 47;
end;
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;
ALTER FUNCTION dbversion() OWNER TO dbadminlogs;
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
ALTER FUNCTION increment_version_to(integer) OWNER TO dbadminlogs;
GRANT EXECUTE ON FUNCTION increment_version_to(integer) TO public;
