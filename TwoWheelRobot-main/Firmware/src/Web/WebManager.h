#pragma once

// Project
#include "WebLibrariesServer.h"
#include <TwoWheelLineFollower.h>
#if   defined(ARDUINO_ESP32_DEV)
#include <CamStream.h>
#endif

enum _steering_mode_t {
    STEERING_MODE_MANUAL = 0,
    STEERING_MODE_AUTO
};
typedef uint8_t steering_mode_t;

#define WS_WRITE_PERIOD_MS  250

class PrototypeWebServer : public TwoWheelLineFollowerClass {
    // Public Usage
    public:
        // Constructor
        PrototypeWebServer(TwoWheelRobotClass* pRobot, LineFinderClass* pLineFinder);

        // Public Methods
        void setup(void);
        void handleInLoop();

    // Protected Methods
    protected:
        // Configuration
        void setupWiFi(String pName = "Robot");
        void setupWebSockets();
        void sendWSMessage(void);  

    // Callbacks
    public:
        // HTML Handlers 
        void handleRoot(AsyncWebServerRequest *request);
        // Send XML and JSON
        void sendStatusJSON(AsyncWebServerRequest *request);
        // Web Sockets Handlers
        void handleWSOnEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
        void handleWSMessage(AsyncWebSocket * server, AsyncWebSocketClient * client);
    
    // Attributes
    protected:
        // Attributes
        AsyncWebServer  _server;
        AsyncWebSocket  _ws;
        String          _wsMessage;
        steering_mode_t _steeringMode : 1;
        uint8_t         _powerMode : 1;
        uint32_t        _wsTimeLastWrite;
        #if CAMERA_MODEL_SELECTED
        CamStreamClass  _cam;
        #endif
};