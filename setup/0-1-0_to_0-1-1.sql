# ========================================================
# Updating Database for phpVideoPro from v0.1.0 to v0.1.1
# ========================================================

# --------------------------------------------------------
#
# Table structure for table 'preferences'
#

CREATE TABLE preferences (
   id int(5) NOT NULL auto_increment,
   name varchar(30),
   value text,
   PRIMARY KEY (id)
);
