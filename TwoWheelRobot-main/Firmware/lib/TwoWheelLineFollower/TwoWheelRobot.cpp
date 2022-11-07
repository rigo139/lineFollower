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
                _isBackwards(0),
                _throttle(0)
{
    //
}

uint8_t TwoWheelRobotClass::setSteeringSensibilityGain(float pSteeringSensibilityGain){
    if(pSteeringSensibilityGain <= 0){return 0;}
    _steeringSensibilityGain = pSteeringSensibilityGain;
    return 1;
}

void TwoWheelRobotClass::setSteeringWheelPosition(float pSteeringWheelPosition, float pSpeed) {
    _steeringWheelPosition = pSteeringWheelPosition;
    _isBackwards         = pSpeed < 0;
    _dutyCycleLeftMotor  = findMotorDutyCycle(  pSteeringWheelPosition, pSpeed);
    _dutyCycleRightMotor = findMotorDutyCycle( -pSteeringWheelPosition, pSpeed);
    applyDutyCycle(_dutyCycleLeftMotor, _dutyCycleRightMotor, _isBackwards);
}

void TwoWheelRobotClass::setThrottle(uint8_t pThrottle) {
    _throttle = pThrottle;
}

uint16_t TwoWheelRobotClass::findMotorDutyCycle(float pSteeringWheelPosition, float pSpeed) {
    //  x   , LeftMotor = M(x)  , RightMotor = M(-x)
    // -1   , stopped           , min
    //  0   , max               , max
    //  1   , min               , stopped
    
    // Apply gain while constraining Steering Position to [-1, 1]
    pSteeringWheelPosition *= _steeringSensibilityGain;
    if( pSteeringWheelPosition < -1 ){pSteeringWheelPosition = -1;}
    if( pSteeringWheelPosition >  1 ){pSteeringWheelPosition =  1;}
    // Saturate speed and consider always positive
    pSpeed = pSpeed < 0 ? -pSpeed : pSpeed;
    if( pSpeed > 1){ pSpeed = 1.0f; }

    // Auto or Manual speed
    const uint16_t maxDuty = (_throttle/255.0f) * pSpeed * _maxMovingDutyCycle;
	
	//const uint16_t minDuty = maxDuty;
    const uint16_t minDuty = M_MIN( _minMovingDutyCycle , maxDuty );

    // if( x < 0 ): Remap [-1, 0] -> [  0, max]
    if( pSteeringWheelPosition <= 0 ){ return maxDuty * (pSteeringWheelPosition + 1); }
    // if( x > 0 ): Remap [ 0, 1] -> [max, min]
    return maxDuty - (maxDuty - minDuty) * pSteeringWheelPosition;
}