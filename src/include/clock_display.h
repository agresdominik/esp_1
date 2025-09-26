#ifndef CLOCK_DISPLAY_H
#define CLOCK_DISPLAY_H

#include <Arduino.h>
#include <TM1637Display.h>

class ClockDisplay {
public:
    ClockDisplay(uint8_t clkPin, uint8_t dioPin, uint8_t brightness = 3);
    void begin();
    void showTime(int hour24, int minute, bool colonOn);

private:
    uint8_t _clk, _dio, _brightness;
    TM1637Display _display;
};

#endif