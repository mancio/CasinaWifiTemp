#include "DeepSleep.h"
#include <Esp.h>



// Define constants for time units
const String SECOND = "sec";
const String MINUTE = "min";
const String HOUR = "hour";

unsigned long convertToMicroseconds(unsigned long number, const String& unit) {
    unsigned long microseconds;

    if (unit == SECOND) {
        microseconds = number * 1000000UL; // 1 second = 1,000,000 microseconds
    } else if (unit == MINUTE) {
        microseconds = number * 60000000UL; // 1 minute = 60,000,000 microseconds
    } else if (unit == HOUR) {
        microseconds = number * 3600000000UL; // 1 hour = 3,600,000,000 microseconds
    } else {
        // If the unit is not recognized, return 0
        Serial.println("Unit not recognized. Please use 'sec', 'min', or 'hour'.");
        microseconds = 0;
    }

    return microseconds;
}

void goToDeepSleep() {
    // Use constants for time units
    EspClass::deepSleep(convertToMicroseconds(30, MINUTE));
}


