# ===========================================================
# Updating Database for phpVideoPro from v0.4.2/3/4 to v0.4.5
# ===========================================================

DELETE FROM lang WHERE lang='en';
DELETE FROM lang WHERE lang='es';

# version update
UPDATE pvp_config SET value='0.4.5' WHERE name='version';
