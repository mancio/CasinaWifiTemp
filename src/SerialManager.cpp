#include "SerialManager.h"

void initializeSerial(bool enableSerial, unsigned long baudRate) {
    if (enableSerial) {
        Serial.begin(baudRate);
        while (!Serial); // Wait for the serial port to connect. Necessary for some boards.
        Serial.println("Serial communication started.");
    }
}
