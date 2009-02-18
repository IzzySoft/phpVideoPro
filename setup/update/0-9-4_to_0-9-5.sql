# ========================================================
# Updating Database for phpVideoPro from v0.9.4 to v0.9.5
# ========================================================

# prepare default lang update
DELETE FROM pvp_lang WHERE lang='en';

# new features
INSERT INTO pvp_config (name,value) VALUES ('user_backup_download','0');
INSERT INTO pvp_config (name,value) VALUES ('user_backup_store','0');
INSERT INTO pvp_config (name,value) VALUES ('user_backup_restore','0');
INSERT INTO pvp_config (name,value) VALUES ('max_user_backups','3');

# version update
UPDATE pvp_config SET value='0.9.5' WHERE name='version';
