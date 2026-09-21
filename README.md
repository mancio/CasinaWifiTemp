## WiFi Thermometer Setup Guide

### Overview:

This WiFi Thermometer is designed to measure temperature data and upload it directly to Firebase, providing a seamless way to monitor temperature readings remotely. The device is built using the NodeMCU V3 board, leveraging its WiFi capabilities to connect and transmit data over the internet.


![box](https://github.com/mancio/CasinaWifiTemp/blob/71a789c17b30f7a4f402f0c2387b660cc454c00f/photos/circuit.PNG)


### Key Features:

- **Real-time Temperature Monitoring:** Continuously measures and uploads temperature data to a Firebase database.
- **Wireless Connectivity:** Utilizes the onboard WiFi module of the NodeMCU V3 board to connect to the internet.
- **Firebase Integration:** Configured to interface directly with Firebase, allowing data to be accessed in real time.
- **Deep Sleep Between Readings:** The ESP8266 sleeps for 30 minutes between transmissions. Note that on a NodeMCU V3 the board-level drain dominates anyway - see "Known issues" below.
- **Easy Configuration:** Users can set their WiFi and Firebase settings via a simple configuration file.

### Technical Specifications:

- **Board:** NodeMCU V3
- **Connectivity:** WiFi (ESP8266)
- **Power:** USB 5V, or a 4x AA pack on `VIN` with voltage monitoring via `A0`.
- **Additional Components:** DS18B20 temperature sensor, battery monitoring voltage divider, and a 1F supercapacitor across `VIN` (ineffective - see "Known issues").

### Battery voltage divider:

Battery positive feeds a two-resistor divider whose tap goes to the `A0` pin:

```
BAT+ ---[ R1 = 60k ]---+--- A0
                       |
                    [ R2 = 10k ]
                       |
BAT- ------------------+--- GND
```

- **R1 (60 kΩ)** is not a single part: it is a chain of smaller resistors in series, housed inside the black heat-shrink tube on the battery lead (see photo above).
- **R2 (10 kΩ)** is the single resistor mounted next to the `A0` pin.
- These values are mirrored in `getBatteryVoltage()` in `src/SensorManagement.cpp`.

**Caveat - the NodeMCU V3 has its own internal divider on `A0`** (220 kΩ in series, 100 kΩ to ground) in front of the ESP8266's 1.0 V ADC. That 320 kΩ network sits in parallel with R2, making the effective lower leg ~9.7 kΩ instead of 10 kΩ:

```
V_A0 = V_bat * 9.7k / (60k + 9.7k) = 0.139 * V_bat
```

The result is a ~2-3% under-read, which is what the `fineTuneOffset` constant compensates for. Recalibrate that offset against a multimeter if R1 or R2 is ever changed.

**Standby drain:** the divider is permanently across the pack, so it draws ~86 µA continuously, including during deep sleep. This is minor compared to the AMS1117 regulator and CH340G USB-serial chip on the NodeMCU V3, which together consume roughly 10 mA at all times and dominate the battery budget. Raising the divider to 600k/100k is worthwhile only after the board-level drain is addressed.

### Known issues / what to fix:

**Symptom:** with alkaline AA the device updates far less often than every 30 minutes, while the same build on NiMH rechargeables is reliable.

**Root cause:** the AMS1117 regulator on the NodeMCU V3 needs roughly 4.4 V on `VIN` to hold 3.3 V. Alkaline cells slope down from 1.5 to 1.0 V each and their internal resistance rises as they discharge, so during a WiFi burst (300-400 mA peaks) the pack sags below that threshold and the board browns out mid-upload. NiMH holds a flat 1.2 V/cell with roughly 5-10x lower internal resistance, so it never crosses the dropout point even though its nominal voltage is lower.

Fixes in order of payoff:

1. **Board standby drain (~10 mA).** The AMS1117 quiescent current and the always-powered CH340G mean deep sleep saves almost nothing - the batteries are flattened in a week or two, and spend most of that time in the sagging region. Move to a bare ESP-12F, or bypass the on-board regulator and cut the CH340G supply, feeding 3.3 V directly to the `3V3` pin from a low-quiescent buck (TPS62740, MCP1700 class). Verify by measuring pack current during deep sleep: expect ~20 µA, not ~10 mA.
2. **Regulator dropout.** Replacing the `VIN` path with a buck/buck-boost feeding `3V3` lets the pack run down to ~3.6 V, unlocking most of the alkaline capacity that is currently unusable.
3. **Bulk capacitance in the right place.** Fit a 470-1000 µF low-ESR electrolytic plus a 100 nF ceramic directly across the `3V3` and `GND` pins, short leads.
4. **Remove the 1F supercapacitor from `VIN`.** It cannot do the job it was fitted for. Its ESR is on the order of 1-30 Ω against a battery pack of ~0.3-1 Ω, and in parallel the lower resistance carries the current, so the cap supplies only ~1-3% of each burst. It also sits upstream of the regulator (which still drops 1.1-1.3 V regardless), presents a near-short to the pack at boot while charging, and leaks 1-10 µA continuously. Supercapacitors are worthwhile for high-impedance sources such as coin cells or solar harvesting, not for an AA pack. If it stays, add 10-22 Ω in series to limit inrush.
5. **Retry on failed connect.** `setup()` in `src/Main.cpp` skips straight to `goToDeepSleep()` when WiFi fails, so a single failure costs a full 30-minute slot and two in a row look like a 90-minute gap. Retry with a short sleep instead.
6. **Shorten the high-current window.** `connectToWiFi()` uses `WiFiMulti` with two APs, forcing a full channel scan on every wake and allowing up to 10 s at peak current. A static IP plus BSSID/channel cached in RTC memory cuts this to a few hundred milliseconds. `WiFi.setOutputPower()` can also reduce peak draw.
7. **Measure the battery before enabling WiFi.** `getBatteryVoltage()` is currently called with the radio active, so the value logged to Firebase is the sagged voltage rather than the resting one.

### Target wiring:

The board itself stays unmodified - only the battery routing changes. `VIN` is left unconnected, which also removes the AMS1117 quiescent draw since its input is then dead.

![wiring diagram](photos/wiring-diagram.svg)

SW1 exists so the battery can be isolated before plugging USB, avoiding two supplies driving the 3.3 V rail at once. The voltage divider stays on the raw pack, upstream of the converter - moving it downstream would just measure a constant 3.3 V.

Parts and links: [docs/shopping-list.md](docs/shopping-list.md).

The diagram is generated from `tools/wiring_diagram.py` using [schemdraw](https://schemdraw.readthedocs.io). To regenerate after editing the script:

```powershell
python -m venv .venv
.\.venv\Scripts\python.exe -m pip install schemdraw matplotlib
.\.venv\Scripts\python.exe tools\wiring_diagram.py
```

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
```

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
