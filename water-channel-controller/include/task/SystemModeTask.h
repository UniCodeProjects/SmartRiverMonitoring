#ifndef SYSTEM_MODE_TASK_H
#define SYSTEM_MODE_TASK_H

#include <LiquidCrystal_I2C.h>

#include "../include/components/Valve.h"
#include "../include/components/ValveKnob.h"
#include "TaskImpl.h"

extern bool isAutomaticMode;
extern String receivedState;
extern bool fromDashboard;
extern int levelFromDashboard;

class SystemModeTask : public TaskImpl {
   public:
    SystemModeTask(LiquidCrystal_I2C* const monitor, ValveKnob* const knob, Valve* const valve, const int period);
    void start();

   private:
    LiquidCrystal_I2C* monitor;
    ValveKnob* knob;
    Valve* valve;
    enum { AUTOMATIC,
           LOCAL_MANUAL,
           REMOTE_CONTROL } state = AUTOMATIC;

    void printAndSetValveLevel(const int level);
};

#endif
