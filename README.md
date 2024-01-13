# Capstone Library
This library has been specifically developed for my capstone project, aiming to support computer science counterparts in interpreting data from hardware sensors and actuators. The primary goal is to simplify the intricate process of coding for hardware by encapsulating it into straightforward functions.

## Installation
1. Download the library ZIP file from the [Releases page](link-to-releases).
2. Open the Arduino IDE on your computer.
3. Navigate to `Sketch > Include Library > Add .ZIP Library.
4. After the installation, you should see "Your Library Name" in the `Sketch > Include Library` menu.


## Functions

## `void move(int target_pos, int spd = 500)`
A function that controls the position of the tray. Takes in a position argument and moves the tray according to the position. Every time the tray hits the limit switch, that position will be reset to the new neutral position. Outputs no argument.

### Input
- `target_pos` (int): The targeted position of the tray in mm, with a neutral position at value 0. The tray will move to this value’s position. The value ranges from 0-335.
- `spd` (int): Default value: 500. This argument controls the speed of the tray moving. No exact range of this value but a default value of 500 is a good value to start with. TAKE NOTE: Even though it says speed, but it is actually a delay variable. Counterintuitively, in short, the **higher** the value, the **slower** the tray.

### Output
- `current_pos` (int): Returns the updated position of the tray.

## `void resetFront(int spd = 500)`
A function that resets the position of the tray. This function moves the tray to the **front** and stops.

### Input
- `spd` (int): Default value: 500. This argument controls the speed of the tray moving. No exact range of this value but a default value of 500 is a good value to start with. TAKE NOTE: Even though it says speed, but it is actually a delay variable. Counterintuitively, in short, the **higher** the value, the **slower** the tray

### Output
- `current_pos` (int): Returns the updated position of the tray

## `void resetBack(int spd = 500)`
A function that resets the position of the tray. This function moves the tray to the **back** and stops.

### Input
- `spd` (int): Default value: 500. This argument controls the speed of the tray moving. No exact range of this value but a default value of 500 is a good value to start. TAKE NOTE: Even though it says speed, but it is actually a delay variable. Counterintuitively, in short, the **higher** the value, the **slower** the tray

### Output
- `current_pos` (int): Returns the updated position of the tray

## `float* readLuxs()`
A function that cycles through each port of the multiplexer, reads the light sensor values connected to individual ports, and stores them inside an array. Outputs the pointer address of the array.

### Input
- \-

### Output
- `array` (float*): A pointer to an array of size 9, that contains the lux readings of the 9 light sensors
