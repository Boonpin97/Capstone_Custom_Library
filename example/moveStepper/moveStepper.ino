/*
    This example resets the Tray to the 0 position.
   Open the Serial Monitor, change the settings to "No Line Ending"
   Input the desired position for the tray to move to
*/

#include "Capstone.h"

// Pin Declaration
#define stepPin 33        // motor driver step pin
#define dirPin 32         // motor driver direction pin
#define backLimitPin 36   // back limit switch pin
#define frontLimitPin 39  // front limit switch pin

TrayControl myTray(stepPin, dirPin, backLimitPin, frontLimitPin); // Instantiate a Tray object with the motor and limit switch GPIO as input

void setup() {
  Serial.begin(115200);
  myTray.resetBack(); // Reset tray
}

void loop() {
  if (Serial.available() > 0) {
    int target_pos = Serial.parseInt();                            // Read integer input from serial monitor
    Serial.print("Target position: "); Serial.println(target_pos); // Print out the input integer

    int current = myTray.move(target_pos);                        // Move tray
    Serial.print("Current position: "); Serial.println(current);
  }
}