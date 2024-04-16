#ifndef MQTT_UTILS_H
#define MQTT_UTILS_H

#include <Arduino.h>

#define MQTT_PORT 1883

void setupMqtt(const char* serverName, const uint16_t port, void (*callback)(char*, byte*, unsigned int));
void connect(const char* subscribeTopic);
bool publish(const char* topic, const char* payload, const bool retained);
bool keepConnectionAlive();
bool isConnectedToMqttBroker();

#endif
