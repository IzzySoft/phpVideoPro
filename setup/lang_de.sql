# ========================================================
# English Translation phrases for phpVideoPro
# ========================================================

INSERT INTO lang (message_id,lang,content) VALUES ('not_yet_implemented','de','Sorry - leider noch nicht verfügbar.');
INSERT INTO lang VALUES('medium','de','Medium');
INSERT INTO lang VALUES('nr','de','Nr');
INSERT INTO lang VALUES('title','de','Titel');
INSERT INTO lang VALUES('length','de','Länge');
INSERT INTO lang VALUES('year','de','Jahr');
INSERT INTO lang VALUES('date_rec','de','Aufnahmedatum');
INSERT INTO lang VALUES('category','de','Kategorie');
INSERT INTO lang VALUES('medialist','de','Medienliste');


# when finished, activate language
UPDATE languages SET available='Yes' WHERE lang_id='de';
