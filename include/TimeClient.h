/**
 * @file TimeClient.h
 * @brief Interface for time retrieval and NTP client setup.
 *
 * This header file provides functions for setting up a time client and retrieving
 * the current time. It is designed to abstract the complexity of time synchronization
 * over the network and provide a simple interface for obtaining the current time.
 */

#ifndef TimeClient_h
#define TimeClient_h

/**
 * @brief Initializes the network time protocol (NTP) client.
 *
 * Sets up the NTP client with default server and timezone configurations. This function
 * should be called at the beginning of the program to ensure accurate time is available
 * for time-stamp or scheduling purposes. It configures the NTP client to synchronize
 * the device's time with a remote NTP server.
 */
void setupTimeClient();

/**
 * @brief Retrieves the current UNIX timestamp.
 *
 * Obtains the current time as a UNIX timestamp (the number of seconds that have elapsed
 * since January 1, 1970). The time is synchronized over the network using the NTP client
 * initialized by setupTimeClient().
 *
 * @return The current time as an unsigned long representing the UNIX timestamp. This
 * value can be used to perform time-related operations, such as scheduling tasks or
 * creating time-stamped records.
 */
unsigned long getCurrentTime();

#endif // TimeClient_h

