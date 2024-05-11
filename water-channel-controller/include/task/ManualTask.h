#ifndef MANUAL_TASK_H
#define MANUAL_TASK_H

#include <LiquidCrystal_I2C.h>

#include "../components/Valve.h"
#include "../components/ValveKnob.h"
#include "TaskImpl.h"

extern bool isAutomaticMode;
extern bool fromDashboard;
extern int levelFromDashboard;

class ManualTask : public TaskImpl {
   public:
    ManualTask(Valve* const valve, ValveKnob* const knob, LiquidCrystal_I2C* const monitor, const int period);
    void start();

   private:
    Valve* valve;
    ValveKnob* knob;
    LiquidCrystal_I2C* monitor;
};

#endif
