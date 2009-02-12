# ========================================================
# Updating Database for phpVideoPro from v0.9.3 to v0.9.4
# ========================================================

# prepare default lang update
DELETE FROM pvp_lang WHERE lang='en';

# new features
INSERT INTO pvp_preferences (name,value) VALUES ('default_editor','plain');

# version update
UPDATE pvp_config SET value='0.9.4' WHERE name='version';
