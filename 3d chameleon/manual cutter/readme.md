# Files for 3D chameleon on Flashforge Adventurer 5M <ins>WITHOUT</ins> servo cutter (manual or semi-automatic cutting)
## Gcodes for Flashforge adventurer 5M
### Start gcode:
- Cleaning nozzle before leveling
- Leveling heatbed
- Purge filament from previous printing (if there is something forgetten)
- Select color by slicer (if you chose different color for start printing than #1, it will auto select correct color)
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

Note: With my gcodes was flushing volumes between each filament 215mm<sup>3</sup> (Multiplier 1.00). Its good value for start.

  
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
4 in 1 ptfe adapter for using festo fittings. Alternatively you can use bambulab 4to1 ptfe adapter.

**UPDATE 19.4.2025**
Recomend using version 2 where is knife position lower 5mm (closer to the hotend) 

**UPDATE 4.5.2025**
Added version with better orientation. since this version i use bambulab filament hub 4to1 and ver.2 gcodes (start, end, change).
Added gcode to existing macro in file macros.cfg. For cutting and unload filament with cancel printing.


**Other parts:**
- one piece from 9mm blade for utility knife
- spring from ball pen
- M3x20 
- M3x16 (as stop screw) 
- push-in fitting from festo for 4mm tube


  ![screenshot](img/IMG20250402203225.jpg)
    ![screenshot](img/IMG20250402203259.jpg)
    ![screenshot](img/IMG20250402203352.jpg)
    ![screenshot](img/IMG20250402203529.jpg)
    ![screenshot](img/IMG20250402203504.jpg)
    ![screenshot](img/screen.png)




