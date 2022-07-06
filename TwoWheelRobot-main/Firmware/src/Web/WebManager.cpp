#include "WebManager.h"
#include <functional>

PrototypeWebServer::PrototypeWebServer(TwoWheelRobotClass* pRobot, LineFinderClass* pLineFinder)
    : TwoWheelLineFollowerClass(pRobot, pLineFinder),
    _server(80),
    _ws("/control"),
    _wsMessage(""),
    _steeringMode(STEERING_MODE_AUTO),
    _powerMode(0),
    _wsTimeLastWrite(0)
{
    //
}

#pragma region Public Methods

void PrototypeWebServer::setup(void)
{
    WiFiUtils::setupWiFi("PROTOTYPE");
    LibrariesServer::setupMainHandlers(_server);
	LibrariesServer::setupDefaultOTA( _server, "/uploadFirmware" );
    setupWebSockets();
    // Setup root request handler
    {
        auto cb = std::bind(&PrototypeWebServer::handleRoot, this, std::placeholders::_1);
        _server.on("/", cb);
    }
    // Setup statusJson request handler
    {
        auto cb = std::bind(&PrototypeWebServer::sendStatusJSON, this, std::placeholders::_1);
        _server.on("/status.json", cb);
    }
    _server.begin();
}

void PrototypeWebServer::handleInLoop()
{
    if( Update.isRunning() ){ return; }
    WiFiUtils::handleInLoop();
    _ws.cleanupClients();
    sendWSMessage();
    // Robot logic
    if(!_powerMode){
        _robot->applyDutyCycle(0, 0);
    }else if(_steeringMode == STEERING_MODE_AUTO){
        control();
    }
}

#pragma endregion // Public Methods

#pragma region Setup Methods

void PrototypeWebServer::setupWebSockets()
{
    // WS Event Callback
    {
        auto cb = std::bind(&PrototypeWebServer::handleWSOnEvent, this,
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3,
            std::placeholders::_4, std::placeholders::_5, std::placeholders::_6
        );
        _ws.onEvent( cb );
    }
    _server.addHandler(&_ws);
}
#pragma endregion // Setup Methods

#pragma region HTML Handlers  

void PrototypeWebServer::handleRoot(AsyncWebServerRequest *request)
{
    request->send_P(200, "text/html", HTML_ROOT);
}

void PrototypeWebServer::sendStatusJSON(AsyncWebServerRequest *request)
{
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    char temp[64];
    String jsonBuffer = "{";
    jsonBuffer.concat("\"AP SSID\":");sprintf( temp , "\"%s\"", WiFiUtils::getAcessPointSSID().c_str() );jsonBuffer.concat(temp);
    jsonBuffer.concat(",\r\n\"AP IPV4\":");sprintf( temp , "\"%s\"", WiFi.softAPIP().toString().c_str());jsonBuffer.concat(temp);
    if (WiFiUtils::getSSID() == "")
    {
        jsonBuffer.concat(",\r\n\"WiFi Info\":\"No\"");
    }
    else
    {
        jsonBuffer.concat(",\r\n\"SSID\":");sprintf(temp, "\"%s\"", WiFiUtils::getSSID().c_str());jsonBuffer.concat(temp);
        //jsonBuffer.concat(",\r\n\"PSWD\":");sprintf(temp, "\"%s\"", WiFiUtils::getPSWD().c_str());jsonBuffer.concat(temp);
        jsonBuffer.concat(",\r\n\"IPV4\":");sprintf(temp, "\"%s\"", WiFi.localIP().toString().c_str());jsonBuffer.concat(temp);
    }
    if( jsonBuffer.charAt( jsonBuffer.length()-1 ) == ',' ){
        jsonBuffer = jsonBuffer.substring(0, jsonBuffer.length() - 1 );
    }
    jsonBuffer.concat((char)'}');
    response->write(jsonBuffer.c_str());
    request->send(response);
}

#pragma endregion // HTML Methods 

#pragma region Web Sockets Methods 

void PrototypeWebServer::handleWSOnEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        //client connected
        #ifndef ARDUINO_ESP8266_ESP01
        Serial.printf("ws[%s][%u] connect\r\n", server->url(), client->id());
        #endif
        client->ping();
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        //client disconnected
        #ifndef ARDUINO_ESP8266_ESP01
        Serial.printf("ws[%s][%u] disconnect\r\n", server->url(), client->id());
        #endif
    }
    else if (type == WS_EVT_ERROR)
    {
        //error was received from the other end
        #ifndef ARDUINO_ESP8266_ESP01
        Serial.printf("ws[%s][%u] error(%u): %s\r\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
        #endif
    }
    else if (type == WS_EVT_PONG)
    {
        //pong message was received (in response to a ping request maybe)
        #ifndef ARDUINO_ESP8266_ESP01
        Serial.printf("ws[%s][%u] pong[%u]: %s\r\n", server->url(), client->id(), len, (len) ? (char *)data : "");
        #endif
    }
    else if (type == WS_EVT_DATA)
    {
        //data packet
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        
        if (info->final && info->index == 0 && info->len == len)
        {
            if (info->opcode != WS_TEXT){
                return;
            }
            data[len] = 0;
            _wsMessage = String( (char*)data );
            handleWSMessage(server, client);
        }
        else
        {
            if (info->message_opcode != WS_TEXT){
                return;
            }

            //message is comprised of multiple frames or the frame is split into multiple packets
            if( (info->index == 0) && (info->num == 0) )
            {
                _wsMessage = "";
            }

            data[len] = 0;
            #ifndef ARDUINO_ESP8266_ESP01
            Serial.printf("ws[%s][%u] frame[%u] text[%llu - %llu]: ", server->url(), client->id(), info->num, info->index, info->index + len);
            Serial.println( (char *)data );
            #endif
            _wsMessage.concat( (char *)data );

            if( (info->final) && ( (info->index + len) == info->len ) )
            {
                handleWSMessage(server, client);
            }
        }
    }
}

void PrototypeWebServer::handleWSMessage(AsyncWebSocket * server, AsyncWebSocketClient * client){
    //Serial.printf("ws[%s][%u] text: %s\r\n", server->url(), client->id(), _wsMessage.c_str() );
    DynamicJsonDocument jsonObj(320); // usually 16 per json object
	DeserializationError deserializeResult = deserializeJson(jsonObj, _wsMessage);
	if (deserializeResult != DeserializationError::Ok) {
        #ifndef ARDUINO_ESP8266_ESP01
		Serial.println(deserializeResult.f_str());
        #endif
		return;
	}

    if( jsonObj.containsKey("power") ) {
        _powerMode    = jsonObj["power"].as<uint8_t>() % 2;
    }
    if( jsonObj.containsKey("steeringMode")) {
        _steeringMode = jsonObj["steeringMode"].as<uint8_t>() % 2;
    }
    if( jsonObj.containsKey("throttleMode")) {
        _robot->setThrottleMode( jsonObj["throttleMode"].as<uint8_t>() );
    }
    if( ( _robot->getThrottleMode()==ROBOT_THROTTLE_MODE_MANUAL ) && jsonObj.containsKey("speed")) {
        _robot->setThrottle( jsonObj["speed"].as<uint8_t>() );
    }
    if( jsonObj.containsKey("qtrMax") && jsonObj.containsKey("qtrMin") ){
        _lineFinder->setAdcConstraints(jsonObj["qtrMin"].as<uint16_t>(), jsonObj["qtrMax"].as<uint16_t>());
    }
    if( jsonObj.containsKey("steeringGain")) { 
        _robot->setSteeringSensibilityGain( jsonObj["steeringGain"].as<float>() );
    }
    if( ( _steeringMode==STEERING_MODE_MANUAL ) && jsonObj.containsKey("steering") ) {
        _robot->setSteeringWheelPosition( jsonObj["steering"].as<int8_t>() / 127.0f );
    }
}

void PrototypeWebServer::sendWSMessage(void){
    if( (uint32_t)(millis() - _wsTimeLastWrite) < WS_WRITE_PERIOD_MS ){return;}
    // 125 chars json string
    _ws.printfAll("{\"qtr0\":%d,\"qtr1\":%d,\"qtr2\":%d,\"qtr3\":%d,\"qtr4\":%d,\"qtr5\":%d,\"qtr6\":%d,\"qtr7\":%d,\"speed\":%d,\"steering\":%d}",
        _lineFinder->getQtrValue(0),
        _lineFinder->getQtrValue(1),
        _lineFinder->getQtrValue(2),
        _lineFinder->getQtrValue(3),
        _lineFinder->getQtrValue(4),
        _lineFinder->getQtrValue(5),
        _lineFinder->getQtrValue(6),
        _lineFinder->getQtrValue(7),
        _robot->getThrottle(),
        (int8_t)(_robot->getSteeringWheelPosition()*127)
    );
    _wsTimeLastWrite = millis();
}

#pragma endregion // Web Sockets Methods 

