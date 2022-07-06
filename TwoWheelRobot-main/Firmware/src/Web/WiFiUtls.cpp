#include "Web/WiFiUtils.h"

#pragma region Static Attributes
#if   defined(ARDUINO_ESP32_DEV)
wifi_config_t WiFiUtils::_staConf;
String WiFiUtils::_SSID = "";
String WiFiUtils::_PSWD = "";
#endif
String WiFiUtils::_apSSID = "";
String WiFiUtils::_apPSWD = "";
String WiFiUtils::_brandName = "";
uint32_t WiFiUtils::_lastCheck = 0;
#pragma endregion // Static Attributes

String WiFiUtils::getSSID() {
    #if   defined(ARDUINO_ESP32_DEV)
	esp_err_t value = esp_wifi_get_config(WIFI_IF_STA, &_staConf);
	if (value == ESP_OK) {
        _SSID = String((char*)_staConf.sta.ssid);
	}else{
        _SSID = String();
    }
	return _SSID;
    #else
    return WiFi.SSID();
    #endif
}

String WiFiUtils::getPSWD() {
    #if   defined(ARDUINO_ESP32_DEV)
	esp_err_t value = esp_wifi_get_config(WIFI_IF_STA, &_staConf);
	if (value == ESP_OK) {
        _PSWD = String((char*)_staConf.sta.password);
	}else{
	    _PSWD = String();
    }
    return _PSWD;
    #else
    return WiFi.psk();
    #endif
}

void WiFiUtils::handleInLoop()
{
    static bool __flagScanNetwork = false;
    if( (uint32_t)(millis() - _lastCheck) > 30000U )
    {
        _lastCheck = millis();
        __flagScanNetwork = !__flagScanNetwork;

        //if( (_ssid == "") && (_pswd == "1") ){ setupWiFiSTA(); }

        if( __flagScanNetwork )
        {
            #if     defined(ARDUINO_ESP8266_ESP01)
            WiFi.scanNetworks(false, false);
            #elif   defined(ARDUINO_ESP32_DEV)
            WiFi.scanNetworks(true, false, false, 100);
            #endif
        }else
        {
            checkWiFiSTA();
        }
    }
}

bool WiFiUtils::checkWiFiSTA()
{
    static bool _connectedToWifi = false;

    // WiFi STA is connected
    if( WiFi.status() == WL_CONNECTED )
    {
        // Failed to get IP
        if( WiFi.localIP() == IPAddress(0,0,0,0) )
        {
            // Disable WiFi
            WiFi.disconnect(true);
            _connectedToWifi = false;
            return _connectedToWifi;
        }

        // Just connected to WiFi
        if( !_connectedToWifi )
        {
            #ifndef ARDUINO_ESP8266_ESP01
            Serial.print("IP address: ");
            Serial.println( WiFi.localIP() );
            #endif
        }
        _connectedToWifi = true;
    }
    else
    {
        _connectedToWifi = false;
        setupWiFiSTA();   
    }
    return _connectedToWifi;
}

void WiFiUtils::setWirelessNetwork(String pSSID, String pPSWD)
{
    WiFi.begin(pSSID.c_str(), pPSWD.c_str());
    WiFi.setAutoReconnect( true );
    _lastCheck = millis();
}

void WiFiUtils::setupWiFi(String brandName)
{
    brandName.toUpperCase();
    _brandName = brandName;

    WiFi.mode(WIFI_AP_STA);

    // Get Mac Address
    uint8_t mac[] = {0, 0, 0, 0, 0, 0};
    // ESP_IF_WIFI_STA = 0,     /**< ESP32 station interface */
    // ESP_IF_WIFI_AP,          /**< ESP32 soft-AP interface */
    // ESP_IF_ETH,              /**< ESP32 ethernet interface */
    WiFi.macAddress(mac);

    // Get SSID
    char temp[22];
    sprintf(temp, "%s - %2.2X%2.2X%2.2X", brandName.c_str(), mac[3], mac[4], mac[5]);
    _apSSID = temp;
    sprintf(temp, "%s_I103", brandName.c_str());
    _apPSWD = temp;
    // Set AP with SSID
    WiFi.softAP( _apSSID.c_str() , _apPSWD.c_str() );
    
    // WiFi Connection 
    WiFiUtils::setupWiFiSTA();
}

void WiFiUtils::setupWiFiSTA(void) {
    WiFi.setHostname( _apSSID.c_str() );
    WiFi.begin();
    WiFi.setAutoReconnect( true );    
    _lastCheck = millis();
}


#pragma endregion // Functions

