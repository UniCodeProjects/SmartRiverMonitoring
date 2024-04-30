#ifndef VALVE_KNOB_IMPL_H
#define VALVE_KNOB_IMPL_H

#include "Potentiometer.h"
#include "ValveKnob.h"

/// @brief Implementation of a ValveKnob.
class ValveKnobImpl : public ValveKnob {
   public:
    /// @brief Default constructor.
    /// @param potentiometer the potentiometer used to set the valve opening level.
    ValveKnobImpl(Potentiometer* potentiometer);

    int getValveOpeningLevel();

   private:
    Potentiometer* potentiometer;
};

#endif
