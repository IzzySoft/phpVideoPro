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
   id serial,
   type int,
   free int,
   PRIMARY KEY (id)
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
# Table structure for table 'video'
#

CREATE TABLE video (
   id serial,
   mtype_id int,
   cass_id int,
   part int,
   title varchar(60),
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
   cat1_id int,
   cat2_id int,
   cat3_id int,
   actor1_id int,
   actor2_id int,
   actor3_id int,
   actor4_id int,
   actor5_id int,
   actor1_list int,
   actor2_list int,
   actor3_list int,
   actor4_list int,
   actor5_list int,
   tone_id int,
   color_id int,
   pict_id int,
   lp int,
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
