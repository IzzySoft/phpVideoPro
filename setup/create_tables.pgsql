# ========================================================
# Database for phpVideoPro
# ========================================================

# --------------------------------------------------------
#
# Table structure for table 'actors'
#

CREATE TABLE actors (
   id serial,
   name varchar(30),
   firstname varchar(30),
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'cass'
#

CREATE TABLE cass (
   id int NOT NULL,
   mtype_id int DEFAULT 1,
   type int,
   free int,
   PRIMARY KEY (id,mtype_id)
);


# --------------------------------------------------------
#
# Table structure for table 'cat'
#

CREATE TABLE cat (
   id serial,
   name varchar(30) UNIQUE,
   PRIMARY KEY (id)
);


# --------------------------------------------------------
#
# Table structure for table 'colors'
#

CREATE TABLE colors (
   id serial,
   name varchar(30),
   sname varchar(5) UNIQUE,
   PRIMARY KEY (id)
);


# --------------------------------------------------------
#
# Table structure for table 'directors'
#

CREATE TABLE directors (
   id serial,
   name varchar(30),
   firstname varchar(30),
   PRIMARY KEY (id)
);


# --------------------------------------------------------
#
# Table structure for table 'mtypes'
#

CREATE TABLE mtypes (
   id serial,
   name varchar(30),
   sname varchar(5) UNIQUE,
   PRIMARY KEY (id)
);


# --------------------------------------------------------
#
# Table structure for table 'music'
#

CREATE TABLE music (
   id serial,
   name varchar(30),
   firstname varchar(30),
   PRIMARY KEY (id)
);


# --------------------------------------------------------
#
# Table structure for table 'pict'
#

CREATE TABLE pict (
   id serial,
   name varchar(30),
   sname varchar(5) UNIQUE,
   PRIMARY KEY (id)
);


# --------------------------------------------------------
#
# Table structure for table 'tone'
#

CREATE TABLE tone (
   id serial,
   name varchar(30),
   sname varchar(5) UNIQUE,
   PRIMARY KEY (id)
);


# --------------------------------------------------------
#
# Table structure for table 'commercials'
#

CREATE TABLE commercials (
   id int,
   name varchar(30),
   PRIMARY KEY (id)
);


# --------------------------------------------------------
#
# Table structure for table 'video'
#

CREATE TABLE video (
   id serial,
   mtype_id int,
   cass_id int,
   part int,
   title varchar(60),
   label int NOT NULL,
   length int,
   counter1 varchar(10),
   counter2 varchar(10),
   aq_date varchar(10),
   source varchar(15),
   director_id int,
   director_list int,
   music_id int,
   music_list int,
   country varchar(30),
   year int,
   cat1_id int NOT NULL,
   cat2_id int NOT NULL,
   cat3_id int NOT NULL,
   actor1_id int,
   actor2_id int,
   actor3_id int,
   actor4_id int,
   actor5_id int,
   actor1_list int NOT NULL,
   actor2_list int NOT NULL,
   actor3_list int NOT NULL,
   actor4_list int NOT NULL,
   actor5_list int NOT NULL,
   tone_id int,
   color_id int,
   pict_id int NOT NULL,
   commercials_id int NOT NULL,
   lp int NOT NULL,
   fsk int,
   comment text,
   PRIMARY KEY (id)
);


# --------------------------------------------------------
#
# Table structure for table 'preferences'
#

CREATE TABLE preferences (
   id serial,
   name varchar(30),
   value text,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'pvp_system' (system settings)
#

CREATE TABLE pvp_config (
   id serial,
   name varchar(30) NOT NULL,
   value text,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'lang' (translations)
#

CREATE TABLE lang (
  message_id varchar(150) NOT NULL,
  lang varchar(5) DEFAULT 'en' NOT NULL,
  content text NOT NULL,
  PRIMARY KEY (message_id,lang)
);

# --------------------------------------------------------
#
# Table structure for table 'languages' (supported languages)
#

CREATE TABLE languages (
  lang_id char(2) NOT NULL,
  lang_name varchar(50) NOT NULL,
  charset varchar(20),
  available char(3) DEFAULT 'No' NOT NULL,
  PRIMARY KEY (lang_id)
);

# --------------------------------------------------------
#
# Table structure for table 'pvp_users' (user management and authorization)
#

CREATE TABLE pvp_users (
  id SERIAL,
  login VARCHAR(20) UNIQUE,
  pwd VARCHAR(32),
  admin INT NOT NULL,
  browse INT NOT NULL,
  ins INT NOT NULL,
  upd INT NOT NULL,
  del INT NOT NULL,
  comment VARCHAR(255),
  PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'pvp_sessions' (session management)
#

CREATE TABLE pvp_sessions (
  id VARCHAR(255) NOT NULL,
  ip VARCHAR(255) NOT NULL,
  user_id INT,
  started VARCHAR(50),
  dla VARCHAR(50),
  ended VARCHAR(50),
  PRIMARY KEY (id)
);
