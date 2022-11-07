#pragma once

#include <stdint.h>

#if !defined(M_MIN) && !defined(M_MAX)
#define M_MIN(a, b) ( (a) < (b) ? (a) : (b) ) //!< Get min value in a macro 
#define M_MAX(a, b) ( (a) > (b) ? (a) : (b) ) //!< Get max value in a macro
#endif

// Line Finder Config
#define ADS1015_ADDRESS_MODULE0     0x48    //!< I2C Address for ADC Module 0
#define ADS1015_ADDRESS_MODULE1     0x49    //!< I2C Address for ADC Module 1
#define DEFAULT_OUT_OF_LINE_ADC     3000    //!< On the line ADC value
#define DEFAULT_ON_THE_LINE_ADC     300     //!< Out of line ADC value
#define DEFAULT_QTR_COUNT           8       //!< QTR Sensor Count
#define DEFAULT_LINE_IS_BLACK       1       //!< Is line black
#define DEFAULT_SINC_FILTER_WINDOW  5       //!< Moving window average size
#define DEFAULT_SAMPLING_TIME_MS    50      //!< Sampling period in ms
// Two Wheel Robot Config
#define MOTOR_PWM_RES               10      //!< PWM Resolution [bits]
#define MOTOR_PWM_FREQ              15000U  //!< PWM Frequency [Hz]
#define PWM_LEFT_MOTOR_CHANNEL      1       //!< ESP PWM Channel to left motor
#define PWM_RIGHT_MOTOR_CHANNEL     2       //!< ESP PWM Channel to right motor
#define PWM_MAX_SPEED_VALUE         1023    //!< PWM Value for max speed
#define PWM_MIN_SPEED_VALUE         (PWM_MAX_SPEED_VALUE/2)//55      //!< PWM Value for min speed, but still moving
#define DEFAULT_STEERING_GAIN       0.5f    //!< Default steering wheel sensibility gain


// Board Pinout
#if     defined(ARDUINO_ESP8266_ESP01)
#define PWM_HAS_OPEN_DRAIN          0       //!< Using open-drain for PWM
#define PIN_LEFT_MOTOR_PWM          0       //!< Pin to control left  motor voltage using PWM
#define PIN_RIGHT_MOTOR_PWM         3       //!< Pin to control right motor voltage using PWM
#define PIN_SDA                     1       //!< I2C SDA Pin
#define PIN_SCL                     2       //!< I2C SCL Pin

// 
#elif   defined(ARDUINO_ESP32_DEV)
#define PIN_LEFT_MOTOR_DIR          14      //!< Left  Motor rotation direction
#define PIN_RIGHT_MOTOR_DIR         2       //!< Right Motor rotation direction
#define PIN_FLASHLIGHT              4       //!< On-board flashlight
#define PIN_LEFT_MOTOR_PWM          13      //!< Pin to control left  motor voltage using PWM
#define PIN_RIGHT_MOTOR_PWM         12      //!< Pin to control right motor voltage using PWM
#define PIN_SDA                     16      //!< I2C SDA Pin
#define PIN_SCL                     3       //!< I2C SCL Pin
#define PIN_UART_TX                 1

#else
#error "Your board is not yet compatible"
#endif