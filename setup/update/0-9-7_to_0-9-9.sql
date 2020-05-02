# ========================================================
# Updating Database for phpVideoPro from v0.9.7 to v0.9.9
# ========================================================

# version update
INSERT INTO pvp_mtypes (name,sname) VALUES 'Blu-ray Disc','BD';
UPDATE pvp_config SET value='0.9.9' WHERE name='version';
