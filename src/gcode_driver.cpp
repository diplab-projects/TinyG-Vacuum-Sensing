#include "Arduino.h"
#include "pid.h"

char incomingData[100];
char buffer[100];

void parse_commands()
{
    if (strcmp(incomingData, "M105") == 0)
    {
        Serial.print("ok T:");
        Serial.println(get_raw_adc());
    }
}

void serialEvent()
{
    while(Serial.available())
    {
        Serial.readBytesUntil('\n', incomingData, 10);
        //incomingData[strlen(incomingData) -1] = '\0';
    }
    incomingData[strcspn(incomingData, "\r\n")] = 0;
    parse_commands();
    Serial.println("expansion ok");
}