# =======================================================
# Updating Database for phpVideoPro from v0.5.5 to v0.5.8
# =======================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.5.8' WHERE name='version';
