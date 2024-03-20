## NOTE

remember to include in the folder include the file ``secrets.h``

```cpp
#ifndef CASINAWIFITEMP_SECRETS_H
#define CASINAWIFITEMP_SECRETS_H

// Network credentials
#define WIFI_SSID "REPLACE_WITH_YOUR_SSID"
#define WIFI_PASSWORD "REPLACE_WITH_YOUR_PASSWORD"

// Firebase project API Key
#define API_KEY "REPLACE_WITH_YOUR_PROJECT_API_KEY"

// Authorized Email and Password
#define USER_EMAIL "REPLACE_WITH_THE_USER_EMAIL"
#define USER_PASSWORD "REPLACE_WITH_THE_USER_PASSWORD"

// RTDB URL
#define DATABASE_URL "REPLACE_WITH_YOUR_DATABASE_URL"

// GPIO where the DS18B20 is connected
#define ONE_WIRE_BUS D2

#endif // CASINAWIFITEMP_SECRETS_H
```
