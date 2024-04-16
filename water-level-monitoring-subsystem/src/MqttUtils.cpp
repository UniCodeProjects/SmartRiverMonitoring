#include "../include/MqttUtils.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>

#define MQTT_CONNECTION_TIMEOUT_MILLIS 15000
#define MQTT_CONNECTION_DELTA_MILLIS 5000

static WiFiClient wifiClient;
static PubSubClient mqttClient(wifiClient);

void setupMqtt(const char* serverName, const uint16_t port, void (*callback)(char*, byte*, unsigned int)) {
    mqttClient.setServer(serverName, port);
    if (callback != NULL) {
        mqttClient.setCallback(callback);
    }
}

void connect(const char* subscribeTopic) {
    int timeElapsedMillis = 0;
    do {
        if (mqttClient.connect((String("river-water-level-monitor-client") + String(random(0xFFFF), HEX)).c_str())) {
            if (subscribeTopic != NULL) {
                mqttClient.subscribe(subscribeTopic);
            }
        } else {
            timeElapsedMillis += MQTT_CONNECTION_DELTA_MILLIS;
            delay(MQTT_CONNECTION_DELTA_MILLIS);
        }
    } while (!mqttClient.connected() && timeElapsedMillis < MQTT_CONNECTION_TIMEOUT_MILLIS);
}

bool publish(const char* topic, const char* payload, const bool retained) {
    return mqttClient.publish(topic, payload, retained);
}

bool keepConnectionAlive() {
    return mqttClient.loop();
}

bool isConnectedToMqttBroker() {
    return mqttClient.connected();
}
