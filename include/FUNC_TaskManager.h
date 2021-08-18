#pragma once
#ifndef _FUNC_TASK_MANAGER_H_
    // Включения
        #define _FUNC_TASK_MANAGER_H_
        #include <Arduino.h>
        #include <FreeRTOS.h>
        #include "TASK_EventModeFactory.h"
        #include "TASK_EventModeInstallation.h"
        #include "TASK_EventModeUser.h"
        #include "TASK_WebServer.h"
        #include "TASK_Staff.h"
        #include "FUNC_General.h"
    // Перечисления
        enum EnumTaskStatus
        {
            TASK_CREATE,
            TASK_PAUSE,
            TASK_RESUME,
            TASK_DELETE
        };
    // Объявления
        extern TaskHandle_t handleEventModeFactory;
        extern TaskHandle_t handleEventModeInstallation;
        extern TaskHandle_t handleEventModeUser;
        extern TaskHandle_t handleWebServer;
        extern TaskHandle_t handleStaff;
    // Глобальные функций
        void SetTaskStatus(TaskHandle_t handle, byte status);
        void StartOS();
#endif