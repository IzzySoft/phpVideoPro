<?
$width     = 150;      # width in mm
$height    =  20;      # heigth in mm
$textcolor = "black";

$maxlines  = 4;        # how many lines fit on the label

# coordinates: "x1,y1,x2,y2". Startpoint (0,0) is upper left corner
$nr_coord   = "0,0,10,20";    # coordinates of the number field
$main_coord = "10,0,130,20";  # main field contains title & time
$symb_coord = "130,0,150,20"; # symbol field for genre symbol

# what information should be displayed on the label (per movie)
# we want one line only, so we use a scalar variable:
$entry = "*{title}   {length}";