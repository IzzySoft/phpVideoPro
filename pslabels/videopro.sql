-- MySQL dump 8.21
--
-- Host: localhost    Database: videopro
---------------------------------------------------------
-- Server version	3.23.48-log

--
-- Table structure for table 'eps_templates'
--

DROP TABLE IF EXISTS eps_templates;
CREATE TABLE eps_templates (
  id smallint(6) NOT NULL default '0',
  type int(11) NOT NULL default '0',
  description varchar(64) NOT NULL default '',
  eps_filename varchar(255) NOT NULL default '',
  ps_filename varchar(255) NOT NULL default '',
  llx smallint(6) NOT NULL default '0',
  lly smallint(6) NOT NULL default '0',
  urx smallint(6) NOT NULL default '0',
  ury smallint(6) NOT NULL default '0',
  PRIMARY KEY  (id),
  UNIQUE KEY id (id),
  FULLTEXT KEY description (description)
) TYPE=MyISAM COMMENT='bounding box of eps template';

--
-- Dumping data for table 'eps_templates'
--


INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (1,2,'action_side','action_side.eps','action_side.ps',0,0,513,68);
INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (2,2,'default_side','simple_side.eps','simple_side.ps',0,0,414,54);
INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (3,1,'default_top','simple_top.eps','simple_top.ps',0,0,223,126);
INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (4,1,'action_top','action_top.eps','action_top.ps',0,0,273,160);

--
-- Table structure for table 'label_forms'
--

DROP TABLE IF EXISTS label_forms;
CREATE TABLE label_forms (
  id tinyint(4) NOT NULL auto_increment,
  vendor char(16) NOT NULL default '',
  product char(32) NOT NULL default '',
  description char(48) default NULL,
  type int(11) NOT NULL default '0',
  unit_id int(11) NOT NULL default '0',
  h_dist float NOT NULL default '0',
  v_dist float NOT NULL default '0',
  width float NOT NULL default '0',
  heigth float NOT NULL default '0',
  leftm float NOT NULL default '0',
  topm float NOT NULL default '0',
  cols tinyint(4) NOT NULL default '0',
  rows tinyint(4) NOT NULL default '0',
  sheet_id tinyint(4) NOT NULL default '0',
  PRIMARY KEY  (id),
  UNIQUE KEY id (id),
  KEY id_2 (id)
) TYPE=MyISAM COMMENT='label definition table';

--
-- Dumping data for table 'label_forms'
--


INSERT INTO label_forms (id, vendor, product, description, type, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (1,'Zweckform','4742 Inkjet+Laser, S+L Video TOP','VHS video cass. top label',1,3,8.13,4.66,7.87,4.66,2.5,0.87,2,6,1);
INSERT INTO label_forms (id, vendor, product, description, type, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (2,'Zweckform','4746 Inkjet+Laser, S+L,vid. SIDE','VHS cass. SIDE label',2,3,14.73,2,14.73,2,3.13,1.84,1,13,1);

--
-- Table structure for table 'label_type'
--

DROP TABLE IF EXISTS label_type;
CREATE TABLE label_type (
  id tinyint(4) NOT NULL auto_increment,
  vendor char(16) NOT NULL default '',
  product char(32) NOT NULL default '',
  description char(48) default NULL,
  unit_id int(11) NOT NULL default '0',
  h_dist float NOT NULL default '0',
  v_dist float NOT NULL default '0',
  width float NOT NULL default '0',
  heigth float NOT NULL default '0',
  leftm float NOT NULL default '0',
  topm float NOT NULL default '0',
  cols tinyint(4) NOT NULL default '0',
  rows tinyint(4) NOT NULL default '0',
  sheet_id tinyint(4) NOT NULL default '0',
  PRIMARY KEY  (id),
  UNIQUE KEY id (id),
  KEY id_2 (id)
) TYPE=MyISAM COMMENT='label definition table';

--
-- Dumping data for table 'label_type'
--


INSERT INTO label_type (id, vendor, product, description, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (1,'Zweckform','4742 Inkjet+Laser, S+L Video TOP','VHS video cass. top label',3,8.13,4.66,7.87,4.66,2.5,0.87,2,6,1);
INSERT INTO label_type (id, vendor, product, description, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (2,'Zweckform','4746 Inkjet+Laser, S+L,vid. SIDE','VHS cass. SIDE label',3,14.73,2,14.73,2,3.13,1.84,1,13,1);

--
-- Table structure for table 'label_types'
--

DROP TABLE IF EXISTS label_types;
CREATE TABLE label_types (
  id smallint(6) NOT NULL default '0',
  description varchar(64) NOT NULL default '',
  PRIMARY KEY  (id),
  UNIQUE KEY id (id)
) TYPE=MyISAM;

--
-- Dumping data for table 'label_types'
--


INSERT INTO label_types (id, description) VALUES (1,'VHS top label');
INSERT INTO label_types (id, description) VALUES (2,'VHS side label');

--
-- Table structure for table 'printers'
--

DROP TABLE IF EXISTS printers;
CREATE TABLE printers (
  id tinyint(4) NOT NULL default '0',
  name varchar(32) NOT NULL default '',
  unit_id tinyint(4) NOT NULL default '0',
  top_offset float NOT NULL default '0',
  left_offset float NOT NULL default '0',
  PRIMARY KEY  (id),
  UNIQUE KEY id (id)
) TYPE=MyISAM COMMENT='Printer offset definition';

--
-- Dumping data for table 'printers'
--


INSERT INTO printers (id, name, unit_id, top_offset, left_offset) VALUES (1,'OKI 610ex',4,5.5,4.5);
INSERT INTO printers (id, name, unit_id, top_offset, left_offset) VALUES (2,'EPSON Stylus Photo 890',0,0,0);

--
-- Table structure for table 'sheets'
--

DROP TABLE IF EXISTS sheets;
CREATE TABLE sheets (
  id tinyint(4) NOT NULL auto_increment,
  name char(16) NOT NULL default '',
  unit_id int(11) NOT NULL default '0',
  width float NOT NULL default '0',
  length float NOT NULL default '0',
  PRIMARY KEY  (id),
  UNIQUE KEY id (id),
  KEY id_2 (id)
) TYPE=MyISAM COMMENT='label print sheet description';

--
-- Dumping data for table 'sheets'
--


INSERT INTO sheets (id, name, unit_id, width, length) VALUES (1,'a4',3,21,29.7);

--
-- Table structure for table 'units'
--

DROP TABLE IF EXISTS units;
CREATE TABLE units (
  id int(11) NOT NULL auto_increment,
  unit char(8) NOT NULL default '',
  size float NOT NULL default '0',
  PRIMARY KEY  (id),
  UNIQUE KEY id (id),
  KEY id_2 (id)
) TYPE=MyISAM COMMENT='unit conversion table';

--
-- Dumping data for table 'units'
--


INSERT INTO units (id, unit, size) VALUES (1,'pt',1);
INSERT INTO units (id, unit, size) VALUES (2,'inch',72);
INSERT INTO units (id, unit, size) VALUES (3,'cm',28.3465);
INSERT INTO units (id, unit, size) VALUES (4,'mm',2.8346);