
; ZACIATOK VYMENY

M117 Unloading Tool T[previous_extruder]
M83 ; turn relative distances for the extruder
G92 E0

G0 E-37 F1000 ;retract for cut =<46mm !!!!!!
G0 Y25 X2 F18000   ;presun k tlacidlo
G0 Y20 X2 F18000   ;presun k strihaniu
G0 Y3 X2 F1800 ;odstrihne filament
G0 Y3 X40  E45 F1500
;G0 Y3 X30 F18000 ;neplati?
G0 Y25 X2 F18000 ;vrati sa ku tlacidlu


G91 ; move to relative mode

;M83
;M117 Loading Tool T{next_extruder}

{if previous_extruder>-1}
;G1 E-25 F1500
;M109 S165
;G1 E-70 F700
;M104 S[nozzle_temperature_initial_layer]
{endif}

{if previous_extruder>-1}
;G92 E0
;G91 ; move to relative mode
;M82

{endif}

G0 X-2 F6000
{if next_extruder==0}
G4 P600 ; dwell for .5 seconds - adjust this to match your machines single pulse time
{endif}
{if next_extruder==1}
G4 P1000 ; dwell for 1.0 seconds - adjust this to match your machines two pulse time
{endif}
{if next_extruder==2}
G4 P1400 ; dwell for 1.5 seconds - adjust this to match your machines three pulse time
{endif}
{if next_extruder==3}
G4 P1800 ; dwell for 2.0 seconds - adjust this to match your machines four pulse time
{endif}
G0 X2
G4 P3000

{if previous_extruder>-1}
{endif}

G1 X-2 F6000 ;vysuva filament 
G4 P3500  ;dlzka vysuvania filamentu
G1 X2 F6000
G4 P2000
G1 X-2 F6000 ;zasuva filament 
G4 P5500
G1 E5 F1496 ;povodna hodnote 78mm !!!!!!!!!!!!!!!!
G1 X2 F3000 ;presun k tlacidlu

G92 E0
G90 ; move back to absolute mode
M83 ; but make sure the extruder stays in relative
G92 E0
M83 ; turn relative distances for the extruder
M117 3D Chameleon Tool T{next_extruder}

; KONIEC VYMENY

