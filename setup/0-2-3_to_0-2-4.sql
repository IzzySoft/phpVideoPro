# ========================================================
# Updating Database for phpVideoPro from v0.2.3 to v0.2.4
# ========================================================

# version update
UPDATE pvp_config SET value='0.2.4' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
