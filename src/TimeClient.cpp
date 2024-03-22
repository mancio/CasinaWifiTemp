#include <NTPClient.h>
#include <WiFiUdp.h>
#include "TimeClient.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setupTimeClient() {
    timeClient.begin();
}

unsigned long getCurrentTime() {
    timeClient.update();
    return timeClient.getEpochTime();
}

