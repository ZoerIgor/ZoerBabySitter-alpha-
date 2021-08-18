#include "TASK_EventModeInstallation.h"
#define DEBUG
const byte size = 2;
const byte lenght = WORK_RANGE - 4;
const short prefix = lenght / 2;
short arrIndex;
bool direction;
short currentAmplitude;
volatile int counter;
void TASK_EventModeInstallation(void *pvParameters)
{
    #ifdef DEBUG
        Serial.print("Start task:\t");
        Serial.println("EVENT MODE INSTALLATION");
        Serial.println("-------------------------------");
    #endif
    event = EVENT_LOADIND_SETUP;
    for(;;)
    {
        switch(event)
        {
            case EVENT_LOADIND_SETUP:
            {
                ServoSetup();
                ServoCalibrate();
                ServoDefaultVarInInstallationMode();
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_REST:
            {
                SERVO_MAIN.setRelativeMiddle(true);
                startPosition = SERVO_MAIN.getActualAngle();
                restCalibrate = true;
                short startPositionModul = startPosition;
                if(startPosition < 0)
                {
                    startPositionModul = startPosition * (-1);
                }
                if(startPositionModul > badDeflection)
                {
                    restCalibrateComplite = false;
                }
                else
                {
                    restCalibrateComplite = true;
                }
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_AMPLITUDE_MEASURE:
            {
                SERVO_MAIN.setRelativeMiddle(true);
                amplitudeMeashure = true;
                extremeMinusAngle = 0;
                extremePlusAngle = 0;
                int ** arrMeasureDelays = new int * [size];
                short previousAngle = SERVO_MAIN.getActualAngle();
                // Создание многомерного динамического массива
                for(byte i = 0; i < size; i++)
                {
                    arrMeasureDelays[i] = new int [lenght];
                }
                // Заполнение 1-го массива метками
                for(byte i = 0; i < lenght; i++)
                {
                    short k = (i + 2) - (WORK_RANGE / 2);
                    if(k < 0)
                    {
                        arrMeasureDelays[0][i] = k;
                    }
                    else
                    {
                        arrMeasureDelays[0][i] = k + 1;
                    }
                }
                // Заполнение 2-го массива нолями
                for(byte i = 1; i < size; i++)
                {
                    for(byte j = 0; j < lenght; j++)
                    {
                        arrMeasureDelays[i][j] = 0;
                    }
                }
                // Цикл замера амплитуды
                while(!amplitudeMeashureComplite)
                {
                    short currentAngle = SERVO_MAIN.getActualAngle();
                    if(previousAngle != currentAngle)
                    {
                        arrIndex = currentAngle + prefix;
                        if(arrIndex >= 0 && arrIndex < lenght)
                        {
                            arrMeasureDelays[1][arrIndex] = 1;
                        }
                        previousAngle = currentAngle;
                    }
                }
                // Поиск наименьшего угла
                for(byte i = 0; i < lenght; i++)
                {
                    if(arrMeasureDelays[1][i] == 1)
                    {
                        extremeMinusAngle = arrMeasureDelays[0][i];
                        break;
                    }
                }
                // Поиск наибольшего угла
                for(byte i = (lenght - 1); i >= 0; i--)
                {
                    if(arrMeasureDelays[1][i] == 1)
                    {
                        extremePlusAngle = arrMeasureDelays[0][i];
                        break;
                    }
                }
                // Расчет амплитуды
                short minAng = 0;
                short maxAng = 0;
                if(extremeMinusAngle < 0)
                {
                    minAng = extremeMinusAngle * (-1);
                }
                else
                {
                    minAng = extremeMinusAngle;
                }
                if(extremePlusAngle < 0)
                {
                    maxAng = extremePlusAngle * (-1);
                }
                else
                {
                    maxAng = extremePlusAngle;
                }
                maxAmplitude = minAng + maxAng;
                // Очистка динамической памяти
                for(short i = 0; i < size; i++)
                {
                    delete[] arrMeasureDelays[i];
                }
                delete[] arrMeasureDelays;
                // Выключение
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_SLOW_MO_TEST:
            {
                RELAY_MAIN.set(ENABLE);
                if(descendingAccModel)
                {
                    slowMoTest = true;
                }
                ServoInstallationSettings();
                ServoInstallationSetupSlowMo();
                SERVO_MAIN.swingCalibration(slowMoTest);
                if(slowMoTest)
                {
                    slowMoTestComplite = true;
                }
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_FAST_MO_TEST:
            {
                RELAY_MAIN.set(ENABLE);
                if(descendingAccModel)
                {
                    fastMoTest = true;
                }
                ServoInstallationSetupFastMo();
                SERVO_MAIN.swingCalibration(fastMoTest);
                if(fastMoTest)
                {
                    fastMoTestComplite = true;
                }
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_AUTO_MO_TEST:
            {
                event = EVENT_SHUTDOWN;
                break;
            }
            case EVENT_SHUTDOWN:
            {
                RELAY_MAIN.set(DISABLE);
                SERVO_MAIN.detach();
                vTaskDelay(DELAY_RELAY);
                RELAY_MAIN.set(ENABLE);
                event = EVENT_OFF;
                break;
            }
            case EVENT_OFF:
            {
                if (BUTTON_FACTORY.get() == HOLD)
                {
                    FormatFactoryCluster();
                    event = EVENT_RESTART;
                }
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