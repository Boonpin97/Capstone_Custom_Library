#ifndef StepperTrayControl_h
#define StepperTrayControl_h

#include "Arduino.h"

class StepperTrayControl {
public:
    StepperTrayControl(int stepPin, int dirPin, int backlimit, int frontlimit);
    void initialize();
    void updatePosition();

    int moveTray(int target_pos, int spd);
    int resetTrayFront(int spd);
    int resetTrayBack(int spd);

private:
    int stepPin;
    int dirPin;
    int backlimit;
    int frontlimit;
    int current_pos;

    const int DELAY = 500;
    const float GEAR_DIAMETER = 19.15;
    const int STEPS_PER_REV = 1600;
    const int STROKE_LENGTH = 335;
};

#endif
