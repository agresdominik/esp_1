#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

class MQTTClientWrapper {
public:
    MQTTClientWrapper(const char* broker, uint16_t port, const char* user, const char* password);
    void begin();
    void loop();
    void publishSensorData(float temp, float humidity, bool gas);

private:
    const char* _broker;
    uint16_t _port;
    const char* _user;
    const char* _password;

    WiFiClient _wifiClient;
    PubSubClient _client;

    void reconnect();
};

#endif