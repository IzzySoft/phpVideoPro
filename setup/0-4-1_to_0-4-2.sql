# ========================================================
# Updating Database for phpVideoPro from v0.4.1 to v0.4.2
# ========================================================

# version update
UPDATE pvp_config SET value='0.4.2' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
