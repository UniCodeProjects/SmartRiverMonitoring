#include "../include/WifiUtils.h"
#include <WiFi.h>

#define WIFI_CONNECTION_TIMEOUT_MILLIS 5000
#define WIFI_CONNECTION_DELTA_MILLIS 500

void setupWifi(const char* ssid, const char* password) {
    // wl_status_t status;
    // WiFi.mode(WIFI_STA);
    // while (true) {
    //     Serial.println(status);
    //     if (status == WL_IDLE_STATUS) {
    //         // Serial.println("Connecting");
    //         continue;
    //     }
    //     if (status == WL_CONNECTED) {
    //         // Serial.println("Connected");
    //         break;
    //     }
    //     // Serial.println("Not connected, not connecting, beginning a wifi connection");
    //     status = WiFi.begin(ssid, password);
    // }
    int timeElapsedMillis = 0;
    WiFi.mode(WIFI_STA);
    while (WiFi.status() != WL_CONNECTED) {
        if (timeElapsedMillis >= WIFI_CONNECTION_TIMEOUT_MILLIS) {
            return;
        }
        WiFi.begin(ssid, password);
        delay(WIFI_CONNECTION_DELTA_MILLIS);
        timeElapsedMillis += WIFI_CONNECTION_DELTA_MILLIS;
    }
}

bool isConnectedToWiFi() {
    return WiFi.status() == WL_CONNECTED;
}

bool isConnectingToWiFi() {
    return WiFi.status() == WL_IDLE_STATUS;
}
