#ifndef SERVO_MOTOR_IMPL_H
#define SERVO_MOTOR_IMPL_H

#include <Arduino.h>
#include <ServoTimer2.h>

#include "ServoMotor.h"

/// @brief Implementation of a servo motor.
class ServoMotorImpl : public ServoMotor {
   public:
    /// @brief Default constructor.
    /// @param pin the pin in which the motor is plugged in. The pin must support PWM.
    ServoMotorImpl(const int pin);

    void on();
    void off();
    void setAngle(const int angle);

   private:
    int pin;
    ServoTimer2 servoMotor;
};

#endif
