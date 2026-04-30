**Alexa-Compatible Bedroom Door Control**

3D printed door control with Alexa for under $50

# Overview

This project is a cost-effective system designed to automate the opening and closing of a standard bedroom door. The assembly mounts directly at the door hinge and utilizes an ESP32-controlled stepper motor to provide precise mechanical movement. To keep the project accessible and easy to replicate, the frame and internal gears are almost entirely 3D printed in PLA. On the software side, the system integrates with Amazon Alexa via the Sinric Pro library, allowing for voice control. 

# Design Decisions

1. Gear Design: To maintain a project budget under $50, the design utilizes the 28BYJ-48 stepper motor. While this motor is highly accessible and cost-effective, it produces relatively low torque. To reach the force required to move a bedroom door, the system required a large gear reduction. A worm gear meshing with a 65-tooth base gear was selected to achieve a 65:1 gear ratio. The other options being considered were a two layer planetary gear box (2x 8:1 layers for a 64:1 ratio) and a cyclodial drive, but a worm gear was chosen for several reasons:

   1. Spatial Efficiency: The worm gear provides a large reduction in a relatively small footprint. A planetary gear box reaching the same ratio would require a larger diameter, taking up more space on the wall and requiring a large print time.

   2. Reduced Complexity: By achieving the target ratio in a single stage, the part count is kept to a minimum. Comparing a worm gear to a cycloidal drive or planetary gear box, it uses much less parts and is the most straightforward to assemble. Multi-layer planetary gear boxes require many different planetary gears and connections, making print time much longer and the final assembly more complicated.

   3. Tolerance Reliability: Alternative designs like cycloidal drives are highly sensitive to 3D printing tolerances. Minor variations in filament width and printer tolerances can lead to increased friction or mechanical locking. The worm gear design is more robust and forgiving, ensuring consistent performance across different 3D printers and materials.

| Design | Parts | Outside Diameter | Notes |
| :---- | :---- | :---- | :---- |
| Worm Gear | 2 | 8 cm | High Friction |
| Planetary Gearbox | 8 | 10 cm | Would need 2 Layers for same gear ratio |
| Cycloidal Drive | 4 | 8 cm | Smoothest, but more complex assembly |

2. Slippage Mechanism: One requirement was ensuring the door remained free to be manually opened and closed while the system was attached. Due to the high 65:1 gear ratio, a direct connection between the motor and the door would make the motor nearly impossible to backdrive.The first design to address this used two flat discs lined with a high-friction material pushed together by a spring. The goal was to allow the plates to slip if manually pushed, while maintaining enough friction to move the door with the motor. However, when testing it was found that getting enough friction to allow the motor to control the door was very difficult, and made it hard to move the door manually. The final design utilizes a slotted cutout in the base gear. This allows the arm to move freely within a specific range of motion without engaging the motor’s drivetrain. This design offers no resistance for manual movement while still allowing the motor to fully control the door when needed.

3. Code: The design is built on custom motor control logic and utilizes the Sinric Pro library for Amazon Alexa integration. This library was chosen for its reliability and wide compatibility compared to alternatives. One important feature of the software design was creating a non-blocking stepper motor loop. Because the door takes a large amount of  time to open or close, a blocking loop would prevent the ESP32 from communicating with the Alexa servers during that time, causing the device to appear unresponsive. By calling a function to step the motor once and tracking the time since that last step, it is possible to have a non-blocking stepper motor loop that allows Sinric Pro to continue running and staying connected.

4. Torque Optimization: Since producing enough torque to move the door was the main challenge in the design, several mechanical and code optimizations were made to reduce both friction and the necessary torque to move the door.

1. Leverage and Arm Lengths: The arm lengths were optimized by extending the arm’s attachment point on the door as much as possible while still allowing each arm to be printed on a standard 20 cm x 20 cm print bed. Increasing the arm’s attachment point on the door decreases the force that must be applied in order to move the door.

2. Friction Reduction: Worm gears, especially when 3D printed, have very high friction and inefficiency. Worm gears are known to have around 40% efficiency, compared to cycloidal drive and planetary gear boxes that have around 70% efficiency. To counter this, the worm gear is printed vertically with fine layer heights to ensure a smoother surface finish on the threads. The use of synthetic lubricant further reduces sliding friction.

3. Code Step Delays: To prevent the motor from stalling during high-load phases such as the final portion of closing the door, the delay between steps increases. This adjustment ensures consistent movement without exceeding the physical limitations of the stepper motor.

# Features

1. Smart Home Integration: Native voice control through Amazon Alexa using the Sinric Pro platform.

2. Thermal Management: Automated coil power-off to prevent motor overheating during idle periods.

3. Asynchronous Processing: Non-blocking firmware ensures the device remains responsive to network commands during operation.

4. Manual Override: A mechanical cutout allows for manual door movements without disconnecting the drive system.

5. Cost-Efficient Design: Optimized for affordability and creation for under $40 with 3D-printed components designed for standard PLA filament.

# Limitations

1. Operation Speed: Due to the high gear ratio required to generate sufficient torque from the 28BYJ-48 motor, a full open/close cycle requires approximately three minutes.

   - Note: This specific motor was selected to prioritize cost-efficiency. Future designs utilizing a higher-torque motor (e.g., NEMA 17\) could significantly reduce this cycle time.

2. Mechanical Requirements: The door must be well-balanced and move freely with less than 5 lbs of force required at the handle.

3. Latch Compatibility: The existing door latch must be taped or removed to allow for automated movement. A magnetic catch is recommended to secure the door when closed without impeding the motor's operation.

4. Connectivity: The ESP32 requires a 2.4GHz Wi-Fi network for cloud communication.

5. Command Syntax: Current Alexa integration utilizes the standard "Turn On/Turn Off" syntax to trigger the open and close cycles.

# Safety and Emergency Procedures

The design includes a primary slippage mechanism to allow for manual motion, as well as built in emergency features to ensure the door remains accessible during power outages, WiFi loss, or emergencies:

- Default Slip Design: When the arm is in its default position, the cutout design allows the door to be opened and closed manually with zero resistance.

- Quick-Release Mounting: The entire assembly is held to the wall by a slide in bracket. This allows for fast removal if needed by pulling the main assembly up, and then the holes will line up and the assembly can be pulled off of the wall.

- Emergency Breakaway (Last case scenario): In an emergency where the motor is stopped in the fully closed position the secondary arm is designed to break if necessary.

# Non-Printed Parts

\*\*Items without a price listed are not factored into the final cost

| Name | Quantity | Cost | Link |
| ----- | ----- | ----- | ----- |
| XIAO ESP32C6 | 1 | $13 | [Link](https://www.amazon.com/dp/B0DRNW9LJM?ref=ppx_yo2ov_dt_b_fed_asin_title) |
| 6701ZZ Bearing | 10 | $8.50 | [Link](https://www.amazon.com/uxcell-6701ZZ-Groove-Bearings-Shielded/dp/B082PP2T1R/ref=sr_1_3?dib=eyJ2IjoiMSJ9.UkOF76jK0MRJNhZprBTfFS5fwy9t3yfm_gPPRMqO4S5CMSc9-1X7PZtYmKDNfyUUdjsGbJF4PVfgMISN5NrygoPDnFlVyCeYuollZB_9foZ8DLEBn5Uur7nX7f5S18CsEI6FS8tf7fOwpkXrWuDri-uh6584ef1dWYIfOlG_GyPCENu4i0xJXDEaQ-ukGngPcBy3p0nthZROEhvPRrfY2i62npd0EOLdxJz9QpIfBPQ.qQKTi4q50riKhKmmBRq3UZf0oMVdVu1ntoLS9RIz_-c&dib_tag=se&keywords=6701ZZ%2Bbearing&qid=1777463904&sbo=RZvfv%2F%2FHxDF%2BO5021pAnSA%3D%3D&sr=8-3&th=1) |
| 28BYJ-48 Stepper Motor \+ ULN2003 Driver | 1 | $7 | [Link](https://www.amazon.com/4-Phase-28BYJ-48-Stepper-ULN2003-Raspberry/dp/B0F8M4BB18/ref=sr_1_6?crid=BTA6RZUS4GBW&dib=eyJ2IjoiMSJ9.B-M5MkIJEuoF6-5If8QRZDoUaY-5pR6X_XkKvXFSmSaNwct-F1bcihsh6BveEPpf92aQ9L66W8RFfk0vPQVaN8bygZT4IJ6DHq7fotisQ1LGECH9ymkoB36TCw-e7tjusclGqa8YdrFJt_9vWU27rRYQz0hWtyoYwVewXhHXUl96OGczNhugrP68_D6QWHWnmh_y0KfEf2m3nD4vL1HRfehEcNV1qAdzrjFAsi3ccnk.loraPzn73IoGKxh5Eff0RotHs731gztxH2Id38_Ea4c&dib_tag=se&keywords=28BYJ-48+%2B+ULN2003&qid=1777464107&sbo=RZvfv%2F%2FHxDF%2BO5021pAnSA%3D%3D&sprefix=28byj-48+%2B+uln2003%2Caps%2C158&sr=8-6) |
| 5V 2A Power Adapter \+ Wire Adapter | 1 | $6 | [Link](https://www.amazon.com/dp/B0FMFXHYJ3?ref=ppx_yo2ov_dt_b_fed_asin_title) |
| Magnets (Optional) | 2 | $5 | [Link](https://www.amazon.com/dp/B0GHMHMY7V?ref=ppx_yo2ov_dt_b_fed_asin_title) |
| Dry Wall Anchors \+ Screws | 4 | \- | \- |
| Command Strips | 4 Pairs | \- | \- |
| Silicon Lubricant | 1 | \- | Any general purpose silicone grease  |
| 5mm M3 Screws | 4 | \- | \- |
| 6mm M3 Screws | 2 |  |  |
| 10mm M3 Screws | 6 | \- | \- |
| 15mm M3 Screws | 2 | \- | \- |
| 20mm M3 Screws | 3 | \- | \- |
| M3 Nuts | 4 | \- | \- |
| M3 Washers | 3 | \- | \- |
| TOTAL COST: | \- | $39.50 | \- |

# Printed Parts

All parts can be printed in PLA. 1 of each part must be printed.  
Onshape:[https://cad.onshape.com/documents/3e4b522c54b8b294a1afd016/w/298214d4b85e58891adc7ef1/e/4cf30c14211e550b4f351c0a](https://cad.onshape.com/documents/3e4b522c54b8b294a1afd016/w/298214d4b85e58891adc7ef1/e/4cf30c14211e550b4f351c0a)

| Name | Infill | Walls | Support | Layer Height | Notes |
| :---: | :---: | :---: | :---: | :---: | :---: |
| Main Body | 30% | 4 | Tree | 0.2 |  |
| Wall Mount | 30% | 4 | \- | 0.16 |  |
| Body Lid | 20% | 2 | \- | 0.2 |  |
| Electronics Lid | 20% | 2 | Grid | 0.2 | Tiny support under sunken in screw head location |
| Worm Gear\* | 50% | 6 | Grid | 0.1 | supports on bottom so it doesn’t fall off build plate |
| Base Gear | 50% | 4 | \- | 0.16 |  |
| Base Gear Top | 50% | 4 | \- | 0.16 |  |
| Arm 1 | 60% | 6 | \- | 0.16 |  |
| Arm 1 Top | 60% | 6 | \- | 0.16 |  |
| Arm 2 | 60% | 6 | \- | 0.16 |  |
| Door Attachment | 30% | 2 | \- | 0.16 |  |
| Door Attachment Side | 30% | 2 | \- | 0.16 |  |
| Door Magnet | 30% | 2 | \- | 0.16 | OPTIONAL |
| Wall Magnet | 30% | 2 | \- | 0.16 | OPTIONAL |

\*Worm gear can be printed in PETG to reduce friction if needed, though it still works if printed in PLA

Tolerances: Right now, inside bearings are set to 1.21 cm instead of 1.20 cm and outsides are set to 1.84 cm instead of 1.80. These are the settings that have worked well for my printer. If your printer has different tolerances, these are set as variables in the Onshape so it is easy to adjust.

# Firmware and Code Setup

1. Arduino IDE Setup  
   1. Open or install Arduino IDE  
   2. Go to File \-\> Preferences and paste the official Espressif link into the Additional Boards Manager URLs: https://espressif.github.io/arduino-esp32/package\_esp32\_index.json  
   3. Navigate to Boards Manager and install the Espressif ESP32 boards platform  
   4. Board Selection: Tools \-\> Board \-\> esp32 \-\> Seeed Studio XIAO\_ESP32C6  
   5. Libraries: Install SinricPro from library manager

2. Sinric Pro Setup  
   1. Go to [https://sinric.pro/](https://sinric.pro/) and make an account  
   2. Go to the devices tab and click “Add Device”  
      1. Device Name: Door Control  
      2. Device Type: Switch  
      3. \*\*All other settings can be left as default  
   3. Click save and the device should be added to the dashboard

3. Code Setup  
   1. Download the files “doorOpener.ino” and “credentials.h” and place them in the same folder  
   2. To fill in credentials.h:  
      1. Fill in wifi name and password for WIFI\_SSID and WIFI\_PASS  
      2. SINRIC\_APP\_KEY and SINRIC\_APP\_SECRET are found under the “Credentials” tab in the Sinric Pro website  
      3. SINRIC\_DEVICE\_ID is found directly below the device name in the “Devices” tab  
   3. Compile and upload the code onto the ESP32C6. Credentials.h will automatically be included.

4. Alexa Setup  
   1. Search for the Sinric Pro skill in the Alexa app  
   2. Install the Sinric Pro skill and follow the instructions to link accounts  
   3. Say, “Alexa, discover devices”  
   4. Once Alexa finds the new device, name it “door”  
      1. Note: The device must be named exactly "door" to enable natural voice commands like "Alexa, turn the door on" or "turn the door off."

5. Code Verification  
   1. Open the Arduino IDE Serial Monitor and set the baud rate to 115200\. Verify that the console prints “\[SINRIC\] Connected\!”  
   2. Test the connection via the Alexa app by toggling the device on and off. The state should change smoothly in the app without displaying an error message or "device unresponsive" warning.

# Assembly

Step 1: Arm Linkage Assembly  
Parts: Arm 1 and Arm 1 Top, Arm 2, Door Attachment and Door Attachment Side, 4 Bearings, 2 M3x6mm screws, 2 M3x15mm screws, 2 M3 washers, 4 M3 nuts.

1. Press-fit the four bearings onto the cylinders located at both ends of Arm 2\.  
     
2. Secure the Door Attachment and Door Attachment Side to one end of Arm 2 using two M3x10mm screws and nuts.  
     
3. Join Arm 1 and Arm 1 Top to the opposite end of Arm 2, securing the assembly with two M3x15mm screws, washers, and nuts.  
     
4. Verify that the completed assembly moves smoothly at all joints and that all screws are securely tightened.

Step 2: Main Body and Arm Integration  
Parts: Main Body, Worm Gear, Base Gear, Base Gear Top, Lubricant, 6 Bearings, 2 M3x10mm screws, Arm Assembly

1. Worm Gear Preparation: Apply lubricant to the Worm Gear threads and install a bearing on each end of the shaft. Insert the assembly into the main body housing, ensuring the motor shaft receptacle faces outward. Confirm the worm gear rotates freely within the housing.

2. Base Gear Installation: Seat one bearing into the underside of the Base Gear. Slide the gear onto the main shaft until it reaches the base. Manually rotate the worm gear to mesh the teeth and align the base gear to the angle specified in the reference image.

3. Arm Linkage Integration: Install two bearings into the housing of Arm 1, one on top and one on the bottom. Slide the pre-assembled Arm Assembly onto the main shaft.

4. Drive Train Finalization: Install a bearing into the Base Gear Top and slide it down the main shaft. Secure the Base Gear Top to the Base Gear using two M3x10mm screws, ensuring the arm assembly remains captured but mobile.

Step 3: Motor and Driver Installation  
Parts: Stepper Motor, Motor Driver, 1 M3x20mm screw, 4 M3x5mm screws

1. Insert the Stepper Motor into the main body, ensuring the shaft fully engages with the internal worm gear.

2. Secure the motor by installing the M3x20mm screw into the designated top mounting hole.

3. Route the motor wiring through the cable pass-through hole located immediately adjacent to the motor housing.

4. Align the Motor Driver with the four mounting holes in the rear electronics compartment.

5. Secure the driver using four M3x5mm screws and connect the stepper motor wiring harness to the designated header on the driver board.

Step 4: Custom Low-Profile Power Harness  
Parts: 3x Female-to-Female (F-F) Jumper Wires, DC Power Jack Adapter

\*\*\*Short Circuit Risk: Ensure all junctions are thoroughly insulated. Exposed wire strands can cause a short circuit, potentially damaging the ESP32 or the motor driver. Verify all connections with a multimeter before applying power.  
\*\*Note: Due to the compact nature of the electronics housing, standard connectors like breadboards or lever nuts were excluded to minimize the overall footprint of the device.

1. Wire Preparation: Cut the three jumper wires in half to create six equal segments. Strip approximately 10mm of insulation from the cut ends of each segment.  
     
2. Junction Creation: Form a 3-way "Y" junction. Soldering these junctions is highly recommended to ensure long-term electrical conductivity and vibration resistance. Lightly pull the ends apart to verify the connection is secure.  
     
3. Power Input Prep: On each Y-harness, select one of the remaining ends and strip 10mm of insulation. These two leads will serve as the primary Positive (+) and Negative (-) inputs for the DC power adapter.

4. Insulation: Seal each junction with heat-shrink tubing. This provides mechanical strain relief and prevents short circuits within the cramped enclosure.

Step 5\. Logic and Power Wiring  
Parts: ESP32C6, Jumper Wires

1. Microcontroller Placement: Seat the ESP32C6 into the designated thin-walled section of the main body, ensuring the pins align with the two rows of cutouts. The USB-C port should face towards the middle of the body.  
     
2. Signal Connections: Thread four female-to-female jumper wires through the upper pin cutout. Connect the ESP32 pins to the Motor Driver inputs according to the table below.  
     
3. Power Integration: Thread the two Y-harnesses through the bottom cutout. Connect the female leads of the Positive (+) harness to VBUS on the ESP32 and 5V on the Motor Driver. Connect the Negative (-) harness to GND on both boards.  
     
4. Input Power: Secure the stripped ends of the Y-harnesses into the DC power adapter terminals, verifying that one harness is dedicated strictly to Positive (+) and the other to Ground (-).

   Wiring Diagram:

   Stripped End \+5v \-\> ESP32 VBUS \+ Motor Driver 5v

   Stripped End \-GND \-\> ESP32 GND \+ Motor Driver GND

   

   Motor Driver IN1 \-\> ESP32 B0

   Motor Driver IN2 \-\> ESP32 B1

   Motor Driver IN3 \-\> ESP32 B2

   Motor Driver IN4 \-\> ESP32 B3

   

Step 6: Enclosure  
	Parts: Body Lid, Electronics Lid, 4 M3x10mm screws, 2 M3x20mm screw, 1 M3 Washer.

1. Align the Body Lid with the main shaft and secure it using three M3x10mm screws.

2. Fit all of the cables into the area between the body and electronics lid so they are not pinched and all connections remain connected.

3. Place the DC Adapter into the housing on the inside of the lid. Screw 1 M3X20mm screw through the hole in the side of the lid to secure it. Be sure all connections are still in place.

4. Place the electronics lid over the cables and screw in one M3x10mm screw on the top and one M3x20mm screw on the bottom.

Step 7: Wall Mount Positioning  
Parts: Mounting Bracket, 4 Drywall Anchors and Screws

1. Alignment: Attach the mounting bracket to the main assembly. Position the assembly against the wall on the hinge side of the door.  
     
2. Height Specification: Ensure the door attachment arm sits approximately 5 cm below the top edge of the door.  
     
3. Marking: Level the assembly and mark the four mounting hole locations on the wall with a pencil.  
     
4. Anchoring: Remove the assembly, drill the marked holes, and insert the drywall anchors. Detach the mounting bracket from the main assembly and secure the bracket to the wall using the provided screws.

Step 8: Door Attachment  
Parts: 4 Command Strips

1. Adhesive Preparation: Apply two Command Strips to the rear of the door attachment piece (one on each half). Reinstall the main assembly onto the wall-mounted bracket.  
     
2. Door Attachment Placement: With the door fully closed, extend the arm assembly across the door. Position the door attachment piece at its maximum extension, then retract it 1 cm back toward the hinge to prevent mechanical strain during operation.  
   

   Note: The final position of the attachment piece should be approximately 26 cm from the door hinge.

     
3. Final Adhesion: Apply the matching Command Strips to the door surface at the calibrated position and firmly press the attachment piece into place.

Step 9: Magnetic Catch (Optional \- Keeps door closed in door naturally swings open)  
Parts: 2 10 x 60 x 3mm magnets, 4 Command Strips, Door Magnet print, Wall Magnet print

1. Put command strips on the bottom of both the door magnet and wall magnet prints. Ensure the foam end is pointing away from the magnets housing.

2. Place a magnet into the rectangular hole in both the door magnet and wall magnet prints.

3. Stick the door magnet onto the door using the command strips so that the edge of the print is level with the side of the door and the end with the magnet is facing towards the outside wall

4. Stick the wall magnet onto the wall level with the door magnet so that it does not interfere with the doors path, but is lined up with the door magnet when the door is closed.

5. TEST: The 2 magnets should visibly move towards each other when the door is closed, and have enough strength to hold the door shut without physically touching each other or the door

# Future Improvements

These are changes that are being considered, and may appear in the future.

1. Cyclodial Drive: A cyclodial drive would address 2 of the limitations for this setup: It would make the door open and close faster, and also provide more torque for moving heavier doors and keeping the doors natural latching mechanism. However, before this is fully implemented it will need to be tested to ensure that users are able to easily assemble the cyclodial drive and that printers with varied tolerances are able to print it and still have it be functional and low friction. Considering the design all uses minimal non-printed parts, the cycloidal drive would have 3D printed pins, further increasing friction. Testing would need to be done to ensure that it is still beneficial even with the added friction.

2. Alexa compatible library or setup changes: Currently, the user must say to either turn on or off the door. This is naturally confusing, and it would be beneficial if the user could use normal phrasing of open and close the door. Currently, the setup with SinricPro does not allow this to happen because setting up the door opener as a garage door requires the user to tell Alexa a password every time they want to use the command, which most would consider more work than saying to turn the door on or off. For that reason, new libraries or new setups are being looked into to allow for easier communication with Alexa. As a temporary solution, the user is able to set up a routine in Alexa that allows them to say open or close the door.
