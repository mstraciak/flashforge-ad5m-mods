G90
M83
G92 E0

G0 Y-90 X-100 F6000 
G0 Y-105 X-100 F2000 ;odstrihne filament
;G0 Y-108 X-80 F6000
G0 Y0 X-100 F6000
G0 Y0 X-110 F2400 ;stlacenie tlacidla
G4 P3000  ;caka 6 pulzov pre strih filamentu
G0 Y0 X-100 F2400 ;presun k tlacidlu
G4 P2000
G0 Y0 X-110 F2400 ;stlacenie tlacidla  
G4 P2500  ;dlzka vysuvania
G0 Y0 X-100 F2400 ;presun k tlacidlu

G0 E65 F2000 ;vytlacenie zbytku

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
