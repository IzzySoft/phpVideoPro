# =======================================================
# Updating Database for phpVideoPro from v0.4.5 to v0.4.6
# =======================================================

# prepare default language update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.4.6' WHERE name='version';
