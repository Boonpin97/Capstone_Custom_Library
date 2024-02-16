# Tray Control
This library has been specifically developed for my capstone project, aiming to support computer science counterparts in interpreting data from hardware sensors and actuators. The primary goal is to simplify the intricate process of coding for hardware by encapsulating it into straightforward functions.

## Installation
1. **Open Terminal (macOS/Linux) or Command Prompt (Windows):** 

2. **Navigate to the Desired Directory:**
   - Use the `cd` command to navigate to the Arduino library director. For example:
     ```bash
     cd /path/to/your/Arduino/library/directory
     ```

3. **Clone the Repository:**
     ```bash
     git clone https://github.com/piapstone/Tray_Control.git
     ```
4. **Downloading WS2811 LED library dependencies (ignore if you already have it)**

      ```bash
     git clone https://github.com/adafruit/Adafruit_NeoPixel.git
     ```

## Attributes
- `current_pos: int`
- `power_consumption  : float`
- `current_consumption: float`

### `int current_pos`
A attribute that keeps track of the position of the tray in mm
### `int power_consumption`
A attribute that keeps track of the power consumption in Wh
### `int current_consumption`
A attribute that keeps track of the current drawn in Ampre


## Methods
- `begin(): void`
- `move(target_pos: int, spd: int): bool`
- `resetFront(spd: int): bool`
- `resetBack(spd: int): bool`
- `disableTray(): void`
- `readLuxs(): float*`
- `readTempFront(): float`
- `readTempBack(): float`
- `readHumiFront(): float`
- `readHumiBack(): float`
- `eStopPressed(): bool`
- `resetPressed(): bool`
- `setRedWhiteLight(strip_index: int, brightness: int): void`
-  `setColor(strip_index: int, r: int, g: int, b: int, brightness: int): void`
- `offLight(strip_index: int): void`
- `setStatusLight(r: int, g: int, b: int, brightness: int): void`
- `updatePower(): void`

## `void begin()`
A function that initalize the tray. This includes the GPIO pins declaration, settings the lights to off, initializing the light sensors.

&nbsp;

## `bool move(int target_pos, int spd = 10)`
A function that controls the position of the tray. Takes in a position argument and moves the tray according to the position. If the tray hits a limit switch, the tray will stop and updates the attribute **current_position** as the maximum length. If the target position has not been reached yet, the tray moves by 1mm each time this function is called. If the target position has been met, the tray will not move even if this function is called.


### Input
- `int target_pos` _(0-780)_ : The targeted position of the tray in mm, with a neutral position at value 0. The tray will move to this value’s position.
- `int spd` _(0-100)_ : Default value: 10. This argument controls the speed of the tray moving.

### Output
- `bool reached` : 
<br>
-Return **true** if the target position is reached or limit siwtch is hit
<br>
-Return **false** if target position is not reached
&nbsp;

&nbsp;

## `bool resetFront(int spd = 10)`
A function that resets the position of the tray. This function moves the tray to the **front** and stops. If the target position has not been reached yet, the tray moves by 1mm each time this function is called. If the target position has been met, the tray will not move even if this function is called.

### Input
- `int spd` _(0-100)_ : Default value: 10. This argument controls the speed of the tray moving. If the target position has not been reached yet, the tray moves by 1mm each time this function is called. If the target position has been met, the tray will not move even if this function is called.

### Output
- `bool reached` : 
<br>
-Return **true** if the target position is reached or limit siwtch is hit
<br>
-Return **false** if target position is not reached
&nbsp;

&nbsp;
 
## `bool resetBack(int spd = 10)`
A function that resets the position of the tray. This function moves the tray to the **back** and stops.

### Input
- `int spd` _(0-100)_ : Default value: 10. This argument controls the speed of the tray moving.

### Output
- `bool reached` : 
<br>
-Return **true** if the target position is reached or limit siwtch is hit
<br>
-Return **false** if target position is not reached
&nbsp;

&nbsp;
 
## `void disableTray()`
A function that unlocks the tray to allow it to be free moving
&nbsp;

&nbsp;
 
## `float readLuxs()`
A function that cycles through each port of the multiplexer, reads the light sensor values connected to individual ports, and stores them inside an array. Outputs the pointer address of the array.

### Output
- `float array` : A pointer to an array of size 6, that contains the lux readings of the 6 light sensors

&nbsp;

&nbsp;
 
## `float readTempFront()`
A function that returns the value of the temperature sensor at the front of the tray in °C.

### Output
- `float temperature` : A float that contains the temperature in °C 

&nbsp;

&nbsp;
 
## `float readTempBack()`
A function that returns the value of the temperature sensor at the back of the tray in °C.

### Output
- `float temperature` : A float that contains the temperature in °C 
&nbsp;

&nbsp;
 
## `float readHumiFront()`
A function that returns the value of the humidity sensor at the front of the tray in °C.

### Output
- `float temperature` : A float that contains the humidity in % 

&nbsp;

&nbsp;
 
## `float readTHumiBack()`
A function that returns the value of the humidity sensor at the back of the tray in °C.

### Output
- `float temperature` : A float that contains the humidity in % 

&nbsp;

&nbsp;
 
## `bool eStopPressed()`
A function that returns the state of the emergency stop button. 

### Output
- `bool state` : A boolean that describes the state of the button. **True(Pressed)**, **False(Released).**

&nbsp;

&nbsp;
 
## `bool resetPressed()`
A function that returns the state of the reset button. 

### Output
- `bool state` : A boolean that describes the state of the button. **True(Pressed)**, **False(Released).**

&nbsp;

&nbsp;

## `void setRedWhiteLight(int strip_index, int brightness = 50)`
This function controls individual strips of LED. This functions turns on 1 red LED for every 3 white LED.

### Input
- `int strip_index` _(0-3)_ : Index of the strip you are controlling
- `int brightness` _(0-255)_ : Default value: 50. Controls the brightness of LED

&nbsp;

&nbsp;
 
## `void setColor(int strip_index, int r, int g, int b, int brightness = 50)`

### Input
- `int strip_index` _(0-3)_ : Index of the strip you are controlling
- `int r` _(0-255)_ : Intensity of red light 
- `int g` _(0-255)_ : Intensity of green light 
- `int b` _(0-255)_ : Intensity of blue light 
- `int brightness` _(0-255)_ : Default value: 50. Controls the brightness of LED.

&nbsp;

&nbsp;

## `void offLight(int strip_index)`

### Input
- `int strip_index` _(0-3)_ : Index of the strip you are turning off

&nbsp;

&nbsp;

## `void setStatusLight(int r, int g, int b, int brightness = 50)`

### Input
- `int r` _(0-255)_ : Intensity of red light 
- `int g` _(0-255)_ : Intensity of green light 
- `int b` _(0-255)_ : Intensity of blue light 
- `int brightness` _(0-255)_ : Default value: 50. Controls the brightness of LED.

&nbsp;

&nbsp;

## `void updatePower()`
A function that reads the value from current sensor and converts it into power consumption. Everytime this function is called, it updates the **power_consumption** attribute, thus this function should be called as often as possible to ensure accuracy of the result.

&nbsp;
 

