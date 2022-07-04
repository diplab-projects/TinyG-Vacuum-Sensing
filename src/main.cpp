#include "io_pinout.h"
#include "pid.h"
#include "main.h"
#include <TaskSchedulerDeclarations.h>
#include <OSFS.h>

extern AutoPID myPID;
extern Scheduler ts;
OSFS::result r;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(VACUUM_SENSOR, INPUT);
  pinMode(RELAY_OUTPUT, OUTPUT);
  PID_config();
  Serial.println("Reading setpoint from EEPROM...");
  double teste = 90.0;
  r = OSFS::newFile("setpoint", teste);
  if (r == OSFS::result::UNFORMATTED)
  {
    Serial.println("EEPROM not formatted, formatting...");
    OSFS::format();
  }

  else if (r == OSFS::result::FILE_ALREADY_EXISTS)
  {
    Serial.println("Found previous setpoint in EEPROM, will use it");
  }
}

void loop()
{
  ts.execute();
  myPID.run(); //call every loop, updates automatically at certain time interval
}

void blink_CB()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

Task tBlink ( 1000 * TASK_MILLISECOND, TASK_FOREVER, &blink_CB, &ts, true );
