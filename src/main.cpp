#include "main.h"
#define DEBUG
void setup()
{
    setlocale(LC_ALL, "ru");
    Serial.begin(921600);
    #ifdef DEBUG
        Serial.println();
        Serial.println("-------------------------------");
        Serial.println("SERIAL MONITOR initialized");
        Serial.println("-------------------------------");
    #endif
    pinMode(LED_BUILTIN, OUTPUT);
    BeginEeprom();
    #ifdef DEBUG0
        EepromService.clear(MEMORY_ALL);
        EepromService.read(false, MEMORY_ALL);
    #else
        ReadEeprom();
    #endif
    #ifdef DEBUG
        onTestMic = true;
        testMic = true;
    #endif
    #ifdef DEBUG
        minDelaySlow = 5;
        maxDelaySlow = 20;
        //betweenDelaySlow = 100;
        incrementSlow = 3;
        accelerationModelSlow[0] = 9.0;
        accelerationModelSlow[1] = 5.0;
        accelerationModelSlow[2] = 3.0;
        accelerationModelSlow[3] = 2.0;
        accelerationModelSlow[4] = 1.0;
        minDelayFast = 3;
        maxDelayFast = 15;
        //betweenDelayFast = 150;
        incrementFast = 5;
        accelerationModelFast[0] = 9.0;
        accelerationModelFast[1] = 3.5;
        accelerationModelFast[2] = 2.0;
        accelerationModelFast[3] = 1.5;
        accelerationModelFast[4] = 1.0;
        EepromMinDelaySlow.set(minDelaySlow);
        EepromMaxDelaySlow.set(maxDelaySlow);
        //EepromBetweenDelaySlow.set(betweenDelaySlow);
        EepromIncrementSlow.set(incrementSlow);
        EepromAccelerationModelSlow.set(accelerationModelSlow);
        EepromMinDelayFast.set(minDelayFast);
        EepromMaxDelayFast.set(maxDelayFast);
        //EepromBetweenDelayFast.set(betweenDelayFast);
        EepromIncrementFast.set(incrementFast);
        EepromAccelerationModelFast.set(accelerationModelFast);
    #endif
    #ifdef DEBUG0
        /* Serial.print("accelerationModelSlow: ");
        for(byte i = 0; i < 5; i++)
        {
            Serial.print(String(accelerationModelSlow[i], DEC) + " ");
        }
        Serial.println(); */
        mode = MODE_INSTALATION;
        pageNumber = HTML_INSTALATION_MANUAL_SLOW;
    #endif
    #ifdef DEBUG0
        for (byte i = 0 ; i < maxSizeArhive; i++)
        {
            arhiveArray[i] = 0;
        }
        EepromArhiveArray.set(arhiveArray);
    #endif
    #ifdef DEBUG0
        for (byte i = 0 ; i < maxSizeArhive; i++)
        {
            Serial.print(arhiveArray[i]);
        }
        Serial.println();
    #endif
    #ifdef DEBUG
        mode = MODE_USER;
        /* MemoryASCII header(349, 1);
        header.write(349, 200); */
    #endif
    #ifdef DEBUG
        wirelessMode = WIRELESS_AP;
        staEncryptionType = ENCRYPT_WPA2;
        staSsid = "MOBILE";
        staPassword = "4829pack";
        apSsid = "TEST";
        apPassword = "12345678";
        apStaticNetworkConfig = true;
        apIp[0] = 192;
        apIp[1] = 168;
        apIp[2] = 0;
        apIp[3] = 1;
        apMask[0] = 255;
        apMask[1] = 255;
        apMask[2] = 255;
        apMask[3] = 0;
        apGateway[0] = 192;
        apGateway[1] = 168;
        apGateway[2] = 0;
        apGateway[3] = 1;
    #endif
    #ifdef DEBUG0
        FormatUserCluster();
        FormatWirelessCluster();
    #endif
    #ifdef DEBUG0
        mechanicalStart = ONE_HUNDRED_MILLIONS;
        EepromMechanicalStart.set(mechanicalStart);
    #endif
    #ifdef DEBUG0
        #ifdef DEBUG0
            EepromService.read(true, MEMORY_ALL);
        #else
            byte eeprom[512] = {49,0,255,255,255,255,255,255,255,255,255,255,255,72,17,212,209,8,240,197,59,65,55,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,20,180,0,244,1,196,9,139,0,251,6,179,13,91,0,0,0,166,255,0,0,0,0,0,0,0,0,0,0,2,0,97,4,0,6,0,20,0,6,0,3,0,0,16,65,0,0,160,64,0,0,64,64,0,0,0,64,0,0,128,63,2,0,3,0,10,0,1,0,5,0,0,16,65,0,0,96,64,0,0,0,64,0,0,192,63,0,0,128,63,0,0,0,69,83,84,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,50,51,52,53,54,55,56,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,79,66,73,76,69,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,56,50,57,112,97,99,107,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,97,114,121,39,115,32,98,101,100,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,1,1,0,0,0,0,255,255,0,0,0,255,0,0,0,100,131,162,15,4,9,101,195,226,10,9,9,102,194,225,15,9,9,103,195,227,15,9,9,255,193,5,6,7,8,6,194,5,6,7,195,5,6,7,8,9,224,7,6,5,4,3,2,225,2,1,2,226,9,5,2,227,5,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            EepromService.write(MEMORY_ALL, eeprom);
        #endif
    #endif
    EepromService.deleteAllCluster();
    StartOS();
}
void loop(){delay(9999999);}