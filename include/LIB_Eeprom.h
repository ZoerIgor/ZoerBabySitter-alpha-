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
                        _encoding.emplace(144, "А");
                        _encoding.emplace(145, "Б");
                        _encoding.emplace(146, "В");
                        _encoding.emplace(147, "Г");
                        _encoding.emplace(148, "Д");
                        _encoding.emplace(149, "Е");
                        _encoding.emplace(150, "Ж");
                        _encoding.emplace(151, "З");
                        _encoding.emplace(152, "И");
                        _encoding.emplace(153, "Й");
                        _encoding.emplace(154, "К");
                        _encoding.emplace(155, "Л");
                        _encoding.emplace(156, "М");
                        _encoding.emplace(157, "Н");
                        _encoding.emplace(158, "О");
                        _encoding.emplace(159, "П");
                        _encoding.emplace(160, "Р");
                        _encoding.emplace(161, "С");
                        _encoding.emplace(162, "Т");
                        _encoding.emplace(163, "У");
                        _encoding.emplace(164, "Ф");
                        _encoding.emplace(165, "Х");
                        _encoding.emplace(166, "Ц");
                        _encoding.emplace(167, "Ч");
                        _encoding.emplace(168, "Ш");
                        _encoding.emplace(169, "Щ");
                        _encoding.emplace(170, "Ъ");
                        _encoding.emplace(171, "Ы");
                        _encoding.emplace(172, "Ь");
                        _encoding.emplace(173, "Э");
                        _encoding.emplace(174, "Ю");
                        _encoding.emplace(175, "Я");
                        _encoding.emplace(176, "а");
                        _encoding.emplace(177, "б");
                        _encoding.emplace(178, "в");
                        _encoding.emplace(179, "г");
                        _encoding.emplace(180, "д");
                        _encoding.emplace(181, "е");
                        _encoding.emplace(182, "ж");
                        _encoding.emplace(183, "з");
                        _encoding.emplace(184, "и");
                        _encoding.emplace(185, "й");
                        _encoding.emplace(186, "к");
                        _encoding.emplace(187, "л");
                        _encoding.emplace(188, "м");
                        _encoding.emplace(189, "н");
                        _encoding.emplace(190, "о");
                        _encoding.emplace(191, "п");
                        _encoding.emplace(128, "р");
                        _encoding.emplace(129, "с");
                        _encoding.emplace(130, "т");
                        _encoding.emplace(131, "у");
                        _encoding.emplace(132, "ф");
                        _encoding.emplace(133, "х");
                        _encoding.emplace(134, "ц");
                        _encoding.emplace(135, "ч");
                        _encoding.emplace(136, "ш");
                        _encoding.emplace(137, "щ");
                        _encoding.emplace(138, "ъ");
                        _encoding.emplace(139, "ы");
                        _encoding.emplace(140, "ь");
                        _encoding.emplace(141, "э");
                        _encoding.emplace(142, "ю");
                        _encoding.emplace(143, "я");
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