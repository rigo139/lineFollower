#include "PrototypeTwoWheelRobot.h"

#if defined(ARDUINO_ESP8266_ESP01)
#include <ESP8266WiFi.h>
#endif

PrototypeTwoWheelRobotClass::PrototypeTwoWheelRobotClass(void)
    : TwoWheelRobotClass(PWM_MIN_SPEED_VALUE, PWM_MAX_SPEED_VALUE, DEFAULT_STEERING_GAIN)
{
    // Empty Constructor
}

PrototypeTwoWheelRobotClass::~PrototypeTwoWheelRobotClass(void)
{
    // Turn off PWM
    #if     defined(ARDUINO_ESP8266_ESP01)
    analogWrite(PIN_LEFT_MOTOR_PWM, 0);
    analogWrite(PIN_RIGHT_MOTOR_PWM, 0);
    #elif   defined(ARDUINO_ESP32_DEV)
    ledcDetachPin(PIN_LEFT_MOTOR_PWM);
    ledcDetachPin(PIN_RIGHT_MOTOR_PWM);
    #endif
}

void PrototypeTwoWheelRobotClass::setup(void)
{
    #if     defined(ARDUINO_ESP8266_ESP01)
    analogWriteMode( PIN_LEFT_MOTOR_PWM, 0, PWM_HAS_OPEN_DRAIN);
    analogWriteMode(PIN_RIGHT_MOTOR_PWM, 0, PWM_HAS_OPEN_DRAIN);
    analogWriteFreq( MOTOR_PWM_FREQ );
    analogWriteResolution( MOTOR_PWM_RES );
    #elif   defined(ARDUINO_ESP32_DEV)
    // Setup PWM for left motor
    ledcAttachPin(PIN_LEFT_MOTOR_PWM, PWM_LEFT_MOTOR_CHANNEL);
    ledcSetup(PWM_LEFT_MOTOR_CHANNEL, MOTOR_PWM_FREQ, MOTOR_PWM_RES);

    // Setup PWM for right motor
    ledcAttachPin(PIN_RIGHT_MOTOR_PWM, PWM_RIGHT_MOTOR_CHANNEL);
    ledcSetup(PWM_RIGHT_MOTOR_CHANNEL, MOTOR_PWM_FREQ, MOTOR_PWM_RES);
    #endif

    // Initially stopped
    this->applyDutyCycle(0, 0);
}

void PrototypeTwoWheelRobotClass::applyDutyCycle(uint16_t pLeftMotorPwm, uint16_t pRightMotorPwm)
{
    #if defined(ARDUINO_ESP8266_ESP01)
    if(WiFi.scanComplete() < 0){return;}
    #endif

    #if     defined(ARDUINO_ESP8266_ESP01)
    analogWrite( PIN_LEFT_MOTOR_PWM, pLeftMotorPwm);
    analogWrite(PIN_RIGHT_MOTOR_PWM, pRightMotorPwm);
    #elif   defined(ARDUINO_ESP32_DEV)
    ledcWrite(PWM_LEFT_MOTOR_CHANNEL    , pLeftMotorPwm );
    ledcWrite(PWM_RIGHT_MOTOR_CHANNEL   , pRightMotorPwm);
    #endif
}