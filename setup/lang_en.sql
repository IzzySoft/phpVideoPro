# ========================================================
# English Translation phrases for phpVideoPro
# ========================================================

INSERT INTO lang (message_id,lang,content) VALUES ('not_yet_implemented','en','Sorry - not yet implemented.');
INSERT INTO lang VALUES('medium','en','Medium');
INSERT INTO lang VALUES('nr','en','Nr');
INSERT INTO lang VALUES('title','en','Title');
INSERT INTO lang VALUES('length','en','Length');
INSERT INTO lang VALUES('year','en','Year');
INSERT INTO lang VALUES('date_rec','en','Date Aquired');
INSERT INTO lang VALUES('category','en','Category');
INSERT INTO lang VALUES('medialist','en','Medialist');
INSERT INTO lang VALUES('enter_min_free','en','Enter minimum of free space on medium to display:');
INSERT INTO lang VALUES('display','en','Display');
INSERT INTO lang VALUES('free_space_on_media','en','Following media have at least %1 minutes of free space available:');
INSERT INTO lang VALUES('free','en','Free');
INSERT INTO lang VALUES('content','en','Content');
INSERT INTO lang VALUES('filter_setup','en','Filter Setup');
INSERT INTO lang VALUES('mediatype','en','MediaType');
INSERT INTO lang VALUES('screen','en','Screen Format');
INSERT INTO lang VALUES('picture','en','Color Format');
INSERT INTO lang VALUES('tone','en','Tone Format');
INSERT INTO lang VALUES('longplay','en','LongPlay');
INSERT INTO lang VALUES('fsk','en','PG');
INSERT INTO lang VALUES('actor','en','Actor');
INSERT INTO lang VALUES('director','en','Director');
INSERT INTO lang VALUES('composer','en','Composer');
INSERT INTO lang VALUES('min','en','min');
INSERT INTO lang VALUES('max','en','max');
INSERT INTO lang VALUES('s/w','en','b/w');
INSERT INTO lang VALUES('farbe','en','Color');
INSERT INTO lang VALUES('3d','en','3D');

# when finished, activate language
UPDATE languages SET available='Yes' WHERE lang_id='en';
