# =======================================================
# Updating Database for phpVideoPro from v0.4.7 to v0.4.8
# =======================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# fix printer settings for Canon S520
UPDATE printers SET left_offset=0 WHERE id=3;

# version update
UPDATE pvp_config SET value='0.4.8' WHERE name='version';
