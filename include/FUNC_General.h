#pragma once
#ifndef _FUNC_GENERAL_H_
    #define _FUNC_GENERAL_H_
    // Библиотеки
        #include <Arduino.h>
        #include <list>
        #include <map>
        #include <iterator>
        #include "LIB_Peripherals.h"
        #include "LIB_Html.h"
        #include "FUNC_Eeprom.h"
        using namespace std;
    // Перечисления
        enum EnumMode
        {
            MODE_FACTORY,
            MODE_INSTALATION,
            MODE_USER,
            MODE_NONE = 255
        };
        enum EnumDemoMode
        {
            DEMO_MODE_OFF = 0,
            DEMO_MODE_ALWAYS,
            DEMO_MODE_TIMETABLE
        };
        enum EnumEncryptedType
        {
            ENCRYPT_OPEN,
            ENCRYPT_WEP64,
            ENCRYPT_WEP128,
            ENCRYPT_WPA,
            ENCRYPT_WPA2,
            ENCRYPT_WPA_WPA2
        };
        enum EnumEvents
        {
            EVENT_FASTENER_CHECK = 0,
            EVENT_MECH_START_SWING = 1,
            EVENT_MECH_START_CONT = 2,
            EVENT_SAVE_DEMO_SETUP,
            EVENT_DEMO,
            EVENT_WORK,
            EVENT_HOLD_IN_REST,
            EVENT_GET_CURRENT_ANGLE,
            EVENT_AUTO_MO_TEST,
            EVENT_FAST_MO_TEST,
            EVENT_SLOW_MO_TEST,
            EVENT_AMPLITUDE_MEASURE,
            EVENT_REST,
            EVENT_LOADIND_SETUP,
            EVENT_RESTART,
            EVENT_TEST_MIC,
            EVENT_BUTTON_MAIN_TEST,
            EVENT_BUTTON_FACTORY_TEST,
            EVENT_SERVO_CALIBRATE_TEST,
            EVENT_SERVO_CALIBRATE_MAX,
            EVENT_SERVO_CALIBRATE_MID,
            EVENT_SERVO_CALIBRATE_MIN,
            EVENT_SERVO_TEST,
            EVENT_SHUTDOWN,
            EVENT_OFF = 255
        };
    // Константы
        // Числовые
            #define BILLION 1000000000
            #define ONE_HUNDRED_MILLIONS 100000000
            #define TEN_MILLIONS 10000000
            #define MILLION 1000000
            #define ONE_HUNDRED_THOUSANDS 100000
            #define TEN_THOUSANDS 10000
            #define THOUSAND 1000
            #define ONE_HUNDRED 100
            #define TEN 10
        // Общие
            #define PROG_LIMIT 6
            #define DELAY_RESTART 1000
            #define DELAY_RELAY 100
            #define SEC_IN_MIN 60
            #define SEC_IN_HOUR 3600
            #define SEC_IN_DAY 86400
            #define REFRESH_PAGE_IN_SEC 20
            #define DEFAULT_CONF_TIME 3
            #define DEFAUL_CONF_DEGREES 30
        // Кнопка
            #define TIME_DEBAUNSE 50
            #define TIME_CLICK 2000
            #define TIME_HOLD 10000
            #define TIME_LONG_HOLD 30000
            #define TIME_STICKY 60000
        // Сервопривод
            #define CHANNEL 0
            #define WORK_RANGE 180
            #define GEARS_COUNT 9
            #define SIZE_SPLINE_ARRAY 5
            #define MULTIPLIER 10
            #define AMPLITUDE_RATIO 5
        // Объявление пинов
            #define BUTTON_MAIN_IN 26
            #define BUTTON_FACTORY_IN 27
            #define SERVO_OUT 17
            #define RELAY_OUT 5
            #define SERVO_IN ADC1_CHANNEL_6
            #define MIC_IN ADC1_CHANNEL_7
    // Инициализация глобальных переменных
        // Общие
            extern byte event;
            extern byte previousMeashureAngle;
            extern byte newMeashureAngle;
            extern byte switchEvent;
        // Заводские
            extern short delayPulse;
            extern short delayBetween;
            extern bool testServo;
            extern bool sortBeforeCalibServ;
            extern bool calibrateServo;
            extern short testDuration;
            extern bool onTestFactoryButton;
            extern bool testFactoryButton;
            extern bool onTestMainButton;
            extern bool testMainButton;
            extern bool quietAdc;
            extern bool loudAdc;
            extern byte currentDb;
            extern bool onTestMic;
            extern bool testMic;
        // Инсталяционные
            extern bool restCalibrate;
            extern bool restCalibrateComplite;
            extern const byte goodDeflection;
            extern const byte badDeflection;
            extern bool amplitudeMeashure;
            extern bool amplitudeMeashureComplite;
            extern int **arrMeasureDelays;
            extern short extremeMinusAngle;
            extern short extremePlusAngle;
            extern bool descendingAccModel;
            extern bool slowMoTest;
            extern bool slowMoTestComplite;
            extern bool fastMoTest;
            extern bool fastMoTestComplite;
        // Пользовательские
            // Программы апмлитуды и скорости
                extern byte maxSizeArhive;
                extern list <byte> arhiveList;
                extern list <byte> descriptionCatalog;
                extern list <byte> catalogUserProg;
                extern list <byte> catalogBuildProg;
                extern list <byte> headerUserProg;
                extern std::map <byte, String> catalogHeaderUserProg;
                extern list <String> idUserProg;
                extern list <String> headerBuildAmpProg;
                extern list <String> headerBuildSpeedProg;
                extern list <byte> idBuildAmpProg;
                extern list <byte> idBuildSpeedProg;
                extern list <byte> description;
                extern list <byte> ampProg;
                extern list <byte> speedProg;
                extern byte progCode;
                extern byte ampCode;
                extern byte speedCode;
                extern byte ampLimit;
                extern byte speedLimit;
                extern const byte PROG_NUMBER_DEF;
                extern const byte BUILD_AMP_BEG;
                extern const byte BUILD_AMP_END;
                extern const byte BUILD_SPEED_BEG;
                extern const byte BUILD_SPEED_END;
                extern const byte WORK_TIME;
                extern const byte AMP_LIMIT;
                extern const byte SPEED_LIMIT;
            // Основные
                extern bool doWork;
                extern bool clockOn;
                extern bool needSaveDemo;
                extern int messageUpdateTime;
                extern volatile int workedTime;
                extern volatile int systemTime;
                extern volatile int messageTime;
            // Демо
                extern bool timerOn;
                extern bool beginDemo;
                extern int beginTimetableWork;
                extern int endTimetableWork;
                extern short demoDurBreakSec;
            // Механический старт
                extern bool onTimeBlocking;
                extern bool holdInRest;
                extern bool startSwinging;
                extern bool startControlled;
                extern byte startConfirmationTime;
                extern byte startConfirmationDegrees;
                extern byte startControlledProg;
                extern byte startSwingingProg;
            // Опции
                extern bool landscape;
    // Классы
        // Индексирование нумераторов списков
            template <typename T> class CodeInList
            {
                public:
                    CodeInList(list <T> mainList, const T beginCode, const T endCode);
                    void setCounter(list <T> mainList);
                    void resetCounter();
                    T getLastUsed();
                    T getNext(bool increment);
                    T getNext();
                    T getIncrement();
                    T getDecrement();
                    bool setIncrement();
                    bool setDecrement();
                    void setRememberCode(T code);
                    T getRememberCode();
                private:
                    T _beginCode, _endCode, _counter, _rememberCode = 0;
            };
        // Кодировка URI
            class ASCII_URI_RU
            {
                public:
                    ASCII_URI_RU()
                    {
                        _coding.emplace("%D0%90", "А");
                        _coding.emplace("%D0%91", "Б");
                        _coding.emplace("%D0%92", "В");
                        _coding.emplace("%D0%93", "Г");
                        _coding.emplace("%D0%94", "Д");
                        _coding.emplace("%D0%95", "Е");
                        _coding.emplace("%D0%81", "Ё");
                        _coding.emplace("%D0%96", "Ж");
                        _coding.emplace("%D0%97", "З");
                        _coding.emplace("%D0%98", "И");
                        _coding.emplace("%D0%99", "Й");
                        _coding.emplace("%D0%9A", "К");
                        _coding.emplace("%D0%9B", "Л");
                        _coding.emplace("%D0%9C", "М");
                        _coding.emplace("%D0%9D", "Н");
                        _coding.emplace("%D0%9E", "О");
                        _coding.emplace("%D0%9F", "П");
                        _coding.emplace("%D0%A0", "Р");
                        _coding.emplace("%D0%A1", "С");
                        _coding.emplace("%D0%A2", "Т");
                        _coding.emplace("%D0%A3", "У");
                        _coding.emplace("%D0%A4", "Ф");
                        _coding.emplace("%D0%A5", "Х");
                        _coding.emplace("%D0%A6", "Ц");
                        _coding.emplace("%D0%A7", "Ч");
                        _coding.emplace("%D0%A8", "Ш");
                        _coding.emplace("%D0%A9", "Щ");
                        _coding.emplace("%D0%AA", "Ъ");
                        _coding.emplace("%D0%AB", "Ы");
                        _coding.emplace("%D0%AC", "Ь");
                        _coding.emplace("%D0%AD", "Э");
                        _coding.emplace("%D0%AE", "Ю");
                        _coding.emplace("%D0%AF", "Я");
                        _coding.emplace("%D0%B0", "а");
                        _coding.emplace("%D0%B1", "б");
                        _coding.emplace("%D0%B2", "в");
                        _coding.emplace("%D0%B3", "г");
                        _coding.emplace("%D0%B4", "д");
                        _coding.emplace("%D0%B5", "е");
                        _coding.emplace("%D1%91", "ё");
                        _coding.emplace("%D0%B6", "ж");
                        _coding.emplace("%D0%B7", "з");
                        _coding.emplace("%D0%B8", "и");
                        _coding.emplace("%D0%B9", "й");
                        _coding.emplace("%D0%BA", "к");
                        _coding.emplace("%D0%BB", "л");
                        _coding.emplace("%D0%BC", "м");
                        _coding.emplace("%D0%BD", "н");
                        _coding.emplace("%D0%BE", "о");
                        _coding.emplace("%D0%BF", "п");
                        _coding.emplace("%D1%80", "р");
                        _coding.emplace("%D1%81", "с");
                        _coding.emplace("%D1%82", "т");
                        _coding.emplace("%D1%83", "у");
                        _coding.emplace("%D1%84", "ф");
                        _coding.emplace("%D1%85", "х");
                        _coding.emplace("%D1%86", "ц");
                        _coding.emplace("%D1%87", "ч");
                        _coding.emplace("%D1%88", "ш");
                        _coding.emplace("%D1%89", "щ");
                        _coding.emplace("%D1%8A", "ъ");
                        _coding.emplace("%D1%8B", "ы");
                        _coding.emplace("%D1%8C", "ь");
                        _coding.emplace("%D1%8D", "э");
                        _coding.emplace("%D1%8E", "ю");
                        _coding.emplace("%D1%8F", "я");
                    };
                    ~ASCII_URI_RU(){_coding.clear();};
                    String getLetter(String codeUri);
                    String getString(String incomingCipher);
                private:
                    std::map<String, String> _coding;
                    size_t _part = 5;
            };
    // Инициализация экземпляров классов
        // Переферия
            extern BUTTON BUTTON_FACTORY;
            extern BUTTON BUTTON_MAIN;
            extern SERVO SERVO_MAIN;
            extern RELAY RELAY_MAIN;
            extern MIC MIC_MAIN;
        // Индексы списков
            extern CodeInList<byte> UserProgCode;
            extern CodeInList<byte> UserAmpCode;
            extern CodeInList<byte> UserSpeedCode;
            extern CodeInList<byte> BuildAmpCode;
            extern CodeInList<byte> BuildSpeedCode;
        // Информирование
            extern InfoQueue Informer;
            extern RemainingTime LeftToWork;
    // Функции
        // Универсальные методы работы со списками list
            template <typename T> size_t ConvertStaticArrayToList(const T staticArray[], const size_t sizeArray, list <T> &list);
            template <typename T> size_t ConvertStaticArrayToList(const T staticArray[], const size_t sizeArray, const T terminationSymbol, list <T> &list);
            template <typename T> size_t ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray);
            template <typename T> size_t ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray, const T terminationSymbol);
            template <typename T> size_t ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray, const T terminationSymbol, bool eraseEnd);
            template <typename T> size_t LinkingLists(bool emplaceFront, list <T> &generalList, list <T> attachList);
            template <typename T> size_t LinkingLists(list <T> &generalList, list <T> beginList, list <T> endList);
            template <typename T> size_t LinkingLists(list <T> &generalList, list <T> beginList, T separator, list <T> endList);
            template <typename T> void InsertValueInEdgesList(list <T> &list, const T value, const bool end); // insertValueInToListEnd - InVtLE
            template <typename T> bool SplitList(list <T> generalList, const T separator, bool eraseSeparator, list <T> &beginList, list <T> &endList);
            template <typename T> bool LinkingListsWithSubstitution(const size_t maxLenghtGeneralList, list <T> &generalList, list <T> attachList);
            template <typename T> bool LinkingListsWithSubstitution(const size_t maxLenghtGeneralList, list <T> &generalList, const T code, list <T> attachList);
            template <typename T> bool EracePartFromList(list <T> &list, const T code);
            template <typename T> bool EracePartFromList(list <T> &list, const T code, const T lenght);
            template <typename T> void CodeOffset(list <T> &list, T firstCode);
            template <typename T> void CodeOffset(list <T> &generalList, list <T> &offsetCodes, const T lenght);
            template <typename T> T GetLastCodeFromList(list <T> list, const T beginCode, const T endCode);
            template <typename T> T GetNextCodeFromList(bool add, T lastCode, const T beginCode, const T endCode);
            template <typename T> bool FindCodeInList(list <T> list, const T code);
            template <typename T> T GetPartFromArray(list <T> list, const T code);
            template <typename T> size_t GetRangeSize(list <T> list, T code);
            template <typename T> size_t CopyPartFromList(list <T> originalList, list <T> &copyList, const T code);
            template <typename T> size_t CopyPartFromList(list <T> originalList, list <T> &copyList, const T code, const T lenght);
            template <typename T> size_t ExtractValidValuesFromList(list <T> originalList, list <T> &copyList, const T minValue, const T maxValue);
        // Преобразования типов данных
            void RemoveSeparators(String &hexString);
            void ReturnSeparators(String &hexString, byte blockSize, String viewSeparator);
            void HexStringToByteArray(String hexString, byte byteArray[], int sizeArray);
            void ByteArrayToHexString(String &hexString, String viewSeparator, byte byteArray[], int sizeArray);
            void DecStringToByteArray(String decString, byte byteArray[]);
            void ByteArrayToDecString(String &decString, String viewSeparator, byte byteArray[], int sizeArray);
            void FloatArrayToDecString(String &decString, String viewSeparator, float floatArray[], int sizeArray);
            void StringToList(String string, String separator, list <byte> &list);
            String IntToTime(int value);
            int StrinTimeToInt(String value);
        // Настройки сервопривода
            void ServoSetup();
            void ServoCalibrate();
            void ServoInstallationSettings();
            void ServoInstallationSetupSlowMo();
            void ServoInstallationSetupFastMo();
            void ServoInstallationSetup();
            void ServoUserSetup();
            void ServoDefaultVarInFactoryMode();
            void ServoDefaultVarInInstallationMode();
        // Реализация смены состояний
            byte WatchdogDemoTimer();
        // Обработка пользовательских программ
            void CreatCodeInLists();
            void CreatBuildProgramm();
            void CreateHeaderUserProg();
            void ExtractArhive();
            bool CheckProgramm(byte code);
            void DefaultProgramm();
            bool ExtractProgramm(const byte code);
            short PreparingProgramm();
            bool PreparingDescription(short progSize);
            bool CompilingArhive(bool write);
            bool ExtraHighArhive(bool write);
            bool DeleteProgramm(const byte code);
            void SaveExtraArrayInEEprom(size_t address);
            bool SaveArrayInEEprom(bool write);
            void ExtractIdBuildAmpProg();
            void ExtractIdBuildSpeedProg();
            byte GetNextProgCode();
            byte GetNextAmpCode();
            byte GetNextSpeedCode();
            byte GetLastProg();
            void ResetCodesCounters();
        // Таймеры
            // График работы ДЕМО
                void SetDemoTimetable();
                void GetDemoWorkTime();
            // Таймер работы сервопривода
                void BeginWorkTimer();
                void EndWorkTimer();
            // Таймер системного времени
                void BeginSystemTimer(int currentTime);
                void EndSystemTimer();
                void RunSystemTimer(int h, int m, int s);
            // Таймер циклических сообщений
                void BeginMessageTimer();
                void EndMessageTimer();
                void RunMessageTimer();
            // Таймер замера поворота сервопривода
                void BeginRotAngMeashTimer();
                void EndRotAngMeashTimer();
        // Информирование
            void MessageAssembly();
        // Механический старт
            void ExtractParamMechStart(unsigned int arhive);
            unsigned int ArhiveParamMechStart();
#endif