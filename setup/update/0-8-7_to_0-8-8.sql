# ========================================================
# Updating Database for phpVideoPro from v0.8.7 to v0.8.8
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# additional PSLabel printers
INSERT INTO pvp_psprinters (id, name, unit_id, top_offset, left_offset) VALUES (4,'Brother MFC',4,4.5,-4.5);

# version update
UPDATE pvp_config SET value='0.8.8' WHERE name='version';
