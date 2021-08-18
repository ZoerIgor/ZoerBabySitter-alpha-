#include "LIB_Eeprom.h"
#define DEBUG0
// SERVISE
MemoryService::MemoryService()
{
    countArrow = 0;
}
void MemoryService::setCluster(int clasterName, int startAddress, int endAddress)
{
    arrNewCluster = new int * [++countArrow];
    for(int i = 0; i < countArrow; i++)
    {
        arrNewCluster[i] = new int[sizeArrow];
    }
    if(countArrow > 1)
    {
        for(int i = 0; i < countArrow - 1; i++)
        {
            for(byte j = 0; j < sizeArrow; j++)
            {
                arrNewCluster[i][j] = arrCluster[i][j];
            }
        }
    }
    for(int i = 0; i < countArrow - 1; i++)
    {
        delete[] arrCluster[i];
    }
    delete[] arrCluster;
    arrNewCluster[countArrow-1][0] = clasterName;
    arrNewCluster[countArrow-1][1] = startAddress;
    arrNewCluster[countArrow-1][2] = endAddress;
    arrCluster = new int * [countArrow];
    for(int i = 0; i < countArrow; i++)
    {
        arrCluster[i] = new int[sizeArrow];
    }
    for(int i = 0; i < countArrow; i++)
    {
        for(byte j = 0; j < sizeArrow; j++)
        {
            arrCluster[i][j] = arrNewCluster[i][j];
        }
    }
    for(int i = 0; i < countArrow; i++)
    {
        delete[] arrNewCluster[i];
    }
    delete[] arrNewCluster;
}
void MemoryService::deleteAllCluster()
{
    for(int i = 0; i < countArrow; i++)
    {
        delete[] arrCluster[i];
    }
    delete[] arrCluster;
}
void MemoryService::read(bool inRow, int clasterName)
{
    if(countArrow == 0)
    {
        Serial.println("No cluster created");
    }
    else
    {
        for(int i = 0; i < countArrow; i++)
        {
            if(clasterName == arrCluster[i][0])
            {
                int address = arrCluster[i][1];
                int endAddress = arrCluster[i][2];
                Serial.println("-------------------------------");
                Serial.println("Read Eeprom!");
                Serial.println("-------------------------------");
                while (address <= endAddress)
                {
                    if (inRow)
                    {
                        Serial.print(EEPROM.readByte(address++));
                        if (address < endAddress)
                        {
                            Serial.print(",");
                        }
                        else
                        {
                            Serial.println();
                        }
                    }
                    else
                    {
                        Serial.print("Read byte # ");
                        Serial.print(address);
                        Serial.print("\tvalue byte: ");
                        Serial.println(EEPROM.readByte(address++));
                    }
                }
                Serial.println("-------------------------------");
                Serial.println("Read complite!");
                Serial.println("-------------------------------");
                break;
            }
        }
    }
}
void MemoryService::write(int clasterName, byte array[])
{
    for(int i = 0; i < countArrow; i++)
    {
        if(clasterName == arrCluster[i][0])
        {
            int address = arrCluster[i][1];
            int endAddress = arrCluster[i][2];
            while (address <= endAddress)
            {
                if(EEPROM.readByte(address) != array[address])
                {
                    EEPROM.writeByte(address, array[address]);
                    EEPROM.commit();
                }
                address++;
            }
            break;
        }
    }
}
void MemoryService::clear(int clasterName)
    {
        #define MAX_BYTE_VALUE 255
        for(int i = 0; i < countArrow; i++)
        {
            if(clasterName == arrCluster[i][0])
            {
                int address = arrCluster[i][1];
                int endAddress = arrCluster[i][2];
                while (address <= endAddress)
                {
                    if(EEPROM.readByte(address) != MAX_BYTE_VALUE)
                    {
                        EEPROM.writeByte(address, MAX_BYTE_VALUE);
                        EEPROM.commit();
                    }
                    address++;
                }
                break;
            }
        }
    }
// TYPE BOOL
MemoryBool::MemoryBool(int address)
{
    this->address = address;
}
bool MemoryBool::get()
{
    valueByte = EEPROM.readByte(address);
    if(valueByte == 0)
    {
        valueBool = true;
    }
    else
    {
        valueBool = false;
    }
    return valueBool;
}
void MemoryBool::set(bool valueBool)
    {
        if(valueBool)
        {
            valueByte = 0;
        }
        else
        {
            valueByte = 255;
        }
        if(EEPROM.readByte(address) != valueByte)
        {
            EEPROM.writeByte(address, valueByte);
            EEPROM.commit();
        }
    }
// TYPE BYTE
MemoryByte::MemoryByte(int address)
{
    this->address = address;
}
byte MemoryByte::get()
{
    return EEPROM.readByte(address);
}
void MemoryByte::set(byte valueByte)
    {
        this->valueByte = valueByte;
        if(MemoryByte::get() != valueByte)
        {
            EEPROM.writeByte(address, valueByte);
            EEPROM.commit();
        }
    }
// TYPE BYTE_ARRAY
MemoryByteArray::MemoryByteArray(int address, int lenght)
{
    this->_address = address;
    this->_lenght = lenght;
}
int MemoryByteArray::get(byte valueBytes[])
{
    int counter = 0;
    int sum = 0;
    int currentAddress = _address;
    int lastAddress = _address + _lenght;
    #ifdef DEBUG
        Serial.println("---2-3-1");
    #endif
    while(currentAddress < lastAddress)
    {
        #ifdef DEBUG
            Serial.println("---2-3-2");
        #endif
        valueBytes[counter] = EEPROM.readByte(currentAddress++);
        #ifdef DEBUG
            Serial.println("---2-3-3");
        #endif
        sum += valueBytes[counter++];
        #ifdef DEBUG
            Serial.println("---2-3-4");
        #endif
    }
    #ifdef DEBUG
        Serial.println("---2-3-5");
    #endif
    return sum;
}
int MemoryByteArray::getLenght()
{
    return _lenght;
}
void MemoryByteArray::set(byte valueBytes[])
{
    _arrayBytes = new byte[_lenght];
    bool record;
    int counter = 0;
    int currentAddress = _address;
    int lastAddress = _address + _lenght;
    #ifdef DEBUG
        Serial.println("---2-4-1");
    #endif
    while(currentAddress < lastAddress)
    {
        #ifdef DEBUG
            Serial.println("---2-4-2");
        #endif
        _arrayBytes[counter++] = EEPROM.readByte(currentAddress++);
        #ifdef DEBUG
            Serial.println("---2-4-3");
        #endif
    }
    for(int i = 0; i < _lenght; i++)
    {
        #ifdef DEBUG
            Serial.println("---2-4-4");
        #endif
        if(_arrayBytes[i] != valueBytes[i])
        {
            #ifdef DEBUG
            Serial.println("---2-4-5");
        #endif
            record = true;
        }
    }
    if(record)
    {
        #ifdef DEBUG
            Serial.println("---2-4-6");
        #endif
        int counter = 0;
        int currentAddress = _address;
        int lastAddress = _address + _lenght;
        while(currentAddress < lastAddress)
        {
            #ifdef DEBUG
            Serial.println("---2-4-7");
        #endif
            if (_arrayBytes[counter] != valueBytes[counter])
            {
                #ifdef DEBUG
                    Serial.println("---2-4-8");
                #endif
                try
                {
                    #ifdef DEBUG0
                        Serial.println("ARRAY//\t Read: " + String(currentAddress, DEC) + "\tVal: " + String(_arrayBytes[counter], DEC) + "//\t\t Write: " + String(currentAddress, DEC) + "\tVal: " + String(valueBytes[counter], DEC));
                    #endif
                    EEPROM.writeByte(currentAddress, valueBytes[counter]);
                    #ifdef DEBUG
                        Serial.println("---2-4-9");
                    #endif
                    delay(1);
                    EEPROM.commit();
                    delay(1);
                    #ifdef DEBUG
                        Serial.println("---2-4-10");
                    #endif
                }
                catch (const std::exception & ex)
                {
                    Serial.print("ОШИБКА ЗАПИСИ! ");
                    Serial.println(ex.what());
                }
            }
            #ifdef DEBUG0
                else
                {
                    #ifdef DEBUG0
                        Serial.println("ARRAY//\t Read: " + String(currentAddress, DEC) + "\tVal: " + String(_arrayBytes[counter], DEC) + "//");
                    #endif
                }
            #endif
            currentAddress++;
            counter++;
        }
    }
    #ifdef DEBUG
        Serial.println("---2-4-11");
    #endif
    delete[] _arrayBytes;
}
void MemoryByteArray::set(byte valueBytes[], byte interruptSymbol)
{
    _arrayBytes = new byte[_lenght];
    bool record = false;
    bool interrupt = false;
    int counter = 0;
    int currentAddress = _address;
    int lastAddress = _address + _lenght;
    while(currentAddress < lastAddress)
    {
        if (valueBytes[counter] == interruptSymbol && interrupt)
        {
            break;
        }
        _arrayBytes[counter] = EEPROM.readByte(currentAddress++);
        interrupt = (valueBytes[counter] == interruptSymbol) ? true : false;
        if ((_arrayBytes[counter] != valueBytes[counter]))
        {
            record = true;
        }
        counter++;
    }
    if(record)
    {
        currentAddress = _address;
        for (int i = 0; i < counter; i++)
        {
            if (_arrayBytes[i] != valueBytes[i])
            {
                try
                {
                    #ifdef DEBUG0
                        Serial.println("ARRAY\t//\t Read: " + String(currentAddress, DEC) + "\tVal: " + String(_arrayBytes[i], DEC) + "\t//\t Write: " + String(currentAddress, DEC) + "\tVal: " + String(valueBytes[i], DEC));
                    #endif
                    EEPROM.writeByte(currentAddress, valueBytes[i]);
                    EEPROM.commit();
                }
                catch (const std::exception & ex)
                {
                    Serial.print("ОШИБКА ЗАПИСИ! ");
                    Serial.println(ex.what());
                }
            }
            #ifdef DEBUG0
                else
                {
                    #ifdef DEBUG0
                        Serial.println("ARRAY\t//\t Read: " + String(currentAddress, DEC) + "\tVal: " + String(_arrayBytes[i], DEC) + "\t//");
                    #endif
                }
            #endif
            currentAddress++;
        }
    }
    #ifdef DEBUG
        Serial.println("---2-4-11");
    #endif
    delete[] _arrayBytes;
}
// TYPE SHORT
MemoryShort::MemoryShort(int address)
{
    this->address = address;
}
short MemoryShort::get()
{
    return EEPROM.readShort(address);
}
void MemoryShort::set(short valueShort)
{
    if(EEPROM.readShort(address) != valueShort)
    {
        EEPROM.writeShort(address, valueShort);
        EEPROM.commit();
    }
}
// TYPE INT
MemoryInt::MemoryInt(int address)
{
    this->address = address;
}
int MemoryInt::get()
{
    return EEPROM.readInt(address);
}
void MemoryInt::set(int valueInt)
{
    if(MemoryInt::get() != valueInt)
    {
        EEPROM.writeInt(address, valueInt);
        EEPROM.commit();
    }
}
// TYPE UNSIGNED INT
MemoryUInt::MemoryUInt(unsigned int address)
{
    this->address = address;
}
int MemoryUInt::get()
{
    return EEPROM.readUInt(address);
}
void MemoryUInt::set(unsigned int valueUInt)
{
    if(MemoryUInt::get() != valueUInt)
    {
        EEPROM.writeUInt(address, valueUInt);
        EEPROM.commit();
    }
}
// TYPE FLOAT
MemoryFloat::MemoryFloat(int address)
{
    this->address = address;
}
float MemoryFloat::get()
{
    return EEPROM.readFloat(address);
}
void MemoryFloat::set(float valueFloat)
    {          
        if(MemoryFloat::get() != valueFloat)
        {
            EEPROM.writeFloat(address, valueFloat);
            EEPROM.commit();
        }
    }
// TYPE FLOAT_ARRAY
MemoryFloatArray::MemoryFloatArray(int address, int size)
{
    _address = address;
    _size = size;
}
void MemoryFloatArray::get(float array[])
{
    int counter = 0;
    while(counter < _size)
    {
        array[counter] = EEPROM.readFloat(_address + counter * sizeof(array[0]));
        counter++;
    }
}
void MemoryFloatArray::set(float array[])
    {          
        bool record;
        int counter = 0;
        while(counter < _size)
        {
            if(EEPROM.readFloat(_address + counter * sizeof(array[0]) != array[counter]))
            {
                record = true;
            }
            counter++;
        }
        if(record)
        {
            int iterator = 0;
            while(iterator < _size)
            {
                EEPROM.writeFloat(_address + iterator * sizeof(array[0]), array[iterator]);
                EEPROM.commit();
                iterator++;
            }
        }
    }
// TYPE STRING
MemoryString::MemoryString(int address)
{
    this->address = address;
}
String MemoryString::get()
{
    return EEPROM.readString(address);
}
void MemoryString::set(String valueString)
{          
    if(MemoryString::get() != valueString)
    {
        EEPROM.writeString(address, valueString);
        EEPROM.commit();
    }
    else
    {
        if(MemoryString::get() == "")
        {
            EEPROM.writeString(address, "\0");
            EEPROM.commit();
        }
    }  
}
// TYPE ASCII
void MemoryASCII::ASCII_UTF8_RU::use7LetterAlphabet(bool value)
{
    _letter7 = value;
}
byte MemoryASCII::ASCII_UTF8_RU::charToByte(const char symbol)
{
    byte value = symbol;
    return value;
}
char MemoryASCII::ASCII_UTF8_RU::byteToChar(const byte value)
{
    char symbol = value;
    return symbol;
}
String MemoryASCII::ASCII_UTF8_RU::getValue(const byte &key)
{
    String value = "";
    if (key >= _secondByteBegin && key <= _secondByteEnd)
    {
        for (auto it = _encoding.begin(); it != _encoding.end(); it++)
        {
            if (it->first == key)
            {
                value += it->second;
                return value;
            }
        }
    }
    char v = byteToChar(key);
    value += v;
    return value;
}
byte MemoryASCII::ASCII_UTF8_RU::getKey(const char &value)
{
    byte val = charToByte(value);
    if (val == _firstByteBegin)
    {
        _fb208 = true;
        return 0;
    }
    if (val == _firstByteEnd)
    {
        _fb209 = true;
        return 0;
    }
    if (val == 129 && _fb208)
    {
        if (_letter7)
        {
            val = 208;
        }
        else
        {
            val = 149;
        }
    }
    if (val == 145 && _fb209)
    {
        if (_letter7)
        {
            val = 209;
        }
        else
        {
            val = 181;
        }
    }
    if (_fb208){_fb208 = false;}
    if (_fb209){_fb209 = false;}
    return val;
}
MemoryASCII::MemoryASCII(const size_t address, const size_t range)
{
    _address = address;
    _range = range;
}
byte MemoryASCII::read(const size_t address)
{
    return EEPROM.readByte(address);
}
void MemoryASCII::readArray(String &target)
{
    size_t counter = 0;
    target = "";
    while (counter < _range)
    {
        byte v = read(_address + counter++);
        if (v == 0)
        {
            break;
        }
        if (v == 208)
        {
            target += "Ё";
        }
        else if (v == 209)
        {
            target += "ё";
        }
        else
        {
            target += ru.getValue(v);
        }
    }
}
bool MemoryASCII::write(const size_t address, const byte &value)
{
    #ifdef DEBUG
        Serial.println("---2-2-1");
    #endif
    byte oldValue = EEPROM.readByte(address);
    #ifdef DEBUG
        Serial.println("---2-2-2");
    #endif
    if (value != oldValue)
    {
        #ifdef DEBUG
            Serial.println("---2-2-3");
        #endif
        try
        {
            #ifdef DEBUG0
                Serial.println("ASCII\t//\t Read: " + String(address, DEC) + "\tVal: " + String(oldValue, DEC) + "\t//\t Write: " + String(address, DEC) + "\tVal: " + String(value, DEC));
            #endif
            EEPROM.writeByte(address, value);
            #ifdef DEBUG
                Serial.println("---2-2-4");
            #endif
            delay(1);
            EEPROM.commit();
            delay(1);
            #ifdef DEBUG
                Serial.println("---2-2-5");
            #endif
        }
        catch (const std::exception & ex)
        {
            Serial.print("ОШИБКА ЗАПИСИ! ");
            Serial.println(ex.what());
        }
        //Serial.println("WRITE ADDR: " + String(address, DEC) + ". VAL: " + String(value, DEC));
        #ifdef DEBUG
            Serial.println("---2-2-6");
        #endif
        return true;
    }
    #ifdef DEBUG0
        else
        {
            #ifdef DEBUG0
                Serial.println("ASCII\t//\t Read: " + String(address, DEC) + "\tVal: " + String(oldValue, DEC) + "\t//");
            #endif
        }
    #endif
    #ifdef DEBUG
        Serial.println("---2-2-7");
    #endif
    return false;
}
void MemoryASCII::writeArray(const String &source)
{
    size_t length = source.length();
    size_t counter = 0;
    size_t indx = 0;
    #ifdef DEBUG
        Serial.println("---2-1-1");
    #endif
    while (counter < length)
    {
        #ifdef DEBUG
            Serial.println("---2-1-2");
        #endif
        byte value = ru.getKey(source[counter]);
        #ifdef DEBUG
            Serial.println("---2-1-3");
        #endif
        if (value != 0)
        {
            #ifdef DEBUG
                Serial.println("---2-1-4");
            #endif
            write(_address + indx++, value);
            #ifdef DEBUG
            Serial.println("---2-1-5");
        #endif
        }
        #ifdef DEBUG
            Serial.println("---2-1-6");
        #endif
        counter++;
    }
    /* if (counter < length)
    {
        write(_address + counter, 0);
    } */
}