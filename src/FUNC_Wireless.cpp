#include "FUNC_Wireless.h"
#define DEBUG0
// Инициализация переменных
char ssid[25];
char password[65];
// Функции
byte Wireless(byte mode)
{
    wirelessMode = mode;
    switch (wirelessMode)
    {
        case WIRELESS_OFF:
        {
            WiFi.mode(WIFI_OFF);
            #ifdef DEBUG
                Serial.println("Wireless mode:\tOFF");
                Serial.println("-------------------------------");
            #endif
            break;
        }
        case WIRELESS_DEFAULT_AP:
        {
            const char ssid0[] = "Zoer_Baby_Sitter_";
            int num = 0;
            for (int i = 0; i < strlen(ssid0); i++)
            {
                ssid[num] = ssid0[i];
                num++;
            }
            char ssid1[5];
            snprintf(ssid1, 5, "%04X", (uint16_t)(ESP.getEfuseMac() >> 32));
            for (int i = 0; i < strlen(ssid1); i++)
            {
                ssid[num] = ssid1[i];
                num++;
            }
            ssid[num] = '\0';
            char passka[] = "admin123";
            int k = 0;
            for(int i = 0; i < strlen(passka); i++)
            {
                password[k] = passka[i];
                k++;
            }
            password[k] = '\0';
            #ifdef DEBUG
                Serial.println("Wireless mode:\tDefault AP");
                Serial.print("AP SSID:\t");
                Serial.println(ssid);
                Serial.print("AP password:\t");
                Serial.println(password);
            #endif
            WiFi.mode(WIFI_AP);
            WiFi.softAP(ssid, password);
            vTaskDelay(100);
                IPAddress ip = {192, 168, 4, 1};
                IPAddress mask = {255, 255, 255, 0};
                WiFi.softAPConfig(ip, ip, mask);
                #ifdef DEBUG_0
                    IPAddress myIP = WiFi.softAPIP();
                    Serial.print("AP IP address: ");
                    Serial.println(myIP);
                #endif
            break;
        }
        case WIRELESS_AP:
        {
            String ss = apSsid;
            ss.toCharArray(ssid, ss.length()+1);
            String pass = apPassword;
            pass.toCharArray(password, pass.length()+1);
            int channel = apChannel;
            int hidden = 0;
            if(apHiddenSsid)
            {
                hidden = 1;
            }
            WiFi.mode(WIFI_AP);
            WiFi.softAP(ssid, password, channel, hidden);
            if(apStaticNetworkConfig)
            {
                vTaskDelay(100);
                IPAddress ip = {apIp[0], apIp[1], apIp[2], apIp[3]};
                IPAddress mask = {apMask[0], apMask[1], apMask[2], apMask[3]};
                WiFi.softAPConfig(ip, ip, mask);
                #ifdef DEBUG
                    IPAddress myIP = WiFi.softAPIP();
                    Serial.print("AP IP address: ");
                    Serial.println(myIP);
                #endif
            }
            int sumMac = 0;
            for(byte i = 0; i < 6; i++)
            {
                sumMac += apMac[i];
            }
            if(sumMac != 0)
            {
                WiFi.softAPmacAddress(apMac);
            }
            #ifdef DEBUG
                Serial.println("Wireless mode:\tAP");
                Serial.print("AP SSID:\t");
                Serial.println(ssid);
                Serial.print("AP password:\t");
                Serial.println(password);
                Serial.print("AP IP address:\t");
                Serial.println(WiFi.softAPIP());
                Serial.println("-------------------------------");
            #endif
            break;
        }
        case WIRELESS_STA:
        {
            String ss = staSsid;
            ss.toCharArray(ssid, ss.length()+1);
            String pass = staPassword;
            pass.toCharArray(password, pass.length()+1);
            WiFi.mode(WIFI_STA);
            uint8_t encryptType;
            switch (staEncryptionType)
            {
                case ENCRYPT_OPEN:
                    encryptType = WIFI_AUTH_OPEN;
                    break;
                case ENCRYPT_WPA:
                    encryptType = WIFI_AUTH_WPA_PSK;
                    break;
                case ENCRYPT_WPA2:
                    encryptType = WIFI_AUTH_WPA2_PSK;
                    break;
                case ENCRYPT_WPA_WPA2:
                    encryptType = WIFI_AUTH_WPA_WPA2_PSK;
                    break;
                default:
                    encryptType = WIFI_AUTH_WEP;
                    break;
            }
            WiFi.encryptionType(encryptType);
            WiFi.begin(ssid, password);
            #ifdef DEBUG
                Serial.println("Wireless mode:\tSTA");
                Serial.print("STA SSID:\t");
                Serial.println(ssid);
                Serial.print("STA password:\t");
                Serial.println(password);
                Serial.println("-------------------------------");
            #endif
            if(staStaticNetworkConfig)
            {
                vTaskDelay(1000);
                IPAddress ip = {staIp[0], staIp[1], staIp[2], staIp[3]};
                IPAddress mask = {staMask[0], staMask[1], staMask[2], staMask[3]};
                IPAddress gate {staGateway[0], staGateway[1], staGateway[2], staGateway[3]};
                WiFi.config(ip, gate, mask);
                #ifdef DEBUG_0
                    IPAddress myIP = WiFi.localIP();
                    Serial.print("STA IP address: ");
                    Serial.println(myIP);
                #endif
            }
            int sumMac = 0;
            for(byte i = 0; i < 6; i++)
            {
                sumMac += staMac[i];
            }
            if(sumMac != 0)
            {
                WiFi.softAPmacAddress(staMac);
            }
            break;
        }
    }
    return wirelessMode;
}
bool WirelessStatus()
{
    if(WiFi.status() == WL_CONNECTED || WiFi.softAPgetStationNum() != 0)
    {
        return true;
    }else
    {
        return false;
    }
}