#include "Capstone.h"

void Tray::begin()
{
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(BACK_LIMIT_PIN, INPUT);
  pinMode(FRONT_LIMIT_PIN, INPUT);
  pinMode(ENABLE_PIN, OUTPUT);

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
  digitalWrite(ENABLE_PIN, LOW);
  float K = STEPS_PER_REV / (3.1415 * GEAR_DIAMETER);
  bool dir;
  int delay = speedToDelay(spd);
  if (target_pos - current_pos != 0)
  {
    if (target_pos - current_pos > 0)
    {
      dir = true;
      digitalWrite(DIR_PIN, LOW);
    }
    else
    {
      dir = false;
      digitalWrite(DIR_PIN, HIGH);
    }
    for (int i = 0; i < K; i++)
    {
      bool front_pressed = digitalRead(FRONT_LIMIT_PIN);
      bool back_pressed = digitalRead(BACK_LIMIT_PIN);
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
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(delay);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(delay);
      }
    }
    if (!(digitalRead(FRONT_LIMIT_PIN) || digitalRead(BACK_LIMIT_PIN)))
      if (dir)
        current_pos++;
      else
        current_pos--;
  }
  return current_pos;
}

int Tray::resetFront(int spd)
{
  int delay = speedToDelay(spd);
  digitalWrite(DIR_PIN, LOW);

  while (!digitalRead(FRONT_LIMIT_PIN))
  {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delay);
  }

  current_pos = STROKE_LENGTH;
  return current_pos;
}

int Tray::resetBack(int spd)
{
  int delay = speedToDelay(spd);
  digitalWrite(DIR_PIN, HIGH);

  while (!digitalRead(BACK_LIMIT_PIN))
  {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delay);
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

int Tray::speedToDelay(int spd)
{
  if (spd > 100)
    spd = 100;
  else if (spd < 1)
    spd = 1;
  int delay = -450 * log10(spd) + 1000;
  return delay;
}

void Tray::disableTray()
{
  digitalWrite(ENABLE_PIN, HIGH);
}


