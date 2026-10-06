#ifndef SensorManagement_h
#define SensorManagement_h

// Pack voltage below which the device stops for good (1.0 V/cell on 4x AA).
// Protects NiMH cells from over-discharge; costs alkalines almost nothing.
constexpr float BATTERY_CUTOFF_V = 4.0f;

// Below this the divider sees no pack at all: running from USB with the
// batteries removed, so the cutoff must not apply.
constexpr float BATTERY_ABSENT_V = 1.0f;

void beginSensors();
float getTemperature();

/**
 * @brief Reads the pack voltage through the divider on A0.
 *
 * Averages several samples. Call it before WiFi starts so the value is the
 * resting voltage, not the one sagging under the radio's current peaks.
 */
float getBatteryVoltage();

#endif
