/*
   This example uses a state machine:
   State 1: Resets the Tray to the 0 position
   State 2: Check for Serial Monitor input
   State 3: Moves the Tray to the target position
*/

#include <Capstone.h>

Tray myTray; // Create an instance of Tray
int target_pos = 0;
int state = 0;

void setup() {
  Serial.begin(115200);
  myTray.begin();      // Initialise GPIO pins etc
  myTray.resetBack(); // Reset tray
}

void loop() {
  Serial.print("State: ");
  Serial.println(state);
  if (state == 1) { // State 0: Reset the tray to the 0 position
    if (myTray.resetBack() == true) {
      state++;
    }
  }
  else if (state == 2) {  // State 1: Check for Serial Monitor input
    if (Serial.available() > 0) {
      target_pos = Serial.parseInt();                                 // Read integer input from serial monitor
      Serial.print("Target position: "); Serial.println(target_pos); // Print out the target position of the tray
      state++;
    }
  }
  else if (state == 3) {  // State 2: Move the tray to the target position
    if (myTray.move(target_pos, 50) == true) {                                             // Move the tray to the target position
      state = 1;
    }
    Serial.print("Current position: "); Serial.println(myTray.current_pos);  // Print out the current position of the tray
  }
}

