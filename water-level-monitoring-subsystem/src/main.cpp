#include <Arduino.h>
#include "components/Sonar.h"
#include "components/SonarImpl.h"

#include "../include/components/LedImpl.h"
#include "../include/WifiUtils.h"
#include "../include/MqttUtils.h"

#define SERIAL_BAUD_RATE 115200
#define SUBSCRIBE_TOPIC "sampleTopic"
#define WIFI_SSID "" // TODO: set the ssid with the proper one
#define WIFI_PASSWORD "" // TODO: set the password with the proper one
#define MQTT_BROKER "broker.mqtt-dashboard.com"

Led* const redLed = new LedImpl(1);
Led* const greenLed = new LedImpl(2);
Sonar* const sonar = new SonarImpl(4, 5);
bool connectionWorks;

void keepConnectionTask(void* parameters) {
    while (true) {
        connectionWorks = keepConnectionAlive();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void ledTask(void* parameters) {
    while (true) {
        if (connectionWorks) {
            redLed->switchOff();
            greenLed->switchOn();
        } else {
            redLed->switchOn();
            greenLed->switchOff();
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
#ifdef DEBUG
    Serial.println("Message arrived on topic: " + String(topic));
    Serial.print("Message length:");
    Serial.println(length);
#endif
    String msg;
    for (int i = 0; i < length; i++) {
        msg += String((char) payload[i]);
    }
    Serial.println(msg);
}

void reconnectionTask(void* parameters) {
    while (true) {
        if (!connectionWorks) {
            connectToWiFi(WIFI_SSID, WIFI_PASSWORD);
            connect(SUBSCRIBE_TOPIC);
            connectionWorks = isConnectedToWiFi() && isConnectedToMqttBroker();
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void waterSamplingTask(void* parameters) {
    while (true) {
        Serial.println(String(sonar->getDistance()));
        delay(100);
    }
}

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    randomSeed(analogRead(4));

    connectToWiFi(WIFI_SSID, WIFI_PASSWORD);
    setupMqtt(MQTT_BROKER, MQTT_PORT, callback);
    connect(SUBSCRIBE_TOPIC);
    connectionWorks = isConnectedToWiFi() && isConnectedToMqttBroker();
    xTaskCreate(ledTask, "ledTask", 1000, NULL, 1, NULL);
    xTaskCreate(keepConnectionTask, "keepConnectionTask", 10000, NULL, 3, NULL);
    xTaskCreate(reconnectionTask, "reconnectionTask", 10000, NULL, 1, NULL);
    // xTaskCreate(waterSamplingTask, "waterSamplingTask", 10000, NULL, 1, NULL);
}

void loop() {
    publish(SUBSCRIBE_TOPIC, "Hi", false);
    delay(10000);
}
