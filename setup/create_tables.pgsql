# ========================================================
# Database for phpVideoPro
# ========================================================

# --------------------------------------------------------
#
# Table structure for table 'actors'
#

CREATE TABLE actors (
   id SERIAL,
   name VARCHAR(30),
   firstname VARCHAR(30),
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'cass'
#

CREATE TABLE cass (
   id INT NOT NULL,
   mtype_id INT DEFAULT 1,
   disks_id INT,
   type INT,
   free INT,
   rc VARCHAR,
   PRIMARY KEY (id,mtype_id)
);

CREATE INDEX cass_free_idx ON cass(free,id);

# --------------------------------------------------------
#
# Table structure for table 'cat'
#

CREATE TABLE cat (
   id SERIAL,
   name VARCHAR(30) UNIQUE,
   enabled INT DEFAULT 1 NOT NULL,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'colors'
#

CREATE TABLE colors (
   id SERIAL,
   name VARCHAR(30),
   sname VARCHAR(5) UNIQUE,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'directors'
#

CREATE TABLE directors (
   id SERIAL,
   name VARCHAR(30),
   firstname VARCHAR(30),
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'mtypes'
#

CREATE TABLE mtypes (
   id SERIAL,
   name VARCHAR(30),
   sname VARCHAR(5) UNIQUE,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'disks'
#
CREATE TABLE disks (
  id SERIAL,
  mtype_id INT NOT NULL,
  name VARCHAR(100) NOT NULL,
  size VARCHAR(20),
  lp INT NOT NULL DEFAULT 0,
  rc INT NOT NULL DEFAULT 0,
  PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'music'
#

CREATE TABLE music (
   id SERIAL,
   name VARCHAR(30),
   firstname VARCHAR(30),
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'pict'
#

CREATE TABLE pict (
   id SERIAL,
   name VARCHAR(30),
   sname VARCHAR(5) UNIQUE,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'tone'
#

CREATE TABLE tone (
   id SERIAL,
   name VARCHAR(30),
   sname VARCHAR(5) UNIQUE,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'commercials'
#

CREATE TABLE commercials (
   id INT,
   name VARCHAR(30),
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'video'
#

CREATE TABLE video (
   id SERIAL,
   mtype_id INT,
   cass_id INT,
   part INT,
   title VARCHAR(60),
   label INT NOT NULL,
   length INT,
   counter1 VARCHAR(10),
   counter2 VARCHAR(10),
   aq_date VARCHAR(10),
   source VARCHAR(15),
   director_id INT,
   director_list INT,
   music_id INT,
   music_list INT,
   country VARCHAR(30),
   year INT,
   cat1_id INT NOT NULL,
   cat2_id INT NOT NULL,
   cat3_id INT NOT NULL,
   actor1_id INT,
   actor2_id INT,
   actor3_id INT,
   actor4_id INT,
   actor5_id INT,
   actor1_list INT NOT NULL,
   actor2_list INT NOT NULL,
   actor3_list INT NOT NULL,
   actor4_list INT NOT NULL,
   actor5_list INT NOT NULL,
   tone_id INT,
   color_id INT,
   pict_id INT NOT NULL,
   commercials_id INT NOT NULL,
   lp INT NOT NULL,
   fsk INT,
   audio VARCHAR(50),
   subtitle VARCHAR(100),
   comment TEXT,
   PRIMARY KEY (id)
);

CREATE INDEX video_cat_idx ON video(cat1_id,cat2_id,cat3_id);
CREATE UNIQUE INDEX video_unique_medium_idx ON video(mtype_id,cass_id,part);

# --------------------------------------------------------
#
# Table structure for table 'preferences'
#

CREATE TABLE preferences (
   id SERIAL,
   name VARCHAR(30),
   value TEXT,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'userprefs'
#
CREATE TABLE pvp_userprefs (
   id SERIAL,
   user_id INT NOT NULL,
   name VARCHAR(30),
   value TEXT,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'pvp_system' (system settings)
#

CREATE TABLE pvp_config (
   id SERIAL,
   name VARCHAR(30) NOT NULL,
   value TEXT,
   PRIMARY KEY (id)
);

# --------------------------------------------------------
#
# Table structure for table 'lang' (translations)
#

CREATE TABLE lang (
  message_id VARCHAR(150) NOT NULL,
  lang VARCHAR(5) DEFAULT 'en' NOT NULL,
  content TEXT NOT NULL,
  comment TEXT,
  PRIMARY KEY (message_id,lang)
);

# --------------------------------------------------------
#
# Table structure for table 'languages' (supported languages)
#

CREATE TABLE languages (
  lang_id CHAR(2) NOT NULL,
  lang_name VARCHAR(50) NOT NULL,
  charset VARCHAR(20),
  available CHAR(3) DEFAULT 'No' NOT NULL,
  audio INT(1) DEFAULT 0 NOT NULL,
  subtitle INT(1) DEFAULT 0 NOT NULL,
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

# --------------------------------------------------------
#
# Table structure for table 'pvp_options' (option management)
#

CREATE TABLE pvp_options (
  id SERIAL,
  name VARCHAR(30) NOT NULL,
  value TEXT,
  PRIMARY KEY  (id)
);
