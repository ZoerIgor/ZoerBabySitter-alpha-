#include "Debug.h"
// Утечка памяти
    MemoryLeak::MemoryLeak(String description)
    {
        _description = description;
        _total = 0;
    }
    MemoryLeak::MemoryLeak(String description, int size)
    {
        _description = description;
        _size = size;
    }
    void MemoryLeak::add(int count)
    {
        _total += count * _size;
        Serial.println(_description + ":\t\t\t" + String(_total, DEC));
    }
    void MemoryLeak::add(int count, int size)
    {
        _total += count * size;
        Serial.println(_description + ":\t\t\t" + String(_total, DEC));
    }
    void MemoryLeak::remove(int count)
    {
        _total -= count * _size;
        if (_total < 0)
        {
            _total = 0;
        }
        Serial.println(_description + ":\t\t\t" + String(_total, DEC));
    }
    void MemoryLeak::remove(int count, int size)
    {
        _total -= count * size;
        if (_total < 0)
        {
            _total = 0;
        }
        Serial.println(_description + ":\t\t\t" + String(_total, DEC));
    }
    void MemoryLeak::getTotal()
    {
        Serial.println(_description + ":\t\t\t" + String(_total, DEC));
    }