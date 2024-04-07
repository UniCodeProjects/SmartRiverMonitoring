#ifndef POTENTIOMETER_IMPL_H
#define POTENTIOMETER_IMPL_H

#include "Potentiometer.h"

/// @brief The implementation of a potentiometer.
class PotentiometerImpl : public Potentiometer {
   public:
    /// @brief Default constructor.
    /// @param pin the pin in which the potentiometer is plugged in.
    PotentiometerImpl(const int pin);

    int readValue();

   private:
    int pin;
};

#endif
