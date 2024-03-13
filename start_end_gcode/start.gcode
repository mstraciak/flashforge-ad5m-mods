M140 S[bed_temperature_initial_layer_single]
M104 S[nozzle_temperature_initial_layer]
G90
M83
G1 X0 Z0.15 F1200 ;start cleaning nozzle before leveling
M106 S255
G1 X50
G1 X-100
G1 X0
G1 Z5 F6000 ;end cleaning
M140 S60
M109 S120
M106 S0
BED_MESH_CLEAR
BED_MESH_CALIBRATE
M190 S[bed_temperature_initial_layer_single]
M109 S[nozzle_temperature_initial_layer]
;start clean nozzle before print
G1 Z5 F6000
G1 X100 Y110 Z0.25 F1200
G1 X90 E12 F1200
G1 X-110 E12 F2400
G1 Y0 E4 F2400
G1 X-109.6 F2400
G1 Y110 E5 F2400

G92 E0 ;start printing
