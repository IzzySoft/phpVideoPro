# ========================================================
# Updating Database for phpVideoPro from v0.7.2 to v0.7.3
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# Add new config values and preferences
INSERT INTO pvp_config (name,value) VALUES ('cache_enable','0');
INSERT INTO preferences (name,value) VALUES ('imdb_txwin_autoclose','1');

# version update
#UPDATE pvp_config SET value='0.7.2' WHERE name='version';
