#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

/// @brief Connects to the WiFi with the provided ssid and password, if exists.
/// @param ssid the WiFi ssid.
/// @param password the WiFi password.
void connectToWiFi(const char* ssid, const char* password);

/// @brief Returns whether the device is connected to WiFi.
/// @return `true` if the device is connected to WiFi, `false` otherwise.
bool isConnectedToWiFi();

#endif
