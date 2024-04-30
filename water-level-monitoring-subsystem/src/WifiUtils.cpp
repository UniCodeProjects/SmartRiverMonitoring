#include "../include/WifiUtils.h"
#include <WiFi.h>

#define MAX_ATTEMPTS 10
#define WIFI_CONNECTION_DELTA_MILLIS 500

static bool isModeSet = false;

void connectToWiFi(const char* ssid, const char* password) {
    int attempts = 0;
    if (!isModeSet) {
        WiFi.mode(WIFI_STA);
        isModeSet = true;
    }
    while (!isConnectedToWiFi() && attempts < MAX_ATTEMPTS) {
        WiFi.begin(ssid, password);
        delay(WIFI_CONNECTION_DELTA_MILLIS);
        attempts++;
    }
}

bool isConnectedToWiFi() {
    return WiFi.status() == WL_CONNECTED;
}
