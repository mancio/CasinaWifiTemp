## NOTE

add a new file ``Secrets.h`` and copy the following data inside it

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
```
