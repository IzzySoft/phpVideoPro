# =======================================================
# Updating Database for phpVideoPro from v0.6.1 to v0.6.2
# =======================================================

# add column to cat table to mark a category als enabled/disabled
ALTER TABLE cat ADD enabled INT;
ALTER TABLE cat ALTER enabled SET DEFAULT 1;
ALTER TABLE cat ADD CONSTRAINT cat_enabled_notnullcheck CHECK (enabled IS NOT NULL);

# add a table to keep the user preferences when cookies are disabled
CREATE TABLE pvp_userprefs (
   id serial,
   user_id int NOT NULL,
   name varchar(30),
   value text,
   PRIMARY KEY (id)
);

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.6.2' WHERE name='version';
