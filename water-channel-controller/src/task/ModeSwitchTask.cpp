#include "../include/task/ModeSwitchTask.h"

#include <Arduino.h>

bool isAutomaticMode = true;
bool fromDashboard = false;
static bool hasModeChanged = false;
String receivedState;
int levelFromDashboard = 0;

ModeSwitchTask::ModeSwitchTask(Button* const button, LiquidCrystal_I2C* const monitor, const int period) : TaskImpl(period) {
    this->button = button;
    this->monitor = monitor;
}

void ModeSwitchTask::start() {
    if (button->isPressed()) {
        isAutomaticMode = !isAutomaticMode;
        hasModeChanged = true;
        printModeOnLCD();
    }
    if (isAutomaticMode || fromDashboard) {
        const String remoteControlState = Serial.readStringUntil('\n');
        if (remoteControlState.equals("ON")) {
            isAutomaticMode = false;
            fromDashboard = true;
            hasModeChanged = true;
        } else if (remoteControlState.equals("OFF")) {
            isAutomaticMode = true;
            fromDashboard = false;
            hasModeChanged = true;
        } else if (remoteControlState != "") { // this last branch is needed in order not to waste the string read, if it has a meaning for the other tasks
            if (fromDashboard) {
                // TODO: remove startsWith() control, the server should not send the system state in the remote control mode
                levelFromDashboard = remoteControlState == "0\n" ? 0 : (remoteControlState.startsWith("ALARM") ? levelFromDashboard : remoteControlState.toInt());
            } else {
                receivedState = remoteControlState;
            }
        }
        printModeOnLCD();
    }
}

void ModeSwitchTask::printModeOnLCD() {
    if (hasModeChanged) {
        monitor->setCursor(8, 0);
        monitor->print("         ");
        monitor->setCursor(8, 0);
        monitor->print(isAutomaticMode ? "AUTOMATIC" : "MANUAL");
        hasModeChanged = false;
    }
}
