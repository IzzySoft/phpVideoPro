# =======================================================
# Updating Database for phpVideoPro from v0.4.6 to v0.4.7
# =======================================================

# prepare default language update
DELETE FROM lang WHERE lang='en';

# update the character sets
UPDATE languages SET charset='iso-8859-2' WHERE lang_id='pl';
UPDATE languages SET charset='iso-8859-2' WHERE lang_id='ro';
UPDATE languages SET charset='iso-8859-2' WHERE lang_id='sk';
UPDATE languages SET charset='iso-8859-2' WHERE lang_id='sl';
UPDATE languages SET charset='iso-8859-2' WHERE lang_id='cs';
UPDATE languages SET charset='iso-8859-2' WHERE lang_id='hu';
UPDATE languages SET charset='iso-8859-2' WHERE lang_id='hr';
UPDATE languages SET charset='iso-8859-2' WHERE lang_id='sr';
UPDATE languages SET charset='iso-8859-3' WHERE lang_id='eo';
UPDATE languages SET charset='iso-8859-3' WHERE lang_id='mt';
UPDATE languages SET charset='iso-8859-5' WHERE lang_id='be';
UPDATE languages SET charset='iso-8859-5' WHERE lang_id='bg';
UPDATE languages SET charset='koi8-r' WHERE lang_id='ru';
UPDATE languages SET charset='iso-8859-5' WHERE lang_id='sh';
UPDATE languages SET charset='iso-8859-5' WHERE lang_id='uk';
UPDATE languages SET charset='iso-8859-6' WHERE lang_id='ar';
UPDATE languages SET charset='iso-8859-7' WHERE lang_id='el';
UPDATE languages SET charset='iso-8859-8-i' WHERE lang_id='iw';
UPDATE languages SET charset='iso-8859-9' WHERE lang_id='tr';
UPDATE languages SET charset='iso-8859-10' WHERE lang_id='kl';
UPDATE languages SET charset='iso-8859-13' WHERE lang_id='lr';
UPDATE languages SET charset='iso-8859-13' WHERE lang_id='lt';
UPDATE languages SET charset='iso-8859-15' WHERE lang_id='et';

# version update
UPDATE pvp_config SET value='0.4.7' WHERE name='version';
