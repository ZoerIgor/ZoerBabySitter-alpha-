#pragma once
#ifndef _LIB_EEPROM_H_
    #define _LIB_EEPROM_H_
    #include <Arduino.h>
    #include <EEPROM.h>
    #include <map>
    // SERVISE
    class MemoryService
    {
        public:
            MemoryService();
            void setCluster(int clasterName, int startAddress, int endAddress);
            void deleteAllCluster();
            void read(bool inRow, int clasterName);
            void write(int clasterName, byte array[]);
            void clear(int clasterName);
        private:
            const byte sizeArrow = 3;
            int countArrow, ** arrCluster, ** arrNewCluster;
    };
    // TYPE BOOL
    class MemoryBool
    {
        public:
            MemoryBool();
            MemoryBool(int address);
            bool get();
            void set(bool valueBool);
        private:
            int address;
            bool valueBool;
            byte valueByte;
    };
    // TYPE BYTE
    class MemoryByte
    {
        public:
            MemoryByte();
            MemoryByte(int address);
            byte get();
            void set(byte valueByte);
        private:
            int address;
            byte valueByte;
    };
    // TYPE BYTE_ARRAY
    class MemoryByteArray
    {
        public:
            MemoryByteArray();
            MemoryByteArray(int address, int lenght);
            int get(byte valueBytes[]);
            int getLenght();
            void set(byte valueBytes[]);
            void set(byte valueBytes[], byte interruptSymbol);
        private:
            byte * _arrayBytes;
            int _address, _lenght;
    };
    // TYPE SHORT
    class MemoryShort
    {
        public:
            MemoryShort();
            MemoryShort(int address);
            short get();
            void set(short valueShort);
        private:
            int address;
            short valueShort;
    };
    // TYPE INT
    class MemoryInt
    {
        public:
            MemoryInt();
            MemoryInt(int address);
            int get();
            void set(int valueInt);
        private:
            int address;
            int valueInt;
    };
    // TYPE UNSIGNED INT
    class MemoryUInt
    {
        public:
            MemoryUInt();
            MemoryUInt(unsigned int address);
            int get();
            void set(unsigned int valueUInt);
        private:
            int address;
            unsigned int valueUInt;
    };
    // TYPE FLOAT
    class MemoryFloat
    {
        public:
            MemoryFloat();
            MemoryFloat(int address);
            float get();
            void set(float valueFloat);
        private:
            int address;
            float valueFloat;
    };
    // TYPE FLOAT_ARRAY
    class MemoryFloatArray
    {
        public:
            MemoryFloatArray();
            MemoryFloatArray(int address, int size);
            void get(float array[]);
            void set(float array[]);
        private:
            int _address, _size;
    };
    // TYPE STRING
    class MemoryString
    {
        public:
            MemoryString();
            MemoryString(int address);
            String get();
            void set(String valueString);
        private:
            int address;
            String valueString;
    };
    // TYPE ASCII
    class MemoryASCII
    {
        public:
            MemoryASCII(const size_t address, const size_t range);
            byte read(const size_t address);
            void readArray(String &target);
            bool write(const size_t address, const byte &value);
            void writeArray(const String &source);
        private:
            class ASCII_UTF8_RU
            {
                public:
                    ASCII_UTF8_RU()
                    {
                        _encoding.emplace(144, "??");
                        _encoding.emplace(145, "??");
                        _encoding.emplace(146, "??");
                        _encoding.emplace(147, "??");
                        _encoding.emplace(148, "??");
                        _encoding.emplace(149, "??");
                        _encoding.emplace(150, "??");
                        _encoding.emplace(151, "??");
                        _encoding.emplace(152, "??");
                        _encoding.emplace(153, "??");
                        _encoding.emplace(154, "??");
                        _encoding.emplace(155, "??");
                        _encoding.emplace(156, "??");
                        _encoding.emplace(157, "??");
                        _encoding.emplace(158, "??");
                        _encoding.emplace(159, "??");
                        _encoding.emplace(160, "??");
                        _encoding.emplace(161, "??");
                        _encoding.emplace(162, "??");
                        _encoding.emplace(163, "??");
                        _encoding.emplace(164, "??");
                        _encoding.emplace(165, "??");
                        _encoding.emplace(166, "??");
                        _encoding.emplace(167, "??");
                        _encoding.emplace(168, "??");
                        _encoding.emplace(169, "??");
                        _encoding.emplace(170, "??");
                        _encoding.emplace(171, "??");
                        _encoding.emplace(172, "??");
                        _encoding.emplace(173, "??");
                        _encoding.emplace(174, "??");
                        _encoding.emplace(175, "??");
                        _encoding.emplace(176, "??");
                        _encoding.emplace(177, "??");
                        _encoding.emplace(178, "??");
                        _encoding.emplace(179, "??");
                        _encoding.emplace(180, "??");
                        _encoding.emplace(181, "??");
                        _encoding.emplace(182, "??");
                        _encoding.emplace(183, "??");
                        _encoding.emplace(184, "??");
                        _encoding.emplace(185, "??");
                        _encoding.emplace(186, "??");
                        _encoding.emplace(187, "??");
                        _encoding.emplace(188, "??");
                        _encoding.emplace(189, "??");
                        _encoding.emplace(190, "??");
                        _encoding.emplace(191, "??");
                        _encoding.emplace(128, "??");
                        _encoding.emplace(129, "??");
                        _encoding.emplace(130, "??");
                        _encoding.emplace(131, "??");
                        _encoding.emplace(132, "??");
                        _encoding.emplace(133, "??");
                        _encoding.emplace(134, "??");
                        _encoding.emplace(135, "??");
                        _encoding.emplace(136, "??");
                        _encoding.emplace(137, "??");
                        _encoding.emplace(138, "??");
                        _encoding.emplace(139, "??");
                        _encoding.emplace(140, "??");
                        _encoding.emplace(141, "??");
                        _encoding.emplace(142, "??");
                        _encoding.emplace(143, "??");
                    };
                    ~ASCII_UTF8_RU(){_encoding.clear();};
                    void use7LetterAlphabet(bool value);
                    byte charToByte(const char symbol);
                    char byteToChar(const byte value);
                    String getValue(const byte &key);
                    byte getKey(const char &value);
                private:
                    std::map<byte, String> _encoding;
                    bool _letter7 = true, _fb208, _fb209;
                    const byte _firstByteBegin = 208, _firstByteEnd = 209, _secondByteBegin = 128, _secondByteEnd = 191;
            };
            size_t _address, _range;
        public:
            ASCII_UTF8_RU ru;
    };
#endif