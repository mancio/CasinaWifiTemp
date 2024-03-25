#ifndef FirebaseModule_h
#define FirebaseModule_h

#include <Arduino.h>

void initializeFirebase();
void sendDataToFirebase(const String& path, float temperature, float voltage, unsigned long timestamp);

#endif
