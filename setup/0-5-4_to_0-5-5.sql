# =======================================================
# Updating Database for phpVideoPro from v0.5.4 to v0.5.5
# =======================================================

# New table structs
ALTER TABLE lang ADD comment TEXT;
DELETE FROM lang WHERE message_id LIKE 'feedback_%';

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.5.5' WHERE name='version';
