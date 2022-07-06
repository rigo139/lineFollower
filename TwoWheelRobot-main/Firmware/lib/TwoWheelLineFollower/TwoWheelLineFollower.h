#pragma once

#include <LineFinder.h>
#include <TwoWheelRobot.h>

class TwoWheelLineFollowerClass
{
    // Public Member Functions
    public:
        TwoWheelLineFollowerClass(TwoWheelRobotClass* pRobot, LineFinderClass* pLineFinder)
        : _robot( pRobot ),
          _lineFinder( pLineFinder )
        {
            //
        }

        void control(void) {
            float linePosition = _lineFinder->findLinePosition();
            _robot->setSteeringWheelPosition( linePosition );
        }

    // Protected Member Functions

    // Member Values
    protected:
        TwoWheelRobotClass* _robot;
        LineFinderClass*    _lineFinder;
};