# ========================================================
# Updating Database for phpVideoPro from v0.6.6 to v0.7.0
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# Selectable options for the new IMDB features
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_title');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_country');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_year');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_pg');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_length');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_cat');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_director');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_actor');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_comments');

# New preferences for IMDB handling
INSERT INTO preferences (name,value) VALUES ('imdb_url2','http://us.imdb.com/');
INSERT INTO preferences (name,value) VALUES ('imdb_tx_title','1');
INSERT INTO preferences (name,value) VALUES ('imdb_tx_country','1');
INSERT INTO preferences (name,value) VALUES ('imdb_tx_year','1');
INSERT INTO preferences (name,value) VALUES ('imdb_tx_pg','1');
INSERT INTO preferences (name,value) VALUES ('imdb_tx_length','1');
INSERT INTO preferences (name,value) VALUES ('imdb_tx_cat','1');
INSERT INTO preferences (name,value) VALUES ('imdb_tx_director','1');
INSERT INTO preferences (name,value) VALUES ('imdb_tx_actor','1');
INSERT INTO preferences (name,value) VALUES ('imdb_tx_comments','1');

# version update
#UPDATE pvp_config SET value='0.7.2' WHERE name='version';
