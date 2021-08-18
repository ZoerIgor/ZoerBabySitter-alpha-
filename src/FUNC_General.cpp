#include "FUNC_General.h"
#define DEBUG1111
// Инициализация глобальных переменных
    // Общие
        byte event = EVENT_OFF;
        byte previousMeashureAngle = 0;
        byte newMeashureAngle = 0;
        byte switchEvent = 2;
    // Заводские
        short delayPulse = 15;
        short delayBetween = 500;
        bool testServo = false;
        bool sortBeforeCalibServ = false;
        bool calibrateServo = false;
        short testDuration = (TIME_HOLD / 2);
        bool onTestFactoryButton = false;
        bool testFactoryButton = false;
        bool onTestMainButton = false;
        bool testMainButton = false;
        bool quietAdc = false;
        bool loudAdc = false;
        byte currentDb = 0;
        bool onTestMic = false;
        bool testMic = false;
    // Инсталяционные
        bool restCalibrate = false;
        bool restCalibrateComplite = false;
        const byte goodDeflection = 2;
        const byte badDeflection = 5;
        bool amplitudeMeashure = false;
        bool amplitudeMeashureComplite = false;
        int ** arrMeasureDelays;
        short extremeMinusAngle = 0;
        short extremePlusAngle = 0;
        bool descendingAccModel = true;
        bool slowMoTest = false;
        bool slowMoTestComplite = false;
        bool fastMoTest = false;
        bool fastMoTestComplite = false;
    // Пользовательские
        // Программы апмлитуды и скорости
            byte maxSizeArhive = SIZE_PROGRAM_ARHIVE;
            list <byte> arhiveList;
            list <byte> descriptionCatalog;
            list <byte> catalogUserProg;
            list <byte> catalogBuildProg;
            list <byte> headerUserProg;
            std::map <byte, String> catalogHeaderUserProg;
            list <String> idUserProg;
            list <String> headerBuildAmpProg;
            list <String> headerBuildSpeedProg;
            list <byte> idBuildAmpProg;
            list <byte> idBuildSpeedProg;
            list <byte> description;
            list <byte> ampProg;
            list <byte> speedProg;
            byte progCode;
            byte ampCode;
            byte speedCode;
            byte ampLimit;
            byte speedLimit;
            const byte PROG_NUMBER_DEF = 100;
            const byte PROG_NUMBER_BEG = 101;
            const byte PROG_NUMBER_END = 130;
            const byte BUILD_AMP_BEG = 131;
            const byte BUILD_AMP_END = 161;
            const byte BUILD_SPEED_BEG = 162;
            const byte BUILD_SPEED_END = 192;
            const byte USER_AMP_BEG = 193;
            const byte USER_AMP_END = 223;
            const byte USER_SPEED_BEG = 224;
            const byte USER_SPEED_END = 254;
            const byte WORK_TIME = 15;
            const byte AMP_LIMIT = 6;
            const byte SPEED_LIMIT = 6;
            const byte NUL = 0;
            const byte SEPARATOR = 255;
            const byte CODE_LENGTH = 5;
            const byte DESCRIPTION_LENGTH = CODE_LENGTH + 1;
        // Основные
            bool doWork = false;
            bool clockOn = false;
            int volatile workedTime = 0;
            int volatile systemTime = 0;
            int volatile messageTime = 0;
            int messageUpdateTime = 0;
            hw_timer_t *workTimer = NULL;
            hw_timer_t *systemTimer = NULL;
            hw_timer_t *messageTimer = NULL;
            hw_timer_t *rotAngMeashTimer = NULL; 
            portMUX_TYPE workTimerMux = portMUX_INITIALIZER_UNLOCKED;
            portMUX_TYPE systemTimerMux = portMUX_INITIALIZER_UNLOCKED;
            portMUX_TYPE messageTimerMux = portMUX_INITIALIZER_UNLOCKED;
            portMUX_TYPE rotAngMeashTimerMux = portMUX_INITIALIZER_UNLOCKED;
        // Демо
            bool timerOn = false;
            bool beginDemo = false;
            bool needSaveDemo = false;
            int beginTimetableWork = 32400;
            int endTimetableWork = 75600;
            short demoDurBreakSec = 0;
        // Механический старт
            bool onTimeBlocking = false;
            bool holdInRest = false;
            bool startSwinging = false;
            bool startControlled = false;
            byte startConfirmationTime = 0;
            byte startConfirmationDegrees = 0;
            byte startControlledProg = PROG_NUMBER_DEF;
            byte startSwingingProg = PROG_NUMBER_DEF;
        // Опции
            bool landscape = true;
// Классы
    // Индексирование нумераторов списков
        template <typename T> CodeInList<T>::CodeInList(list <T> mainList, const T beginCode, const T endCode)
        {
            _beginCode = beginCode;
            _endCode = endCode;
            _counter = 0;
            for (auto i = mainList.begin(); i != mainList.end(); i++)
            {
                if (*i >= _beginCode && *i <= _endCode)
                {
                    _counter++;
                }
            }
        }
        template <typename T> void CodeInList<T>::setCounter(list <T> mainList)
        {
            _counter = 0;
            for (auto i = mainList.begin(); i != mainList.end(); i++)
            {
                if (*i >= _beginCode && *i <= _endCode)
                {
                    _counter++;
                }
            }
        }
        template <typename T> void CodeInList<T>::resetCounter()
        {
            _counter = 0;
        }
        template <typename T> T CodeInList<T>::getLastUsed()
        {
            if (_counter > 0)
            {
                return _beginCode + _counter - 1;
            }
            return _beginCode;
        }
        template <typename T> T CodeInList<T>::getNext(bool increment)
        {
            if (increment)
            {
                if (_counter == _endCode)
                {
                    return _endCode;
                }
                else
                {
                    return _beginCode + _counter++;
                }
            }
            else
            {
                if (_counter <= _beginCode)
                {
                    return _beginCode;
                }
                else
                {
                    return _beginCode + _counter--;
                }
            }
        }
        template <typename T> T CodeInList<T>::getNext()
        {
            return _beginCode + _counter;
        }
        template <typename T> T CodeInList<T>::getIncrement()
        {
            if (_counter == (_endCode - _beginCode))
            {
                return _endCode;
            }
            else
            {
                return _beginCode + _counter++;
            }
        }
        template <typename T> T CodeInList<T>::getDecrement()
        {
            if (_counter == 0)
            {
                return _beginCode;
            }
            else
            {
                return _beginCode + _counter--;
            }
        }
        template <typename T> bool CodeInList<T>::setIncrement()
        {
            if (_counter == (_endCode - _beginCode))
            {
                return false;
            }
            _counter++;
            return true;
        }
        template <typename T> bool CodeInList<T>::setDecrement()
        {
            if (_counter == 0)
            {
                return false;
            }
            _counter--;
            return true;
        }
        template <typename T> void CodeInList<T>::setRememberCode(T code)
        {
            _rememberCode = code;
        }
        template <typename T> T CodeInList<T>::getRememberCode()
        {
            return _rememberCode;
        }
    // Кодировка URI
        String ASCII_URI_RU::getLetter(String codeUri)
        {
            auto it = _coding.find(codeUri);
            if (it != _coding.end())
            {
                return it->second;
            }
            return "";
        }
        String ASCII_URI_RU::getString(String incomingCipher)
        {
            String text = "";
            String partText = "%";
            size_t counter = 0;
            bool uri = false;
            for (auto &element: incomingCipher)
            {
                if (uri)
                {
                    partText += element;
                    if (++counter == _part)
                    {
                        counter = 0;
                        uri = false;
                        text += getLetter(partText);
                        partText = "%";
                    }
                }
                else
                {
                    if (element == '%')
                    {
                        uri = true;
                    }
                    else
                    {
                        text += element;
                    }
                }
            }
            return text;
        }
// Инициализация экземпляров классов
    // Переферия
        BUTTON ButtonSetup(TOUCH, TIME_DEBAUNSE, TIME_CLICK, TIME_HOLD, TIME_LONG_HOLD, TIME_STICKY);
        BUTTON BUTTON_FACTORY(BUTTON_FACTORY_IN, ButtonSetup);
        BUTTON BUTTON_MAIN(BUTTON_MAIN_IN, ButtonSetup);
        SERVO SERVO_MAIN(SERVO_OUT, SERVO_IN);
        RELAY RELAY_MAIN(RELAY_OUT);
        MIC MIC_MAIN(MIC_IN);
    // Индексы списков
        CodeInList <byte> UserProgCode(descriptionCatalog, PROG_NUMBER_BEG, PROG_NUMBER_END);
        CodeInList <byte> UserAmpCode(catalogUserProg, USER_AMP_BEG, USER_AMP_END);
        CodeInList <byte> UserSpeedCode(catalogUserProg, USER_SPEED_BEG, USER_SPEED_END);
        CodeInList <byte> BuildAmpCode(catalogBuildProg, BUILD_AMP_BEG, BUILD_AMP_END);
        CodeInList <byte> BuildSpeedCode(catalogBuildProg, BUILD_SPEED_BEG, BUILD_SPEED_END);
    // Информирование
        InfoQueue Informer;
// Функции
    // Универсальные методы работы со списками list
        template <typename T> size_t ConvertStaticArrayToList(const T staticArray[], const size_t sizeArray, list <T> &list)
        {
            list.clear();
            for (size_t i = 0; i < sizeArray; i++)
            {
                list.emplace_back(staticArray[i]);
            }
            return list.size();
        }
        template <typename T> size_t ConvertStaticArrayToList(const T staticArray[], const size_t sizeArray, const T terminationSymbol, list <T> &list)
        {
            list.clear();
            for (size_t i = 0; i < sizeArray; i++)
            {
                if (staticArray[i] != terminationSymbol)
                {
                    list.emplace_back(staticArray[i]);
                }
                else
                {
                    break;
                }
            }
            return list.size();
        }
        template <typename T> size_t ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray)
        {
            if (list.size() > sizeArray)
            {
                return 0;
            }
            size_t counter = 0;
            for (auto i = list.begin(); i != list.end(); i++)
            {
                staticArray[counter++] = *i;
            }
            return counter;
        }
        template <typename T> size_t ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray, const T terminationSymbol)
        {
            if (list.size() > sizeArray)
            {
                return 0;
            }
            size_t counter = 0;
            for (auto i = list.begin(); i != list.end(); i++)
            {
                staticArray[counter++] = *i;
            }
            if (counter < sizeArray)
            {
                staticArray[counter++] = terminationSymbol;
            }
            return counter;
        }
        template <typename T> size_t ConvertListToStaticArray(list <T> list, T staticArray[], const size_t sizeArray, const T terminationSymbol, bool eraseEnd)
        {
            if (list.size() > sizeArray)
            {
                return 0;
            }
            size_t counter = 0;
            for (auto i = list.begin(); i != list.end(); i++)
            {
                staticArray[counter++] = *i;
            }
            if (eraseEnd)
            {
                size_t size = counter;
                while (counter < sizeArray)
                {
                    staticArray[counter++] = terminationSymbol;
                }
                return size;
            }
            return counter;
        }
        template <typename T> size_t LinkingLists(bool emplaceFront, list <T> &generalList, list <T> attachList)
        {
            if (emplaceFront)
            {
                for (auto i = attachList.rbegin(); i != attachList.rend(); i++)
                {
                    generalList.emplace_front(*i);
                }
            }
            else
            {
                for (auto i = attachList.begin(); i != attachList.end(); i++)
                {
                    generalList.emplace_back(*i);
                }
            }
            return generalList.size();
        }
        template <typename T> size_t LinkingLists(list <T> &generalList, list <T> beginList, list <T> endList)
        {
            generalList = beginList;
            for (auto i = endList.begin(); i != endList.end(); i++)
            {
                generalList.emplace_back(*i);
            }
            return generalList.size();
        }
        template <typename T> size_t LinkingLists(list <T> &generalList, list <T> beginList, T separator, list <T> endList)
        {
            generalList = beginList;
            generalList.emplace_back(separator);
            for (auto i = endList.begin(); i != endList.end(); i++)
            {
                generalList.emplace_back(*i);
            }
            return generalList.size();
        }
        template <typename T> void InsertValueInEdgesList(list <T> &list, const T value, const bool end) // insertValueInToListEnd
        {
            if (end)
            {
                list.emplace_back(value);
            }
            else
            {
                list.emplace_front(value);
            }
        }
        template <typename T> bool SplitList(list <T> generalList, const T separator, bool eraseSeparator, list <T> &beginList, list <T> &endList)
        {
            typename list <T>::iterator generalIt = generalList.begin();
            size_t beforeSeparator = 0;
            size_t afterSeparator = 0;
            size_t generalSize = generalList.size();
            while (*generalIt != separator) // Поиск разделителя
            {
                generalIt++;
                if (++beforeSeparator >= generalSize)
                {
                    break;
                }
            }
            if (beforeSeparator >= generalSize) // Разделитель не найден
            {
                return false;
            }
            generalIt = generalList.begin();
            beginList.clear();
            endList.clear();
            while (afterSeparator < beforeSeparator) // Первый список
            {
                afterSeparator++;
                beginList.emplace_back(*generalIt++);
            }
            if (eraseSeparator)
            {
                generalIt++;
                afterSeparator++;
            }
            while (afterSeparator < generalSize) // Второй список
            {
                afterSeparator++;
                endList.emplace_back(*generalIt++);
            }
            return true;
        }
        template <typename T> bool LinkingListsWithSubstitution(const size_t maxLenghtGeneralList, list <T> &generalList, list <T> attachList)
        {
            typename list <T>::iterator generalIt = generalList.begin();
            typename list <T>::iterator attachIt = attachList.begin();
            size_t attachSize = attachList.size();
            size_t counter = 0;
            size_t partCounter = 0;
            size_t offset = 0;
            bool notFound = true;
            bool nextCode = false;
            for (auto i = generalList.begin(); i != generalList.end(); i++)
            {
                if (partCounter++ == 0)
                {
                    if (*i == *attachIt)
                    {
                        notFound = false;
                        offset = counter;
                        advance(generalIt, offset);
                    }
                    if (*i > *attachIt && !nextCode)
                    {
                        if (notFound)
                        {
                            offset = counter;
                            advance(generalIt, offset);
                        }
                        nextCode = true;
                    }
                }
                if (partCounter == attachSize)
                {
                    partCounter = 0;
                }
                counter++;
            }
            if (!notFound) // Предварительное удаление старого присоединенного массива из основного
            {
                typename list <T>::iterator i = generalIt;
                advance(i, attachSize);
                generalList.erase(generalIt, i);
                advance(generalIt, offset);
            }
            // Присоединение массива
            if (generalList.size() + attachSize <= maxLenghtGeneralList || maxLenghtGeneralList == 0) // Проверка превышения длины основного массива
            {
                if (!nextCode) // Присоединение нового массива в конец основного
                {
                    for (auto i = attachList.begin(); i != attachList.end(); i++)
                    {
                        generalList.emplace_back(*i);
                    }
                }
                else //Вставляем новый массив на порядковое место
                {
                    if(offset == 0)
                    {
                        generalIt = generalList.begin();
                    }
                    for (auto i = attachList.begin(); i != attachList.end(); i++)
                    {
                        generalList.insert(generalIt, *i);
                    }
                }
                return true;
            }
            return false; // Сумма массивов превосходит максимальную длинну основного массива
        }
        template <typename T> bool LinkingListsWithSubstitution(const size_t maxLenghtGeneralList, list <T> &generalList, const T code, list <T> attachList)
        {
            typename list <T>::iterator generalIt = generalList.begin();
            typename list <T>::iterator attachIt = attachList.begin();
            if (code != 0)
            {
                attachList.insert(attachIt, code);
            }
            size_t generalSize = generalList.size();
            size_t attachSize = attachList.size();
            size_t beginPart = 0;
            size_t endPart = 0;
            size_t maxFindNumber = 0;
            while (*generalIt <= code && endPart < generalSize) // Поиск позиции по возростанию для присоединяемых кодового номера и массива
            {
                if (*generalIt == code)
                {
                    beginPart = endPart;
                }
                if(maxFindNumber < *generalIt)
                {
                    maxFindNumber = *generalIt;
                }
                generalIt++;
                endPart++;
            }
            if (endPart == generalSize && maxFindNumber != code) // Присоединение нового массива в конец основного
            {
                if (generalSize + attachSize <= maxLenghtGeneralList || maxLenghtGeneralList == 0) // Проверка превышения длины основного массива
                {
                    for (auto i = attachList.begin();i != attachList.end(); i++)
                    {
                        generalList.emplace_back(*i);
                    }
                    return true;
                }
                else
                {
                    return false; // Сумма массивов превосходит максимальную длинну основного массива
                }
            }
            else if (*--generalIt <= code) // Добавление массива в начало или в середину
            {
                if (generalSize - (endPart - beginPart) + attachSize <= maxLenghtGeneralList || maxLenghtGeneralList == 0) // Проверка превышения длины основного массива
                {
                    generalIt++;
                    if (maxFindNumber == code) // Присоединяемый массив уже существует
                    {
                        typename list <T>::iterator i = generalList.begin();
                        advance(i, beginPart);
                        for (; i != generalIt; i++) // Удаляем область старого массива
                        {
                            generalList.erase(i);
                        }
                    }
                    if (maxFindNumber == 0) // Указываем начало основного массива в качестве начала вставляемого массива
                    {
                        generalIt = generalList.begin();
                    }
                    for (auto i = attachList.begin(); i != attachList.end(); i++) // Вставляем новый массив на порядковое место
                    {
                        generalList.insert(generalIt, *i);
                    }
                    return true;
                }
                else
                {
                    return false; // Сумма массивов превосходит максимальную длинну основного массива
                }
            }
            return false;
        }
        template <typename T> bool EracePartFromList(list <T> &list, const T code)
        {
            size_t counter = 0;
            size_t beginPart = 0;
            size_t endPart = 0;
            bool beginFound = false;
            bool endFound = false;
            for (auto i = list.begin(); i != list.end(); i++) // Поиск кодового номера в массиве
            {
                if (*i == code)
                {
                    beginFound = true;
                    beginPart = counter;
                }
                if(*i > code && !endFound)
                {
                    endPart = counter;
                    endFound = true;
                }
                counter++;
            }
            if (beginFound && !endFound)
            {
                endPart = list.size();
            }
            if (beginFound) // Кодовый номер найден
            {
                typename list <T>::iterator iBegin = list.begin();
                advance(iBegin, beginPart);
                typename list <T>::iterator iEnd = list.begin();
                advance(iEnd, endPart);
                for (; iBegin != iEnd; iBegin++) // Удаляем область массива
                {
                    list.erase(iBegin);
                }
                return true;
            }
            return false; // Кодовый номер не найден
        }
        template <typename T> bool EracePartFromList(list <T> &list, const T code, const T lenght)
        {
            typename list <T>::iterator i = list.begin();
            bool find = false;
            for (; i != list.end(); i++) // Поиск кодового номера в массиве
            {
                if (*i == code)
                {   
                    find = true;
                    break;
                }
            }
            if (find)
            {
                for (auto n = 0; n < lenght; n++)
                {
                    list.erase(i++);
                }
                return true;
            }
            return false;
        }
        template <typename T> void CodeOffset(std::map <T, String> &map, T firstCode)
        {
            for (auto it = map.begin(); it != map.end(); it++)
            {
                if (it->first > firstCode)
                {
                    T first = it->first - 1;
                    String second = it->second;
                    map.erase(it->first);
                    map.emplace(first, second);
                }
            }
        }
        template <typename T> void CodeOffset(list <T> &list, T firstCode)
        {
            typename list <T>::iterator i = list.begin();
            if (*i != firstCode)
            {
                *i = firstCode;
            }
            T counter = firstCode;
            for (; i != list.end(); i++)
            {
                if (*i > counter)
                {
                    *i = ++counter;
                }
            }
        }
        template <typename T> void CodeOffset(list <T> &generalList, list <T> &offsetCodes, const T lenght)
        {
            typename list <T>::iterator itGen = generalList.begin();
            typename list <T>::iterator i = offsetCodes.begin();
            size_t offsetSize = offsetCodes.size();
            bool toBegin = false;
            if (*itGen < *i)
            {
                advance(itGen, lenght);
                toBegin = true;
            }
            while (itGen != generalList.end())
            {
                for (auto itOff = offsetCodes.begin(); itOff != offsetCodes.end(); itOff++)
                {
                    if (*itGen >= *itOff)
                    {
                        *itGen = *itOff;
                        *itOff = *itOff + 1;
                    }
                    itGen++;
                }
                advance(itGen, lenght - offsetSize);
            }
            if (toBegin)
            {
                itGen = generalList.begin();
                for (auto itOff = offsetCodes.begin(); itOff != offsetCodes.end(); itOff++)
                {
                    if (*itGen > *itOff)
                    {
                        *itGen = *itOff;
                    }
                    itGen++;
                }
            }
            
        }
        template <typename T> T GetLastCodeFromList(list <T> list, const T beginCode, const T endCode)
        {
            T value = 0;
            for (auto i = list.begin(); i != list.end(); i++)
            {
                if (*i >= beginCode && *i <= endCode && *i > value)
                {
                    value = *i;
                }
            }
            if (value == 0)
            {
                return beginCode - 1;
            }
            return value;
        }
        template <typename T> T GetNextCodeFromList(bool add, T lastCode, const T beginCode, const T endCode)
        {
            if (add)
            {
                if (++lastCode > endCode)
                {
                    return endCode;
                }
                return lastCode;
            }
            if (--lastCode < beginCode)
            {
                return beginCode;
            }
            return lastCode;
        }
        template <typename T> bool FindCodeInList(list <T> list, const T code)
        {
            for (auto i = list.begin(); i != list.end(); i++)
            {
                if (*i == code)
                {
                    return true;
                }
            }
            return false;
        }
        template <typename T> size_t GetRangeSize(list <T> list, T code)
        {
            typename list <T>::iterator i = list.begin();
            for (; i != list.end(); i++) // Поиск кода
            {
                if (*i == code)
                {
                    break;
                }
            }
            if (i != list.end()) // Код найден
            {
                code++;
                size_t counter = 0;
                for (; i != list.end(); i++) // Подсчет диаппазона
                {
                    if (*i >= code)
                    {
                        break;
                    }
                    counter++;
                }
                return counter;
            }
            return 0; // Код не найден
        }
        template <typename T> size_t CopyPartFromList(list <T> originalList, list <T> &copyList, const T code)
        {
            typename list <T>::iterator i = originalList.begin();
            for (; i != originalList.end(); i++)
            {
                if (*i == code)
                {
                    i++;
                    break;
                }
            }
            for (; i != originalList.end(); i++)
            {
                if (*i > code)
                {
                    break;
                }
                copyList.emplace_back(*i);
            }
            return copyList.size();
        }
        template <typename T> size_t CopyPartFromList(list <T> originalList, list <T> &copyList, const T code, const T lenght)
        {
            typename list <T>::iterator i = originalList.begin();
            for (; i != originalList.end(); i++)
            {
                if (*i == code)
                {
                    i++;
                    break;
                }
            }
            for (T n = 0; n < lenght; n++)
            {
                copyList.emplace_back(*i++);
            }
            return copyList.size();
        }
        template <typename T> size_t ExtractValidValuesFromList(list <T> originalList, list <T> &copyList, const T minValue, const T maxValue)
        {
            for (auto i = originalList.begin(); i != originalList.end(); i++)
            {
                if (*i >= minValue && *i <= maxValue)
                {
                    copyList.emplace_back(*i);
                }
            }
            return copyList.size();
        }
    // Преобразования типов данных
        void RemoveSeparators(String &hexString)
        {
            String separators = " ,./:;-_%";
            String clearHexString = "";
            String mayBe = "";
            byte count = 0;
            bool miss = false;
            bool longMiss = false;
            for(int i = 0; i < hexString.length(); i++)
            {
                for(int j = 0; j < separators.length(); j++)
                {
                    if(hexString[i] == separators[j])
                    {
                        miss = true;
                        if(hexString[i] == '%')
                        {
                            if(i <= hexString.length() - 2)
                            {
                                mayBe += hexString[i];
                                mayBe += hexString[i + 1];
                                mayBe += hexString[i + 2];
                                if(mayBe == "%3A")
                                {
                                    longMiss = true;
                                }
                            }
                        }
                    }
                }
                if(longMiss && count <= 2)
                {
                    miss = true;
                    count++;
                }
                else
                {
                    longMiss = false;
                    count = 0;
                    mayBe = "";
                }
                if(!miss)
                {
                    clearHexString += hexString[i];
                }
                else
                {
                    miss = false;
                }
            }
            hexString = clearHexString;
        }
        void ReturnSeparators(String &hexString, byte blockSize, String viewSeparator)
        {
            byte counter = 0;
            String separatorHexString = "";
            for(int i = 0; i < hexString.length(); i++)
            {
                counter++;
                separatorHexString += hexString[i];
                if(counter == blockSize)
                {
                    counter = 0;
                    if(i != hexString.length() - 1)
                    {
                        separatorHexString += viewSeparator;
                    }
                }
            }
            hexString = separatorHexString;
        }
        void HexStringToByteArray(String hexString, byte byteArray[], int sizeArray)
        {
            RemoveSeparators(hexString);
            int counter = 0;
            int n = 0;
            byte size = 2;
            for(int i = 0; i < hexString.length(); i++)
            {
                ++counter;
                if(counter == size)
                {
                    counter = 0;
                    int k = i - 1;
                    char hexChar[size];
                    for(int j = 0; j < size; j++)
                    {
                        hexChar[j] = hexString[k++];
                    }
                    unsigned int decInt;
                    sscanf(hexChar,"%x",&decInt);
                    byteArray[n++] = decInt;
                }
            }
        }
        void ByteArrayToHexString(String &hexString, String viewSeparator, byte byteArray[], int sizeArray)
        {
            hexString = "";
            const byte size = 2;
            const byte dec = 10;
            unsigned int decInt;
            char hexChar[size];
            for(int i = 0; i < sizeArray; i++)
            {
                decInt = byteArray[i];
                sprintf(hexChar, "%X", decInt);
                for (byte i = 0; i < size; i++)
                {
                    if(decInt < dec)
                    {
                        if(i == 0)
                        {
                            hexString += "0";
                        }
                        else
                        {
                            hexString += hexChar[0];
                        }
                    }
                    else
                    {
                        if(hexChar[i] == 0)
                        {
                            hexString += "0";
                        }
                        else
                        {
                            hexString += hexChar[i];
                        }
                    }
                }
            }
            ReturnSeparators(hexString, size, viewSeparator);
        }
        void DecStringToByteArray(String decString, byte byteArray[])
        {
            String separators = " ,./:;-_";
            String blockDecString = "";
            int counter = 0;
            bool miss = false;
            bool end;
            for(int i = 0; i < decString.length(); i++)
            {
                if(i == decString.length() - 1)
                {
                    end = true;
                }
                for(int j = 0; j < separators.length(); j++)
                {
                    if(decString[i] == separators[j])
                    {
                        miss = true;
                    }
                }
                if(!miss)
                {
                    blockDecString += decString[i];
                    if(end)
                    {
                        byteArray[counter] = blockDecString.toInt();
                    }
                }
                else
                {
                    byteArray[counter++] = blockDecString.toInt();
                    miss = false;
                    blockDecString = "";
                }
            }
        }
        void ByteArrayToDecString(String &decString, String viewSeparator, byte byteArray[], int sizeArray)
        {
            decString = "";
            for(int i = 0; i < sizeArray; i++)
            {
                decString += String(byteArray[i], DEC);
                if(i != sizeArray - 1)
                {
                    decString += viewSeparator;
                }
            }
        }
        void FloatArrayToDecString(String &decString, String viewSeparator, float floatArray[], int sizeArray)
        {
            decString = "";
            for(int i = 0; i < sizeArray; i++)
            {
                String str = String(floatArray[i], DEC);
                if(str[3] != '0')
                {
                    int str0 = floatArray[i];
                    String str2;
                    str2 = str[2];
                    int int2 = str2.toInt();
                    str = String(str0, DEC) + "." + String(++int2, DEC);
                }
                for(byte i = 0; i < 3; i++)
                {
                    decString += str[i];
                }
                if(i != sizeArray - 1)
                {
                    decString += viewSeparator;
                }
            }
        }
        void StringToList(String string, String separator, list <byte> &list)
        {
            size_t size = string.length();
            String subString = "";
            for (size_t i = 0; i < size; i++)
            {
                if (string[i] != separator[0])
                {
                    subString += string[i];
                }
                else
                {
                    list.emplace_back(subString.toInt());
                    subString = "";
                }
            }
            list.emplace_back(subString.toInt());
        }
        String IntToTime(int value)
        {
            short hours = value / 3600;
            String h = "";
            if (hours < 10)
            {
                h += "0";
            }
            h += String(hours, DEC);
            short minutes = value - (hours * 3600);
            String m = "";
            if (minutes < 10)
            {
                m += "0";
            }
            m += String(minutes / 60, DEC);
            return h + ":" + m;
        }
        int StrinTimeToInt(String value)
        {
            byte length = value.length();
            String hours = "";
            String minutes = "";
            for (byte i = 0; i < length; i++)
            {
                if (i < 2)
                {
                    hours += value[i];
                }
                else if (i > 4)
                {
                    minutes += value[i];
                }
            }
            return (hours.toInt() * 3600) + (minutes.toInt() * 60);
        }
    // Настройки сервопривода
        void ServoSetup()
        {
            SERVO_MAIN.setFrequency(frequency);
            SERVO_MAIN.setMaxAngle(rotateAngle);
            SERVO_MAIN.setMinPulseWidth(minPulseWidth);
            SERVO_MAIN.setMaxPulseWidth(maxPulseWidth);
            SERVO_MAIN.setCountMeasure(4);
            SERVO_MAIN.setDelayPulse(delayPulse);
            SERVO_MAIN.setDelayBetween(delayBetween);
            SERVO_MAIN.setRelativeMiddle(true);
            SERVO_MAIN.setWorkRange(WORK_RANGE);
        }
        void ServoCalibrate()
        {
            SERVO_MAIN.setMinAnalogSig(minAnalogSig);
            SERVO_MAIN.setMidAnalogSig(midAnalogSig);
            SERVO_MAIN.setMaxAnalogSig(maxAnalogSig);
            SERVO_MAIN.setDegrees();
            SERVO_MAIN.setCalibMinAng(calibMinDeg);
            SERVO_MAIN.setCalibMidAng(calibMidDeg);
            SERVO_MAIN.setCalibMaxAng(calibMaxDeg);
        }
        void ServoInstallationSettings()
        {
            SERVO_MAIN.setRelativeMiddle(false);
            SERVO_MAIN.setGearCounts(GEARS_COUNT);
            SERVO_MAIN.setAmplitudeMax(maxAmplitude);
            SERVO_MAIN.setAccelerationModelSize(SIZE_SPLINE_ARRAY);
            SERVO_MAIN.setMultiplier(MULTIPLIER);
            SERVO_MAIN.setAmplitudeRatio(AMPLITUDE_RATIO);
        }
        void ServoInstallationSetupSlowMo()
        {
            SERVO_MAIN.slowMo(true);
            SERVO_MAIN.setStepDelayMinSlow(minDelaySlow);
            SERVO_MAIN.setStepDelayMaxSlow(maxDelaySlow);
            SERVO_MAIN.setBetweenDelayMinSlow(betweenDelayMinSlow);
            SERVO_MAIN.setBetweenDelayMaxSlow(betweenDelayMaxSlow);
            SERVO_MAIN.setIncrementSlow(incrementSlow);
            SERVO_MAIN.setAccelerationModelSlow(accelerationModelSlow);
        }
        void ServoInstallationSetupFastMo()
        {
            SERVO_MAIN.slowMo(false);
            SERVO_MAIN.setStepDelayMinFast(minDelayFast);
            SERVO_MAIN.setStepDelayMaxFast(maxDelayFast);
            SERVO_MAIN.setBetweenDelayMinFast(betweenDelayMinFast);
            SERVO_MAIN.setBetweenDelayMaxFast(betweenDelayMaxFast);
            SERVO_MAIN.setIncrementFast(incrementFast);
            SERVO_MAIN.setAccelerationModelFast(accelerationModelFast);
        }
        void ServoInstallationSetup()
        {
            ServoInstallationSetupSlowMo();
            ServoInstallationSetupFastMo();
        }
        void ServoUserSetup()
        {
            SERVO_MAIN.setAmplitudeProgramm(ampProg);
            SERVO_MAIN.setAccelerationProgramm(speedProg);
            SERVO_MAIN.setAmplitudeLimit(ampLimit);
            SERVO_MAIN.setAcceleratioLimit(speedLimit);
        }
        void ServoDefaultVarInFactoryMode()
        {
            frequency = 20;
            rotateAngle = 180;
            minPulseWidth = 500;
            maxPulseWidth = 2500;
        }
        void ServoDefaultVarInInstallationMode()
    {
        minDelaySlow = 3;
        maxDelaySlow = 7;
        betweenDelayMinSlow = 30;
        betweenDelayMaxSlow = 7;
        incrementSlow = 3;
        accelerationModelSlow[0] = 9.0;
        accelerationModelSlow[1] = 5.0;
        accelerationModelSlow[2] = 3.0;
        accelerationModelSlow[3] = 2.0;
        accelerationModelSlow[4] = 1.0;
        minDelayFast = 1;
        maxDelayFast = 5;
        betweenDelayMinFast = 30;
        betweenDelayMaxFast = 5;
        incrementFast = 5;
        accelerationModelFast[0] = 9.0;
        accelerationModelFast[1] = 3.5;
        accelerationModelFast[2] = 2.0;
        accelerationModelFast[3] = 1.5;
        accelerationModelFast[4] = 1.0;
    }
    // Реализация смены состояний
        byte ExtractProg()
        {
            if (!ExtractProgramm(PROG_NUMBER_DEF))
            {
                DefaultProgramm();
                // Serial.println("Номер ошибки (2) для генерирования сообщения пользователю");
            }
            workTime = demoDurationWork;
            beginDemo = true;
            return EVENT_WORK;
        }
        byte WatchdogDemoTimer()
        {
            if (!beginDemo)
            {
                return ExtractProg();
            }
            else
            {
                if (!timerOn)
                {
                    BeginWorkTimer();
                    timerOn = true;
                    demoDurBreakSec = demoDurationWork * SEC_IN_MIN;
                }
                else
                {
                    if (workedTime >= demoDurBreakSec)
                    {
                        EndWorkTimer();
                        timerOn = false;
                        return ExtractProg();
                    }
                }
                return EVENT_OFF;
            }
        }
    // Обработка пользовательских программ
        void CreatCodeInLists()
        {
            #ifdef DEBUG
                Serial.println("---1-1-0");
            #endif
            UserProgCode.setCounter(descriptionCatalog);
            UserAmpCode.setCounter(catalogUserProg);
            UserSpeedCode.setCounter(catalogUserProg);
            BuildAmpCode.setCounter(catalogBuildProg);
            BuildSpeedCode.setCounter(catalogBuildProg);
            #ifdef DEBUG
                Serial.println("---1-1-1");
            #endif
        }
        void CreatBuildProgramm()
        {
            #ifdef DEBUG
                Serial.println("---1-1-0");
            #endif
            headerBuildAmpProg.emplace_back("Постоянная");
            ampProg = {9};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getNext(true), ampProg);
            headerBuildAmpProg.emplace_back("Возростающая");
            ampProg = {1,2,3,4,5,6,7,8,9};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getNext(true), ampProg);
            headerBuildAmpProg.emplace_back("Убывающая");
            ampProg = {9,8,7,6,5,4,3,2,1};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getNext(true), ampProg);
            headerBuildAmpProg.emplace_back("Пиковая");
            ampProg = {1,3,5,7,9,7,5,3,1};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getNext(true), ampProg);
            headerBuildAmpProg.emplace_back("Пилообразная");
            ampProg = {3,7,3,7,3,7,3,7,3,7};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildAmpCode.getNext(true), ampProg);
            headerBuildSpeedProg.emplace_back("Постоянная");
            speedProg = {9};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getNext(true), speedProg);
            headerBuildSpeedProg.emplace_back("Возростающая");
            speedProg = {1,2,3,4,5,6,7,8,9};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getNext(true), speedProg);
            headerBuildSpeedProg.emplace_back("Убывающая");
            speedProg = {9,8,7,6,5,4,3,2,1};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getNext(true), speedProg);
            headerBuildSpeedProg.emplace_back("Пиковая");
            speedProg = {1,3,5,7,9,7,5,3,1};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getNext(true), speedProg);
            headerBuildSpeedProg.emplace_back("Пилообразная");
            speedProg = {3,7,3,7,3,7,3,7,3,7};
            LinkingListsWithSubstitution(maxSizeArhive, catalogBuildProg, BuildSpeedCode.getNext(true), speedProg);
            #ifdef DEBUG
                Serial.println("---1-1-2");
            #endif
        }
        void CreateHeaderUserProg()
        {
            #ifdef DEBUG11
                Serial.println("---1-1-0");
            #endif
            headerUserProg.clear();
            if (descriptionCatalog.size() == 0)
            {
                #ifdef DEBUG11
                Serial.println("---1-1-3");
            #endif
                headerUserProg.emplace_back(PROG_NUMBER_DEF);
                #ifdef DEBUG11
                Serial.println("---1-1-4");
            #endif
            }
            else
            {
                #ifdef DEBUG11
                Serial.println("---1-1-5");
            #endif
                for (list <byte>::iterator i = descriptionCatalog.begin(); i != descriptionCatalog.end(); advance(i, DESCRIPTION_LENGTH))
                {
                    headerUserProg.emplace_back(*i);
                    #ifdef DEBUG11
                Serial.println("---1-1-6");
            #endif
                }
            }
        }
        void ExtractExtraArhive(size_t size)
        {
            #ifdef DEBUG111
                Serial.println("---1-2-1");
            #endif
            size_t address = ADDRESS_PROGRAM_ARHIVE + size + 1;
            if (address < ADDRESS_PROGRAM_ARHIVE + maxSizeArhive)
            {
                #ifdef DEBUG111
                    Serial.println("---1-2-2");
                #endif
                MemoryASCII headerDirectoryBegin(address, 1);
                if (headerDirectoryBegin.read(address) != 0)
                {
                    #ifdef DEBUG111
                        Serial.println("---1-2-3");
                    #endif
                    bool zero = false;;
                    while(true)
                    {
                        #ifdef DEBUG111
                            Serial.println("---1-2-4");
                        #endif
                        MemoryASCII headerDirectoryCode(address, 1);
                        byte code = headerDirectoryCode.read(address);
                        String codeName = "";
                        size_t length = 0;
                        size_t indx = address + 1;
                        if (zero)
                        {
                            #ifdef DEBUG111
                                Serial.println("---1-2-5");
                            #endif
                            if (indx < ADDRESS_PROGRAM_ARHIVE + maxSizeArhive)
                            {
                                #ifdef DEBUG111
                                    Serial.println("---1-2-6");
                                #endif
                                MemoryASCII headerDirectoryNext(indx, 1);
                                if (headerDirectoryNext.read(indx) == 0)
                                {
                                    #ifdef DEBUG111
                                        Serial.println("---1-2-7");
                                    #endif
                                    break;
                                }
                                else
                                {
                                    #ifdef DEBUG111
                                        Serial.println("---1-2-8");
                                    #endif
                                    zero = false;
                                }
                            }
                            else
                            {
                                #ifdef DEBUG111
                                    Serial.println("---1-2-9");
                                #endif
                                break;
                            }
                        }
                        #ifdef DEBUG111
                            Serial.println("---1-2-10");
                        #endif
                        while (indx < ADDRESS_PROGRAM_ARHIVE + maxSizeArhive)
                        {
                            #ifdef DEBUG111
                                Serial.println("---1-2-11");
                            #endif
                            MemoryASCII headerDirectoryReadByte(indx, 1);
                            if (headerDirectoryReadByte.read(indx++) == 0)
                            {
                                #ifdef DEBUG111
                                    Serial.println("---1-2-12");
                                #endif
                                zero = true;
                                break;
                            }
                            else
                            {
                                #ifdef DEBUG111
                                    Serial.println("---1-2-13");
                                #endif
                                length++;
                            }
                        }
                        #ifdef DEBUG111
                            Serial.println("---1-2-14");
                        #endif
                        MemoryASCII headerDirectoryName(++address, length);
                        headerDirectoryName.readArray(codeName);
                        if (code >= PROG_NUMBER_DEF && codeName != "")
                        {
                            #ifdef DEBUG111
                                Serial.println("---1-2-15");
                            #endif
                            catalogHeaderUserProg.emplace(code, codeName);
                        }
                        address += length + 1;
                    }
                }
            }
        }
        void ExtractArhive()
        {
            #ifdef DEBUG
                Serial.println("---1-3-0");
            #endif
            arhiveList.clear();
            #ifdef DEBUG0
                Serial.println("EXTRACT ARHIVE");
                for (short i = 0; i < maxSizeArhive; i++)
                {
                    Serial.print(arhiveArray[i]);
                    Serial.print(" ");
                }
                Serial.println();
            #endif
            #ifdef DEBUG
                Serial.println("---1-3-1");
            #endif
            ExtractExtraArhive(ConvertStaticArrayToList(arhiveArray, maxSizeArhive, NUL, arhiveList));
            #ifdef DEBUG
                Serial.println("---1-3-2");
            #endif
            descriptionCatalog.clear();
            catalogUserProg.clear();
            SplitList(arhiveList, SEPARATOR, true, descriptionCatalog, catalogUserProg);
            #ifdef DEBUG
                Serial.println("---1-3-3");
            #endif
        }
        bool CheckProgramm(byte code)
        {
            #ifdef DEBUG
                Serial.println("---1-4-1");
            #endif
            if (code != PROG_NUMBER_DEF)
            {
                #ifdef DEBUG
                Serial.println("---1-4-2");
            #endif
                return true;
            }
            list <byte>::iterator i = descriptionCatalog.begin();
            if (*i == PROG_NUMBER_DEF)
            {
                #ifdef DEBUG
                Serial.println("---1-4-3");
            #endif
                return true;
            }
            #ifdef DEBUG
                Serial.println("---1-4-4");
            #endif
            return false;
        }
        void DefaultProgramm()
        {
            #ifdef DEBUG
                Serial.println("---1-5-0");
            #endif
            ampProg.clear();
            #ifdef DEBUG
                Serial.println("---1-5-1");
            #endif
            CopyPartFromList(catalogBuildProg, ampProg, BUILD_AMP_BEG);
            #ifdef DEBUG
                Serial.println("---1-5-2");
            #endif
            speedProg.clear();
            CopyPartFromList(catalogBuildProg, speedProg, BUILD_SPEED_BEG);
            #ifdef DEBUG
                Serial.println("---1-5-3");
            #endif
            progCode = PROG_NUMBER_DEF;
            ampCode = BUILD_AMP_BEG;
            speedCode = BUILD_SPEED_BEG;
            workTime = WORK_TIME;
            ampLimit = AMP_LIMIT;
            speedLimit = SPEED_LIMIT;
        }
        bool ExtractProgramm(const byte code)
        {
            #ifdef DEBUG
                Serial.println("---1-6-0");
            #endif
            description.clear();
            #ifdef DEBUG
                Serial.println("---1-6-1");
            #endif
            CopyPartFromList(descriptionCatalog, description, code, CODE_LENGTH);
            #ifdef DEBUG
                Serial.println("---1-6-2");
            #endif
            list <byte>::iterator i = description.begin();
            ampCode = *i;
            #ifdef DEBUG
                Serial.println("---1-6-3");
            #endif
            ampProg.clear();
            if (FindCodeInList(catalogBuildProg, *i))
            {
                CopyPartFromList(catalogBuildProg, ampProg, *i);
                #ifdef DEBUG
                Serial.println("---1-6-4");
            #endif
            }
            else if (FindCodeInList(catalogUserProg, *i))
            {
                CopyPartFromList(catalogUserProg, ampProg, *i);
                #ifdef DEBUG
                Serial.println("---1-6-5");
            #endif
            }
            else
            {
                #ifdef DEBUG
                Serial.println("---1-6-6");
            #endif
                return false; // + Код ошибки
            }
            speedProg.clear();
            i++;
            speedCode = *i;
            if (FindCodeInList(catalogBuildProg, *i))
            {
                CopyPartFromList(catalogBuildProg, speedProg, *i);
                #ifdef DEBUG
                Serial.println("---1-6-7");
            #endif
            }
            else if (FindCodeInList(catalogUserProg, *i))
            {
                CopyPartFromList(catalogUserProg, speedProg, *i);
                #ifdef DEBUG
                Serial.println("---1-6-8");
            #endif
            }
            else
            {
                #ifdef DEBUG
                Serial.println("---1-6-9");
            #endif
                return false; // + Код ошибки
            }
            workTime = *++i;
            ampLimit = *++i;
            speedLimit = *++i;
            return true;
        }
        size_t ExtraArchiveSize()
        {
            #ifdef DEBUG
                Serial.println("---1-7-0");
            #endif
            size_t size = catalogHeaderUserProg.size();
            #ifdef DEBUG
                Serial.println("---1-7-1");
            #endif
            if (size == 0)
            {
                #ifdef DEBUG
                Serial.println("---1-7-2");
            #endif
                return 0;
            }
            else
            {
                #ifdef DEBUG
                Serial.println("---1-7-3");
            #endif
                size = size * 2; // С учетом терминирующего нуля основного архива
                for (auto &element: catalogHeaderUserProg)
                {
                    size += element.second.length();
                    #ifdef DEBUG
                Serial.println("---1-7-4");
            #endif
                }
                #ifdef DEBUG
                Serial.println("---1-7-5");
            #endif
                return size;
            }
        }
        short PreparingProgramm()
        {
            #ifdef DEBUG
                Serial.println("---1-8-1");
            #endif
            short size = 0;
            if (ampCode >= USER_AMP_BEG)
            {
                size += ampProg.size();
                #ifdef DEBUG
                Serial.println("---1-8-2");
            #endif
            }
            else
            {
                #ifdef DEBUG
                Serial.println("---1-8-3");
            #endif
                ampProg.clear();
            }
            if (speedCode >= USER_SPEED_BEG)
            {
                size += speedProg.size();
                #ifdef DEBUG
                Serial.println("---1-8-4");
            #endif
            }
            else
            {
                speedProg.clear();
                #ifdef DEBUG
                Serial.println("---1-8-5");
            #endif
            }
            #ifdef DEBUG
                Serial.println("---1-8-6");
            #endif
            return size;
        }
        bool PreparingDescription(short progSize)
        {
            #ifdef DEBUG
                Serial.println("---1-9-1");
            #endif
            if (arhiveList.size() + DESCRIPTION_LENGTH + progSize + ExtraArchiveSize() <= maxSizeArhive)
            {
                #ifdef DEBUG
                Serial.println("---1-9-2");
            #endif
                description.clear();
                if (progCode <= PROG_NUMBER_END) // Проверка резерва кодов программы (а следовательно и кодов амплитуды и скорости, т.к. коды амплитуды или скорости меньше или равны количеству программ)
                {
                    #ifdef DEBUG
                Serial.println("---1-9-3");
            #endif
                    if (progCode == PROG_NUMBER_DEF)
                    {
                        description.emplace_back(PROG_NUMBER_DEF);
                        #ifdef DEBUG
                Serial.println("---1-9-4");
            #endif
                    }
                    else
                    {
                        #ifdef DEBUG
                Serial.println("---1-9-5");
            #endif
                        if (!FindCodeInList(descriptionCatalog, progCode))
                        {
                            description.emplace_back(UserProgCode.getIncrement());
                            #ifdef DEBUG
                Serial.println("---1-9-6");
            #endif
                        }
                        else
                        {
                            description.emplace_back(progCode);
                            #ifdef DEBUG
                Serial.println("---1-9-7");
            #endif
                        }
                    }
                    #ifdef DEBUG
                Serial.println("---1-9-8");
            #endif
                    if (ampCode < USER_AMP_BEG || FindCodeInList(descriptionCatalog, ampCode))
                    {
                        description.emplace_back(ampCode);
                        #ifdef DEBUG
                Serial.println("---1-9-9");
            #endif
                    }
                    else
                    {
                        description.emplace_back(UserAmpCode.getIncrement());
                        #ifdef DEBUG
                Serial.println("---1-9-10");
            #endif
                    }
                    if (speedCode < USER_SPEED_BEG || FindCodeInList(descriptionCatalog, speedCode))
                    {
                        description.emplace_back(speedCode);
                        #ifdef DEBUG
                Serial.println("---1-9-11");
            #endif
                    }
                    else
                    {
                        description.emplace_back(UserSpeedCode.getIncrement());
                        #ifdef DEBUG
                Serial.println("---1-9-12");
            #endif
                    }
                    description.emplace_back(workTime);
                    description.emplace_back(ampLimit);
                    description.emplace_back(speedLimit);
                }
                else
                {
                    #ifdef DEBUG
                Serial.println("---1-9-13");
            #endif
                    return false;
                }
                #ifdef DEBUG
                Serial.println("---1-9-14");
            #endif
                return true;
            }
            #ifdef DEBUG
                Serial.println("---1-9-15");
            #endif
            return false;
        }
        bool CompilingArhive(bool write)
        {
            #ifdef DEBUG
                Serial.println("---1-10-1");
            #endif
            if (write) // Если память и пул кодов не переполнены
            {
                #ifdef DEBUG
                Serial.println("---1-10-2");
            #endif
                list <byte>::iterator i = ++description.begin(); // Указатель на код амплитуды
                if (ampProg.size() > 0) // Если пользовательская программа амплитуды указана
                {
                    LinkingListsWithSubstitution(maxSizeArhive, catalogUserProg, *i, ampProg); // Проводим слияние каталогов с заменой содержимого
                    #ifdef DEBUG
                Serial.println("---1-10-3");
            #endif
                }
                if (speedProg.size() > 0) // Если пользовательская программа скорости указана
                {
                    LinkingListsWithSubstitution(maxSizeArhive, catalogUserProg, *++i, speedProg); // Проводим слияние каталогов с заменой содержимого
                    #ifdef DEBUG
                Serial.println("---1-10-4");
            #endif
                }
                if (LinkingListsWithSubstitution(maxSizeArhive, descriptionCatalog, description)) // Проводим слияние каталогов с заменой содержимого
                {
                    #ifdef DEBUG
                Serial.println("---1-10-5");
            #endif
                    // Удалиние неиспользованных программ амплитуды или скорости из каталога (catalogUserProg)
                    list <byte> bin; // Мусорная корзина для неиспользуемых кодов
                    for (auto &element: catalogUserProg)
                    {
                        #ifdef DEBUG
                Serial.println("---1-10-6");
            #endif
                        if (element >= USER_AMP_BEG) // Если найден код пользовательской амплитуды или скорости
                        {
                            #ifdef DEBUG
                Serial.println("---1-10-7");
            #endif
                            if (!FindCodeInList(descriptionCatalog, element)) // И его нет в каталоге описания программ
                            {
                                bin.emplace_back(element); // Помещаем в карзину
                                #ifdef DEBUG
                Serial.println("---1-10-8");
            #endif
                            }
                        }
                    }
                    #ifdef DEBUG
                Serial.println("---1-10-9");
            #endif
                    for (auto &element: bin) // Обходим элементы корзины
                    {
                        // Удаляем неиспользуемую программу амплитуды или скорости
                        EracePartFromList(catalogUserProg, element);
                        #ifdef DEBUG
                Serial.println("---1-10-10");
            #endif
                        // Проверка необходимости сдвига кодов с большим значением
                        if (element < USER_SPEED_BEG) // Проверка сдвига кодов амплитуды
                        {
                            #ifdef DEBUG
                Serial.println("---1-10-11");
            #endif
                            UserAmpCode.setDecrement(); // Освободить номерной фонд на 1
                            #ifdef DEBUG
                Serial.println("---1-10-12");
            #endif
                            for (auto descAmp = descriptionCatalog.begin(); descAmp != descriptionCatalog.end(); descAmp++)
                            {
                                #ifdef DEBUG
                Serial.println("---1-10-13");
            #endif
                                if (*descAmp > element && *descAmp <= USER_AMP_END) // Если код в диапазоне пользовательской амплитуды
                                {
                                    *descAmp -= 1; // Уменьшаем его на единицу
                                    #ifdef DEBUG
                Serial.println("---1-10-14");
            #endif
                                }
                            }
                            for (auto userElem = catalogUserProg.begin(); userElem != catalogUserProg.end(); userElem++)
                            {
                                #ifdef DEBUG
                Serial.println("---1-10-15");
            #endif
                                if (*userElem > element && *userElem <= USER_AMP_END) // Если код в диапазоне пользовательской амплитуды
                                {
                                    *userElem -= 1; // Уменьшаем его на единицу
                                    #ifdef DEBUG
                Serial.println("---1-10-16");
            #endif
                                }
                            }
                        }
                        else // Проверка сдвига кодов скорости
                        {
                            #ifdef DEBUG
                Serial.println("---1-10-17");
            #endif
                            UserSpeedCode.setDecrement(); // Освободить номерной фонд на 1
                            #ifdef DEBUG
                Serial.println("---1-10-18");
            #endif
                            for (auto &descSpeed: descriptionCatalog)
                            {
                                #ifdef DEBUG
                Serial.println("---1-10-19");
            #endif
                                if (descSpeed > element && descSpeed <= USER_SPEED_END) // Если код в диапазоне пользовательской скорости
                                {
                                    descSpeed -= 1; // Уменьшаем его на единицу
                                    #ifdef DEBUG
                Serial.println("---1-10-20");
            #endif
                                }
                            }
                            for (auto &userSpeed: catalogUserProg)
                            {
                                #ifdef DEBUG
                Serial.println("---1-10-21");
            #endif
                                if (userSpeed > element && userSpeed <= USER_SPEED_END) // Если код в диапазоне пользовательской скорости
                                {
                                    userSpeed -= 1; // Уменьшаем его на единицу
                                    #ifdef DEBUG
                Serial.println("---1-10-22");
            #endif
                                }
                            }
                        }
                    }
                    bin.clear(); //Очищаем корзину
                    #ifdef DEBUG
                Serial.println("---1-10-23");
            #endif
                }
                arhiveList.clear();
                LinkingLists(arhiveList, descriptionCatalog, SEPARATOR, catalogUserProg);
                #ifdef DEBUG
                Serial.println("---1-10-24");
            #endif
                ConvertListToStaticArray(arhiveList, arhiveArray, maxSizeArhive, NUL, true);
                #ifdef DEBUG
                Serial.println("---1-10-25");
            #endif
                return true;
                
            }
            #ifdef DEBUG
                Serial.println("---1-10-26");
            #endif
            return false;
        }
        bool DeleteProgramm(const byte code)
        {
            #ifdef DEBUG
                Serial.println("---1-11-1");
            #endif
            if (FindCodeInList(descriptionCatalog, code))
            {
                #ifdef DEBUG
                    Serial.println("---1-11-2");
                #endif
                description.clear();
                CopyPartFromList(descriptionCatalog, description, code, CODE_LENGTH);
                #ifdef DEBUG
                    Serial.println("---1-11-3");
                #endif
                list <byte> offsetCodes;
                if (code != PROG_NUMBER_DEF)
                {
                    offsetCodes.emplace_back(code);
                    #ifdef DEBUG
                        Serial.println("---1-11-4");
                    #endif
                    UserProgCode.setDecrement();
                    #ifdef DEBUG
                        Serial.println("---1-11-5");
                    #endif
                }
                else
                {
                    offsetCodes.emplace_back(PROG_NUMBER_BEG);
                    #ifdef DEBUG
                        Serial.println("---1-11-6");
                    #endif
                }
                list <byte>::iterator itDes = description.begin();
                byte first = *itDes++;
                byte second = *itDes--;
                #ifdef DEBUG
                    Serial.println("---1-11-7");
                #endif
                if (first >= USER_AMP_BEG || second >= USER_AMP_BEG) // В каталоге программ существует запись, которую надо удалить
                {
                    #ifdef DEBUG
                        Serial.println("---1-11-8");
                    #endif
                    catalogUserProg.emplace_back(SEPARATOR);
                    #ifdef DEBUG
                        Serial.println("---1-11-9");
                    #endif
                    list <byte>::iterator itCat = catalogUserProg.begin();
                    list <byte> ampCatalog;
                    list <byte> speedCatalog;
                    while (*itCat < USER_SPEED_BEG) // Разделяем каталог
                    {
                        ampCatalog.emplace_back(*itCat++);
                        #ifdef DEBUG
                            Serial.println("---1-11-10");
                        #endif
                    }
                    while (*itCat < SEPARATOR) // Разделяем каталог
                    {
                        speedCatalog.emplace_back(*itCat++);
                        #ifdef DEBUG
                            Serial.println("---1-11-11");
                        #endif
                    }
                    if (first >= USER_AMP_BEG && first <= USER_AMP_END) // Удаляем программу
                    {
                        #ifdef DEBUG
                            Serial.println("---1-11-12");
                        #endif
                        EracePartFromList(ampCatalog, first);
                        #ifdef DEBUG
                            Serial.println("---1-11-13");
                        #endif
                        CodeOffset(ampCatalog, USER_AMP_BEG);
                        #ifdef DEBUG
                            Serial.println("---1-11-14");
                        #endif
                        offsetCodes.emplace_back(first);
                        #ifdef DEBUG
                            Serial.println("---1-11-15");
                        #endif
                        UserAmpCode.setDecrement();
                        #ifdef DEBUG
                            Serial.println("---1-11-16");
                        #endif
                    }
                    if (second >= USER_SPEED_BEG && second <= USER_SPEED_END) // Удаляем программу
                    {
                        EracePartFromList(speedCatalog, second);
                        #ifdef DEBUG
                            Serial.println("---1-11-17");
                        #endif
                        CodeOffset(speedCatalog, USER_SPEED_BEG);
                        #ifdef DEBUG
                            Serial.println("---1-11-18");
                        #endif
                        offsetCodes.emplace_back(second);
                        #ifdef DEBUG
                            Serial.println("---1-11-19");
                        #endif
                        UserSpeedCode.setDecrement();
                        #ifdef DEBUG
                            Serial.println("---1-11-20");
                        #endif
                    }
                    catalogUserProg.clear();
                    LinkingLists(catalogUserProg, ampCatalog, speedCatalog);
                    #ifdef DEBUG
                        Serial.println("---1-11-21");
                    #endif
                }
                EracePartFromList(descriptionCatalog, code, DESCRIPTION_LENGTH);
                #ifdef DEBUG
                    Serial.println("---1-11-22");
                #endif
                CodeOffset(descriptionCatalog, offsetCodes, DESCRIPTION_LENGTH);
                #ifdef DEBUG
                    Serial.println("---1-11-23");
                #endif
                arhiveList.clear();
                if (descriptionCatalog.size() == 0 && catalogUserProg.size() == 0)
                {
                    #ifdef DEBUG
                        Serial.println("---1-11-24");
                    #endif
                }
                else
                {
                    LinkingLists(arhiveList, descriptionCatalog, SEPARATOR, catalogUserProg);
                    #ifdef DEBUG
                        Serial.println("---1-11-25");
                    #endif
                }
                CodeOffset(catalogHeaderUserProg, code);
                if (ConvertListToStaticArray(arhiveList, arhiveArray, maxSizeArhive, NUL))
                {
                    #ifdef DEBUG
                        Serial.println("---1-11-26");
                    #endif
                    return true;
                }
            }
            #ifdef DEBUG
                Serial.println("---1-11-27");
            #endif
            return false;
        }
        void SaveExtraArrayInEEprom(size_t address)
        {
            #ifdef DEBUG11
                Serial.println("---1-12-0");
            #endif
            size_t begin = ADDRESS_PROGRAM_ARHIVE + address;
            size_t length = catalogHeaderUserProg.size();
            //Serial.println("Length: " + String(length, DEC));
            size_t end = ADDRESS_PROGRAM_ARHIVE + SIZE_PROGRAM_ARHIVE - 1;
            size_t counter = 1;
            for (auto &element: catalogHeaderUserProg)
            {
                #ifdef DEBUG11
                Serial.println("---1-12-1");
            #endif
                MemoryASCII headerDirectoryCode(++begin, 1);
                headerDirectoryCode.write(begin, element.first);
                MemoryASCII headerDirectoryName(++begin, 1);
                headerDirectoryName.writeArray(element.second);
                #ifdef DEBUG11
                Serial.println("---1-12-2");
            #endif
                begin += element.second.length();
                if (counter < length)
                {
                    #ifdef DEBUG11
                Serial.println("---1-12-3");
            #endif
                    MemoryASCII headerDirectoryTerminator(begin, 1);
                    headerDirectoryTerminator.write(begin, NUL);
                    counter++;
                    //Serial.println("TESMINATOR ADDR: " + String(begin, DEC));
                }
            }
            begin++;
            while (begin <= end)
            {
                #ifdef DEBUG11
                Serial.println("---1-12-4");
            #endif
                MemoryASCII headerDirectoryFill(begin, 1);
                if (headerDirectoryFill.read(begin) != NUL)
                {
                    headerDirectoryFill.write(begin, NUL);
                    #ifdef DEBUG11
                Serial.println("---1-12-5");
            #endif
                }
                begin++;
            }
        }
        bool SaveArrayInEEprom(bool write)
        {
            #ifdef DEBUG11
                Serial.println("---1-13-0");
            #endif
            if (write)
            {
                #ifdef DEBUG11
                Serial.println("---1-13-1");
            #endif
                #ifdef DEBUG1
                    int counter = 0;
                    for (int i = 0; i < maxSizeArhive; i++)
                    {
                        Serial.println(arhiveArray[counter]);
                        Serial.println(counter++);
                    }
                #endif
                EepromArhiveArray.set(arhiveArray, NUL);
                #ifdef DEBUG11
                Serial.println("---1-13-2");
            #endif
                #ifdef DEBUG0
                    byte arh[maxSizeArhive];
                    EepromArhiveArray.get(arh);
                    Serial.println("SAVE ARHIVE");
                    for (short i = 0; i < maxSizeArhive; i++)
                    {
                        Serial.print(arh[i]);
                        Serial.print(" ");
                    }
                    Serial.println();
                #endif
                #ifdef DEBUG11
                Serial.println("---1-13-3");
            #endif
                return true;
            }
            else
            {
                //Serial.println("Номер ошибки (4) для генерирования сообщения пользователю");
                #ifdef DEBUG
                Serial.println("---1-13-4");
            #endif
                return false;
            }
        }
        void ExtractIdBuildAmpProg()
        {
            #ifdef DEBUG
                Serial.println("---1-14-1");
            #endif
            ExtractValidValuesFromList(catalogBuildProg, idBuildAmpProg, BUILD_AMP_BEG, BUILD_AMP_END);
            #ifdef DEBUG
                Serial.println("---1-14-2");
            #endif
        }
        void ExtractIdBuildSpeedProg()
        {
            #ifdef DEBUG
                Serial.println("---1-15-1");
            #endif
            ExtractValidValuesFromList(catalogBuildProg, idBuildSpeedProg, BUILD_SPEED_BEG, BUILD_SPEED_END);
            #ifdef DEBUG
                Serial.println("---1-15-2");
            #endif
        }
        byte GetNextProgCode()
        {
            #ifdef DEBUG
                Serial.println("---1-16-1");
            #endif
            return UserProgCode.getNext();
        }
        byte GetNextAmpCode()
        {
            #ifdef DEBUG
                Serial.println("---1-17-1");
            #endif
            return UserAmpCode.getNext();
        }
        byte GetNextSpeedCode()
        {
            #ifdef DEBUG
                Serial.println("---1-18-1");
            #endif
            return UserSpeedCode.getNext();
        }
        byte GetLastProg()
        {
            return UserProgCode.getLastUsed();
        }
        void ResetCodesCounters()
        {
            #ifdef DEBUG
                Serial.println("---1-19-1");
            #endif
            UserProgCode.resetCounter();
            UserAmpCode.resetCounter();
            UserSpeedCode.resetCounter();
            #ifdef DEBUG
                Serial.println("---1-19-2");
            #endif
        }
    // Таймеры
        // График работы ДЕМО
            void SetDemoTimetable()
            {
                if (beginDemoWorkTime != 0 || endDemoWorkTime != 0)
                {
                    beginTimetableWork = beginDemoWorkTime * SEC_IN_MIN;
                    endTimetableWork = endDemoWorkTime * SEC_IN_MIN;
                }
            }
            void GetDemoWorkTime()
            {
                beginDemoWorkTime = beginTimetableWork / SEC_IN_MIN;
                endDemoWorkTime = endTimetableWork / SEC_IN_MIN;
            }
        // Таймер работы сервопривода
            void IRAM_ATTR OnWorkTimer()
            {
                portENTER_CRITICAL_ISR(&workTimerMux);
                workedTime++;
                portEXIT_CRITICAL_ISR(&workTimerMux);
            }
            void BeginWorkTimer()
            {
                workTimer = timerBegin(0, 80, true);
                timerAttachInterrupt(workTimer, &OnWorkTimer, true);
                timerAlarmWrite(workTimer, 1000000, true);
                timerAlarmEnable(workTimer);
            }
            void EndWorkTimer()
            {
                timerEnd(workTimer);
                workedTime = 0;
            }
        // Таймер системного времени
            void IRAM_ATTR OnSystemTimer()
            {
                portENTER_CRITICAL_ISR(&systemTimerMux);
                if (++systemTime == SEC_IN_DAY)
                {
                    systemTime = 0;
                }
                portEXIT_CRITICAL_ISR(&systemTimerMux);
            }
            void BeginSystemTimer(int currentTime)
            {
                clockOn = true;
                systemTime = currentTime;
                systemTimer = timerBegin(1, 80, true);
                timerAttachInterrupt(systemTimer, &OnSystemTimer, true);
                timerAlarmWrite(systemTimer, 1000000, true);
                timerAlarmEnable(systemTimer);
            }
            void EndSystemTimer()
            {
                if (clockOn)
                {
                    timerEnd(systemTimer);
                    clockOn = false;
                    systemTime = 0;
                }
            }
            void RunSystemTimer(int h, int m, int s)
            {
                h = h * SEC_IN_HOUR;
                m = m * SEC_IN_MIN;
                s++;
                EndSystemTimer();
                BeginSystemTimer(h + m + s);
            }
        // Таймер циклических сообщений
            void IRAM_ATTR OnMessageTimer()
            {
                portENTER_CRITICAL_ISR(&messageTimerMux);
                if (messageTime++ >= messageUpdateTime)
                {
                    Informer.automatic();
                    messageTime = 0;
                }
                portEXIT_CRITICAL_ISR(&messageTimerMux);
            }
            void BeginMessageTimer()
            {
                messageTimer = timerBegin(2, 80, true);
                timerAttachInterrupt(messageTimer, &OnMessageTimer, true);
                timerAlarmWrite(messageTimer, 1000000, true);
                timerAlarmEnable(messageTimer);
            }
            void EndMessageTimer()
            {
                if (messageTime != 0)
                {
                    timerEnd(messageTimer);
                }
            }
            void RunMessageTimer()
            {
                EndMessageTimer();
                BeginMessageTimer();
            }
        // Таймер замера поворота сервопривода
            void IRAM_ATTR OnRotAngMeashTimer()
            {
                portENTER_CRITICAL_ISR(&rotAngMeashTimerMux);
                //
                portEXIT_CRITICAL_ISR(&rotAngMeashTimerMux);
            }
            void BeginRotAngMeashTimer()
            {
                rotAngMeashTimer = timerBegin(0, 80, true);
                timerAttachInterrupt(rotAngMeashTimer, &OnRotAngMeashTimer, true);
                timerAlarmWrite(rotAngMeashTimer, 10000, true);
                timerAlarmEnable(rotAngMeashTimer);
            }
            void EndRotAngMeashTimer()
            {
                timerEnd(rotAngMeashTimer);
                //workedTime = 0;
            }
    // Информирование
        void MessageAssembly()
        {
            Ticker::setStaticVar(2, 60, 2000);
            Ticker::setUpdateGeneralTimeInSec(REFRESH_PAGE_IN_SEC);
            Ticker Error_1("ERROR_1", "Возникла ошибка во время записи в память", 28, 2);
            Ticker Welcome("WELCOME", "Мы рады что вы выбрали наше устройство для укачивания малышей!", 28, 1);
            Ticker Condition("CONDITION", "Ошибок не обнаружено, устройство работает штатно!", 28, 1);
            Informer.setEmptyQueueMessage("Добро пожаловать!");
            Informer.setUpdateTimeInSec(REFRESH_PAGE_IN_SEC);
            //Informer.add(Error_1);
            Informer.add(Welcome);
            Informer.add(Condition);
        }
    // Механический старт
        void ExtractParamMechStart(unsigned int arhive)
        {
            //arhive = 3102001401;
            if (arhive == BILLION) // Режим блокировки
            {
                holdInRest = true;
                startSwinging = false;
                startControlled = false;
                startConfirmationDegrees = DEFAUL_CONF_DEGREES;
                startSwingingProg = PROG_NUMBER_DEF;
                startConfirmationTime = DEFAULT_CONF_TIME;
                startControlledProg = PROG_NUMBER_DEF;
            }
            else // Свободное качение
            {
                holdInRest = false;
                arhive -= BILLION * 2;
                if (arhive > BILLION) // Режим ручного запуска
                {
                    arhive -= BILLION;
                    startSwinging = true;
                    startConfirmationDegrees = 0;
                    byte betweenConfirmationDegrees = 0;
                    for (; arhive >= ONE_HUNDRED_MILLIONS; arhive -= ONE_HUNDRED_MILLIONS) // Подсчет градусов (сотни)
                    {
                        betweenConfirmationDegrees++;
                    }
                    startConfirmationDegrees += ONE_HUNDRED * betweenConfirmationDegrees;
                    betweenConfirmationDegrees = 0;
                    for (; arhive >= TEN_MILLIONS; arhive -= TEN_MILLIONS) // Подсчет градусов (десяти)
                    {
                        betweenConfirmationDegrees++;
                    }
                    startConfirmationDegrees += TEN * betweenConfirmationDegrees;
                    betweenConfirmationDegrees = 0;
                    for (; arhive >= MILLION; arhive -= MILLION) // Подсчет градусов более (единицы)
                    {
                        betweenConfirmationDegrees++;
                    }
                    startConfirmationDegrees += betweenConfirmationDegrees;
                    startSwingingProg = 0; // Подсчет номера программы защищенного режима
                    for (; arhive >= ONE_HUNDRED_THOUSANDS; arhive -= ONE_HUNDRED_THOUSANDS) // Подсчет десятков
                    {
                        startSwingingProg++;
                    }
                    startSwingingProg += TEN * startSwingingProg;
                    for (; arhive >= TEN_THOUSANDS; arhive -= TEN_THOUSANDS) // Подсчет единиц
                    {
                        startSwingingProg++;
                    }
                    startSwingingProg += ONE_HUNDRED;
                }
                else
                {
                    startSwinging = false;
                }
                if (arhive > THOUSAND) // Режим защищенного запуска
                {
                    startControlled = true;
                    arhive -= THOUSAND;
                    startConfirmationTime = 0;
                    for (; arhive >= ONE_HUNDRED; arhive -= ONE_HUNDRED) // Подсчет времени
                    {
                        startConfirmationTime++;
                    }
                    startControlledProg = ONE_HUNDRED + arhive; // Номер программы режима запуска раскачкой
                }
                else
                {
                    startControlled = false;
                }
            }
        }
        unsigned int ArhiveParamMechStart()
        {
            if (!holdInRest)
            {
                int arhive = BILLION;
                arhive += (startSwinging) ? (BILLION * 2) + (MILLION * startConfirmationDegrees) + (TEN_THOUSANDS * (startSwingingProg - ONE_HUNDRED)) : BILLION;
                arhive += (startControlled) ? THOUSAND + (ONE_HUNDRED * startConfirmationTime) + (startControlledProg - ONE_HUNDRED) : 0;
                return arhive;
            }
            return BILLION;
        }