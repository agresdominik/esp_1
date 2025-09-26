#ifndef TIME_SYNC_H
#define TIME_SYNC_H

#include <Arduino.h>
#include <time.h>

class TimeSync {
public:
    // tzExample: "CET-1CEST,M3.5.0,M10.5.0/3" for Europe/Berlin
    void begin(const char* tzString = "CET-1CEST,M3.5.0,M10.5.0/3");
    bool isTimeSet() const;
    void update();
    int hour() const;
    int minute() const;
    time_t now() const;

private:
    bool _timeSet = false;
    mutable tm _tmCache{};
    void refreshLocalTM() const;
};

#endif