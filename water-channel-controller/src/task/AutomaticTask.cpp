#include "../include/task/AutomaticTask.h"

#include <Arduino.h>

#include "../include/task/TaskImpl.h"

#define ALARM_TOO_LOW "ALARM-TOO-LOW"
#define NORMAL "NORMAL"
#define ALARM_TOO_HIGH "ALARM-TOO-HIGH"
#define ALARM_TOO_HIGH_CRITIC "ALARM-TOO-HIGH-CRITIC"
#define LOW_OPENING_LEVEL 0
#define NORMAL_OPENING_LEVEL 25
#define HIGH_OPENING_LEVEL 50
#define CRITIC_OPENING_LEVEL 100

AutomaticTask::AutomaticTask(LiquidCrystal_I2C* const monitor, Valve* const valve, const int period) : TaskImpl(period) {
    this->monitor = monitor;
    this->valve = valve;
}

void AutomaticTask::start() {
    const String receivedState = Serial.readStringUntil('\n');
    monitor->clear();
    monitor->setCursor(3, 1);
    if (receivedState.equals(ALARM_TOO_LOW)) {
        printAndSetValveLevel(LOW_OPENING_LEVEL);
    } else if (receivedState.equals(NORMAL)) {
        printAndSetValveLevel(NORMAL_OPENING_LEVEL);
    } else if (receivedState.equals(ALARM_TOO_HIGH)) {
        printAndSetValveLevel(HIGH_OPENING_LEVEL);
    } else if (receivedState.equals(ALARM_TOO_HIGH_CRITIC)) {
        printAndSetValveLevel(CRITIC_OPENING_LEVEL);
    }
}

void AutomaticTask::printAndSetValveLevel(const int level) {
    valve->setLevel(level);
    monitor->print("Valve opening");
    monitor->setCursor(5, 2);
    monitor->print("level: " + String(level));
}
