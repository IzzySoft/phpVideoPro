# ========================================================
# Updating Database for phpVideoPro from v0.2.7 to v0.2.8
# ========================================================

# Category table has changed
DELETE FROM cat;

# version update
UPDATE pvp_config SET value='0.2.8' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
