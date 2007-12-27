# ========================================================
# Updating Database for phpVideoPro from v0.8.7 to v0.8.8
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.9.0' WHERE name='version';
