#include <Arduino.h>
#include "WiFiConnection.h"
#include "FirebaseModule.h"
#include "TimeClient.h"
#include "SensorManagement.h"
#include "DeepSleep.h"

void setup() {
    Serial.begin(9600);
    connectToWiFi();
    initializeFirebase(); // Corrected from setupFirebase() to initializeFirebase()
    setupTimeClient();
    beginSensors();

    unsigned long timestamp = getCurrentTime();
    float temperature = getTemperature();

    // Define the path where the data should be sent
    String databasePath = "/sensorData";

    // Adjusted to include the database path as per the new signature
    sendDataToFirebase(databasePath, temperature, timestamp);

    goToDeepSleep();
}

void loop() {
    // Empty - Execution does not reach here due to deep sleep
}
