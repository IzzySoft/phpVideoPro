# =========================================================
# Updating Database for phpVideoPro from v0.3.5/6 to v0.3.7
# =========================================================

# moved items from config.inc to DB
INSERT INTO pvp_config (name,value) VALUES ('rw_media','1');
INSERT INTO pvp_config (name,value) VALUES ('remove_empty_media','1');
INSERT INTO pvp_config (name,value) VALUES ('site','');
INSERT INTO preferences (name,value) VALUES ('default_movie_colorid','2');
INSERT INTO preferences (name,value) VALUES ('default_movie_onlabel','1');
INSERT INTO preferences (name,value) VALUES ('default_movie_toneid','2');

# should title appear on labels
ALTER TABLE video ADD label INT;
ALTER TABLE video ALTER label SET DEFAULT '1';
UPDATE video SET label='1';
ALTER TABLE video ADD CONSTRAINT label_notnullcheck CHECK (label IS NOT NULL);

# version update
UPDATE pvp_config SET value='0.3.7' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
