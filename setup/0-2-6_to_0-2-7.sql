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

# version update
UPDATE pvp_config SET value='0.2.7' WHERE name='version';
