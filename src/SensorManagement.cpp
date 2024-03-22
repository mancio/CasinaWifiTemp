#include <OneWire.h>
#include <DallasTemperature.h>
#include "SensorManagement.h"

#define ONE_WIRE_BUS D2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void beginSensors() {
    sensors.begin();
}

float getTemperature() {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
}

