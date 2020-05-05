# ========================================================
# Updating Database for phpVideoPro from v0.9.9 to v0.9.10
# ========================================================

# Moviepilot is dead
DELETE FROM pvp_config WHERE name LIKE 'pilot%';
DELETE FROM pvp_options WHERE name LIKE 'pilot%';
DELETE FROM pvp_preferences WHERE name LIKE 'pilot%';
DELETE FROM pvp_userprefs WHERE name LIKE 'pilot%';
DELETE FROM pvp_lang WHERE message_id LIKE 'pilot%';
DELETE FROM pvp_lang WHERE message_id LIKE 'mdbapi_v1_only%';
DELETE FROM pvp_lang WHERE message_id='invalid_pilot_apikey';

# version update
#UPDATE pvp_config SET value='0.9.10' WHERE name='version';
