#pragma once

#include "Web/BinarySourceCode.h"
#include "Web/LibrariesSourceCode.h"
#include "Web/WebSourceCode.h"
#include "Web/WiFiUtils.h"
#include "ArduinoOTA.h"

typedef struct _scanned_wifi_data_t {
    String      _iSSID;
    uint8_t     _iEncryptionType;
    uint8_t*    _iBSSID;
    int32_t     _iRSSI;
    int32_t     _iChannel;
} scanned_wifi_data_t;

static scanned_wifi_data_t _temp_scanned_wifi_data_t = {
    ._iSSID = "12345678901234567890123456789012",
    ._iEncryptionType = 0,
    ._iBSSID          = 0,
    ._iRSSI           = 0,
    ._iChannel        = 0
};

class LibrariesServer{
    public:

        static String mainProcessor(const String& var){
            if( var == "__LOCALIP__"){return WiFi.softAPIP().toString();}
            return String();
        }

        static void setupMainHandlers(AsyncWebServer& server){
            server.onNotFound( LibrariesServer::handleNotFound  );
            // CSS 
            server.on("/Resources/CSS/bootstrap.css"        , LibrariesServer::handleBootstrapCSS           );
            server.on("/Resources/CSS/brand.css"            , LibrariesServer::handleBrandCSS               );
            // JS 
            server.on("/Resources/JS/jquery.js"             , LibrariesServer::handleJQuery                 );
            server.on("/Resources/JS/bootstrap.js"          , LibrariesServer::handleBootstrapJS            );
            server.on("/Resources/JS/bs_toogle.js"          , LibrariesServer::handleBootstrapToogleJS      );
            server.on("/Resources/JS/navitas.js"            , LibrariesServer::handleNavitasJS              );
            server.on("/Resources/JS/navitasRoot.js"        , LibrariesServer::handleNavitasRootJS          );
            server.on("/Resources/JS/md5.min.js"            , LibrariesServer::handleMD5JS                  );
            // Fig 
            server.on("/Resources/Fig/favicon.png"          , LibrariesServer::handleFavicon                );
            server.on("/Resources/Fig/navitas.png"          , LibrariesServer::handleNavitasLogo            );
            server.on("/Resources/Fig/logo.png"             , LibrariesServer::handleBrandLogo              );
            server.on("/Resources/Fig/brand_banner.jpg"     , LibrariesServer::handleBrandBanner            );
            // Fonts 
            server.on("/Resources/nunito_italic_200.woff2"  , LibrariesServer::handleNunitoFontItalic200    );
            // XML and JSON
            server.on("/rede.xml"                           , LibrariesServer::sendNetworksXML              );
            server.on("/firmware.json"                      , LibrariesServer::sendFirmwareInfoJSON         );
            // Forms
            server.on("/connectToWifi"                      , LibrariesServer::handleConnectToWiFi          );
        }

		static void setupDefaultOTA( AsyncWebServer& server, const char* formLink )
        {
            server.on( formLink, HTTP_POST, LibrariesServer::handleUploadFirmwareForm,  LibrariesServer::handleUploadFirmware );
        }

        static void handleNotFound(AsyncWebServerRequest *request){ request->send(404); }

        #pragma region Resources-CSS
        static void handleBootstrapCSS(AsyncWebServerRequest *request){ request->send_P( 200, "text/css", BOOTSTRAP_CSS ); }

        static void handleBrandCSS(AsyncWebServerRequest *request){ request->send_P( 200, "text/css", BRAND_CSS ); }
        #pragma endregion // Resources/CSS

        #pragma region Resources-JS 

        static void handleJQuery(AsyncWebServerRequest *request){ request->send_P( 200, "text/javascript", JQUERY_JS ); }

        static void handleBootstrapJS(AsyncWebServerRequest *request){ request->send_P( 200, "text/javascript", BOOTSTRAP_JS ); }
        
        static void handleBootstrapToogleJS(AsyncWebServerRequest *request){ request->send_P( 200, "text/javascript", BOOTSTRAP_TOOGLE_JS ); }

        static void handleNavitasJS(AsyncWebServerRequest *request){ request->send_P(200, "text/javascript", NAVITAS_JS, LibrariesServer::mainProcessor); }

        static void handleNavitasRootJS(AsyncWebServerRequest *request){ request->send_P(200, "text/javascript", NAVITAS_ROOT_JS); }

        static void handleMD5JS(AsyncWebServerRequest *request){ request->send_P( 200, "text/javascript", MD5_JS ); }

        #pragma endregion // Resources/JS 

        #pragma region Resources-Fig 
        static void handleFavicon(AsyncWebServerRequest *request){
            AsyncWebServerResponse *response = request->beginResponse_P(200, "image/png", FAVICON_PNG, FAVICON_PNG_SIZE);
            response->addHeader("Content-Encoding", "png");
            request->send(response);
        }

        static void handleNavitasLogo(AsyncWebServerRequest *request){
            AsyncWebServerResponse *response = request->beginResponse_P(200, "image/png", NAVITAS_LOGO, NAVITAS_LOGO_SIZE);
            response->addHeader("Content-Encoding", "png");
            request->send(response);
        }

        static void handleBrandLogo(AsyncWebServerRequest *request){
            AsyncWebServerResponse *response = request->beginResponse_P(200, "image/png", BRAND_LOGO, BRAND_LOGO_SIZE);
            response->addHeader("Content-Encoding", "png");
            request->send(response);
        }

        static void handleBrandBanner(AsyncWebServerRequest *request){
            AsyncWebServerResponse *response = request->beginResponse_P(200, "image/jpg", BRAND_BANNER, BRAND_BANNER_SIZE);
            response->addHeader("Content-Encoding", "jpg");
            request->send(response);
        }
        #pragma endregion // Resources/Fig

        #pragma region Resources-Fonts
        static void handleNunitoFontItalic200(AsyncWebServerRequest *request){
            AsyncWebServerResponse *response = request->beginResponse_P(200, "font/woff2", NUNITO_ITALIC_200_WOFF2, NUNITO_ITALIC_200_WOFF2_SIZE);
            response->addHeader("Content-Encoding", "woff2");
            request->send(response);
        }
        #pragma endregion // Resources-Fonts

        #pragma region XML and JSON
        static void sendNetworksXML(AsyncWebServerRequest *request)
        {
            AsyncResponseStream *response = request->beginResponseStream("text/xml");
            response->write(XML_START);
            String      _iSSID              = "";
            uint8_t     _iEncryptionType    = 0;
            uint8_t*    _iBSSID             = nullptr;
            int32_t     _iRSSI              = 0;
            int32_t     _iChannel           = 0;
            for( uint16_t i=0; i<16; i++)
            {
                #if    defined(ARDUINO_ESP8266_ESP01)
                bool    _isHidden = false;
                if( !WiFi.getNetworkInfo( i, _iSSID, _iEncryptionType, _iRSSI, _iBSSID, _iChannel, _isHidden) )
                {
                    break;
                }
                if( _isHidden ){continue;}
                #elif  defined(ARDUINO_ESP32_DEV)
                if( !WiFi.getNetworkInfo( i, _iSSID, _iEncryptionType, _iRSSI, _iBSSID, _iChannel) )
                {
                    break;
                }
                #endif
                response->write("\t<wifi>\r\n");
                response->printf("\t\t<ssid>%s</ssid>\r\n", _iSSID.c_str() );
                response->printf("\t\t<rssi>%d</rssi>\r\n", _iRSSI );
                #if     defined(ARDUINO_ESP8266_ESP01)
                response->printf("\t\t<encr>%d</encr>\r\n", (uint8_t)( _iEncryptionType != ((uint8_t)ENC_TYPE_NONE)) ) ;
                #elif   defined(ARDUINO_ESP32_DEV)
                response->printf("\t\t<encr>%d</encr>\r\n", (uint8_t)( _iEncryptionType != ((uint8_t)WIFI_AUTH_OPEN)) ) ;
                #endif
                response->write("\t</wifi>\r\n");
            }
            response->write(XML_END);
            request->send(response);
        }

        static void sendFirmwareInfoJSON(AsyncWebServerRequest *request)
        {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            char temp[64];

            String jsonBuffer = "{";
            #if     defined(ARDUINO_ESP8266_ESP01)
            jsonBuffer.concat("\"IDF\":"    );sprintf( temp , "\"%s\"", ARDUINO_ESP8266_RELEASE );jsonBuffer.concat(temp);
            #elif   defined(ARDUINO_ESP32_DEV)
            jsonBuffer.concat("\"IDF\":"    );sprintf( temp , "\"%s\"", esp_ota_get_app_description()->idf_ver );jsonBuffer.concat(temp);
            #endif
            #ifdef NAVITAS_PROJECT_VERSION
            jsonBuffer.concat("\r\n,\"Version\":");sprintf( temp , "\"%s\"", NAVITAS_PROJECT_VERSION );jsonBuffer.concat(temp);
            jsonBuffer.concat("\r\n,\"Date\":"   );sprintf( temp , "\"%s\"", NAVITAS_PROJECT_DATE    );jsonBuffer.concat(temp);
            #endif
            jsonBuffer.concat((char)'}');
            response->write(jsonBuffer.c_str());
            request->send(response);
        }
        #pragma endregion // XML and JSON

        #pragma region HTML and Forms
        static void handleUploadFirmwareForm(AsyncWebServerRequest *request)
        {
            if( request->hasParam("MD5", true, false) )
            {
                #ifndef ARDUINO_ESP8266_ESP01
                Serial.printf("MD5 = %s\r\n", request->arg("MD5").c_str() );
                #endif
                Update.setMD5( request->arg("MD5").c_str() );
                #ifndef ARDUINO_ESP8266_ESP01
                if( Update.end(true) ){
                    Serial.printf("Update Finished!\r\n");
                } else {
                    Update.printError(Serial);
                }
                #endif
            }else{
                #ifndef ARDUINO_ESP8266_ESP01
                Serial.println("No MD5!");
                #endif
            }
            #ifndef ARDUINO_ESP8266_ESP01
            Serial.flush();
            #endif
            request->redirect("/");
            delay(100);
            ESP.restart();
        }

        static void handleUploadFirmware(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
        {
            if( !request ){return;}
            if(!index){
                #ifndef ARDUINO_ESP8266_ESP01
                Serial.printf("\r\nUpdate Start: %s\n", filename.c_str());
                #endif
                for(uint8_t _pin=0; _pin<255; _pin++){ detachInterrupt( digitalPinToInterrupt(_pin) ); }
                noInterrupts();
                if(!Update.begin((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000)){
                    #ifndef ARDUINO_ESP8266_ESP01
                    Update.printError(Serial);
                    Serial.flush();
                    #endif
                    delay( 100 );
                    ESP.restart();
                }else{
                    //
                }
            }
            
            if(!Update.hasError()){
                if(Update.write(data, len) != len){
                    #ifndef ARDUINO_ESP8266_ESP01
                    Update.printError(Serial);
                    Serial.flush();
                    #endif
                    delay(100);
                    ESP.restart();
                }
            }
            
            if(final){
                #ifndef ARDUINO_ESP8266_ESP01
                Serial.printf("Update End: %uB\n", index+len);
                Serial.flush();
                #endif
            }

        }
        
        static void handleConnectToWiFi(AsyncWebServerRequest *request)
        {
            if (request->hasArg("SSID") && request->hasArg("PSWD"))
            {
                String _ssid = request->arg("SSID");
                String _pswd = request->arg("PSWD");
                #ifndef ARDUINO_ESP8266_ESP01
                Serial.printf("SSID = \"%s\", PSWD = \"%s\"\r\n", _ssid.c_str(), _pswd.c_str());
                #endif
                WiFiUtils::setWirelessNetwork(_ssid, _pswd);
            }
            request->redirect("/");
        }
        #pragma endregion // HTML and Forms
};

