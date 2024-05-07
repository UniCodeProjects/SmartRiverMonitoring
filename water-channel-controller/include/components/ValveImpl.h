#ifndef VALVE_IMPL_H
#define VALVE_IMPL_H

#include "ServoMotor.h"
#include "Valve.h"

/// @brief Basic implementation of a Valve.
class ValveImpl : public Valve {
   public:
    /// @brief Default constructor.
    /// @param servoMotor the motor used to represent the valve.
    ValveImpl(ServoMotor* servoMotor);

    void setLevel(int level);

    int getLevel();

   private:
    ServoMotor* servoMotor;
    int level;
};

#endif
