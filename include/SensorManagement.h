/**
 * @file SensorManagement.h
 * @brief Provides functions for managing sensor operations.
 *
 * This header file declares functions related to sensor initialization and
 * temperature data retrieval. It's designed to abstract sensor-specific operations
 * and provide a simple interface for main application logic.
 */

#ifndef SensorManagement_h
#define SensorManagement_h

/**
 * @brief Initializes sensor hardware.
 *
 * Prepares the sensor hardware for operation. This function must be called
 * before attempting to read temperature data. It configures necessary hardware
 * interfaces and performs any required initial calibration or configuration.
 */
void beginSensors();

/**
 * @brief Retrieves the current temperature reading from the sensor.
 *
 * Reads the latest temperature value from the sensor. This function assumes
 * that the sensor has been previously initialized using beginSensors().
 *
 * @return The current temperature as a float. The specific units (e.g., Celsius,
 * Fahrenheit) depend on the sensor's configuration and implementation.
 */
float getTemperature();

#endif // SensorManagement_h


