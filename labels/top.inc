<?
$width     = 80;      # width in mm
$height    = 47;      # heigth in mm
$textcolor = "black";

$maxlines  = 12;        # how many lines fit on the label

# coordinates: "x1,y1,x2,y2". Startpoint (0,0) is upper left corner
$nr_coord   = "0,0,10,15";   # coordinates of the number field
$main_coord = "0,15,80,47";  # main field contains title & time
$symb_coord = "64,0,80,15";  # symbol field for genre symbol

# what information should be displayed on the label (per movie)
# we want multiple lines, so we use an array:
$entry[] = "{title}";
$entry[] = "{country} {year}";
$entry[] = "Regie: {director}";
$entry[] = "Darsteller: {actors12}";
$entry[] = "{actor35}";
$entry[] = "";
