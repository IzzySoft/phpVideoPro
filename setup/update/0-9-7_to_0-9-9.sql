# ========================================================
# Updating Database for phpVideoPro from v0.9.7 to v0.9.9
# ========================================================

# add Blu-ray disc
INSERT INTO pvp_mtypes (name,sname) VALUES 'Blu-ray Disc','BD';

# upgrade IMDB URLs to https
UPDATE pvp_options SET value=REPLACE(value,'http:','https:');

# version update
UPDATE pvp_config SET value='0.9.9' WHERE name='version';
