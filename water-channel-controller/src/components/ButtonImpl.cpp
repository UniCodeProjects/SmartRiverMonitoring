#include "../../include/components/ButtonImpl.h"
#include <Arduino.h>

ButtonImpl::ButtonImpl(const int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

bool ButtonImpl::isPressed() {
    return digitalRead(this->pin) == HIGH;
}