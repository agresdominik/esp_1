#include "include/clock_display.h"

ClockDisplay::ClockDisplay(uint8_t clkPin, uint8_t dioPin, uint8_t brightness)
: _clk(clkPin), _dio(dioPin), _brightness(brightness), _display(clkPin, dioPin) {}

void ClockDisplay::begin() {
    _display.setBrightness(_brightness); // 0-7
    _display.clear();
}

void ClockDisplay::showTime(int hour24, int minute, bool colonOn) {
    uint8_t data[] = {
        _display.encodeDigit((hour24 / 10) % 10),
        _display.encodeDigit(hour24 % 10),
        _display.encodeDigit((minute / 10) % 10),
        _display.encodeDigit(minute % 10)
    };
    _display.setSegments(data);
    _display.showNumberDecEx( (hour24/10)*1000 + (hour24%10)*100 + (minute/10)*10 + (minute%10),
                              colonOn ? 0b01000000 : 0,
                              true, 4, 0);
}