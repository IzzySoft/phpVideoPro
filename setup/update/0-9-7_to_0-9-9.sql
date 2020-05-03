# ========================================================
# Updating Database for phpVideoPro from v0.9.7 to v0.9.9
# ========================================================

# add Blu-ray disc
INSERT INTO pvp_mtypes (name,sname) VALUES 'Blu-ray Disc','BD';

# upgrade IMDB URLs to https
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

# version update
UPDATE pvp_config SET value='0.9.9' WHERE name='version';
