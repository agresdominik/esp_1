#ifndef DHT20_SENSOR_H
#define DHT20_SENSOR_H

#include <Arduino.h>
#include <Adafruit_AHTX0.h>

class DHT20Sensor {
public:
    DHT20Sensor();
    bool begin();
    void readAndPrint();
    void read();
    float getTemperature() const;
    float getHumidity() const;

private:
    Adafruit_AHTX0 aht;
    float _temperature;
    float _humidity;
};

#endif