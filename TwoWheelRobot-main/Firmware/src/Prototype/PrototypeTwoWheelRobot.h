//! 
//! @file PrototypeTwoWheelRobot.h
//! @author Igor Herdt (igor.herdt@catolicasc.edu.br)
//! @author Wellington R Gallo (wellington@navitastecnologia.com.br)
//! @brief Prototype implementation for a Two Wheel Robot
//! @date 2022-07-01
//! 
//! @copyright Copyright (c) 2022
//! 
#pragma once

#include <Arduino.h>
#include <TwoWheelRobot.h>
#include "PrototypeConfig.h"

//! 
//! @brief Prototype implementation of TwoWheelRobotClass
//! 
class PrototypeTwoWheelRobotClass : public TwoWheelRobotClass
{
    // Public Member Functions
    public:
        //! 
        //! @brief Construct a new Prototype Two Wheel Robot Class object
        //! 
        PrototypeTwoWheelRobotClass(void);

        //! 
        //! @brief Destroy the Prototype Two Wheel Robot Class object
        //! 
        ~PrototypeTwoWheelRobotClass(void);

        //! 
        //! @brief Setup the Prototype Two Wheel Robot object
        //! 
        void setup(void);

    // Protected Member Functions
    protected:
        //! 
        //! @brief Apply duty-cicle in the hardware level
        //! 
        //! @param pLeftMotorPwm    Duty-Cycle for the Left Motor
        //! @param pRightMotorPwm   Duty-Cycle for the Right Motor
        //! @param pBackwards       1 for backwards       
        void applyDutyCycle(uint16_t pLeftMotorPwm, uint16_t pRightMotorPwm, uint8_t pBackwards=0);
};