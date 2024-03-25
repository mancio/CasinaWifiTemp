#include <Arduino.h>
#include "WiFiConnection.h"
#include "FirebaseModule.h"
#include "TimeClient.h"
#include "SensorManagement.h"
#include "DeepSleep.h"
#include "SerialManager.h"

void setup() {
    initializeSerial(true, 9600);
    connectToWiFi();
    initializeFirebase();
    setupTimeClient();
    beginSensors();

    unsigned long timestamp = getCurrentTime();
    Serial.println("Current Unix Timestamp: " + String(timestamp));

    float temperature = getTemperature();
    Serial.println("Temperature is: " + String(temperature) + " °C");

    // Read and print the battery voltage
    float batteryVoltage = getBatteryVoltage();
    Serial.println("Battery Voltage: " + String(batteryVoltage, 2) + " V");

    // Define the path where the data should be sent
    String databasePath = "/Casina";

    // Adjusted to include the database path as per the new signature
    sendDataToFirebase(databasePath, temperature, batteryVoltage, timestamp);

    goToDeepSleep();
}

void loop() {
    // Empty - Execution does not reach here due to deep sleep
}
