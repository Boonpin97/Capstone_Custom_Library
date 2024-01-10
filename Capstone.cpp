#include "Capstone.h"

Tray::Tray(int stepPin, int dirPin, int backlimit, int frontlimit)
  : stepPin(stepPin), dirPin(dirPin), backlimit(backlimit), frontlimit(frontlimit) {
}

void Tray::begin() {
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(backlimit, INPUT);
  pinMode(frontlimit, INPUT);

  for (int i = 0; i < NUM_LIGHT_SENSOR; i++) {
    tcaselect(i);
    if (!light_sensor[i].begin()) {
      Serial.print("Light sensor ");
      Serial.print(i);
      Serial.println(" not found");
      Serial.println("WARNING: CODE MIGHT CRASH IF THE ERROR ABOVE IS IGNORED");
      delay(2000);
    }
    Serial.print("Light sensor ");
    Serial.print(i);
    Serial.println(" found!");
    light_sensor[i].setLowThreshold(10000);
    light_sensor[i].setHighThreshold(20000);
    light_sensor[i].interruptEnable(true);
  }
}

int Tray::move(int target_pos, int spd) {
  int diff_pos = (target_pos - current_pos) * STEPS_PER_REV / (3.1415 * GEAR_DIAMETER);
  bool dir;

  if (diff_pos != 0) {
    if (diff_pos > 0) {
      dir = true;
      digitalWrite(dirPin, HIGH);
    } else {
      dir = false;
      digitalWrite(dirPin, LOW);
    }

    current_pos = target_pos;

    for (int i = 0; i < abs(diff_pos); i++) {
      if ((digitalRead(frontlimit) || !dir) && (digitalRead(backlimit) || dir)) {
        if (digitalRead(frontlimit)) {
          current_pos = STROKE_LENGTH;
        } else if (digitalRead(backlimit)) {
          current_pos = 0;
        }
        break;
      } else {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(spd);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(spd);
      }
    }

    return current_pos;
  }
}

int Tray::resetFront(int spd) {
  digitalWrite(dirPin, HIGH);

  while (!digitalRead(frontlimit)) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(spd);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(spd);
  }

  current_pos = STROKE_LENGTH;
  return current_pos;
}

int Tray::resetBack(int spd) {
  digitalWrite(dirPin, LOW);

  while (!digitalRead(backlimit)) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(spd);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(spd);
  }

  current_pos = 0;
  return current_pos;
}

float* Tray::readLuxs() {
  static float light_array[NUM_LIGHT_SENSOR];
  for (int i = 0; i < NUM_LIGHT_SENSOR; i++) {
    tcaselect(i);
    light_array[i] = light_sensor[i].readLux();
  }
  return light_array;
} 

void Tray::tcaselect(uint8_t i) {
  if (i <= 7) {
    Wire.beginTransmission(0x71);
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(0x70);
    Wire.write(1 << i);
    Wire.endTransmission();
  }
  else if (i == 8) {
    Wire.beginTransmission(0x70);
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(0x71);
    Wire.write(1);
    Wire.endTransmission();
  }
  return;
} 

