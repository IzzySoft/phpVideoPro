# ========================================================
# Updating Database for phpVideoPro from v0.3.3 to v0.3.4
# ========================================================

# Cass table has changed
ALTER TABLE cass ADD mtype_id INT;
ALTER TABLE cass ALTER mtype_id SET DEFAULT '1';
UPDATE cass SET mtype_id=1;
ALTER TABLE cass ADD CONSTRAINT mtype_id_notnullcheck CHECK (mtype_id IS NOT NULL);

# version update
UPDATE pvp_config SET value='0.3.4' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
