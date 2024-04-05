#include "Capstone.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel growLight(NUM_LED * 4, GROWLIGHT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel statusLight(1, STATUSLIGHT_PIN, NEO_GRB + NEO_KHZ800);

void Tray::begin()
{
  Wire.begin(SDA_PIN, SCL_PIN);
  // Wire.setClock(10000);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(BACK_LIMIT_PIN, INPUT);
  pinMode(FRONT_LIMIT_PIN, INPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(ESTOP_PIN, INPUT);
  pinMode(CURRENT_SENSOR_PIN, INPUT);

  growLight.begin();                             // Initialize the NeoPixel library.
  growLight.show();                              // Initialize all pixels to 'off'
  growLight.setBrightness(DEFAULT_BRIGHTNESS);   // set the brightness of the lights
  statusLight.begin();                           // Initialize the NeoPixel library.
  statusLight.show();                            // Initialize all pixels to 'off'
  statusLight.setBrightness(DEFAULT_BRIGHTNESS); // set the brightness of the lights

  for (int i = 0; i < NUM_LIGHT_SENSOR; i++) // loop to initialize the light sensors
  {
    tcaselect(i);
    delay(100);
    if (!light_sensor[i].begin())
    {
      Serial.print("Light sensor ");
      Serial.print(i);
      Serial.println(" not found");
      Serial.println("WARNING: CODE MIGHT CRASH IF THE ERROR ABOVE IS IGNORED");
      // delay(2000);
    }
    else
    {
      Serial.print("Light sensor ");
      Serial.print(i);
      Serial.println(" found!");
      light_sensor[i].setLowThreshold(10000);
      light_sensor[i].setHighThreshold(20000);
      light_sensor[i].interruptEnable(true);
    }
  }
  timer = millis(); // record last time the power was updated
}
float *Tray::readLuxs()
{
  static float light_array[NUM_LIGHT_SENSOR]; // array to store the light readings
  for (int i = 0; i < NUM_LIGHT_SENSOR; i++)  // loop to read the light sensors
  {
    tcaselect(i); // select the i2c multiplexer channel
    int loop_count = 0;
    do
    {
      light_array[i] = light_sensor[i].readLux(VEML_LUX_NORMAL_NOWAIT); // read the light sensor
      loop_count++;
    } while (light_array[i] < 0 && loop_count < NUM_READINGS_LIGHT); // loop to read the light sensor if the reading is negative
    if (light_array[i] < 0)
    {
      light_array[i] = -1;
    }
  }
  return light_array; // return the light readings
}

bool Tray::move(int target_pos, int spd)
{
  digitalWrite(ENABLE_PIN, LOW);     // enable the tray
  bool dir;                          // variable to store the direction of the tray
  int delay = speedToDelay(spd);     // convert the speed to delay
  if (target_pos - current_pos != 0) // check if the target position is different from the current position
  {
    if (target_pos - current_pos > 0) // check if the target position is greater than the current position
    {
      dir = true;
      digitalWrite(DIR_PIN, LOW); // set the direction to move the tray
    }
    else
    {
      dir = false;
      digitalWrite(DIR_PIN, HIGH); // set the direction to move the tray
    }
    for (int i = 0; i < STEPS_PER_MM; i++) // loop to move the tray
    {
      bool front_pressed = digitalRead(FRONT_LIMIT_PIN);
      bool back_pressed = digitalRead(BACK_LIMIT_PIN);
      if ((front_pressed || !dir) && (back_pressed || dir)) // check if the front or back limit switch is pressed
      {
        if (front_pressed)
        {
          current_pos = STROKE_LENGTH; // set the current position to the front limit switch
        }
        else if (back_pressed)
        {
          current_pos = 0; // set the current position to the back limit switch
        }
        return true;
      }
      else
      {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(delay + 100 * sin(2 * PI * i / STEPS_PER_MM));  //move the tray
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(delay + 100 * sin(2 * PI * i / STEPS_PER_MM));
      }
    }
    if (!(digitalRead(FRONT_LIMIT_PIN) || digitalRead(BACK_LIMIT_PIN))) // check if the front or back limit switch is pressed
      if (dir)
        current_pos++;
      else
        current_pos--;
    return false;
  }
  else
  {
    return true;
  }
}

bool Tray::resetFront(int spd)
{
  int delay = speedToDelay(spd);     // convert the speed to delay
  digitalWrite(ENABLE_PIN, LOW);     // enable the tray
  digitalWrite(DIR_PIN, LOW);        // set the direction to move the tray
  if (!digitalRead(FRONT_LIMIT_PIN)) // check if the front limit switch is pressed
  {
    for (int i = 0; i < STEPS_PER_MM; i++) // loop to move the tray
    {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(delay + 100 * sin(2 * PI * i / STEPS_PER_MM));  //move the tray
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(delay + 100 * sin(2 * PI * i / STEPS_PER_MM));
    }
    current_pos++;
    return false;
  }
  else
  {
    current_pos = STROKE_LENGTH;
    return true;
  }
}

bool Tray::resetBack(int spd)
{
  int delay = speedToDelay(spd);    // convert the speed to delay
  digitalWrite(ENABLE_PIN, LOW);    // enable the tray
  digitalWrite(DIR_PIN, HIGH);      // set the direction to move the tray
  if (!digitalRead(BACK_LIMIT_PIN)) // check if the front limit switch is pressed
  {
    for (int i = 0; i < STEPS_PER_MM; i++) // loop to move the tray
    {
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(delay + 100 * sin(2 * PI * i / STEPS_PER_MM));
      digitalWrite(STEP_PIN, LOW);
      delayMicroseconds(delay + 100 * sin(2 * PI * i / STEPS_PER_MM));
    }
    current_pos--;
    return false;
  }
  else
  {
    current_pos = 0;
    return true;
  }
}

void Tray::tcaselect(uint8_t i)
{
  if (i <= 7) // select the i2c multiplexer channel
  {
    Wire.beginTransmission(0x71);
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(0x70);
    Wire.write(1 << i);
    Wire.endTransmission();
  }
  else if (i == 8)
  {
    Wire.beginTransmission(0x70);
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(0x71);
    Wire.write(1);
    Wire.endTransmission();
  }
  return;
}

int Tray::speedToDelay(int spd)
{
  if (spd > 100) // limit the speed from 1 to 100
    spd = 100;
  else if (spd < 1)
    spd = 1;
  int delay = -450 * log10(spd) + 1000; // convert the speed to delay
  return delay;
}

void Tray::disableTray()
{
  digitalWrite(ENABLE_PIN, HIGH);
}

float Tray::readTempBack()
{
  frontDHT11.read(BACK_DHT_PIN);
  return frontDHT11.temperature;
}

float Tray::readTempFront()
{
  backDHT11.read(FRONT_DHT_PIN);
  return backDHT11.temperature;
}

float Tray::readHumiBack()
{
  frontDHT11.read(BACK_DHT_PIN);
  return frontDHT11.humidity;
}

float Tray::readHumiFront()
{
  backDHT11.read(FRONT_DHT_PIN);
  return backDHT11.humidity;
}

bool Tray::eStopPressed()
{
  return digitalRead(ESTOP_PIN); // read the input on digital pin 27:
}

// bool Tray::resetPressed()
// {
//   return digitalRead(RESET_PIN); // read the input on digital pin 0:
// }

void Tray::setRedWhiteLight(int strip_index, int brightness)
{
  growLight.setBrightness(brightness);
  for (int i = strip_index * NUM_LED; i < (strip_index + 1) * NUM_LED; i++) // loop to set the color of the lights
  {
    if (i % 4 == 0)
      growLight.setPixelColor(i, growLight.Color(255, 0, 0)); // Red
    else
      growLight.setPixelColor(i, growLight.Color(255, 255, 255)); // White
  }
  growLight.show(); // show the color of the lights
}

void Tray::setColor(int strip_index, int r, int g, int b, int brightness)
{
  growLight.setBrightness(brightness);                                      // set the brightness of the lights
  for (int i = strip_index * NUM_LED; i < (strip_index + 1) * NUM_LED; i++) // loop to set the color of the lights
  {
    growLight.setPixelColor(i, growLight.Color(r, b, g)); // set the color of the lights
  }
  growLight.show(); // show the color of the lights
}

void Tray::offLight(int strip_index)
{
  for (int i = strip_index * NUM_LED; i < (strip_index + 1) * NUM_LED; i++) // loop to turn off the lights
  {
    growLight.setPixelColor(i, growLight.Color(0, 0, 0)); //  off the lights
  }
  growLight.show(); // show the lights are off
}

void Tray::updatePower()
{
  int sumReading = analogRead(CURRENT_SENSOR_PIN);   // read the input on analog pin 0:
  for (int i = 0; i < NUM_READINGS_CURRENT - 1; i++) // loop to take the average of the readings
  {
    sumReading += analogRead(CURRENT_SENSOR_PIN);
  }
  current_consumption = (0.0007 * sumReading / NUM_READINGS_CURRENT) + 0.174;         // convert the analog reading (which goes from 0 - 4096) to a voltage level
  power_consumption += (current_consumption * 24.0 * (millis() - timer) / 3600000.0); // calculate the power consumption in Wh
  timer = millis();                                                                   // record last time the power was updated
  return;
}

void Tray::setStatusLight(int r, int g, int b, int brightness)
{
  statusLight.setBrightness(brightness);
  statusLight.setPixelColor(0, statusLight.Color(r, g, b));
  statusLight.show(); // show the color of the lights
}
