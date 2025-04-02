# Files for 3D chameleon on Flashforge Adventurer 5M <ins>WITHOUT</ins> servo cutter (manual cutting)
## Gcodes for Flashforge adventurer 5M
### Start gcode:
- Cleaning nozzle before leveling
- Leveling heatbed
- Purge filament from previous printing (if there is something forgetten)
~~- Select color by orca slicer (if you chose different color for start printing than #1, it will auto select correct color)~~(not implemented)
- Load filament into extruder
- Purge nozzle before printing

### End gcode:
- Select "Unload filament" command in chameleon
- Move to position and cut filament
- Purge filament from printing (prepare for load in new printing)
- Homing
- Beep for notification of ended printing

### Change gcode:
- Retract filament for cutting (to minimize residual filament = less filaments for clean color)
- Select correct color
- Move to position and cut filament
- Unload filament
- Extrude residual filament (prepare extruder for new color)
- Load new color

  
## My STL files for using chameleon
**ad5m cut-arm-*.stl:**\
Cutting arm for manual cutter. Print without support.

**ad5m cut-block.stl:**\
Block for manual cutting. Position is front left corner.

**ad5m cut-1to1input.stl:**\
Main body for manual cutter. Print with support. After printing clean all holes, specialy for knife.

**4tubes - guider.stl:**\
Simple holder for 4 tubes.

**ad5m 4n1 - body.stl:**\
4 in 1 ptfe adapter for using festo fittings.


**Other parts:**
- one piece from 9mm blade for utility knife
- spring from ball pen
- M3x20 
- M3x16 (as stop screw) 
- push-in fitting from festo for 4mm tube



