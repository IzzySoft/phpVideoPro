# ========================================================
# Updating Database for phpVideoPro from v0.4.0 to v0.4.1
# ========================================================

# adding table for user management and authorization
CREATE TABLE pvp_users (
  id SERIAL,
  login VARCHAR(20) UNIQUE,
  pwd VARCHAR(32),
  admin INT NOT NULL,
  browse INT NOT NULL,
  ins INT NOT NULL,
  upd INT NOT NULL,
  del INT NOT NULL,
  comment VARCHAR(255),
  PRIMARY KEY (id)
);
INSERT INTO pvp_users (login,pwd,admin,browse,ins,upd,del,comment) VALUES ('admin','421b47ffd946ca083b65cd668c6b17e6',1,1,1,1,1,'Administrator');
INSERT INTO pvp_users (login,admin,browse,ins,upd,del,comment) VALUES ('guest',0,1,0,0,0,'Alien Visitor');

# adding table for session management
CREATE TABLE pvp_sessions (
  id VARCHAR(255) NOT NULL,
  ip VARCHAR(255) NOT NULL,
  user_id INT,
  started VARCHAR(50),
  dla VARCHAR(50),
  ended VARCHAR(50),
  PRIMARY KEY (id)
);

# update config for session management
INSERT INTO pvp_config (name,value) VALUES ('session_purgetime','7200');

# prepare for language update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.4.1' WHERE name='version';
