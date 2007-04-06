# ========================================================
# Updating Database for phpVideoPro from v0.8.6 to v0.8.8
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# additional PSLabel Forms
INSERT INTO pvp_pslabelforms (id, vendor, product, description, type, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (4,'Zweckform','No. 6043 CD-Etiketten','CD/DVD Label',3,3,11.9,12.9,11.9,11.9,4.65,2.143,1,2,1);
INSERT INTO pvp_pslabelforms (id, vendor, product, description, type, unit_id, h_dist, v_dist, width, heigth, leftm, topm, cols, rows, sheet_id) VALUES (5,'Data Becker','No. 6815 +XL- Label CD-Etiketten','CD/DVD Label',3,3,11.9,14.8,11.9,11.9,4.7,1.65,1,2,1);

# AutoLogin
INSERT INTO pvp_config (name,value) VALUES ('use_http_auth','0');

# Preferences
INSERT INTO preferences (name,value) VALUES ('default_pstemplate_id','1');

# version update
UPDATE pvp_config SET value='0.8.7' WHERE name='version';
