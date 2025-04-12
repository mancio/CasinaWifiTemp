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

float getBatteryVoltage() {
    const int analogPin = A0;
    const float R1 = 60000.0; // 60K Ohms resistor
    const float R2 = 10000.0; // 10K Ohms resistor
    const float adcRefVoltage = 3.3; // ADC reference voltage
    const float adcMax = 1023.0; // 10-bit ADC
    const float fineTuneOffset = -0.02; // Adjust this value for fine-tuning

    auto adcValue = static_cast<float>(analogRead(analogPin));
    float adcVoltage = (adcValue / adcMax) * adcRefVoltage;
    float batteryVoltage = adcVoltage * ((R1 + R2) / R2);

    return batteryVoltage + fineTuneOffset;
}

