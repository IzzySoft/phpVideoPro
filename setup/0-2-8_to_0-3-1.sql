# ==========================================================
# Updating Database for phpVideoPro from v0.2.8/9 to v0.3.0
# ==========================================================

# version update
UPDATE pvp_config SET value='0.3.1' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
