# ========================================================
# Updating Database for phpVideoPro from v0.7.4 to v0.7.5
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# Add new config values and preferences
UPDATE pvp_config SET name='http_cache_enable' WHERE name='cache_enable';
INSERT INTO pvp_config (name,value) VALUES ('imdb_cache_enable','0');
INSERT INTO pvp_config (name,value) VALUES ('imdb_cache_use','0');

# version update
UPDATE pvp_config SET value='0.7.5' WHERE name='version';
