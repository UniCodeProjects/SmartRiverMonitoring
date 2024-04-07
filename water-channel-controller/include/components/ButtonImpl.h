#ifndef BUTTON_IMPL_H
#define BUTTON_IMPL_H

#include "Button.h"

/// @brief Implementation of a button.
class ButtonImpl : public Button {
   public:
    /// @brief Default constructor.
    /// @param pin the pin in which the button is plugged in.
    ButtonImpl(const int pin);

    bool isPressed();

   private:
    int pin;
};

#endif
