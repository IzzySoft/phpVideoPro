# ========================================================
# Updating Database for phpVideoPro from v0.3.7 to v0.3.8
# ========================================================

# version update
UPDATE pvp_config SET value='0.3.8' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
