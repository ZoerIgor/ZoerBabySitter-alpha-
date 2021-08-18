#include "TASK_EventModeFactory.h"
#define DEBUG
void TASK_EventModeFactory(void *pvParameters)
{
    #ifdef DEBUG
        Serial.print("Start task:\t");
        Serial.println("EVENT MODE FACTORY");
        Serial.println("-------------------------------");
    #endif
    event = EVENT_LOADIND_SETUP;
    int timer = 0;
    for(;;)
    {
        switch(event)
        {
            case EVENT_LOADIND_SETUP:
            {
                ServoDefaultVarInFactoryMode();
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_SERVO_TEST:
            {
                ServoSetup();
                RELAY_MAIN.set(ENABLE);
                SERVO_MAIN.testAvailableRange();
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_SERVO_CALIBRATE_MIN:
            {
                minAnalogSig = SERVO_MAIN.setMinAnalogSig();
                #ifdef DEBUG0
                    Serial.print("Min analog sig:\t");
                    Serial.println(SERVO_MAIN.setMinAnalogSig());
                #endif
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_SERVO_CALIBRATE_MID:
            {
                midAnalogSig = SERVO_MAIN.setMidAnalogSig();
                #ifdef DEBUG0
                    Serial.print("Mid analog sig:\t");
                    Serial.println(SERVO_MAIN.setMidAnalogSig());
                #endif
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_SERVO_CALIBRATE_MAX:
            {
                maxAnalogSig = SERVO_MAIN.setMaxAnalogSig();
                #ifdef DEBUG0
                    Serial.print("Max analog sig:\t");
                    Serial.println(SERVO_MAIN.setMaxAnalogSig());
                #endif
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_SERVO_CALIBRATE_TEST:
            {
                RELAY_MAIN.set(ENABLE);
                SERVO_MAIN.setDegrees();
                SERVO_MAIN.testCalibrateRange();
                calibMinDeg = SERVO_MAIN.getCalibMinAng();
                calibMidDeg = SERVO_MAIN.getCalibMidAng();
                calibMaxDeg = SERVO_MAIN.getCalibMaxAng();
                /* Serial.print("Min: ");
                Serial.print(calibMinDeg);
                Serial.print("\tMid: ");
                Serial.print(calibMidDeg);
                Serial.print("\tMax: ");
                Serial.println(calibMaxDeg); */
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_BUTTON_FACTORY_TEST:
            {
                if(BUTTON_FACTORY.get() >= HOLD)
                {
                    testFactoryButton = true;
                }
                if(timer == 0)
                {
                    timer = millis();
                }
                if((millis() - timer) >= testDuration)
                {
                    timer = 0;
                    onTestFactoryButton = false;
                    event = EVENT_SHUTDOWN;
                }
                break;
            }
            case EVENT_BUTTON_MAIN_TEST:
            {
                if(BUTTON_MAIN.get() >= HOLD)
                {
                    testMainButton = true;
                }
                if(timer == 0)
                {
                    timer = millis();
                }
                if((millis() - timer) >= testDuration)
                {
                    timer = 0;
                    onTestMainButton = false;
                    event = EVENT_SHUTDOWN;
                }
                break;
            }
            case EVENT_TEST_MIC:
            {
                short countdown = TIME_HOLD / 2;
                int timeLeft = millis();
                while(millis() - timeLeft < countdown)
                {
                    if(quietDb == 0 && loudDb == 0)
                    {
                        quietAdc = MIC_MAIN.setQuiteAdc();
                        /* Serial.print("Quite TOP\t");
                        Serial.print(MIC_MAIN.getQuiteTopAdc());
                        Serial.print("\tQuite BOT\t");
                        Serial.println(MIC_MAIN.getQuiteBotAdc()); */
                    }
                    else if(quietDb != 0 && loudDb == 0)
                    {
                        loudAdc = MIC_MAIN.setLoudAdc();
                        /* Serial.print("Loud TOP\t");
                        Serial.print(MIC_MAIN.getLoudTopAdc());
                        Serial.print("\tLoud BOT\t");
                        Serial.println(MIC_MAIN.getLoudBotAdc()); */
                    }
                    else if(quietDb != 0 && loudDb != 0)
                    {
                        MIC_MAIN.setQuietDb(quietDb);
                        MIC_MAIN.setLoudDb(loudDb);
                        if(MIC_MAIN.calcDb())
                        {
                            short sigTop = 0;
                            short sigBot = MIC_MAIN.getResolution();
                            short meashure;
                            int timeLeft = millis();
                            while(millis() - timeLeft < countdown)
                            {
                                meashure = MIC_MAIN.getAdc();
                                if(sigTop < meashure)
                                {
                                    sigTop = meashure;
                                }
                                if(sigBot > meashure)
                                {
                                    sigBot = meashure;
                                }
                                if(!onTestMic)
                                {
                                    break;
                                }
                            }
                            currentDb = MIC_MAIN.getDb(sigTop, sigBot);
                            if(currentDb != 0);
                            {
                                testMic = true;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    if(!onTestMic)
                    {
                        break;
                    }
                }
                onTestMic = false;
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_SHUTDOWN:
            {
                RELAY_MAIN.set(DISABLE);
                SERVO_MAIN.detach();
                vTaskDelay(DELAY_RELAY);
                RELAY_MAIN.set(ENABLE);
                timer = 0;
                event = EVENT_OFF;
                break;
            }
            case EVENT_OFF:
            {
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