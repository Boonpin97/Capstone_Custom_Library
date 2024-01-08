#include "Capstone.h"

StepperTrayControl::StepperTrayControl(int stepPin, int dirPin, int backlimit, int frontlimit)
  : stepPin(stepPin), dirPin(dirPin), backlimit(backlimit), frontlimit(frontlimit) {
}

void StepperTrayControl::initialize() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(backlimit, INPUT);
  pinMode(frontlimit, INPUT);

  Serial.begin(115200);
  delay(500);

  current_pos = resetTrayBack(500);
  delay(1000);
}

void StepperTrayControl::updatePosition() {
  if (Serial.available() != 0) {
    int target_pos = Serial.parseInt();
    Serial.print("Target position: "); Serial.println(target_pos);
    current_pos = moveTray(target_pos, 400);
  }
}

int StepperTrayControl::moveTray(int target_pos, int spd) {
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

    Serial.print("Current position: "); Serial.println(current_pos);
    return current_pos;
  }
}

int StepperTrayControl::resetTrayFront(int spd) {
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

int StepperTrayControl::resetTrayBack(int spd) {
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
