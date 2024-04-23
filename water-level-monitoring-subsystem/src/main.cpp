#include <Arduino.h>
#include "SPIFFS.h"
#include "components/Sonar.h"
#include "components/SonarImpl.h"

#include "../include/components/LedImpl.h"
#include "../include/WifiUtils.h"
#include "../include/MqttUtils.h"

#define SERIAL_BAUD_RATE 115200
#define SUBSCRIBE_TOPIC "sampleTopic"
#define MQTT_BROKER "broker.mqtt-dashboard.com"

char* wifi_ssid;
char* wifi_password;
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
            connectToWiFi(wifi_ssid, wifi_password);
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

void readEnv() {
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    File file = SPIFFS.open("/.env");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }
    while (file.available()) {
        String line = file.readStringUntil('\n');
        int indexOfSeparator = line.indexOf('=');
        String var_name = line.substring(0, indexOfSeparator);
        String var_value = line.substring(indexOfSeparator + 1, line.length());
        if (var_name == "WIFI_SSID") {
            wifi_ssid = (char*)malloc(sizeof(char) * var_value.length() + 1);
            var_value.toCharArray(wifi_ssid, var_value.length() + 1);
        } else {
            wifi_password = (char*)malloc(sizeof(char) * var_value.length() + 1);
            var_value.toCharArray(wifi_password, var_value.length() + 1);
        }
    }
    file.close();
}

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    randomSeed(analogRead(4));

    readEnv();
    connectToWiFi(wifi_ssid, wifi_password);
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
