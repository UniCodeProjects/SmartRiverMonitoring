#include "../include/components/PotentiometerImpl.h"
#include <Arduino.h>

PotentiometerImpl::PotentiometerImpl(const int pin) {
    this->pin = pin;
}

int PotentiometerImpl::readValue() {
    return analogRead(this->pin);
}
