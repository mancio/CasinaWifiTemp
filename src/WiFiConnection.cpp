#include <ESP8266WiFi.h>
#include "WiFiConnection.h"
#include "Secrets.h"

bool connectToWiFi() {
    int attempts = 0;  // Initialize connection attempts counter
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED && attempts < 2) {  // Check connection status and attempt limit
        Serial.print('.');
        delay(2000);
        attempts++;  // Increment the counter after each attempt
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println(" connected");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println(" connection failed");
    }
    return false;
}
