#pragma once
#ifndef _FUNC_EEPROM_H_
    // Включения
        #define _FUNC_EEPROM_H_
        #include <Arduino.h>
        #include "LIB_Eeprom.h"
        #include "FUNC_TaskManager.h"
        #include "FUNC_General.h"
    // Перечисления
        #define ADDRESS_PROGRAM_ARHIVE 318
        #define SIZE_PROGRAM_ARHIVE 194
        enum EnumMemoryCluster
        {
            MEMORY_ALL,
            MEMORY_SERVICE,
            MEMORY_FACTORY,
            MEMORY_INSTALATION,
            MEMORY_USER,
            MEMORY_WIRELESS
        };
    // Объявление экземпляров классов энергонезависимой памяти
        extern MemoryService EepromService;
        extern MemoryString EepromDeviceSerialNumber;
        extern MemoryByteArray EepromControllerSerialNumber;
        extern MemoryInt EepromBuildDate;
        extern MemoryInt EepromMaintenanceDate;
        extern MemoryInt EepromLastServiceDate;
        extern MemoryInt EepromTotalWork;
        extern MemoryByte EepromWorkTime;
        extern MemoryByte EepromTimePassed;
        extern MemoryInt EepromTotalWorkServo;
        extern MemoryShort EepromActivitiesServoPerDay;
        extern MemoryByte EepromMode;
        extern MemoryByte EepromFrequency;
        extern MemoryShort EepromRotateAngle;
        extern MemoryShort EepromMinPulseWidth;
        extern MemoryShort EepromMaxPulseWidth;
        extern MemoryShort EepromMinAnalogSig;
        extern MemoryShort EepromMidAnalogSig;
        extern MemoryShort EepromMaxAnalogSig;
        extern MemoryShort EepromCalibMinDeg;
        extern MemoryShort EepromCalibMidDeg;
        extern MemoryShort EepromCalibMaxDeg;
        extern MemoryShort EepromQuiteTopAdc;
        extern MemoryShort EepromQuiteBotAdc;
        extern MemoryByte EepromQuietDb;
        extern MemoryShort EepromLoudTopAdc;
        extern MemoryShort EepromLoudBotAdc;
        extern MemoryByte EepromLoudDb;
        extern MemoryShort EepromStartPosition;
        extern MemoryByte EepromMaxAmplitude;
        extern MemoryShort EepromMinDelaySlow;
        extern MemoryShort EepromMaxDelaySlow;
        extern MemoryShort EepromBetweenDelayMinSlow;
        extern MemoryShort EepromBetweenDelayMaxSlow;
        extern MemoryByte EepromIncrementSlow;
        extern MemoryFloatArray EepromAccelerationModelSlow;
        extern MemoryShort EepromMinDelayFast;
        extern MemoryShort EepromMaxDelayFast;
        extern MemoryShort EepromBetweenDelayMinFast;
        extern MemoryShort EepromBetweenDelayMaxFast;
        extern MemoryByte EepromIncrementFast;
        extern MemoryFloatArray EepromAccelerationModelFast;
        extern MemoryByte EepromWirelessMode;
        extern MemoryByte EepromApChannel;
        extern MemoryString EepromApSsid;
        extern MemoryString EepromApPassword;
        extern MemoryBool EepromApHiddenSsid;
        extern MemoryBool EepromApStaticNetworkConfig;
        extern MemoryByteArray EepromApIp;
        extern MemoryByteArray EepromApGateway;
        extern MemoryByteArray EepromApMask;
        extern MemoryByteArray EepromApMac;
        extern MemoryString EepromStaSsid;
        extern MemoryByte EepromStaEncryptionType;
        extern MemoryString EepromStaPassword;
        extern MemoryBool EepromStaStaticNetworkConfig;
        extern MemoryByteArray EepromStaIp;
        extern MemoryByteArray EepromStaGateway;
        extern MemoryByteArray EepromStaMask;
        extern MemoryByteArray EepromStaMac;
        extern MemoryString EepromName;
        extern MemoryByte EepromDemoMode;
        extern MemoryByte EepromDemoDurationWork;
        extern MemoryByte EepromDemoDurationBreak;
        extern MemoryShort EepromBeginDemoWorkTime;
        extern MemoryShort EepromEndDemoWorkTime;
        extern MemoryBool EepromVoiceStart;
        extern MemoryBool EepromVoiceStop;
        extern MemoryByte EepromVoiceProgramNumber;
        extern MemoryByte EepromIntervalVoiceCommands;
        extern MemoryByte EepromSensitiveVoice;
        extern MemoryUInt EepromMechanicalStart;
        extern MemoryByteArray EepromArhiveArray;
    // Объявление переменных энергонезависимой памяти
        extern String deviceSerialNumber;
        extern byte controllerSerialNumber[];
        extern int buildDate;
        extern int maintenanceDate;
        extern int lastServiceDate;
        extern int totalWork;
        extern byte workTime;
        extern byte timePassed;
        extern int totalWorkServo;
        extern short activitiesServoPerDay;
        extern byte mode;
        extern byte frequency;
        extern short rotateAngle;
        extern short minPulseWidth;
        extern short maxPulseWidth;
        extern short minAnalogSig;
        extern short midAnalogSig;
        extern short maxAnalogSig;
        extern short calibMinDeg;
        extern short calibMidDeg;
        extern short calibMaxDeg;
        extern short quiteTopAdc;
        extern short quiteBotAdc;
        extern byte quietDb;
        extern short loudTopAdc;
        extern short loudBotAdc;
        extern byte loudDb;
        extern short startPosition;
        extern byte maxAmplitude;
        extern short minDelaySlow;
        extern short maxDelaySlow;
        extern short betweenDelayMinSlow;
        extern short betweenDelayMaxSlow;
        extern byte incrementSlow;
        extern float accelerationModelSlow[];
        extern short minDelayFast;
        extern short maxDelayFast;
        extern short betweenDelayMinFast;
        extern short betweenDelayMaxFast;
        extern byte incrementFast;
        extern float accelerationModelFast[];
        extern byte wirelessMode;
        extern byte apChannel;
        extern String apSsid;
        extern String apPassword;
        extern bool apHiddenSsid;
        extern bool apStaticNetworkConfig;
        extern byte apIp[];
        extern byte apGateway[];
        extern byte apMask[];
        extern byte apMac[];
        extern String staSsid;
        extern byte staEncryptionType;
        extern String staPassword;
        extern bool staStaticNetworkConfig;
        extern byte staIp[];
        extern byte staGateway[];
        extern byte staMask[];
        extern byte staMac[];
        extern String name;
        extern byte demoMode;
        extern byte demoDurationWork;
        extern byte demoDurationBreak;
        extern short beginDemoWorkTime;
        extern short endDemoWorkTime;
        extern bool voiceStart;
        extern bool voiceStop;
        extern byte voiceProgramNumber;
        extern byte intervalVoiceCommands;
        extern byte sensitiveVoice;
        extern unsigned int mechanicalStart;
        extern byte arhiveArray[];
    // Глобальные функции
        void BeginEeprom();
        void ReadEeprom();
        void WriteFactoryCluster();
        void WriteInstallationCluster();
        void WriteWirelessCluster(byte _wirelessMode);
        void FormatFactoryCluster();
        void FormatInstalationCluster();
        void FormatUserCluster();
        void FormatProg();
        void FormatWirelessCluster();
        void SaveDemoSetup();
#endif