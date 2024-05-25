#include "../include/task/SystemModeTask.h"

#include <Arduino.h>

#include "../include/task/TaskImpl.h"

#define ALARM_TOO_LOW "ALARM-TOO-LOW"
#define NORMAL "NORMAL"
#define PRE_ALARM_TOO_HIGH "PRE-ALARM-TOO-HIGH"
#define ALARM_TOO_HIGH "ALARM-TOO-HIGH"
#define ALARM_TOO_HIGH_CRITIC "ALARM-TOO-HIGH-CRITIC"
#define LOW_OPENING_LEVEL 0
#define NORMAL_OPENING_LEVEL 25
#define HIGH_OPENING_LEVEL 50
#define CRITIC_OPENING_LEVEL 100

static int lastValveLevel;

SystemModeTask::SystemModeTask(LiquidCrystal_I2C* const monitor, ValveKnob* const knob, Valve* const valve, const int period) : TaskImpl(period) {
    this->monitor = monitor;
    this->knob = knob;
    this->valve = valve;
}

void SystemModeTask::start() {
    switch (state) {
        case AUTOMATIC:
            if (receivedState.equals(ALARM_TOO_LOW)) {
                printAndSetValveLevel(LOW_OPENING_LEVEL);
            } else if (receivedState.equals(NORMAL)) {
                printAndSetValveLevel(NORMAL_OPENING_LEVEL);
            } else if (receivedState.equals(ALARM_TOO_HIGH) || receivedState.equals(PRE_ALARM_TOO_HIGH)) {
                printAndSetValveLevel(HIGH_OPENING_LEVEL);
            } else if (receivedState.equals(ALARM_TOO_HIGH_CRITIC)) {
                printAndSetValveLevel(CRITIC_OPENING_LEVEL);
            }
            if (!isAutomaticMode) {
                state = fromDashboard ? REMOTE_CONTROL : LOCAL_MANUAL;
                if (state == REMOTE_CONTROL) {
                    /*
                     * With this instruction, the valve opening level will be set with the level
                     * currently written on the dashboard. Otherwise, the valve opening level would
                     * have been set with the last level read from the dashboard when this task was in
                     * REMOTE_CONTROL state, causing a mismatch with the dashboard.
                     */
                    levelFromDashboard = lastValveLevel;
                }
            }
            break;
        case LOCAL_MANUAL:
            printAndSetValveLevel(knob->getValveOpeningLevel());
            if (isAutomaticMode) {
                state = AUTOMATIC;
            }
            break;
        case REMOTE_CONTROL:
            printAndSetValveLevel(levelFromDashboard);
            if (isAutomaticMode) {
                state = AUTOMATIC;
            }
            break;
    }
}

void SystemModeTask::printAndSetValveLevel(const int level) {
    valve->setLevel(level);
    if (state != REMOTE_CONTROL && lastValveLevel != level) {
        Serial.println("VALVE_LVL=" + String(level));
        lastValveLevel = level;
    }
    monitor->setCursor(12, 3);
    monitor->print("   ");
    monitor->setCursor(12, 3);
    monitor->print(level);
}
