# ========================================================
# Updating Database for phpVideoPro from v0.1.4 to v0.1.5
# ========================================================

# set default template set to use
INSERT INTO preferences (name,value) VALUES ('template','default');

# version update
UPDATE pvp_config SET value='0.1.5' WHERE name='version';
