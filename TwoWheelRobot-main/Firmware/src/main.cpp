#include <Arduino.h>
#include "Prototype/PrototypeLineFinder.h"
#include "Prototype/PrototypeTwoWheelRobot.h"
#include "Web/WebManager.h"

PrototypeTwoWheelRobotClass twoWheelRobot;
PrototypeLineFinderClass    lineFinder;
PrototypeWebServer          webServer(&twoWheelRobot, &lineFinder);

void setup()
{
    // Safe wait, avoid brownout miss-trigger
    delay(5000);

    #ifndef ARDUINO_ESP8266_ESP01
    Serial.begin(115200, SERIAL_8N1, -1, PIN_UART_TX);
    // Start default COM for debug information
    Serial.println("\r\nRobot says hello!");
    #endif

    // Setup robot
    twoWheelRobot.setup();
    lineFinder.setup();
    webServer.setup();
}

void loop()
{
    lineFinder.handleInLoop();
    webServer.handleInLoop();
}
