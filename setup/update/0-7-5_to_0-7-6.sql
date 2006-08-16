# ========================================================
# Updating Database for phpVideoPro from v0.7.5 to v0.7.9
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.7.9' WHERE name='version';
