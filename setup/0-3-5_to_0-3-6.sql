# =======================================================
# Updating Database for phpVideoPro from v0.3.5 to v0.3.6
# =======================================================

# version update
UPDATE pvp_config SET value='0.3.6' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
