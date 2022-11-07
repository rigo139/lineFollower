#pragma once

#include "camera_pins.h"
#if (CAMERA_MODEL_SELECTED)
#include "esp_camera.h"
#include <WiFi.h>
#include <esp_wifi.h>

// Config
#define CAM_DISABLE_BROWNOUT    0
#define LOG_CAM_STREAM          1
#if __has_include("ArduinoWebsockets.h")
#define USING_TINYWEBSOCKETS 1
#include <ArduinoWebsockets.h>
using namespace websockets;
typedef WebsocketsServer CamServer_t;
#define SEND_CAMERA_PERIOD_MS   250U
#else
// See https://github.com/me-no-dev/ESPAsyncWebServer/issues/1082
#include <ESPAsyncWebServer.h>
#define USING_TINYWEBSOCKETS 0
typedef AsyncWebSocket CamServer_t;
//! Important!: Reduce WS_MAX_QUEUED_MESSAGES to a minimum
#define SEND_CAMERA_PERIOD_MS   250U
#endif

//! @brief Class to stream camera data to the WEBSOCKET_SERVER_ADDRESS
class CamStreamClass
{
    // Public Member Functions
    public:
        //! @brief Construct a new Cam Stream Class object
        //! 
        //! @param pWsAddress WebSocket server address
        CamStreamClass(String pWsAddress = String("/cam"));
        
        //! @brief Setup the camera streamer object
        esp_err_t setup(void);

        //! @brief Handle the camera stream object on loop
        void loop(void);

        #if !(USING_TINYWEBSOCKETS)
        //! @brief Get the Web Socket server object
        //! 
        //! @return AsyncWebSocket* Pointer to web-socket server
        AsyncWebSocket* getWebSocketServer(void) {return &_ws;}
        #endif

    // Protected Member Functions
    protected:

        //! @brief Send camera stream to server
        //! @return 1 if data was sent
        uint8_t sendCamera(void);
    
    // Attributes
    protected:
        CamServer_t     _ws;                        //!< Web Sockets Object
        uint32_t        _lastSentMs = 0;            //!< Millis timestamp of last sent
};

#endif // (CAMERA_MODEL_SELECTED)