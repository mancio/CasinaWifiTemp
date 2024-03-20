#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "secrets.h"

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
String databasePath;

void connectToWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
    Serial.println();
}

void waitForFirebaseUID() {
    Serial.println("Waiting for Firebase UID");
    while (auth.token.uid.empty()) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println("Firebase UID received");
}

void setupFirebase() {
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    Firebase.begin(&config, &auth);
    waitForFirebaseUID();
}

void setupTimeClient() {
    timeClient.begin();
}

unsigned long getCurrentTime() {
    timeClient.update();
    return timeClient.getEpochTime();
}

float getTemperature() {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
}

void sendDataToFirebase(unsigned long timestamp, float temperature) {
    if (!Firebase.ready()) return;

    databasePath = String("/UsersData/") + String(auth.token.uid.c_str()) + String("/readings");
    String parentPath = databasePath + "/" + String(timestamp);

    FirebaseJson json;
    json.set("/temperature", temperature);
    json.set("/timestamp", (int)timestamp); // Cast to int if necessary

    Serial.printf("Sending data... %s\n", Firebase.RTDB.setJSON(&firebaseData, parentPath.c_str(), &json) ? "Success" : firebaseData.errorReason().c_str());
}

void goToDeepSleep() {
    EspClass::deepSleep(3600e6); // 1 hour
}




void setup() {
    Serial.begin(9600);
    connectToWiFi();
    setupFirebase();
    setupTimeClient();
    sensors.begin();

    // Get current timestamp and temperature
    unsigned long timestamp = getCurrentTime();
    float temperature = getTemperature();

    // Prepare and send data to Firebase
    sendDataToFirebase(timestamp, temperature);

    // Deep sleep for 1 hour
    goToDeepSleep();
}

void loop() {
    // Empty - Execution does not reach here due to deep sleep
}

