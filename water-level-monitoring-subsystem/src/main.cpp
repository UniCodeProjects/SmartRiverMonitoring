#include <Arduino.h>
#include "SPIFFS.h"
#include "components/Sonar.h"
#include "components/SonarImpl.h"

#include "../include/components/LedImpl.h"
#include "../include/WifiUtils.h"
#include "../include/MqttUtils.h"

#define SERIAL_BAUD_RATE 115200
#define SAMPLE_PERIOD_TOPIC "sample-period"
#define MQTT_BROKER "broker.mqtt-dashboard.com"

char* wifi_ssid;
char* wifi_password;
Led* const redLed = new LedImpl(1);
Led* const greenLed = new LedImpl(2);
Sonar* const sonar = new SonarImpl(4, 5);
bool connectionWorks;
String receivedMessage;

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

void onMessageReceived(char* topic, byte* payload, unsigned int length) {
#ifdef DEBUG
    Serial.println("Message arrived on topic: " + String(topic));
    Serial.print("Message length:");
    Serial.println(length);
#endif
    receivedMessage = "";
    for (int i = 0; i < length; i++) {
        receivedMessage += String((char) payload[i]);
    }
}

String getMessage() {
    if (!receivedMessage.endsWith("\n")) {
        return "";
    }
    return receivedMessage;
}

void reconnectionTask(void* parameters) {
    while (true) {
        if (!connectionWorks) {
            connectToWiFi(wifi_ssid, wifi_password);
            connect(SAMPLE_PERIOD_TOPIC);
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
    setupMqtt(MQTT_BROKER, MQTT_PORT, onMessageReceived);
    connect(SAMPLE_PERIOD_TOPIC);
    connectionWorks = isConnectedToWiFi() && isConnectedToMqttBroker();
    xTaskCreate(ledTask, "ledTask", 1000, NULL, 1, NULL);
    xTaskCreate(keepConnectionTask, "keepConnectionTask", 10000, NULL, 3, NULL);
    xTaskCreate(reconnectionTask, "reconnectionTask", 10000, NULL, 1, NULL);
    // xTaskCreate(waterSamplingTask, "waterSamplingTask", 10000, NULL, 1, NULL);

    // TODO: add explaination.
    // while (getMessage().isEmpty());
    // String msg = getMessage();
    // msg.remove(msg.length() - 1);
    // uint32_t samplingPeriod = msg.toInt();
    // Serial.println(samplingPeriod + 1);
}

void loop() {
}
