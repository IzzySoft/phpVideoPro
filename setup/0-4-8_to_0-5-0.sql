# =======================================================
# Updating Database for phpVideoPro from v0.4.8 to v0.5.0
# =======================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.5.0' WHERE name='version';
