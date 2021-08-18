#pragma once
#ifndef _FUNC_HTML_H_
    // Включения
        #define _FUNC_HTML_H_
        #include <Arduino.h>
        #include <list>
        #include <iterator>
        #include "LIB_Html.h"
        #include "FUNC_General.h"
        #include "LIB_Peripherals.h"
        using namespace std;
    // Обозначения
        enum EnumHTML
        {
            HTML_USER_MAIN_HELP,
            HTML_USER_NAME,
            HTML_USER_MANUAL_START,
            HTML_USER_RESET_WIRELESS,
            HTML_USER_RESET_PROG,
            HTML_USER_RESET_USER,
            HTML_USER_RESET_INSTALLATION,
            HTML_USER_RESET_SETTINGS,
            HTML_USER_RESET_SETTINGS_HELP,
            HTML_USER_DEMO_SETUP,
            HTML_USER_SETTINGS,
            HTML_USER_PROGRAM_OPTIONS,
            HTML_USER_PROGRAM_OPTIONS_HELP,
            HTML_USER_CALIBRATION_REST,
            HTML_INSTALATION_AUTO,
            HTML_INSTALATION_AUTO_HELP,
            HTML_INSTALATION_MANUAL_FAST,
            HTML_INSTALATION_MANUAL_FAST_HELP,
            HTML_INSTALATION_MANUAL_SLOW,
            HTML_INSTALATION_MANUAL_SLOW_HELP,
            HTML_INSTALATION_MANUAL_CALIB_AMP,
            HTML_INSTALATION_MANUAL_CALIB_AMP_HELP,
            HTML_INSTALATION_SETTING_MODE,
            HTML_INSTALATION_SETTING_MODE_HELP,
            HTML_INSTALATION_REST_POSITION,
            HTML_INSTALATION_REST_POSITION_HELP,
            HTML_FACTORY_MIC,
            HTML_FACTORY_MIC_HELP,
            HTML_FACTORY_TEST_MAIN_BUTTON,
            HTML_FACTORY_TEST_MAIN_BUTTON_HELP,
            HTML_FACTORY_CALIBRATE_SERVO,
            HTML_FACTORY_CALIBRATE_SERVO_HELP,
            HTML_FACTORY_REFERENCE_SERVO_DS329MG,
            HTML_FACTORY_TEST_SERVO,
            HTML_FACTORY_TEST_SERVO_HELP,
            HTML_FACTORY_TEST_RESET_BUTTON,
            HTML_FACTORY_TEST_RESET_BUTTON_HELP,
            HTML_WIFI,
            HTML_AP,
            HTML_WIRELESS_MODE,
            HTML_LOADING,
            HTML_CONTACTS,
            HTML_MAIN = 255
        };
    // Глобальные переменные
        extern bool animation;
        extern bool animationMain;
        extern bool reloadPage;
        extern bool breakAction;
        extern bool loadNextPage;
        extern byte pageNumber;
        extern short pageYOffset;
        extern short pageOffsetMain;
    // Общие страницы
        String Page_Contacts();
        String Page_Loading();
        String Page_SerialNumber();
        String Page_WirelessMode();
        String Page_UserAp();
        String Page_WiFi();
    // Страницы заводских настроек
        String Page_Factory_TestFactoryButton();
        String Page_Factory_TestFactoryButtonHelp();
        String Page_Factory_TestServo();
        String Page_Factory_TestServoHelp();
        String Page_Factory_Reference_CoronaDS329MG();
        String Page_Factory_CalibrateServo();
        String Page_Factory_CalibrateServoHelp();
        String Page_Factory_TestMainButton();
        String Page_Factory_TestMainButtonHelp();
        String Page_Factory_TestMicrophone();
        String Page_Factory_TestMicrophoneHelp();
    // Страницы инсталляционных настроек
        String Page_Installation_RestPosition();
        String Page_Installation_RestPositionHelp();
        String Page_Installation_SettingMode();
        String Page_Installation_SettingModeHelp();
        String Page_Installation_ManualCalibrateAmplitude();
        String Page_Installation_ManualCalibrateAmplitudeHelp();
        String Page_Installation_ManualSlow();
        String Page_Installation_ManualSlowHelp();
        String Page_Installation_ManualFast();
        String Page_Installation_ManualFastHelp();
        String Page_Installation_Auto();
        String Page_Installation_AutoHelp();
    // Пользовательские страницы
        String Page_User_MainMenu();
        String Page_User_MainMenuHelp();
        String Page_User_ProgramOptions();
        String Page_User_ProgramOptionsHelp();
        String Page_User_Settings();
        String Page_User_Name();
        String Page_User_ManualStart();
        String Page_User_VoiceStart();
        String Page_User_ResetSettings();
        String Page_User_ResetSettingsHelp();
        String Page_User_ResetWireless();
        String Page_User_ResetProg();
        String Page_User_ResetUser();
        String Page_User_ResetInstallation();
        String Page_User_Demo();
        String Page_User_CalibrateAmplitude();
#endif