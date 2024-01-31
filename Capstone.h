#ifndef Capstone_h
#define Capstone_h

#include "Arduino.h"
#include "Adafruit_VEML7700.h"

#define STEP_PIN 33
#define DIR_PIN 32
#define ENABLE_PIN 25
#define BACK_LIMIT_PIN 36
#define FRONT_LIMIT_PIN 39
#define SDA_PIN 21
#define SCL_PIN 22
#define GROWLIGHT_PIN 13
#define WIFILIGHT_PIN 19
#define RESET_PIN 0

class Tray
{
public:
    Tray(int stepPin = STEP_PIN, int dirPin = DIR_PIN, int backlimit = BACK_LIMIT_PIN, int frontlimit = FRONT_LIMIT_PIN);
    void begin();
    int move(int target_pos, int spd = DEFAULT_TRAY_SPEED);
    int resetFront(int spd = DEFAULT_TRAY_SPEED);
    int resetBack(int spd = DEFAULT_TRAY_SPEED);
    float *readLuxs();
    void disable();

    int current_pos = 0;

private:
    // Parameters
    static const int DEFAULT_TRAY_SPEED = 10;
    static constexpr float GEAR_DIAMETER = 19.15;
    static const int STEPS_PER_REV = 1600;
    static const int STROKE_LENGTH = 334;
    static const int MIN_DELAY = 100;
    static const int MAX_DELAY = 1100;
    static const int NUM_LIGHT_SENSOR = 6;
    static const int LIGHT_LOW_THRESHOLD = 10000;
    static const int LIGHT_HIGH_THRESHOLD = 20000;
    static const bool LIGHT_INTERRUPT_ENABLE = true;

    int stepPin;
    int dirPin;
    int backlimit;
    int frontlimit;

    Adafruit_VEML7700 light_sensor[NUM_LIGHT_SENSOR];

    void tcaselect(uint8_t i);
    int speedToDelay(int spd);
};
#endif
