# ========================================================
# Updating Database for phpVideoPro from v0.2.4 to v0.2.5
# ========================================================

# version update
UPDATE pvp_config SET value='0.2.5' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
