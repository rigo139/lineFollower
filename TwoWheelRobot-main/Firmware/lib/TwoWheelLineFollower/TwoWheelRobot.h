//! 
//! @file TwoWheelRobot.h
//! @author Wellington R Gallo (wellington@navitastecnologia.com.br)
//! @brief Simple Two Wheel Robot Control
//! @date 2022-07-01
//! 
//! @copyright Copyright (c) 2022
//! 
//! 
#pragma once

#include <stdint.h>

// TODO Use integer numbers instead of floating-point whenever possible

//! @brief Simple Two Wheel Robot Control
class TwoWheelRobotClass
{
    // Public Methods
    public:
        //! @brief Construct a new Two Wheel Robot Class object
        //! 
        //! @param pMinMovingDutyCycle Duty-Cycle to minimum speed (but not stopped), used in the most high pitched curves
        //! @param pMaxMovingDutyCycle Duty-Cycle to maximum speed
        //! @param pSteeringSensibilityGain Steering Wheel Sensibility Gain, default to 1.0f
        TwoWheelRobotClass(uint16_t pMinMovingDutyCycle, uint16_t pMaxMovingDutyCycle, float pSteeringSensibilityGain = 1.0f);

        //! @brief Set the Steering Sensibility Gain object
        //! 
        //! @param pGain Update steering sensibility gain
        //! @return uint8_t 1 if gain was updated
        //! @return uint8_t 0 if gain was invalid (gain <= 0)
        uint8_t setSteeringSensibilityGain(float pGain);

        //! @brief Get the Actual Steering Wheel Position
        //! 
        //! @return float Value between [-1, 1], where -1 means left and +1 means right
        float getSteeringWheelPosition(void){return _steeringWheelPosition; }

        //! @brief Set the Steering Wheel Position
        //! 
        //! @param pSteeringWheelPosition Value between [-1, 1], where -1 means go left and +1 means go right 
        //! @param pSpeed Value between [-1, 1] where -1 means full backwards, 0 stopped, and 1 full speed
        void setSteeringWheelPosition(float pSteeringWheelPosition, float pSpeed=1.0f);

        //! @brief Set the Throttle percentage (percentage to max speed)
        //! 
        //! @param pThrottle Throttle value from 0 to 255
        void setThrottle(uint8_t pThrottle);

        //! @brief Get Throttle percentage
        //! 
        //! @return uint8_t Throttle value from 0 to 255
        uint8_t getThrottle(void){return _throttle;}

        //! @brief Apply duty-cicle in the hardware level
        //! 
        //! @param pLeftMotorPwm    Duty-Cycle for the Left Motor
        //! @param pRightMotorPwm   Duty-Cycle for the Right Motor
        //! @param pBackwards       1 for backwards       
        virtual void applyDutyCycle(uint16_t pLeftMotorPwm, uint16_t pRightMotorPwm, uint8_t pBackwards=0) = 0;

    // Protected Methods
    protected:
        //! @brief Evaluate the motor duty-cicle for the desired steering wheel position.
        //! 
        //! @param pSteeringWheelPosition Desired steering wheel position
        //! @param pSpeed Value between [-1, 1] where -1 means full backwards, 0 stopped, and 1 full speed
        //! @return uint16_t Motor duty-cicle value
        uint16_t findMotorDutyCycle(float pSteeringWheelPosition, float pSpeed);

    // Attributes
    protected:
        uint16_t _minMovingDutyCycle;           //!< Duty-Cycle to minimum speed (but not stopped)
        uint16_t _maxMovingDutyCycle;           //!< Duty-Cycle to maximum speed
        float    _steeringSensibilityGain;      //!< Steering wheel sensibility gain
        uint16_t _dutyCycleLeftMotor;           //!< Last Left  Motor Duty Cycle evaluated
        uint16_t _dutyCycleRightMotor;          //!< Last Right Motor Duty Cycle evaluated
        float    _steeringWheelPosition;        //!< Last robot steering wheel position
        uint8_t  _isBackwards : 1;              //!< Flag for rotation direction
        uint8_t  _throttle;                     //!< Throttle value (0 means stopped, 255 means max)    
};