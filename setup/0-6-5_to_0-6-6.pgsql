# =======================================================
# Updating Database for phpVideoPro from v0.6.4 to v0.6.5
# =======================================================

# adding audio + subtitle facility
ALTER TABLE languages ADD audio INT;
ALTER TABLE languages ALTER audio SET DEFAULT 0;
UPDATE languages SET audio=0;
UPDATE languages SET audio=1 WHERE lang_id IN ("de","en","es","fr","it","ru");
ALTER TABLE languages ADD CONSTRAINT audio_notnullcheck CHECK (audio IS NOT NULL);
ALTER TABLE languages ADD subtitle INT;
ALTER TABLE languages ALTER subtitle SET DEFAULT 0;
UPDATE languages SET subtitle=0;
UPDATE languages SET subtitle=1 WHERE lang_id IN ("da","de","en","es","fi","fr","hr","hu","it","iw","nl","no","pl","ru","sk","sr","sv","tr");
ALTER TABLE languages ADD CONSTRAINT subtitle_notnullcheck CHECK (subtitle IS NOT NULL);

ALTER TABLE video ADD audio VARCHAR(50);
ALTER TABLE video ADD subtitle VARCHAR(100);

# extending the source field
-- unfortunately dows not work with PG - no way!
-- ALTER TABLE video ALTER source VARCHAR(25);

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.6.6' WHERE name='version';
