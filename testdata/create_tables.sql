
# tapes
CREATE table cass (
       CASSNR Int(4),
       TYP Int(3),
       FREI Int(3)
);

# deleted tapes
CREATE table gloescht (
       FILMNR Char(7),
       TITEL Char(60),
       LAENGE Int(3)
);

# categories
CREATE table kat (
       KATE Char(15)
);

# countries
CREATE table land (
       LAND Char(30)
);

# actors
CREATE table sp (
       SSP Char(30),
       STITEL Char(60),
       SFILMNR Char(7),
       SLAENGE Int(3),
       SSTEREO Char(2),
       SHIFI Char(1),
       SKAT Char(15),
       SFARBE Char(4),
       BES ENum('T','F'),
       DRUCK ENum('T','F'),
       SBANDZ Char(4),
       SLP Char(2)
);

# movies
CREATE table video (
       BEL ENum('T','F'),
       CNR Int(4),
       FC Int(2),
       FILMNR Char(7),
       TITEL Char(60),
       LAENGE Int(3),
       DATUM Date,
       QUELLE Char(15),
       REGISSEUR Char(30),
       MUSIK Char(30),
       LAND Char(30),
       JAHR Char(4),
       KAT Char(15),
       KAT1 Char(15),
       KAT2 Char(15),
       KAT3 Char(15),
       SP1 Char(30),
       SP2 Char(30),
       SP3 Char(30),
       SP4 Char(30),
       SP5 Char(30),
       SPL1 ENum('T','F'),
       SPL2 ENum('T','F'),
       SPL3 ENum('T','F'),
       SPL4 ENum('T','F'),
       SPL5 ENum('T','F'),
       HIFI Char(1),
       STEREO Char(2),
       FARBE Char(4),
       BANDZ Char(4),
       BANDE Char(4),
       LP Char(2),
       FSK Char(2),
       BEMERK01 Char(70),
       BEMERK02 Char(70),
       BEMERK03 Char(70)
);

