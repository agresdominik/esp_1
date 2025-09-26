#include "include/mq2.h"

MQ2Sensor::MQ2Sensor(uint8_t digitalPin) : _digitalPin(digitalPin) {}

void MQ2Sensor::begin() {
    pinMode(_digitalPin, INPUT);
    Serial.println("Initialized the MQ-2 sensor.");
}

void MQ2Sensor::read() {
    int state = digitalRead(_digitalPin);
    _gasDetected = (state == LOW);
}

bool MQ2Sensor::isGasDetected() const {
    return _gasDetected;
}

void MQ2Sensor::printStatus() {
    if (isGasDetected()) {
        Serial.println("Gas/Smoke detected!");
    } else {
        Serial.println("Clean");
    }
}
