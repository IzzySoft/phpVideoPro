# MySQL table created by DBV

# delete table if already exists
DROP TABLE IF EXISTS gloescht;

# create a new table
CREATE table gloescht (
       FILMNR Char(7),
       TITEL Char(60),
       LAENGE Int(3)
);

INSERT into gloescht Values ('0077-01','Die Bibel: Moses I',80);
INSERT into gloescht Values ('0081-01','',0);
INSERT into gloescht Values ('0037-02','Planet der Affen',105);
INSERT into gloescht Values ('0086-01','',0);
