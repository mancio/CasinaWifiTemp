## WiFi Thermometer Setup Guide

### Overview:

This WiFi Thermometer is designed to measure temperature data and upload it directly to Firebase, providing a seamless way to monitor temperature readings remotely. The device is built using the NodeMCU V3 board, leveraging its WiFi capabilities to connect and transmit data over the internet.


![box](https://github.com/mancio/CasinaWifiTemp/blob/71a789c17b30f7a4f402f0c2387b660cc454c00f/photos/circuit.PNG)


### Key Features:

- **Real-time Temperature Monitoring:** Continuously measures and uploads temperature data to a Firebase database.
- **Wireless Connectivity:** Utilizes the onboard WiFi module of the NodeMCU V3 board to connect to the internet.
- **Firebase Integration:** Configured to interface directly with Firebase, allowing data to be accessed in real time.
- **Energy Efficient:** Includes a deep sleep mode to save energy between data transmissions, making it ideal for long-term deployments.
- **Enhanced Power Management:** Features a 1F supercapacitor to maintain operation in low battery and low temperature conditions. The supercapacitor supports higher energy demand during wake periods while minimizing battery drain during deep sleep phases, ensuring only minimal milliampere-hours (mAh) are consumed.
- **Easy Configuration:** Users can set their WiFi and Firebase settings via a simple configuration file.

### Technical Specifications:

- **Board:** NodeMCU V3
- **Connectivity:** WiFi (ESP8266)
- **Power:** USB 5V or via battery with voltage monitoring, enhanced by a 1F supercapacitor for improved low-temperature performance and reduced energy consumption during wake cycles.
- **Additional Components:** Temperature sensor, voltage divider circuit for battery monitoring

### Setup:

1. Configure your WiFi and Firebase settings in the `Secrets.h` file.
2. Flash the firmware to the NodeMCU V3 board.
3. Place the device in the desired location for temperature monitoring.
4. Power the device using a USB connection or battery.
5. Monitor the temperature data remotely through your Firebase console.

## NOTE

Add a new file `Secrets.h` and copy the following data inside it:

```cpp
/**
 * @file secrets.h
 * @brief Configuration file for WiFi and Firebase credentials.
 *
 * This header file contains the definitions for WiFi credentials and Firebase
 * project settings. Replace each macro value with your actual WiFi network
 * credentials and Firebase project details.
 */

#ifndef CASINAWIFITEMP_SECRETS_H
#define CASINAWIFITEMP_SECRETS_H

/** 
 * @def WIFI_SSID
 * @brief WiFi network SSID.
 *
 * This macro defines the SSID of the WiFi network the device should connect to.
 * Replace "REPLACE_WITH_YOUR_SSID" with the actual SSID of your WiFi network.
 */
#define WIFI_SSID "REPLACE_WITH_YOUR_SSID"

/** 
 * @def WIFI_PASSWORD
 * @brief WiFi network password.
 *
 * This macro defines the password for the WiFi network defined by WIFI_SSID.
 * Replace "REPLACE_WITH_YOUR_PASSWORD" with the actual password of your WiFi network.
 */
#define WIFI_PASSWORD "REPLACE_WITH_YOUR_PASSWORD"

/** 
 * @def API_KEY
 * @brief Firebase project API key.
 *
 * This macro defines the API key of your Firebase project. This key is used to
 * authenticate your application with Firebase services. Replace
 * "REPLACE_WITH_YOUR_PROJECT_API_KEY" with the API key found in your Firebase
 * project settings.
 */
#define API_KEY "REPLACE_WITH_YOUR_PROJECT_API_KEY"

/** 
 * @def USER_EMAIL
 * @brief Authorized user email for Firebase authentication.
 *
 * This macro defines the email address of a user authorized to access the Firebase
 * database. Replace "REPLACE_WITH_THE_USER_EMAIL" with the email address of the
 * Firebase user.
 */
#define USER_EMAIL "REPLACE_WITH_THE_USER_EMAIL"

/** 
 * @def USER_PASSWORD
 * @brief Password for the authorized user email.
 *
 * This macro defines the password for the user email defined by USER_EMAIL.
 * Replace "REPLACE_WITH_THE_USER_PASSWORD" with the password of the Firebase user.
 */
#define USER_PASSWORD "REPLACE_WITH_THE_USER_PASSWORD"

/** 
 * @def DATABASE_URL
 * @brief Firebase Realtime Database URL.
 *
 * This macro defines the URL of the Firebase Realtime Database associated with
 * your project. Replace "REPLACE_WITH_YOUR_DATABASE_URL" with the database URL
 * found in your Firebase project settings.
 */
#define DATABASE_URL "REPLACE_WITH_YOUR_DATABASE_URL"

#endif // CASINAWIFITEMP_SECRETS_H
