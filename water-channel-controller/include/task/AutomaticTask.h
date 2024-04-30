#ifndef AUTOMATIC_TASK_H
#define AUTOMATIC_TASK_H

#include <LiquidCrystal_I2C.h>

#include "../include/components/Valve.h"
#include "../include/components/ValveKnob.h"
#include "TaskImpl.h"

extern bool isAutomaticMode;

class AutomaticTask : public TaskImpl {
   public:
    AutomaticTask(LiquidCrystal_I2C* const monitor, Valve* const valve, const int period);
    void start();

   private:
    LiquidCrystal_I2C* monitor;
    Valve* valve;

    void printAndSetValveLevel(const int level);
};

#endif
