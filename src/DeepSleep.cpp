#include "DeepSleep.h"
#include <Esp.h>

void goToDeepSleep() {
    ESP.deepSleep(3600e6); // 1 hour
}

