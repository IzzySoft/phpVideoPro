# ========================================================
# Updating Database for phpVideoPro from v0.2.6 to v0.2.7
# ========================================================

# clean up some infinite values
UPDATE video SET pict_id=0 WHERE pict_id IS NULL;
UPDATE video SET commercials_id=0 WHERE commercials_id IS NULL;
UPDATE video SET cat2_id=0 WHERE cat2_id IS NULL;
UPDATE video SET cat3_id=0 WHERE cat3_id IS NULL;
UPDATE video SET actor1_list=0 WHERE actor1_list IS NULL;
UPDATE video SET actor2_list=0 WHERE actor2_list IS NULL;
UPDATE video SET actor3_list=0 WHERE actor3_list IS NULL;
UPDATE video SET actor4_list=0 WHERE actor4_list IS NULL;
UPDATE video SET actor5_list=0 WHERE actor5_list IS NULL;
UPDATE video SET lp=0 WHERE lp IS NULL;
ALTER TABLE video ADD CONSTRAINT notnullcheck_pict_id CHECK (pict_id IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_commercials_id CHECK (commercials_id IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_cat1_id CHECK (cat1_id IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_cat2_id CHECK (cat2_id IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_cat3_id CHECK (cat3_id IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_actor1_list CHECK (actor1_list IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_actor2_list CHECK (actor2_list IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_actor3_list CHECK (actor3_list IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_actor4_list CHECK (actor4_list IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_actor5_list CHECK (actor5_list IS NOT NULL);
ALTER TABLE video ADD CONSTRAINT notnullcheck_lp CHECK (lp IS NOT NULL);

# version update
UPDATE pvp_config SET value='0.2.7' WHERE name='version';
