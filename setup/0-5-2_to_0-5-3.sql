# =======================================================
# Updating Database for phpVideoPro from v0.5.2 to v0.5.3
# =======================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.5.3' WHERE name='version';
