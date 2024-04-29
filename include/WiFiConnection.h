/**
 * @file WiFiConnection.h
 * @brief Interface for WiFi network connection.
 *
 * This header file provides the declaration for the connectToWiFi function,
 * which is responsible for establishing a connection to a WiFi network using
 * predefined network credentials.
 */

#ifndef WiFiConnection_h
#define WiFiConnection_h

/**
 * @brief Connects the device to a WiFi network.
 *
 * Attempts to establish a connection to a WiFi network using the SSID and password
 * specified in the project's secrets file. This function attempts to connect up to
 * two times, with a delay of 2 seconds between attempts. The connection status is
 * printed to the Serial monitor. Execution will continue after two unsuccessful
 * attempts or upon successful connection.
 *
 * @return bool True if connected successfully, False if connection failed after
 * two attempts.
 */

bool connectToWiFi();

#endif // WiFiConnection_h

