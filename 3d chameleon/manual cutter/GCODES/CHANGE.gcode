
M117 Unloading Tool T[previous_extruder]
M83 ; turn relative distances for the extruder
G92 E0

G0 E-50 F500 ;retract for cut (47mm)    #1 ADJUST!!! WITH #2
G0 Y0 X-100 F6000 
G0 Y-105 X-100 F6000 ;odstrihne filament
G0 Y-105 X-80 F6000
G0 Y0 X-100 F6000 ;vrati sa ku tlacidlu
G0 E55 F900     ;vytlaci odstrihnuty     #2 ADJUST!!!! WITH #1

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
G4 P5000      
G1 X10 F6000
G4 P300
G1 X-10 F6000 ;zasuva filament 
G4 P4400
G1 E51 F1500 ;original value 78mm. ADJUST!!!! #3
G1 X10 F3000 ;presun k tlacidlu
;G1 E35 F400  ;optional




G92 E0
G90 ; move back to absolute mode
M83 ; but make sure the extruder stays in relative
G92 E0
M83 ; turn relative distances for the extruder
M117 3D Chameleon Tool T{next_extruder}
