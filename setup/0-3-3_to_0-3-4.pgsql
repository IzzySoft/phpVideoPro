# ========================================================
# Updating Database for phpVideoPro from v0.3.3 to v0.3.4
# ========================================================

# Cass table has changed
ALTER TABLE cass ADD mtype_id INT DEFAULT '1' NOT NULL;
UPDATE cass SET mtype_id=1;
ALTER TABLE cass DROP INDEX;
ALTER TABLE cass MODIFY id int NOT NULL;
ALTER TABLE cass ADD PRIMARY KEY (id,mtype_id);

# version update
UPDATE pvp_config SET value='0.3.4' WHERE name='version';

# prepare default language update
DELETE FROM lang WHERE lang='en';
