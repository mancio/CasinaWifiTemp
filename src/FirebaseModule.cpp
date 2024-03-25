#include <Firebase_ESP_Client.h>
#include "FirebaseModule.h"
#include "Secrets.h"

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"


//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;


void initializeFirebase() {


    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Sign up */
    if (Firebase.signUp(&config, &auth, "", "")) {
        Serial.println("ok");
    } else {
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}


void sendDataToFirebase(const String& path, const float temperature, const float voltage, const unsigned long timestamp){

    const int maxRetries = 3; // Maximum number of retries
    int retryCount = 0; // Retry counter

    while (!Firebase.ready() && retryCount < maxRetries) {
        Serial.println("Waiting for Firebase to be ready...");
        delay(5000); // Wait for 5 seconds
        retryCount++;
    }

    if (Firebase.ready()) {
        if (Firebase.RTDB.setFloat(&fbdo, path + "/temp", temperature)) {
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
        } else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
        }

        if (Firebase.RTDB.setFloat(&fbdo, path + "/voltage", voltage)) {
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
        } else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
        }

        if (Firebase.RTDB.setDouble(&fbdo, path + "/time", static_cast<double>(timestamp))) {
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
        } else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
        }
    }
}




































//// Define Firebase Data object globally
//FirebaseData fbdo;
//FirebaseAuth auth;
//FirebaseConfig config;
//bool isFirebaseInitialized = false;
//
//void initializeFirebase() {
//    // Assign the API key and RTDB URL
//    config.api_key = API_KEY;
//    config.database_url = DATABASE_URL;
//
//    // Attempt anonymous sign up
//    if (Firebase.signUp(&config, &auth, "", "")) {
//        Serial.println("Anonymous sign-up successful.");
//    } else {
//        Serial.println("Failed to sign-up anonymously: " + String(config.signer.signupError.message.c_str()));
//    }
//
//    // Initialize Firebase with the configuration
//    Firebase.begin(&config, &auth);
//    Firebase.reconnectWiFi(true);
//
//    isFirebaseInitialized = true;
//}
//
//void sendDataToFirebase(const String& path, const float temperature, const float voltage, const unsigned long timestamp) {
//    const int maxRetries = 10; // Maximum number of retries
//    int retryCount = 0;
//    bool success = false;
//
//    while (!Firebase.ready() && retryCount < maxRetries) {
//        Serial.println("Firebase is not ready. Waiting...");
//        delay(1000); // Wait for 1 second before retrying
//        retryCount++;
//        Firebase.reconnectWiFi(); // Attempt to reconnect WiFi
//    }
//
//    if (Firebase.ready()) {
//        // Prepare the data to be sent
//        FirebaseJson json;
//        json.set("temperature", temperature);
//        json.set("voltage", voltage); // Add the voltage to the JSON payload
//        json.set("timestamp", timestamp); // No need to cast, as FirebaseJson handles types
//
//        // Construct the full path where the data will be stored
//        String fullPath = path + "/" + String(timestamp);
//
//        // Attempt to send the data to Firebase
//        success = Firebase.RTDB.setJSON(&fbdo, fullPath.c_str(), &json);
//        if (success) {
//            Serial.println("Data sent to Firebase successfully.");
//        } else {
//            Serial.println("Failed to send data to Firebase: " + String(fbdo.errorReason()));
//        }
//    } else {
//        Serial.println("Failed to send data to Firebase: Firebase not ready after retries.");
//    }
//}
//
//
