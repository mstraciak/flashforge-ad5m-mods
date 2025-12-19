# Files for modified HTLF with 3d chameleon PCB

**Changes in HTLF design (new STL files):**
- The lobe elements are rotated 70 degrees relative to each other. This ensures that only one filament is pressed at a time and the others are loose.
- The PCB holder is supplemented with holes for the 3D chameleon PCB.
- Only the home switch is used. The other switches are not used.

**Changes in firmware:**
- Removed OLED display support (due to ws2812b and home switch support)
- Home switch connected to the connector marked "S LIMIT"
- WS2812B connected to the connector marked "FILAMENT"
- Removed the option to choose a random filament
- Removed the option to select the next filament in the sequence
- Removed "no command" option. Replaced with "home and idle" command
- Removed motor vibration function when selecting filament
- Removed support for other devices
- Option to select extruder feedrate in code (1197,1496,1796,2245). Note: Original 3D chameleon uses feedrate 1500, so the setting for feedrate 1496 can be used).
- After inserting the current filament into the extruder, the lobe elements move to a parking position where they do not press any filament.
**The "guillotine" function for cutting filament using a servo motor is untouched.**

**Planned changes:**
- Add command to move to parking position
- Code optimization
