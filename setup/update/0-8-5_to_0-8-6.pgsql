# ========================================================
# Updating Database for phpVideoPro from v0.8.5 to v0.8.6
# ========================================================

BEGIN;

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.8.6' WHERE name='version';

# PS Label Packs
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
INSERT INTO pvp_pspacks (rev,sname,name,descript,creator) VALUES
  (1,'pvplvd','Default VHS Labels','Top and Side labels for VHS tapes originally came along with the application','Izzy ([url]http://www.qumran.org/homes/izzy/software/pvp/[/url])');

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
# VHS:
INSERT INTO pvp_epstemplates (type,pack_id,description,eps_filename,ps_filename,
 llx,lly,urx,ury) SELECT type,1,description,eps_filename,ps_filename,llx,lly,
 urx,ury FROM eps_templates WHERE type=1 OR type=2;

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
DROP TABLE label_forms;

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
INSERT INTO pvp_psunits SELECT * FROM units;
DROP TABLE units;

ALTER TABLE sheets RENAME TO pvp_pssheets;
ALTER TABLE printers RENAME TO pvp_psprinters;

COMMIT;
