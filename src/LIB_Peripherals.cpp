#include "LIB_Peripherals.h"
#define DEBUG
// Последовательная ассимитричная шина
    I2C::I2C(byte pinSda, byte pinClk, int frequency, byte maxAddress)
    {
        this->maxAddress = maxAddress;
        Wire.begin(pinSda, pinClk, frequency);
    }
    byte I2C::CountBus()
    {
        byte error;
        foundBus = 0;
        for(byte i = 1; i <= maxAddress; i++)
        {
            Wire.beginTransmission(i);
            error = Wire.endTransmission();
            if(error == 0)
            {
                foundBus++;
            }
        }
        return foundBus;
    }
    void I2C::writeArray()
    {
        delete[] arrAddress;
        arrAddress = new byte [CountBus()];
        byte error;
        foundBus = 0;
        for(byte i = 1; i <= maxAddress; i++)
        {
            Wire.beginTransmission(i);
            error = Wire.endTransmission();
            if(error == 0)
            {
                arrAddress[foundBus++] = i;
            }
        }
    }
    byte I2C::getAddress()
    {
        byte error;
        byte address = 0;
        foundBus = 0;
        for(byte i = 1; i <= maxAddress; i++)
        {
            Wire.beginTransmission(i);
            error = Wire.endTransmission();
            if(error == 0)
            {
                foundBus++;
                address = i;
            }
        }
        if(foundBus == 0)
        {
            Serial.println("Unit bus not found!");
            Serial.println("-------------------------------");
            return 0;
        }
        else if(foundBus > 1)
        {
            Serial.println("Multiple addresses found.\nImpossible to identify the unit bus!");
            Serial.println("-------------------------------");
            return 0;
        }
        return address;
    }
    byte I2C::getSizeArray()
    {
        return foundBus;
    }
    byte I2C::getAddressOfArray(byte number)
    {
        return arrAddress[number];
    }
// Мультиплексор
    MULTIPLEXOR::MULTIPLEXOR(byte pinS0, byte pinS1, byte pinS2, byte pinS3, byte pinSig)
    {
        this->pinS0 = pinS0;
        this->pinS1 = pinS1;
        this->pinS2 = pinS2;
        this->pinS3 = pinS3;
        this->pinSig = pinSig;
        columns = 2;
        rows = 4;
        pinMode(pinS0, OUTPUT);
        pinMode(pinS1, OUTPUT);
        arrayInternal[0] = pinS0;
        arrayInternal[1] = pinS1;
        arrayInternal[2] = pinS2;
        arrayInternal[3] = pinS3;
        if(pinS2 != 255)
        {
            pinMode(pinS2, OUTPUT);
            arrayInternal[2] = pinS2;
            columns++;
            rows += rows;
        }
        if(pinS3 != 255)
        {
            pinMode(pinS3, OUTPUT);
            arrayInternal[3] = pinS3;
            columns++;
            rows += rows;
        }
        for(byte i = 0; i < columns; i++)
        {
            bool value = true;
            byte counter = 0;
            for(byte j = 0; j < rows; j++)
            {
                if(counter == 0)
                {
                    value = !value;
                }
                counter++;
                arrayExternal[i][j] = value;
                if(i <= 1 && counter > i)
                {
                    counter = 0;
                }
                else if (i == 2 && counter == 4)
                {
                    counter = 0;
                }
                else if (i == 3 && counter == 8)
                {
                    counter = 0;
                }
            }
        }
    }
    void MULTIPLEXOR::set(byte address)
    {
        this->address = address;
        if(address > rows)
        {
            address = rows;
        }
        for(byte i = 0; i < columns; i++)
        {
            if(arrayExternal[i][address])
            {
                digitalWrite(arrayInternal[i], HIGH);
            }
            else
            {
                digitalWrite(arrayInternal[i], LOW);
            }
        }
    }
    byte MULTIPLEXOR::get()
    {
        return pinSig;
    }
// Кнопка по ассимитричной шине
    BUTTON_I2C::BUTTON_I2C(byte pin, BUTTON_I2C &setupButton)
    {
        this->pin = pin;
        mode = setupButton.getMode();
        timeDebounce = setupButton.getTimeDebounce();
        timeClick = setupButton.getTimeClick();
        timeHold = setupButton.getTimeHold();;
        timeLongHold = setupButton.getTimeLongHold();
        timeSticky = setupButton.getTimeSticky();
        status = RELEASE;
        pressStatus = UNDEFINED;
        switched = false;
    }
    BUTTON_I2C::BUTTON_I2C(byte pin, byte mode, BUTTON_I2C &setupButton)
    {
        this->pin = pin;
        this->mode = mode;
        timeDebounce = setupButton.getTimeDebounce();
        timeClick = setupButton.getTimeClick();
        timeHold = setupButton.getTimeHold();
        timeLongHold = setupButton.getTimeLongHold();
        timeSticky = setupButton.getTimeSticky();
        status = RELEASE;
        pressStatus = UNDEFINED;
        switched = false;
    }
    BUTTON_I2C::BUTTON_I2C(byte mode, unsigned short timeDebounce)
    {
        this->mode = mode;
        this->timeDebounce = timeDebounce;
    }
    BUTTON_I2C::BUTTON_I2C(byte mode, unsigned short timeDebounce, unsigned short timeClick, unsigned short timeHold, unsigned short timeLongHold, unsigned short timeSticky)
    {
        this->mode = mode;
        this->timeDebounce = timeDebounce;
        this->timeClick = timeClick;
        this->timeHold = timeHold;
        this->timeLongHold = timeLongHold;
        this->timeSticky = timeSticky;
    }
    BUTTON_I2C::BUTTON_I2C(byte pin, byte mode, unsigned short timeDebounce, unsigned short timeClick, unsigned short timeHold, unsigned short timeLongHold, unsigned short timeSticky)
    {
        this->pin = pin;
        this->mode = mode;
        this->timeDebounce = timeDebounce;
        this->timeClick = timeClick;
        this->timeHold = timeHold;
        this->timeLongHold = timeLongHold;
        this->timeSticky = timeSticky;
        status = RELEASE;
        pressStatus = UNDEFINED;
        switched = false;
    }
    byte BUTTON_I2C::getMode()
    {
        return mode;
    }
    unsigned short BUTTON_I2C::getTimeDebounce()
    {
        return timeDebounce;
    }
    unsigned short BUTTON_I2C::getTimeClick()
    {
        return timeClick;
    }
    unsigned short BUTTON_I2C::getTimeHold()
    {
        return timeHold;
    }
    unsigned short BUTTON_I2C::getTimeLongHold()
    {
        return timeLongHold;
    }
    unsigned short BUTTON_I2C::getTimeSticky()
    {
        return timeSticky;
    }
    void BUTTON_I2C::TimeConflict()
    {
        if(millis() < pressTime)
        {
            unsigned long t = 0;
            elapsedTime = (--t) - pressTime;
            elapsedTime += millis();
        }
        else
        {
            elapsedTime = millis() - pressTime;
        }
    }
    byte BUTTON_I2C::get(SX1509 &sx1509)
    {
        switch (mode)
        {
            case TOUCH:
            {
                if(sx1509.digitalRead(pin))
                {
                    if(status == RELEASE)
                    {
                        status = PRESSED;
                        pressTime = millis();
                    }
                    if(status == PRESSED)
                    {
                        TimeConflict();
                        if(elapsedTime <= timeDebounce && pressStatus != DEBOUNCE)
                        {
                            pressStatus = DEBOUNCE;
                        }
                        else if(elapsedTime > timeDebounce && elapsedTime <= timeClick && pressStatus != CLICK)
                        {
                            pressStatus = CLICK;
                        }
                        else if(elapsedTime > timeClick && elapsedTime <= timeHold && pressStatus != HOLD)
                        {
                            pressStatus = HOLD;
                        }
                        else if(elapsedTime > timeHold && elapsedTime <= timeLongHold && pressStatus != LONG_HOLD)
                        {
                            pressStatus = LONG_HOLD;
                        }
                        else if(elapsedTime > timeLongHold && elapsedTime <= timeSticky && pressStatus != STICKY)
                        {
                            pressStatus = STICKY;
                        }
                        else if(elapsedTime > timeSticky)
                        {
                            pressStatus = UNDEFINED;
                            status = RELEASE;
                            pressTime = 0;
                            elapsedTime = 0;
                        }
                    }
                }
                else
                {
                    pressStatus = UNDEFINED;
                    status = RELEASE;
                    pressTime = 0;
                    elapsedTime = 0;
                }
                break;
            }
            case SWITCH:
            {
                if(sx1509.digitalRead(pin))
                {
                    if(status == RELEASE)
                    {
                        status = PRESSED;
                        pressTime = millis();
                    }
                    if(status == PRESSED)
                    {
                        TimeConflict();
                        if(elapsedTime > timeDebounce && switched == false)
                        {
                            if(pressStatus == PUSH)
                            {
                                pressStatus = PULL;
                            }else
                            {
                                pressStatus = PUSH;
                            }
                            switched = true;
                        }
                    }
                }
                else
                {
                    status = RELEASE;
                    pressTime = 0;
                    elapsedTime = 0;
                    switched = false;
                }
                break;
            }
        }
        return pressStatus;
    }
// Кнопка
    BUTTON::BUTTON(byte pin, BUTTON &setupButton)
    {
        this->pin = pin;
        pinMode(pin, INPUT_PULLDOWN);
        mode = setupButton.getMode();
        timeDebounce = setupButton.getTimeDebounce();
        timeClick = setupButton.getTimeClick();
        timeHold = setupButton.getTimeHold();;
        timeLongHold = setupButton.getTimeLongHold();
        timeSticky = setupButton.getTimeSticky();
        status = RELEASE;
        pressStatus = UNDEFINED;
        switched = false;
    }
    BUTTON::BUTTON(byte pin, byte mode, BUTTON &setupButton)
    {
        this->pin = pin;
        this->mode = mode;
        pinMode(pin, INPUT_PULLDOWN);
        timeDebounce = setupButton.getTimeDebounce();
        timeClick = setupButton.getTimeClick();
        timeHold = setupButton.getTimeHold();
        timeLongHold = setupButton.getTimeLongHold();
        timeSticky = setupButton.getTimeSticky();
        status = RELEASE;
        pressStatus = UNDEFINED;
        switched = false;
    }
    BUTTON::BUTTON(byte mode, unsigned short timeDebounce)
    {
        this->mode = mode;
        this->timeDebounce = timeDebounce;
    }
    BUTTON::BUTTON(byte mode, unsigned short timeDebounce, unsigned short timeClick, unsigned short timeHold, unsigned short timeLongHold, unsigned short timeSticky)
    {
        this->mode = mode;
        this->timeDebounce = timeDebounce;
        this->timeClick = timeClick;
        this->timeHold = timeHold;
        this->timeLongHold = timeLongHold;
        this->timeSticky = timeSticky;
    }
    BUTTON::BUTTON(byte pin, byte mode, unsigned short timeDebounce, unsigned short timeClick, unsigned short timeHold, unsigned short timeLongHold, unsigned short timeSticky)
    {
        this->pin = pin;
        this->mode = mode;
        this->timeDebounce = timeDebounce;
        this->timeClick = timeClick;
        this->timeHold = timeHold;
        this->timeLongHold = timeLongHold;
        this->timeSticky = timeSticky;
        pinMode(pin, INPUT_PULLDOWN);
        status = RELEASE;
        pressStatus = UNDEFINED;
        switched = false;
    }
    byte BUTTON::getMode()
    {
        return mode;
    }
    unsigned short BUTTON::getTimeDebounce()
    {
        return timeDebounce;
    }
    unsigned short BUTTON::getTimeClick()
    {
        return timeClick;
    }
    unsigned short BUTTON::getTimeHold()
    {
        return timeHold;
    }
    unsigned short BUTTON::getTimeLongHold()
    {
        return timeLongHold;
    }
    unsigned short BUTTON::getTimeSticky()
    {
        return timeSticky;
    }
    void BUTTON::TimeConflict()
    {
        if(millis() < pressTime)
        {
            unsigned long t = 0;
            elapsedTime = (--t) - pressTime;
            elapsedTime += millis();
        }
        else
        {
            elapsedTime = millis() - pressTime;
        }
    }
    byte BUTTON::get()
    {
        switch (mode)
        {
            case TOUCH:
            {
                if(digitalRead(pin))
                {
                    if(status == RELEASE)
                    {
                        status = PRESSED;
                        pressTime = millis();
                    }
                    if(status == PRESSED)
                    {
                        TimeConflict();
                        if(elapsedTime <= timeDebounce && pressStatus != DEBOUNCE)
                        {
                            pressStatus = DEBOUNCE;
                        }
                        else if(elapsedTime > timeDebounce && elapsedTime <= timeClick && pressStatus != CLICK)
                        {
                            pressStatus = CLICK;
                        }
                        else if(elapsedTime > timeClick && elapsedTime <= timeHold && pressStatus != HOLD)
                        {
                            pressStatus = HOLD;
                        }
                        else if(elapsedTime > timeHold && elapsedTime <= timeLongHold && pressStatus != LONG_HOLD)
                        {
                            pressStatus = LONG_HOLD;
                        }
                        else if(elapsedTime > timeLongHold && elapsedTime <= timeSticky && pressStatus != STICKY)
                        {
                            pressStatus = STICKY;
                        }
                        else if(elapsedTime > timeSticky)
                        {
                            pressStatus = UNDEFINED;
                            status = RELEASE;
                            pressTime = 0;
                            elapsedTime = 0;
                        }
                    }
                }
                else
                {
                    pressStatus = UNDEFINED;
                    status = RELEASE;
                    pressTime = 0;
                    elapsedTime = 0;
                }
                break;
            }
            case SWITCH:
            {
                if(digitalRead(pin))
                {
                    if(status == RELEASE)
                    {
                        status = PRESSED;
                        pressTime = millis();
                    }
                    if(status == PRESSED)
                    {
                        TimeConflict();
                        if(elapsedTime > timeDebounce && switched == false)
                        {
                            if(pressStatus == PUSH)
                            {
                                pressStatus = PULL;
                            }else
                            {
                                pressStatus = PUSH;
                            }
                            switched = true;
                        }
                    }
                }
                else
                {
                    status = RELEASE;
                    pressTime = 0;
                    elapsedTime = 0;
                    switched = false;
                }
                break;
            }
        }
        return pressStatus;
    }
    void BUTTON::resetPressStatus()
    {
        pressStatus = UNDEFINED;
        status = RELEASE;
        pressTime = 0;
        elapsedTime = 0;
    }
// Драйвер светодиода через последовательную ассимитричную шину
    LED_I2C_DRIVER::LED_I2C_DRIVER()
    {
        duty = ConvertDuty(0);
    }
    void LED_I2C_DRIVER::setDuty(byte _duty)
    {
        this->duty = ConvertDuty(_duty);
    }
    void LED_I2C_DRIVER::turnOn(SX1509 &sx1509, byte pin, byte _duty, int smooth)
    {
        _duty = ConvertDuty(_duty);
        for(byte i = duty; i >= _duty; i--)
        {
            sx1509.pwm(pin, i);
            vTaskDelay(smooth);
            if(i == _duty)
            {
                if(i != duty)
                {
                    duty = i;
                }
                break;
            }
        }
    }
    void LED_I2C_DRIVER::turnOff(SX1509 &sx1509, byte pin, byte _duty, int smooth)
    {
        _duty = ConvertDuty(_duty);
        for(byte i = duty; i <= _duty; i++)
        {
            sx1509.pwm(pin, i);
            vTaskDelay(smooth);
            if(i == _duty)
            {
                if(i != duty)
                {
                    duty = i;
                }
                break;
            }
        }
    }
    void LED_I2C_DRIVER::smoothBlinking(SX1509 &sx1509, byte pin, int intervalBetweenImpulses, int delayBetweenWaves, byte maxDuty, byte minDuty)
    {
        setDuty(minDuty);
        turnOn(sx1509, pin, maxDuty, intervalBetweenImpulses);
        turnOff(sx1509, pin, minDuty, intervalBetweenImpulses);
        vTaskDelay(delayBetweenWaves);
    }
    void LED_I2C_DRIVER::risingSaw(SX1509 &sx1509, byte pin, int intervalBetweenImpulses, int delayBetweenWaves, byte maxDuty, byte minDuty)
    {
        maxDuty = ConvertDuty(maxDuty);
        minDuty = ConvertDuty(minDuty);
        for(byte i = minDuty; i >= maxDuty; i--)
        {
            sx1509.pwm(pin, i);
            vTaskDelay(intervalBetweenImpulses);
        }
        vTaskDelay(delayBetweenWaves);
    }
    void LED_I2C_DRIVER::ascendingSaw(SX1509 &sx1509, byte pin, int intervalBetweenImpulses, int delayBetweenWaves, byte maxDuty, byte minDuty)
    {
        maxDuty = ConvertDuty(maxDuty);
        minDuty = ConvertDuty(minDuty);
        for(byte i = maxDuty; i <= minDuty; i++)
        {
            sx1509.pwm(pin, i);
            vTaskDelay(intervalBetweenImpulses);
        }
        vTaskDelay(delayBetweenWaves);
    }
    void LED_I2C_DRIVER::blinking(SX1509 &sx1509, byte pin, int blinkSeries, int intervalBetweenBlinks, int intervalBetweenSeries, byte maxDuty, byte minDuty)
    {
        bool counter = false;
        int currentDuty;
        for(int i = 0; i <= (blinkSeries * 2); i++)
        {
            if(counter)
            {
                currentDuty = ConvertDuty(maxDuty);
                counter = false;
            }
            else
            {
                currentDuty = ConvertDuty(minDuty);
                counter = true;
            }
            sx1509.pwm(pin, currentDuty);
            vTaskDelay(intervalBetweenBlinks);
        }
        vTaskDelay(intervalBetweenSeries);
    }
    byte LED_I2C_DRIVER::ConvertDuty(byte _duty)
    {
        return 255 - _duty;
    }
    byte LED_I2C_DRIVER::getDuty()
    {
        return ConvertDuty(duty);
    }
    byte LED_I2C_DRIVER::getMaxDuty()
    {
        return 255;
    }
// Драйвер RGB светодиода через последовательную ассимитричную шину
    RGB_LED_I2C_DRIVER::RGB_LED_I2C_DRIVER(){}
    void RGB_LED_I2C_DRIVER::transfusion(SX1509 &ledI2cDriver, byte rPin, byte gPin, byte bPin, int intervalBetweenImpulses, int duty)
    {
        #define ROW 6
        #define COL 3
        byte array[ROW][COL]
        {
            {0, 0, 1},
            {0, 1, 1},
            {1, 1, 1},
            {1, 0, 1},
            {1, 0, 0},
            {0, 1, 0}
        };
        bool currentR = array[ROW - 1][0];
        bool currentG = array[ROW - 1][1];
        bool currentB = array[ROW - 1][2];
        bool nextR = false;
        bool nextG = false;
        bool nextB = false;
        for(byte row = 0; row < ROW; row++)
        {
            int upDuty = 0;
            int downDuty = duty;
            for(byte col = 0; col < COL; col++)
            {
                if(col == 0)
                {
                    nextR = array[row][col];
                }
                else if(col == 1)
                {
                    nextG = array[row][col];
                }
                else if(col == 2)
                {
                    nextB = array[row][col];
                }
            }
            for(int i = 0; i < duty; i++)
            {
                upDuty++;
                downDuty--;
                if(currentR != nextR)
                {
                    if(nextR == 1)
                    {
                        
                        ledI2cDriver.pwm(rPin, upDuty);
                    }
                    else if(nextR == 0)
                    {
                        ledI2cDriver.pwm(rPin, downDuty);
                    }
                }
                if(currentG != nextG)
                {
                    if(nextG == 1)
                    {
                        ledI2cDriver.pwm(gPin, upDuty);
                    }
                    else if(nextG == 0)
                    {
                        ledI2cDriver.pwm(gPin, downDuty);
                    }
                }
                if(currentB != nextB)
                {
                    if(nextB == 1)
                    {
                        ledI2cDriver.pwm(bPin, upDuty);
                    }
                    else if(nextB == 0)
                    {
                        ledI2cDriver.pwm(bPin, downDuty);
                    }
                }
                vTaskDelay(intervalBetweenImpulses);
            }
            currentR = nextR;
            currentG = nextG;
            currentB = nextB;
        }
    }
// Драйвер светодиода
    LED_DRIVER::LED_DRIVER(uint8_t channel, double frequency, uint8_t resolution)
    {
        this->channel = channel;
        this->frequency = frequency;
        this->resolution = resolution;
        ledcSetup(channel, frequency, resolution);
    }
    void LED_DRIVER::setFrequency(double frequency)
    {
        ledcSetup(getChannel(), frequency, getResolution());
    }
    void LED_DRIVER::setResolution(uint8_t resolution)
    {
        ledcSetup(getChannel(), getFrequency(), resolution);
    }
    void LED_DRIVER::setDuty(int duty)
    {
        this->duty = duty;
        ledcWrite(getChannel(), duty);
    }
    void LED_DRIVER::turnOn(int duty, int smooth)
    {
        for(int i = getDuty(); i <= duty; i++)
        {
            setDuty(i);
            vTaskDelay(smooth);
        }
    }
    void LED_DRIVER::turnOff(int duty, int smooth)
    {
        for(int i = getDuty(); i >= duty; i--)
        {
            setDuty(i);
            vTaskDelay(smooth);
        }
    }
    void LED_DRIVER::smoothBlinking(int intervalBetweenImpulses, int delayBetweenWaves, int maxDuty, int minDuty)
    {
        risingSaw(intervalBetweenImpulses, delayBetweenWaves, maxDuty, minDuty);
        ascendingSaw(intervalBetweenImpulses, delayBetweenWaves, maxDuty, minDuty);
    }
    void LED_DRIVER::risingSaw(int intervalBetweenImpulses, int delayBetweenWaves, int maxDuty, int minDuty)
    {
        for(int i = minDuty; i <= maxDuty; i++)
        {
            setDuty(i);
            if(intervalBetweenImpulses != 0)
            {
                vTaskDelay(intervalBetweenImpulses);
            }
        }
        vTaskDelay(delayBetweenWaves);
    }
    void LED_DRIVER::ascendingSaw(int intervalBetweenImpulses, int delayBetweenWaves, int maxDuty, int minDuty)
    {
        for(int i = maxDuty; i >= minDuty; i--)
        {
            setDuty(i);
            if(intervalBetweenImpulses != 0)
            {
                vTaskDelay(intervalBetweenImpulses);
            }
        }
        vTaskDelay(delayBetweenWaves);
    }
    void LED_DRIVER::blinking(int blinkSeries, int intervalBetweenBlinks, int intervalBetweenSeries, int maxDuty, int minDuty)
    {
        bool counter = false;
        int currentDuty;
        for(int i = 0; i <= (blinkSeries * 2); i++)
        {
            if(counter)
            {
                currentDuty = maxDuty;
                counter = false;
            }
            else
            {
                currentDuty = minDuty;
                counter = true;
            }
            setDuty(currentDuty);
            vTaskDelay(intervalBetweenBlinks);
        }
        vTaskDelay(intervalBetweenSeries);
    }
    uint8_t LED_DRIVER::getChannel()
    {
        return channel;
    }
    double LED_DRIVER::getFrequency()
    {
        return frequency;
    }
    uint8_t LED_DRIVER::getResolution()
    {
        return resolution;
    }
    int LED_DRIVER::getDuty()
    {
        return duty;
    }
    int LED_DRIVER::getMaxDuty()
    {
        return pow(2,resolution);
    }
// Драйвер RGB светодиода
    RGB_LED_DRIVER::RGB_LED_DRIVER(){}
    void RGB_LED_DRIVER::transfusion(LED_DRIVER &redLedDriver, LED_DRIVER &greenLedDriver, LED_DRIVER &blueLedDriver, int intervalBetweenImpulses, int duty)
    {
        #define ROW 6
        #define COL 3
        byte array[ROW][COL]
        {
            {0, 0, 1},
            {0, 1, 1},
            {1, 1, 1},
            {1, 0, 1},
            {1, 0, 0},
            {0, 1, 0}
        };
        bool currentR = array[ROW - 1][0];
        bool currentG = array[ROW - 1][1];
        bool currentB = array[ROW - 1][2];
        bool nextR = false;
        bool nextG = false;
        bool nextB = false;
        for(byte row = 0; row < ROW; row++)
        {
            int upDuty = 0;
            int downDuty = duty;
            for(byte col = 0; col < COL; col++)
            {
                if(col == 0)
                {
                    nextR = array[row][col];
                }
                else if(col == 1)
                {
                    nextG = array[row][col];
                }
                else if(col == 2)
                {
                    nextB = array[row][col];
                }
            }
            for(int i = 0; i < duty; i++)
            {
                upDuty++;
                downDuty--;
                if(currentR != nextR)
                {
                    if(nextR == 1)
                    {
                        redLedDriver.setDuty(upDuty);
                    }
                    else if(nextR == 0)
                    {
                        redLedDriver.setDuty(downDuty);
                    }
                }
                if(currentG != nextG)
                {
                    if(nextG == 1)
                    {
                        greenLedDriver.setDuty(upDuty);
                    }
                    else if(nextG == 0)
                    {
                        greenLedDriver.setDuty(downDuty);
                    }
                }
                if(currentB != nextB)
                {
                    if(nextB == 1)
                    {
                        blueLedDriver.setDuty(upDuty);
                    }
                    else if(nextB == 0)
                    {
                        blueLedDriver.setDuty(downDuty);
                    }
                }
                vTaskDelay(intervalBetweenImpulses);
            }
            currentR = nextR;
            currentG = nextG;
            currentB = nextB;
        }
    }
// Светодиод
    LED::LED(byte pin, LED_DRIVER &ledDriver)
    {
        this->pin = pin;
        ledcAttachPin(pin, ledDriver.getChannel());
    }
// Драйвер зуммера через последовательную ассимитричную шину
    BUZZER_I2C_DRIVER::BUZZER_I2C_DRIVER(){}
    void BUZZER_I2C_DRIVER::play(SX1509 &sx1509, byte pin, byte countBeep, byte durationsBeep, byte durationspaused, byte volume)
    {
        for(byte i = 0; i < countBeep; i++)
        {
            sx1509.analogWrite(pin, Volume(volume));
            vTaskDelay(durationsBeep);
            sx1509.analogWrite(pin, 0);
            vTaskDelay(durationspaused);
        }
        sx1509.analogWrite(pin, 0);
    }
    byte BUZZER_I2C_DRIVER::Volume(byte volume)
    {
        switch (volume)
        {
            case 1:
                volume = 10;
                break;
            case 2:
                volume = 20;
                break;
            case 3:
                volume = 30;
                break;
            case 4:
                volume = 40;
                break;
            case 5:
                volume = 60;
                break;
            case 6:
                volume = 80;
                break;
            case 7:
                volume = 100;
                break;
            case 8:
                volume = 150;
                break;
            default:
                volume = 255;
                break;
        }
        return volume;
    }
// Драйвер зуммера
    // Ноты
        #define NONE 0
        #define NOTE_B0  31
        #define NOTE_C1  33
        #define NOTE_CS1 35
        #define NOTE_D1  37
        #define NOTE_DS1 39
        #define NOTE_E1  41
        #define NOTE_F1  44
        #define NOTE_FS1 46
        #define NOTE_G1  49
        #define NOTE_GS1 52
        #define NOTE_A1  55
        #define NOTE_AS1 58
        #define NOTE_B1  62
        #define NOTE_C2  65
        #define NOTE_CS2 69
        #define NOTE_D2  73
        #define NOTE_DS2 78
        #define NOTE_E2  82
        #define NOTE_F2  87
        #define NOTE_FS2 93
        #define NOTE_G2  98
        #define NOTE_GS2 104
        #define NOTE_A2  110
        #define NOTE_AS2 117
        #define NOTE_B2  123
        #define NOTE_C3  131
        #define NOTE_CS3 139
        #define NOTE_D3  147
        #define NOTE_DS3 156
        #define NOTE_E3  165
        #define NOTE_F3  175
        #define NOTE_FS3 185
        #define NOTE_G3  196
        #define NOTE_GS3 208
        #define NOTE_A3  220
        #define NOTE_AS3 233
        #define NOTE_B3  247
        #define NOTE_C4  262
        #define NOTE_CS4 277
        #define NOTE_D4  294
        #define NOTE_DS4 311
        #define NOTE_E4  331
        #define NOTE_F4  349
        #define NOTE_FS4 369
        #define NOTE_G4  392
        #define NOTE_GS4 415
        #define NOTE_A4  440
        #define NOTE_AS4 466
        #define NOTE_B4  493
        #define NOTE_C5  523
        #define NOTE_CS5 544
        #define NOTE_D5  587
        #define NOTE_DS5 622
        #define NOTE_E5  659
        #define NOTE_F5  698
        #define NOTE_FS5 739
        #define NOTE_G5  784
        #define NOTE_GS5 831
        #define NOTE_A5  880
        #define NOTE_AS5 932
        #define NOTE_B5  988
        #define NOTE_C6  1047
        #define NOTE_CS6 1109
        #define NOTE_D6  1175
        #define NOTE_DS6 1245
        #define NOTE_E6  1319
        #define NOTE_F6  1397
        #define NOTE_FS6 1480
        #define NOTE_G6  1568
        #define NOTE_GS6 1661
        #define NOTE_A6  1760
        #define NOTE_AS6 1865
        #define NOTE_B6  1976
        #define NOTE_C7  2093
        #define NOTE_CS7 2217
        #define NOTE_D7  2349
        #define NOTE_DS7 2489
        #define NOTE_E7  2637
        #define NOTE_F7  2794
        #define NOTE_FS7 2960
        #define NOTE_G7  3136
        #define NOTE_GS7 3322
        #define NOTE_A7  3520
        #define NOTE_AS7 3729
        #define NOTE_B7  3951
        #define NOTE_C8  4186
        #define NOTE_CS8 4435
        #define NOTE_D8  4699
        #define NOTE_DS8 4978
    // Предустановленные мелодии
        // Двойной дискретный сигнал
            int notes_doubleBeep[] = {NOTE_DS8, NOTE_DS8};
            int durations_doubleBeep[] = {100, 100};
        // Тройной дискретный сигнал
            int notes_tripleBeep[] = {NOTE_DS8, NOTE_DS8, NOTE_DS8};
            int durations_tripleBeep[] = {100, 90, 80};
        // Бетховен: к Элизе
            int notes_BeethovenFurElise[] = 
            {
                NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_A4, NONE, NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4, NONE, NOTE_E4, NOTE_A4, NOTE_B4, NOTE_C5,
            };
            int durations_BeethovenFurElise[] =
            {
                125, 125, 125, 125, 125, 125, 125, 125, 250, 125, 125, 125, 125, 250, 125, 125, 125, 125, 250
            };
        // Имперский марш
            int notes_TheImperialMarch[] = 
            {
                NOTE_G4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_AS4, NOTE_G4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_D5,
                NOTE_D5, NOTE_D5, NOTE_DS5, NOTE_AS4, NOTE_FS4, NOTE_DS4, NOTE_AS4, NOTE_G4, NOTE_G5, NOTE_G4,
                NOTE_G4, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_GS4, NOTE_CS5, NOTE_C5,
                NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_DS4, NOTE_FS4, NOTE_DS4, NOTE_AS4, NOTE_G4
            };
            int durations_TheImperialMarch[] =
            {
                350, 350, 350, 250, 100, 350, 250, 100, 700, 350,
                350, 350, 250, 100, 350, 250, 100, 700, 350, 250,
                100, 350, 250, 100, 100, 100, 450, 150, 350, 250,
                100, 100, 100, 450, 150, 350, 250, 100, 750
            };
        // Марио
            int notes_Mario[] = 
            {
                NOTE_E7, NOTE_E7, NONE, NOTE_E7,
                NONE, NOTE_C7, NOTE_E7, NONE,
                NOTE_G7, NONE, NONE,  NONE,
                NOTE_G6, NONE, NONE, NONE,
                NOTE_C7, NONE, NONE, NOTE_G6,
                NONE, NONE, NOTE_E6, NONE,
                NONE, NOTE_A6, NONE, NOTE_B6,
                NONE, NOTE_AS6, NOTE_A6, NONE,
                NOTE_G6, NOTE_E7, NOTE_G7,
                NOTE_A7, NONE, NOTE_F7, NOTE_G7,
                NONE, NOTE_E7, NONE, NOTE_C7,
                NOTE_D7, NOTE_B6, NONE, NONE,
                NOTE_C7, NONE, NONE, NOTE_G6,
                NONE, NONE, NOTE_E6, NONE,
                NONE, NOTE_A6, NONE, NOTE_B6,
                NONE, NOTE_AS6, NOTE_A6, NONE,
                NOTE_G6, NOTE_E7, NOTE_G7,
                NOTE_A7, NONE, NOTE_F7, NOTE_G7,
                NONE, NOTE_E7, NONE, NOTE_C7,
                NOTE_D7, NOTE_B6, NONE, NONE
            };
            int durations_Mario[] =
            {
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                9, 9, 9,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12, 
                9, 9, 9,
                12, 12, 12, 12,
                12, 12, 12, 12,
                12, 12, 12, 12
            };
        // Подземный мир Марио
            int notes_MarioUnderWorld[] = 
            {
                NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,NOTE_AS3, NOTE_AS4, NONE, NONE,
                NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, NONE, NONE,
                NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,NOTE_DS3, NOTE_DS4, NONE, NONE,
                NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,NOTE_DS3, NOTE_DS4, NONE,
                NONE, NOTE_DS4, NOTE_CS4, NOTE_D4,
                NOTE_CS4, NOTE_DS4, NOTE_DS4, NOTE_GS3, NOTE_G3, NOTE_CS4,
                NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
                NOTE_GS4, NOTE_DS4, NOTE_B3,  NOTE_AS3, NOTE_A3, NOTE_GS3, NONE, NONE, NONE
            };
            int durations_MarioUnderWorld[] =
            {
                12, 12, 12, 12, 12, 12, 6, 3,
                12, 12, 12, 12, 12, 12, 6, 3,
                12, 12, 12, 12, 12, 12, 6,
                3, 12, 12, 12, 12,
                12, 12, 6, 6, 18, 18, 18,
                6, 6, 6, 6, 6, 6,
                18, 18, 18, 18, 18, 18, 10, 10, 10,
                10, 10, 10, 3, 3, 3
            };
        // Сумасшедшая лягушка
            int notes_CrazyFrog[] = 
            {
                NOTE_D4, NONE,    NOTE_F4, NOTE_D4, NONE,    NOTE_D4, NOTE_G4,  NOTE_D4, NOTE_C4,
                NOTE_D4, NONE,    NOTE_A4, NOTE_D4, NONE,    NOTE_D4, NOTE_AS4, NOTE_A4, NOTE_F4,
                NOTE_D4, NOTE_A4, NOTE_D5, NOTE_D4, NOTE_C4, NONE,    NOTE_C4,  NOTE_A3, NOTE_E4,
                NOTE_D4, NONE,    NOTE_D4, NOTE_D4
            };
            int durations_CrazyFrog[] =
            {
                8, 8, 6, 16, 16, 16, 8, 8, 8, 
                8, 8, 6, 16, 16, 16, 8, 8, 8,
                8, 8, 8, 16, 16, 16, 16, 8, 8,
                2, 8, 4, 4
            };
        // Пираты Карибского моря
            int notes_Pirates[] = 
            {
                NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
                NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, 
                NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,  
                NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, 
                NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4,
                NONE,    NOTE_A3, NOTE_C4, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_E4, NOTE_F4,
                NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_D4,
                NONE,    NONE,    NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4,
                NOTE_G4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4,
                NOTE_A4, NOTE_D4, NONE,    NOTE_D4, NOTE_E3, NOTE_F4, NOTE_F4, NOTE_G4,
                NOTE_A4, NOTE_D4, NONE,    NOTE_D4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_F4,
                NOTE_D4, NOTE_D4
            };
            int durations_Pirates[] =
            {
                4, 8, 4, 8, 4, 8, 8, 8,
                8, 4, 8, 4, 8, 4, 8, 8,
                8, 8, 4, 8, 4, 8, 4, 8,
                8, 8, 8, 4, 4, 8, 8, 4,
                4, 8, 8, 4, 4, 8, 8, 8,
                4, 8, 8, 8, 4, 4, 8, 8,
                4, 4, 8, 8, 4, 4, 8, 4,
                4, 8, 8, 8, 8, 4, 4, 8,
                8, 4, 4, 8, 8, 4, 4, 8,
                8, 8, 4, 8, 8, 8, 4, 4,
                4, 8, 4, 8, 8, 8, 4, 4,
                8, 4
            };
    BUZZER_DRIVER::BUZZER_DRIVER(uint8_t channel)
    {
        this->channel = channel;
        paused = 0;
    }
    uint8_t BUZZER_DRIVER::getChannel()
    {
        return channel;
    }
    void BUZZER_DRIVER::playOwnMelody(int notes[], int durations[])
    {
        stop = false;
        do
        {
            for(int i = 0; i < size; i++)
            {
                if(stop)
                {
                    break;
                }
                if(notes[i] != 0)
                {
                    ledcWriteTone(getChannel(), notes[i]);
                }
                else
                {
                    ledcWriteTone(getChannel(), DR_REG_LEDC_BASE);
                }
                vTaskDelay(durations[i]);
                ledcWriteTone(getChannel(), DR_REG_LEDC_BASE);
                vTaskDelay(durations[i]);
            }
            ledcWriteTone(getChannel(), DR_REG_LEDC_BASE);
            vTaskDelay(paused);
        } while (repeat);
    }
    void BUZZER_DRIVER::playOwnMelody(int notes[], int durations[], int convertDurationNote, float melodyPace)
    {
        stop = false;
        do
        {
            for(int i = 0; i < size; i++)
            {
                if(stop)
                {
                    break;
                }
                if(notes[i] != 0)
                {
                    ledcWriteTone(getChannel(), notes[i]);
                }
                else
                {
                    ledcWriteTone(getChannel(), DR_REG_LEDC_BASE);
                }
                vTaskDelay(convertDurationNote / durations[i] * melodyPace);
                ledcWriteTone(getChannel(), DR_REG_LEDC_BASE);
                vTaskDelay(durations[i] * melodyPace);
            }
            ledcWriteTone(getChannel(), DR_REG_LEDC_BASE);
            vTaskDelay(paused);
        } while (repeat);
    }
    void BUZZER_DRIVER::pausedBetweenReplay(unsigned int paused)
    {
        this->paused = paused;
    }
    void BUZZER_DRIVER::repeatPlay(bool repeat)
    {
        this->repeat = repeat;
    }
    void BUZZER_DRIVER::stopPlaying()
    {
        stop = true;
    }
    void BUZZER_DRIVER::convertVolume(int notes[], int volume)
    {
        #define FREQANCY 1700
        delete[] convertNotes;
        convertNotes = new int [size];
        switch (volume)
        {
            case 1:
                volume = 9 * FREQANCY;
                break;
            case 2:
                volume = 8 * FREQANCY;
                break;
            case 3:
                volume = 7 * FREQANCY;
                break;
            case 4:
                volume = 6 * FREQANCY;
                break;
            case 5:
                volume = 5 * FREQANCY;
                break;
            case 6:
                volume = 4 * FREQANCY;
                break;
            case 7:
                volume = 3 * FREQANCY;
                break;
            case 8:
                volume = 2 * FREQANCY;
                break;
            default:
                volume = 1;
                break;
        }
        for(int i = 0; i < size; i++)
        {
            convertNotes[i] = notes[i] + volume;
        }
    }
    void BUZZER_DRIVER::playDoubleDeep(int volume)
    {
        size = sizeof(notes_doubleBeep) / sizeof(notes_doubleBeep[0]);
        convertVolume(notes_doubleBeep, volume);
        playOwnMelody(convertNotes, durations_doubleBeep);
    }
    void BUZZER_DRIVER::playTripleDeep(int volume)
    {
        size = sizeof(notes_tripleBeep) / sizeof(notes_tripleBeep[0]);
        convertVolume(notes_tripleBeep, volume);
        playOwnMelody(convertNotes, durations_tripleBeep);
    }
    void BUZZER_DRIVER::playBeethovenFurElise()
    {
        size = sizeof(notes_BeethovenFurElise) / sizeof(notes_BeethovenFurElise[0]);
        playOwnMelody(notes_BeethovenFurElise, durations_BeethovenFurElise);
    }
    void BUZZER_DRIVER::playTheImperialMarch()
    {
        size = sizeof(notes_TheImperialMarch) / sizeof(notes_TheImperialMarch[0]);
        playOwnMelody(notes_TheImperialMarch, durations_TheImperialMarch);
    }
    void BUZZER_DRIVER::playMario()
    {
        size = sizeof(notes_Mario) / sizeof(notes_Mario[0]);
        playOwnMelody(notes_Mario, durations_Mario, 1000, 1.80);
    }
    void BUZZER_DRIVER::playMarioUnderWorld()
    {
        size = sizeof(notes_MarioUnderWorld) / sizeof(notes_MarioUnderWorld[0]);
        playOwnMelody(notes_MarioUnderWorld, durations_MarioUnderWorld, 1000, 1.80);
    }
    void BUZZER_DRIVER::playCrazyFrog()
    {
        size = sizeof(notes_CrazyFrog) / sizeof(notes_CrazyFrog[0]);
        playOwnMelody(notes_CrazyFrog, durations_CrazyFrog, 1200, 1.50);
    }
    void BUZZER_DRIVER::playPirates()
    {
        size = sizeof(notes_Pirates) / sizeof(notes_Pirates[0]);
        playOwnMelody(notes_Pirates, durations_Pirates, 1000, 1.05);
    }
// Зуммер
    BUZZER::BUZZER(byte pin, BUZZER_DRIVER &BuzzerDriver)
    {
        this->pin = pin;
        pinMode(pin, OUTPUT);
        ledcAttachPin(pin, BuzzerDriver.getChannel());
    }
// Инфракрасный сенсор
    PIR::PIR(byte pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT);
    }
    bool PIR::get()
    {
        if(digitalRead(pin) == HIGH)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
// Термометр
    /* TEMPERATURE::TEMPERATURE(){}
    TEMPERATURE::TEMPERATURE(byte pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT);
    }
    byte TEMPERATURE::get(byte pin, MULTIPLEXOR &multiplexor)
    {
        this->pin = pin;
        multiplexor.set(pin);
        pin = multiplexor.get();
        pinMode(pin, INPUT);
        OneWire OneWire(pin);
        DallasTemperature DS18B20(&OneWire);
        DS18B20.begin();
        DS18B20.requestTemperatures();
        return DS18B20.getTempCByIndex(0);
    }
    byte TEMPERATURE::get()
    {
        OneWire OneWire(pin);
        DallasTemperature DS18B20(&OneWire);
        DS18B20.begin();
        DS18B20.requestTemperatures();
        return DS18B20.getTempCByIndex(0);
    } */
// Вольтметр
    #define VOLT_CONST 168.00
    VOLTMETER::VOLTMETER(){}
    VOLTMETER::VOLTMETER(byte pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT);
    }
    float VOLTMETER::get()
    {
        return analogRead(pin) / VOLT_CONST;
    }
    float VOLTMETER::get(byte pin, MULTIPLEXOR &multiplexor)
    {
        this->pin = pin;
        multiplexor.set(pin);
        pin = multiplexor.get();
        pinMode(pin, INPUT);
        return analogRead(pin) / VOLT_CONST;
    }
// Датчик дыма
    SMOKE::SMOKE(){}
    SMOKE::SMOKE(byte pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT);
    }
    short SMOKE::get()
    {
        return analogRead(pin);
    }
    short SMOKE::get(byte pin, MULTIPLEXOR &multiplexor)
    {
        this->pin = pin;
        multiplexor.set(pin);
        pin = multiplexor.get();
        pinMode(pin, INPUT);
        return analogRead(pin);
    }
// Датчик звука
    VOICE::VOICE(uint8_t pin)
    {
        this->_pin = pin;
        pinMode(_pin, INPUT);
        _limit = 10;
    }
    void VOICE::setLimit(short limit)
    {
        this->_limit = limit;
    }
    short VOICE::getLimit()
    {
        return _limit;
    }
    short VOICE::get()
    {
        return analogRead(_pin);
    }
    bool VOICE::getAlarm()
    {
        if(analogRead(_pin) > getLimit())
        {
            return true;
        }
        return false;
    }
// Датчик линии
    LINE::LINE(byte pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT);
    }
    byte LINE::get()
    {
        return !digitalRead(pin);
    }
// Магнитный концевик
    HALL::HALL(){}
    HALL::HALL(byte pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT);
    }
    bool HALL::get()
    {
        if(digitalRead(pin) == HIGH)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool HALL::get(byte pin, MULTIPLEXOR &multiplexor)
    {
        multiplexor.set(pin);
        pin = multiplexor.get();
        pinMode(pin, INPUT);
        if(digitalRead(pin) == HIGH)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
// Ультразвуковой дальномер
    ULTRASONIC::ULTRASONIC(byte pinTrig, byte pinEcho)
    {
        this->pinTrig = pinTrig;
        this->pinEcho = pinEcho;
        pinMode(pinTrig, OUTPUT);
        pinMode(pinEcho, INPUT);
    }
    double ULTRASONIC::get(float ambientTemperature)
    {
        #define MIN_PRESET_TEMP -20
        #define MAX_PRESET_TEMP 50
        #define DEFAULT_TEMP 25
        this->ambientTemperature = ambientTemperature;
        float temperature = 0;
        if(ambientTemperature > MIN_PRESET_TEMP && ambientTemperature < MAX_PRESET_TEMP)
        {
            temperature = ambientTemperature;
        }
        else
        {
            temperature = DEFAULT_TEMP;
        }
        digitalWrite(pinTrig, LOW);
        delayMicroseconds(2);
        digitalWrite(pinTrig, HIGH);
        delayMicroseconds(10);
        digitalWrite(pinTrig, LOW);
        unsigned long durationMicroSec = pulseIn(pinEcho, HIGH);
        double speedOfSoundInCmPerMs = 0.03313 + 0.0000606 * temperature;
        value = durationMicroSec / 2.0 * speedOfSoundInCmPerMs;
        if(value == 0 || value > 400) 
        {
            value = -1.0;
        }
        return value;
    }
// Реле по последовательной ассимитричной шине
    RELAY_I2C::RELAY_I2C(){}
    void RELAY_I2C::set(SX1509 &sx1509, byte pin, byte command)
    {
        if(command == ENABLE)
        {
            sx1509.digitalWrite(pin, HIGH);
        }
        else if(command == DISABLE)
        {
            sx1509.digitalWrite(pin, LOW);
        }
    }
// Реле
    RELAY::RELAY(){}
    RELAY::RELAY(byte pin)
    {
        this->pin = pin;
        pinMode(pin, OUTPUT);
    }
    void RELAY::set(byte command)
    {
        this->command = command;
        if(command == ENABLE)
        {
            digitalWrite(pin, HIGH);
        }
        else if(command == DISABLE)
        {
            digitalWrite(pin, LOW);
        }
    }
    void RELAY::set(byte pin, MULTIPLEXOR &multiplexor, byte command)
    {
        this->pin = pin;
        this->command = command;
        multiplexor.set(pin);
        pin = multiplexor.get();
        pinMode(pin, OUTPUT);
        if(command == ENABLE)
        {
            digitalWrite(pin, HIGH);
        }
        else if(command == DISABLE)
        {
            digitalWrite(pin, LOW);
        }
    }
// Потенциометр
    POTENCIOMETER::POTENCIOMETER(byte pinUd, byte pinNc, byte pinCs)
    {
        this->pinUd = pinUd;
        this->pinNc = pinNc;
        this->pinCs = pinCs;
        pinMode(pinUd, OUTPUT);
        pinMode(pinNc, OUTPUT);
        pinMode(pinCs, OUTPUT);
        digitalWrite(pinCs, HIGH);
    }
    void POTENCIOMETER::set(byte command)
    {
        this->command = command;
        if(command == UP)
        {
            digitalWrite(pinUd, HIGH);
            digitalWrite(pinNc, HIGH);
            digitalWrite(pinCs, LOW);
            delayMicroseconds(1);
            digitalWrite(pinNc, LOW);
            delayMicroseconds(1);
            digitalWrite(pinNc, HIGH);
            delayMicroseconds(1);
            digitalWrite(pinCs, HIGH);
        }else if(command == DOWN)
        {
            digitalWrite(pinUd, LOW);
            digitalWrite(pinNc, HIGH);
            digitalWrite(pinCs, LOW);
            delayMicroseconds(1);
            digitalWrite(pinNc, LOW);
            delayMicroseconds(1);
            digitalWrite(pinNc, HIGH);
            delayMicroseconds(1);
            digitalWrite(pinCs, HIGH);
        }
    }
// Микроволновой радар
    MICROWAVE::MICROWAVE(byte pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT);
    }
    double MICROWAVE::get()
    {
        #define AVERAGE 1
        #define DOPPLER_DIV 19
        float samples[AVERAGE];
        noInterrupts();
        pulseIn(pin, HIGH);
        unsigned int pulseLength = 0;
        for(byte x = 0; x < AVERAGE; x++)
        {
            pulseLength = pulseIn(pin, HIGH); 
            pulseLength += pulseIn(pin, LOW);    
            samples[x] = pulseLength;
        }
        interrupts();
        bool samplesOk = true;
        float nbPulsesTime = samples[0];
        for(byte x = 1; x < AVERAGE; x++)
        {
            nbPulsesTime += samples[x];
            if((samples[x] > samples[0] * 2) || (samples[x] < samples[0] / 2))
            {
                samplesOk = true;
            }
        }
        if(samplesOk)
        {
            float Ttime = nbPulsesTime / AVERAGE;
            float Freq = 1000000 / Ttime;
            value = Freq / DOPPLER_DIV;
        }
        return value;
    }
// Драйвер мотора
    DRIVER::DRIVER(byte pinEn, byte pinCw, byte pinClk)
    {
        this->pinEn = pinEn;
        this->pinCw = pinCw;
        this->pinClk = pinClk;
        pinMode(pinEn, OUTPUT);
        digitalWrite(pinEn, LOW);
        pinMode(pinClk, OUTPUT);
        pinMode(pinCw, OUTPUT);
    }
    void DRIVER::setDirection(bool direction)
    {
        this->direction = direction;
        if(direction)
        {
            digitalWrite(pinCw, HIGH);
        }
        else
        {
            digitalWrite(pinCw, LOW);
        }
    }
    void DRIVER::setSwitch(byte switchPosition)
    {
        this->switchPosition = switchPosition;
        switch (switchPosition)
        {
            case ENABLE:
            {
                digitalWrite(pinEn, LOW);
                break;
            }
            case DISABLE:
            {
                digitalWrite(pinEn, HIGH);
                break;
            }
        }
    }
    void DRIVER::step(short int currentDelay)
    {
        this->currentDelay = currentDelay;
        digitalWrite(pinClk, HIGH);
        delayMicroseconds(currentDelay);
        digitalWrite(pinClk, LOW);
        delayMicroseconds(currentDelay);
    }
// Энкодер
    ENCODER::ENCODER(byte pin01, byte pin02)
    {
        this->pin01 = pin01;
        this->pin02 = pin02;
        pinMode(pin01, INPUT);
        pinMode(pin02, INPUT);
    }
    ENCODER::ENCODER(int baseCircleDriver, short baseDelayBetweenSteps, byte lotSize, float delta)
    {
        this->baseCircleDriver = baseCircleDriver;
        this->baseDelayBetweenSteps = baseDelayBetweenSteps;
        this->lotSize = lotSize;
        this->delta = delta;
    }
    byte ENCODER::Read()
    {
        noInterrupts();
        return digitalRead(pin01) + digitalRead(pin02);
        interrupts();
    }
    byte ENCODER::getLotSize()
    {
        return lotSize;
    }
    short ENCODER::getBaseDelayBetweenSteps()
    {
        return baseDelayBetweenSteps;
    }
    int ENCODER::getBaseCircleDriver()
    {
        return baseCircleDriver;
    }
    float ENCODER::getDelta()
    {
        return delta;
    }
    int ENCODER::getCount()
    {
        noInterrupts();
        if(!event)
        {
            firstRequest = Read();
            event = true;
        }
        if(!newEvent)
        {
            secondRequest = Read();
            if(firstRequest != secondRequest)
            newEvent = true;
        }
        if(event && newEvent)
        {
            if(!hole)
            {
                count++;
            }
            hole = !hole;
            event = false;
            newEvent = false;
        }
        return count;
        interrupts();
    }
    int ENCODER::getCountDown(byte value)
    {
        noInterrupts();
        if(!assign)
        {
            count = value;
            assign = true;
        }
        if(!event)
        {
            firstRequest = Read();
            event = true;
        }
        if(!newEvent)
        {
            secondRequest = Read();
            if(firstRequest != secondRequest)
            newEvent = true;
        }
        if(event && newEvent)
        {
            count--;
            event = false;
            newEvent = false;
        }
        return count;
        interrupts();
    }
    void ENCODER::reset()
    {
        count = 0;
    }
    void ENCODER::reset(int value)
    {
        count = value;
    }
    short * coutError;
    short * maxError;
    void ENCODER::tact(int circleEncoder, int circleDriver, byte measure, DRIVER &driver,  ENCODER &settings)
    {
        this->circleEncoder = circleEncoder;
        this->circleDriver = circleDriver;
        this->measure = measure;
        this->baseCircleDriver = settings.getBaseCircleDriver();
        this->baseDelayBetweenSteps = settings.getBaseDelayBetweenSteps();
        this->lotSize = settings.getLotSize();
        this->delta = settings.getDelta();
        delete[] coutError;
        delete[] maxError;
        coutError = new short [lotSize];
        maxError = new short [lotSize];
        if(measure < 2)
        {
            measure = 2;
        }
        short ** data = new short * [measure];
        driver.setDirection(true);
        driver.setSwitch(ENABLE);
        for(int j = 0; j < measure; j++)
        {
            data[j] = new short [lotSize];
            int baseDelay = baseCircleDriver * baseDelayBetweenSteps;
            baseDelay = baseDelay / circleDriver;
            float coeff = 1.00;
            for(int k = 0; k < lotSize; k++)
            {
                coeff = coeff - delta;
                int delay = baseDelay * coeff;
                for(int i = 0; i < circleDriver; i++)
                {
                    noInterrupts();
                    driver.step(delay);
                    getCount();
                    interrupts();
                }
                data[j][k] = count;
            }
        }
        driver.setSwitch(DISABLE);
        for(int i = 0; i < lotSize; i++)
        {
            int difference = 0;
            int sum = 0;
            int maxDifference = 0;
            bool negative = false;
            for(int j = 0; j < measure; j++)
            {
                difference = circleEncoder - data[j][i];
                if(difference < 0)
                {
                    negative = true;
                    difference = difference * (-1);
                }
                if(difference > maxDifference)
                {
                    maxDifference = difference;
                    if(negative)
                    {
                        maxDifference = maxDifference * (-1);
                        negative = false;
                    }
                }
                sum = sum + difference;
            }
            coutError[i] = sum;
            maxError[i] = maxDifference;
        }
        for(int i = 0; i < measure; i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }
    String ENCODER::printTact()
    {
        String print = "";
        for(int i = 0; i < lotSize; i++)
        {
            print = print + "c" + coutError[i] + "m" + maxError[i];
        }
        /* short sizeCout = sizeof(coutError)/sizeof(coutError[0]);
        short sizeMax = sizeof(maxError)/sizeof(maxError[0]);
        if(sizeCout > 0)
        {
            delete[] coutError;
        }
        if(sizeMax > 0)
        {
            delete[] maxError;
        } */
        delete[] coutError;
        delete[] maxError;
        return print;
    }
    float ENCODER::getRatio()
    {
        return circleDriver / circleEncoder;
    }
// Сервопривод
    SERVO::SERVO(uint8_t pinOut, adc1_channel_t pinIn)
    {
        defaultConfig();
        _pinOut = pinOut;
        _pinIn = pinIn;
    }
    SERVO::SERVO(byte pinOut, adc1_channel_t pinIn, byte channel, short maxAngle, short minPulseWidth, short maxPulseWidth)
    {
        defaultConfig();
        _pinOut = pinOut;
        _pinIn = pinIn;
        _channel = channel;
        _maxAngle = maxAngle;
        _minPulseWidth = minPulseWidth;
        _maxPulseWidth = maxPulseWidth;
        attach();
    }
    SERVO::~SERVO()
    {
        detach();
    }
    void SERVO::setMaxAngle(short maxAngle)
    {
        this->_maxAngle = maxAngle;
    }
    void SERVO::setMinPulseWidth(short minPulseWidth)
    {
        this->_minPulseWidth = minPulseWidth;
    }
    void SERVO::setMaxPulseWidth(short maxPulseWidth)
    {
        this->_maxPulseWidth = maxPulseWidth;
    }
    void SERVO::setChannel(byte channel)
    {
        _channel = channel;
        attach();
    }
    void SERVO::setAdcWidthBit(adc_bits_width_t adcWidthBit)
    {
        this->_adcWidthBit = adcWidthBit;
        attach();
    }
    void SERVO::setAdcAttenDb(adc_atten_t adcAttenDb)
    {
        this->_adcAttenDb = adcAttenDb;
        attach();
    }
    void SERVO::setResolutionBets(uint8_t resolutionBits)
    {
        this->_resolutionBits = resolutionBits;
        attach();
    }
    void SERVO::setFrequency(int frequency)
    {
        this->_frequency = frequency;
        attach();
    }
    void SERVO::defaultConfig()
    {
        _adcWidthBit = ADC_WIDTH_BIT_12;
        _adcAttenDb = ADC_ATTEN_DB_11;
        _frequency = FREQUENCY;
        _resolutionBits = RESOLUTION_BITS;
        _pinIn = ADC1_CHANNEL_0;
        _pinOut = 0;
        _channel = 0;

        _countMeasure = COUNT_MEASHURE;

        _minPulseWidth = 0;
        _maxPulseWidth = 0;
        _minAnalogSig = DEFAULT_SHORT;
        _midAnalogSig = DEFAULT_SHORT;
        _maxAnalogSig = DEFAULT_SHORT;
        _minAngle = 0;
        _maxAngle = 0;
        _minAnalog = false;
        _midAnalog = false;
        _maxAnalog = false;
        
        _degrees = DEFAULT_FLOAT;
        _degreesMinus = DEFAULT_FLOAT;
        _degreesPlus = DEFAULT_FLOAT;
        _relativeMiddle = false;

        _minCalibAng = DEFAULT_SHORT;
        _midCalibAng = DEFAULT_SHORT;
        _maxCalibAng = DEFAULT_SHORT;

        _interrupt = false;
        _autoMovement = false;
        _customeDelayPulse = DELAY_PULSE;
        _customeDelayBetween = DELAY_BETWEEN;
        _customeIncrementAngle = INCREMENT_ANGLE;

        _periodSec = 0;

        _slowMo = false;
        _generationError = false;
        _direction = false;
        _gears = 0;
        _multiplier = 1;
        _currentAngle = 0;
    }
    bool SERVO::attach()
    {
        adc1_config_width(_adcWidthBit);
        adc1_config_channel_atten(_pinIn, _adcAttenDb);
        ledcSetup(_channel, _frequency, _resolutionBits);
        ledcAttachPin(_pinOut, _channel);
        return true;
    }
    bool SERVO::detach()
    {
        ledcDetachPin(_pinOut);
        return true;
    }
    void SERVO::WriteMicroseconds(int pulseUs)
    {
        //pulseUs = constrain(pulseUs, _minPulseWidth, _maxPulseWidth);
        //_pulseWidthDuty = UsToDuty(pulseUs);
        ledcWrite(_channel, UsToDuty(constrain(pulseUs, _minPulseWidth, _maxPulseWidth)));
    }
    void SERVO::write(short degrees)
    {
        //degrees = constrain(degrees, _minAngle, _maxAngle);
        WriteMicroseconds(AngleToUs(constrain(degrees, _minAngle, _maxAngle)));
    }
    void SERVO::step(short degrees, short delayPulse)
    {
        write(degrees);
        vTaskDelay(1);
        delayMicroseconds(delayPulse * 1000 - 1000);
    }
    void SERVO::setCountMeasure(short countMeasure)
    {
        this->_countMeasure = countMeasure;
    }
    short SERVO::readAnalogSig()
    {
        // Среднеарифметическое
        float * array_1 = new float[_countMeasure];
        for(short i = 0; i < _countMeasure; i++)
        {
            array_1[i] = adc1_get_raw(_pinIn);
        }
        float average = 0;
        for(short i = 0; i < _countMeasure; i++)
        {
            average += array_1[i];
        }
        float countMeasure = _countMeasure;
        average = average / countMeasure;
        // Отклонение частного от среднеарифметической
        float * array_2 = new float[_countMeasure];
        for(short i = 0; i < _countMeasure; i++)
        {
            array_2[i] = array_1[i] - average;
        }
        // Квадрат отклонения
        float * array_3 = new float[_countMeasure];
        for(short i = 0; i < _countMeasure; i++)
        {
            array_3[i] = pow(array_2[i], 2);
        }
        // Среднеквадратичное отклонение
        float squareDeviation = 0;
        for(short i = 0; i < _countMeasure; i++)
        {
            squareDeviation += array_3[i];
        }
        squareDeviation = sqrt(squareDeviation / countMeasure);
        // Подсчет отрицательных и положительных отклонений от среднего
        short countNeg = 0;
        short countPos = 0;
        short kMin = 0;
        short kMax = 0;
        for(short i = 0; i <_countMeasure; i++)
        {
            if(array_2[i] < 0)
            {
                countNeg++;
            }
            else
            {
                countPos++;
            }
            // Подсчет позиций в массивах, которые исключат радикальные отклонения от среднеквадратичных
            float x = abs(array_2[i]);
            if(x > squareDeviation)
            {
                if(array_2[i] < 0)
                {
                    kMin++;
                }
                else
                {
                    kMax++;
                }
            }
        }
        // Запись массива отрицательных отклонений
        float * array_min = new float[countNeg];
        countNeg = 0;
        for(short i = 0; i < _countMeasure; i++)
        {
            if(array_2[i] < 0)
            {
                array_min[countNeg++] = array_2[i];
            }
        }
        // Пузырьковая сортировка отрицательных отклонений
        float temp = 0;
        if(kMin > 0)
        {
            for(short i = 0; i < countNeg - 1; i++)
            {
                for(short j = countNeg - 1; j > i; j--)
                {
                    if(array_min[j] < array_min[j - 1])
                    {
                        temp = array_min[j - 1];
                        array_min[j - 1] = array_min[j];
                        array_min[j] = temp;
                    }
                }
            }
            // Перезапись радикальных отклонений в отрицательном массиве
            for(short i = 0; i < kMin; i++)
            {
                array_min[i] = array_min[kMin];
            }
        }
        // Запись массива положительных отклонений
        float * array_max = new float[countPos];
        countPos = 0;
        for(short i = 0; i < _countMeasure; i++)
        {
            if(array_2[i] >= 0)
            {
                array_max[countPos++] = array_2[i];
            }
        }
        if(kMax > 0)
        {
            // Пузырьковая сортировка положительных отклонений
            for(short i = 0; i < countPos - 1; i++)
            {
                for(short j = countPos - 1; j > i; j--)
                {
                    if(array_max[j] < array_max[j - 1])
                    {
                        temp = array_max[j - 1];
                        array_max[j - 1] = array_max[j];
                        array_max[j] = temp;
                    }
                }
            }
            // Перезапись радикальных отклонений в положительном массиве
            for(short i = countPos; i > countPos - kMax; i--)
            {
                array_max[i - 1] = array_max[countPos - kMax - 1];
            }
        }
        // Запись откорректированных значений 
        float * array_4 = new float[_countMeasure];
        for(int i = 0; i < countNeg; i++)
        {
            array_4[i] = array_min[i] + average;
        }
        for(int i = 0; i < countPos; i++)
        {
            array_4[countNeg + i] = array_max[i] + average;
        }
        // Расчет среднеарифметического значения без радикальных отклонений
        average = 0;
        for(short i = 0; i <_countMeasure; i++)
        {
            average += array_4[i];
        }
        average = average / _countMeasure;
        delete[] array_1;
        delete[] array_2;
        delete[] array_3;
        delete[] array_4;
        delete[] array_min;
        delete[] array_max;
        return average;
    }
    void SERVO::testAvailableRange()
    {
        attach();
        for (short i = _minAngle; i <= _maxAngle; i++)
        {
            if(_interrupt)
            {
                break;
            }
            step(i, _customeDelayPulse);
        }
        if(!_interrupt)
        {
            vTaskDelay(_customeDelayBetween);
            for (short i = _maxAngle; i >= _minAngle; i--)
            {
                if(_interrupt)
                {
                    break;
                }
                step(i, _customeDelayPulse);
            }
        }
        _interrupt = false;
    }
    void SERVO::resetAnalogSig()
    {
        _minAnalogSig = DEFAULT_SHORT;
        _midAnalogSig = DEFAULT_SHORT;
        _maxAnalogSig = DEFAULT_SHORT;
        _minAnalog = false;
        _midAnalog = false;
        _maxAnalog = false;
        _minCalibAng = DEFAULT_SHORT;
        _midCalibAng = DEFAULT_SHORT;
        _maxCalibAng = DEFAULT_SHORT;
    }
    void SERVO::calcDegrees()
    {
        float minAnalogSig = _minAnalogSig;
        float maxAnalogSig = _maxAnalogSig;
        float maxAngle = _maxAngle;
        _degrees = (maxAnalogSig - minAnalogSig) / maxAngle;
    }
    short SERVO::setMinAnalogSig()
    {
        int analogSig = 0;
        for(short i = 0; i < _countMeasure; i++)
        {
            analogSig += readAnalogSig();
        }
        _minAnalogSig = analogSig / _countMeasure;
        _minAnalog = true;
        if(getMaxAnalog())
        {
            calcDegrees();
        }
        return _minAnalogSig;
    }
    short SERVO::setMidAnalogSig()
    {
        int analogSig = 0;
        for(short i = 0; i < _countMeasure; i++)
        {
            analogSig += readAnalogSig();
        }
        _midAnalogSig = analogSig / _countMeasure;
        _midAnalog = true;
        return _midAnalogSig;
    }
    short SERVO::setMaxAnalogSig()
    {
        int analogSig = 0;
        for(short i = 0; i < _countMeasure; i++)
        {
            analogSig += readAnalogSig();
        }
        _maxAnalogSig = analogSig / _countMeasure;
        _maxAnalog = true;
        if(getMinAnalog())
        {
            calcDegrees();
        }
        return _maxAnalogSig;
    }
    void SERVO::setMinAnalogSig(short analogSig)
    {
        _minAnalogSig = analogSig;
        _minAnalog = true;
        if(getMaxAnalog())
        {
            calcDegrees();
        }
    }
    void SERVO::setMidAnalogSig(short analogSig)
    {
        _midAnalog = true;
        _midAnalogSig = analogSig;
    }
    void SERVO::setMaxAnalogSig(short analogSig)
    {
        _maxAnalog = true;
        _maxAnalogSig = analogSig;
        if(getMinAnalog())
        {
            calcDegrees();
        }
    }
    short SERVO::getMinAnalogSig()
    {
        return _minAnalogSig;
    }
    short SERVO::getMidAnalogSig()
    {
        return _midAnalogSig;
    }
    short SERVO::getMaxAnalogSig()
    {
        return _maxAnalogSig;
    }
    bool SERVO::getMinAnalog()
    {
        return _minAnalog;
    }
    bool SERVO::getMidAnalog()
    {
        return _midAnalog;
    }
    bool SERVO::getMaxAnalog()
    {
        return _maxAnalog;
    }
    void SERVO::setRelativeMiddle(bool relativeMiddle)
    {
        this->_relativeMiddle = relativeMiddle;
    }
    byte SERVO::ConverterRelativeDegrees(short degrees)
    {
        degrees += 90;
        return degrees;
    }
    void SERVO::setWorkRange(short workRange)
    {
        this->_workRange = workRange;
    }
    void SERVO::setDegrees()
    {
        float minAnalogSig = _minAnalogSig;
        float midAnalogSig = _midAnalogSig;
        float maxAnalogSig = _maxAnalogSig;
        float workRange = _workRange / 2;
        _degreesMinus = (midAnalogSig - minAnalogSig) / workRange;
        _degreesPlus = (maxAnalogSig - midAnalogSig) / workRange;
    }
    float SERVO::getDegrees(short analogSig)
    {
        if(analogSig < (_midAnalogSig - _degrees))
        {
            return _degreesMinus;
        }
        else if(analogSig > (_midAnalogSig + _degrees))
        {
            return _degreesPlus;
        }
        return _degrees;
    }
    short SERVO::getActualAngle()
    {
        int analogSig = 0;
        noInterrupts();
        for(short i = 0; i < _countMeasure; i++)
        {
            analogSig += readAnalogSig();
        }
        interrupts();
        analogSig = analogSig / _countMeasure;
        if(_relativeMiddle)
        {
            return (_midAnalogSig - analogSig) / getDegrees(analogSig);
        }
        else
        {
            return (analogSig - _minAnalogSig) / getDegrees(analogSig);
        }
    }
    short SERVO::ConvertAnalogToDeg(short analogSig)
    {
        return analogSig / getDegrees(analogSig);
    }
    void SERVO::print()
    {
        Serial.println("bool-------------------------------------");
        Serial.println(_minAnalog);
        Serial.println(_midAnalog);
        Serial.println(_maxAnalog);
        Serial.println(_relativeMiddle);
        Serial.println(_autoMovement);
        Serial.println(_interrupt);
        Serial.println("byte-------------------------------------");
        Serial.println(_channel);
        Serial.println(_customeIncrementAngle);
        Serial.println(_periodSec);
        Serial.println("adc1_channel_t-------------------------------------");
        Serial.println(_pinIn);
        Serial.println("adc_bits_width_t-------------------------------------");
        Serial.println(_adcWidthBit);
        Serial.println("adc_atten_t-------------------------------------");
        Serial.println(_adcAttenDb);
        Serial.println("uint8_t-------------------------------------");
        Serial.println(_pinOut);
        Serial.println(_resolutionBits);
        Serial.println("short-------------------------------------");
        Serial.println(_countMeasure);
        Serial.println(_minPulseWidth);
        Serial.println(_maxPulseWidth);
        Serial.println(_minAnalogSig);
        Serial.println(_midAnalogSig);
        Serial.println(_maxAnalogSig);
        Serial.println(_minAngle);
        Serial.println(_maxAngle);
        Serial.println(_minAngleWork);
        Serial.println(_maxAngleWork);
        Serial.println(_restAngle);
        Serial.println(_customeDelayPulse);
        Serial.println(_customeDelayBetween);
        Serial.println(_workRange);
        Serial.println(_minCalibAng);
        Serial.println(_midCalibAng);
        Serial.println(_maxCalibAng);
        Serial.println("int-------------------------------------");
        Serial.println(_frequency);
        Serial.println(_pulseWidthDuty);
        Serial.println("float-------------------------------------");
        Serial.println(_degrees);
        Serial.println(_degreesMinus);
        Serial.println(_degreesPlus);
    }
    void SERVO::testCalibrateRange()
    {
        short min = 0;
        short mid = 0;
        short max = 0;
        attach();
        short deg = 0;
        if(_relativeMiddle)
        {
            if(getActualAngle() < 0) // Левая четверть
            {
                deg = ConvertAnalogToDeg(_maxAnalogSig);
                while(getActualAngle() > -90 && deg < _workRange) // Возврат в левое положение
                {
                    /* Serial.print("Target: ");
                    Serial.print(deg);
                    Serial.print("\tActual: ");
                    Serial.println(getActualAngle()); */
                    step(++deg, DELAY_PULSE);
                }
                //max = deg;
                max = getActualAngle();
                /* Serial.print("Max calibrate angle:\t");
                Serial.println(max); */
                vTaskDelay(DELAY_BETWEEN);
                while(getActualAngle() < 0) // Движение в среднее положение
                {
                    /* Serial.print("Target: ");
                    Serial.print(deg);
                    Serial.print("\tActual: ");
                    Serial.println(getActualAngle()); */
                    step(--deg, DELAY_PULSE);
                }
                //mid = deg;
                mid = getActualAngle();
                /* Serial.print("Mid calibrate angle:\t");
                Serial.println(mid); */
                vTaskDelay(DELAY_BETWEEN);
                while(getActualAngle() < 90 && deg > 0) // Движение в правое положение
                {
                    /* Serial.print("Target: ");
                    Serial.print(deg);
                    Serial.print("\tActual: ");
                    Serial.println(getActualAngle()); */
                    step(--deg, DELAY_PULSE);
                }
                //min = deg;
                min = getActualAngle();
                /* Serial.print("Min calibrate angle:\t");
                Serial.println(min); */
            }
            else // Правая четверть
            {
                deg = ConvertAnalogToDeg(_minAnalogSig);
                while(getActualAngle() < 90 && deg > 0) // Доводка в правое положение
                {
                    /* Serial.print("Target: ");
                    Serial.print(deg);
                    Serial.print("\tActual: ");
                    Serial.println(getActualAngle()); */
                    step(--deg, DELAY_PULSE);
                }
                //min = deg;
                min = getActualAngle();
                /* Serial.print("Min calibrate angle:\t");
                Serial.println(min); */
                vTaskDelay(DELAY_BETWEEN);
                while(getActualAngle() > 0) // Движение в среднее положение
                {
                    /* Serial.print("Target: ");
                    Serial.print(deg);
                    Serial.print("\tActual: ");
                    Serial.println(getActualAngle()); */
                    step(++deg, DELAY_PULSE);
                }
                //mid = deg;
                mid = getActualAngle();
                /* Serial.print("Mid calibrate angle:\t");
                Serial.println(mid); */
                vTaskDelay(DELAY_BETWEEN);
                while(getActualAngle() > -90 && deg < _workRange) // Движение в левое положение
                {
                    /* Serial.print("Target: ");
                    Serial.print(deg);
                    Serial.print("\tActual: ");
                    Serial.println(getActualAngle()); */
                    step(++deg, DELAY_PULSE);
                }
                //max = deg;
                max = getActualAngle();
                /* Serial.print("Max calibrate angle:\t");
                Serial.println(max); */
            }
        }
        //print();
        if(!_interrupt)
        {
            _minCalibAng = min;
            _midCalibAng = mid;
            _maxCalibAng = max;
           /*  Serial.print("Min: ");
            Serial.print(_minCalibAng);
            Serial.print("\tMid: ");
            Serial.print(_midCalibAng);
            Serial.print("\tMax: ");
            Serial.println(_maxCalibAng); */
        }
        else
        {
            _interrupt = false;
        }
    }
    void SERVO::setCalibMinAng(short degrees)
    {
        _minCalibAng = degrees;
    }
    void SERVO::setCalibMidAng(short degrees)
    {
        _midCalibAng = degrees;
    }
    void SERVO::setCalibMaxAng(short degrees)
    {
        _maxCalibAng = degrees;
    }
    short SERVO::getCalibMinAng()
    {
        return _minCalibAng;
    }
    short SERVO::getCalibMidAng()
    {
        return _midCalibAng;
    }
    short SERVO::getCalibMaxAng()
    {
        return _maxCalibAng;
    }

    void SERVO::slowMo(bool on)
    {
        _slowMo = on;
    }
    void SERVO::setAmplitudeMax(short amplitude)
    {
        _amplitudeMax = amplitude;
    }
    void SERVO::setGearCounts(short gears)
    {
        _gears = gears;
    }
    void SERVO::setAmplitudeRatio(short ratio)
    {
        _amplitudeRatio = ratio;
    }
    void SERVO::setMultiplier(short multiplier)
    {
        _multiplier = multiplier;
    }

    void SERVO::setIncrementSlow(short increment)
    {
        _incrementSlow = increment;
    }
    void SERVO::setIncrementFast(short increment)
    {
        _incrementFast = increment;
    }

    void SERVO::setStepDelayMinSlow(short delay)
    {
        _stepDelayMinSlow = delay;
    }
    void SERVO::setStepDelayMaxSlow(short delay)
    {
        _stepDelayMaxSlow = delay;
    }
    void SERVO::setStepDelayMinFast(short delay)
    {
        _stepDelayMinFast = delay;
    }
    void SERVO::setStepDelayMaxFast(short delay)
    {
        _stepDelayMaxFast = delay;
    }

    void SERVO::setBetweenDelayMinSlow(short delay)
    {
        _betweenDelayMinSlow = delay;
    }
    void SERVO::setBetweenDelayMaxSlow(short delay)
    {
        _betweenDelayMaxSlow = delay;
    }
    void SERVO::setBetweenDelayMinFast(short delay)
    {
        _betweenDelayMinFast = delay;
    }
    void SERVO::setBetweenDelayMaxFast(short delay)
    {
        _betweenDelayMaxFast = delay;
    }

    void SERVO::setAccelerationModelSize(short sizeArray)
    {
        _accelerationModelSize = sizeArray;
    }
    void SERVO::setAccelerationModelSlow(float array[])
    {
        delete[] _accelerationModelSlow;
        _accelerationModelSlow = new float[_accelerationModelSize];
        for(byte i = 0; i < _accelerationModelSize; i++)
        {
            _accelerationModelSlow[i] = array[i];
        }
    }
    void SERVO::setAccelerationModelFast(float array[])
    {
        delete[] _accelerationModelFast;
        _accelerationModelFast = new float[_accelerationModelSize];
        for(byte i = 0; i < _accelerationModelSize; i++)
        {
            _accelerationModelFast[i] = array[i];
        }
    }
    void SERVO::setAccelerationModelCurrent(float array[])
    {
        delete[] _accelerationModelCurrent;
        _accelerationModelCurrent = new float[_accelerationModelSize];
        for(byte i = 0; i < _accelerationModelSize; i++)
        {
            _accelerationModelCurrent[i] = array[i];
        }
    }
    float SERVO::MapFloat(float x, float in_min, float in_max, float out_min, float out_max)
    {
        float divisor = (in_max - in_min);
        if(divisor == 0){
            return -1; //AVR returns -1, SAM returns 0
        }
        return (x - in_min) * (out_max - out_min) / divisor + out_min;
    }
    void SERVO::setDynamicAccelerationModel(byte value)
    {
        delete[] _accelerationModelCurrent;
        _accelerationModelCurrent = new float[_accelerationModelSize];
        for(byte i = 0; i < _accelerationModelSize; i++)
        {
            _accelerationModelCurrent[i] = MapFloat(value, MIN_GEAR, _gears, _accelerationModelSlow[i], _accelerationModelFast[i]);
        }
    }
    void SERVO::setAmplitudeProgramm(list <byte> programList)
    {
        _sizeAmpProg = programList.size();
        delete[] _amplitudeProgramm;
        _amplitudeProgramm = new float[_sizeAmpProg];
        byte j = 0;
        for(auto i = programList.begin(); i != programList.end(); i++)
        {
            _amplitudeProgramm[j++] = *i;
        }
    }
    void SERVO::setAccelerationProgramm(list <byte> programList)
    {
        _sizeAccProg = programList.size();
        delete[] _accelerationProgramm;
        _accelerationProgramm = new float[_sizeAccProg];
        byte j = 0;
        for(auto i = programList.begin(); i != programList.end(); i++)
        {
            _accelerationProgramm[j++] = *i;
        }
    }
    void SERVO::setAmplitudeLimit(byte value)
    {
        for(byte i = 0; i < _sizeAmpProg; i++)
        {
            _amplitudeProgramm[i] = map(value, MIN_GEAR, _gears, MIN_GEAR, _amplitudeProgramm[i]);
        }
    }
    void SERVO::setAcceleratioLimit(byte value)
    {
        for(byte i = 0; i < _sizeAccProg; i++)
        {
            _accelerationProgramm[i] = map(value, MIN_GEAR, _gears, MIN_GEAR, _accelerationProgramm[i]);
        }
    }

    short SERVO::calcAmplitudeIndex(short index)
    {
        return map(_amplitudeProgramm[index], MIN_GEAR, _gears, _amplitudeMax / _amplitudeRatio, _amplitudeMax);
    }
    short SERVO::calcAmplitudeCurrent()
    {
        if(_amplitudeCurrent < _amplitudeIndex)
        {
            _amplitudeCurrent += (_incrementCurrent * 2);
            if(_amplitudeCurrent > _amplitudeIndex)
            {
                _amplitudeCurrent = _amplitudeIndex;
            }
        }
        else if(_amplitudeCurrent > _amplitudeIndex)
        {
            _amplitudeCurrent -= (_incrementCurrent * 2);
            if(_amplitudeCurrent < _amplitudeIndex)
            {
                _amplitudeCurrent = _amplitudeIndex;
            }
        }
        return _amplitudeCurrent;
    }
    short SERVO::calcIncrementCurrent(short index)
    {
        byte small;
        byte large;
        if(_incrementFast >= _incrementSlow)
        {
            small = _incrementSlow;
            large = _incrementFast;
        }
        else
        {
            small = _incrementFast;
            large = _incrementSlow;
        }
        return map(index, MIN_GEAR, _gears, small, large);
    }
    short SERVO::calcStepDelayMinCurrent(short index)
    {
        return map(index, MIN_GEAR, _gears, _stepDelayMinFast * _multiplier, _stepDelayMinSlow * _multiplier);
    }
    short SERVO::calcStepDelayMaxCurrent(short index)
    {
        return map(index, MIN_GEAR, _gears, _stepDelayMaxFast * _multiplier, _stepDelayMaxSlow * _multiplier);
    }
    short SERVO::calcBeetweenDelayCurrent(short index)
    {
        short slowBeetCurrDel = map(_amplitudeCurrent, _amplitudeMax / _amplitudeRatio, _amplitudeMax, _betweenDelayMinSlow, _betweenDelayMaxSlow);
        short fastBeetCurrDel = map(_amplitudeCurrent, _amplitudeMax / _amplitudeRatio, _amplitudeMax, _betweenDelayMinFast, _betweenDelayMaxFast);
        return map(index, MIN_GEAR, _gears, fastBeetCurrDel, slowBeetCurrDel);
    }
    void SERVO::calcAccelerationModelCurrent(short index)
    {
        short summAccModSlow = 0;
        short summAccModFast = 0;
        for(byte i = 0; i < _accelerationModelSize; i++)
        {
            summAccModSlow += _accelerationModelSlow[i];
            summAccModFast += _accelerationModelFast[i];
        }
        delete[] _accelerationModelCurrent;
        _accelerationModelCurrent = new float[_accelerationModelSize];
        for(byte i = 0; i < _accelerationModelSize; i++)
        {
            byte small;
            byte large;
            if(summAccModSlow >= summAccModFast)
            {
                small = _accelerationModelFast[i];
                large = _accelerationModelSlow[i];
            }
            else
            {
                small = _accelerationModelSlow[i];
                large = _accelerationModelFast[i];
            }
            _accelerationModelCurrent[i] = map(index, MIN_GEAR, _gears, small, large);
        }
    }
    bool SERVO::checkGenerationError()
    {
        if(_generationError)
        {
            _generationError = false;
            return true;
        }
        return false;
    }
    bool SERVO::move(bool &on)
    {
        cs::AkimaSpline DelayGenerator;
        short degCount = calcAmplitudeCurrent() / 2;
        std::vector<float> del(_accelerationModelSize);
        byte min = 9;
        byte max = 0;
        for(byte i = 0; i < _accelerationModelSize; i++)
        {
            if(min > _accelerationModelCurrent[i])
            {
                min = _accelerationModelCurrent[i];
            }
            if(max < _accelerationModelCurrent[i])
            {
                max = _accelerationModelCurrent[i];
            }
        }
        for(byte i = 0; i < _accelerationModelSize; i++)
        {
            del[i] = map(_accelerationModelCurrent[i], min, max, _stepDelayMinCurrent, _stepDelayMaxCurrent);
        }
        std::vector<float> deg(_accelerationModelSize);
        deg[0] = 1;
        deg[_accelerationModelSize - 1] = degCount;
        short partSize = degCount / (_accelerationModelSize - 1);
        for(byte i = 1; i < _accelerationModelSize - 1; i++)
        {
            deg[i] = deg[i - 1] + partSize;
        }
        DelayGenerator.init(deg, del, degCount);
        if(DelayGenerator.proc())
        {
            _generationError = false;
        }
        else
        {
            _generationError = true;
        }
        if(_generationError) // Ошибка расчета
        {
            on = false;
            return false;
        }
        else // Успешный расчет
        {
            short counter = 0;
            short iterator = 0;
            while(counter < _amplitudeCurrent) // Цикл движения в одном направлении
            {
                if(!on)
                {
                    break;
                }
                if(_direction)
                {
                    _currentAngle++;
                }
                else
                {
                    _currentAngle--;
                }
                if(counter < degCount)
                {
                    step(_currentAngle, DelayGenerator.y_out[iterator++] / _multiplier);
                }
                else if(counter > degCount)
                {
                    step(_currentAngle, DelayGenerator.y_out[iterator--] / _multiplier);
                }
                else
                {
                    step(_currentAngle, DelayGenerator.y_out[--iterator] / _multiplier);
                }
                counter++;
            }
        }
        return true;
    }
    void SERVO::swingCalibration(bool &on)
    {
        _amplitudeCurrent = _incrementCurrent * (-1);
        _amplitudeIndex = _amplitudeMax;
        if(_slowMo) // Медленный статический режим
        {   
            _incrementCurrent = _incrementSlow;
            _stepDelayMinCurrent = _stepDelayMinSlow * _multiplier;
            _stepDelayMaxCurrent = _stepDelayMaxSlow * _multiplier;
            _betweenDelayCurrent = map(_amplitudeCurrent, _amplitudeMax / _amplitudeRatio, _amplitudeMax, _betweenDelayMinSlow, _betweenDelayMaxSlow);
            setAccelerationModelCurrent(_accelerationModelSlow);
        }
        else // Быстрый статический режим
        {
            _incrementCurrent = _incrementFast;
            _stepDelayMinCurrent = _stepDelayMinFast * _multiplier;
            _stepDelayMaxCurrent = _stepDelayMaxFast * _multiplier;
            _betweenDelayCurrent = map(_amplitudeCurrent, _amplitudeMax / _amplitudeRatio, _amplitudeMax, _betweenDelayMinFast, _betweenDelayMaxFast);
            setAccelerationModelCurrent(_accelerationModelFast);
        }
        _currentAngle = getActualAngle();
        attach();
        while (on)
        {
            if (move(on))
            {
                if (_slowMo)
                {
                    _betweenDelayCurrent = map(_amplitudeCurrent, _amplitudeMax / _amplitudeRatio, _amplitudeMax, _betweenDelayMinSlow, _betweenDelayMaxSlow);
                }
                else
                {
                    _betweenDelayCurrent = map(_amplitudeCurrent, _amplitudeMax / _amplitudeRatio, _amplitudeMax, _betweenDelayMinFast, _betweenDelayMaxFast);
                }
                vTaskDelay(_betweenDelayCurrent);
                _direction = !_direction;
            }
            else
            {
                break;
            }
        }
    }
    void SERVO::swing(bool &on, short workingTime, const volatile int &elapsedTime)
    {
        // Глобальные объявления
        float partSizeAmpProg = 0;
        short currentPartAmpProg = 0;
        float partSizeAccProg = 0;
        short currentPartAccProg = 0;
        if(workingTime > 0) // Расчет количественного и длительного изменения программы
        {
            workingTime = workingTime * SEC_IN_MIN;
            partSizeAmpProg = workingTime / _sizeAmpProg;
            partSizeAccProg = workingTime / _sizeAccProg;
            _amplitudeIndex = calcAmplitudeIndex(currentPartAmpProg);
        }
        else
        {
            _amplitudeIndex = _amplitudeMax;
        }
        // Присвоения основных параметров
        _incrementCurrent = map(_accelerationProgramm[currentPartAccProg], MIN_GEAR, _gears, _incrementSlow, _incrementFast);
        _amplitudeCurrent = _incrementCurrent * (-1);
        _stepDelayMinCurrent = _multiplier * map(_accelerationProgramm[currentPartAccProg], MIN_GEAR, _gears, _stepDelayMinSlow, _stepDelayMinFast);
        _stepDelayMaxCurrent = _multiplier * map(_accelerationProgramm[currentPartAccProg], MIN_GEAR, _gears, _stepDelayMaxSlow, _stepDelayMaxFast);
        setDynamicAccelerationModel(_accelerationProgramm[currentPartAccProg]);
        _currentAngle = getActualAngle();
        attach();
        // Подготовительный цикл
        while(on)
        {
            if(workingTime > 0) // Подготовительные расчеты программы, ограниченной по времени
            {
                if(elapsedTime > workingTime) // Выключение по окончании времени работы
                {
                    on = false;
                    break;
                }
                if(elapsedTime > partSizeAmpProg) // Переход к следующему запрограммированному этапу изменения амплитуды
                {
                    partSizeAmpProg += (workingTime / _sizeAmpProg);
                    _amplitudeIndex = calcAmplitudeIndex(++currentPartAmpProg);
                }
                if(elapsedTime > partSizeAccProg) // Переход к следующему запрограммированному этапу изменения скорости
                {
                    partSizeAccProg += (workingTime / _sizeAccProg);
                    _incrementCurrent = map(_accelerationProgramm[++currentPartAccProg], MIN_GEAR, _gears, _incrementSlow, _incrementFast);
                    _stepDelayMinCurrent = _multiplier * map(_accelerationProgramm[currentPartAccProg], MIN_GEAR, _gears, _stepDelayMinSlow, _stepDelayMinFast);
                    _stepDelayMaxCurrent = _multiplier * map(_accelerationProgramm[currentPartAccProg], MIN_GEAR, _gears, _stepDelayMaxSlow, _stepDelayMaxFast);
                    setDynamicAccelerationModel(_accelerationProgramm[currentPartAccProg]);
                }
            }
            // Корректор задержек основанный на программе амплитуды
            if (move(on))
            {
                vTaskDelay(calcBeetweenDelayCurrent(_accelerationProgramm[currentPartAccProg]));
                _direction = !_direction;
            }
            else
            {
                break;
            }
        }
    }

    void SERVO::setPeriodWorkCalibration(short periodSec)
    {
        this->_periodSec = periodSec;
    }
    void SERVO::setAutoMovement(bool autoMovement)
    {
        this->_autoMovement = autoMovement;
    }
    void SERVO::setDelayPulse(int delayPulse)
    {
        this->_customeDelayPulse = delayPulse;
    }
    void SERVO::setDelayBetween(int delayBetween)
    {
        this->_customeDelayBetween = delayBetween;
    }
    void SERVO::setIncrementAngle(short incrementAngle)
    {
        this->_customeIncrementAngle = incrementAngle;
    }
    void SERVO::interruptCycle()
    {
        this->_interrupt = true;
        detach();
    }
    void SERVO::calibrateWorkRange()
    {
        /* if(_rest)
        { */
            if(_autoMovement)
            {
                attach();
            }
            //_minDeclared = false;
            //_maxDeclared = false;
            short * arrRightDeg = new short[_countMeasure];
            short * arrLeftDeg = new short[_countMeasure];
            short counter = 0;
            short rightCounter = 0;
            short leftCounter = 0;
            arrRightDeg[rightCounter] = 0;
            arrLeftDeg[leftCounter] = 0;

            int timeLeft = 0;
            bool direction = true;
            short deg = _restAngle;
            short increment = 0;
            int countdown = millis();

            while(timeLeft <= (_periodSec * 1000) || counter < _countMeasure)
            {
                if(_interrupt)
                {
                    _interrupt = false;
                    //_minDeclared = true;
                    //_maxDeclared = true;
                    break;
                }
                if(_autoMovement)
                {
                    if(increment < _maxAngleWork)
                    {
                        increment = increment + _customeIncrementAngle * 2;
                    }
                    if(direction)
                    {
                        if(getActualAngle() != arrRightDeg[rightCounter])
                        {
                            arrRightDeg[++rightCounter] = getActualAngle();
                            if(arrRightDeg[rightCounter] > _maxAngleWork)
                            {
                                _maxAngleWork = arrRightDeg[rightCounter];
                                countdown = millis();
                            }
                        }
                        short i = deg;
                        for(; i <= deg + increment; i++)
                        {
                            step(i, _customeDelayPulse);
                        }
                        deg = i;
                    }
                    else
                    {
                        if(getActualAngle() != arrLeftDeg[leftCounter])
                        {
                            arrLeftDeg[++leftCounter] = getActualAngle();
                            if(arrLeftDeg[leftCounter] < _minAngleWork)
                            {
                                _minAngleWork = arrLeftDeg[leftCounter];
                                countdown = millis();
                            }
                        }
                        short i = deg;
                        for(; i >= deg - increment; i--)
                        {
                            step(i, _customeDelayPulse);
                        }
                        deg = i;
                    }
                    direction = !direction;
                    delayMicroseconds(_customeDelayBetween);
                }
                else
                {
                    if(getActualAngle() > 0)
                    {
                        if(getActualAngle() != arrRightDeg[rightCounter])
                        {
                            arrRightDeg[++rightCounter] = getActualAngle();
                            if(arrRightDeg[rightCounter] > _maxAngleWork)
                            {
                                _maxAngleWork = arrRightDeg[rightCounter];
                                countdown = millis();
                            }
                        }
                    }
                    else if(getActualAngle() < 0)
                    {
                        if(getActualAngle() != arrLeftDeg[leftCounter])
                        {
                            arrLeftDeg[++leftCounter] = getActualAngle();
                            if(arrLeftDeg[leftCounter] < _minAngleWork)
                            {
                                _minAngleWork = arrLeftDeg[leftCounter];
                                countdown = millis();
                            }
                        }
                    }
                }
                counter = rightCounter + leftCounter;
                timeLeft = millis() - countdown;
            }
            delete[] arrRightDeg;
            delete[] arrLeftDeg;
        /* } */
    }
    short SERVO::getGreatestDoublesAngle()
    {
        short module = _minAngleWork * (-1);
        if(module < _maxAngleWork)
        {
            return module;
        }
        return _maxAngleWork;
    }
// Микрофон
    MIC::MIC(adc1_channel_t pin)
    {
        this->_pin = pin;
        defaultParam();
        adc1_config_width(_adcBitsWidth);
        adc1_config_channel_atten(_pin, _adcAtten);
    }
    void MIC::defaultParam()
    {
        _adcBitsWidth = ADC_WIDTH_BIT_12;
        _resolution = 4095;
        _adcAtten = ADC_ATTEN_DB_11;
        reset();
    }
    void MIC::param(adc_bits_width_t adcBitsWidth, short resolution, adc_atten_t adcAtten)
    {
        _adcBitsWidth = adcBitsWidth;
        _resolution = resolution;
        _adcAtten = adcAtten;
    }
    short MIC::getResolution()
    {
        return _resolution;
    }
    void MIC::config(short quiteTopAdc, short quiteBotAdc, short loudTopAdc, short loudBotAdc, byte quietDb, byte loudDb)
    {
        _quiteTopAdc = quiteTopAdc;
        _quiteBotAdc = quiteBotAdc;
        _loudTopAdc = loudTopAdc;
        _loudBotAdc = loudBotAdc;
        _quietDb = quietDb;
        _loudDb = loudDb;
        calcDb();
    }
    short MIC::getAdc()
    {
        return adc1_get_raw(_pin);
    }
    void MIC::reset()
    {
        _quiteTopAdc = 0;
        _quiteBotAdc = _resolution;
        _quietDb = 0;
        _loudTopAdc = 0;
        _loudBotAdc = _resolution;
        _loudDb = 0;
        _middle = 0;
    }
    bool MIC::setQuiteAdc()
    {
        short adc = getAdc();
        if(_quiteTopAdc < adc)
        {
            _quiteTopAdc = adc;
        }
        if(_quiteBotAdc > adc)
        {
            _quiteBotAdc = adc;
        }
        return true;
    }
    bool MIC::setLoudAdc()
    {
        short adc = getAdc();
        if(_loudTopAdc < adc)
        {
            _loudTopAdc = adc;
        }
        if(_loudBotAdc > adc)
        {
            _loudBotAdc = adc;
        }
        return true;
    }
    short MIC::getQuiteTopAdc()
    {
        return _quiteTopAdc;
    }
    short MIC::getQuiteBotAdc()
    {
        return _quiteBotAdc;
    }
    short MIC::getLoudTopAdc()
    {
        return _loudTopAdc;
    }
    short MIC::getLoudBotAdc()
    {
        return _loudBotAdc;
    }
    void MIC::setQuietDb(byte dB)
    {
        _quietDb = dB;
    }
    void MIC::setLoudDb(byte dB)
    {
        _loudDb = dB;
    }
    bool MIC::calcDb()
    {
        if(_quiteTopAdc != 0 && _quiteBotAdc != _resolution && _quietDb != 0 && _loudTopAdc != 0 && _loudBotAdc != _resolution && _loudDb != 0)
        {
            _middle = (((_quiteTopAdc - (_quiteTopAdc - _quiteBotAdc) / 2)) + ((_loudTopAdc - (_loudTopAdc - _loudBotAdc) / 2))) / 2;
            return true;
        }
        else
        {
            return false;
        }
    }
    short MIC::getDb(short adcTop, short adcBot)
    {
        short top = map(adcTop, _quiteTopAdc, _loudTopAdc, _quietDb, _loudDb);
        short bot = map(adcBot, _quiteBotAdc, _loudBotAdc, _quietDb, _loudDb);
        if(top > bot)
        {
            return top;
        }
        else
        {
            return bot;
        }
    }
    /* bool MIC::excess(byte dB)
    {
        if(getDb(short adc) >= dB)
        {
            return true;
        }
        else
        {
            return false;
        }
    } */