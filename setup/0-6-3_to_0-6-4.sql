# =======================================================
# Updating Database for phpVideoPro from v0.6.3 to v0.6.4
# =======================================================

# Speed up SQL by indices / ensure integrity
CREATE INDEX video_cat_idx ON video(cat1_id,cat2_id,cat3_id);
CREATE INDEX cass_free_idx ON cass(free,id);
CREATE UNIQUE INDEX video_unique_medium_idx ON video(mtype_id,cass_id,part);

# version update
UPDATE pvp_config SET value='0.6.4' WHERE name='version';
