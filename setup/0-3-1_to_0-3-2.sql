# ==========================================================
# Updating Database for phpVideoPro from v0.3.0/1 to v0.3.2
# ==========================================================

# version update
UPDATE pvp_config SET value='0.3.2' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
