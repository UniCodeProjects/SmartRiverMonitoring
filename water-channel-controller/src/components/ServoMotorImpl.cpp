#include "../../include/components/ServoMotorImpl.h"
#include <ServoTimer2.h>

#define ANGLE_COEFFICIENT 8.33
#define ZERO_DEGREE_VALUE 750.0

ServoMotorImpl::ServoMotorImpl(const int pin) {
    this->pin = pin;
}

void ServoMotorImpl::on() {
    servoMotor.attach(this->pin);
}

void ServoMotorImpl::off() {
    servoMotor.detach();
}

void ServoMotorImpl::setAngle(const int angle) {
    if (angle >= SERVO_MIN_ANGLE && angle <= SERVO_MAX_ANGLE) {
        servoMotor.write(ZERO_DEGREE_VALUE + (ANGLE_COEFFICIENT * angle));
    }
}
