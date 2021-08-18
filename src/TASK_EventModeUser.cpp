#include "TASK_EventModeUser.h"
#define DEBUG
void TASK_EventModeUser(void *pvParameters)
{
    #ifdef DEBUG
        Serial.print("Start task:\t");
        Serial.println("EVENT MODE USER");
        Serial.println("-------------------------------");
    #endif
    event = EVENT_LOADIND_SETUP;
    for(;;)
    {
        switch(event)
        {
            case EVENT_LOADIND_SETUP:
            {
                ExtractArhive();
                CreatCodeInLists();
                CreatBuildProgramm();
                ServoSetup();
                ServoCalibrate();
                ServoInstallationSettings();
                ServoInstallationSetup();
                SetDemoTimetable();
                MessageAssembly();
                ExtractParamMechStart(mechanicalStart);
                BeginRotAngMeashTimer();
                //previousMeashureAngle = SERVO_MAIN.getActualAngle();
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_GET_CURRENT_ANGLE:
            {
                if (++switchEvent > EVENT_MECH_START_CONT)
                {
                    switchEvent = 0;
                }
                newMeashureAngle = SERVO_MAIN.getActualAngle();
                switch(switchEvent)
                {
                    case EVENT_FASTENER_CHECK:
                    {
                        
                        event = EVENT_OFF;
                        break;
                    }
                    case EVENT_MECH_START_SWING:
                    {
                        if (startSwinging)
                        {

                        }
                        event = EVENT_OFF;
                        break;
                    }
                    case EVENT_MECH_START_CONT:
                    {
                        if (startControlled)
                        {

                        }
                        event = EVENT_OFF;
                        break;
                    }
                }
                break;
            }
            case EVENT_HOLD_IN_REST:
            {
                SERVO_MAIN.attach();
                SERVO_MAIN.write(SERVO_MAIN.getActualAngle());
                event = EVENT_OFF;
                break;
            }
            case EVENT_SAVE_DEMO_SETUP:
            {
                if (EepromDemoMode.get() == DEMO_MODE_OFF)
                {
                    if (BUTTON_MAIN.get() == CLICK)
                    {
                        SaveDemoSetup();
                        BUTTON_MAIN.resetPressStatus();
                        needSaveDemo = false;
                    }
                    else
                    {
                        if (!needSaveDemo)
                        {
                            needSaveDemo = true;
                        }
                    }
                }
                else
                {
                    SaveDemoSetup();
                    needSaveDemo = false;
                }
                event = EVENT_OFF;
                break;
            }
            case EVENT_DEMO:
            {
                if (demoMode == DEMO_MODE_ALWAYS)
                {
                    event = WatchdogDemoTimer();
                }
                else
                {
                    if (clockOn)
                    {
                        if (systemTime >= beginTimetableWork && systemTime < endTimetableWork)
                        {
                            event = WatchdogDemoTimer();
                        }
                    }
                }
                break;
            }
            case EVENT_WORK:
            {
                RemainingTime LeftToWork("LEFT_WORK", (workTime * SEC_IN_MIN) - workedTime, "ЗАВЕРШЕНО", 3);
                Informer.add(LeftToWork);
                doWork = true;
                ServoUserSetup();
                RELAY_MAIN.set(ENABLE);
                BeginWorkTimer();
                SERVO_MAIN.swing(doWork, workTime, workedTime);
                EndWorkTimer();
                Informer.pop();
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_SHUTDOWN:
            {
                doWork = false;
                RELAY_MAIN.set(DISABLE);
                SERVO_MAIN.detach();
                vTaskDelay(DELAY_RELAY);
                RELAY_MAIN.set(ENABLE);
                event = EVENT_OFF;
                break;
            }
            case EVENT_OFF:
            {
                if (BUTTON_MAIN.get() == HOLD)
                {
                    if (pageNumber == HTML_USER_RESET_INSTALLATION)
                    {
                        FormatInstalationCluster();
                        FormatUserCluster();
                        FormatWirelessCluster();
                        event = EVENT_RESTART;
                        BUTTON_MAIN.resetPressStatus();
                    }
                    else if (pageNumber == HTML_USER_RESET_USER)
                    {
                        FormatUserCluster();
                        FormatWirelessCluster();
                        event = EVENT_RESTART;
                        BUTTON_MAIN.resetPressStatus();
                    }
                    else if (pageNumber == HTML_USER_RESET_PROG)
                    {
                        ResetCodesCounters();
                        FormatProg();
                        catalogHeaderUserProg.clear();
                        ExtractArhive();
                        pageNumber = HTML_MAIN;
                        BUTTON_MAIN.resetPressStatus();
                    }
                    else
                    {
                        EepromWirelessMode.set(WIRELESS_DEFAULT_AP);
                        event = EVENT_RESTART;
                        BUTTON_MAIN.resetPressStatus();
                    }
                }
                if (demoMode != DEMO_MODE_OFF && !needSaveDemo)
                {
                    event = EVENT_DEMO;
                }
                if (needSaveDemo)
                {
                    event = EVENT_SAVE_DEMO_SETUP;
                }
                event = EVENT_GET_CURRENT_ANGLE;
                break;
            }
            case EVENT_RESTART:
            {
                vTaskDelay(DELAY_RESTART);
                ESP.restart();
                break;
            }
        }
        vTaskDelay(1);
    }
}