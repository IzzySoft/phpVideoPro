# ========================================================
# Updating Database for phpVideoPro from v0.1.7 to v0.2.0
# ========================================================

# version update
ALTER TABLE languages ADD charset VARCHAR (20);
UPDATE languages SET charset='iso-8859-1' WHERE lang_id='de' OR lang_id='en';
DELETE FROM preferences WHERE name='charset';
UPDATE pvp_config SET value='0.2.0' WHERE name='version';
