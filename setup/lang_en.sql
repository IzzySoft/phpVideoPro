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



# when finished, activate language
UPDATE languages SET available='Yes' WHERE lang_id='en';
