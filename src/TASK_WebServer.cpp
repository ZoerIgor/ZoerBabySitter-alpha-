#include "TASK_WebServer.h"
#define DEBUG0
// Объявления
    #define bufferMax 512 //256
    bool request = false;
    bool runServer;
    char post;
    byte pageNumber = 255;
    byte previousPage = 255;
    int tryNumber = 0;
    String buffer;
    WiFiServer Server(80);
    //WiFiClient Client;
    IPAddress prevClient(0, 0, 0, 0);
// Вспомогательные функции
ReadBuffer::ReadBuffer(){}
String ReadBuffer::getName(String buffer, byte inputNumber)
{
    String value = "";
    byte counter = 1;
    for(int i = 0; i < buffer.length(); i++)
    {
        if (buffer[i] == '=')
        {
            if (inputNumber == counter)
            {
                break;
            }
        }
        else if (buffer[i] == '&')
        {
            counter++;
            value = "";
            i++;
        }
        value += buffer[i];
    }
    return value;
}
String ReadBuffer::get(String buffer, byte inputNumber)
{
    this->buffer = buffer;
    value = "";
    indexNumber = 1;
    answer = false;
    endRequest = false;
    for(int i = 0; i < buffer.length(); i++)
    {
        if(endRequest)
        {
            answer = true;
            endRequest = false;
        }
        if(buffer[i] == '=')
        {
            endRequest = true;
        }
        else if(buffer[i] == '&')
        {
            answer = false;
            indexNumber++;
        }
        if(answer || endRequest)
        {
            if(inputNumber == indexNumber)
            {
                if(buffer[i] != '=')
                {
                    value = value + buffer[i];
                }
            }
        }
    }
    return value;
}
ReadBuffer ReadBuff;
float DecimalFraction(String &value1, String &value2, String &value3)
{
    float value = 0;
    value += value1.toInt();
    if(value2.toInt() < 9)
    {
        if(value3.toInt() > 0)
        {
            value2 = String(value2.toInt() + 1, DEC);
        }
    }
    value += value2.toInt();
    return value;
}
String LoadGeneralHtml(byte page)
{
    String html;
    vTaskDelay(DELAY_DECISEC);
    switch(page)
    {
        case HTML_WIFI:
            html = Page_WiFi();
            break;
        case HTML_AP:
            html = Page_UserAp();
            break;
        case HTML_WIRELESS_MODE:
            html = Page_WirelessMode();
            break;
        case HTML_LOADING:
            html = Page_Loading();
            break;
        case HTML_CONTACTS:
            html = Page_Contacts();
            break;
    }
    return html;
}
String LoadFactoryHTML(byte page)
{
    String html;
    vTaskDelay(DELAY_DECISEC);
    switch(page)
    {
        case HTML_MAIN:
            html = Page_SerialNumber();
            break;
        case HTML_CONTACTS:
            html = Page_Contacts();
            break;
        case HTML_FACTORY_TEST_RESET_BUTTON:
            html = Page_Factory_TestFactoryButton();
            break;
        case HTML_FACTORY_TEST_RESET_BUTTON_HELP:
            html = Page_Factory_TestFactoryButtonHelp();
            break;
        case HTML_FACTORY_TEST_SERVO:
            html = Page_Factory_TestServo();
            break;
        case HTML_FACTORY_TEST_SERVO_HELP:
            html = Page_Factory_TestServoHelp();
            break;
        case HTML_FACTORY_REFERENCE_SERVO_DS329MG:
            html = Page_Factory_Reference_CoronaDS329MG();
            break;
        case HTML_FACTORY_CALIBRATE_SERVO:
            html = Page_Factory_CalibrateServo();
            break;
        case HTML_FACTORY_CALIBRATE_SERVO_HELP:
            html = Page_Factory_CalibrateServoHelp();
            break;
        case HTML_FACTORY_TEST_MAIN_BUTTON:
            html = Page_Factory_TestMainButton();
            break;
        case HTML_FACTORY_TEST_MAIN_BUTTON_HELP:
            html = Page_Factory_TestMainButtonHelp();
            break;
        case HTML_FACTORY_MIC:
            html = Page_Factory_TestMicrophone();
            break;
        case HTML_FACTORY_MIC_HELP:
            html = Page_Factory_TestMicrophoneHelp();
            break;
        case HTML_LOADING:
            html = Page_Loading();
            break;
    }
    return html;
}
String LoadInstalationHTML(byte page)
{
    String html;
    vTaskDelay(DELAY_DECISEC);
    switch(page)
    {
        case HTML_MAIN:
            html = Page_SerialNumber();
            break;
        case HTML_CONTACTS:
            html = Page_Contacts();
            break;
        case HTML_INSTALATION_REST_POSITION:
            html = Page_Installation_RestPosition();
            break;
        case HTML_INSTALATION_REST_POSITION_HELP:
            html = Page_Installation_RestPositionHelp();
            break;
        case HTML_INSTALATION_SETTING_MODE:
            html = Page_Installation_SettingMode();
            break;
        case HTML_INSTALATION_MANUAL_CALIB_AMP:
            html = Page_Installation_ManualCalibrateAmplitude();
            break;
        case HTML_INSTALATION_MANUAL_CALIB_AMP_HELP:
            html = Page_Installation_ManualCalibrateAmplitudeHelp();
            break;
        case HTML_INSTALATION_MANUAL_SLOW:
            html = Page_Installation_ManualSlow();
            break;
        case HTML_INSTALATION_MANUAL_SLOW_HELP:
            html = Page_Installation_ManualSlowHelp();
            break;
        case HTML_INSTALATION_MANUAL_FAST:
            html = Page_Installation_ManualFast();
            break;
        case HTML_INSTALATION_MANUAL_FAST_HELP:
            html = Page_Installation_ManualFastHelp();
            break;
        case HTML_INSTALATION_AUTO:
            html = Page_Installation_Auto();
            break;
        case HTML_INSTALATION_AUTO_HELP:
            html = Page_Installation_AutoHelp();
            break;
        default:
            html = LoadGeneralHtml(page);
            break;
    }
    return html;
}
String LoadUserHTML(byte page)
{
    String html;
    vTaskDelay(DELAY_DECISEC);
    switch(page)
    {
        case HTML_USER_MAIN_HELP:
            html = Page_User_MainMenuHelp();
            break;
        case HTML_USER_NAME:
            html = Page_User_Name();
            break;
        case HTML_USER_MANUAL_START:
            html = Page_User_ManualStart();
            break;
        case HTML_USER_RESET_WIRELESS:
            html = Page_User_ResetWireless();
            break;
        case HTML_USER_RESET_PROG:
            html = Page_User_ResetProg();
            break;
        case HTML_USER_RESET_USER:
            html = Page_User_ResetUser();
            break;
        case HTML_USER_RESET_INSTALLATION:
            html = Page_User_ResetInstallation();
            break;
        case HTML_USER_RESET_SETTINGS:
            html = Page_User_ResetSettings();
            break;
        case HTML_USER_RESET_SETTINGS_HELP:
            html = Page_User_ResetSettingsHelp();
            break;
        case HTML_USER_DEMO_SETUP:
            html = Page_User_Demo();
            break;    
        case HTML_USER_SETTINGS:
            html = Page_User_Settings();
            break;
        case HTML_USER_PROGRAM_OPTIONS:
            html = Page_User_ProgramOptions();
            break;
        case HTML_USER_PROGRAM_OPTIONS_HELP:
            html = Page_User_ProgramOptionsHelp();
            break;
        case HTML_USER_CALIBRATION_REST:
            html = Page_User_CalibrateAmplitude();
            break;
        case HTML_MAIN:
            vTaskDelay(DELAY_DECISEC);
            html = Page_User_MainMenu();
            break;
        default:
            html = LoadGeneralHtml(page);
            break;
    }
    return html;
}
void EasyAccess()
{
    breakAction = false;
    reloadPage = false;
    loadNextPage = true;
    pageYOffset = 0;
}
void PassWithDeferredVerification()
{
    breakAction = false;
    reloadPage = false;
    loadNextPage = false;
    pageYOffset = 0;
}
void GettingAccess(short readBuff)
{
    breakAction = false;
    reloadPage = true;
    loadNextPage = false;
    pageYOffset = readBuff;
}
void PassageAllowed(short readBuff)
{
    breakAction = false;
    reloadPage = true;
    loadNextPage = true;
    pageYOffset = readBuff;
}
void AbortedAccess(short readBuff)
{
    breakAction = true;
    reloadPage = true;
    loadNextPage = false;
    pageYOffset = readBuff;
}
void ThreeWaysTwoDirections(bool &var, byte testDevice, byte mode, byte page, short buff)
{
    if(var)
    {

        if(event == mode)
        {
            switch(testDevice)
            {
                case 0:
                    SERVO_MAIN.interruptCycle();
                    break;
                case 1:
                    testFactoryButton = false;
                    break;
                case 2:
                    testMainButton = false;
                    break;
                default:
                    break;
            }
            event = EVENT_SHUTDOWN;
            var = false;
            AbortedAccess(buff);
        }
        else
        {
            EasyAccess();
            pageNumber = page;
        }
    }
    else
    {
        bool sw = false;
        switch(testDevice)
        {
            case 1:
                if(testFactoryButton)
                {
                    sw = true;
                }
                break;
            case 2:
                if(testMainButton)
                {
                    sw = true;
                }
                break;
            default:
                break;
        }
        if(sw)
        {
            EasyAccess();
            pageNumber = page;
        }
        else
        {
            AbortedAccess(buff);
        }
    }
}
// Задача
void TASK_WebServer( void * pvParameters)
{
    // Отладка
    #ifdef DEBUG
        Serial.print("Start task:\t");
        Serial.println("WEB SERVER");
        Serial.println("-------------------------------");
    #endif
    // Основной цикл задачи
    for(;;)
    {
        // Попытка подключения по беспроводной сети
        if(WirelessStatus() == false)
        {
            // Остановка сервера если нет соединения
            if(runServer == true)
            {
                //Server.stop();
                runServer = false;
                digitalWrite(LED_BUILTIN, LOW);
                tryNumber = 0;
                #ifdef DEBUG
                    Serial.println("Disconnected");
                    Serial.println("-------------------------------");
                #endif
            }
            Wireless(wirelessMode);
            if(tryNumber++ % 2 == 0)
            {
                digitalWrite(LED_BUILTIN, HIGH);
            }
            else
            {
                digitalWrite(LED_BUILTIN, LOW);
            }
            #ifdef DEBUG
                Serial.print("Try connection:\t");
                Serial.println(tryNumber);
                Serial.println("-------------------------------");
            #endif
            vTaskDelay(DELAY_SEC);
        }
        // Запуск сервера
        if(WirelessStatus() == true && runServer == false)
        {
            Server.begin();
            runServer = true;
            digitalWrite(LED_BUILTIN, HIGH);
            tryNumber = 0;
            #ifdef DEBUG
                Serial.println("Сonnected");
                Serial.println("-------------------------------");
                tryNumber = 0;
            #endif
        }
        // Сессия обмена данными (начало)
        if(runServer == true)
        {
            WiFiClient Client = Server.available();
            if(Client)
            {
                /* if (request)
                {
                    request = false;
                    Serial.println("Answer");
                }
                else
                {
                    Serial.println("Request");
                }
                Serial.println("Start session"); */
                boolean currentLineIsBlank = true;
                buffer = String("");
                while(Client.connected())
                {
                    char c = Client.read();
                    #ifdef DEBUG
                        Serial.write(c);
                    #endif
                    if(c == '\n' && currentLineIsBlank)
                    {
                        while(Client.available())
                        {
                            post = Client.read();  
                            if(buffer.length() <= bufferMax)
                            {
                                buffer += post;
                            }
                            if (!request)
                            {
                                request = true;
                            }
                        }
                        // Отправка заголовка
                        Client.println("HTTP/1.1 200 OK");
                        Client.println("Content-Type: text/html");
                        Client.print("Connection: close\r\n\r\n");
                        // Реализация сайта
                        if(buffer.indexOf("SERIAL_NUMBER") >= 0)
                        {
                            EasyAccess();
                            pageNumber = HTML_MAIN;
                        }
                        if(buffer.indexOf("CONTACTS") >= 0)
                        {  
                            EasyAccess();
                            pageNumber = HTML_CONTACTS;
                        }
                        if(buffer.indexOf("WIRELESS_MODE") >= 0)
                        {
                            if(mode == MODE_INSTALATION)
                            {
                                if(fastMoTestComplite)
                                {
                                    pageNumber = HTML_WIRELESS_MODE;
                                }
                                else
                                {
                                    AbortedAccess(ReadBuff.get(buffer, 2).toInt());
                                }
                            }
                            else
                            {
                                pageNumber = HTML_WIRELESS_MODE;
                            }
                        }
                        if(buffer.indexOf("CHANGE_USER_AP") >= 0)
                        {
                            pageNumber = HTML_AP;
                        }
                        if(buffer.indexOf("CHANGE_WIFI") >= 0)
                        {
                            pageNumber = HTML_WIFI;
                        }
                        if(buffer.indexOf("SAVE_AP") >= 0)
                        {
                            wirelessMode = WIRELESS_AP;
                            apSsid = ReadBuff.get(buffer, 1);
                            apPassword = ReadBuff.get(buffer, 2);
                            if(ReadBuff.get(buffer, 3) == "auto")
                            {
                                apChannel = 0;
                            }
                            else
                            {
                                apChannel = ReadBuff.get(buffer, 3).toInt();
                            }
                            byte indexMac;
                            byte indexSet;
                            if(ReadBuff.get(buffer, 4) == "on")
                            {
                                apHiddenSsid = true;
                                indexMac = 5;
                                indexSet = 6;
                            }
                            else
                            {
                                apHiddenSsid = false;
                                indexMac = 4;
                                indexSet = 5;
                            }
                            String mac = ReadBuff.get(buffer, indexMac);
                            RemoveSeparators(mac);
                            HexStringToByteArray(mac, apMac, 6);
                            byte indexIp;
                            byte indexMask;
                            if(ReadBuff.get(buffer, indexSet) == "on")
                            {
                                if(indexSet == 5)
                                {
                                    indexIp = 6;
                                    indexMask = 7;
                                }
                                else
                                {
                                    indexIp = 7;
                                    indexMask = 8;
                                }
                                apStaticNetworkConfig = true;
                                String ip = ReadBuff.get(buffer, indexIp);
                                DecStringToByteArray(ip, apIp);
                                String mask = ReadBuff.get(buffer, indexMask);
                                DecStringToByteArray(mask, apMask);
                            }
                            else
                            {
                                apStaticNetworkConfig = false;
                            }
                            WriteWirelessCluster(wirelessMode);
                            if(mode == MODE_INSTALATION)
                            {
                                EepromMode.set(MODE_USER);
                                WriteInstallationCluster();
                            }
                            event = EVENT_RESTART;
                            pageNumber = HTML_LOADING;
                        }
                        if(buffer.indexOf("SAVE_STA") >= 0)
                        {
                            wirelessMode = WIRELESS_STA;
                            staSsid = ReadBuff.get(buffer, 1);
                            String encrypt = ReadBuff.get(buffer, 2);
                            if(encrypt == "OPEN")
                            {
                                staEncryptionType = ENCRYPT_OPEN;
                            }
                            else if(encrypt == "WEP64")
                            {
                                staEncryptionType = ENCRYPT_WEP64;
                            }
                            else if(encrypt == "WEP128")
                            {
                                staEncryptionType = ENCRYPT_WEP128;
                            }
                            else if(encrypt == "WPA")
                            {
                                staEncryptionType = ENCRYPT_WPA;
                            }
                            else if(encrypt == "WPA2")
                            {
                                staEncryptionType = ENCRYPT_WPA2;
                            }
                            else if(encrypt == "WPA_WPA2")
                            {
                                staEncryptionType = ENCRYPT_WPA_WPA2;
                            }
                            staPassword = ReadBuff.get(buffer, 3);
                            String mac = ReadBuff.get(buffer, 4);
                            RemoveSeparators(mac);
                            HexStringToByteArray(mac, staMac, 6);
                            if(ReadBuff.get(buffer, 5) == "on")
                            {
                                staStaticNetworkConfig = true;
                                String ip = ReadBuff.get(buffer, 6);
                                DecStringToByteArray(ip, staIp);
                                String mask = ReadBuff.get(buffer, 7);
                                DecStringToByteArray(mask, staMask);
                                String gateway = ReadBuff.get(buffer, 8);
                                DecStringToByteArray(gateway, staGateway);
                            }
                            else
                            {
                                staStaticNetworkConfig = false;
                            }
                            WriteWirelessCluster(wirelessMode);
                            if(mode == MODE_INSTALATION)
                            {
                                EepromMode.set(MODE_USER);
                                WriteInstallationCluster();
                            }
                            event = EVENT_RESTART;
                            pageNumber = HTML_LOADING;
                        }
                        switch (mode)
                        {
                            case MODE_FACTORY:
                            {
                                if(buffer.indexOf("FACTORY_BUTTON") >= 0)
                                {  
                                    if(deviceSerialNumber == "")
                                    {
                                        deviceSerialNumber = ReadBuff.get(buffer, 1);
                                    }
                                    if(testFactoryButton)
                                    {
                                        EasyAccess();
                                    }
                                    else
                                    {
                                        PassWithDeferredVerification();
                                    }
                                    pageNumber = HTML_FACTORY_TEST_RESET_BUTTON;
                                }
                                if(buffer.indexOf("HELP_FACTORY_BUTTON") >= 0)
                                {  
                                    if(event == EVENT_BUTTON_FACTORY_TEST)
                                    {
                                        event = EVENT_SHUTDOWN;
                                        onTestFactoryButton = false;
                                    }
                                    EasyAccess();
                                    pageNumber = HTML_FACTORY_TEST_RESET_BUTTON_HELP;
                                }
                                if(buffer.indexOf("TEST_FACTORY_BUTTON") >= 0)
                                {  
                                    if(event != EVENT_BUTTON_FACTORY_TEST)
                                    {
                                        onTestFactoryButton = true;
                                        testFactoryButton = false;
                                        BUTTON_FACTORY.resetPressStatus();
                                        PassageAllowed(ReadBuff.get(buffer, 2).toInt());
                                        event = EVENT_BUTTON_FACTORY_TEST;
                                    }
                                    else
                                    {
                                        onTestFactoryButton = false;
                                        testFactoryButton = false;
                                        GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                        event = EVENT_SHUTDOWN;
                                    }
                                }
                                if(buffer.indexOf("FACTORY_SERVO") >= 0)
                                {
                                    ThreeWaysTwoDirections(onTestFactoryButton, 1, EVENT_BUTTON_FACTORY_TEST, HTML_FACTORY_TEST_SERVO, ReadBuff.get(buffer, 2).toInt());
                                }
                                if(buffer.indexOf("HELP_SERVO") >= 0)
                                {
                                    EasyAccess();
                                    pageNumber = HTML_FACTORY_TEST_SERVO_HELP;
                                }
                                if(buffer.indexOf("CORONA_DS329MG") >= 0)
                                {
                                    EasyAccess();
                                    pageNumber = HTML_FACTORY_REFERENCE_SERVO_DS329MG;
                                }
                                if(buffer.indexOf("TEST_SERVO") >= 0)
                                {
                                    if(event != EVENT_SERVO_TEST)
                                    {
                                        frequency = ReadBuff.get(buffer, 1).toInt();
                                        rotateAngle = ReadBuff.get(buffer, 2).toInt();
                                        minPulseWidth = ReadBuff.get(buffer, 3).toInt();
                                        maxPulseWidth = ReadBuff.get(buffer, 4).toInt();
                                        delayPulse = ReadBuff.get(buffer, 5).toInt();
                                        delayBetween = ReadBuff.get(buffer, 6).toInt();
                                        event = EVENT_SERVO_TEST;
                                        testServo = true;
                                        PassageAllowed(ReadBuff.get(buffer, 8).toInt());
                                    }
                                    else
                                    {
                                        SERVO_MAIN.interruptCycle();
                                        event = EVENT_SHUTDOWN;
                                        testServo = false;
                                        GettingAccess(ReadBuff.get(buffer, 8).toInt());
                                    }
                                }
                                if(buffer.indexOf("CALIBRATE_SERVO") >= 0)
                                {
                                    ThreeWaysTwoDirections(testServo, 0, EVENT_SERVO_TEST, HTML_FACTORY_CALIBRATE_SERVO, ReadBuff.get(buffer, 2).toInt());
                                }
                                if(buffer.indexOf("READ_ANALOG_SERVO") >= 0)
                                {
                                    if(!SERVO_MAIN.getMinAnalog() && !SERVO_MAIN.getMidAnalog() && !SERVO_MAIN.getMaxAnalog())
                                    {
                                        event = EVENT_SERVO_CALIBRATE_MIN;
                                        GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                    }
                                    if(SERVO_MAIN.getMinAnalog() && !SERVO_MAIN.getMidAnalog() && !SERVO_MAIN.getMaxAnalog())
                                    {
                                        event = EVENT_SERVO_CALIBRATE_MID;
                                        GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                    }
                                    if(SERVO_MAIN.getMinAnalog() && SERVO_MAIN.getMidAnalog() && !SERVO_MAIN.getMaxAnalog())
                                    {
                                        event = EVENT_SERVO_CALIBRATE_MAX;
                                        GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                    }
                                }
                                if(buffer.indexOf("RESET_CALIBRATE") >= 0)
                                {
                                    SERVO_MAIN.resetAnalogSig();
                                    SERVO_MAIN.interruptCycle();
                                    event = EVENT_SHUTDOWN;
                                    sortBeforeCalibServ = false;
                                    calibrateServo = false;
                                    GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                }
                                if(buffer.indexOf("HELP_CALIBRATE_SERVO") >= 0)
                                {
                                    EasyAccess();
                                    pageNumber = HTML_FACTORY_CALIBRATE_SERVO_HELP;
                                }
                                if(buffer.indexOf("TEST_CALIBRATE_SERVO") >= 0)
                                {
                                    if(sortBeforeCalibServ && event != EVENT_SERVO_CALIBRATE_TEST)
                                    {
                                        event = EVENT_SERVO_CALIBRATE_TEST;
                                        calibrateServo = true;
                                        PassageAllowed(ReadBuff.get(buffer, 2).toInt());
                                    }
                                    else if(!sortBeforeCalibServ)
                                    {
                                        AbortedAccess(ReadBuff.get(buffer, 2).toInt());
                                    }
                                    else if(event == EVENT_SERVO_CALIBRATE_TEST)
                                    {
                                        SERVO_MAIN.interruptCycle();
                                        event = EVENT_SHUTDOWN;
                                        calibrateServo = false;
                                        GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                    }
                                }
                                if(buffer.indexOf("MAIN_BUTTON") >= 0)
                                {
                                    ThreeWaysTwoDirections(calibrateServo, 0, EVENT_SERVO_CALIBRATE_TEST, HTML_FACTORY_TEST_MAIN_BUTTON, ReadBuff.get(buffer, 2).toInt());
                                }
                                if(buffer.indexOf("HELP_MAIN_BUTTON") >= 0)
                                {
                                    EasyAccess();
                                    pageNumber = HTML_FACTORY_TEST_MAIN_BUTTON_HELP;
                                }
                                if(buffer.indexOf("TEST_MAIN_BUTTON") >= 0)
                                {
                                    if(event != EVENT_BUTTON_MAIN_TEST)
                                    {
                                        onTestMainButton = true;
                                        testMainButton = false;
                                        BUTTON_MAIN.resetPressStatus();
                                        PassageAllowed(ReadBuff.get(buffer, 2).toInt());
                                        event = EVENT_BUTTON_MAIN_TEST;
                                    }
                                    else
                                    {
                                        onTestMainButton = false;
                                        testMainButton = false;
                                        GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                        event = EVENT_SHUTDOWN;
                                    }
                                }
                                if(buffer.indexOf("MIC") >= 0)
                                {
                                    ThreeWaysTwoDirections(testMainButton, 2, EVENT_BUTTON_MAIN_TEST, HTML_FACTORY_MIC, ReadBuff.get(buffer, 2).toInt());
                                }
                                if(buffer.indexOf("RESET_MIC") >= 0)
                                {
                                    onTestMic = false;
                                    testMic = false;
                                    quietAdc = false;
                                    quietDb = 0;
                                    loudAdc = false;
                                    loudDb = 0;
                                    currentDb = 0;
                                    MIC_MAIN.reset();
                                    GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                }
                                if(buffer.indexOf("TEST_MIC") >= 0)
                                {
                                    if(event != EVENT_TEST_MIC)
                                    {
                                        event = EVENT_TEST_MIC;
                                        onTestMic = true;
                                        PassageAllowed(ReadBuff.get(buffer, 2).toInt());
                                    }
                                    else
                                    {
                                        event = EVENT_SHUTDOWN;
                                        onTestMic = false;
                                        //testMic = false;
                                        GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                    }
                                }
                                if(buffer.indexOf("HELP_MIC") >= 0)
                                {
                                    EasyAccess();
                                    pageNumber = HTML_FACTORY_MIC_HELP;
                                }
                                if(buffer.indexOf("ENTER_DB_MIC") >= 0)
                                {
                                    if(quietAdc != 0 && quietDb == 0 && loudAdc == 0 && loudDb == 0)
                                    {
                                        quietDb = ReadBuff.get(buffer, 1).toInt();
                                    }
                                    else if(quietAdc != 0 && quietDb != 0 && loudAdc != 0 && loudDb == 0)
                                    {
                                        if(MIC_MAIN.getLoudBotAdc() == 0 && MIC_MAIN.getLoudTopAdc() == MIC_MAIN.getResolution())
                                        {
                                            loudDb = ReadBuff.get(buffer, 1).toInt();
                                        }
                                    }
                                    GettingAccess(ReadBuff.get(buffer, 3).toInt());
                                }
                                if(buffer.indexOf("SAVE_FACTORY_SETTINGS") >= 0)
                                {
                                    if(testMic)
                                    {
                                        if(event == EVENT_TEST_MIC)
                                        {
                                            event = EVENT_SHUTDOWN;
                                            testMic = false;
                                            onTestMic = false;
                                            AbortedAccess(ReadBuff.get(buffer, 2).toInt());
                                            pageNumber = HTML_FACTORY_MIC;
                                        }
                                        else
                                        {
                                            buildDate = 900000000;
                                            int day = 1000000 * ReadBuff.get(buffer, 3).toInt();
                                            int month = 10000 * ReadBuff.get(buffer, 4).toInt();
                                            int year = ReadBuff.get(buffer, 5).toInt();
                                            buildDate += day + month + year;
                                            EepromDeviceSerialNumber.set(deviceSerialNumber);
                                            EepromBuildDate.set(buildDate);
                                            EepromMode.set(MODE_INSTALATION);
                                            WriteFactoryCluster();
                                            event = EVENT_RESTART;
                                            pageNumber = HTML_LOADING;
                                        }
                                    }
                                    else
                                    {
                                        AbortedAccess(ReadBuff.get(buffer, 2).toInt());
                                        pageNumber = HTML_FACTORY_MIC;
                                    }
                                }
                                break;
                            }
                            case MODE_INSTALATION:
                            {
                                if(buffer.indexOf("REST") >= 0)
                                {
                                    if(restCalibrateComplite)
                                    {
                                        EasyAccess();
                                    }
                                    else
                                    {
                                        PassWithDeferredVerification();
                                    }
                                    pageNumber = HTML_INSTALATION_REST_POSITION;
                                }
                                if(buffer.indexOf("HELP_REST") >= 0)
                                {
                                    pageNumber = HTML_INSTALATION_REST_POSITION_HELP;
                                }
                                if(buffer.indexOf("TEST_REST") >= 0)
                                {
                                    event = EVENT_REST;
                                    vTaskDelay(DELAY_DECISEC);
                                    GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                }
                                if(buffer.indexOf("MODE_CALIBRATION") >= 0)
                                {
                                    if(restCalibrateComplite)
                                    {
                                        pageNumber = HTML_INSTALATION_SETTING_MODE;
                                    }
                                    else
                                    {
                                        AbortedAccess(ReadBuff.get(buffer, 2).toInt());
                                    }
                                }
                                if(buffer.indexOf("AMPLITUDE_AUTO") >= 0)
                                {
                                    pageNumber = HTML_INSTALATION_AUTO;
                                }
                                if(buffer.indexOf("AMPLITUDE_MANUAL") >= 0)
                                {
                                    EasyAccess();
                                    pageNumber = HTML_INSTALATION_MANUAL_CALIB_AMP;
                                }
                                if(buffer.indexOf("AMPLITUDE_MEASURE") >= 0)
                                {
                                    GettingAccess(ReadBuff.get(buffer, 2).toInt());
                                    if(!amplitudeMeashure && !amplitudeMeashureComplite)
                                    {
                                        event = EVENT_AMPLITUDE_MEASURE;
                                    }
                                    else if(amplitudeMeashure)
                                    {
                                        amplitudeMeashure = false;
                                        amplitudeMeashureComplite = true;
                                    }
                                    else if(amplitudeMeashureComplite)
                                    {
                                        amplitudeMeashureComplite = false;
                                    }
                                }
                                if(buffer.indexOf("HELP_AMPLITUDE") >= 0)
                                {
                                    PassWithDeferredVerification();
                                    pageNumber = HTML_INSTALATION_MANUAL_CALIB_AMP_HELP;
                                }
                                if(buffer.indexOf("SLOW_MO_SETUP") >= 0)
                                {
                                    if(amplitudeMeashureComplite)
                                    {
                                        pageNumber = HTML_INSTALATION_MANUAL_SLOW;
                                    }
                                    else
                                    {
                                        AbortedAccess(ReadBuff.get(buffer, 2).toInt());
                                    }
                                }
                                if(buffer.indexOf("SLOW_MO_TEST") >= 0)
                                {
                                    minDelaySlow = ReadBuff.get(buffer, 1).toInt();
                                    maxDelaySlow = ReadBuff.get(buffer, 2).toInt();
                                    if((maxDelaySlow - minDelaySlow) < 1)
                                    {
                                        maxDelaySlow = minDelaySlow + 1;
                                    }
                                    betweenDelayMinSlow = ReadBuff.get(buffer, 3).toInt();
                                    betweenDelayMaxSlow = ReadBuff.get(buffer, 4).toInt();
                                    incrementSlow = ReadBuff.get(buffer, 5).toInt();
                                    if(incrementSlow <= 1)
                                    {
                                        incrementSlow = 2;
                                    }
                                    String accModel = ReadBuff.get(buffer, 6);
                                    String value = "";
                                    byte counter = 0;
                                    byte end = accModel.length() - 1;
                                    for(byte i = 0; i < accModel.length(); i++)
                                    {
                                        if(accModel[i] == '+')
                                        {
                                            accelerationModelSlow[counter++] = value.toFloat();
                                            value = "";
                                        }
                                        else if(i == end)
                                        {
                                            if(value == "")
                                            {
                                                value = accModel[i];
                                            }
                                            accelerationModelSlow[counter] = value.toFloat();
                                        }
                                        else
                                        {
                                            value += accModel[i];
                                        }
                                    }
                                    if(accelerationModelSlow[0] != 9.00)
                                    {
                                        accelerationModelSlow[0] = 9.00;
                                    }
                                    if(accelerationModelSlow[SIZE_SPLINE_ARRAY - 1] != 1.00)
                                    {
                                        accelerationModelSlow[SIZE_SPLINE_ARRAY - 1] = 1.00;
                                    }
                                    descendingAccModel = true;
                                    for(byte i = 1; i < SIZE_SPLINE_ARRAY; i++)
                                    {
                                        if(accelerationModelSlow[i - 1] <= accelerationModelSlow[i])
                                        {
                                            descendingAccModel = false;
                                        }
                                    }
                                    GettingAccess(ReadBuff.get(buffer, 8).toInt());
                                    if(!slowMoTest && !slowMoTestComplite)
                                    {
                                        event = EVENT_SLOW_MO_TEST;
                                    }
                                    else if(slowMoTest && !slowMoTestComplite)
                                    {
                                        slowMoTest = false;
                                        slowMoTestComplite = true;
                                    }
                                    else if(!slowMoTest && slowMoTestComplite)
                                    {
                                        slowMoTest = false;
                                        slowMoTestComplite = false;
                                        event = EVENT_SLOW_MO_TEST;
                                    }
                                }
                                if(buffer.indexOf("HELP_SLOW_MO_TEST") >= 0)
                                {
                                    EasyAccess();
                                    pageNumber = HTML_INSTALATION_MANUAL_SLOW_HELP;
                                }
                                if(buffer.indexOf("FAST_MO_SETUP") >= 0)
                                {
                                    if(slowMoTestComplite)
                                    {
                                        pageNumber = HTML_INSTALATION_MANUAL_FAST;
                                    }
                                    else
                                    {
                                        AbortedAccess(ReadBuff.get(buffer, 2).toInt());
                                    }
                                }
                                if(buffer.indexOf("FAST_MO_TEST") >= 0)
                                {
                                    minDelayFast = ReadBuff.get(buffer, 1).toInt();
                                    maxDelayFast = ReadBuff.get(buffer, 2).toInt();
                                    if((maxDelayFast - minDelayFast) < 1)
                                    {
                                        maxDelayFast = minDelayFast + 1;
                                    }
                                    betweenDelayMinFast = ReadBuff.get(buffer, 3).toInt();
                                    betweenDelayMaxFast = ReadBuff.get(buffer, 4).toInt();
                                    incrementFast = ReadBuff.get(buffer, 5).toInt();
                                    if(incrementFast <= 1)
                                    {
                                        incrementFast = 2;
                                    }
                                    String accModel = ReadBuff.get(buffer, 6);
                                    String value = "";
                                    byte counter = 0;
                                    byte end = accModel.length() - 1;
                                    for(byte i = 0; i < accModel.length(); i++)
                                    {
                                        if(accModel[i] == '+')
                                        {
                                            accelerationModelFast[counter++] = value.toFloat();
                                            value = "";
                                        }
                                        else if(i == end)
                                        {
                                            if(value == "")
                                            {
                                                value = accModel[i];
                                            }
                                            accelerationModelFast[counter] = value.toFloat();
                                        }
                                        else
                                        {
                                            value += accModel[i];
                                        }
                                    }
                                    if(accelerationModelFast[0] != 9.00)
                                    {
                                        accelerationModelFast[0] = 9.00;
                                    }
                                    if(accelerationModelFast[SIZE_SPLINE_ARRAY - 1] != 1.00)
                                    {
                                        accelerationModelFast[SIZE_SPLINE_ARRAY - 1] = 1.00;
                                    }
                                    descendingAccModel = true;
                                    for(byte i = 1; i < SIZE_SPLINE_ARRAY; i++)
                                    {
                                        if(accelerationModelFast[i - 1] <= accelerationModelFast[i])
                                        {
                                            descendingAccModel = false;
                                        }
                                    }
                                    GettingAccess(ReadBuff.get(buffer, 8).toInt());
                                    if(!fastMoTest && !fastMoTestComplite)
                                    {
                                        event = EVENT_FAST_MO_TEST;
                                    }
                                    else if(fastMoTest && !fastMoTestComplite)
                                    {
                                        fastMoTest = false;
                                        fastMoTestComplite = true;
                                    }
                                    else if(!fastMoTest && fastMoTestComplite)
                                    {
                                        fastMoTest = false;
                                        fastMoTestComplite = false;
                                        event = EVENT_FAST_MO_TEST;
                                    }
                                }
                                if(buffer.indexOf("HELP_FAST_MO_TEST") >= 0)
                                {
                                    EasyAccess();
                                    pageNumber = HTML_INSTALATION_MANUAL_FAST_HELP;
                                }
                                if(buffer.indexOf("CHANGE_DEFAULT_AP") >= 0)
                                {
                                    EepromMode.set(MODE_USER);
                                    WriteInstallationCluster();
                                    event = EVENT_RESTART;
                                    pageNumber = HTML_LOADING;
                                }
                                break;
                            }
                            case MODE_USER:
                            {
                                if (pageNumber == HTML_MAIN)
                                {
                                    pageYOffset = ReadBuff.get(buffer, 1).toInt();
                                    for (list <String>::iterator it = idUserProg.begin(); it != idUserProg.end(); it++)
                                    {
                                        if(buffer.indexOf(*it) >= 0)
                                        {
                                            String commandType = "";
                                            String commandNumber = "";
                                            byte i = 0;
                                            byte len = buffer.length();
                                            for (; i < len; i++)
                                            {
                                                if (buffer[i] == '_')
                                                {
                                                    i++;
                                                    break;
                                                }
                                                commandType += buffer[i];
                                            }
                                            for (; i < len; i++)
                                            {
                                                if (buffer[i] == '_')
                                                {
                                                    break;
                                                }
                                            }
                                            i++;
                                            for (; i < len; i++)
                                            {
                                                if (buffer[i] == '=')
                                                {
                                                    break;
                                                }
                                                commandNumber += buffer[i];
                                            }
                                            progCode = commandNumber.toInt();
                                            if (CheckProgramm(progCode))
                                            {
                                                if (!ExtractProgramm(progCode))
                                                {
                                                    DefaultProgramm();
                                                    // Serial.println("Номер ошибки (2) для генерирования сообщения пользователю");
                                                }
                                            }
                                            else
                                            {
                                                DefaultProgramm();
                                            }
                                            if (commandType == "START")
                                            {
                                                event = EVENT_WORK;
                                            }
                                            else if (commandType == "OPTIONS")
                                            {
                                                pageNumber = HTML_USER_PROGRAM_OPTIONS;
                                            }
                                            else
                                            {
                                                // Serial.println("Номер ошибки (2) для генерирования сообщения пользователю");
                                            }
                                        }
                                    }
                                }
                                if(buffer.indexOf("MAIN_MENU") >= 0)
                                {
                                    EasyAccess();
                                    animationMain = true;
                                    pageNumber= HTML_MAIN;
                                }
                                if(buffer.indexOf("HELP_MAIN") >= 0)
                                {  
                                    EasyAccess();
                                    pageNumber = HTML_USER_MAIN_HELP;
                                }
                                if(buffer.indexOf("BREAK_WORK") >= 0)
                                {
                                    event = EVENT_SHUTDOWN; // Переделать через мьютекс
                                    doWork = false;
                                }
                                if(buffer.indexOf("ADD_PROGRAMM") >= 0)
                                {
                                    DefaultProgramm();
                                    progCode = GetNextProgCode();
                                    pageNumber= HTML_USER_PROGRAM_OPTIONS;
                                }
                                if(buffer.indexOf("SAVE_PROG_OPTIONS") >= 0)
                                {
                                    ASCII_URI_RU Uri;
                                    
                                    String headerUserProg = Uri.getString(ReadBuff.get(buffer, 1));
                                    if (headerUserProg == "")
                                    {
                                        catalogHeaderUserProg.erase(progCode);
                                    }
                                    else
                                    {
                                        catalogHeaderUserProg[progCode] = headerUserProg;
                                    }
                                    workTime = ReadBuff.get(buffer, 2).toInt();
                                    ampLimit = ReadBuff.get(buffer, 3).toInt();
                                    ampCode = ReadBuff.get(buffer, 4).toInt();
                                    ampProg.clear();
                                    if (ampCode > BUILD_AMP_END)
                                    {
                                        StringToList(ReadBuff.get(buffer, 5), "+", ampProg);
                                    }
                                    speedLimit = ReadBuff.get(buffer, 6).toInt();
                                    speedCode = ReadBuff.get(buffer, 7).toInt();
                                    speedProg.clear();
                                    if (speedCode > BUILD_SPEED_END)
                                    {
                                        StringToList(ReadBuff.get(buffer, 8), "+", speedProg);
                                    }
                                    if (progCode == PROG_NUMBER_DEF && workTime == WORK_TIME && ampLimit == AMP_LIMIT && ampCode == BUILD_AMP_BEG && speedLimit == SPEED_LIMIT && speedCode == BUILD_SPEED_BEG)
                                    {
                                        EasyAccess();
                                        animationMain = true;
                                        pageNumber= HTML_MAIN;
                                    }
                                    else
                                    {
                                        if (SaveArrayInEEprom(CompilingArhive(PreparingDescription(PreparingProgramm()))))
                                        {
                                            EasyAccess();
                                            animationMain = true;
                                            pageNumber= HTML_MAIN;
                                        }
                                        else
                                        {
                                            AbortedAccess(ReadBuff.get(buffer, 9).toInt());
                                            pageNumber= HTML_USER_PROGRAM_OPTIONS;
                                        }
                                    }
                                    SaveExtraArrayInEEprom(arhiveList.size());
                                }
                                if(buffer.indexOf("DELETE_USER_PROG") >= 0)
                                {
                                    catalogHeaderUserProg.erase(progCode);
                                    SaveArrayInEEprom(DeleteProgramm(progCode));
                                    SaveExtraArrayInEEprom(arhiveList.size());
                                    animationMain = true;
                                    pageNumber= HTML_MAIN;
                                }
                                if(buffer.indexOf("HELP_USER_PROG") >= 0)
                                {
                                    pageNumber = HTML_USER_PROGRAM_OPTIONS_HELP;
                                }
                                if(buffer.indexOf("SETTINGS") >= 0)
                                {
                                    pageNumber = HTML_USER_SETTINGS;
                                }
                                if(buffer.indexOf("NAME") >= 0)
                                {
                                    pageNumber = HTML_USER_NAME;
                                }
                                if(buffer.indexOf("MECHANICAL_START") >= 0)
                                {
                                    pageNumber = HTML_USER_MANUAL_START;
                                }
                                if(buffer.indexOf("SAVE_MECHANICAL_START") >= 0)
                                {
                                    byte index = 1;
                                    holdInRest = (ReadBuff.get(buffer, index++)  == "HOLD_FALSE") ? false : true; 
                                    if (!holdInRest)
                                    {
                                        startSwinging = (ReadBuff.getName(buffer, index) == "START_SWING") ? true : false;
                                        index = (startSwinging) ? index + 1 : index;
                                        startControlled = (ReadBuff.getName(buffer, index) == "START_CONT") ? true : false;
                                        index = (startControlled) ? index : index - 1;
                                        startConfirmationDegrees = ReadBuff.get(buffer, ++index).toInt();
                                        startSwingingProg = ReadBuff.get(buffer, ++index).toInt();
                                        startConfirmationTime = ReadBuff.get(buffer, ++index).toInt();
                                        startControlledProg = ReadBuff.get(buffer, ++index).toInt();
                                    }
                                    else
                                    {
                                        startControlled = false;
                                        startSwinging = false;
                                    }
                                    EepromMechanicalStart.set(ArhiveParamMechStart());
                                    if (holdInRest)
                                    {
                                        event = EVENT_HOLD_IN_REST;
                                    }
                                    else
                                    {
                                        event = EVENT_SHUTDOWN;
                                    }
                                    pageNumber = HTML_USER_SETTINGS;
                                }
                                if(buffer.indexOf("ON_TIME_BLOCKING") >= 0)
                                {
                                    onTimeBlocking = !onTimeBlocking;
                                }
                                if(buffer.indexOf("OFF_WIRELESS") >= 0)
                                {
                                    EepromWirelessMode.set(Wireless(WIRELESS_OFF));
                                    event = EVENT_RESTART;
                                    pageNumber = HTML_LOADING;
                                }
                                if(buffer.indexOf("SAVE_NAME") >= 0)
                                {
                                    String newName = ReadBuff.get(buffer, 1);
                                    name = "";
                                    byte length = newName.length();
                                    for (auto i = 0; i < length; i++)
                                    {
                                        if (newName[i] == '%')
                                        {
                                            String ascii = "%";
                                            for (auto j = i; j < i + 2; j++)
                                            {
                                                ascii += newName[j];
                                            }
                                            if (ascii = "%27")
                                            {
                                                name += "'";
                                                i += 2;
                                            }
                                        }
                                        else if (newName[i] == '+')
                                        {
                                            name += " ";
                                        }
                                        else
                                        {
                                            name += newName[i];
                                        }
                                    }
                                    EepromName.set(name);
                                    pageNumber = HTML_USER_SETTINGS;
                                }
                                if(buffer.indexOf("RESET_SETTINGS") >= 0)
                                {
                                    animation = true;
                                    pageNumber = HTML_USER_RESET_SETTINGS;
                                }
                                if(buffer.indexOf("HELP_RESET") >= 0)
                                {
                                    pageNumber = HTML_USER_RESET_SETTINGS_HELP;
                                }
                                if(buffer.indexOf("RESET_WIRELESS") >= 0)
                                {
                                    pageNumber = HTML_USER_RESET_WIRELESS;
                                }
                                if(buffer.indexOf("RESET_PROG") >= 0)
                                {
                                    pageNumber = HTML_USER_RESET_PROG;
                                }
                                if(buffer.indexOf("RESET_USER") >= 0)
                                {
                                    pageNumber = HTML_USER_RESET_USER;
                                }
                                if(buffer.indexOf("RESTART_INSTALLATION") >= 0)
                                {
                                    pageNumber = HTML_USER_RESET_INSTALLATION;
                                }
                                if(buffer.indexOf("DEMO_SETUP") >= 0)
                                {
                                    PassageAllowed(0);
                                    pageNumber = HTML_USER_DEMO_SETUP;
                                }
                                if(buffer.indexOf("SYNC_SYSTEM_TIME") >= 0)
                                {
                                    PassageAllowed(ReadBuff.get(buffer, 5).toInt());
                                    RunSystemTimer(ReadBuff.get(buffer, 1).toInt(), ReadBuff.get(buffer, 2).toInt(), ReadBuff.get(buffer, 3).toInt());
                                }
                                if(buffer.indexOf("SAVE_DEMO") >= 0)
                                {
                                    byte i = 1;
                                    if (ReadBuff.get(buffer, i++) == "on")
                                    {
                                        if (demoMode != DEMO_MODE_OFF)
                                        {
                                            beginDemo = false;
                                            timerOn = false;
                                        }
                                        demoDurationWork = ReadBuff.get(buffer, i++).toInt();
                                        demoDurationBreak = ReadBuff.get(buffer, i++).toInt();
                                        if (ReadBuff.get(buffer, i++) == "DEMO_ALWAYS")
                                        {
                                            demoMode = DEMO_MODE_ALWAYS;
                                            EndSystemTimer();
                                        }
                                        else
                                        {
                                            demoMode = DEMO_MODE_TIMETABLE;
                                            beginTimetableWork = StrinTimeToInt(ReadBuff.get(buffer, i++));
                                            endTimetableWork = StrinTimeToInt(ReadBuff.get(buffer, i));
                                            i += 3;
                                            int h = ReadBuff.get(buffer, i++).toInt();
                                            int m = ReadBuff.get(buffer, i++).toInt();
                                            int s = ReadBuff.get(buffer, i).toInt();
                                            RunSystemTimer(h, m, s);
                                            GetDemoWorkTime();
                                        }
                                        if (event == EVENT_WORK)
                                        {
                                            event = EVENT_SHUTDOWN; // Переделать через мьютекс
                                            doWork = false;
                                        }
                                        needSaveDemo = true;
                                        event = EVENT_SAVE_DEMO_SETUP;
                                    }
                                    else
                                    {
                                        EndSystemTimer();
                                        demoMode = DEMO_MODE_OFF;
                                        EepromDemoMode.set(demoMode);
                                        if (event == EVENT_WORK)
                                        {
                                            event = EVENT_SHUTDOWN; // Переделать через мьютекс
                                            doWork = false;
                                        }
                                        needSaveDemo = false;
                                    }
                                    beginDemo = false;
                                    animationMain = true;
                                    pageNumber = HTML_MAIN;
                                }
                                if(buffer.indexOf("CALIBRATION_REST") >= 0)
                                {
                                    pageNumber = HTML_USER_CALIBRATION_REST;
                                }
                                if(buffer.indexOf("MEASHURE_REST") >= 0)
                                {
                                    pageNumber = HTML_USER_CALIBRATION_REST;
                                }
                                break;
                            }
                        }
                        if (request)
                        {
                            request = false;
                            pageOffsetMain = pageYOffset;
                        }
                        else
                        {
                            pageYOffset = pageOffsetMain;
                        }
                        // Сессия обмена данными (начало)
                        #ifdef DEBUG
                            Serial.print("Buffer:\t\t");
                            Serial.println(buffer);
                        #endif
                        switch(mode)
                        {
                            case MODE_FACTORY:
                                Client.println(LoadFactoryHTML(pageNumber));
                                break;
                            case MODE_INSTALATION:
                                Client.println(LoadInstalationHTML(pageNumber));
                                break;
                            case MODE_USER:
                                Client.println(LoadUserHTML(pageNumber));
                                break;
                        }
                        break;
                    }
                    if(c == '\n')
                    {
                        currentLineIsBlank = true;
                    }
                    else if(c != '\r')
                    {
                        currentLineIsBlank = false;
                    }
                }
                Client.stop();
                /* Serial.println("End session");
                Serial.println(); */
            }
        }
        vTaskDelay(1);
    }
}