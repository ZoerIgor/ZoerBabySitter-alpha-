// Включения
    #include "FUNC_Eeprom.h"
// Обозначения
    #define DEBUG
    #define DELAY 500
    #define SIZE_IP 4
    #define SIZE_ACC_MODEL 5
    #define SIZE_MAC 6
    #define SIZE_TOTAL_EEPROM 512
// Инициализация экземпляров классов энергонезависимой памяти
    MemoryService EepromService;
    MemoryString EepromDeviceSerialNumber(0);
    MemoryByteArray EepromControllerSerialNumber(13, SIZE_MAC);
    MemoryInt EepromBuildDate(19);
    MemoryInt EepromMaintenanceDate(23);
    MemoryInt EepromLastServiceDate(27);
    MemoryInt EepromTotalWork(31);
    MemoryByte EepromWorkTime(35);
    MemoryByte EepromTimePassed(36);
    MemoryInt EepromTotalWorkServo(37);
    MemoryShort EepromActivitiesServoPerDay(41);
    MemoryByte EepromMode(43);
    MemoryByte EepromFrequency(44);
    MemoryShort EepromRotateAngle(45);
    MemoryShort EepromMinPulseWidth(47);
    MemoryShort EepromMaxPulseWidth(49);
    MemoryShort EepromMinAnalogSig(51);
    MemoryShort EepromMidAnalogSig(53);
    MemoryShort EepromMaxAnalogSig(55);
    MemoryShort EepromCalibMinDeg(57);
    MemoryShort EepromCalibMidDeg(59);
    MemoryShort EepromCalibMaxDeg(61);
    MemoryShort EepromQuiteTopAdc(63);
    MemoryShort EepromQuiteBotAdc(65);
    MemoryByte EepromQuietDb(67);
    MemoryShort EepromLoudTopAdc(68);
    MemoryShort EepromLoudBotAdc(70);
    MemoryByte EepromLoudDb(72);
    MemoryShort EepromStartPosition(73);
    MemoryByte EepromMaxAmplitude(75);
    MemoryShort EepromMinDelaySlow(76);
    MemoryShort EepromMaxDelaySlow(78);
    MemoryShort EepromBetweenDelayMinSlow(80);
    MemoryShort EepromBetweenDelayMaxSlow(82);
    MemoryByte EepromIncrementSlow(84);
    MemoryFloatArray EepromAccelerationModelSlow(85, SIZE_ACC_MODEL);
    MemoryShort EepromMinDelayFast(105);
    MemoryShort EepromMaxDelayFast(107);
    MemoryShort EepromBetweenDelayMinFast(109);
    MemoryShort EepromBetweenDelayMaxFast(111);
    MemoryByte EepromIncrementFast(113);
    MemoryFloatArray EepromAccelerationModelFast(114, SIZE_ACC_MODEL);
    MemoryByte EepromWirelessMode(134);
    MemoryByte EepromApChannel(135);
    MemoryString EepromApSsid(136);
    MemoryString EepromApPassword(160);
    MemoryBool EepromApHiddenSsid(184);
    MemoryBool EepromApStaticNetworkConfig(185);
    MemoryByteArray EepromApIp(186, SIZE_IP);
    MemoryByteArray EepromApGateway(190, SIZE_IP);
    MemoryByteArray EepromApMask(194, SIZE_IP);
    MemoryByteArray EepromApMac(198, SIZE_MAC);
    MemoryString EepromStaSsid(204);
    MemoryByte EepromStaEncryptionType(228);
    MemoryString EepromStaPassword(229);
    MemoryBool EepromStaStaticNetworkConfig(253);
    MemoryByteArray EepromStaIp(254, SIZE_IP);
    MemoryByteArray EepromStaGateway(258, SIZE_IP);
    MemoryByteArray EepromStaMask(262, SIZE_IP);
    MemoryByteArray EepromStaMac(266, SIZE_MAC);
    MemoryString EepromName(272);
    MemoryByte EepromDemoMode(302);
    MemoryByte EepromDemoDurationWork(303);
    MemoryByte EepromDemoDurationBreak(304);
    MemoryShort EepromBeginDemoWorkTime(305);
    MemoryShort EepromEndDemoWorkTime(307);
    MemoryBool EepromVoiceStart(309);
    MemoryBool EepromVoiceStop(310);
    MemoryByte EepromVoiceProgramNumber(311);
    MemoryByte EepromIntervalVoiceCommands(312);
    MemoryByte EepromSensitiveVoice(313);
    MemoryUInt EepromMechanicalStart(314);
    MemoryByteArray EepromArhiveArray(ADDRESS_PROGRAM_ARHIVE, SIZE_PROGRAM_ARHIVE);
// Инициализация переменных энергонезависимой памяти
    // Сектор service
        String deviceSerialNumber = "";
        byte controllerSerialNumber[SIZE_MAC] = {0};
        int buildDate = 0;
        int maintenanceDate = 0;
        int lastServiceDate = 0;
        int totalWork = 0;
        byte workTime = 0;
        byte timePassed = 0;
        int totalWorkServo = 0;
        short activitiesServoPerDay = 0;
        byte mode = 0;
    // Сектор factory
        byte frequency;
        short rotateAngle;
        short minPulseWidth;
        short maxPulseWidth;
        short minAnalogSig;
        short midAnalogSig;
        short maxAnalogSig;
        short calibMinDeg;
        short calibMidDeg;
        short calibMaxDeg;
        short quiteTopAdc;
        short quiteBotAdc;
        byte quietDb;
        short loudTopAdc;
        short loudBotAdc;
        byte loudDb;
    // Сектор Installation
        short startPosition;
        byte maxAmplitude;
        short minDelaySlow;
        short maxDelaySlow;
        short betweenDelayMinSlow;
        short betweenDelayMaxSlow;
        byte incrementSlow;
        float accelerationModelSlow[SIZE_ACC_MODEL];
        short minDelayFast;
        short maxDelayFast;
        short betweenDelayMinFast;
        short betweenDelayMaxFast;
        byte incrementFast;
        float accelerationModelFast[SIZE_ACC_MODEL];
    // Сектор Wireless
        byte wirelessMode;
        byte apChannel;
        String apSsid;
        String apPassword;
        bool apHiddenSsid;
        bool apStaticNetworkConfig;
        byte apIp[SIZE_IP];
        byte apGateway[SIZE_IP];
        byte apMask[SIZE_IP];
        byte apMac[SIZE_MAC];
        String staSsid;
        byte staEncryptionType;
        String staPassword;
        bool staStaticNetworkConfig;
        byte staIp[SIZE_IP];
        byte staGateway[SIZE_IP];
        byte staMask[SIZE_IP];
        byte staMac[SIZE_MAC];
    // Сектор User
        String name;
        byte demoMode;
        byte demoDurationWork;
        byte demoDurationBreak;
        short beginDemoWorkTime;
        short endDemoWorkTime;
        bool voiceStart;
        bool voiceStop;
        byte voiceProgramNumber;
        byte intervalVoiceCommands;
        byte sensitiveVoice;
        unsigned int mechanicalStart;
        byte arhiveArray[SIZE_PROGRAM_ARHIVE];
    // Посекторная инициализация переменных
    void DefaultValuesFactoryCluster()
    {
        frequency = 0;
        rotateAngle = 0;
        minPulseWidth = 0;
        maxPulseWidth = 0;
        minAnalogSig = 0;
        midAnalogSig = 0;
        maxAnalogSig = 0;
        calibMinDeg = 0;
        calibMidDeg = 0;
        calibMaxDeg = 0;
        quiteTopAdc = 0;
        quiteBotAdc = 0;
        quietDb = 0;
        loudTopAdc = 0;
        loudBotAdc = 0;
        loudDb = 0;
    }
    void DefaultValuesInstallationCluster()
    {
        startPosition = 0;
        maxAmplitude = 0;
        minDelaySlow = 0;
        maxDelaySlow = 0;
        betweenDelayMinSlow = 0;
        betweenDelayMaxSlow = 0;
        incrementSlow = 0;
        for (auto i = 0; i < SIZE_ACC_MODEL; i++){accelerationModelSlow[i] = {0};}
        minDelayFast = 0;
        maxDelayFast = 0;
        betweenDelayMinFast = 0;
        betweenDelayMaxFast = 0;
        incrementFast = 0;
        for (auto i = 0; i < SIZE_ACC_MODEL; i++){accelerationModelFast[i] = {0};}
    }
    void DefaultValuesWirelessCluster()
    {
        wirelessMode = 0;
        apChannel = 0;
        apSsid = "";
        apPassword = "";
        apHiddenSsid = false;
        apStaticNetworkConfig = false;
        for (auto i = 0; i < SIZE_IP; i++){apIp[i] = {0};}
        for (auto i = 0; i < SIZE_IP; i++){apGateway[i] = {0};}
        for (auto i = 0; i < SIZE_IP; i++){apMask[i] = {0};}
        for (auto i = 0; i < SIZE_MAC; i++){apMac[i] = {0};}
        staSsid = "";
        staEncryptionType = 0;
        staPassword = "";
        staStaticNetworkConfig = false;
        for (auto i = 0; i < SIZE_IP; i++){staIp[i] = {0};}
        for (auto i = 0; i < SIZE_IP; i++){staGateway[i] = {0};}
        for (auto i = 0; i < SIZE_IP; i++){staMask[i] = {0};}
        for (auto i = 0; i < SIZE_MAC; i++){staMac[i] = {0};}
    }
    void DefaultValuesUserCluster()
    {
        name = "";
        demoMode = 0;
        demoDurationWork = 0;
        demoDurationBreak = 0;
        beginDemoWorkTime = 0;
        endDemoWorkTime = 0;
        voiceStart = false;
        voiceStop = false;
        voiceProgramNumber = 0;
        intervalVoiceCommands = 0;
        sensitiveVoice = 0;
        mechanicalStart = BILLION;
        for (auto i = 0; i < SIZE_PROGRAM_ARHIVE; i++){arhiveArray[i] = {0};}
    }
// Функции
void WriteSerialNumber()
{
    String serialNumber = "";
    char hiBytes[5];
    char lowBytes[9];
    snprintf(hiBytes, 5, "%04X", (uint16_t)(ESP.getEfuseMac() >> 32));
    for (int i = 0; i < strlen(hiBytes); i++)
    {
        serialNumber += hiBytes[i];
    }
    snprintf(lowBytes, 9, "%08X", (uint32_t)(ESP.getEfuseMac()));
    for (int i = 0; i < strlen(lowBytes); i++)
    {
        serialNumber += lowBytes[i];
    }
    HexStringToByteArray(serialNumber, controllerSerialNumber, 6);
    EepromControllerSerialNumber.set(controllerSerialNumber);
}
void BeginEeprom()
{
    if (!EEPROM.begin(SIZE_TOTAL_EEPROM))
    {
        #ifdef DEBUG
            Serial.println("Failed to initialise EEPROM");
            Serial.println("Restarting...");
            Serial.println("-------------------------------");
        #endif
        ESP.restart();
    }
    delay(DELAY);
    #ifdef DEBUG // Не актуальны
        EepromService.setCluster(MEMORY_ALL, 0, (SIZE_TOTAL_EEPROM - 1));
        EepromService.setCluster(MEMORY_SERVICE, 0, 43);
        EepromService.setCluster(MEMORY_FACTORY, 44, 72);
        EepromService.setCluster(MEMORY_INSTALATION, 73, 133);
        EepromService.setCluster(MEMORY_WIRELESS, 134, 271);
        EepromService.setCluster(MEMORY_USER, 272, 510);
    #endif
    DefaultValuesFactoryCluster();
    DefaultValuesInstallationCluster();
    DefaultValuesWirelessCluster();
    DefaultValuesUserCluster();
    if (EepromControllerSerialNumber.get(controllerSerialNumber) == (255 * EepromControllerSerialNumber.getLenght()))
    {
        WriteSerialNumber();
        EepromControllerSerialNumber.set(controllerSerialNumber);
    }
}
void WriteServiceCluster()
{
    EepromDeviceSerialNumber.set(deviceSerialNumber);
    EepromControllerSerialNumber.set(controllerSerialNumber);
    EepromBuildDate.set(buildDate);
    EepromMaintenanceDate.set(maintenanceDate);
    EepromLastServiceDate.set(lastServiceDate);
    EepromTotalWork.set(totalWork);
    EepromWorkTime.set(workTime);
    EepromTimePassed.set(timePassed);
    EepromTotalWorkServo.set(totalWorkServo);
    EepromActivitiesServoPerDay.set(activitiesServoPerDay);
    EepromMode.set(mode);
}
void WriteFactoryCluster()
{
    EepromFrequency.set(frequency);
    EepromRotateAngle.set(rotateAngle);
    EepromMinPulseWidth.set(minPulseWidth);
    EepromMaxPulseWidth.set(maxPulseWidth);
    EepromMinAnalogSig.set(minAnalogSig);
    EepromMidAnalogSig.set(midAnalogSig);
    EepromMaxAnalogSig.set(maxAnalogSig);
    EepromCalibMinDeg.set(calibMinDeg);
    EepromCalibMidDeg.set(calibMidDeg);
    EepromCalibMaxDeg.set(calibMaxDeg);
    EepromQuiteTopAdc.set(quiteTopAdc);
    EepromQuiteBotAdc.set(quiteBotAdc);
    EepromQuietDb.set(quietDb);
    EepromLoudTopAdc.set(loudTopAdc);
    EepromLoudBotAdc.set(loudBotAdc);
    EepromLoudDb.set(loudDb);
}
void WriteInstallationCluster()
{
    EepromStartPosition.set(startPosition);
    EepromMaxAmplitude.set(maxAmplitude);
    EepromMinDelaySlow.set(minDelaySlow);
    EepromMaxDelaySlow.set(maxDelaySlow);
    EepromBetweenDelayMinSlow.set(betweenDelayMinSlow);
    EepromBetweenDelayMaxSlow.set(betweenDelayMaxSlow);
    EepromIncrementSlow.set(incrementSlow);
    EepromAccelerationModelSlow.set(accelerationModelSlow);
    EepromMinDelayFast.set(minDelayFast);
    EepromMaxDelayFast.set(maxDelayFast);
    EepromBetweenDelayMinFast.set(betweenDelayMinFast);
    EepromBetweenDelayMaxFast.set(betweenDelayMaxFast);
    EepromIncrementFast.set(incrementFast);
    EepromAccelerationModelFast.set(accelerationModelFast);
}
void WriteUserCluster()
{
    EepromName.set(name);
    EepromDemoMode.set(demoMode);
    EepromDemoDurationWork.set(demoDurationWork);
    EepromDemoDurationBreak.set(demoDurationBreak);
    EepromBeginDemoWorkTime.set(beginDemoWorkTime);
    EepromEndDemoWorkTime.set(endDemoWorkTime);
    EepromVoiceStart.set(voiceStart);
    EepromVoiceStop.set(voiceStop);
    EepromVoiceProgramNumber.set(voiceProgramNumber);
    EepromIntervalVoiceCommands.set(intervalVoiceCommands);
    EepromSensitiveVoice.set(sensitiveVoice);
    EepromMechanicalStart.set(mechanicalStart);
    EepromArhiveArray.set(arhiveArray);
}
void WriteWirelessStaSettings()
{
    EepromStaSsid.set(staSsid);
    EepromStaEncryptionType.set(staEncryptionType);
    EepromStaPassword.set(staPassword);
    EepromStaStaticNetworkConfig.set(staStaticNetworkConfig);
    EepromStaIp.set(staIp);
    EepromStaGateway.set(staGateway);
    EepromStaMask.set(staMask);
    EepromStaMac.set(staMac);
}
void WriteWirelessApSettings()
{
    EepromApChannel.set(apChannel);
    EepromApSsid.set(apSsid);
    EepromApPassword.set(apPassword);
    EepromApHiddenSsid.set(apHiddenSsid);
    EepromApStaticNetworkConfig.set(apStaticNetworkConfig);
    EepromApIp.set(apIp);
    EepromApGateway.set(apGateway);
    EepromApMask.set(apMask);
    EepromApMac.set(apMac);
}
void WriteWirelessCluster(byte _wirelessMode)
{
    EepromWirelessMode.set(_wirelessMode);
    if (_wirelessMode != WIRELESS_STA)
    {
        WriteWirelessApSettings();
    }
    if (_wirelessMode != WIRELESS_AP)
    {
        WriteWirelessStaSettings();
    }
}
void WriteEeprom()
{
    WriteServiceCluster();
    WriteFactoryCluster();
    WriteInstallationCluster();
    WriteWirelessCluster(wirelessMode);
    WriteUserCluster();
}
void ReadEeprom()
{
    if (EepromMode.get() == MODE_NONE)
    {
        mode = MODE_FACTORY;
        WriteEeprom();
        delay(DELAY);
        ESP.restart();
    }
    else
    {
        deviceSerialNumber = EepromDeviceSerialNumber.get();
        EepromControllerSerialNumber.get(controllerSerialNumber);
        buildDate = EepromBuildDate.get();
        maintenanceDate = EepromMaintenanceDate.get();
        lastServiceDate = EepromLastServiceDate.get();
        totalWork = EepromTotalWork.get();
        workTime = EepromWorkTime.get();
        timePassed = EepromTimePassed.get();
        totalWorkServo = EepromTotalWorkServo.get();
        activitiesServoPerDay = EepromActivitiesServoPerDay.get();
        mode = EepromMode.get();
        frequency = EepromFrequency.get();
        rotateAngle = EepromRotateAngle.get();
        minPulseWidth = EepromMinPulseWidth.get();
        maxPulseWidth = EepromMaxPulseWidth.get();
        minAnalogSig = EepromMinAnalogSig.get();
        midAnalogSig = EepromMidAnalogSig.get();
        maxAnalogSig = EepromMaxAnalogSig.get();
        calibMinDeg = EepromCalibMinDeg.get();
        calibMidDeg = EepromCalibMidDeg.get();
        calibMaxDeg = EepromCalibMaxDeg.get();
        quiteTopAdc = EepromQuiteTopAdc.get();
        quiteBotAdc = EepromQuiteBotAdc.get();
        quietDb = EepromQuietDb.get();
        loudTopAdc = EepromLoudTopAdc.get();
        loudBotAdc = EepromLoudBotAdc.get();
        loudDb = EepromLoudDb.get();
        startPosition = EepromStartPosition.get();
        maxAmplitude = EepromMaxAmplitude.get();
        minDelaySlow = EepromMinDelaySlow.get();
        maxDelaySlow = EepromMaxDelaySlow.get();
        betweenDelayMinSlow = EepromBetweenDelayMinSlow.get();
        betweenDelayMaxSlow = EepromBetweenDelayMaxSlow.get();
        incrementSlow = EepromIncrementSlow.get();
        EepromAccelerationModelSlow.get(accelerationModelSlow);
        minDelayFast = EepromMinDelayFast.get();
        maxDelayFast = EepromMaxDelayFast.get();
        betweenDelayMinFast = EepromBetweenDelayMinFast.get();
        betweenDelayMaxFast = EepromBetweenDelayMaxFast.get();
        incrementFast = EepromIncrementFast.get();
        EepromAccelerationModelFast.get(accelerationModelFast);
        wirelessMode = EepromWirelessMode.get();
        apChannel = EepromApChannel.get();
        apSsid = EepromApSsid.get();
        apPassword = EepromApPassword.get();
        apHiddenSsid = EepromApHiddenSsid.get();
        apStaticNetworkConfig = EepromApStaticNetworkConfig.get();
        EepromApIp.get(apIp);
        EepromApGateway.get(apGateway);
        EepromApMask.get(apMask);
        EepromApMac.get(apMac);
        staSsid = EepromStaSsid.get();
        staEncryptionType = EepromStaEncryptionType.get();
        staPassword = EepromStaPassword.get();
        staStaticNetworkConfig = EepromStaStaticNetworkConfig.get();
        EepromStaIp.get(staIp);
        EepromStaGateway.get(staGateway);
        EepromStaMask.get(staMask);
        EepromStaMac.get(staMac);
        name = EepromName.get();
        demoMode = EepromDemoMode.get();
        demoDurationWork = EepromDemoDurationWork.get();
        demoDurationBreak = EepromDemoDurationBreak.get();
        beginDemoWorkTime = EepromBeginDemoWorkTime.get();
        endDemoWorkTime = EepromEndDemoWorkTime.get();
        voiceStart = EepromVoiceStart.get();
        voiceStop = EepromVoiceStop.get();
        voiceProgramNumber = EepromVoiceProgramNumber.get();
        intervalVoiceCommands = EepromIntervalVoiceCommands.get();
        sensitiveVoice = EepromSensitiveVoice.get();
        mechanicalStart = EepromMechanicalStart.get();
        EepromArhiveArray.get(arhiveArray);
    }
}
void FormatFactoryCluster()
{
    DefaultValuesFactoryCluster();
    WriteFactoryCluster();
    EepromMode.set(MODE_FACTORY);
}
void FormatInstalationCluster()
{
    DefaultValuesInstallationCluster();
    WriteInstallationCluster();
    EepromMode.set(MODE_INSTALATION);
}
void FormatUserCluster()
{
    DefaultValuesUserCluster();
    WriteUserCluster();
}
void FormatProg()
{
    for (auto i = 0; i < SIZE_PROGRAM_ARHIVE; i++)
    {
        arhiveArray[i] = {0};
    }
    EepromArhiveArray.set(arhiveArray);
}
void FormatWirelessCluster()
{
    DefaultValuesWirelessCluster();
    WriteWirelessCluster(wirelessMode);
}
void SaveDemoSetup()
{
    EepromDemoMode.set(demoMode);
    EepromDemoDurationWork.set(demoDurationWork);
    EepromDemoDurationBreak.set(demoDurationBreak);
    if (demoMode == DEMO_MODE_TIMETABLE)
    {
        EepromBeginDemoWorkTime.set(beginDemoWorkTime);
        EepromEndDemoWorkTime.set(endDemoWorkTime);
    }
}