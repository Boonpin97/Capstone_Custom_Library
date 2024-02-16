/*
   This example changed the status lights in the following sequence:
    1. Magenta 
    2. Cyan
    3. Yellow
*/

#include <Capstone.h>

Tray myTray; // Create an instance of Tray

void setup() {
  Serial.begin(115200);
  myTray.begin();      // Initialise GPIO pins etc
  delay(1000);
}

void loop() {
  myTray.setStatusLight(255, 0, 255); // Magenta
  delay(1000);
  myTray.setStatusLight(0, 255, 255); // Cyan
  delay(1000);
  myTray.setStatusLight(255, 255, 0); // Yellow
  delay(1000);
}
