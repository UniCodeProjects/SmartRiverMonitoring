#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "../include/components/ButtonImpl.h"
#include "../include/components/ValveImpl.h"
#include "../include/components/ValveKnobImpl.h"
#include "../include/components/PotentiometerImpl.h"
#include "../include/components/ServoMotorImpl.h"
#include "../include/scheduler/Scheduler.h"
#include "../include/task/SystemModeTask.h"
#include "../include/task/ModeSwitchTask.h"
#include "../include/task/MessageReceiverTask.h"

#define SERIAL_BAUD_RATE 9600
#define SERIAL_TIMEOUT_MILLIS 50

LiquidCrystal_I2C* monitor = new LiquidCrystal_I2C(0x27, 20, 4);
Button* const button = new ButtonImpl(2);
ValveKnob* const valveKnob = new ValveKnobImpl(new PotentiometerImpl(A0));
ServoMotor* const motor = new ServoMotorImpl(9);
Valve* const valve = new ValveImpl(motor);

Scheduler scheduler;

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.setTimeout(SERIAL_TIMEOUT_MILLIS); // Serial timeout in order to avoid overrun exception in AutomaticTask
  /*
   * This instruction is needed because Arduino resets when the server opens a serial connection with it.
   * In this way, data will be lost because the device is not ready to receive them.
   * This problem is worked around by letting Arduino send a ready sequence that the server waits for before writing.
   */
  Serial.println("ARDUINO_READY");
  monitor->init();
  monitor->backlight();
  monitor->setCursor(0, 0);
  monitor->print("Mode: AUTOMATIC");
  monitor->setCursor(3, 2);
  monitor->print("Valve opening");
  monitor->setCursor(5, 3);
  monitor->print("level: ");
  motor->on();
  scheduler.initialize(100);
  scheduler.addTask(new SystemModeTask(monitor, valveKnob, valve, 500));
  scheduler.addTask(new ModeSwitchTask(button, monitor, 100));
  scheduler.addTask(new MessageReceiverTask(100));
}

void loop() {
  scheduler.tick();
}
