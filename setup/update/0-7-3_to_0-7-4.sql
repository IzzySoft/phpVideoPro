# ========================================================
# Updating Database for phpVideoPro from v0.7.3 to v0.7.4
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# Add new config values and preferences
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://italian.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://akas.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url2','http://akas.imdb.com/');

# version update
UPDATE pvp_config SET value='0.7.4' WHERE name='version';
