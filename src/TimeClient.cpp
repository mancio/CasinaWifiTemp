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
    if (!timeClient.update()) {
        Serial.println("Failed to update time from NTP server");
        timeClient.forceUpdate();
    }
    return timeClient.getEpochTime();
}


