#ifndef VALVE_KNOB_H
#define VALVE_KNOB_H

#define VALVE_KNOB_LEVELS 100

/// @brief Class that represents the knob used to control the river valve.
class ValveKnob {
   public:
    /// @brief Retrieves the current valve opening level from 0 (= closed) to 100 (= fully opened).
    /// @return The current valve opening level.
    virtual int getValveOpeningLevel() = 0;
};

#endif
