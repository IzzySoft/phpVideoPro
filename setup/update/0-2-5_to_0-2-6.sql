# ========================================================
# Updating Database for phpVideoPro from v0.2.5 to v0.2.6
# ========================================================

# new preference added
INSERT INTO preferences (name,value) VALUES ('date_format','y-m-d');
INSERT INTO preferences (name,value) VALUES ('page_length','85');

# version update
UPDATE pvp_config SET value='0.2.6' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
