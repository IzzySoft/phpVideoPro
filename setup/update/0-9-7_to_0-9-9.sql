# ========================================================
# Updating Database for phpVideoPro from v0.9.7 to v0.9.9
# ========================================================

# add Blu-ray disc
INSERT INTO pvp_mtypes (name,sname) VALUES 'Blu-ray Disc','BD';

# upgrade IMDB URLs to https and remove local IMDB sites which no longer exist
UPDATE pvp_options SET value=REPLACE(value,'http:','https:');
UPDATE pvp_options SET value=REPLACE(value,'https://www.imdb.de','https://www.imdb.com');
DELETE FROM pvp_options WHERE value='https://akas.imdb.com/';
DELETE FROM pvp_options WHERE value='https://uk.imdb.com/';
DELETE FROM pvp_options WHERE value='https://us.imdb.com/';
DELETE FROM pvp_options WHERE value='https://www.imdb.es/';
DELETE FROM pvp_options WHERE value='https://www.imdb.fr/';
DELETE FROM pvp_options WHERE value='https://www.imdb.it/';
DELETE FROM pvp_options WHERE value='https://www.imdb.pt/';
INSERT INTO pvp_options (name,value) VALUES ('imdb_url2','https://www.imdb.com/');
UPDATE pvp_preferences SET value='https://www.imdb.com/' WHERE name='imdb_url';
UPDATE pvp_preferences SET value='https://www.imdb.com/' WHERE name='imdb_url2';

# add newer Dolby formats
INSERT INTO pvp_tone (name,sname) VALUES ( 'Dolby 7.1', '7.1');
INSERT INTO pvp_tone (name,sname) VALUES ( 'Dolby Atmos', '7.1.4');
INSERT INTO pvp_tone (name,sname) VALUES ( 'Dolby Atmos 9.1', '9.1');

# new translations
INSERT INTO pvp_lang VALUES ('imdb_lang','en','IMDB languages','Item on the configuration screen');
INSERT INTO pvp_lang VALUES ('imdb_lang_comment','en','Override IMDBPHP default languages. This should be a comma-separated list of ISO language codes, e.g. <code>de-DE,de,en-US,en</code>. Leave empty to use the defaults you’ve defined with the IMDBPHP config.','Item on the configuration screen');

# version update
UPDATE pvp_config SET value='0.9.9' WHERE name='version';
