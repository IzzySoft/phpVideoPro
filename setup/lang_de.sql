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
INSERT INTO lang VALUES('enter_min_free','de','Mindestgröße des freien Platzes in Minuten:');
INSERT INTO lang VALUES('display','de','Anzeigen');
INSERT INTO lang VALUES('free_space_on_media','de','Auf folgenden Medien sind noch mindestens %1 Minuten frei:');
INSERT INTO lang VALUES('free','de','Frei');
INSERT INTO lang VALUES('content','de','Inhalt');
INSERT INTO lang VALUES('filter_setup','de','Filter Setup');
INSERT INTO lang VALUES('mediatype','de','MedienTyp');
INSERT INTO lang VALUES('screen','de','Bildformat');
INSERT INTO lang VALUES('picture','de','Farbformat');
INSERT INTO lang VALUES('tone','de','Tonformat');
INSERT INTO lang VALUES('longplay','de','LongPlay');
INSERT INTO lang VALUES('fsk','de','FSK');
INSERT INTO lang VALUES('actor','de','Schauspieler');
INSERT INTO lang VALUES('director','de','Regie');
INSERT INTO lang VALUES('composer','de','Musik');
INSERT INTO lang VALUES('min','de','min');
INSERT INTO lang VALUES('max','de','max');
INSERT INTO lang VALUES('s/w','de','s/w');
INSERT INTO lang VALUES('farbe','de','Farbe');
INSERT INTO lang VALUES('3d','de','3D');

# when finished, activate language
UPDATE languages SET available='Yes' WHERE lang_id='de';
