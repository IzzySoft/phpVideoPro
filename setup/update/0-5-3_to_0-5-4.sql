# =======================================================
# Updating Database for phpVideoPro from v0.5.3 to v0.5.4
# =======================================================

# color settings have been moved to stylesheet
DELETE FROM preferences WHERE name='colors';

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.5.4' WHERE name='version';
