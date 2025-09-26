#ifndef MQ2_SENSOR_H
#define MQ2_SENSOR_H

#include <Arduino.h>

class MQ2Sensor {
public:
    MQ2Sensor(uint8_t digitalPin);
    void begin();
    void read();
    bool isGasDetected() const;
    void printStatus();

private:
    uint8_t _digitalPin;
    bool _gasDetected;
};

#endif
