#pragma once
#ifndef _TASK_EVENT_MODE_USER_H_
    #define _TASK_EVENT_MODE_USER_H_
    #include <Arduino.h>
    #include "FUNC_General.h"
    extern volatile int workCounter;
    void TASK_EventModeUser(void *pvParameters);
#endif