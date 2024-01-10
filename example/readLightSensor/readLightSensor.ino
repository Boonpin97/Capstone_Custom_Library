/*
   This example reads the light sensor values
*/

#include <Capstone.h>

Tray myTray; // Create an instance of Tray

void setup() {
  Serial.begin(115200);
  myTray.begin();
}

void loop() {
  // Store light readings into a pointer
  float* luxValues = myTray.readLuxs();

  // Iterate through the array the pointer is pointing to and print the light readings
  for (int i = 0; i < 9; i++) {
    Serial.print("Sensor "); Serial.print(i); Serial.print(": ");
    Serial.println(luxValues[i]); 
    }
  delay(1000);
}