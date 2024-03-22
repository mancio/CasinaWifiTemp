#include <Firebase_ESP_Client.h>
#include "FirebaseModule.h"
#include "Secrets.h" // Contains Firebase and WiFi credentials

// Firebase Data object for sending and receiving data with Firebase
FirebaseData firebaseData;

// Firebase authentication and configuration
FirebaseAuth auth;
FirebaseConfig config;

void initializeFirebase() {
    // Assign the project host and api key (required)
    config.database_url = DATABASE_URL; // e.g., "https://your-project-id.firebaseio.com/"
    config.api_key = API_KEY; // Firebase API key

    // Assign the user sign in credentials
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    // Initialize the Firebase library
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("Initialized Firebase connection.");
}

void sendDataToFirebase(const String& path, const float temperature, const unsigned long timestamp) {
    if (!Firebase.ready()) {
        Serial.println("Firebase is not ready. Reinitializing...");
        initializeFirebase();
    }

    // Construct the full path where the data will be stored
    String fullPath = path + "/" + String(timestamp);

    // Prepare the data to be sent
    FirebaseJson json;
    json.set("temperature", temperature);
    json.set("timestamp", (int)timestamp); // Cast timestamp to int to avoid issues with large numbers

    // Send the data to Firebase
    if (Firebase.RTDB.setJSON(&firebaseData, fullPath.c_str(), &json)) {
        Serial.println("Data sent to Firebase successfully.");
    } else {
        Serial.println("Failed to send data to Firebase.");
        Serial.println(firebaseData.errorReason());
    }
}
