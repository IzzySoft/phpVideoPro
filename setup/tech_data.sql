# $Id$
#
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

INSERT INTO pvp_config (name,value) VALUES ('version','0.6.1');
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

#
# list of languages and their keys
#

INSERT INTO languages VALUES ('aa','Afar','','No');
INSERT INTO languages VALUES ('ab','Abkhazian','','No');
INSERT INTO languages VALUES ('af','Afrikaans','','No');
INSERT INTO languages VALUES ('am','Amharic','','No');
INSERT INTO languages VALUES ('ar','Arabic','iso-8859-6','No');
INSERT INTO languages VALUES ('as','Assamese','','No');
INSERT INTO languages VALUES ('ay','Aymara','','No');
INSERT INTO languages VALUES ('az','Azerbaijani','','No');
INSERT INTO languages VALUES ('ba','Bashkir','','No');
INSERT INTO languages VALUES ('be','Byelorussian','iso-8859-5','No');
INSERT INTO languages VALUES ('bg','Bulgarian','iso-8859-5','No');
INSERT INTO languages VALUES ('bh','Bihari','','No');
INSERT INTO languages VALUES ('bi','Bislama','','No');
INSERT INTO languages VALUES ('bn','Bengali / Bangla','','No');
INSERT INTO languages VALUES ('bo','Tibetan','','No');
INSERT INTO languages VALUES ('br','Breton','','No');
INSERT INTO languages VALUES ('ca','Catalan','iso-8859-1','No');
INSERT INTO languages VALUES ('co','Corsican','','No');
INSERT INTO languages VALUES ('cs','Czech','iso-8859-2','No');
INSERT INTO languages VALUES ('cy','Welsh','','No');
INSERT INTO languages VALUES ('da','Danish','iso-8859-1','No');
INSERT INTO languages VALUES ('de','German','iso-8859-1','Yes');
INSERT INTO languages VALUES ('dz','Bhutani','','No');
INSERT INTO languages VALUES ('el','Greek','iso-8859-7','No');
INSERT INTO languages VALUES ('en','English / American','iso-8859-1','Yes');
INSERT INTO languages VALUES ('eo','Esperanto','iso-8859-3','No');
INSERT INTO languages VALUES ('es','Spanish','iso-8859-1','No');
INSERT INTO languages VALUES ('et','Estonian','iso-8859-15','No');
INSERT INTO languages VALUES ('eu','Basque','iso-8859-1','No');
INSERT INTO languages VALUES ('fa','Persian','','No');
INSERT INTO languages VALUES ('fi','Finnish','','No');
INSERT INTO languages VALUES ('fj','Fiji','','No');
INSERT INTO languages VALUES ('fo','Faeroese','iso-8859-1','No');
INSERT INTO languages VALUES ('fr','French','','No');
INSERT INTO languages VALUES ('fy','Frisian','','No');
INSERT INTO languages VALUES ('ga','Irish','iso-8859-1','No');
INSERT INTO languages VALUES ('gd','Gaelic / Scots Gaelic','iso-8859-1','No');
INSERT INTO languages VALUES ('gl','Galician','iso-8859-1','No');
INSERT INTO languages VALUES ('gn','Guarani','','No');
INSERT INTO languages VALUES ('gu','Gujarati','','No');
INSERT INTO languages VALUES ('ha','Hausa','','No');
INSERT INTO languages VALUES ('hi','Hindi','','No');
INSERT INTO languages VALUES ('hr','Croatian','iso-8859-2','No');
INSERT INTO languages VALUES ('hu','Hungarian','iso-8859-2','No');
INSERT INTO languages VALUES ('hy','Armenian','','No');
INSERT INTO languages VALUES ('ia','Interlingua','','No');
INSERT INTO languages VALUES ('ie','Interlingue','','No');
INSERT INTO languages VALUES ('ik','Inupiak','','No');
INSERT INTO languages VALUES ('in','Indonesian','','No');
INSERT INTO languages VALUES ('is','Icelandic','iso-8859-1','No');
INSERT INTO languages VALUES ('it','Italian','iso-8859-1','No');
INSERT INTO languages VALUES ('iw','Hebrew','iso-8859-8-i','No');
INSERT INTO languages VALUES ('ja','Japanese','','No');
INSERT INTO languages VALUES ('ji','Yiddish','','No');
INSERT INTO languages VALUES ('jw','Javanese','','No');
INSERT INTO languages VALUES ('ka','Georgian','','No');
INSERT INTO languages VALUES ('kk','Kazakh','','No');
INSERT INTO languages VALUES ('kl','Greenlandic','iso-8859-10','No');
INSERT INTO languages VALUES ('km','Cambodian','','No');
INSERT INTO languages VALUES ('kn','Kannada','','No');
INSERT INTO languages VALUES ('ko','Korean','','No');
INSERT INTO languages VALUES ('ks','Kashmiri','','No');
INSERT INTO languages VALUES ('ku','Kurdish','','No');
INSERT INTO languages VALUES ('ky','Kirghiz','','No');
INSERT INTO languages VALUES ('la','Latin','','No');
INSERT INTO languages VALUES ('ln','Lingala','','No');
INSERT INTO languages VALUES ('lo','Laothian','','No');
INSERT INTO languages VALUES ('lt','Lithuanian','iso-8859-13','No');
INSERT INTO languages VALUES ('lv','Latvian / Lettish','iso-8859-13','No');
INSERT INTO languages VALUES ('mg','Malagasy','','No');
INSERT INTO languages VALUES ('mi','Maori','','No');
INSERT INTO languages VALUES ('mk','Macedonian','iso-8859-5','No');
INSERT INTO languages VALUES ('ml','Malayalam','','No');
INSERT INTO languages VALUES ('mn','Mongolian','','No');
INSERT INTO languages VALUES ('mo','Moldavian','','No');
INSERT INTO languages VALUES ('mr','Marathi','','No');
INSERT INTO languages VALUES ('ms','Malay','','No');
INSERT INTO languages VALUES ('mt','Maltese','iso-8859-3','No');
INSERT INTO languages VALUES ('my','Burmese','','No');
INSERT INTO languages VALUES ('na','Nauru','','No');
INSERT INTO languages VALUES ('ne','Nepali','','No');
INSERT INTO languages VALUES ('nl','Dutch','iso-8859-1','No');
INSERT INTO languages VALUES ('no','Norwegian','iso-8859-1','No');
INSERT INTO languages VALUES ('oc','Occitan','','No');
INSERT INTO languages VALUES ('om','Oromo / Afan','','No');
INSERT INTO languages VALUES ('or','Oriya','','No');
INSERT INTO languages VALUES ('pa','Punjabi','','No');
INSERT INTO languages VALUES ('pl','Polish','iso-8859-2','No');
INSERT INTO languages VALUES ('ps','Pashto / Pushto','','No');
INSERT INTO languages VALUES ('pt','Portuguese','iso-8859-1','No');
INSERT INTO languages VALUES ('qu','Quechua','','No');
INSERT INTO languages VALUES ('rm','Rhaeto-Romance','','No');
INSERT INTO languages VALUES ('rn','Kirundi','','No');
INSERT INTO languages VALUES ('ro','Romanian','iso-8859-2','No');
INSERT INTO languages VALUES ('ru','Russian','iso-8859-5','No');
INSERT INTO languages VALUES ('rw','Kinyarwanda','','No');
INSERT INTO languages VALUES ('sa','Sanskrit','','No');
INSERT INTO languages VALUES ('sd','Sindhi','','No');
INSERT INTO languages VALUES ('sg','Sangro','','No');
INSERT INTO languages VALUES ('sh','Serbo-Croatian','iso-8859-5','No');
INSERT INTO languages VALUES ('si','Singhalese','','No');
INSERT INTO languages VALUES ('sk','Slovak','iso-8859-2','No');
INSERT INTO languages VALUES ('sl','Slovenian','iso-8859-2','No');
INSERT INTO languages VALUES ('sm','Samoan','','No');
INSERT INTO languages VALUES ('sn','Shona','','No');
INSERT INTO languages VALUES ('so','Somali','','No');
INSERT INTO languages VALUES ('sq','Albanian','iso-8859-1','No');
INSERT INTO languages VALUES ('sr','Serbian','iso-8859-2','No');
INSERT INTO languages VALUES ('ss','Siswati','','No');
INSERT INTO languages VALUES ('st','Sesotho','','No');
INSERT INTO languages VALUES ('su','Sudanese','','No');
INSERT INTO languages VALUES ('sv','Swedish','iso-8859-1','No');
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
INSERT INTO languages VALUES ('tr','Turkish','iso-8859-9','No');
INSERT INTO languages VALUES ('ts','Tsonga','','No');
INSERT INTO languages VALUES ('tt','Tatar','','No');
INSERT INTO languages VALUES ('tw','Twi','','No');
INSERT INTO languages VALUES ('uk','Ukrainian','iso-8859-5','No');
INSERT INTO languages VALUES ('ur','Urdu','','No');
INSERT INTO languages VALUES ('uz','Uzbek','','No');
INSERT INTO languages VALUES ('vi','Vietnamese','','No');
INSERT INTO languages VALUES ('vo','Volapuk','','No');
INSERT INTO languages VALUES ('wo','Wolof','','No');
INSERT INTO languages VALUES ('xh','Xhosa','','No');
INSERT INTO languages VALUES ('yo','Yoruba','','No');
INSERT INTO languages VALUES ('zh','Chinese','','No');
INSERT INTO languages VALUES ('zu','Zulu','','No');
