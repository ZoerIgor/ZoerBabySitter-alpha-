#include "FUNC_TaskManager.h"
#define DELAY_MICROSECONDS 1000
#define DEBUG
// Ключи управления задачь
TaskHandle_t handleEventModeFactory;
TaskHandle_t handleEventModeInstallation;
TaskHandle_t handleEventModeUser;
TaskHandle_t handleWebServer;
TaskHandle_t handleStaff;
// Функции
void SetTaskStatus(TaskHandle_t handle, byte status)
{
    TaskHandle_t *pointerToHandle = &handle;
    switch (status)
    {
        case TASK_CREATE:
        {
            if(*pointerToHandle == &handleEventModeFactory)
            {
                xTaskCreatePinnedToCore(TASK_EventModeFactory, "EventModeFactory", 4096, NULL, 0, &handleEventModeFactory, 1);
            }
            if(*pointerToHandle == &handleEventModeInstallation)
            {
                xTaskCreatePinnedToCore(TASK_EventModeInstallation, "EventModeInstallation", 16384, NULL, 0, &handleEventModeInstallation, 1);
            }
            if(*pointerToHandle == &handleEventModeUser)
            {
                xTaskCreatePinnedToCore(TASK_EventModeUser, "EventModeUser", 4096, NULL, 5, &handleEventModeUser, 1);
            }
            if(*pointerToHandle == &handleWebServer)
            {
                xTaskCreatePinnedToCore(TASK_WebServer, "WebServer", 16384, NULL, 0, &handleWebServer, 0);
            }
            if(*pointerToHandle == &handleStaff)
            {
                xTaskCreatePinnedToCore(TASK_Staff, "Staff", 4096, NULL, 0, &handleStaff, 0);
            }
            delayMicroseconds(DELAY_MICROSECONDS);
            break;
        }
        case TASK_PAUSE:
        {
            vTaskSuspend(handle);
            break;
        }
        case TASK_RESUME:
        {
            vTaskResume(handle);
            break;
        }
        case TASK_DELETE:
        {
            vTaskDelete(handle);
            break;
        }
    }
}
void StartOS()
{
    if(mode == MODE_FACTORY)
    {
        SetTaskStatus(&handleEventModeFactory, TASK_CREATE);
    }
    else if(mode == MODE_INSTALATION)
    {
        SetTaskStatus(&handleEventModeInstallation, TASK_CREATE);
    }
    else if(mode == MODE_USER)
    {
        SetTaskStatus(&handleEventModeUser, TASK_CREATE);
    }
    if(wirelessMode == WIRELESS_OFF)
    {
        SetTaskStatus(&handleStaff, TASK_CREATE);
    }
    else
    {
        SetTaskStatus(&handleWebServer, TASK_CREATE);
    }
}