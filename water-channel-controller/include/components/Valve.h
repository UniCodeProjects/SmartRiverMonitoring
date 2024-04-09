#ifndef VALVE_H
#define VALVE_H

/// @brief A generic river valve.
class Valve {
   public:
    /// @brief Sets the valve opening level with the provided one.
    /// @param level the valve opening level. Its value must be between 0 (included) and 100 (included).
    /// If its value is less than 0, the valve opening level will be set at its minimum.
    /// Otherwise, if its value is more than `ValveKnob::VALVE_KNOB_LEVELS` the valve will be fully opened.
    virtual void setLevel(int level) = 0;
};

#endif
