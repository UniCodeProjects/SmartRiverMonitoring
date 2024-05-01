#include "../include/task/ModeSwitchTask.h"

bool isAutomaticMode = true;

ModeSwitchTask::ModeSwitchTask(Button* const button, LiquidCrystal_I2C* const monitor, const int period) : TaskImpl(period) {
    this->button = button;
    this->monitor = monitor;
}

void ModeSwitchTask::start() {
    if (button->isPressed()) {
        isAutomaticMode = !isAutomaticMode;
        monitor->setCursor(8, 0);
        monitor->print("         ");
        monitor->setCursor(8, 0);
        monitor->print(isAutomaticMode ? "AUTOMATIC" : "MANUAL");
    }
}
