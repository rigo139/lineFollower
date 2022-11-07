//! 
//! @file PrototypeLineFinder.h
//! @author Igor Herdt (igor.herdt@catolicasc.edu.br)
//! @author Wellington R Gallo (wellington@navitastecnologia.com.br)
//! @brief Prototype implementation for a Line Follower logic
//! @date 2022-07-01
//! 
//! @copyright Copyright (c) 2022
//! 
#pragma once

#include <LineFinder.h>
#include <Adafruit_ADS1X15.h>
#include <SincFilter.h>
#include "PrototypeConfig.h"

//! 
//! @brief Prototype implementation of LineFinderClass
//! 
class PrototypeLineFinderClass : public LineFinderClass
{
    // Public Methods
    public:
        //! 
        //! @brief Construct a new Prototype Line Finder Class object
        //! 
        PrototypeLineFinderClass(void);

        //! 
        //! @brief Destroy the Prototype Line Finder Class object
        //! 
        ~PrototypeLineFinderClass(void);

        //! 
        //! @brief Setup the Prototype Line Finder Class object
        //! 
        void setup(void);

        //! 
        //! @brief  Check if it is time to resample the sensor. 
        //!         Must be called periodically
        //!
        void handleInLoop(void);

        uint8_t getIsAdcModule1Connected(void){return _adc0IsConnected;}
        uint8_t getIsAdcModule2Connected(void){return _adc1IsConnected;}
    
    // Protected Methods
    protected:
        //! 
        //! @brief Sample the QTR Sensors
        //! 
        void sampleSensors(void);

        //! 
        //! @brief Get the index of the QTR sensor from ADC Index.
        //! Both ADC modules (0 and 1) have 4 channels each
        //!
        //! @param uint8_t i (ModuleIndex*4 + ChannelIndex)
        //! @return uint8_t actual QTR Index, from 0 (left) to DEFAULT_QTR_COUNT-1 (right)
        //!
        uint8_t getActualQtrIndex(uint8_t i);
    
    // Attributes
    protected:
        uint8_t                 _sensorsAreConnected;               //!< Flag ADS1015 sensors are connected
        uint32_t                _lastSampleTimeMs;                  //!< Time of last sampling in ms
        Adafruit_ADS1015        _adc[2];                            //!< ADS1015 Instances
        SincFilter<uint16_t>*   _qtrFilter[DEFAULT_QTR_COUNT];      //!< Dynamic Filter for each QTR Sensor
        uint8_t                 _adc0IsConnected : 1;
        uint8_t                 _adc1IsConnected : 1;
};