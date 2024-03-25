#include "DeepSleep.h"
#include <Esp.h>

unsigned long convertToMicroseconds(unsigned long number, const String& unit) {
    unsigned long microseconds;

    if (unit == "sec") {
        microseconds = number * 1000000UL; // 1 second = 1,000,000 microseconds
    } else if (unit == "min") {
        microseconds = number * 60000000UL; // 1 minute = 60,000,000 microseconds
    } else if (unit == "hour") {
        microseconds = number * 3600000000UL; // 1 hour = 3,600,000,000 microseconds
    } else {
        // If the unit is not recognized, return 0
        Serial.println("Unit not recognized. Please use 'sec', 'min', or 'hour'.");
        microseconds = 0;
    }

    return microseconds;
}

void goToDeepSleep() {
    EspClass::deepSleep(convertToMicroseconds(10, "sec")); // 1 hour
}

