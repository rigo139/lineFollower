//! 
//! @file SincFilter.h
//! @author Wellington R Gallo (wellington@navitastecnologia.com.br)
//! @brief 1st order SincFilter as a CIC Moving Average Filter
//! @date 2022-07-01
//! 
//! @copyright Copyright (c) 2022
//! 
//! @code
//! const uint8_t N = FindMaxSincFilterWindow<uint8_t>(43);
//! printf("Max SincFilter window for type u8 and max value 43 = %d\n", N);
//! SincFilter<uint8_t> filter(N);
//! filter.iterate(0);              // Force filter to start with value 0
//! for(uint8_t i=0; i<N; i++) {
//!     printf( "%3d %3d\n", i, filter.iterate(43) );
//! }
//! @endcode
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <limits>
#include <type_traits>

//! 
//! @brief Evaluates what is the maximum window a SincFilter can have,
//!     when filtering a value that can be as high as `pMaxSampleValue`,
//!     when the values have type T
//!
//! @tparam T Type of numbers
//! @param pMaxSampleValue Max possible value to be filtered
//! @return uint8_t Max window to avoid overflow
//! 
template<typename T>
static uint8_t FindMaxSincFilterWindow(T pMaxSampleValue){
    if( std::is_floating_point<T>::value ){
        return 127;
    }
    T out = std::numeric_limits<T>::max() / pMaxSampleValue;
    return (uint8_t)((out > 127) ? 127 : ( (out < 0) ? 0 : out ));
}

//! 
//! @brief 1st order SincFilter as a CIC Moving Average Filter
//! 
//! @tparam T Type of the value being filtered
//! 
template<typename T>
class SincFilter
{
    public:
        //! 
        //! @brief Construct a new Sinc Filter object
        //! 
        //! @param N Size of the window
        //! 
        SincFilter(const uint8_t N);

        //! 
        //! @brief Filter a new sample
        //! 
        //! @param pSample Sample to be filtered
        //! @return T Filtered output
        //! 
        T iterate(T pSample);

        //! 
        //! @brief Get last filtered output
        //! 
        //! @return T last filtered output
        //! 
        T get(void);

        //! 
        //! @brief Destroy the Sinc Filter object
        //! 
        //! 
        ~SincFilter(void);

    protected:
        const uint8_t   _bufferLength;              //!< Size of the window
        T*              _buffer;                    //!< Buffer
        T               _bufferSum;                 //!< Sum of the buffer
        uint8_t         _i : 7;                     //!< Circular index to avoid shifting
        uint8_t         _flagNeverSampled : 1;      //!< Flag to treat first sample differently
};




//#region Implementation

// Template Class are preferred to be implemented in header to avoid linker errors
// https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl

template<typename T>
SincFilter<T>::SincFilter(const uint8_t N)
    : _bufferLength(N),
    _buffer{new T[N]},
    _bufferSum(0),
    _i(0),
    _flagNeverSampled(1)
{
    //
}

template<typename T>
SincFilter<T>::~SincFilter(){
    delete[] _buffer;
    _buffer = nullptr;
}

template<typename T>
T SincFilter<T>::iterate(T pSample)
{
    // Treat invalid floating-point values as 0
    if( std::is_floating_point<T>::value ){
        if( std::isnan(pSample) || std::isinf(pSample) ){
            pSample = 0;
        }
    }

    // Fix first sample to act as starting already filtered
    if( _flagNeverSampled ){
        _flagNeverSampled = 0;
        for(_i=0; _i<_bufferLength; _i++){
            _buffer[_i] = pSample;
        }
        _bufferSum = pSample * _bufferLength;
    }

    // Filter
    _i          = (_i >= _bufferLength) ? 0 : _i;
    _bufferSum += ( pSample - _buffer[_i] );
    _buffer[ _i++ ] = pSample;
    return get();
}

template<typename T>
T SincFilter<T>::get(void){return _bufferSum/( (T)_bufferLength );}

//#endregion Implementation