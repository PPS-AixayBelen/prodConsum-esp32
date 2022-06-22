#include <Arduino.h>

extern "C" {
  #include "printUtils.h"
}

void stringPrint(const char *msg) {
  Serial.print(msg);
}

void stringPrintWithParam(const char *param1, int param2, const char * param3, int param4)
{
  char aux2[100]="";
  strcat(aux2,param1);
  char aux[10]="";
  itoa(param2,aux,10);
  strcat(aux2,aux);
  strcat(aux2,param3);
  char aux3[10] = "";
  itoa(param4,aux3,10);
  strcat(aux2,aux3);
  strcat(aux2,"\n");
  stringPrint(aux2);
}