#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WiFiConnection {
public:
    WiFiConnection(const char* ssid, const char* password);
    void begin();
    bool isConnected();
    void printIP();

private:
    const char* _ssid;
    const char* _password;
};

#endif