# ========================================================
# Updating Database for phpVideoPro from v0.2.0 to v0.2.1
# ========================================================

ALTER TABLE video ADD counter1 VARCHAR(10), ADD counter2 VARCHAR(10);
# version update
UPDATE pvp_config SET value='0.2.1' WHERE name='version';
