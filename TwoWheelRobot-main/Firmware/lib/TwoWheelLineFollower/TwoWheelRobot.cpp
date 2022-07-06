#include "TwoWheelRobot.h"

#if !defined(M_MIN) && !defined(M_MAX)
#define M_MIN(a, b) ( (a) < (b) ? (a) : (b) ) //!< Get min value in a macro 
#define M_MAX(a, b) ( (a) > (b) ? (a) : (b) ) //!< Get max value in a macro
#endif

TwoWheelRobotClass::TwoWheelRobotClass(uint16_t pMinMovingDutyCycle, uint16_t pMaxMovingDutyCycle, float pSteeringSensibilityGain)
            :   _minMovingDutyCycle( pMinMovingDutyCycle ),
                _maxMovingDutyCycle( pMaxMovingDutyCycle ),
                _steeringSensibilityGain( pSteeringSensibilityGain ),
                _dutyCycleLeftMotor( 0 ),
                _dutyCycleRightMotor( 0 ),
                _throttleMode(ROBOT_THROTTLE_MODE_AUTO),
                _throttle(0xFF)
{
    //
}

uint8_t TwoWheelRobotClass::setSteeringSensibilityGain(float pSteeringSensibilityGain){
    if(pSteeringSensibilityGain <= 0){return 0;}
    _steeringSensibilityGain = pSteeringSensibilityGain;
    return 1;
}

void TwoWheelRobotClass::setSteeringWheelPosition(float pSteeringWheelPosition) {
    _steeringWheelPosition = pSteeringWheelPosition;
    _dutyCycleLeftMotor  = findMotorDutyCycle(  pSteeringWheelPosition );
    _dutyCycleRightMotor = findMotorDutyCycle( -pSteeringWheelPosition );
    applyDutyCycle(_dutyCycleLeftMotor, _dutyCycleRightMotor);
    if(_throttleMode == ROBOT_THROTTLE_MODE_AUTO ){
        _throttle = ( (M_MAX(_dutyCycleLeftMotor, _dutyCycleRightMotor))*0xFF )/ _maxMovingDutyCycle;
    }
}

void TwoWheelRobotClass::setThrottle(uint8_t pThrottle) {
    _throttle = pThrottle;
}

uint16_t TwoWheelRobotClass::findMotorDutyCycle(float pSteeringWheelPosition) {
    //  x   , LeftMotor = M(x)  , RightMotor = M(-x)
    // -1   , stopped           , min
    //  0   , max               , max
    //  1   , min               , stopped
    
    // Apply gain while constraining Steering Position to [-1, 1]
    pSteeringWheelPosition *= _steeringSensibilityGain;
    if( pSteeringWheelPosition < -1 ){pSteeringWheelPosition = -1;}
    if( pSteeringWheelPosition >  1 ){pSteeringWheelPosition =  1;}

    // Auto or Manual speed
    const uint16_t maxDuty = (_throttleMode == ROBOT_THROTTLE_MODE_AUTO )
        ? _maxMovingDutyCycle
        : (_throttle/255.0f) * _maxMovingDutyCycle;
    const uint16_t minDuty = (_throttleMode == ROBOT_THROTTLE_MODE_AUTO ) ? _minMovingDutyCycle : _maxMovingDutyCycle;

    // if( x <= 0 ): Remap [-1, 0] -> [0, max]
    if( pSteeringWheelPosition <= 0 ){
        return maxDuty * (pSteeringWheelPosition + 1);
    }
    // else: Remap [0, 1] -> [min, max]
    return maxDuty - (maxDuty - minDuty) * pSteeringWheelPosition;
}