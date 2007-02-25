BEGIN

#
# Table structure and data for 'PS Label Pack Info'
#
CREATE TABLE pvp_pspacks (
  id    SERIAL,
  rev   INT DEFAULT 1,
  sname VARCHAR(20) UNIQUE,
  name  VARCHAR(50),
  descript      VARCHAR(200),
  creator       VARCHAR(200)
);
COMMENT ON TABLE pvp_pspacks IS 'PS Label Pack Info';
COMMENT ON COLUMN pvp_pspacks.rev IS 'Revision number of the installed pack';
COMMENT ON COLUMN pvp_pspacks.sname IS 'Unique identifier e.g. for downloading updates';
COMMENT ON COLUMN pvp_pspacks.name IS 'Name of the pack';
COMMENT ON COLUMN pvp_pspacks.descript IS 'Description of the pack';
COMMENT ON COLUMN pvp_pspacks.creator IS 'Who made/maintains the pack';
ALTER TABLE pvp_pspacks ADD CONSTRAINT pk_pspacks PRIMARY KEY (id);
ALTER TABLE pvp_pspacks ADD CONSTRAINT notnullcheck_pspacks_rev CHECK(rev IS NOT NULL);
ALTER TABLE pvp_pspacks ADD CONSTRAINT notnullcheck_pspacks_sname CHECK(sname IS NOT NULL);
INSERT INTO pvp_pspacks (id,rev,sname,name,descript,creator) VALUES (1,1,'pvplvd','Default VHS Labels','Top and Side labels for VHS tapes originally came along with the application','Izzy ([url]http://www.qumran.org/homes/izzy/software/pvp/[/url])');
INSERT INTO pvp_pspacks (id,rev,sname,name,descript,creator) VALUES (2,1,'pvplcs','Simple Color CD/DVD Labels','CD/DVD labels just using simple  colored background (originally shipped with phpVideoPro v0.8.5)','Izzy ([url]http://www.qumran.org/homes/izzy/software/pvp/[/url])')
INSERT INTO pvp_pspacks (id,rev,sname,name,descript,creator) VALUES (3,1,'pvplcp','Simple Pix CD/DVD Labels','CD/DVD labels using simple picture background (originally shipped with phpVideoPro v0.8.5)','Izzy ([url]http://www.qumran.org/homes/izzy/software/pvp/[/url])')
SELECT setval('pvp_pspacks_id_seq', 3);

#
# Table structure and data for 'eps templates bounding box definition'
#
CREATE TABLE pvp_epstemplates ( 
	id            SERIAL, 
	type          INT default '0', 
	pack_id       INT, 
	description   VARCHAR(64), 
	eps_filename  VARCHAR(255), 
	ps_filename   VARCHAR(255), 
	llx           SMALLINT default 0, 
	lly           SMALLINT default 0, 
	urx           SMALLINT default 0, 
	ury           SMALLINT default 0
);
COMMENT ON TABLE pvp_epstemplates IS 'Bounding box of EPS template';
COMMENT ON COLUMN pvp_epstemplates.type IS 'Type of the template (CD/VHS/..) like in pvp_pslabelforms';
COMMENT ON COLUMN pvp_epstemplates.pack_id IS 'ID of PSPack this label belongs to';
COMMENT ON COLUMN pvp_epstemplates.description IS 'Short description/Name of this label';
COMMENT ON COLUMN pvp_epstemplates.eps_filename IS 'EPS (Image) file used';
COMMENT ON COLUMN pvp_epstemplates.ps_filename IS 'PS (control) file used';
COMMENT ON COLUMN pvp_epstemplates.llx IS 'Coordinate for LowerLeft x';
COMMENT ON COLUMN pvp_epstemplates.lly IS 'Coordinate for LowerLeft y';
COMMENT ON COLUMN pvp_epstemplates.urx IS 'Coordinate for UpperRight x';
COMMENT ON COLUMN pvp_epstemplates.ury IS 'Coordinate for UpperRight y';
ALTER TABLE pvp_epstemplates ADD CONSTRAINT pk_epstemplates PRIMARY KEY (id);
ALTER TABLE pvp_epstemplates ADD CONSTRAINT notnullcheck_epstemplates_type CHECK (type IS NOT NULL);
ALTER TABLE pvp_epstemplates ADD CONSTRAINT notnullcheck_epstemplates_packid CHECK (pack_id IS NOT NULL);
ALTER TABLE pvp_epstemplates ADD CONSTRAINT notnullcheck_epstemplates_desc CHECK (description IS NOT NULL);
ALTER TABLE pvp_epstemplates ADD CONSTRAINT notnullcheck_epstemplates_epsfile CHECK (eps_filename IS NOT NULL);
ALTER TABLE pvp_epstemplates ADD CONSTRAINT notnullcheck_epstemplates_psfile CHECK (ps_filename IS NOT NULL);
ALTER TABLE pvp_epstemplates ADD CONSTRAINT notnullcheck_epstemplates_llx CHECK (llx IS NOT NULL);
ALTER TABLE pvp_epstemplates ADD CONSTRAINT notnullcheck_epstemplates_lly CHECK (lly IS NOT NULL);
ALTER TABLE pvp_epstemplates ADD CONSTRAINT notnullcheck_epstemplates_urx CHECK (urx IS NOT NULL);
ALTER TABLE pvp_epstemplates ADD CONSTRAINT notnullcheck_epstemplates_ury CHECK (ury IS NOT NULL);

CREATE INDEX pvp_epstemplates_desc ON pvp_epstemplates (description);

# Pack 1
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (1,2,1,'adventure_side','adventure_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (2,1,1,'adventure_top','adventure_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (3,2,1,'action_side','action_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (4,1,1,'action_top','action_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (5,2,1,'b5_side','b5_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (6,1,1,'b5_top','b5_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (7,2,1,'bible_side','bibelfilm_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (8,1,1,'bible_top','bibelfilm_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (9,2,1,'comedy_side','comedy_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (10,1,1,'comedy_top','comedy_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (11,2,1,'default_side','simple_side.eps','simple_side.ps',0,0,414,54);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (12,1,1,'default_top','simple_top.eps','simple_top.ps',0,0,223,126);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (13,2,1,'docu_side','docu_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (14,1,1,'docu_top','docu_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (15,2,1,'drama_side','drama_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (16,1,1,'drama_top','drama_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (17,2,1,'fantasy_side','fantasy_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (18,1,1,'fantasy_top','fantasy_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (19,2,1,'history_side','history_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (20,1,1,'history_top','history_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (21,2,1,'music_side','music_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (22,1,1,'music_top','music_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (23,2,1,'sf_side','sf_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (24,1,1,'sf_top','sf_top.eps','common_top.ps',0,0,273,160);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (25,2,1,'trick_side','trick_side.eps','common_side.ps',0,0,513,68);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (26,1,1,'trick_top','trick_top.eps','common_top.ps',0,0,273,160);

# Pack 2
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (27,3,2,'Action','action_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (28,3,2,'Comedy','comedy_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (29,3,2,'Doku','docu_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (30,3,2,'SciFi','sf_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (31,3,2,'Simple','simple_cddvd.eps','common_cddvd.ps',0,0,468,474);

# Pack 3
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (32,3,3,'Marmor','marmor_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (33,3,3,'Sky','sky_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (34,3,3,'Water','water_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (35,3,3,'Pool','pool_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (36,3,3,'Electronic','electronic_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (37,3,3,'Citrus','citrus_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (38,3,3,'World','world_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (39,3,3,'Clouds','clouds_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO pvp_epstemplates (id, type, pack_id, description, eps_filename, ps_filename, llx, lly, urx, ury) VALUES (40,3,3,'Celtic','celtic_cddvd.eps','common_cddvd.ps',0,0,470,468);

SELECT setval('pvp_epstemplates_id_seq', 40);

#
# Table structure and data for 'label form definition'
#
CREATE TABLE pvp_pslabelforms (
  id            SERIAL,
  vendor        VARCHAR(16),
  product       VARCHAR(32),
  description   VARCHAR(48) DEFAULT NULL,
  type          INT DEFAULT 0,
  unit_id       INT DEFAULT 0,
  h_dist        FLOAT DEFAULT 0,
  v_dist        FLOAT DEFAULT 0,
  width         FLOAT DEFAULT 0,
  heigth        FLOAT DEFAULT 0,
  leftm         FLOAT DEFAULT 0,
  topm          FLOAT DEFAULT 0,
  cols          INT DEFAULT 0,
  rows          INT DEFAULT 0,
  sheet_id      INT DEFAULT 0
);
COMMENT ON TABLE pvp_pslabelforms IS 'PS label formsheet definition table';
COMMENT ON COLUMN pvp_pslabelforms.vendor IS 'Vendor/Brand name';
COMMENT ON COLUMN pvp_pslabelforms.product IS 'Product name/details';
COMMENT ON COLUMN pvp_pslabelforms.description IS 'Detailed description of the sheet';
COMMENT ON COLUMN pvp_pslabelforms.type IS 'Target (CD/DVDLabel, VHS,...) ID';
COMMENT ON COLUMN pvp_pslabelforms.unit_id IS 'Unit used for measures in the following fields';
COMMENT ON COLUMN pvp_pslabelforms.cols IS 'Number of label columns on this sheet';
COMMENT ON COLUMN pvp_pslabelforms.rows IS 'Number of label rows on this sheet';
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT pk_pslabelforms PRIMARY KEY (id);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_vendor CHECK (vendor IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_product CHECK (product IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_type CHECK (type IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_unitid CHECK (unit_id IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_hdist CHECK (h_dist IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_vdist CHECK (v_dist IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_width CHECK (width IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_heigth CHECK (heigth IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_leftm CHECK (leftm IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_topm CHECK (topm IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_cols CHECK (cols IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_rows CHECK (rows IS NOT NULL);
ALTER TABLE pvp_pslabelforms ADD CONSTRAINT nutnullcheck_pslabelforms_sheetid CHECK (sheet_id IS NOT NULL);
INSERT INTO pvp_pslabelforms SELECT * FROM label_forms;

INSERT INTO pvp_pslabelforms (id, vendor, product, description, type, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (1,'Zweckform','4742 Inkjet+Laser, S+L Video TOP','VHS video cass. top label',1,3,8.13,4.66,7.87,4.66,2.5,0.87,2,6,1);
INSERT INTO pvp_pslabelforms (id, vendor, product, description, type, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (2,'Zweckform','4746 Inkjet+Laser, S+L,vid. SIDE','VHS cass. SIDE label',2,3,14.73,2,14.73,2,3.13,1.84,1,13,1);
INSERT INTO pvp_pslabelforms (id, vendor, product, description, type, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (3,3,'Memorex','CD/DVD Label','CD/DVD Label',3,3,11.9,11.9,11.9,11.9,1.1,2.4,1,1,1);

SELECT setval('pvp_pslabelforms_id_seq', 3);

#
# Table structure and data for 'printer offset definition'
#

CREATE TABLE pvp_psprinters (
  id numeric(4) NOT NULL default '0' UNIQUE,
  name varchar(32) NOT NULL default '',
  unit_id numeric(4) NOT NULL default '0',
  top_offset numeric NOT NULL default '0',
  left_offset numeric NOT NULL default '0',
  PRIMARY KEY  (id)
);

INSERT INTO pvp_psprinters (id, name, unit_id, top_offset, left_offset) VALUES (1,'OKI 610ex',4,5.5,4.5);
INSERT INTO pvp_psprinters (id, name, unit_id, top_offset, left_offset) VALUES (2,'EPSON Stylus Photo 890',4,0,0);
INSERT INTO pvp_psprinters (id, name, unit_id, top_offset, left_offset) VALUES (3,'Canon S520',4,0,0);

#
# Table structure and data for 'label print sheet description'
#

CREATE TABLE pvp_pssheets (
  id serial,
  name char(16) NOT NULL default '',
  unit_id numeric(11) NOT NULL default '0',
  width numeric NOT NULL default '0',
  length numeric NOT NULL default '0',
  PRIMARY KEY  (id)
);

INSERT INTO pvp_pssheets (id, name, unit_id, width, length) VALUES (1,'a4',3,21,29.7);

#
# Table structure and data for 'unit conversion'
#

CREATE TABLE pvp_psunits (
  id    SERIAL,
  unit  VARCHAR(8),
  size  FLOAT DEFAULT 0
);
COMMENT ON TABLE pvp_psunits IS 'unit conversion table';
COMMENT ON COLUMN pvp_psunits.unit IS 'Name/Reference of the unit';
COMMENT ON COLUMN pvp_psunits.size IS 'Size in points';
ALTER TABLE pvp_psunits ADD CONSTRAINT pk_psunits PRIMARY KEY (id);
ALTER TABLE pvp_psunits ADD CONSTRAINT notnullcheck_psunits_unit CHECK (unit IS NOT NULL);
ALTER TABLE pvp_psunits ADD CONSTRAINT notnullcheck_psunits_size CHECK (size IS NOT NULL);

INSERT INTO pvp_psunits (id, unit, size) VALUES (1,'pt',1);
INSERT INTO pvp_psunits (id, unit, size) VALUES (2,'inch',72);
INSERT INTO pvp_psunits (id, unit, size) VALUES (3,'cm',28.3465);
INSERT INTO pvp_psunits (id, unit, size) VALUES (4,'mm',2.8346);

SELECT setval('pvp_psunits_id_seq', 4);

COMMIT;
