#ifndef MQTT_UTILS_H
#define MQTT_UTILS_H

#include <Arduino.h>

#define MQTT_PORT 1883

/// @brief Sets up the environment for the mqtt connection.
/// @param serverName the name of the mqtt broker.
/// @param port the port to connect to.
/// @param callback a pointer to a function called when a message arrives on the subscribed topic. If it is `NULL` the callback is not set.
void setupMqtt(const char* serverName, const uint16_t port, void (*callback)(char*, byte*, unsigned int));

/// @brief Attempts to establish a connection with the broker. If the connection is successful, subscribes the device to the provided topic.
/// @param subscribeTopic The topic to subscribe to. If it is `NULL`, the subscription will not be done.
void connect(const char* subscribeTopic);

/// @brief Publishes a message on the broker for the provided topic.
/// @param topic the topic to send the message to.
/// @param payload the message content.
/// @param retained `true` if the server should keep the message until it is read from any device subscripted to the provided topic, `false` otherwise.
/// @return `true` if the operation is successful, `false` otherwise.
bool publish(const char* topic, const char* payload, const bool retained);

/// @brief Keeps the connection with the server. This function must be called regularly, otherwise the connection will be dropped.
/// @return `true` if the connection is still maintained, `false` otherwise.
bool keepConnectionAlive();

/// @brief Returns if the mqtt connection with the provided server is alive or not.
/// @return `true` if the client is connected to the mqtt broker, `false` otherwise.
bool isConnectedToMqttBroker();

#endif
