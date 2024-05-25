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

/// @brief The main task of the system. Manages the valve and its opening level.
class SystemModeTask : public TaskImpl {
   public:
    /// @brief Default constructor.
    /// @param monitor The user display.
    /// @param knob The knob that manages the valve opening level in the LOCAL_MANUAL mode.
    /// @param valve The valve.
    /// @param period The task period.
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
