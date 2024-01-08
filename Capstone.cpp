#include "Capstone.h"

TrayControl::TrayControl(int stepPin, int dirPin, int backlimit, int frontlimit)
  : stepPin(stepPin), dirPin(dirPin), backlimit(backlimit), frontlimit(frontlimit) {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(backlimit, INPUT);
  pinMode(frontlimit, INPUT);
}

int TrayControl::move(int target_pos, int spd) {
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

int TrayControl::resetFront(int spd) {
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

int TrayControl::resetBack(int spd) {
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
