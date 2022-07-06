//! 
//! @file LineFinder.h
//! @author Wellington R Gallo (wellington@navitastecnologia.com.br)
//! @brief Line finder for line follower applications with QTR sensors
//! @date 2022-07-01
//! 
//! @copyright Copyright (c) 2022
//! 
//! 
#pragma once

#include <stdint.h>
#include <stdbool.h>

//! 
//! @brief Line finder for line follower applications with QTR sensors
//! 
class LineFinderClass
{
    // Public member functions
    public:
        //! 
        //! @brief Construct a new Line Finder Class object
        //! 
        //! @param pSensorCount Count of QTR Sensors
        //! @param pLineIsBlack 1 if Line is black, 0 otherwise
        //! @param pMinAdcConstraint Constrain ADC Samples to this minimum value
        //! @param pMaxAdcConstraint Constrain ADC Samples to this maximum value
        //! 
        LineFinderClass(uint8_t pSensorCount, bool pLineIsBlack, uint16_t pMinAdcConstraint, uint16_t pMaxAdcConstraint);

        //! 
        //! @brief Destroy the Line Finder Class object
        //! 
        //! 
        virtual ~LineFinderClass(void);

        //! 
        //! @brief Find the direction to the line as a value between -1 and +1.
        //!
        //! @return float Value between interval [-1, 1]. -1 means left and +1 means right
        float findLinePosition(void);
        
        //! 
        //! @brief Get the Last Line Position object
        //! 
        //! @return float Value between interval [-1, 1]. -1 means left and +1 means right
        //! 
        float getLastLinePosition(void) {return _linePosition;}

        //! 
        //! @brief Get the Line Is Black object
        //! 
        //! @return true if following black line
        //! @return false if following white line
        //! 
        bool getLineIsBlack(void) {return _lineIsBlack;}

        //! 
        //! @brief Set the Line Is Black object
        //! 
        //! @param pLineIsBlack true to black line, false otherwise
        //! 
        void setLineIsBlack(bool pLineIsBlack) {_lineIsBlack = pLineIsBlack;}

        //! 
        //! @brief Set the Adc Constraints object
        //! 
        //! @param pMinAdcConstraint Constrain ADC Samples to this minimum value
        //! @param pMaxAdcConstraint Constrain ADC Samples to this maximum value
        //! 
        void setAdcConstraints(uint16_t pMinAdcConstraint, uint16_t pMaxAdcConstraint);

        //! 
        //! @brief Get the QTR ADC Value for a given index
        //! 
        //! @param pIndex Index of the QTR Sensor
        //! @return uint16_t ADC Value
        //! 
        uint16_t getQtrValue(uint8_t pIndex){return _sensorData[ pIndex % _sensorCount]; }
    
    // Protected member functions
    protected:

        //! 
        //! @brief  Refresh the _sensorData array with new samples.
        //!         Override this function in your application
        virtual void sampleSensors(void) = 0;

        //! 
        //! @brief Must be called after resampling!
        //!        
        void setFlagHasNewData(void){_hasNewData = 1;};

        //! 
        //! @brief Constraint the ADC Sample
        //! 
        //! @param adcSample ADC Sample to constrain
        //! @return uint16_t Constrained sample
        //! 
        uint16_t constrainAdcSample(uint16_t adcSample);

        //! 
        //! @brief Constrain and remap ADC sample range to a more useful range
        //! 
        //! @param adcSample ADC Sample
        //! @return uint16_t Constrained and remapped sample
        //! 
        uint16_t evalueAdcSample(uint16_t adcSample);

    // Member values
    protected:
        uint8_t   _sensorCount;             //!< Count of QTR Sensors
        uint8_t   _lineIsBlack : 1;         //!< Flag line is black
        uint8_t   _hasNewData : 1;          //!< Flag ADC Has been re-sampled
        uint16_t  _minAdcConstraint;        //!< Constrain ADC Samples to this minimum value
        uint16_t  _maxAdcConstraint;        //!< Constrain ADC Samples to this maximum value
        float     _linePosition;            //!< Last line position
        uint16_t* _sensorData;              //!< Dynamic array with ADC data
};