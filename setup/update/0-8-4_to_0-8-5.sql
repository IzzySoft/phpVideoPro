# ========================================================
# Updating Database for phpVideoPro from v0.8.4 to v0.8.5
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.8.5' WHERE name='version';

# New CD/DVD labels
INSERT INTO label_forms VALUES
  (3,'Memorex','CD/DVD Label','CD/DVD Label',3,3,11.9,11.9,11.9,11.9,1.1,
   2.4,1,1,1);
INSERT INTO eps_templates VALUES
  (27,3,'Action','action_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (28,3,'Comedy','comedy_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (29,3,'Doku','docu_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (30,3,'SciFi','sf_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (31,3,'Simple','simple_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (32,3,'Marmor','marmor_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (33,3,'Sky','sky_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (34,3,'Water','water_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (35,3,'Pool','pool_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (36,3,'Electronic','electronic_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (37,3,'Citrus','citrus_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (38,3,'World','world_cddvd.eps','common_cddvd.ps',0,0,468,474);
INSERT INTO eps_templates VALUES
  (39,3,'Clouds','clouds_cddvd.eps','common_cddvd.ps',0,0,468,474);
