
M117 Unloading Tool T[previous_extruder]
M83 ; turn relative distances for the extruder
G92 E0

G0 E-45 F500 ;retract for cut =<46mm
G0 Y0 X-100 F18000 
G0 Y-90 X-100 F18000
G0 Y-105 X-100 F1800 ;odstrihne filament
G0 E45 F1500
;G0 Y-105 X-80 F18000
G0 Y0 X-100 F18000 ;vrati sa ku tlacidlu


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

G0 X-10 F6000
{if next_extruder==0}
G4 P600 ; dwell for .5 seconds - adjust this to match your machines single pulse time
{endif}
{if next_extruder==1}
G4 P1200 ; dwell for 1.0 seconds - adjust this to match your machines two pulse time
{endif}
{if next_extruder==2}
G4 P1700 ; dwell for 1.5 seconds - adjust this to match your machines three pulse time
{endif}
{if next_extruder==3}
G4 P2200 ; dwell for 2.0 seconds - adjust this to match your machines four pulse time
{endif}
G0 X10
G4 P2000

{if previous_extruder>-1}
{endif}

G1 X-10 F6000 ;vysuva filament 
G4 P2500
G1 X10 F6000
G4 P300
G1 X-10 F6000 ;zasuva filament 
G4 P3800
G1 E5 F1500 ;povodna hodnote 78mm
G1 X10 F3000 ;presun k tlacidlu

G92 E0
G90 ; move back to absolute mode
M83 ; but make sure the extruder stays in relative
G92 E0
M83 ; turn relative distances for the extruder
M117 3D Chameleon Tool T{next_extruder}
