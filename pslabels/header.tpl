%! PS-Adobe-1.0
%%
%%
%% Reihenfolge:
%%	header
%%	{
%%	  {
%%	    image
%%	    image (EPS file)
%%	    text
%%	  } forall labels on page
%%	  finish
%%	} forall pages
%%
/bdef { bind readonly def } bind readonly def
/FG 0   def 		%% grey value für die Buchstaben
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%% ANFANG VARAIBLER TEIL %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% printer offsets
/printer_unit { {_pr_unit_size_} mul } bdef
/left_offset { {_pr_left_} printer_unit } bdef
/top_offset { {_pr_top_} printer_unit } bdef
%%
%% hier wird die Seite und das Etikett definiert
%% aus der Datenbank
%% Papersize
{_sheet_papersize_}	% a4
%% z.B. units ( /units {size mul } bind def )
/sheet_unit { {_sheet_unit_size_} mul } bdef
/label_unit { {_label_unit_size_} mul } bdef
/sheet_length { {_sheet_length_} sheet_unit } bdef
/sheet_width { {_sheet_width_} sheet_unit } bdef
/left_margin { {_left_margin_} label_unit } bdef
/top_margin { {_top_margein_} label_unit } bdef
/label_width { {_label_width_} label_unit } bdef
/label_height { {_label_height_} label_unit } bdef
/label_vdist { {_label_vdist_} label_unit } bdef
/label_hdist { {_label_hdist_} label_unit } bdef
/label_cols { {_label_cols_} } bdef
/label_rows { {_label_rows_} } bdef
%%
%% language adaptations for label text fields
/lang_director { ({_lang_director_}) } bdef
/lang_actor { ({_lang_actor_}) } bdef
/lang_composer { ({_lang_composer_}) } bdef
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%% ENDE VARAIBLER TEIL %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%

%% utility functions
%%
%% 
/verticalBar
%% procedure to draw a vertical bar at current point
%%
%% called as: length verticalBar --
{
gsave
  dup
  neg
  0 exch
  rmoveto
  2 mul
  0 exch
  rlineto
  stroke
grestore
} def

/horizontalBar
%% procedure to draw a horizontal bar at current point
%%
%% called as: length horizontalBar --
{
gsave
  dup
  neg
  0
  rmoveto
  2 mul
  0
  rlineto
  stroke
grestore
} def

/crossHairs
%% procedure to draw a crosshair at current point
%%
%% called as: length crossHairs --
{
/L exch def
gsave
  L verticalBar
  L horizontalBar
grestore
} def


% Function c-show (str => -)
% centers text only according to x axis.
/c-show { 
  dup stringwidth pop
  2 div neg 0 rmoveto
  show
} bind def

% Function l-show (str => -)
% prints texts so that it ends at currentpoint
/l-show {
  dup stringwidth pop neg 
  0 
  rmoveto show
} bind def

% center-fit show (str w => -)
% show centered, and scale currentfont so that the width is less than w
/cfshow {
  exch dup stringwidth pop
  % If the title is too big, try to make it smaller
  3 2 roll 2 copy
  gt
  { % if, i.e. too big
    exch div
    currentfont exch scalefont setfont
  } { % ifelse
    pop pop 
  }
  ifelse
  c-show			% center title
} bind def

% Return the y size of the current font
% - => fontsize
/currentfontsize {
  currentfont /FontMatrix get 3 get 1000 mul
} bind def

/reencode_font {
  findfont reencode 2 copy definefont pop def
} bind def

% reencode the font
% <encoding-vector> <fontdict> -> <newfontdict>
/reencode { %def
  dup length 5 add dict begin
    { %forall
      1 index /FID ne 
      { def }{ pop pop } ifelse
    } forall
    /Encoding exch def

    % Use the font's bounding box to determine the ascent, descent,
    % and overall height; don't forget that these values have to be
    % transformed using the font's matrix.
    % We use `load' because sometimes BBox is executable, sometimes not.
    % Since we need 4 numbers an not an array avoid BBox from being executed
    /FontBBox load aload pop
    FontMatrix transform /Ascent exch def pop
    FontMatrix transform /Descent exch def pop
    /FontHeight Ascent Descent sub def

    % Define these in case they're not in the FontInfo (also, here
    % they're easier to get to.
    /UnderlinePosition 1 def
    /UnderlineThickness 1 def
    
    % Get the underline position and thickness if they're defined.
    currentdict /FontInfo known {
      FontInfo
      
      dup /UnderlinePosition known {
	dup /UnderlinePosition get
	0 exch FontMatrix transform exch pop
	/UnderlinePosition exch def
      } if
      
      dup /UnderlineThickness known {
	/UnderlineThickness get
	0 exch FontMatrix transform exch pop
	/UnderlineThickness exch def
      } if
      
    } if
    currentdict 
  end 
} bind def

%% Concatenate two strings and return result
%% str1 str2 StrCat result
%%
/StrCat
{
  /Str2 exch def
  /Str1 exch def
  Str1 length Str2 length add string /Str3 exch def
  Str3 0 Str1 putinterval
  Str3 Str1 length Str2 putinterval
  Str3
} def


%% A Simple Line Breaking Algorithm
%%
/wordbreak ( )  def	% constant used for word breaks (ASCII space)
/BreakIntoLines
 { /proc exch def 
   /linewidth exch def 
   /textstring exch def
   /breakwidth wordbreak stringwidth pop def 
   /curwidth 0 def   
   /lastwordbreak 0 def   
   /startchar 0 def   
   /restoftext textstring def   
   { restoftext wordbreak search 
    {/nextword exch def pop 
     /restoftext exch def 
     /wordwidth nextword stringwidth pop def 
     curwidth wordwidth add linewidth gt 
      { textstring startchar 
         lastwordbreak startchar sub 
         getinterval proc 
        /startchar lastwordbreak def 
        /curwidth wordwidth breakwidth add def } 
      { /curwidth curwidth wordwidth add 
         breakwidth add def 
      } ifelse 
     /lastwordbreak lastwordbreak 
       nextword length add 1 add def 
     } 
     { pop exit } 
     ifelse 
  } loop 
  /lastchar textstring length def 
  textstring startchar lastchar startchar sub 
   getinterval proc 
  } def

%%%%%% example program 
%%
%%/Times-Roman findfont 16 scalefont setfont 
%%/yline 650 def   
%%(Now we have the opportunity to put some arbitrary\
%%long text in here which will be split into lines)
%%100 	%% Use a line width of 100 points. 
%%{ 72 yline moveto show 
%%/yline yline 18 sub def}
%%BreakIntoLines 
%%showpage
%%%%

%% A Simple Line Truncating Algorithm
%%
/wordbreak ( )  def	% constant used for word breaks (ASCII space)
/TruncateLine
 { /proc exch def 
   /linewidth exch def 
   /textstring exch def
   /breakwidth wordbreak stringwidth pop def 
   /curwidth 0 def   
   /lastwordbreak 0 def   
   /startchar 0 def   
   /restoftext textstring def   
   { restoftext wordbreak search 
    {/nextword exch def pop 
     /restoftext exch def 
     /wordwidth nextword stringwidth pop def 
     curwidth wordwidth add linewidth gt 
      { textstring startchar 
         lastwordbreak startchar sub 
         getinterval true proc exit	% return truncated string
      } 
      { 
         /curwidth curwidth wordwidth add 
         breakwidth add def 
      } ifelse 
     /lastwordbreak lastwordbreak 
       nextword length add 1 add def 
     } 
     { pop textstring false proc exit } % return unchanged string
     ifelse 
   } loop
  } def

%%%%%% example program 
%%
%%/Times-Roman findfont 16 scalefont setfont 
%%/yline 650 def   
%%(Now we have the opportunity to put some arbitrary\
%%long text in here which will be split into lines)
%%%(Short)
%%250 (...) stringwidth pop sub	%% Use a line width of 100 points. 
%%{ 72 yline moveto { show (...) show } { show } ifelse }
%%TruncateLine
%%showpage


%%BeginSetup
%%IncludeResource: font Symbol
%%BeginResource: encoding ISO-8859-15Encoding
/ISO-8859-15Encoding [
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/space /exclam /quotedbl /numbersign /dollar /percent /ampersand /quoteright 
/parenleft /parenright /asterisk /plus /comma /minus /period /slash 
/zero /one /two /three /four /five /six /seven 
/eight /nine /colon /semicolon /less /equal /greater /question 
/at /A /B /C /D /E /F /G 
/H /I /J /K /L /M /N /O 
/P /Q /R /S /T /U /V /W 
/X /Y /Z /bracketleft /backslash /bracketright /asciicircum /underscore 
/quoteleft /a /b /c /d /e /f /g 
/h /i /j /k /l /m /n /o 
/p /q /r /s /t /u /v /w 
/x /y /z /braceleft /bar /braceright /asciitilde /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef /.notdef 
/space /exclamdown /cent /sterling /Euro /yen /Scaron /section 
/scaron /copyright /ordfeminine /guillemotleft /logicalnot /hyphen /registered /macron 
/degree /plusminus /twosuperior /threesuperior /Zcaron /mu /paragraph /bullet 
/zcaron /onesuperior /ordmasculine /guillemotright /OE /oe /Ydieresis /questiondown 
/Agrave /Aacute /Acircumflex /Atilde /Adieresis /Aring /AE /Ccedilla 
/Egrave /Eacute /Ecircumflex /Edieresis /Igrave /Iacute /Icircumflex /Idieresis 
/Eth /Ntilde /Ograve /Oacute /Ocircumflex /Otilde /Odieresis /multiply 
/Oslash /Ugrave /Uacute /Ucircumflex /Udieresis /Yacute /Thorn /germandbls 
/agrave /aacute /acircumflex /atilde /adieresis /aring /ae /ccedilla 
/egrave /eacute /ecircumflex /edieresis /igrave /iacute /icircumflex /idieresis 
/eth /ntilde /ograve /oacute /ocircumflex /otilde /odieresis /divide 
/oslash /ugrave /uacute /ucircumflex /udieresis /yacute /thorn /ydieresis 
] def
%%EndResource

% Dictionary for ISO-8859-15 support
/iso15dict 8 dict begin
  /fCourier ISO-8859-15Encoding /Courier reencode_font
  /fCourier-Bold ISO-8859-15Encoding /Courier-Bold reencode_font
  /fCourier-BoldOblique ISO-8859-15Encoding /Courier-BoldOblique reencode_font
  /fCourier-Oblique ISO-8859-15Encoding /Courier-Oblique reencode_font
  /fHelvetica ISO-8859-15Encoding /Helvetica reencode_font
  /fHelvetica-Bold ISO-8859-15Encoding /Helvetica-Bold reencode_font
  /fTimes-Bold ISO-8859-15Encoding /Times-Bold reencode_font
  /fTimes-Roman ISO-8859-15Encoding /Times-Roman reencode_font
currentdict end def

iso15dict begin

%%
%% label text header
%%
/side-font   /fHelvetica-Bold def
/top-font    /fHelvetica-Bold def
/header-font /fHelvetica-Bold def
/number-font /fHelvetica-Bold def

%% Diese Anweisung muss auch als PAGE-HEADER auf alle Folgeseiten
%% Zunächst wandert der Koordinatenursprung in die 
%% linke untere Ecke des ersten Etikettes
%%
left_offset top_offset neg translate
left_margin sheet_length top_margin sub label_height sub translate
%%
%%%% Ende I (header)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

