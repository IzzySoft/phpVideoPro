# ========================================================
# Updating Database for phpVideoPro from v0.2.0 to v0.2.1
# ========================================================

ALTER TABLE video ADD counter1 VARCHAR(10);
ALTER TABLE video ADD counter2 VARCHAR(10);
ALTER TABLE video ADD commercials_id int;
CREATE TABLE commercials (
   id int NOT NULL,
   name varchar(30),
   PRIMARY KEY (id)
);
INSERT INTO commercials VALUES (0,'unknown');
INSERT INTO commercials VALUES (1,'yes');
INSERT INTO commercials VALUES (2,'no');
INSERT INTO commercials VALUES (3,'cut_off');
# version update
UPDATE pvp_config SET value='0.2.1' WHERE name='version';
