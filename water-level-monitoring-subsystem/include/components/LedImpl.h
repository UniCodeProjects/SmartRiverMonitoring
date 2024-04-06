#ifndef LED_IMPL_H
#define LED_IMPL_H

#include "Led.h"

/// @brief Implementation of a led.
class LedImpl : public Led {
   public:
    /// @brief Default constructor.
    /// @param pin the pin in which the led is plugged in.
    LedImpl(const int pin);

    void switchOn();
    void switchOff();

   private:
    int pin;
};

#endif
