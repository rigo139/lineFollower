#pragma once

// Core
#if     defined(ARDUINO_ESP8266_ESP01)
#include <ESP8266WiFi.h>
#elif   defined(ARDUINO_ESP32_DEV)
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_ota_ops.h>
#endif
// 3rd Party
#include <ESPAsyncWebServer.h>
//#include <ArduinoWebsockets.h> // TODO migrate
#include <ArduinoJson.h>
// Project
#include "Web/BinarySourceCode.h"
#include "Web/LibrariesSourceCode.h"
#include "Web/WebSourceCode.h"

class LibrariesServer
{
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
            server.on("/Resources/JS/nipplejs.min.js"       , LibrariesServer::handleNippleJS               );
            // Fig 
            server.on("/Resources/Fig/favicon.png"          , LibrariesServer::handleFavicon                );
            server.on("/Resources/Fig/logo.png"             , LibrariesServer::handleBrandLogo              );
            server.on("/Resources/Fig/brand_banner.jpg"     , LibrariesServer::handleBrandBanner            );
            // Fonts 
            server.on("/Resources/nunito_italic_200.woff2"  , LibrariesServer::handleNunitoFontItalic200    );
            // XML and JSON
            server.on("/rede.xml"                           , LibrariesServer::sendNetworksXML              );
            // Forms
            server.on("/connectToWifi"                      , LibrariesServer::handleConnectToWiFi          );
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

        static void handleNippleJS(AsyncWebServerRequest *request){ request->send_P(200, "text/javascript", NIPPLE_JS); }
        #pragma endregion // Resources/JS 

        #pragma region Resources-Fig 
        static void handleFavicon(AsyncWebServerRequest *request){
            AsyncWebServerResponse *response = request->beginResponse_P(200, "image/png", FAVICON_PNG, FAVICON_PNG_SIZE);
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
        #pragma endregion // XML and JSON

        #pragma region HTML and Forms
        static void handleConnectToWiFi(AsyncWebServerRequest *request) {
            if (request->hasArg("SSID") && request->hasArg("PSWD")) {
                String _ssid = request->arg("SSID");
                String _pswd = request->arg("PSWD");
                #ifndef ARDUINO_ESP8266_ESP01
                Serial.printf("SSID = \"%s\", PSWD = \"%s\"\r\n", _ssid.c_str(), _pswd.c_str());
                #endif
                WiFi.begin(_ssid.c_str(), _pswd.c_str());
            }
            request->redirect("/");
        }
        #pragma endregion // HTML and Forms
};

