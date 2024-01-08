#include "Capstone.h"

// Pin Declaration
#define stepPin 33
#define dirPin 32
#define backlimit 36
#define frontlimit 39

StepperTrayControl myTrayControl(stepPin, dirPin, backlimit, frontlimit);

void setup() {
  myTrayControl.initialize();
}

void loop() {
  myTrayControl.updatePosition();
}
