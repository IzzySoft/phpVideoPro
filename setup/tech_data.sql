# $Id$
#
# Data for pvp_options
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://us.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://uk.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://german.imdb.com/');

# Data for pvp_users
#
INSERT INTO pvp_users (login,pwd,admin,browse,ins,upd,del,comment) VALUES ('admin','421b47ffd946ca083b65cd668c6b17e6',1,1,1,1,1,'Administrator');
INSERT INTO pvp_users (login,admin,browse,ins,upd,del,comment) VALUES ('guest',0,1,0,0,0,'Alien Visitor');
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
# Data for table 'disks'
#
INSERT INTO disks (mtype_id,name) VALUES (3,'VCD');
INSERT INTO disks (mtype_id,name) VALUES (3,'SVCD');
INSERT INTO disks (mtype_id,name,size) VALUES (3,'CD-R','650 MB');
INSERT INTO disks (mtype_id,name,size) VALUES (3,'CD-R','720 MB');
INSERT INTO disks (mtype_id,name,size) VALUES (3,'CD-RW','650 MB');
INSERT INTO disks (mtype_id,name,size) VALUES (3,'CD-RW','720 MB');
INSERT INTO disks (mtype_id,name,rc) VALUES (4,'DVD-5',1);
INSERT INTO disks (mtype_id,name,rc) VALUES (4,'DVD-9',1);
INSERT INTO disks (mtype_id,name,size,rc) VALUES (4,'DVD-R','4.7 GB',1);
INSERT INTO disks (mtype_id,name,size,rc) VALUES (4,'DVD-RW','4.7 GB',1);
INSERT INTO disks (mtype_id,name,size,rc) VALUES (4,'DVD+R','4.7 GB',1);
INSERT INTO disks (mtype_id,name,size,rc) VALUES (4,'DVD+RW','4.7 GB',1);

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

INSERT INTO pvp_config (name,value) VALUES ('version','0.6.6');
INSERT INTO pvp_config (name,value) VALUES ('rw_media','1');
INSERT INTO pvp_config (name,value) VALUES ('remove_empty_media','1');
INSERT INTO pvp_config (name,value) VALUES ('site','MySite');
INSERT INTO pvp_config (name,value) VALUES ('enable_cookies','1');
INSERT INTO pvp_config (name,value) VALUES ('expire_cookies','0');
INSERT INTO pvp_config (name,value) VALUES ('session_purgetime','0');

#
# set default preferences
#

INSERT INTO preferences (name,value) VALUES ('lang','en');
INSERT INTO preferences (name,value) VALUES ('charset','iso-8859-1');
INSERT INTO preferences (name,value) VALUES ('template','applicat');
INSERT INTO preferences (name,value) VALUES ('display_limit','30');
INSERT INTO preferences (name,value) VALUES ('date_format','y-m-d');
INSERT INTO preferences (name,value) VALUES ('page_length','85');
INSERT INTO preferences (name,value) VALUES ('default_movie_toneid','2');
INSERT INTO preferences (name,value) VALUES ('default_movie_colorid','2');
INSERT INTO preferences (name,value) VALUES ('default_movie_onlabel','1');
INSERT INTO preferences (name,value) VALUES ('printer_id','1');
INSERT INTO preferences (name,value) VALUES ('imdb_url','http://us.imdb.com/');

#
# list of languages and their keys
#

INSERT INTO languages VALUES ('aa','Afar','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ab','Abkhazian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('af','Afrikaans','UTF-8','No','0','0');
INSERT INTO languages VALUES ('am','Amharic','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ar','Arabic','UTF-8','No','0','0');
INSERT INTO languages VALUES ('as','Assamese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ay','Aymara','UTF-8','No','0','0');
INSERT INTO languages VALUES ('az','Azerbaijani','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ba','Bashkir','UTF-8','No','0','0');
INSERT INTO languages VALUES ('be','Byelorussian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('bg','Bulgarian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('bh','Bihari','UTF-8','No','0','0');
INSERT INTO languages VALUES ('bi','Bislama','UTF-8','No','0','0');
INSERT INTO languages VALUES ('bn','Bengali / Bangla','UTF-8','No','0','0');
INSERT INTO languages VALUES ('bo','Tibetan','UTF-8','No','0','0');
INSERT INTO languages VALUES ('br','Breton','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ca','Catalan','UTF-8','No','0','0');
INSERT INTO languages VALUES ('co','Corsican','UTF-8','No','0','0');
INSERT INTO languages VALUES ('cs','Czech','UTF-8','No','0','1');
INSERT INTO languages VALUES ('cy','Welsh','UTF-8','No','0','0');
INSERT INTO languages VALUES ('da','Danish','UTF-8','No','0','1');
INSERT INTO languages VALUES ('de','German','UTF-8','Yes','1','1');
INSERT INTO languages VALUES ('dz','Bhutani','UTF-8','No','0','0');
INSERT INTO languages VALUES ('el','Greek','UTF-8','No','0','0');
INSERT INTO languages VALUES ('en','English / American','UTF-8','Yes','1','1');
INSERT INTO languages VALUES ('eo','Esperanto','UTF-8','No','0','0');
INSERT INTO languages VALUES ('es','Spanish','UTF-8','No','1','1');
INSERT INTO languages VALUES ('et','Estonian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('eu','Basque','UTF-8','No','0','0');
INSERT INTO languages VALUES ('fa','Persian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('fi','Finnish','UTF-8','No','0','1');
INSERT INTO languages VALUES ('fj','Fiji','UTF-8','No','0','0');
INSERT INTO languages VALUES ('fo','Faeroese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('fr','French','UTF-8','No','1','1');
INSERT INTO languages VALUES ('fy','Frisian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ga','Irish','UTF-8','No','0','0');
INSERT INTO languages VALUES ('gd','Gaelic / Scots Gaelic','UTF-8','No','0','0');
INSERT INTO languages VALUES ('gl','Galician','UTF-8','No','0','0');
INSERT INTO languages VALUES ('gn','Guarani','UTF-8','No','0','0');
INSERT INTO languages VALUES ('gu','Gujarati','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ha','Hausa','UTF-8','No','0','0');
INSERT INTO languages VALUES ('hi','Hindi','UTF-8','No','0','0');
INSERT INTO languages VALUES ('hr','Croatian','UTF-8','No','0','1');
INSERT INTO languages VALUES ('hu','Hungarian','UTF-8','No','0','1');
INSERT INTO languages VALUES ('hy','Armenian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ia','Interlingua','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ie','Interlingue','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ik','Inupiak','UTF-8','No','0','0');
INSERT INTO languages VALUES ('in','Indonesian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('is','Icelandic','UTF-8','No','0','0');
INSERT INTO languages VALUES ('it','Italian','UTF-8','No','1','1');
INSERT INTO languages VALUES ('iw','Hebrew','UTF-8','No','0','1');
INSERT INTO languages VALUES ('ja','Japanese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ji','Yiddish','UTF-8','No','0','0');
INSERT INTO languages VALUES ('jw','Javanese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ka','Georgian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('kk','Kazakh','UTF-8','No','0','0');
INSERT INTO languages VALUES ('kl','Greenlandic','UTF-8','No','0','0');
INSERT INTO languages VALUES ('km','Cambodian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('kn','Kannada','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ko','Korean','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ks','Kashmiri','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ku','Kurdish','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ky','Kirghiz','UTF-8','No','0','0');
INSERT INTO languages VALUES ('la','Latin','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ln','Lingala','UTF-8','No','0','0');
INSERT INTO languages VALUES ('lo','Laothian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('lt','Lithuanian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('lv','Latvian / Lettish','UTF-8','No','0','0');
INSERT INTO languages VALUES ('mg','Malagasy','UTF-8','No','0','0');
INSERT INTO languages VALUES ('mi','Maori','UTF-8','No','0','0');
INSERT INTO languages VALUES ('mk','Macedonian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ml','Malayalam','UTF-8','No','0','0');
INSERT INTO languages VALUES ('mn','Mongolian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('mo','Moldavian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('mr','Marathi','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ms','Malay','UTF-8','No','0','0');
INSERT INTO languages VALUES ('mt','Maltese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('my','Burmese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('na','Nauru','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ne','Nepali','UTF-8','No','0','0');
INSERT INTO languages VALUES ('nl','Dutch','UTF-8','No','0','1');
INSERT INTO languages VALUES ('no','Norwegian','UTF-8','No','0','1');
INSERT INTO languages VALUES ('oc','Occitan','UTF-8','No','0','0');
INSERT INTO languages VALUES ('om','Oromo / Afan','UTF-8','No','0','0');
INSERT INTO languages VALUES ('or','Oriya','UTF-8','No','0','0');
INSERT INTO languages VALUES ('pa','Punjabi','UTF-8','No','0','0');
INSERT INTO languages VALUES ('pl','Polish','UTF-8','No','0','1');
INSERT INTO languages VALUES ('ps','Pashto / Pushto','UTF-8','No','0','0');
INSERT INTO languages VALUES ('pt','Portuguese','UTF-8','No','0','1');
INSERT INTO languages VALUES ('qu','Quechua','UTF-8','No','0','0');
INSERT INTO languages VALUES ('rm','Rhaeto-Romance','UTF-8','No','0','0');
INSERT INTO languages VALUES ('rn','Kirundi','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ro','Romanian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ru','Russian','UTF-8','No','1','1');
INSERT INTO languages VALUES ('rw','Kinyarwanda','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sa','Sanskrit','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sd','Sindhi','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sg','Sangro','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sh','Serbo-Croatian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('si','Singhalese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sk','Slovak','UTF-8','No','0','1');
INSERT INTO languages VALUES ('sl','Slovenian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sm','Samoan','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sn','Shona','UTF-8','No','0','0');
INSERT INTO languages VALUES ('so','Somali','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sq','Albanian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sr','Serbian','UTF-8','No','0','1');
INSERT INTO languages VALUES ('ss','Siswati','UTF-8','No','0','0');
INSERT INTO languages VALUES ('st','Sesotho','UTF-8','No','0','0');
INSERT INTO languages VALUES ('su','Sudanese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('sv','Swedish','UTF-8','No','0','1');
INSERT INTO languages VALUES ('sw','Swahili','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ta','Tamil','UTF-8','No','0','0');
INSERT INTO languages VALUES ('te','Tegulu','UTF-8','No','0','0');
INSERT INTO languages VALUES ('tg','Tajik','UTF-8','No','0','0');
INSERT INTO languages VALUES ('th','Thai','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ti','Tigrinya','UTF-8','No','0','0');
INSERT INTO languages VALUES ('tk','Turkmen','UTF-8','No','0','0');
INSERT INTO languages VALUES ('tl','Tagalog','UTF-8','No','0','0');
INSERT INTO languages VALUES ('tn','Setswana','UTF-8','No','0','0');
INSERT INTO languages VALUES ('to','Tonga','UTF-8','No','0','0');
INSERT INTO languages VALUES ('tr','Turkish','UTF-8','No','0','1');
INSERT INTO languages VALUES ('ts','Tsonga','UTF-8','No','0','0');
INSERT INTO languages VALUES ('tt','Tatar','UTF-8','No','0','0');
INSERT INTO languages VALUES ('tw','Twi','UTF-8','No','0','0');
INSERT INTO languages VALUES ('uk','Ukrainian','UTF-8','No','0','0');
INSERT INTO languages VALUES ('ur','Urdu','UTF-8','No','0','0');
INSERT INTO languages VALUES ('uz','Uzbek','UTF-8','No','0','0');
INSERT INTO languages VALUES ('vi','Vietnamese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('vo','Volapuk','UTF-8','No','0','0');
INSERT INTO languages VALUES ('wo','Wolof','UTF-8','No','0','0');
INSERT INTO languages VALUES ('xh','Xhosa','UTF-8','No','0','0');
INSERT INTO languages VALUES ('yo','Yoruba','UTF-8','No','0','0');
INSERT INTO languages VALUES ('zh','Chinese','UTF-8','No','0','0');
INSERT INTO languages VALUES ('zu','Zulu','UTF-8','No','0','0');
