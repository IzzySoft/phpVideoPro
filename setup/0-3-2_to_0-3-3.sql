# ===========================================================
# Updating Database for phpVideoPro from v0.3.0/1/2 to v0.3.3
# ===========================================================

# version update
UPDATE pvp_config SET value='0.3.3' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
