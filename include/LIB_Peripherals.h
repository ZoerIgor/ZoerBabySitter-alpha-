#pragma once
#ifndef _LIB_PERIPHERALS_H_
    #define _LIB_PERIPHERALS_H_
    #include <Arduino.h>
    #include <Wire.h>
    #include <SparkFunSX1509.h>
    //#include <DallasTemperature.h>
    #include <driver/adc.h>
    #include <list>
    #include <iterator>
    #include "LIB_Spline.h"
    using namespace std;
    //#include <set>
    //#include <cstdio>
    //#include <cassert>
    //#include <vector>
    //#include <algorithm>
    //#include <iostream>
    //#include <math.h>
    //#include <iterator>
    #include <OneWire.h>
    enum EnumCommand{ENABLE, DISABLE, UP, DOWN, OFF = 255};
    enum EnumButtonStatusAndMode{UNDEFINED, RELEASE, PRESSED, TOUCH, SWITCH, PULL, PUSH, DEBOUNCE, CLICK, HOLD, LONG_HOLD, STICKY};
    class I2C
    {
        public:
            I2C(byte pinSda, byte pinClk, int frequency, byte maxAddress);
            byte getAddress();
            void writeArray();
            byte getSizeArray();
            byte getAddressOfArray(byte number);
        private:
            byte maxAddress;
            byte foundBus;
            byte * arrAddress;
            byte CountBus();
    };
    class MULTIPLEXOR
    {
        public:
            MULTIPLEXOR(byte pinS0, byte pinS1, byte pinS2, byte pinS3, byte pinSig);
            void set(byte address);
            byte get();
        private:
            #define MAX_COLUMNS 4
            #define MAX_ROWS 16
            byte pinS0, pinS1, pinS2, pinS3, pinSig, device, address, columns, rows, arrayInternal[4];
            bool arrayExternal[MAX_COLUMNS][MAX_ROWS];
    };
    class BUTTON_I2C
    {
        public:
            BUTTON_I2C(byte pin, BUTTON_I2C &setupButton);
            BUTTON_I2C(byte pin, byte mode, BUTTON_I2C &setupButton);
            BUTTON_I2C(byte mode, unsigned short timeDebounce);
            BUTTON_I2C(byte mode, unsigned short timeDebounce, unsigned short timeClick, unsigned short timeHold, unsigned short timeLongHold, unsigned short timeSticky);
            BUTTON_I2C(byte pin, byte mode, unsigned short timeDebounce, unsigned short timeClick, unsigned short timeHold, unsigned short timeLongHold, unsigned short timeSticky);
            byte get(SX1509 &sx1509);
        private:
            byte getMode();
            unsigned short getTimeDebounce();
            unsigned short getTimeClick();
            unsigned short getTimeHold();
            unsigned short getTimeLongHold();
            unsigned short getTimeSticky();
            void TimeConflict();
            bool switched;
            byte pin, mode, status, pressStatus;
            unsigned short timeDebounce, timeClick, timeHold, timeLongHold, timeSticky;
            unsigned long pressTime, elapsedTime;
    };
    class BUTTON
    {
        public:
            BUTTON(byte pin, BUTTON &setupButton);
            BUTTON(byte pin, byte mode, BUTTON &setupButton);
            BUTTON(byte mode, unsigned short timeDebounce);
            BUTTON(byte mode, unsigned short timeDebounce, unsigned short timeClick, unsigned short timeHold, unsigned short timeLongHold, unsigned short timeSticky);
            BUTTON(byte pin, byte mode, unsigned short timeDebounce, unsigned short timeClick, unsigned short timeHold, unsigned short timeLongHold, unsigned short timeSticky);
            byte get();
            byte getMode();
            unsigned short getTimeDebounce();
            unsigned short getTimeClick();
            unsigned short getTimeHold();
            unsigned short getTimeLongHold();
            unsigned short getTimeSticky();
            void resetPressStatus();
        private:
            void TimeConflict();
            bool switched;
            byte pin, mode, status, pressStatus;
            unsigned short timeDebounce, timeClick, timeHold, timeLongHold, timeSticky;
            unsigned long pressTime, elapsedTime;
    };
    class LED_I2C_DRIVER
    {
        public:
            LED_I2C_DRIVER();
            void setDuty(byte _duty);
            void turnOn(SX1509 &sx1509, byte pin, byte _duty, int smooth);
            void turnOff(SX1509 &sx1509, byte pin, byte _duty, int smooth);
            void smoothBlinking(SX1509 &sx1509, byte pin, int intervalBetweenImpulses, int delayBetweenWaves, byte maxDuty, byte minDuty);
            void risingSaw(SX1509 &sx1509, byte pin, int intervalBetweenImpulses, int delayBetweenWaves, byte maxDuty, byte minDuty);
            void ascendingSaw(SX1509 &sx1509, byte pin, int intervalBetweenImpulses, int delayBetweenWaves, byte maxDuty, byte minDuty);
            void blinking(SX1509 &sx1509, byte pin, int blinkSeries, int intervalBetweenBlinks, int intervalBetweenSeries, byte maxDuty, byte minDuty);
            byte getDuty();
            byte getMaxDuty();
        private:
            byte duty;
            byte ConvertDuty(byte _duty);
    };
    class RGB_LED_I2C_DRIVER
    {
        public:
            RGB_LED_I2C_DRIVER();
            void transfusion(SX1509 &ledI2cDriver, byte rPin, byte gPin, byte bPin, int intervalBetweenImpulses, int duty);
    };
    class LED_DRIVER
    {
        public:
            LED_DRIVER(uint8_t channel, double frequency, uint8_t resolution);
            void setFrequency(double frequency);
            void setResolution(uint8_t resolution);
            void setDuty(int duty);
            void turnOn(int duty, int smooth);
            void turnOff(int duty, int smooth);
            void smoothBlinking(int intervalBetweenImpulses, int delayBetweenWaves, int maxDuty, int minDuty);
            void risingSaw(int intervalBetweenImpulses, int delayBetweenWaves, int maxDuty, int minDuty);
            void ascendingSaw(int intervalBetweenImpulses, int delayBetweenWaves, int maxDuty, int minDuty);
            void blinking(int blinkSeries, int intervalBetweenBlinks, int intervalBetweenSeries, int maxDuty, int minDuty);
            uint8_t getChannel();
            double getFrequency();
            uint8_t getResolution();
            int getDuty();
            int getMaxDuty();
        private:
            int8_t channel, resolution;
            int duty;
            double frequency;
    };
    class RGB_LED_DRIVER
    {
        public:
            RGB_LED_DRIVER();
            void transfusion(LED_DRIVER &redLedDriver, LED_DRIVER &greenLedDriver, LED_DRIVER &blueLedDriver, int intervalBetweenImpulses, int duty);
    };
    class LED
    {
        public:
            LED(byte pin, LED_DRIVER &ledDriver);
            LED(LED &led1, LED &led2, LED &led3);
        private:
            byte pin;
    };
    class BUZZER_I2C_DRIVER
    {
        public:
            BUZZER_I2C_DRIVER();
            void play(SX1509 &sx1509, byte pin, byte countBeep, byte durationsBeep, byte durationspaused, byte volume);
        private:
            byte Volume(byte volume);     
    };
    class BUZZER_DRIVER
    {
        public:
            BUZZER_DRIVER(uint8_t channel);
            uint8_t getChannel();
            void playOwnMelody(int notes[], int durations[]);
            void playOwnMelody(int notes[], int durations[], int convertDurationNote, float melodyPace);
            void pausedBetweenReplay(unsigned int paused);
            void repeatPlay(bool repeat);
            void stopPlaying();
            void convertVolume(int notes[], int volume);
            void playDoubleDeep(int volume);
            void playTripleDeep(int volume);
            void playBeethovenFurElise();
            void playTheImperialMarch();
            void playMario();
            void playMarioUnderWorld();
            void playCrazyFrog();
            void playPirates();
        private:
            bool repeat, stop;
            int8_t channel;
            int size;
            int * convertNotes;
            unsigned int paused;
    };
    class BUZZER
    {
        public:
            BUZZER(byte pin, BUZZER_DRIVER &buzzerDriver);
        private:
            byte pin;
    };
    class PIR
    {
        public:
            PIR(byte pin);
            bool get();
        private:
            byte pin;
    };
    class TEMPERATURE
    {
        public:
            TEMPERATURE();
            TEMPERATURE(byte pin);
            byte get();
            byte get(byte pin, MULTIPLEXOR &multiplexor);
        private:
            byte pin;
    };
    class VOLTMETER
    {
        public:
            VOLTMETER();
            VOLTMETER(byte pin);
            float get();
            float get(byte pin, MULTIPLEXOR &multiplexor);
        private:
            byte pin;
    };
    class SMOKE
    {
        public:
            SMOKE();
            SMOKE(byte pin);
            short get();
            short get(byte pin, MULTIPLEXOR &multiplexor);
        private:
            byte pin;
    };
    class VOICE
    {
        public:
            VOICE(uint8_t pin);
            void setLimit(short limit);
            short getLimit();
            short get();
            bool getAlarm();
            short get(uint8_t pin, MULTIPLEXOR &multiplexor);
        private:
            uint8_t _pin;
            short _limit;
    };
    class LINE
    {
        public:
            LINE(byte pin);
            byte get();
        private:
            byte pin;
    };
    class HALL
    {
        public:
            HALL();
            HALL(byte pin);
            bool get();
            bool get(byte pin, MULTIPLEXOR &multiplexor);
        private:
            byte pin;
    };
    class ULTRASONIC
    {
        public:
            ULTRASONIC(byte pinTrig, byte pinEcho);
            double get(float ambientTemperature);
        private:
            byte pinTrig, pinEcho;
            float ambientTemperature;
            double value;
    };
    class RELAY_I2C
    {
        public:
            RELAY_I2C();
            void set(SX1509 &sx1509, byte pin, byte command);
    };
    class RELAY
    {
        public:
            RELAY();
            RELAY(byte pin);
            void set(byte command);
            void set(byte pin, MULTIPLEXOR &multiplexor, byte command);
        private:
            byte pin, command;
    };
    class POTENCIOMETER
    {
        public:
            POTENCIOMETER(byte pinUd, byte pinNc, byte pinCs);
            void set(byte command);
        private:
            byte pinUd, pinNc, pinCs, command;
    };
    class MICROWAVE
    {
        public:
            MICROWAVE(byte pin);
            double get();
        private:
            byte pin;
            double value;
    };
    class DRIVER
    {
        public:
            DRIVER(byte pinEn, byte pinCw, byte pinClk);
            void setDirection(bool direction);
            void setSwitch(byte switchPosition);
            void step(short int currentDelay);
        private:
            bool direction;
            byte pinEn, pinCw, pinClk, switchPosition;
            short int currentDelay;
    };
    class ENCODER
    {
        public:
            ENCODER(byte pin01, byte pin02);
            ENCODER(int baseCircleDriver, short baseDelayBetweenSteps, byte lotSize, float delta);
            int getCount();
            int getCountDown(byte value);
            void reset();
            void reset(int value);
            void tact(int circleEncoder, int circleDriver, byte measure, DRIVER &driver, ENCODER &settings);
            String printTact();
            float getRatio();
        private:
            byte Read();
            byte getLotSize();
            short getBaseDelayBetweenSteps();
            int getBaseCircleDriver();
            float getDelta();
            bool event, newEvent, hole, assign;
            byte pin01, pin02, firstRequest, secondRequest, measure, lotSize;
            float delta;
            short baseDelayBetweenSteps;
            int count, circleEncoder, circleDriver, baseCircleDriver;
    };
    class SERVO
    {
        #define MIN_GEAR 1
        #define SEC_IN_MIN 60
        #define DEFAULT_SHORT 32767
        #define DEFAULT_FLOAT 2147483647.00
        const byte INCREMENT_ANGLE = 1;
        const byte PERIOD = 10;
        const uint8_t RESOLUTION_BITS = 16;
        const short COUNT_MEASHURE = 10;
        const int MAX_COMPARE = ((1 << 16) - 1);
        const int FREQUENCY = 50;
        const int TAU_USEC = (FREQUENCY * 1000);
        const int DELAY_PULSE = 100;
        const int DELAY_BETWEEN = 3000;
        public:
            SERVO(uint8_t pinOut, adc1_channel_t pinPot);
            SERVO(uint8_t pinOut, adc1_channel_t pinIn, byte channel, short maxAngle, short minPulseWidth, short maxPulseWidth);
            ~SERVO();

            void setMaxAngle(short maxAngle);
            void setMinPulseWidth(short minPulseWidth);
            void setMaxPulseWidth(short maxPulseWidth);
            void setChannel(byte channel);
            void setAdcWidthBit(adc_bits_width_t adcWidthBit);
            void setAdcAttenDb(adc_atten_t _adcAttenDb);
            void setResolutionBets(uint8_t resolutionBits);
            void setFrequency(int frequency);
            void defaultConfig();

            bool attach();
            bool detach();
            void WriteMicroseconds(int pulseUs);
            void write(short degrees);
            void step(short degrees, short delayPulse);
            void testAvailableRange();

            short readAnalogSig();
            void calcDegrees();
            void resetAnalogSig();
            short setMinAnalogSig();
            short setMidAnalogSig();
            short setMaxAnalogSig();
            void setMinAnalogSig(short analogSig);
            void setMidAnalogSig(short analogSig);
            void setMaxAnalogSig(short analogSig);

            short getMinAnalogSig();
            short getMidAnalogSig();
            short getMaxAnalogSig();
            bool getMinAnalog();
            bool getMidAnalog();
            bool getMaxAnalog();

            void setCountMeasure(short countMeasure);
            void setCorrection(float correction);
            void setRelativeMiddle(bool relativeMiddle);
            byte ConverterRelativeDegrees(short degrees);
            void setWorkRange(short workRange);
            void setDegrees();
            float getDegrees(short analogSig);
            short getActualAngle();

            void testCalibrateRange();
            void setCalibMinAng(short degrees);
            void setCalibMidAng(short degrees);
            void setCalibMaxAng(short degrees);
            short getCalibMinAng();
            short getCalibMidAng();
            short getCalibMaxAng();

            void slowMo(bool on);
            void setAmplitudeMax(short amplitude);
            void setGearCounts(short gears);
            void setAmplitudeRatio(short ratio);
            void setMultiplier(short multiplier);

            void setIncrementSlow(short increment);
            void setIncrementFast(short increment);

            void setStepDelayMinSlow(short delay);
            void setStepDelayMaxSlow(short delay);
            void setStepDelayMinFast(short delay);
            void setStepDelayMaxFast(short delay);

            void setBetweenDelayMinSlow(short delay);
            void setBetweenDelayMaxSlow(short delay);
            void setBetweenDelayMinFast(short delay);
            void setBetweenDelayMaxFast(short delay);

            void setAccelerationModelSize(short sizeArray);
            void setAccelerationModelSlow(float array[]);
            void setAccelerationModelFast(float array[]);
            void setAccelerationModelCurrent(float array[]);
            void setDynamicAccelerationModel(byte value);
            void setAmplitudeProgramm(list <byte> programList);
            void setAccelerationProgramm(list <byte> programList);
            void setAmplitudeLimit(byte value);
            void setAcceleratioLimit(byte value);
            
            short calcAmplitudeIndex(short index);
            short calcAmplitudeCurrent();
            short calcIncrementCurrent(short index);
            short calcStepDelayMinCurrent(short index);
            short calcStepDelayMaxCurrent(short index);
            short calcBeetweenDelayCurrent(short index);
            void calcAccelerationModelCurrent(short index);
            bool checkGenerationError();
            bool move(bool &on);
            void swingCalibration(bool &on);
            void swing(bool &on, short workingTime, const volatile int &elapsedTime);

            void setPeriodWorkCalibration(short periodSec);
            void setAutoMovement(bool autoMovement);
            void setDelayPulse(int delayPulse);
            void setDelayBetween(int delayBetween);
            void setIncrementAngle(short incrementAngle);
            void interruptCycle();
            void calibrateWorkRange();
            short getGreatestDoublesAngle();

            void print();
        private:
            int UsToDuty(int us){return MAX_COMPARE;}
            int DutyToUs(int duty){return TAU_USEC;}
            short UsToAngle(short us){return _maxAngle;}
            short AngleToUs(short angle){return _maxPulseWidth;}
            /* int UsToDuty(int us){return map(us, 0, TAU_USEC, 0, MAX_COMPARE);}
            int DutyToUs(int duty){return map(duty, 0, MAX_COMPARE, 0, TAU_USEC);}
            short UsToAngle(short us){return map(us, _minPulseWidth, _maxPulseWidth, _minAngle, _maxAngle);}
            short AngleToUs(short angle){return map(angle, _minAngle, _maxAngle, _minPulseWidth, _maxPulseWidth);} */
            int ReadMicroseconds();
            short ConvertAnalogToDeg(short analogSig);
            float MapFloat(float x, float in_min, float in_max, float out_min, float out_max);

            void RecalcDegreesAndMaxAngle();
            bool _minAnalog, _midAnalog, _maxAnalog, _relativeMiddle, _autoMovement, _interrupt, _slowMo, _generationError, _direction;
            byte _channel, _customeIncrementAngle, _periodSec, _gears, _sizeAmpProg, _sizeAccProg;
            adc1_channel_t _pinIn;
            adc_bits_width_t _adcWidthBit;
            adc_atten_t _adcAttenDb;
            uint8_t _pinOut, _resolutionBits;
            short _countMeasure, _minPulseWidth, _maxPulseWidth, _minAnalogSig, _midAnalogSig, _maxAnalogSig, _minAngle, _maxAngle, _minAngleWork, _maxAngleWork, _restAngle, _customeDelayPulse, _customeDelayBetween, _workRange, _minCalibAng, _midCalibAng, _maxCalibAng, _amplitudeMax, _amplitudeIndex, _amplitudeCurrent, _incrementSlow, _incrementFast, _incrementCurrent, _stepDelayMinSlow, _stepDelayMaxSlow, _stepDelayMinFast, _stepDelayMaxFast, _stepDelayMinCurrent, _stepDelayMaxCurrent, _betweenDelayMinSlow, _betweenDelayMaxSlow, _betweenDelayMinFast, _betweenDelayMaxFast, _betweenDelayCurrent, _accelerationModelSize, _amplitudeRatio, _multiplier, _currentAngle;
            int _frequency, _pulseWidthDuty;
            float _degrees, _degreesMinus, _degreesPlus, *_accelerationModelSlow, *_accelerationModelFast, *_accelerationModelCurrent, *_amplitudeProgramm, *_accelerationProgramm;
    };
    class MIC
    {
        public:
            MIC(adc1_channel_t pin);
            void defaultParam();
            void param(adc_bits_width_t adcBitsWidth, short resolution, adc_atten_t adcAtten);
            short getResolution();
            void config(short quiteTopAdc, short quiteBotAdc, short loudTopAdc, short loudBotAdc, byte quietDb, byte loudDb);
            short getAdc();
            void reset();
            bool setQuiteAdc();
            bool setLoudAdc();
            short getQuiteTopAdc();
            short getQuiteBotAdc();
            short getLoudTopAdc();
            short getLoudBotAdc();
            void setQuietDb(byte dB);
            void setLoudDb(byte dB);
            bool calcDb();
            short getDb(short adcTop, short adcBot);
            bool excess(byte dB);
        private:
            adc1_channel_t _pin;
            adc_bits_width_t _adcBitsWidth = ADC_WIDTH_BIT_12;
            adc_atten_t _adcAtten = ADC_ATTEN_DB_11;
            byte _quietDb, _loudDb;
            short _resolution, _quiteTopAdc, _quiteBotAdc, _unitTop, _loudTopAdc, _loudBotAdc, _unitBot, _middle;
    };
#endif