# ========================================================
# Updating Database for phpVideoPro from v0.6.6 to v0.7.0
# ========================================================

# prepare default lang update
# DELETE FROM lang WHERE lang='en';

# language names
UPDATE languages SET lang_name='አማርኛ' WHERE lang_id='am';
UPDATE languages SET lang_name='عربي' WHERE lang_id='ar';
UPDATE languages SET lang_name='Azərbaycanca' WHERE lang_id='az';
UPDATE languages SET lang_name='Ar brezhoneg' WHERE lang_id='br';
UPDATE languages SET lang_name='Català' WHERE lang_id='ca';
UPDATE languages SET lang_name='Corsu' WHERE lang_id='co';
UPDATE languages SET lang_name='Čeština' WHERE lang_id='cs';
UPDATE languages SET lang_name='Cymraeg' WHERE lang_id='cy';
UPDATE languages SET lang_name='Dansk' WHERE lang_id='da';
UPDATE languages SET lang_name='Deutsch' WHERE lang_id='de';
UPDATE languages SET lang_name='Ελληνικά' WHERE lang_id='el';
UPDATE languages SET lang_name='English' WHERE lang_id='en';
UPDATE languages SET lang_name='Español' WHERE lang_id='es';
UPDATE languages SET lang_name='Eesti' WHERE lang_id='et';
UPDATE languages SET lang_name='Euskara' WHERE lang_id='eu';
UPDATE languages SET lang_name='Fārsī' WHERE lang_id='fa';
UPDATE languages SET lang_name='Suomalainen' WHERE lang_id='fi';
UPDATE languages SET lang_name='Føroyskt' WHERE lang_id='fo';
UPDATE languages SET lang_name='Français' WHERE lang_id='fr';
UPDATE languages SET lang_name='Gaeilge na hÉireann' WHERE lang_id='ga';
UPDATE languages SET lang_name='Gàidhlig' WHERE lang_id='gd';
UPDATE languages SET lang_name='Gallego' WHERE lang_id='gl';
UPDATE languages SET lang_name='Hrvatski' WHERE lang_id='hr';
UPDATE languages SET lang_name='Magyar' WHERE lang_id='hu';
UPDATE languages SET lang_name='Íslensku' WHERE lang_id='is';
UPDATE languages SET lang_name='Italiano' WHERE lang_id='it';
UPDATE languages SET lang_name='עברית' WHERE lang_id='iw';
UPDATE languages SET lang_name='Mkhedruli' WHERE lang_id='ka';
UPDATE languages SET lang_name='Kurdî ' WHERE lang_id='ku';
UPDATE languages SET lang_name='Lietuvių' WHERE lang_id='lt';
UPDATE languages SET lang_name='Latviešu' WHERE lang_id='lv';
UPDATE languages SET lang_name='Македонски' WHERE lang_id='mk';
UPDATE languages SET lang_name='Malti' WHERE lang_id='mt';
UPDATE languages SET lang_name='Nederlands' WHERE lang_id='nl';
UPDATE languages SET lang_name='Norsk' WHERE lang_id='no';
UPDATE languages SET lang_name='Polski' WHERE lang_id='pl';
UPDATE languages SET lang_name='Português' WHERE lang_id='pt';
UPDATE languages SET lang_name='Limba Română' WHERE lang_id='ro';
UPDATE languages SET lang_name='Русский' WHERE lang_id='ru';
UPDATE languages SET lang_name='Slovenský' WHERE lang_id='sk';
UPDATE languages SET lang_name='Slovenščina' WHERE lang_id='sl';
UPDATE languages SET lang_name='Shqip' WHERE lang_id='sq';
UPDATE languages SET lang_name='Српски' WHERE lang_id='sr';
UPDATE languages SET lang_name='Svenska' WHERE lang_id='sv';
UPDATE languages SET lang_name='Türkçe' WHERE lang_id='tr';
UPDATE languages SET lang_name='Việt ngữ' WHERE lang_id='vi';

# version update
UPDATE pvp_config SET value='0.7.0' WHERE name='version';
