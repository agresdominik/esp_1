#include <Arduino.h>
#include "include/dht20.h"
#include "include/mq2.h"
#include "include/wifi_connection.h"
#include "include/mqtt_client.h"
#include "include/clock_display.h"
#include "include/time_sync.h"
#include "secrets/secrets.h"


DHT20Sensor dht20;
MQ2Sensor mq2(D5);
WiFiConnection wifi(WIFI_SSID, WIFI_PASSWORD);
MQTTClientWrapper mqtt(MQTT_BROKER, 1883, MQTT_USER, MQTT_PASSWORD);
TimeSync timeSync;
ClockDisplay clockDisp(/*CLK=*/D6, /*DIO=*/D7, /*brightness=*/4);

unsigned long lastDHTPublish = 0;
const unsigned long dhtInterval = 60000;
unsigned long lastClockUpdate = 0;
bool colon = false;


void setup() {
    Serial.begin(9600);
    delay(100);

    if (!dht20.begin()) {
        Serial.println("Sensor init failed, check wiring!");
        while (1) delay(100);
    }
    mq2.begin();

    delay(1000);
    wifi.begin();
    mqtt.begin();

    timeSync.begin("CET-1CEST,M3.5.0,M10.5.0/3");
    clockDisp.begin();
}

void loop() {

    if (!wifi.isConnected()) {
      Serial.println("Lost WiFi, reconnecting...");
      wifi.begin();
    }

    mqtt.loop();
    unsigned long nowMs = millis();

    if (nowMs - lastDHTPublish >= dhtInterval) {
        dht20.read();
        mq2.read();
        float temp = dht20.getTemperature() - 0.3f;
        float hum  = dht20.getHumidity();
        bool gas = mq2.isGasDetected();
        mqtt.publishSensorData(temp, hum, gas);
        lastDHTPublish = nowMs;
    }

    if (nowMs - lastClockUpdate >= 1000) {
        lastClockUpdate = nowMs;
        colon = !colon;

        if (timeSync.isTimeSet()) {
            int h = timeSync.hour();
            int m = timeSync.minute();
            clockDisp.showTime(h, m, colon);
        } else {
            clockDisp.showTime(0, 0, colon);
        }
    }

    delay(50);
}

