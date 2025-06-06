# Files for 3D chameleon on Flashforge Adventurer 5M with servo cutter (autoclipy)
## Gcodes for Flashforge adventurer 5M
### Start gcode:
- Cleaning nozzle before leveling
- Leveling heatbed
- Purge filament from previous printing (if there is something forgetten)
- Select color by orca slicer (if you chose different color for start printing than #1, it will auto select correct color)
- Load filament into extruder
- Purge nozzle before printing

### End gcode:
- Select "Unload filament" command in chameleon
- Cut filament
- Purge filament from printing (prepare for load in new printing)
- Homing
- Beep for notification of ended printing

### Change gcode:
- Retract filament for cutting (to minimize residual filament = less filaments for clean color)
- Select correct color
- Cut filament
- Unload filament
- Extrude residual filament (prepare extruder for new color)
- Load new color

Note: With my gcodes was flushing volumes between each filament 215mm<sup>3</sup> (Multiplier 1.00). Its good value for start.
  
## My STL files for using chameleon
**ad5m-v5-4in1.stl:**\
Rotate with holes to buildplate. support only on buildplate.

**chameleon-*.stl:**\
Print from PETG. part with oled mount print facing down, support only on buildplate.

**clipy-ad5m-body.stl:**\
Rotate to the flat side. need all supports.
 Position of switch is in the middle on the left side. 

## Firmware files.
All collected firmware files for 3D chameleon. I recommended version MK4.1. Also is here guide to burn firmware.
