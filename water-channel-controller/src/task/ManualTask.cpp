#include "../include/task/ManualTask.h"

ManualTask::ManualTask(Valve* const valve,
                       ValveKnob* const knob,
                       LiquidCrystal_I2C* const monitor,
                       const int period) : TaskImpl(period) {
    this->valve = valve;
    this->knob = knob;
    this->monitor = monitor;
}

void ManualTask::start() {
    if (!isAutomaticMode) {
        const int valveLevel = knob->getValveOpeningLevel();
        valve->setLevel(valveLevel);
        monitor->setCursor(12, 3);
        monitor->print("   ");
        monitor->setCursor(12, 3);
        monitor->print(valveLevel);
    }
}
