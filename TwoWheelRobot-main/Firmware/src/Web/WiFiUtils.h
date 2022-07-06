#pragma once 

#if     defined(ARDUINO_ESP8266_ESP01)
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>
#elif   defined(ARDUINO_ESP32_DEV)
#include <Update.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_ota_ops.h>
#endif
#include <ESPAsyncWebServer.h>

#define WIRELESS_NETWORK_INFO_FILE_NAME "/WirelessNetwork.data"

class WiFiUtils{
    #pragma region Attributes
    protected:
        #if   defined(ARDUINO_ESP32_DEV)
        static wifi_config_t _staConf;
        static String _SSID;
        static String _PSWD;
        #endif
        static String _apSSID;
        static String _apPSWD;
        static String _brandName;
        static uint32_t _lastCheck;
    #pragma endregion // Attributes

    #pragma region Functions
    public:
        static bool     updateIsRunning(){return Update.isRunning(); };
        static String   getSSID();
        static String   getPSWD();
        static String   getAcessPointSSID(){ return _apSSID; };
        static String   getAcessPointPSWD(){ return _apPSWD; };
        static void     handleInLoop();
        static bool     checkWiFiSTA();
        static void     setWirelessNetwork(String pSSID, String pPSWD);
        static void     setupWiFi(String brandName);
        static void     setupWiFiSTA(void);
    #pragma endregion // Functions
};