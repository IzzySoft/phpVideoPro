# ========================================================
# Updating Database for phpVideoPro from v0.6.6 to v0.7.0
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

DELETE FROM languages;

# version update
UPDATE pvp_config SET value='0.7.1' WHERE name='version';
