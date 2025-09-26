#include "include/mqtt_client.h"

MQTTClientWrapper::MQTTClientWrapper(const char* broker, uint16_t port, const char* user, const char* password)
: _broker(broker), _port(port), _user(user), _password(password), _client(_wifiClient) {}

void MQTTClientWrapper::begin() {
    _client.setServer(_broker, _port);
}

void MQTTClientWrapper::loop() {
    if (!_client.connected()) {
        reconnect();
    }
    _client.loop();
}

void MQTTClientWrapper::publishSensorData(float temp, float humidity, bool gas) {
    if (_client.connected()) {
        _client.publish("home/esp8266-1/temp", String(temp, 1).c_str());
        _client.publish("home/esp8266-1/humidity", String(humidity, 1).c_str());
        _client.publish("home/esp8266-1/gas", gas ? "1" : "0");
    }
}

void MQTTClientWrapper::reconnect() {
    while (!_client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (_client.connect("ESP8266Client", _user, _password)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(_client.state());
            Serial.println(" try again in 5s");
            delay(5000);
        }
    }
}