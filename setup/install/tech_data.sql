# $Id$
#
# Data for pvp_options
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://us.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://uk.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.de/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.es/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.fr/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.it/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://www.imdb.pt/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url','http://akas.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url2','http://us.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url2','http://uk.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_url2','http://akas.imdb.com/');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_title');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_country');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_year');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_pg');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_length');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_cat');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_director');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_music');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_actor');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_comments');
INSERT INTO pvp_options (name,value) VALUES ('imdb_tx','imdb_tx_rating');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://www.moviepilot.de/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://www.moviepilot.com/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://es.moviepilot.com/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://fr.moviepilot.com/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://pl.moviepilot.com/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_url','http://uk.moviepilot.com/');
INSERT INTO pvp_options (name,value) VALUES ('pilot_fallback','NO_ACCESS');
INSERT INTO pvp_options (name,value) VALUES ('pilot_fallback','BASIC_ACCESS');
INSERT INTO pvp_options (name,value) VALUES ('pilot_fallback','MEDIUM_ACCESS');
INSERT INTO pvp_options (name,value) VALUES ('pilot_fallback','FULL_ACCESS');
INSERT INTO pvp_preferences (name,value) VALUES ('pilot_fallback','NO_ACCESS');

# Data for pvp_users
#
INSERT INTO pvp_users (id,login,pwd,admin,browse,ins,upd,del,comment) VALUES (0,'PUBLIC','x',0,1,0,0,0,'Systems publicity');
UPDATE pvp_users SET id=0 WHERE login='PUBLIC';
INSERT INTO pvp_users (login,pwd,admin,browse,ins,upd,del,comment) VALUES ('admin','421b47ffd946ca083b65cd668c6b17e6',1,1,1,1,1,'Administrator');
INSERT INTO pvp_users (login,admin,browse,ins,upd,del,comment) VALUES ('guest',0,1,0,0,0,'Alien Visitor');
#
# Data for table 'colors'
#

INSERT INTO pvp_colors VALUES ( '1', 's/w', 's/w');
INSERT INTO pvp_colors VALUES ( '2', 'Farbe', 'color');
INSERT INTO pvp_colors VALUES ( '3', '3D', '3d');

#
# Data for table 'mtypes'
#

INSERT INTO pvp_mtypes VALUES ( '1', 'Recorded Video Tape', 'RVT');
INSERT INTO pvp_mtypes VALUES ( '2', 'Original Video Tape', 'OVT');
INSERT INTO pvp_mtypes VALUES ( '3', 'VideoCD', 'VCD');
INSERT INTO pvp_mtypes VALUES ( '4', 'Digital Versatile Disk', 'DVD');

#
# Data for table 'pvp_vnorms'
#
INSERT INTO pvp_vnorms VALUES (0,'unknown');
INSERT INTO pvp_vnorms VALUES (1,'PAL');
INSERT INTO pvp_vnorms VALUES (2,'NTSC');

#
# Data for table 'disks'
#
INSERT INTO pvp_disks (mtype_id,name) VALUES (3,'VCD');
INSERT INTO pvp_disks (mtype_id,name) VALUES (3,'SVCD');
INSERT INTO pvp_disks (mtype_id,name,size) VALUES (3,'CD-R','650 MB');
INSERT INTO pvp_disks (mtype_id,name,size) VALUES (3,'CD-R','720 MB');
INSERT INTO pvp_disks (mtype_id,name,size) VALUES (3,'CD-RW','650 MB');
INSERT INTO pvp_disks (mtype_id,name,size) VALUES (3,'CD-RW','720 MB');
INSERT INTO pvp_disks (mtype_id,name,rc) VALUES (4,'DVD-5',1);
INSERT INTO pvp_disks (mtype_id,name,rc) VALUES (4,'DVD-9',1);
INSERT INTO pvp_disks (mtype_id,name,size,rc) VALUES (4,'DVD-R','4.7 GB',1);
INSERT INTO pvp_disks (mtype_id,name,size,rc) VALUES (4,'DVD-RW','4.7 GB',1);
INSERT INTO pvp_disks (mtype_id,name,size,rc) VALUES (4,'DVD+R','4.7 GB',1);
INSERT INTO pvp_disks (mtype_id,name,size,rc) VALUES (4,'DVD+RW','4.7 GB',1);

#
# Data for table 'pict'
#

INSERT INTO pvp_pict VALUES ( '1', '4:3', '4-3');
INSERT INTO pvp_pict VALUES ( '2', '16:9', '16-9');

#
# Data for table 'tone'
#

INSERT INTO pvp_tone VALUES ( '1', 'Mono', '1.0');
INSERT INTO pvp_tone VALUES ( '2', 'Stereo', '2.0');
INSERT INTO pvp_tone VALUES ( '3', '2-Kanal', '2K');
INSERT INTO pvp_tone VALUES ( '4', 'Dolby Surround', '3.0');
INSERT INTO pvp_tone VALUES ( '5', 'Dolby 4.0', '4.0');
INSERT INTO pvp_tone VALUES ( '6', 'Dolby 5.0', '5.0');
INSERT INTO pvp_tone VALUES ( '7', 'Dolby 5.1', '5.1');
INSERT INTO pvp_tone VALUES ( '8', 'Dolby 6.0', '6.0');
INSERT INTO pvp_tone VALUES ( '9', 'Dolby 6.1', '6.1');

#
# table commercials
#

INSERT INTO pvp_commercials VALUES (0,'unknown');
INSERT INTO pvp_commercials VALUES (1,'yes');
INSERT INTO pvp_commercials VALUES (2,'no');
INSERT INTO pvp_commercials VALUES (3,'cut_off');

#
# initial content of table pvp_system
#

INSERT INTO pvp_config (name,value) VALUES ('version','0.9.6');
INSERT INTO pvp_config (name,value) VALUES ('rw_media','1');
INSERT INTO pvp_config (name,value) VALUES ('remove_empty_media','1');
INSERT INTO pvp_config (name,value) VALUES ('site','MySite');
INSERT INTO pvp_config (name,value) VALUES ('enable_cookies','1');
INSERT INTO pvp_config (name,value) VALUES ('expire_cookies','0');
INSERT INTO pvp_config (name,value) VALUES ('session_purgetime','0');
INSERT INTO pvp_config (name,value) VALUES ('http_cache_enable','0');
INSERT INTO pvp_config (name,value) VALUES ('imdb_cache_enable','0');
INSERT INTO pvp_config (name,value) VALUES ('imdb_cache_use','0');
INSERT INTO pvp_config (name,value) VALUES ('use_http_auth','0');
INSERT INTO pvp_config (name,value) VALUES ('user_backup_download','0');
INSERT INTO pvp_config (name,value) VALUES ('user_backup_store','0');
INSERT INTO pvp_config (name,value) VALUES ('user_backup_restore','0');
INSERT INTO pvp_config (name,value) VALUES ('max_user_backups','3');

#
# set default preferences
#

INSERT INTO pvp_preferences (name,value) VALUES ('lang','en');
INSERT INTO pvp_preferences (name,value) VALUES ('charset','utf-8');
INSERT INTO pvp_preferences (name,value) VALUES ('template','applicat');
INSERT INTO pvp_preferences (name,value) VALUES ('display_limit','30');
INSERT INTO pvp_preferences (name,value) VALUES ('date_format','y-m-d');
INSERT INTO pvp_preferences (name,value) VALUES ('page_length','85');
INSERT INTO pvp_preferences (name,value) VALUES ('default_movie_toneid','2');
INSERT INTO pvp_preferences (name,value) VALUES ('default_movie_colorid','2');
INSERT INTO pvp_preferences (name,value) VALUES ('default_movie_onlabel','1');
INSERT INTO pvp_preferences (name,value) VALUES ('printer_id','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_url','http://akas.imdb.com/');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_url2','http://akas.imdb.com/');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_title','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_country','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_year','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_pg','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_length','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_cat','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_director','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_music','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_actor','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_tx_comments','1');
INSERT INTO pvp_preferences (name,value) VALUES ('imdb_txwin_autoclose','1');
INSERT INTO pvp_preferences (name,value) VALUES ('pilot_url','http://www.moviepilot.com/');
INSERT INTO pvp_preferences (name,value) VALUES ('default_pstemplate_id','1');
INSERT INTO pvp_preferences (name,value) VALUES ('default_editor','plain');
INSERT INTO pvp_preferences (name,value) VALUES ('pilot_fallback','NO_ACCESS');
INSERT INTO pvp_preferences (name,value) VALUES ('mdb_use','0');
