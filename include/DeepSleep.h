#ifndef DeepSleep_h
#define DeepSleep_h

/**
 * @brief Puts the device into deep sleep mode.
 *
 * This function configures the ESP8266 or ESP32 to enter deep sleep mode for a specified duration.
 * The device will wake up automatically after the deep sleep period is over.
 *
 * Note: On ESP8266, deep sleep requires connecting D0 to RST to wake up correctly.
 *
 * @see https://docs.espressif.com/projects/esp8266/en/latest/esp8266_hardware_reference/en/modules/sleep_modes.html
 */
void goToDeepSleep();

#endif


