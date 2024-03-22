#include "DeepSleep.h"
#include <Esp.h>

void goToDeepSleep() {
    EspClass::deepSleep(3600e6); // 1 hour
}

