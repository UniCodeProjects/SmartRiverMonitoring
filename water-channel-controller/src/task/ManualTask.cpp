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
        monitor->clear();
        monitor->setCursor(2, 0);
        monitor->print("Mode: MANUAL");
        const int valveLevel = knob->getValveOpeningLevel();
        valve->setLevel(valveLevel);
        monitor->setCursor(3, 2);
        monitor->print("Valve opening");
        monitor->setCursor(5, 3);
        monitor->print("level: " + String(valveLevel));
    }
}
