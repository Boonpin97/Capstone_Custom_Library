/*
   This example turn the different grow lights in the following sequence:
    1st strip: Purple light, all other lights off
    2nd strip: Red and white light, all other lights off
    3rd strip: Red and white light, all other lights off
    4th strip: Red and white light, all other lights off
*/

#include <Capstone.h> 

Tray myTray; // Create an instance of Tray

void setup() {
  Serial.begin(115200); 
  myTray.begin();      // Initialise GPIO pins etc
  delay(1000);
}

void loop() {
  myTray.setColor(0,255,0,255); // Purple
  myTray.offLight(1);           // Turn off all other lights
  myTray.offLight(2);
  myTray.offLight(3);
  delay(1000);
  myTray.setRedWhiteLight(1); // Red and white
  myTray.offLight(0);         // Turn off all other lights
  myTray.offLight(2);       
  myTray.offLight(3);
  delay(1000);
  myTray.setRedWhiteLight(2); // Red and white
  myTray.offLight(1);         // Turn off all other lights
  myTray.offLight(0);
  myTray.offLight(3);
  delay(1000);
  myTray.setRedWhiteLight(3); // Red and white
  myTray.offLight(1);         // Turn off all other lights
  myTray.offLight(2);
  myTray.offLight(0);
  delay(1000);
}