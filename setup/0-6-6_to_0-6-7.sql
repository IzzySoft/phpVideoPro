# ========================================================
# Updating Database for phpVideoPro from v0.6.6 to v0.6.11
# ========================================================

# prepare default lang update
# DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.6.11' WHERE name='version';
