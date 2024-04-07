#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

/// @brief The number of values that can be read by the potentiometer.
#define POTENTIOMETER_LEVELS 1024

/// @brief A generic potentiometer.
class Potentiometer {
   public:
    /// @brief Reads the current level from the potentiometer.
    /// @return The current potentiometer level.
    virtual int readValue() = 0;
};

#endif
