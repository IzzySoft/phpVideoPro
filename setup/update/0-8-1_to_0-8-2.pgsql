# ========================================================
# Updating Database for phpVideoPro from v0.8.1 to v0.8.2
# ========================================================

BEGIN;

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.8.2' WHERE name='version';

# New table for the video norms:
CREATE TABLE pvp_vnorms (
   id INT,
   name VARCHAR
);
COMMENT ON TABLE pvp_vnorms IS 'List of video norms (PAL,NTSC) we support';
COMMENT ON COLUMN pvp_vnorms.id IS 'ID for reference';
COMMENT ON COLUMN pvp_vnorms.name IS 'Name of the norm (e.g. PAL or NTSC)';
ALTER TABLE pvp_vnorms ADD CONSTRAINT pk_vnorms PRIMARY KEY (id);
ALTER TABLE pvp_vnorms ADD CONSTRAINT notnullcheck_vnorms_name CHECK (name IS NOT NULL);

INSERT INTO pvp_vnorms VALUES (1,'PAL');
INSERT INTO pvp_vnorms VALUES (2,'NTSC');

# New structure for the video table:
CREATE TABLE pvp_video (
   id SERIAL,
   mtype_id INT,
   media_id INT,
   part INT,
   title VARCHAR(60),
   imdb_id VARCHAR(10),
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
   vnorm_id INT,
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
ALTER TABLE pvp_video ADD CONSTRAINT notnullcheck_video_private CHECK (private IS NOT NULL);

INSERT INTO pvp_video (id,mtype_id,media_id,part,title,label,length,counter1,
  counter2,aq_date,source,cat1_id,cat2_id,cat3_id,director_id,director_list,
  music_id,music_list,actor1_id,actor2_id,actor3_id,actor4_id,actor5_id,
  actor1_list,actor2_list,actor3_list,actor4_list,actor5_list,country,year,
  tone_id,color_id,pict_id,commercials_id,lp,fsk,audio,subtitle,comment)
  SELECT id,mtype_id,cass_id,part,title,label,length,counter1,counter2,aq_date,
  source,cat1_id,cat2_id,cat3_id,director_id,director_list,music_id,music_list,
  actor1_id,actor2_id,actor3_id,actor4_id,actor5_id,actor1_list,actor2_list,
  actor3_list,actor4_list,actor5_list,country,year,tone_id,color_id,pict_id,
  commercials_id,lp,fsk,audio,subtitle,comment);
UPDATE pvp_video SET private=0;
DROP INDEX video_cat_idx;
DROP INDEX video_unique_medium_idx;
DROP TABLE video;

CREATE INDEX video_cat_idx ON pvp_video (cat1_id,cat2_id,cat3_id);
COMMENT ON INDEX video_cat_idx IS 'For faster access on searches';
CREATE UNIQUE INDEX video_unique_medium_idx ON pvp_video (mtype_id,cass_id,part);
COMMENT ON INDEX video_unique_medium_idx IS 'Prevent the mess of duplicate entries on double-clicks';
CREATE INDEX video_title_idx ON pvp_video (title);
COMMENT ON INDEX video_title_idx IS 'Improve search speed for movie title';


COMMIT;