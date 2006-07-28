# ========================================================
# Updating Database for phpVideoPro from v0.7.5 to v0.7.8
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.7.8' WHERE name='version';
