#include "../../include/components/LedImpl.h"
#include <Arduino.h>

LedImpl::LedImpl(const int pin) {
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
}

void LedImpl::switchOn() {
    digitalWrite(this->pin, HIGH);
}

void LedImpl::switchOff() {
    digitalWrite(this->pin, LOW);
}