/*
   This example prints the temperature and humidity data of two DHT11 sensors
*/

#include <Capstone.h>

Tray myTray; // Create an instance of Tray

void setup() {
  Serial.begin(115200);
  myTray.begin();      // Initialise GPIO pins etc
}

void loop() {
  // Print the temperature and humidity data of two DHT11 sensors
  Serial.print("Front Temperature:"); Serial.print(myTray.readTempFront());
  Serial.print("  Back Temperature:"); Serial.print(myTray.readTempBack());
  Serial.print("  Front Humidity:"); Serial.print(myTray.readHumiFront());
  Serial.print("  Back Humidty:"); Serial.println(myTray.readHumiBack());
}