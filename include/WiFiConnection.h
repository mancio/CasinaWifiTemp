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
 * Initiates a connection to a WiFi network using the SSID and password specified
 * in the project's secrets file. This function will block execution until a connection
 * is established or the connection attempt fails. It prints the connection status
 * to the Serial monitor.
 */
void connectToWiFi();

#endif // WiFiConnection_h

