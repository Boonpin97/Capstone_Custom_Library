/* 
 *  This example resets the Tray to the 0 position.
 * Open the Serial Monitor, change the settings to "No Line Ending"
 * Input the desired position for the tray to move to
 */


#include "Capstone.h"

// Pin Declaration
#define stepPin 33
#define dirPin 32
#define backLimitPin 36
#define frontLimitPin 39

int current_pos = 0;

TrayControl myTray(stepPin, dirPin, backLimitPin, frontLimitPin); // Instantiate a Tray object with the motor and limit switch GPIO as input

void setup() {
  Serial.begin(115200);
  current_pos = myTray.resetBack(); // Reset tray
}

void loop() {
  if (Serial.available() != 0) {
    int target_pos = Serial.parseInt();                            // Read integer input from serial monitor
    Serial.print("Target position: "); Serial.println(target_pos); // Print out the input integer
    
    current_pos = myTray.move(current_pos,target_pos);             // Move tray
  }
}