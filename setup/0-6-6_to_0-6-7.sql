# =======================================================
# Updating Database for phpVideoPro from v0.6.6 to v0.6.7
# =======================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.6.7' WHERE name='version';
