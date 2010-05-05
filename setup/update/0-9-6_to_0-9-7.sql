# ========================================================
# Updating Database for phpVideoPro from v0.9.6 to v0.9.7
# ========================================================

# MDB sites
# us.imdb.com lately causes only trouble
DELETE FROM pvp_options WHERE name='imdb_url' AND value='http://us.imdb.com/';
DELETE FROM pvp_options WHERE name='imdb_url2' AND value='http://us.imdb.com/';
UPDATE pvp_preferences SET value='http://uk.imdb.com/' WHERE value='http://us.imdb.com/';
# some IMDB sites moved to new domains
UPDATE pvp_options SET value='http://www.imdb.de/' WHERE name='imdb_url' AND value='http://german.imdb.com/';
UPDATE pvp_options SET value='http://www.imdb.it/' WHERE name='imdb_url' AND value='http://italian.imdb.com/';
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.es/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.fr/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.pt/');
# and finally, there is support for Moviepilot now
INSERT INTO pvp_config (name,value) VALUES ('pilot_apikey','');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://www.moviepilot.de/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://es.moviepilot.com/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://fr.moviepilot.com/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://pl.moviepilot.com/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://uk.moviepilot.com/');
INSERT INTO pvp_preferences (name,value) VALUES ('pilot_url','http://uk.moviepilot.com/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_fallback','NO_ACCESS');
INSERT INTO pvp_options (name,value) VALUES ('pilot_fallback','BASIC_ACCESS');
INSERT INTO pvp_options (name,value) VALUES ('pilot_fallback','MEDIUM_ACCESS');
INSERT INTO pvp_options (name,value) VALUES ('pilot_fallback','FULL_ACCESS');
INSERT INTO pvp_preferences (name,value) VALUES ('pilot_fallback','NO_ACCESS');
INSERT INTO pvp_preferences (name,value) VALUES ('mdb_use','0');

# version update
UPDATE pvp_config SET value='0.9.6' WHERE name='version';
