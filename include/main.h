#ifndef MAIN_h
#define MAIN_h

#include <Arduino.h>

#ifdef _DEBUG_
#define _PP(a) Serial.print(a);
#define _PL(a) Serial.println(a);
#else
#define _PP(a)
#define _PL(a)
#endif

#endif