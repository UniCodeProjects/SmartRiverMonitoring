#include "../include/components/ValveKnobImpl.h"

ValveKnobImpl::ValveKnobImpl(Potentiometer* const potentiometer) {
    this->potentiometer = potentiometer;
}

int ValveKnobImpl::getValveOpeningLevel() {
    int step = POTENTIOMETER_LEVELS / VALVE_KNOB_LEVELS;
    int currentLevel = potentiometer->readValue() / step;
    return currentLevel <= VALVE_KNOB_LEVELS ? currentLevel : VALVE_KNOB_LEVELS;
}
