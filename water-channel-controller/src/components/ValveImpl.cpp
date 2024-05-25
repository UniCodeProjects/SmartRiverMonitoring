#include "../include/components/ValveImpl.h"

#include <Arduino.h>

#include "../include/components/ValveKnob.h"

ValveImpl::ValveImpl(ServoMotor* const servoMotor) {
    this->servoMotor = servoMotor;
}

void ValveImpl::setLevel(const int level) {
    this->level = level < 0 ? SERVO_MIN_ANGLE : (level > VALVE_KNOB_LEVELS ? SERVO_MAX_ANGLE : level);
    servoMotor->setAngle(map(this->level, 0, VALVE_KNOB_LEVELS, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE));
}

int ValveImpl::getLevel() {
    return this->level;
}
