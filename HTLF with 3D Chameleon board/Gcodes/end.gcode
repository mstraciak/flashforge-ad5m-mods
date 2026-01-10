G90
M83
G92 E0

G0 Y20 X2 F6000 
G0 Y2 X2 F2000 ;odstrihne filament
G0 Y2 X30 F6000
G0 Y25 X30 ;pravouhly pohyb aby nezachytil rameno
G0 Y25 X2 F6000
G0 Y25 X0 F2400 ;stlacenie tlacidla
G4 P2700  ;caka 6 pulzov pre strih filamentu
G0 Y25 X2 F2400 ;presun k tlacidlu
G4 P2000
G0 Y25 X0 F2400 ;stlacenie tlacidla  
G4 P3500  ;dlzka vysuvania
G0 Y25 X2 F2400 ;presun k tlacidlu

G0 E85 F2000 ;vytlacenie zbytku

M104 T0 S0
M140 S0
G28 X Y Z
;M107 P102
G91
M18
M84     ; disable motors
M300 S3000 P200
M300 S3000 P200
M300 S0 P10
M300 S3000 P200
M300 S3000 P200
