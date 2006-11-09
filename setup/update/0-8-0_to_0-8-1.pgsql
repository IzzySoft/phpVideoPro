# ========================================================
# Updating Database for phpVideoPro from v0.8.0 to v0.8.1
# ========================================================

# prepare default lang update
DELETE FROM lang WHERE lang='en';

# version update
UPDATE pvp_config SET value='0.8.1' WHERE name='version';

CREATE TABLE pvp_media (
   id INT,
   mtype_id INT DEFAULT 1,
   disks_id INT,
   size INT,
   free INT,
   rc VARCHAR,
   owner INT DEFAULT 0,
   storeplace VARCHAR,
   lentto VARCHAR
);
COMMENT ON TABLE pvp_media IS 'Media info (DVDs, tapes, etc)';
COMMENT ON COLUMN pvp_media.id IS 'The media number';
COMMENT ON COLUMN pvp_media.mtype_id IS 'The media type (e.g. DVD) ID';
COMMENT ON COLUMN pvp_media.disks_id IS 'Media subtype (e.g. DVD-5) ID';
COMMENT ON COLUMN pvp_media.size IS 'Media size in minutes (e.g. 240 for 240min tapes)';
COMMENT ON COLUMN pvp_media.free IS 'Free time/space on the medium';
COMMENT ON COLUMN pvp_media.rc IS 'To which regions the medium is restricted';
COMMENT ON COLUMN pvp_media.owner IS 'user_id to whom belongs this medium';
COMMENT ON COLUMN pvp_media.storeplace IS 'Where this medium is physically stored';
COMMENT ON COLUMN pvp_media.lentto IS 'To whom this medium is (temporarily) lent';
ALTER TABLE pvp_media ADD CONSTRAINT pk_media PRIMARY KEY (id,mtype_id);
ALTER TABLE pvp_media ADD CONSTRAINT notnullcheck_media_id CHECK (id IS NOT NULL);
ALTER TABLE pvp_media ADD CONSTRAINT notnullcheck_media_owner CHECK (owner IS NOT NULL);

CREATE INDEX media_free_idx ON pvp_media(free,id);
COMMENT ON INDEX media_free_idx IS 'For faster access to available free space';

INSERT INTO pvp_media (id,mtype_id,disks_id,size,free,rc)
  SELECT id,mtype_id,disks_id,type,free,rc FROM cass;
DROP INDEX cass_free_idx;
DROP TABLE cass;

