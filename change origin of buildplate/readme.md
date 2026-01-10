After installing klipper_mod (from xblax) is origin (X0,Y0) at the center of the buildplate. Homing position is X110 and Y110.
Here are steps, if you need origin in the front left corner (X0,Y0) and homing position at X220, Y220. 
Steps here are for klipper_mod v00.06 beta.
Here are lines from my config files.


## Changes in printer.base.cfg:
> [!NOTE]
>Old values begining with #.
>Example: ``` position_endstop: 220 #110```  (110 is old value, 220 is new value)

1. change in [stepper_x]
   ```
   position_endstop: 220 #110
   position_max: 220.2 #110.1
   position_min: 0 #-110
   ```
2. change in [stepper_y]
   ```
   position_endstop: 220 #110
   position_max: 220.2 #110.1
   position_min: 0 #-110
   ```

3. change in [resonance_tester]
   ```
   probe_points:
       110,110,100 #0,0,100
   ```

4. change in [homing_override]
   ```
   #G1 X105 Y105 Z210 F1800
   G1 X215 Y215 Z210 F1800
   ```
5. change in [bed_mesh]
    ```
   mesh_min: 10, 10 #-100, -100            
   mesh_max: 210, 210 #100, 100
    ```

6. change in [screw_tilt_adjust]
    ```
   screw1: 16, 16 #-94, -94
   screw1_name: Left Near
   screw2: 204, 16 #94, -94
   screw2_name: Right Near
   screw3: 204, 204 #94, 94
   screw3_name: Right Far
   screw4: 16, 204 #-94, 94
    ```


## Changes in printer.cfg:
1. there is normaly no changes


## Changes in macros.cfg (note: i dont have PRO version):
> [!NOTE]
>Old values begining with ;
> Example: ```variable_custom_park_x    : 110 ;-105.0 ``` (-105 is odl value, 110 is new value)

1. change in [gcode_macro _CLIENT_VARIABLE]
   ```
   variable_custom_park_x    : 110 ;-105.0  ; custom x position; value must be within your defined min and max of X
   variable_custom_park_y    : 10 ;-105.0  ; custom y position; value must be within your defined min and max of Y
   variable_park_at_cancel_x : 110 ;105     ; different park position during CANCEL_PRINT [None/Position as Float]; park_at_cancel must be True
   variable_park_at_cancel_y : 10 ;105     ; different park position during CANCEL_PRINT [None/Position as Float]; park_at_cancel must be True
   ```
   
2. change in [gcode_macro _COMMON_END_PRINT]
   ```
   ;G1 X105 Y105 Z220 F1500 ; move near end stop position
    G1 X215 Y215 Z220 F1500 ; move near end stop position
   ```

3. change in [gcode_macro _PRIME_NOZZLE]
   ```
    ;G90
    ;M83
    ;G1 E-1.5 F800
    ;G1 X110 Y-110 F6000
    ;G1 E2 F800
    ;G1 Y-110 X55 Z0.25 F4800
    ;G1 X-55 E8 F2400
    ;G1 Y-109.6 F2400
    ;G1 X55 E5 F2400
    ;G1 Y-110 X55 Z0.45 F4800
    ;G1 X-55 E8 F2400
    ;G1 Y-109.6 F2400
    ;G1 X55 E5 F2400
    ;G92 E0

    G90
    M83
    G1 E-1.5 F800
    G1 X220 Y0 F6000
    G1 E2 F800
    G1 Y0 X165 Z0.25 F4800
    G1 X55 E8 F2400
    G1 Y0.4 F2400
    G1 X165 E5 F2400
    G1 Y0 X165 Z0.45 F4800
    G1 X55 E8 F2400
    G1 Y0.4 F2400
    G1 X165 E5 F2400
    G92 E0



## Changes in OrcaSlicer:
1. open settings for your printer profile
   ![img](img/orca_orgin1.png)

2. Select "set" for printable area
   
   ![img](img/orca_origin2.png)
3. Change "origin" coordinates to X0 and Y0.

   ![img](img/orca_origin3.png)


> [!CAUTION]
> Dont forget change your start/end gcodes!!!


And now you should have origin in left front corner of the buildplate and you can use exclude area and primetower location where you want.
