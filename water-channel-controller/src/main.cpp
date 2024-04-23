#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "../include/components/ButtonImpl.h"
#include "../include/components/ValveImpl.h"
#include "../include/components/ValveKnobImpl.h"
#include "../include/components/PotentiometerImpl.h"
#include "../include/components/ServoMotorImpl.h"

#define SERIAL_BAUD_RATE 9600
// #define VALVE_SUBSYSTEM_TEST
// #define BUTTON_TEST

LiquidCrystal_I2C* lcd = new LiquidCrystal_I2C(0x27, 20, 4);
Button* const button = new ButtonImpl(2);
ValveKnob* const valveKnob = new ValveKnobImpl(new PotentiometerImpl(A0));
ServoMotor* const motor = new ServoMotorImpl(9);
Valve* const valve = new ValveImpl(motor);

bool isButtonPressed = false;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  #ifdef VALVE_SUBSYSTEM_TEST
  lcd->init();
  lcd->backlight();
  motor->on();
  #endif
}

void loop() {
  #ifdef VALVE_SUBSYSTEM_TEST
  lcd->clear();
  lcd->setCursor(3, 1);
  const int level = valveKnob->getValveOpeningLevel();
  lcd->print("Valve level: ");
  lcd->print(level);
  valve->setLevel(level);
  delay(100);
  #endif

  #ifdef BUTTON_TEST
  bool actualButtonStatus = button->isPressed();
  if (actualButtonStatus != isButtonPressed) {
    isButtonPressed = actualButtonStatus;
    Serial.println(isButtonPressed ? "Pressed" : "Not pressed");
  }
  #endif
}
