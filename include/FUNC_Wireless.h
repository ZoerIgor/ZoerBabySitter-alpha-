#pragma once
#ifndef _FUNC_WIRELESS_H_
#define _FUNC_WIRELESS_H_
#include <Arduino.h>
#include <WiFi.h>
#include "main.h"
enum EnumWirelessMode
{
    WIRELESS_DEFAULT_AP,
    WIRELESS_AP,
    WIRELESS_STA,
    WIRELESS_OFF = 255
};
bool WirelessStatus();
void SetHostName(String hostName);
byte Wireless(byte mode);
#endif