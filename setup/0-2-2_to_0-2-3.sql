# ========================================================
# Updating Database for phpVideoPro from v0.2.2 to v0.2.3
# ========================================================

# display limit feature was added with this version
INSERT INTO preferences (name,value) VALUES ('display_limit','30');

# version update
UPDATE pvp_config SET value='0.2.3' WHERE name='version';
