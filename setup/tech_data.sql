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

INSERT INTO pvp_config (name,value) VALUES ('version','0.7.0');
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

