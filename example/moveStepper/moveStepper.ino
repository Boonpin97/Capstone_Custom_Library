/*
   This example resets the Tray to the 0 position.
   Open the Serial Monitor, change the settings to "No Line Ending"
   Input the desired position for the tray to move to
*/

#include <Capstone.h>

Tray myTray; // Create an instance of Tray
int target_pos = 0;

void setup() {
  Serial.begin(115200);
  myTray.begin();      // Initialise GPIO pins etc
  myTray.resetBack(); // Reset tray
}

void loop() {
  if (Serial.available() > 0) {
    target_pos = Serial.parseInt();                                 // Read integer input from serial monitor
    Serial.print("Target position: "); Serial.println(target_pos); // Print out the target position of the tray
  }
  myTray.move(target_pos, 50);                                              // Move the tray to the target position
  Serial.print("Current position: "); Serial.println(myTray.current_pos);  // Print out the current position of the tray
}