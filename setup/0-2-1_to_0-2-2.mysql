# ========================================================
# Updating Database for phpVideoPro from v0.2.0 to v0.2.1
# ========================================================

# provide handling of VideoCD (VCD)
UPDATE mtypes SET id=4 WHERE id=3;
UPDATE video SET mtype_id=4 WHERE mtype_id=3;
INSERT INTO mtypes (id,name,sname) VALUES (3,"VideoCD","VCD");

# version update
UPDATE pvp_config SET value='0.2.1p1' WHERE name='version';
