#
# Table structure and data for 'eps templates bounding box definition'
#

CREATE TABLE eps_templates (
  id numeric(6) NOT NULL default '0' UNIQUE,
  type numeric(11) NOT NULL default '0',
  description varchar(64) NOT NULL default '',
  eps_filename varchar(255) NOT NULL default '',
  ps_filename varchar(255) NOT NULL default '',
  llx numeric(6) NOT NULL default '0',
  lly numeric(6) NOT NULL default '0',
  urx numeric(6) NOT NULL default '0',
  ury numeric(6) NOT NULL default '0',
  PRIMARY KEY  (id)
);

CREATE INDEX eps_templates_desc ON eps_templates (description);

INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (1,2,'action_side','action_side.eps','common_side.ps',0,0,513,68);
INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (2,2,'default_side','simple_side.eps','simple_side.ps',0,0,414,54);
INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (3,1,'default_top','simple_top.eps','simple_top.ps',0,0,223,126);
INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (4,1,'action_top','action_top.eps','common_top.ps',0,0,273,160);
INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (5,2,'sf_side','sf_side.eps','common_side.ps',0,0,513,68);
INSERT INTO eps_templates (id, type, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (6,1,'sf_top','sf_top.eps','common_top.ps',0,0,273,160);

#
# Table structure and data for 'label form definition'
#

CREATE TABLE label_forms (
  id serial,
  vendor char(16) NOT NULL default '',
  product char(32) NOT NULL default '',
  description char(48) default NULL,
  type numeric(11) NOT NULL default '0',
  unit_id numeric(11) NOT NULL default '0',
  h_dist numeric NOT NULL default '0',
  v_dist numeric NOT NULL default '0',
  width numeric NOT NULL default '0',
  heigth numeric NOT NULL default '0',
  leftm numeric NOT NULL default '0',
  topm numeric NOT NULL default '0',
  cols numeric(4) NOT NULL default '0',
  rows numeric(4) NOT NULL default '0',
  sheet_id numeric(4) NOT NULL default '0',
  PRIMARY KEY  (id)
);

INSERT INTO label_forms (id, vendor, product, description, type, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (1,'Zweckform','4742 Inkjet+Laser, S+L Video TOP','VHS video cass. top label',1,3,8.13,4.66,7.87,4.66,2.5,0.87,2,6,1);
INSERT INTO label_forms (id, vendor, product, description, type, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (2,'Zweckform','4746 Inkjet+Laser, S+L,vid. SIDE','VHS cass. SIDE label',2,3,14.73,2,14.73,2,3.13,1.84,1,13,1);

#
# Table structure and data for 'label definition'
#

CREATE TABLE label_type (
  id serial,
  vendor char(16) NOT NULL default '',
  product char(32) NOT NULL default '',
  description char(48) default NULL,
  unit_id numeric(11) NOT NULL default '0',
  h_dist numeric NOT NULL default '0',
  v_dist numeric NOT NULL default '0',
  width numeric NOT NULL default '0',
  heigth numeric NOT NULL default '0',
  leftm numeric NOT NULL default '0',
  topm numeric NOT NULL default '0',
  cols numeric(4) NOT NULL default '0',
  rows numeric(4) NOT NULL default '0',
  sheet_id numeric(4) NOT NULL default '0',
  PRIMARY KEY  (id)
);

INSERT INTO label_type (id, vendor, product, description, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (1,'Zweckform','4742 Inkjet+Laser, S+L Video TOP','VHS video cass. top label',3,8.13,4.66,7.87,4.66,2.5,0.87,2,6,1);
INSERT INTO label_type (id, vendor, product, description, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (2,'Zweckform','4746 Inkjet+Laser, S+L,vid. SIDE','VHS cass. SIDE label',3,14.73,2,14.73,2,3.13,1.84,1,13,1);

#
# Table structure and data for 'label types'
#

CREATE TABLE label_types (
  id numeric(6) NOT NULL default '0' UNIQUE,
  description varchar(64) NOT NULL default '',
  PRIMARY KEY  (id)
);

INSERT INTO label_types (id, description) VALUES (1,'VHS top label');
INSERT INTO label_types (id, description) VALUES (2,'VHS side label');

#
# Table structure and data for 'printer offset definition'
#

CREATE TABLE printers (
  id numeric(4) NOT NULL default '0' UNIQUE,
  name varchar(32) NOT NULL default '',
  unit_id numeric(4) NOT NULL default '0',
  top_offset numeric NOT NULL default '0',
  left_offset numeric NOT NULL default '0',
  PRIMARY KEY  (id)
);

INSERT INTO printers (id, name, unit_id, top_offset, left_offset) VALUES (1,'OKI 610ex',4,5.5,4.5);
INSERT INTO printers (id, name, unit_id, top_offset, left_offset) VALUES (2,'EPSON Stylus Photo 890',0,0,0);

#
# Table structure and data for 'label print sheet description'
#

CREATE TABLE sheets (
  id serial,
  name char(16) NOT NULL default '',
  unit_id numeric(11) NOT NULL default '0',
  width numeric NOT NULL default '0',
  length numeric NOT NULL default '0',
  PRIMARY KEY  (id)
);

INSERT INTO sheets (id, name, unit_id, width, length) VALUES (1,'a4',3,21,29.7);

#
# Table structure and data for 'unit conversion'
#

CREATE TABLE units (
  id serial,
  unit char(8) NOT NULL default '',
  size numeric NOT NULL default '0',
  PRIMARY KEY  (id)
);

INSERT INTO units (id, unit, size) VALUES (1,'pt',1);
INSERT INTO units (id, unit, size) VALUES (2,'inch',72);
INSERT INTO units (id, unit, size) VALUES (3,'cm',28.3465);
INSERT INTO units (id, unit, size) VALUES (4,'mm',2.8346);
