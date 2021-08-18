#include "TASK_Staff.h"
#define DEBUG
#define DELAY 1000
void TASK_Staff(void *pvParameters)
{
    #ifdef DEBUG
        Serial.print("Start task:\t");
        Serial.println("STAFF");
        Serial.println("-------------------------------");
    #endif
    for(;;)
    {
        /* SetTaskStatus(handleWebServer, TASK_DELETE);
        vTaskDelay(DELAY);
        SetTaskStatus(&handleWebServer, TASK_CREATE);
        SetTaskStatus(handleStaff, TASK_DELETE); */
        if (BUTTON_MAIN.get() == HOLD)
        {
            EepromWirelessMode.set(WIRELESS_DEFAULT_AP);
            vTaskDelay(DELAY_SEC);
            ESP.restart();
        }
    }
}