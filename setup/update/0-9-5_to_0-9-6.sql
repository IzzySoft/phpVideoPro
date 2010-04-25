# ========================================================
# Updating Database for phpVideoPro from v0.9.5 to v0.9.6
# ========================================================

# prepare default lang update
DELETE FROM pvp_lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.9.6' WHERE name='version';
