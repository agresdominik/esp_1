#include "include/wifi_connection.h"

WiFiConnection::WiFiConnection(const char* ssid, const char* password)
: _ssid(ssid), _password(password) {}

void WiFiConnection::begin() {
    Serial.print("Connecting to WiFi: ");
    Serial.println(_ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);

    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
        delay(500);
        Serial.print(".");
        retries++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        printIP();
    } else {
        Serial.println("\nFailed to connect to WiFi.");
    }
}

bool WiFiConnection::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiConnection::printIP() {
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
