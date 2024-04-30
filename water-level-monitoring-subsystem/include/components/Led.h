#ifndef LED_H
#define LED_H

/// @brief Class that represents a generic led.
class Led {
   public:
    /// @brief Turns on the led.
    virtual void switchOn() = 0;

    /// @brief Turns off the led.
    virtual void switchOff() = 0;
};

#endif
