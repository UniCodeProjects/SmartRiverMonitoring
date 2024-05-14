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
    if (!fromDashboard && button->isPressed()) {
        isAutomaticMode = !isAutomaticMode;
        Serial.println("Local manual mode: " + String(isAutomaticMode ? "OFF" : "ON"));
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
            levelFromDashboard = 0;
            hasModeChanged = true;
        } else if (remoteControlState != "") { // this last branch is needed in order not to waste the string read, if it has a meaning for the other tasks
            /*
             * If the remote control is enabled, if the string read is not "ON" or "OFF",
             * then it must be the valve opening level read from the dashboard.
             */
            if (fromDashboard) {
                levelFromDashboard = remoteControlState == "0\n" ? 0 : remoteControlState.toInt();
            } else { // If the remote control is not enabled and the string read is neither "ON" nor "OFF", then it is the current system state
                receivedState = remoteControlState;
            }
        }
        printModeOnLCD();
    }
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
