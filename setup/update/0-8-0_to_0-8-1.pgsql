# ========================================================
# Updating Database for phpVideoPro from v0.8.0 to v0.8.1
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.8.1' WHERE name='version';

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
COMMENT ON TABLE pvp_media IS 'Media info (DVDs, tapes, etc)';
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

INSERT INTO pvp_media (id,mtype_id,disks_id,size,free,rc)
  SELECT id,mtype_id,disks_id,type,free,rc FROM cass;
DROP INDEX cass_free_idx;
DROP TABLE cass;

COMMENT ON TABLE actors IS 'Actor names';
COMMENT ON TABLE cat IS 'Categories';
COMMENT ON COLUMN cat.name IS 'Internal name of the category';
COMMENT ON COLUMN cat.enabled IS 'Whether the category is active (used/displayed)';
COMMENT ON TABLE colors IS 'Types of movie colors, such as b/w, color, etc.';
COMMENT ON TABLE directors IS 'Director names';
COMMENT ON TABLE mtypes IS 'Media types used, e.g. DVD, VCD';
COMMENT ON TABLE disks IS 'Disk types, e.g. DVD5, DVD-RW';
COMMENT ON TABLE music IS 'Names of composers/artists';
COMMENT ON TABLE pict IS 'Screen/picture formats, e.g. 4:3 or 16:9';
COMMENT ON TABLE tone IS 'Audio formats, e.g. Stereo, DD 5.1';
COMMENT ON TABLE commercials IS 'Are there commercials in the recording?';
COMMENT ON TABLE video IS 'Movie data';
COMMENT ON COLUMN video.mtype_id IS 'ID of the media type';
COMMENT ON COLUMN video.cass_id IS 'ID of the media';
COMMENT ON COLUMN video.part IS 'Number of the movie on the medium';
COMMENT ON COLUMN video.title IS 'Title of the movie';
COMMENT ON COLUMN video.label IS 'Appears on printed labels?';
COMMENT ON COLUMN video.length IS 'Length in minutes';
COMMENT ON COLUMN video.counter1 IS 'Counter on movie start (for old tape recorders)';
COMMENT ON COLUMN video.counter2 IS 'Counter on movie end (for old tape recorders)';
COMMENT ON COLUMN video.aq_date IS 'Date the movie was recorded/bought/...';
COMMENT ON COLUMN video.source IS 'Where we got it (station/shop/friends name)';
COMMENT ON COLUMN video.cat1_id IS 'ID of category for this movie (refers to cat table)';
COMMENT ON COLUMN video.director_id IS 'ID of the directors name (refers to directors table)';
COMMENT ON COLUMN video.directors_list IS 'List the director for this movie in printouts';
COMMENT ON COLUMN video.music_id IS 'ID of composer/musician (refers to music table)';
COMMENT ON COLUMN video.actor1_id IS 'ID of some actor (refers to actors table)';
COMMENT ON COLUMN video.country IS 'Country where the movie was made';
COMMENT ON COLUMN video.year IS 'Year the movie was made/released';
COMMENT ON COLUMN video.vnorm_id IS 'ID of video norm (refers to vnorms table)';
COMMENT ON COLUMN video.tone_id IS 'ID of tone format (mono/stereo/...). Refers to tone table';
COMMENT ON COLUMN video.color_id IS 'ID of color format (refers to colors table)';
COMMENT ON COLUMN video.pict_id IS 'ID of picture format (4:3/16:9/...). Refers to pict table';
COMMENT ON COLUMN video.commercials IS 'Whether the recording contains commercials (refers to commercials table)';
COMMENT ON COLUMN video.lp IS 'Whether the recording used LongPlay';
COMMENT ON COLUMN video.fsk IS 'Parental Guide information';
COMMENT ON COLUMN video.audio IS 'Language(s) of audio track(s)';
COMMENT ON COLUMN video.subtitle IS 'Language(s) of subtitle(s)';
COMMENT ON COLUMN video.comment IS 'Detailed comments on the movie';
COMMENT ON TABLE preferences IS 'Global preferences';
COMMENT ON TABLE pvp_userprefs IS 'User preferences';
COMMENT ON TABLE pvp_config IS 'General configuration of the application';
COMMENT ON TABLE lang IS 'Translations';
COMMENT ON COLUMN lang.message_id IS 'Internal abbreviation (used as key)';
COMMENT ON COLUMN lang.lang IS 'Two-char language code for the translation';
COMMENT ON COLUMN lang.content IS 'Translated message for the specified language';
COMMENT ON COLUMN lang.comment IS 'Hints for translators';
COMMENT ON TABLE languages IS 'Languages and their settings';
COMMENT ON COLUMN languages.lang_id IS 'Two-char language code';
COMMENT ON COLUMN languages.lang_name IS 'Name of the language';
COMMENT ON COLUMN languages.charset IS 'Character set used by its translations in the lang table';
COMMENT ON COLUMN languages.available IS 'Do we have translations for it and want to use them?';
COMMENT ON COLUMN languages.audio IS 'Will the language be used for audio in our collection(s)?';
COMMENT ON COLUMN languages.subtitle IS 'Will the language be used for subtitles in our collection(s)?';
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
COMMENT ON TABLE pvp_sessions IS 'Session management data';
COMMENT ON COLUMN pvp_sessions.id IS 'SessionID';
COMMENT ON COLUMN pvp_sessions.ip IS 'IP address from the login';
COMMENT ON COLUMN pvp_sessions.user_id IS 'ID of the user the session belongs to';
COMMENT ON COLUMN pvp_sessions.started IS 'Session start time';
COMMENT ON COLUMN pvp_sessions.dla IS 'Last access time';
COMMENT ON COLUMN pvp_sessions.ended IS 'Session end';
COMMENT ON TABLE pvp_options IS 'Global options';
