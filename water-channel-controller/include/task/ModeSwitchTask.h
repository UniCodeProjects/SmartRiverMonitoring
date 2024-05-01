#ifndef MODE_SWITCH_TASK_H
#define MODE_SWITCH_TASK_H

#include <LiquidCrystal_I2C.h>

#include "../components/Button.h"
#include "TaskImpl.h"

class ModeSwitchTask : public TaskImpl {
   public:
    ModeSwitchTask(Button* const button, LiquidCrystal_I2C* const monitor, const int period);
    void start();

   private:
    Button* button;
    LiquidCrystal_I2C* monitor;
};

#endif
