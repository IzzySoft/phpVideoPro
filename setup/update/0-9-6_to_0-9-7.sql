# ========================================================
# Updating Database for phpVideoPro from v0.9.6 to v0.9.7
# ========================================================

# IMDB sites
UPDATE pvp_options SET value='http://www.imdb.de/' WHERE name='imdb_url' AND value='http://german.imdb.com/';
UPDATE pvp_options SET value='http://www.imdb.it/' WHERE name='imdb_url' AND value='http://italian.imdb.com/';
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.es/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.fr/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.pt/');
#INSERT INTO pvp_options (name,value) VALUES ('imdb_url','');

# version update
UPDATE pvp_config SET value='0.9.6' WHERE name='version';
