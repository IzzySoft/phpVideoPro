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
INSERT INTO lang VALUES('edit_entry','de','Bearbeite Datensatz %1');
INSERT INTO lang VALUES('view_entry','de','Anzeige des Datensatzes %1');
INSERT INTO lang VALUES('add_entry','de','Neuer Datensatz');
INSERT INTO lang VALUES('unknown','de','unbekannt');
INSERT INTO lang VALUES('country','de','Land');
INSERT INTO lang VALUES('medianr','de','MediaNr');
INSERT INTO lang VALUES('highest_db_entries','de','letzte DB-Einträge');
INSERT INTO lang VALUES('no','de','Nein');
INSERT INTO lang VALUES('yes','de','Ja');
INSERT INTO lang VALUES('medialength','de','Bandlänge');
INSERT INTO lang VALUES('minute_abbrev','de','min');
INSERT INTO lang VALUES('source','de','Quelle');
INSERT INTO lang VALUES('name','de','Name');
INSERT INTO lang VALUES('first_name','de','Vorname');
INSERT INTO lang VALUES('in_list','de','in Liste');
INSERT INTO lang VALUES('comments','de','Anmerkungen');
INSERT INTO lang VALUES('cancel','de','Abbrechen');
INSERT INTO lang VALUES('create','de','Erstellen');
INSERT INTO lang VALUES('update','de','Aktualisieren');
INSERT INTO lang VALUES('edit','de','Bearbeiten');
INSERT INTO lang VALUES('delete','de','Löschen');

# when finished, activate language
UPDATE languages SET available='Yes' WHERE lang_id='de';
