# =======================================================
# Updating Database for phpVideoPro from v0.3.4 to v0.3.5
# =======================================================

# version update
UPDATE pvp_config SET value='0.3.5' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
