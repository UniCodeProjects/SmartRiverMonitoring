#include <Arduino.h>
#include "../../include/components/SonarImpl.h"

#define AIR_ADIABATIC_INDEX 1.4
#define AIR_MOLAR_CONSTANT 287.057
#define ONE_SECOND_IN_MICROSECONDS 1000000.0
#define MAX_SONAR_TIMEOUT_MICROSECONDS 50000
#define CURRENT_TEMPERATURE 293.15

SonarImpl::SonarImpl(const int trigPin, const int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

double SonarImpl::getSoundSpeed(const double kelvinTemp) {
    return sqrt(AIR_ADIABATIC_INDEX * AIR_MOLAR_CONSTANT * kelvinTemp);
}

double SonarImpl::getDistance() {
    digitalWrite(this->trigPin, LOW),
    delayMicroseconds(5);
    digitalWrite(this->trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trigPin, LOW);

    // pulseIn() returns time in microseconds, so it is converted in seconds.
    double t = pulseIn(this->echoPin, HIGH, MAX_SONAR_TIMEOUT_MICROSECONDS) / (ONE_SECOND_IN_MICROSECONDS * 2);
    return getSoundSpeed(CURRENT_TEMPERATURE) * t;
}
