#
# Data for table 'colors'
#

INSERT INTO colors VALUES ( '1', 's/w', 's/w');
INSERT INTO colors VALUES ( '2', 'Farbe', 'color');
INSERT INTO colors VALUES ( '3', '3D', '3d');

#
# Data for table 'mtypes'
#

INSERT INTO mtypes VALUES ( '1', 'Recorded Video Tape', 'RVT');
INSERT INTO mtypes VALUES ( '2', 'Original Video Tape', 'OVT');
INSERT INTO mtypes VALUES ( '3', 'VideoCD', 'VCD');
INSERT INTO mtypes VALUES ( '4', 'Digital Versatile Disk', 'DVD');

#
# Data for table 'pict'
#

INSERT INTO pict VALUES ( '1', '4:3', '4-3');
INSERT INTO pict VALUES ( '2', '16:9', '16-9');

#
# Data for table 'tone'
#

INSERT INTO tone VALUES ( '1', 'Mono', '1.0');
INSERT INTO tone VALUES ( '2', 'Stereo', '2.0');
INSERT INTO tone VALUES ( '3', '2-Kanal', '2K');
INSERT INTO tone VALUES ( '4', 'Dolby Surround', '3.0');
INSERT INTO tone VALUES ( '5', 'Dolby 4.0', '4.0');
INSERT INTO tone VALUES ( '6', 'Dolby 5.0', '5.0');
INSERT INTO tone VALUES ( '7', 'Dolby 5.1', '5.1');
INSERT INTO tone VALUES ( '8', 'Dolby 6.0', '6.0');
INSERT INTO tone VALUES ( '9', 'Dolby 6.1', '6.1');

#
# table commercials
#

INSERT INTO commercials VALUES (0,'unknown');
INSERT INTO commercials VALUES (1,'yes');
INSERT INTO commercials VALUES (2,'no');
INSERT INTO commercials VALUES (3,'cut_off');

#
# initial content of table pvp_system
#

INSERT INTO pvp_config (name,value) VALUES ('version','0.2.6');

#
# set default preferences
#

INSERT INTO preferences (name,value) VALUES ('lang','en');
INSERT INTO preferences (name,value) VALUES ('charset','iso-8859-1');
INSERT INTO preferences (name,value) VALUES ('colors','a%3A5%3A%7Bs%3A15%3A%22page_background%22%3Bs%3A7%3A%22%236699ff%22%3Bs%3A13%3A%22th_background%22%3Bs%3A7%3A%22%23ffff99%22%3Bs%3A2%3A%22ok%22%3Bs%3A7%3A%22%230000ff%22%3Bs%3A3%3A%22err%22%3Bs%3A7%3A%22%23ff0000%22%3Bs%3A16%3A%22table_background%22%3Bs%3A7%3A%22%23ffffff%22%3B%7D');
INSERT INTO preferences (name,value) VALUES ('template','default');
INSERT INTO preferences (name,value) VALUES ('display_limit','30');
INSERT INTO preferences (name,value) VALUES ('date_format','y-m-d');
INSERT INTO preferences (name,value) VALUES ('page_length','85');

#
# list of languages and their keys
#

INSERT INTO languages VALUES ('aa','Afar','','No');
INSERT INTO languages VALUES ('ab','Abkhazian','','No');
INSERT INTO languages VALUES ('af','Afrikaans','','No');
INSERT INTO languages VALUES ('am','Amharic','','No');
INSERT INTO languages VALUES ('ar','Arabic','','No');
INSERT INTO languages VALUES ('as','Assamese','','No');
INSERT INTO languages VALUES ('ay','Aymara','','No');
INSERT INTO languages VALUES ('az','Azerbaijani','','No');
INSERT INTO languages VALUES ('ba','Bashkir','','No');
INSERT INTO languages VALUES ('be','Byelorussian','','No');
INSERT INTO languages VALUES ('bg','Bulgarian','','No');
INSERT INTO languages VALUES ('bh','Bihari','','No');
INSERT INTO languages VALUES ('bi','Bislama','','No');
INSERT INTO languages VALUES ('bn','Bengali / Bangla','','No');
INSERT INTO languages VALUES ('bo','Tibetan','','No');
INSERT INTO languages VALUES ('br','Breton','','No');
INSERT INTO languages VALUES ('ca','Catalan','','No');
INSERT INTO languages VALUES ('co','Corsican','','No');
INSERT INTO languages VALUES ('cs','Czech','','No');
INSERT INTO languages VALUES ('cy','Welsh','','No');
INSERT INTO languages VALUES ('da','Danish','','No');
INSERT INTO languages VALUES ('de','German','iso-8859-1','Yes');
INSERT INTO languages VALUES ('dz','Bhutani','','No');
INSERT INTO languages VALUES ('el','Greek','','No');
INSERT INTO languages VALUES ('en','English / American','iso-8859-1','Yes');
INSERT INTO languages VALUES ('eo','Esperanto','','No');
INSERT INTO languages VALUES ('es','Spanish','','No');
INSERT INTO languages VALUES ('et','Estonian','','No');
INSERT INTO languages VALUES ('eu','Basque','','No');
INSERT INTO languages VALUES ('fa','Persian','','No');
INSERT INTO languages VALUES ('fi','Finnish','','No');
INSERT INTO languages VALUES ('fj','Fiji','','No');
INSERT INTO languages VALUES ('fo','Faeroese','','No');
INSERT INTO languages VALUES ('fr','French','','No');
INSERT INTO languages VALUES ('fy','Frisian','','No');
INSERT INTO languages VALUES ('ga','Irish','','No');
INSERT INTO languages VALUES ('gd','Gaelic / Scots Gaelic','','No');
INSERT INTO languages VALUES ('gl','Galician','','No');
INSERT INTO languages VALUES ('gn','Guarani','','No');
INSERT INTO languages VALUES ('gu','Gujarati','','No');
INSERT INTO languages VALUES ('ha','Hausa','','No');
INSERT INTO languages VALUES ('hi','Hindi','','No');
INSERT INTO languages VALUES ('hr','Croatian','','No');
INSERT INTO languages VALUES ('hu','Hungarian','','No');
INSERT INTO languages VALUES ('hy','Armenian','','No');
INSERT INTO languages VALUES ('ia','Interlingua','','No');
INSERT INTO languages VALUES ('ie','Interlingue','','No');
INSERT INTO languages VALUES ('ik','Inupiak','','No');
INSERT INTO languages VALUES ('in','Indonesian','','No');
INSERT INTO languages VALUES ('is','Icelandic','','No');
INSERT INTO languages VALUES ('it','Italian','','No');
INSERT INTO languages VALUES ('iw','Hebrew','','No');
INSERT INTO languages VALUES ('ja','Japanese','','No');
INSERT INTO languages VALUES ('ji','Yiddish','','No');
INSERT INTO languages VALUES ('jw','Javanese','','No');
INSERT INTO languages VALUES ('ka','Georgian','','No');
INSERT INTO languages VALUES ('kk','Kazakh','','No');
INSERT INTO languages VALUES ('kl','Greenlandic','','No');
INSERT INTO languages VALUES ('km','Cambodian','','No');
INSERT INTO languages VALUES ('kn','Kannada','','No');
INSERT INTO languages VALUES ('ko','Korean','','No');
INSERT INTO languages VALUES ('ks','Kashmiri','','No');
INSERT INTO languages VALUES ('ku','Kurdish','','No');
INSERT INTO languages VALUES ('ky','Kirghiz','','No');
INSERT INTO languages VALUES ('la','Latin','','No');
INSERT INTO languages VALUES ('ln','Lingala','','No');
INSERT INTO languages VALUES ('lo','Laothian','','No');
INSERT INTO languages VALUES ('lt','Lithuanian','','No');
INSERT INTO languages VALUES ('lv','Latvian / Lettish','','No');
INSERT INTO languages VALUES ('mg','Malagasy','','No');
INSERT INTO languages VALUES ('mi','Maori','','No');
INSERT INTO languages VALUES ('mk','Macedonian','','No');
INSERT INTO languages VALUES ('ml','Malayalam','','No');
INSERT INTO languages VALUES ('mn','Mongolian','','No');
INSERT INTO languages VALUES ('mo','Moldavian','','No');
INSERT INTO languages VALUES ('mr','Marathi','','No');
INSERT INTO languages VALUES ('ms','Malay','','No');
INSERT INTO languages VALUES ('mt','Maltese','','No');
INSERT INTO languages VALUES ('my','Burmese','','No');
INSERT INTO languages VALUES ('na','Nauru','','No');
INSERT INTO languages VALUES ('ne','Nepali','','No');
INSERT INTO languages VALUES ('nl','Dutch','','No');
INSERT INTO languages VALUES ('no','Norwegian','','No');
INSERT INTO languages VALUES ('oc','Occitan','','No');
INSERT INTO languages VALUES ('om','Oromo / Afan','','No');
INSERT INTO languages VALUES ('or','Oriya','','No');
INSERT INTO languages VALUES ('pa','Punjabi','','No');
INSERT INTO languages VALUES ('pl','Polish','','No');
INSERT INTO languages VALUES ('ps','Pashto / Pushto','','No');
INSERT INTO languages VALUES ('pt','Portuguese','','No');
INSERT INTO languages VALUES ('qu','Quechua','','No');
INSERT INTO languages VALUES ('rm','Rhaeto-Romance','','No');
INSERT INTO languages VALUES ('rn','Kirundi','','No');
INSERT INTO languages VALUES ('ro','Romanian','','No');
INSERT INTO languages VALUES ('ru','Russian','','No');
INSERT INTO languages VALUES ('rw','Kinyarwanda','','No');
INSERT INTO languages VALUES ('sa','Sanskrit','','No');
INSERT INTO languages VALUES ('sd','Sindhi','','No');
INSERT INTO languages VALUES ('sg','Sangro','','No');
INSERT INTO languages VALUES ('sh','Serbo-Croatian','','No');
INSERT INTO languages VALUES ('si','Singhalese','','No');
INSERT INTO languages VALUES ('sk','Slovak','','No');
INSERT INTO languages VALUES ('sl','Slovenian','','No');
INSERT INTO languages VALUES ('sm','Samoan','','No');
INSERT INTO languages VALUES ('sn','Shona','','No');
INSERT INTO languages VALUES ('so','Somali','','No');
INSERT INTO languages VALUES ('sq','Albanian','','No');
INSERT INTO languages VALUES ('sr','Serbian','','No');
INSERT INTO languages VALUES ('ss','Siswati','','No');
INSERT INTO languages VALUES ('st','Sesotho','','No');
INSERT INTO languages VALUES ('su','Sudanese','','No');
INSERT INTO languages VALUES ('sv','Swedish','','No');
INSERT INTO languages VALUES ('sw','Swahili','','No');
INSERT INTO languages VALUES ('ta','Tamil','','No');
INSERT INTO languages VALUES ('te','Tegulu','','No');
INSERT INTO languages VALUES ('tg','Tajik','','No');
INSERT INTO languages VALUES ('th','Thai','','No');
INSERT INTO languages VALUES ('ti','Tigrinya','','No');
INSERT INTO languages VALUES ('tk','Turkmen','','No');
INSERT INTO languages VALUES ('tl','Tagalog','','No');
INSERT INTO languages VALUES ('tn','Setswana','','No');
INSERT INTO languages VALUES ('to','Tonga','','No');
INSERT INTO languages VALUES ('tr','Turkish','','No');
INSERT INTO languages VALUES ('ts','Tsonga','','No');
INSERT INTO languages VALUES ('tt','Tatar','','No');
INSERT INTO languages VALUES ('tw','Twi','','No');
INSERT INTO languages VALUES ('uk','Ukrainian','','No');
INSERT INTO languages VALUES ('ur','Urdu','','No');
INSERT INTO languages VALUES ('uz','Uzbek','','No');
INSERT INTO languages VALUES ('vi','Vietnamese','','No');
INSERT INTO languages VALUES ('vo','Volapuk','','No');
INSERT INTO languages VALUES ('wo','Wolof','','No');
INSERT INTO languages VALUES ('xh','Xhosa','','No');
INSERT INTO languages VALUES ('yo','Yoruba','','No');
INSERT INTO languages VALUES ('zh','Chinese','','No');
INSERT INTO languages VALUES ('zu','Zulu','','No');
