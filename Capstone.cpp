#include "Capstone.h"

Tray::Tray(int stepPin, int dirPin, int backlimit, int frontlimit)
    : stepPin(stepPin), dirPin(dirPin), backlimit(backlimit), frontlimit(frontlimit)
{
}

void Tray::begin()
{
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(backlimit, INPUT);
  pinMode(frontlimit, INPUT);

  for (int i = 0; i < NUM_LIGHT_SENSOR; i++)
  {
    tcaselect(i);
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
}

int Tray::move(int target_pos, int spd)
{
  float K = STEPS_PER_REV / (3.1415 * GEAR_DIAMETER);
  bool dir;
  if (target_pos - current_pos != 0)
  {
    if (target_pos - current_pos > 0)
    {
      dir = true;
      digitalWrite(dirPin, LOW);
    }
    else
    {
      dir = false;
      digitalWrite(dirPin, HIGH);
    }
    for (int i = 0; i < K; i++)
    {
      bool front_pressed = digitalRead(frontlimit);
      bool back_pressed = digitalRead(backlimit);
      if ((front_pressed || !dir) && (back_pressed || dir))
      {
        if (front_pressed)
        {
          current_pos = STROKE_LENGTH;
        }
        else if (back_pressed)
        {
          current_pos = 0;
        }
        break;
      }
      else
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(spd);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(spd);
      }
    }
    if (!(digitalRead(frontlimit) || digitalRead(backlimit)))
      current_pos++;
  }
  return current_pos;
}

int Tray::resetFront(int spd)
{
  digitalWrite(dirPin, LOW);

  while (!digitalRead(frontlimit))
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(spd);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(spd);
  }

  current_pos = STROKE_LENGTH;
  return current_pos;
}

int Tray::resetBack(int spd)
{
  digitalWrite(dirPin, HIGH);

  while (!digitalRead(backlimit))
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(spd);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(spd);
  }

  current_pos = 0;
  return current_pos;
}

float *Tray::readLuxs()
{
  static float light_array[NUM_LIGHT_SENSOR];
  for (int i = 0; i < NUM_LIGHT_SENSOR; i++)
  {
    tcaselect(i);
    light_array[i] = light_sensor[i].readLux();
  }
  return light_array;
}

void Tray::tcaselect(uint8_t i)
{
  if (i <= 7)
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
