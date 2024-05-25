#ifndef MODE_SWITCH_TASK_H
#define MODE_SWITCH_TASK_H

#include <LiquidCrystal_I2C.h>

#include "../components/Button.h"
#include "TaskImpl.h"

extern String remoteControlState;

/// @brief The task that detects the events that trigger a change of the system mode.
class ModeSwitchTask : public TaskImpl {
   public:
    /// @brief Default constructor.
    /// @param button The button that the user has to press to enter in the LOCAL_MANUAL mode.
    /// @param monitor The user display.
    /// @param period The task period.
    ModeSwitchTask(Button* const button, LiquidCrystal_I2C* const monitor, const int period);

    void start();

   private:
    Button* button;
    LiquidCrystal_I2C* monitor;

    void printModeOnLCD();
};

#endif
