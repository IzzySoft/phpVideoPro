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
INSERT INTO lang VALUES('edit_entry','en','Edit entry %1');
INSERT INTO lang VALUES('view_entry','en','View entry %1');
INSERT INTO lang VALUES('add_entry','en','Add entry');
INSERT INTO lang VALUES('unknown','en','unknown');
INSERT INTO lang VALUES('country','en','Country');
INSERT INTO lang VALUES('medianr','en','MediaNr');
INSERT INTO lang VALUES('highest_db_entries','en','highest entries in db');
INSERT INTO lang VALUES('no','en','No');
INSERT INTO lang VALUES('yes','en','Yes');
INSERT INTO lang VALUES('medialength','en','MediaLength');
INSERT INTO lang VALUES('minute_abbrev','en','min');
INSERT INTO lang VALUES('source','en','Source');
INSERT INTO lang VALUES('staff','en','Staff');
INSERT INTO lang VALUES('name','en','Name');
INSERT INTO lang VALUES('first_name','en','First Name');
INSERT INTO lang VALUES('in_list','en','in List');
INSERT INTO lang VALUES('comments','en','Comments');
INSERT INTO lang VALUES('cancel','en','Cancel');
INSERT INTO lang VALUES('create','en','Create');
INSERT INTO lang VALUES('update','en','Update');
INSERT INTO lang VALUES('edit','en','Edit');
INSERT INTO lang VALUES('delete','en','Delete');


# when finished, activate language
UPDATE languages SET available='Yes' WHERE lang_id='en';
