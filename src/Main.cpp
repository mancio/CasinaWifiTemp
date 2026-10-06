#include <Arduino.h>
#include "WiFiConnection.h"
#include "FirebaseModule.h"
#include "TimeClient.h"
#include "SensorManagement.h"
#include "DeepSleep.h"
#include "SerialManager.h"

void setup() {
    initializeSerial(false, 9600);

    // Measure the pack at rest, before the radio draws its current peaks.
    float batteryVoltage = getBatteryVoltage();
    Serial.println("Battery Voltage: " + String(batteryVoltage, 2) + " V");

    bool onBattery = batteryVoltage >= BATTERY_ABSENT_V;
    bool batteryLow = onBattery && batteryVoltage < BATTERY_CUTOFF_V;
    if (batteryLow) {
        Serial.println("Battery below cutoff: last upload, then sleeping until reset");
    }

    bool wifi = connectToWiFi();
    if (wifi) {
        initializeFirebase();
        setupTimeClient();
        beginSensors();

        unsigned long timestamp = getCurrentTime();
        Serial.println("Current Unix Timestamp: " + String(timestamp));

        float temperature = getTemperature();
        Serial.println("Temperature is: " + String(temperature) + " °C");

        // Define the path where the data should be sent
        String databasePath = "/Casina";

        // The final low-battery reading still goes out, so the drop is visible in Firebase.
        sendDataToFirebase(databasePath, temperature, batteryVoltage, timestamp);
    }

    if (batteryLow) {
        goToDeepSleepForever();
    }
    goToDeepSleep();
}

void loop() {
    // Empty - Execution does not reach here due to deep sleep
}
