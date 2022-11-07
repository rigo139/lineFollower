#include "PrototypeLineFinder.h"

PrototypeLineFinderClass::PrototypeLineFinderClass(void)
    :  LineFinderClass( DEFAULT_QTR_COUNT,
                        DEFAULT_LINE_IS_BLACK,
                        DEFAULT_ON_THE_LINE_ADC,
                        DEFAULT_OUT_OF_LINE_ADC ),
    _sensorsAreConnected(0),
    _lastSampleTimeMs(0),
    _adc0IsConnected(0),
    _adc1IsConnected(0)
{
    // Dynamic allocate memory for each filter
    for(uint8_t i=0; i<DEFAULT_QTR_COUNT; i++){
        _qtrFilter[i] = new SincFilter<uint16_t>(DEFAULT_SINC_FILTER_WINDOW);
    }
}

PrototypeLineFinderClass::~PrototypeLineFinderClass(void)
{
    // Free dynamic allocated memory for each filter
    for(uint8_t i=0; i<DEFAULT_QTR_COUNT; i++) {
        delete _qtrFilter[i];
        _qtrFilter[i] = nullptr;
    }
}

void PrototypeLineFinderClass::setup(void)
{
    // Setup I2C bus
    Wire.begin(PIN_SDA, PIN_SCL);

    // Setup External ADC Modules
    _sensorsAreConnected = 1;
    if( !_adc[0].begin( ADS1015_ADDRESS_MODULE0, &Wire ) ){
        _sensorsAreConnected = 0;
        #ifndef ARDUINO_ESP8266_ESP01
        puts("Failed to start ADC Module 1!");
        #endif
    }else{
        _adc0IsConnected = 1;
    }
    if( !_adc[1].begin( ADS1015_ADDRESS_MODULE1, &Wire ) ){
        _sensorsAreConnected = 0;
        #ifndef ARDUINO_ESP8266_ESP01
        puts("Failed to start ADC Module 2!");
        #endif
    }else{
        _adc1IsConnected = 1;
    }
    if(!_sensorsAreConnected){return;}
    for(uint8_t i=0; i<2; i++){
        _adc[i].setGain( GAIN_ONE );
        _adc[i].setDataRate( RATE_ADS1015_128SPS );
        _adc[i].startADCReading(ADS1X15_REG_CONFIG_MUX_DIFF_0_1, true);
    }
}

void PrototypeLineFinderClass::handleInLoop(void)
{
    if( (uint32_t)(millis() - _lastSampleTimeMs) < DEFAULT_SAMPLING_TIME_MS ){return;}
    this->sampleSensors();
}

uint8_t PrototypeLineFinderClass::getActualQtrIndex(uint8_t i)
{
    if(i == 4){return 0;}
    if(i == 5){return 1;}
    if(i == 6){return 2;}
    if(i == 7){return 3;}
    if(i == 3){return 4;}
    if(i == 2){return 5;}
    if(i == 1){return 6;}
    return 7;
}

void PrototypeLineFinderClass::sampleSensors(void)
{
    if(!_sensorsAreConnected){return;}
    
    // Pre-condition, only handle valid QTR Count 
    #if( DEFAULT_QTR_COUNT != 8)
    #error "This member function is not yet capable to handle QTRCount other than 8"
    #endif

    // Sample each sensor for each ADC module
    for(uint8_t i=0; i<DEFAULT_QTR_COUNT; i++){
        const uint16_t adcSample = _adc[(2 * i)/DEFAULT_QTR_COUNT].readADC_SingleEnded( i%4 );
        _sensorData[ getActualQtrIndex(i) ] = _qtrFilter[ i ]->iterate( M_MIN(0xFFF, adcSample) );
    }
    _lastSampleTimeMs = millis();

    // Set flag has new sample
    setFlagHasNewData();
}