#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

void setupWifi(const char* ssid, const char* password);
bool isConnectedToWiFi();
bool isConnectingToWiFi();

#endif
