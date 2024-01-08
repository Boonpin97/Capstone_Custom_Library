#ifndef Capstone_h
#define Capstone_h

#include "Arduino.h"

#define DEFAULT_TRAY_SPEED 500

class TrayControl {
public:
    TrayControl(int stepPin, int dirPin, int backlimit, int frontlimit);
    int move(int current_pos, int target_pos, int spd = DEFAULT_TRAY_SPEED);
    int resetFront(int spd = DEFAULT_TRAY_SPEED);
    int resetBack(int spd = DEFAULT_TRAY_SPEED);

private:
    int stepPin;
    int dirPin;
    int backlimit;
    int frontlimit;
    int current_pos;

    const float GEAR_DIAMETER = 19.15;
    const int STEPS_PER_REV = 1600;
    const int STROKE_LENGTH = 335;
};

#endif
