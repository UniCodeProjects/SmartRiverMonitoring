#include "../include/components/ValveKnob.h"
#include "../include/components/ValveImpl.h"

#include <Arduino.h>

ValveImpl::ValveImpl(ServoMotor* const servoMotor) {
    this->servoMotor = servoMotor;
}

void ValveImpl::setLevel(const int level) {
    if (level < 0) {
        servoMotor->setAngle(SERVO_MIN_ANGLE);
        return;
    } else if (level > VALVE_KNOB_LEVELS) {
        servoMotor->setAngle(SERVO_MAX_ANGLE);
        return;
    }
    servoMotor->setAngle(map(level, 0, VALVE_KNOB_LEVELS, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE));
}
