-- Sequence: gm_role_roleid_sequence
CREATE SEQUENCE gm_role_roleid_sequence;
ALTER TABLE gm_role_roleid_sequence OWNER TO gmadmin;

-- Table: gm_roles
CREATE TABLE gm_roles
(
  roleid integer NOT NULL DEFAULT nextval('gm_role_roleid_sequence'::regclass),
  rolename varchar,
  description varchar,
  locale varchar,
  muid varchar,
  CONSTRAINT gm_role_pkey PRIMARY KEY (roleid),
  CONSTRAINT gm_role_rolename_key UNIQUE (rolename)
);
ALTER TABLE gm_roles OWNER TO gmadmin;


-- Sequence: gm_user_userid_sequence
CREATE SEQUENCE gm_user_userid_sequence;
ALTER TABLE gm_user_userid_sequence OWNER TO gmadmin;

-- Table: gm_users
CREATE TABLE gm_users
(
  userid integer NOT NULL DEFAULT nextval('gm_user_userid_sequence'::regclass),
  username character varying NOT NULL,
  fullname character varying,
  email character varying,
  superuser boolean NOT NULL default false,
  CONSTRAINT gm_user_pkey PRIMARY KEY (userid),
  CONSTRAINT gm_user_username_key UNIQUE (username)
);
ALTER TABLE gm_users OWNER TO gmadmin;


-- Table: gm_usermembership
CREATE TABLE gm_usermembership
(
  gmuser integer NOT NULL,
  "password" character varying NOT NULL,
  createdate timestamp without time zone,
  lastlogindate timestamp without time zone,
  CONSTRAINT gm_usermembership_pkey PRIMARY KEY (gmuser),
  CONSTRAINT gm_usermembership_gmuser_fkey FOREIGN KEY (gmuser)
      REFERENCES gm_users (userid) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
);
ALTER TABLE gm_usermembership OWNER TO gmadmin;


-- Sequence: gm_users_in_roles_id_sequence
CREATE SEQUENCE gm_users_in_roles_id_sequence;
ALTER TABLE gm_users_in_roles_id_sequence OWNER TO gmadmin;

-- Table: gm_users_in_roles
CREATE TABLE gm_users_in_roles
(
  id integer NOT NULL DEFAULT nextval('gm_users_in_roles_id_sequence'::regclass),
  userid integer NOT NULL,
  roleid integer,
  CONSTRAINT gm_users_in_roles_pkey PRIMARY KEY (id),
  CONSTRAINT gm_users_in_roles_roleid_fkey FOREIGN KEY (roleid)
      REFERENCES gm_roles (roleid) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT gm_users_in_roles_userid_fkey FOREIGN KEY (userid)
      REFERENCES gm_users (userid) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT gm_users_in_roles_userid_key UNIQUE (userid, roleid)
);
ALTER TABLE gm_users_in_roles OWNER TO gmadmin;


-- Sequence: gm_permissions_permissionid_sequence
CREATE SEQUENCE gm_permissions_permissionid_sequence;
ALTER TABLE gm_permissions_permissionid_sequence OWNER TO gmadmin;

-- Table: gm_permissions
CREATE TABLE gm_permissions
(
  permissionid integer NOT NULL DEFAULT nextval('gm_permissions_permissionid_sequence'::regclass),
  permissionname character varying,
  description character varying,
  CONSTRAINT gm_permissions_pkey PRIMARY KEY (permissionid),
  CONSTRAINT gm_permissions_permissionname_key UNIQUE (permissionname)
);
ALTER TABLE gm_permissions OWNER TO gmadmin;


-- Sequence: gm_roles_has_permissions_id_sequence
CREATE SEQUENCE gm_roles_has_permissions_id_sequence;
ALTER TABLE gm_roles_has_permissions_id_sequence OWNER TO gmadmin;

-- Table: gm_roles_has_permissions
CREATE TABLE gm_roles_has_permissions
(
  id integer NOT NULL DEFAULT nextval('gm_roles_has_permissions_id_sequence'::regclass),
  roleid integer,
  permissionid integer,
  CONSTRAINT gm_roles_has_permissions_pkey PRIMARY KEY (id),
  CONSTRAINT gm_roles_has_permissions_permissionid_fkey FOREIGN KEY (permissionid)
      REFERENCES gm_permissions (permissionid) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION,
  CONSTRAINT gm_roles_has_permissions_roleid_fkey FOREIGN KEY (roleid)
      REFERENCES gm_roles (roleid) MATCH SIMPLE
      ON UPDATE NO ACTION ON DELETE NO ACTION
);
ALTER TABLE gm_roles_has_permissions OWNER TO gmadmin;
