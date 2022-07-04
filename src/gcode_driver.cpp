#include "Arduino.h"
#include "pid.h"

char incomingData[100];
char buffer[100];

void parse_commands()
{
    char* token = strtok(incomingData, "=");
    if (strcmp(token, "$1ps") == 0)
    {
        sprintf(buffer, "$1ps=%s", get_pressure());
        Serial.println(buffer);
    }

    else if (strcmp(token, "$1sp") == 0)
    {
        char* token = strtok(NULL, "=");
        if (token != NULL)
        {
            bool r = set_setpoint(token);
            if (r == true)
            {
                sprintf(buffer, "$1sp=%s", get_setpoint());
                Serial.println(buffer);
            }

            else Serial.println("Error");
        }

        else
        {
            sprintf(buffer, "$1sp=%s", get_setpoint());
            Serial.println(buffer);
        }
    }
}

void serialEvent()
{
    while(Serial.available())
    {
        Serial.readBytesUntil('\n', incomingData, 100);
        incomingData[strlen(incomingData) - 1] = 0;
    }
    Serial.flush();
    parse_commands();
}