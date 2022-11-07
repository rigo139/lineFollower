#include "LineFinder.h"
#include <string.h>

#if !defined(M_MIN) && !defined(M_MAX)
#define M_MIN(a, b) ( (a) < (b) ? (a) : (b) ) //!< Get min value in a macro 
#define M_MAX(a, b) ( (a) > (b) ? (a) : (b) ) //!< Get max value in a macro
#endif

LineFinderClass::LineFinderClass(uint8_t pSensorCount, bool pLineIsBlack, uint16_t pMinAdcConstraint, uint16_t pMaxAdcConstraint)
        :   _sensorCount(pSensorCount),
            _lineIsBlack(pLineIsBlack),
            _hasNewData(0),
            _minAdcConstraint{ M_MIN(pMinAdcConstraint, pMaxAdcConstraint) },
            _maxAdcConstraint{ M_MAX(pMinAdcConstraint, pMaxAdcConstraint) },
            _linePosition(0),
            _sensorData{new uint16_t[pSensorCount]}
{
    // Fill sensor with 0 for start
    memset(_sensorData, 0, sizeof(uint16_t) * pSensorCount );
}

LineFinderClass::~LineFinderClass(void) {
    // Free allocated memory
    delete[] _sensorData;
    _sensorData = nullptr;
}

float LineFinderClass::findLinePosition(void)
{
    // Avoid unnecessary recalculation
    if(!_hasNewData){return getLastLinePosition();}
    _hasNewData = 0;

    // Weighted average
    // Values:  ADC Data 
    // Weights: Constants from 1 to N
    int32_t num = 0, den = 0;
    for(uint8_t i=0; i<_sensorCount; i++){
        uint16_t sample = evalueAdcSample( _sensorData[i] );
        num += (i - (_sensorCount/2)) * sample;
        den += sample;
    }
    // Remap weighted average from [1, N] to [-1, 1]
    _linePosition = num / ((den ? (float)den : 1.0f) * (_sensorCount/2));
    return _linePosition;
}

void LineFinderClass::setAdcConstraints(uint16_t pMinAdcConstraint, uint16_t pMaxAdcConstraint){
    // Updating ADC Constraints
    _minAdcConstraint = M_MIN(pMinAdcConstraint, pMaxAdcConstraint);
    _maxAdcConstraint = M_MAX(pMinAdcConstraint, pMaxAdcConstraint);
}

uint16_t LineFinderClass::constrainAdcSample(uint16_t adcSample) {
    // Constraining ADC Sample
    if( adcSample < _minAdcConstraint ){return _minAdcConstraint;}
    if( adcSample > _maxAdcConstraint ){return _maxAdcConstraint;}
    return adcSample;
}

uint16_t LineFinderClass::evalueAdcSample(uint16_t adcSample ) {
    // remapping from [min, max] to [0, (max-min)]
    adcSample = constrainAdcSample( adcSample ) - _minAdcConstraint;
    if(_lineIsBlack){
        // remapping [0, (max-min)] to [(max-min), 0]
        return (_maxAdcConstraint - _minAdcConstraint) - adcSample;
    }
    return adcSample;
}