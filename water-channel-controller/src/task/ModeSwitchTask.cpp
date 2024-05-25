#include "../include/task/ModeSwitchTask.h"

#include <Arduino.h>

/// @brief `true` when the SystemModeTask must be in the AUTOMATIC mode, `false` otherwise.
bool isAutomaticMode = true;
/// @brief `true` when the SystemModeTask must be in the REMOTE_CONTROL mode, `false` otherwise.
bool fromDashboard = false;
// static variable used to update the state on the serial monitor only when it changes
static bool hasModeChanged = false;

ModeSwitchTask::ModeSwitchTask(Button* const button, LiquidCrystal_I2C* const monitor, const int period) : TaskImpl(period) {
    this->button = button;
    this->monitor = monitor;
}

void ModeSwitchTask::start() {
    if (!fromDashboard && button->isPressed()) {
        isAutomaticMode = !isAutomaticMode;
        Serial.println("Local manual mode: " + String(isAutomaticMode ? "OFF" : "ON"));
        hasModeChanged = true;
    } else if (isAutomaticMode || fromDashboard) {
        if (remoteControlState.equals("Remote control: ON")) {
            isAutomaticMode = false;
            fromDashboard = true;
            hasModeChanged = true;
            remoteControlState = ""; // remoteControlState is reset meaning that this task has read it
        } else if (remoteControlState.equals("Remote control: OFF")) {
            isAutomaticMode = true;
            fromDashboard = false;
            hasModeChanged = true;
            remoteControlState = ""; // remoteControlState is reset meaning that this task has read it
        }
    }
    printModeOnLCD();
}

void ModeSwitchTask::printModeOnLCD() {
    if (hasModeChanged) {
        monitor->setCursor(6, 0);
        monitor->print("              ");
        monitor->setCursor(6, 0);
        monitor->print(isAutomaticMode ? "AUTOMATIC" : (fromDashboard ? "REMOTE CONTROL" : "LOCAL MANUAL"));
        hasModeChanged = false;
    }
}
