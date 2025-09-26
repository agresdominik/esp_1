#include "include/dht20.h"

DHT20Sensor::DHT20Sensor() {}

bool DHT20Sensor::begin() {
    if (!aht.begin()) {
        Serial.println("Failed to load DHT20 sensor.");
        return false;
    }
    Serial.println("Initialized the DHT20 sensor.");
    return true;
}

void DHT20Sensor::readAndPrint() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);

    Serial.print("Temp: ");
    Serial.print(temp.temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity.relative_humidity);
    Serial.println(" %");
}

void DHT20Sensor::read() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    _temperature = temp.temperature;
    _humidity = humidity.relative_humidity;
}

float DHT20Sensor::getTemperature() const {
    return _temperature;
}

float DHT20Sensor::getHumidity() const {
    return _humidity;
}
