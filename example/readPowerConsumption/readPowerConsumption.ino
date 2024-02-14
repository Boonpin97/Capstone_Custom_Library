/*
    This example reads the current and power consumption 
    of the tray and prints it to the serial monitor
*/

#include <Capstone.h>

Tray myTray; // Create an instance of Tray

void setup() {
  Serial.begin(115200);
  myTray.begin();   // Initialise GPIO pins etc
}

void loop() {
  myTray.updatePower();         // Read the current sensor and update the power consumption
  Serial.print("Current:");     // Print the current and power consumption to the serial monitor
  Serial.print(myTray.current_consumption);
  Serial.print("A Power:");
  Serial.print(myTray.power_consumption);
  Serial.println("Wh");
}
