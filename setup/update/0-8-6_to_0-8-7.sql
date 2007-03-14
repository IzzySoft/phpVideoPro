# ========================================================
# Updating Database for phpVideoPro from v0.8.6 to v0.8.7
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.8.7' WHERE name='version';
