#ifndef PID_h
#define PID_h

#include <AutoPID.h>

char* get_setpoint();
bool set_setpoint(char*);
char* get_pressure();
void PID_config();

#endif