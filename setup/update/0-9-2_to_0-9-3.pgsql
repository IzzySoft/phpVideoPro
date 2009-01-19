# ========================================================
# Updating Database for phpVideoPro from v0.9.2 to v0.9.3
# ========================================================

BEGIN;

# prepare default lang update
#DELETE FROM lang WHERE lang='en';

# IMDB name stuff
ALTER TABLE actors ADD imdb_id VARCHAR(10);
ALTER TABLE directors ADD imdb_id VARCHAR(10);
ALTER TABLE music ADD imdb_id VARCHAR(10);

# Table renaming
ALTER TABLE preferences RENAME TO pvp_preferences;
ALTER TABLE tone RENAME TO pvp_tone;
ALTER TABLE pict RENAME TO pvp_pict;
ALTER TABLE disks RENAME TO pvp_disks;
ALTER TABLE mtypes RENAME TO pvp_mtypes;

# version update
UPDATE pvp_config SET value='0.9.3' WHERE name='version';

COMMIT;

# Do some cleanup
BEGIN;
DROP TABLE eps_templates;
COMMIT;
