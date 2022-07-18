#include "Arduino.h"
#include "pid.h"
#include "io_pinout.h"
#include <TaskSchedulerDeclarations.h>
#include <OSFS.h>

extern Scheduler ts;

int adc_reading;
double pressure;
double setPoint, outputVal;
char buf[100];

//pid settings and gains
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255
#define KP .12
#define KI .0003
#define KD 0
#define NOMINAL_VS 5

bool set_setpoint(char* newValue)
{
    char *ptr;
    setPoint = strtod(newValue, &ptr);
    OSFS::result r = OSFS::newFile("setpoint", setPoint, true);
    if (r == OSFS::result::NO_ERROR) return true;
    else return false;
}

char* get_setpoint()
{
    dtostrf(setPoint, -6, 2, buf);
    return buf;
}

char* get_pressure()
{
    dtostrf(pressure, -6, 2, buf);
    return buf;
}

int get_raw_adc()
{
    return adc_reading;
}

void read_sensor()
{
    adc_reading = analogRead(VACUUM_SENSOR);
    if (adc_reading != 0)
    {
      double adc_voltage = adc_reading * (5.0 / 1023.0);
      pressure = adc_voltage / 5.0;
      pressure = pressure + 0.095;
      pressure = pressure / 0.009;
    }
}

void PID_cb();

//input/output variables passed by reference, so they are updated automatically
AutoPID myPID(&pressure, &setPoint, &outputVal, OUTPUT_MIN, OUTPUT_MAX, KP, KI, KD);

void PID_config()
{
    //if temperature is more than 4 degrees below or above setpoint, OUTPUT will be set to min or max respectively
    myPID.setBangBang(4);
    //set PID update interval to 4000ms
    myPID.setTimeStep(4000);
    OSFS::result r = OSFS::getFile("setpoint", setPoint);
    if (r == OSFS::result::FILE_NOT_FOUND)
    {
        Serial.println("Did not found setpoint, something is wrong");
    }
}

void PID_cb()
{
    analogWrite(RELAY_OUTPUT, outputVal);
}

Task tPID ( 1000 * TASK_MILLISECOND, TASK_FOREVER, &PID_cb, &ts, true );