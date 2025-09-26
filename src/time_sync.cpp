#include "include/time_sync.h"

void TimeSync::begin(const char* tzString) {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov", "time.google.com");
    setenv("TZ", tzString, 1);
    tzset();
    for (int i = 0; i < 50; i++) {
        time_t t = time(nullptr);
        if (t > 1600000000) {
            _timeSet = true;
            break;
        }
        delay(100);
    }
}

bool TimeSync::isTimeSet() const {
    time_t t = time(nullptr);
    return (t > 1600000000);
}

void TimeSync::update() {
    
}

void TimeSync::refreshLocalTM() const {
    time_t t = time(nullptr);
    localtime_r(&t, &_tmCache);
}

int TimeSync::hour() const {
    refreshLocalTM();
    return _tmCache.tm_hour;
}

int TimeSync::minute() const {
    refreshLocalTM();
    return _tmCache.tm_min;
}

time_t TimeSync::now() const {
    return time(nullptr);
}