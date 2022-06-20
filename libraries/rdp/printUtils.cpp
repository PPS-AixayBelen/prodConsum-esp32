#include <Arduino.h>

extern "C" {
  #include "printUtils.h"
}

void stringPrint(const char *msg) {
  Serial.print(msg);
}