#ifndef FirebaseModule_h
#define FirebaseModule_h

#include <Arduino.h>

void initializeFirebase();
void sendDataToFirebase(const String& path, const float temperature, const unsigned long timestamp);

#endif
