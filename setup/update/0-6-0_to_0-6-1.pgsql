# =======================================================
# Updating Database for phpVideoPro from v0.5.x to v0.6.1
# =======================================================

# create the options table
CREATE TABLE pvp_options (
  id serial,
  name varchar(30) NOT NULL,
  value text,
  PRIMARY KEY  (id)
);
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://us.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://uk.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://german.imdb.com/');
INSERT INTO preferences (name,value) VALUES ('imdb_url','http://us.imdb.com/');

# remove obsolete entries from the translation table
DELETE FROM lang WHERE message_id='backup_db_moviedel';
DELETE FROM lang WHERE message_id='backup_db_movies';
DELETE FROM lang WHERE message_id='backup_db_runscript';
DELETE FROM lang WHERE message_id='colors';

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.6.1' WHERE name='version';
