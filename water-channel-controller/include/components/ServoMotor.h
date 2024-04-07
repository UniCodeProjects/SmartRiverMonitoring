#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

/// @brief Class that represents a generic servo motor.
class ServoMotor {
   public:
    /// @brief Turns on the motor.
    virtual void on() = 0;

    /// @brief Turns off the motor.
    virtual void off() = 0;

    /// @brief Sets the current angle of the motor with the provided one.
    /// @param angle The new angle of the motor. Its value must be between 0 and 179. Otherwise, the angle is not set.
    virtual void setAngle(int angle) = 0;
};

#endif
