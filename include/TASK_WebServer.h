#pragma once
#ifndef _TASK_WEB_SERVER_H_
    #define _TASK_WEB_SERVER_H_
    #include <Arduino.h>
    #include "FUNC_Wireless.h"
    #include "FUNC_Html.h"
    #include "FUNC_General.h"
    #define DELAY_DECISEC 100
    #define DELAY_SEC 1000
    class ReadBuffer
    {
        public:
            ReadBuffer();
            String getName(String buffer, byte inputNumber);
            String get(String buffer, byte inputNumber);
        private:
            bool endRequest, answer;
            String buffer, value;
            byte inputNumber, indexNumber;
    };
    void TASK_WebServer(void *pvParameters);
#endif