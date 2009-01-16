# ========================================================
# Database for phpVideoPro
# ========================================================

BEGIN;
# --------------------------------------------------------
#
# Table structure for table 'actors'
#

CREATE TABLE actors (
   id SERIAL,
   imdb_id VARCHAR(10),
   name VARCHAR(30),
   firstname VARCHAR(30),
   PRIMARY KEY (id)
);
COMMENT ON TABLE actors IS 'Actor names';

# --------------------------------------------------------
#
# Table structure for table 'pvp_media'
#

CREATE TABLE pvp_media (
   id INT,
   mtype_id INT DEFAULT 1,
   disks_id INT,
   size INT,
   free INT,
   rc VARCHAR,
   owner INT DEFAULT 0,
   storeplace VARCHAR,
   lentto VARCHAR
);
COMMENT ON TABLE pvp_media IS 'Media info (DVDs,tapes, etc)';
COMMENT ON COLUMN pvp_media.id IS 'The media number';
COMMENT ON COLUMN pvp_media.mtype_id IS 'The media type (e.g. DVD) ID';
COMMENT ON COLUMN pvp_media.disks_id IS 'Media subtype (e.g. DVD-5) ID';
COMMENT ON COLUMN pvp_media.size IS 'Media size in minutes (e.g. 240 for 240min tapes)';
COMMENT ON COLUMN pvp_media.free IS 'Free time/space on the medium';
COMMENT ON COLUMN pvp_media.rc IS 'To which regions the medium is restricted';
COMMENT ON COLUMN pvp_media.owner IS 'user_id to whom belongs this medium';
COMMENT ON COLUMN pvp_media.storeplace IS 'Where this medium is physically stored';
COMMENT ON COLUMN pvp_media.lentto IS 'To whom this medium is (temporarily) lent';
ALTER TABLE pvp_media ADD CONSTRAINT pk_media PRIMARY KEY (id,mtype_id);
ALTER TABLE pvp_media ADD CONSTRAINT notnullcheck_media_id CHECK (id IS NOT NULL);
ALTER TABLE pvp_media ADD CONSTRAINT notnullcheck_media_owner CHECK (owner IS NOT NULL);

CREATE INDEX media_free_idx ON pvp_media(free,id);
COMMENT ON INDEX media_free_idx IS 'For faster access to available free space';

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
COMMENT ON TABLE cat IS 'Categories';
COMMENT ON COLUMN cat.name IS 'Internal name of the category';
COMMENT ON COLUMN cat.enabled IS 'Whether the category is active (used/displayed)';

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
COMMENT ON TABLE colors IS 'Types of movie colors, such as b/w, color, etc.';

# --------------------------------------------------------
#
# Table structure for table 'directors'
#

CREATE TABLE directors (
   id SERIAL,
   imdb_id VARCHAR(10),
   name VARCHAR(30),
   firstname VARCHAR(30),
   PRIMARY KEY (id)
);
COMMENT ON TABLE directors IS 'Director names';

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
COMMENT ON TABLE mtypes IS 'Media types used, e.g. DVD, VCD';

# --------------------------------------------------------
#
# Table structure for table 'pvp_vnorms'
#
CREATE TABLE pvp_vnorms (
   id INT,
   name VARCHAR
);
COMMENT ON TABLE pvp_vnorms IS 'List of video norms (PAL,NTSC) we support';
COMMENT ON COLUMN pvp_vnorms.id IS 'ID for reference';
COMMENT ON COLUMN pvp_vnorms.name IS 'Name of the norm (e.g. PAL or NTSC)';
ALTER TABLE pvp_vnorms ADD CONSTRAINT pk_vnorms PRIMARY KEY (id);
ALTER TABLE pvp_vnorms ADD CONSTRAINT notnullcheck_vnorms_name CHECK (name IS NOT NULL);

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
COMMENT ON TABLE disks IS 'Disk types, e.g. DVD5, DVD-RW';

# --------------------------------------------------------
#
# Table structure for table 'music'
#

CREATE TABLE music (
   id SERIAL,
   imdb_id VARCHAR(10),
   name VARCHAR(30),
   firstname VARCHAR(30),
   PRIMARY KEY (id)
);
COMMENT ON TABLE music IS 'Names of composers/artists';

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
COMMENT ON TABLE pict IS 'Screen/picture formats, e.g. 4:3 or 16:9';

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
COMMENT ON TABLE tone IS 'Audio formats, e.g. Stereo, DD 5.1';

# --------------------------------------------------------
#
# Table structure for table 'commercials'
#

CREATE TABLE commercials (
   id INT,
   name VARCHAR(30),
   PRIMARY KEY (id)
);
COMMENT ON TABLE commercials IS 'Are there commercials in the recording?';

# --------------------------------------------------------
#
# Table structure for table 'pvp_video'
#

CREATE TABLE pvp_video (
   id SERIAL,
   mtype_id INT,
   media_id INT,
   part INT,
   title VARCHAR(60),
   imdb_id VARCHAR(10),
   rating NUMERIC(3,1),
   label INT DEFAULT 0,
   length INT,
   counter1 VARCHAR(10),
   counter2 VARCHAR(10),
   aq_date VARCHAR(10),
   source VARCHAR(15),
   cat1_id INT DEFAULT 0,
   cat2_id INT DEFAULT 0,
   cat3_id INT DEFAULT 0,
   director_id INT,
   director_list INT DEFAULT 0,
   music_id INT,
   music_list INT DEFAULT 0,
   actor1_id INT,
   actor2_id INT,
   actor3_id INT,
   actor4_id INT,
   actor5_id INT,
   actor1_list INT DEFAULT 0,
   actor2_list INT DEFAULT 0,
   actor3_list INT DEFAULT 0,
   actor4_list INT DEFAULT 0,
   actor5_list INT DEFAULT 0,
   country VARCHAR(30),
   year INT,
   vnorm_id INT DEFAULT 0,
   tone_id INT,
   color_id INT,
   pict_id INT DEFAULT 0,
   commercials_id INT DEFAULT 0,
   lp INT DEFAULT 0,
   fsk INT,
   audio VARCHAR(50),
   subtitle VARCHAR(100),
   comment TEXT,
   private INT DEFAULT 0,
   lastchange TIMESTAMP
);
COMMENT ON TABLE pvp_video IS 'Stores the movies information';
COMMENT ON COLUMN pvp_video.id IS 'ID for reference';
COMMENT ON COLUMN pvp_video.mtype_id IS 'The media type (refers to mtypes)';
COMMENT ON COLUMN pvp_video.media_id IS 'ID of the medium this movie resides on';
COMMENT ON COLUMN pvp_video.part IS 'The movies number on the medium';
COMMENT ON COLUMN pvp_video.title IS 'The name of the movie';
COMMENT ON COLUMN pvp_video.imdb_id IS 'Movies ID in the Internet Movie DataBase (if known)';
COMMENT ON COLUMN pvp_video.rating IS 'Rating of the movie, like at IMDB.com';
COMMENT ON COLUMN pvp_video.label IS 'Shall the movies data appear on label prints';
COMMENT ON COLUMN pvp_video.length IS 'Length of the movie in minutes';
COMMENT ON COLUMN pvp_video.counter1 IS 'Counter on movie start (for old tape recorders)';
COMMENT ON COLUMN pvp_video.counter2 IS 'Counter on movie end (for old tape recorders)';
COMMENT ON COLUMN pvp_video.aq_date IS 'Date the movie was recorded/bought/...';
COMMENT ON COLUMN pvp_video.source IS 'Where we got it (station/shop/friends name)';
COMMENT ON COLUMN pvp_video.cat1_id IS 'ID of category for this movie (refers to cat table)';
COMMENT ON COLUMN pvp_video.director_id IS 'ID of the directors name (refers to directors table)';
COMMENT ON COLUMN pvp_video.directors_list IS 'List the director for this movie in printouts';
COMMENT ON COLUMN pvp_video.music_id IS 'ID of composer/musician (refers to music table)';
COMMENT ON COLUMN pvp_video.actor1_id IS 'ID of some actor (refers to actors table)';
COMMENT ON COLUMN pvp_video.country IS 'Country where the movie was made';
COMMENT ON COLUMN pvp_video.year IS 'Year the movie was made/released';
COMMENT ON COLUMN pvp_video.vnorm_id IS 'ID of video norm (refers to vnorms table)';
COMMENT ON COLUMN pvp_video.tone_id IS 'ID of tone format (mono/stereo/...). Refers to tone table';
COMMENT ON COLUMN pvp_video.color_id IS 'ID of color format (refers to colors table)';
COMMENT ON COLUMN pvp_video.pict_id IS 'ID of picture format (4:3/16:9/...). Refers to pict table';
COMMENT ON COLUMN pvp_video.commercials IS 'Whether the recording contains commercials (refers to commercials table)';
COMMENT ON COLUMN pvp_video.lp IS 'Whether the recording used LongPlay';
COMMENT ON COLUMN pvp_video.fsk IS 'Parental Guide information';
COMMENT ON COLUMN pvp_video.audio IS 'Language(s) of audio track(s)';
COMMENT ON COLUMN pvp_video.subtitle IS 'Language(s) of subtitle(s)';
COMMENT ON COLUMN pvp_video.comment IS 'Detailed comments on the movie';
COMMENT ON COLUMN pvp_video.private IS 'Show this movie record to all granted (0) or owner only (1)';
COMMENT ON COLUMN pvp_video.lastchange IS 'Timestamp of last change of this record';
ALTER TABLE pvp_video ADD CONSTRAINT pk_video PRIMARY KEY (id);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_label CHECK (label IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_cat1id CHECK (cat1_id IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_cat2id CHECK (cat2_id IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_cat3id CHECK (cat3_id IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_actor1list CHECK (actor1_list IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_actor2list CHECK (actor2_list IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_actor3list CHECK (actor3_list IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_actor4list CHECK (actor4_list IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_actor5list CHECK (actor5_list IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_directorlist CHECK (director_list IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_musiclist CHECK (music_list IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_pictid CHECK (pict_id IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_commercialsid CHECK (commercials_id IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_lp CHECK (lp IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_vnormid CHECK (vnorm_id IS NOT NULL);
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_private CHECK (private IS NOT NULL);
CREATE INDEX video_cat_idx ON pvp_video (cat1_id,cat2_id,cat3_id);
COMMENT ON INDEX video_cat_idx IS 'For faster access on searches';
CREATE UNIQUE INDEX video_unique_medium_idx ON pvp_video (mtype_id,cass_id,part);
COMMENT ON INDEX video_unique_medium_idx IS 'Prevent the mess of duplicate entries on double-clicks';
CREATE INDEX video_title_idx ON pvp_video (title);
COMMENT ON INDEX video_title_idx IS 'Improve search speed for movie title';

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
COMMENT ON TABLE preferences IS 'Global preferences';

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
COMMENT ON TABLE pvp_userprefs IS 'User preferences';

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
COMMENT ON TABLE pvp_config IS 'General configuration of the application';

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
COMMENT ON TABLE lang IS 'Translations';
COMMENT ON COLUMN lang.message_id IS 'Internal abbreviation (used as key)';
COMMENT ON COLUMN lang.lang IS 'Two-char language code for the translation';
COMMENT ON COLUMN lang.content IS 'Translated message for the specified language';
COMMENT ON COLUMN lang.comment IS 'Hints for translators';

# --------------------------------------------------------
#
# Table structure for table 'languages' (supported languages)
#

CREATE TABLE languages (
  lang_id CHAR(2) NOT NULL,
  lang_name VARCHAR(50) NOT NULL,
  charset VARCHAR(20),
  available CHAR(3) DEFAULT 'No' NOT NULL,
  audio INT DEFAULT 0 NOT NULL,
  subtitle INT DEFAULT 0 NOT NULL,
  PRIMARY KEY (lang_id)
);
COMMENT ON TABLE languages IS 'Languages and their settings';
COMMENT ON COLUMN languages.lang_id IS 'Two-char language code';
COMMENT ON COLUMN languages.lang_name IS 'Name of the language';
COMMENT ON COLUMN languages.charset IS 'Character set used by its translations in the lang table';
COMMENT ON COLUMN languages.available IS 'Do we have translations for it and want to use them?';
COMMENT ON COLUMN languages.audio IS 'Will the language be used for audio in our collection(s)?';
COMMENT ON COLUMN languages.subtitle IS 'Will the language be used for subtitles in our collection(s)?';

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
COMMENT ON TABLE pvp_users IS 'User and authorization data';
COMMENT ON COLUMN pvp_users.id IS 'User ID';
COMMENT ON COLUMN pvp_users.login IS 'Login name';
COMMENT ON COLUMN pvp_users.pwd IS 'Password hash';
COMMENT ON COLUMN pvp_users.admin IS 'Admin privilege (yes/no)';
COMMENT ON COLUMN pvp_users.browse IS 'May see contents (yes/no)';
COMMENT ON COLUMN pvp_users.ins IS 'May add new movies (yes/no)';
COMMENT ON COLUMN pvp_users.upd IS 'May update existing data (yes/no)';
COMMENT ON COLUMN pvp_users.del IS 'May delete data (yes/no)';
COMMENT ON COLUMN pvp_users.comment IS 'Some comment on the user';

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
COMMENT ON TABLE pvp_sessions IS 'Session management data';
COMMENT ON COLUMN pvp_sessions.id IS 'SessionID';
COMMENT ON COLUMN pvp_sessions.ip IS 'IP address from the login';
COMMENT ON COLUMN pvp_sessions.user_id IS 'ID of the user the session belongs to';
COMMENT ON COLUMN pvp_sessions.started IS 'Session start time';
COMMENT ON COLUMN pvp_sessions.dla IS 'Last access time';
COMMENT ON COLUMN pvp_sessions.ended IS 'Session end';

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
COMMENT ON TABLE pvp_options IS 'Global options';

# --------------------------------------------------------
#
# Table structure for table 'pvp_usergrants'
#
CREATE TABLE pvp_usergrants (
  grantor INT NOT NULL,
  grantee INT NOT NULL,
  grants VARCHAR NOT NULL
);
ALTER TABLE pvp_usergrants ADD CONSTRAINT pk_usergrants PRIMARY KEY (grantor,grantee,grants);
COMMENT ON TABLE pvp_usergrants IS 'Privileges user grant to other users';
COMMENT ON COLUMN pvp_usergrants.grantor IS 'Owner who gives permission to his collection';
COMMENT ON COLUMN pvp_usergrants.grantee IS 'To whom the permission is given';
COMMENT ON COLUMN pvp_usergrants.grants IS 'Which permission is given';

COMMIT;
