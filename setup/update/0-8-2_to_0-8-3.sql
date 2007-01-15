# ========================================================
# Updating Database for phpVideoPro from v0.8.2 to v0.8.4
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.8.4' WHERE name='version';

# New IMDB TX option
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_rating');
