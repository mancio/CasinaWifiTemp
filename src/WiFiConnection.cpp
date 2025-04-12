#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "Secrets.h"

ESP8266WiFiMulti wifiMulti;

bool connectToWiFi() {
    // Add both WiFi networks to WiFiMulti
    wifiMulti.addAP(WIFI_SSID_1, WIFI_PASSWORD_1);
    wifiMulti.addAP(WIFI_SSID_2, WIFI_PASSWORD_2);

    Serial.println("Connecting to WiFi...");
    unsigned long startTime = millis();
    unsigned long timeout = 10000; // 10 seconds timeout

    // Attempt to connect within the timeout period
    while (wifiMulti.run() != WL_CONNECTED && millis() - startTime < timeout) {
        Serial.print(".");
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to WiFi");
        Serial.println("IP Address: " + WiFi.localIP().toString());
        return true;
    } else {
        Serial.println("\nFailed to connect to WiFi");
        return false;
    }
}