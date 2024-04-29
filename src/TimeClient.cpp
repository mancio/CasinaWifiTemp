#include <NTPClient.h>
#include <WiFiUdp.h>
#include "TimeClient.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setupTimeClient() {
    timeClient.begin();
    Serial.println("NTP client started");
}

unsigned long getCurrentTime() {
    int retries = 0;
    const int maxRetries = 2;

    while (!timeClient.update() && retries < maxRetries) {
        Serial.println("Failed to update time from NTP server, retrying...");
        delay(2000); // Wait for 2 seconds before retrying
        timeClient.forceUpdate();
        retries++;
    }

    if (retries == maxRetries) {
        Serial.println("Failed to update time after maximum retries");
        // Handle the failure to obtain time after retries, if needed
    }

    return timeClient.getEpochTime();
}


