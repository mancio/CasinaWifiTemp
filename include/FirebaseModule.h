#ifndef FirebaseModule_h
#define FirebaseModule_h

#include <Arduino.h>

/**
 * @file FirebaseModule.h
 * @brief Module for initializing Firebase and sending data to Firebase database.
 *
 * This module provides functionality to connect to Firebase and send sensor data.
 * It is designed for use in Arduino projects that require interaction with Firebase
 * for data storage and retrieval.
 */

/**
 * @brief Initializes the connection to Firebase with predefined credentials.
 *
 * This function sets up the Firebase connection using the API key, database URL,
 * and authentication credentials specified in the implementation file. It should
 * be called at the beginning of the program to ensure Firebase services are
 * available for use in subsequent operations.
 */
void initializeFirebase();

/**
 * @brief Sends temperature data to a specified path in the Firebase database.
 *
 * This function uploads temperature data along with a timestamp to the Firebase
 * Realtime Database. The data is stored at the specified path, creating a new
 * entry for each set of temperature and timestamp values.
 *
 * @param path The database path where the data should be stored. This path should
 *             start from the root of the database and include any child nodes as
 *             necessary.
 * @param temperature The temperature value to be stored in the database.
 * @param timestamp The timestamp associated with the temperature reading. This
 *                  value should represent the number of seconds since the Unix
 *                  epoch (Jan 1, 1970).
 */
void sendDataToFirebase(const String& path, const float temperature, const unsigned long timestamp);

#endif

