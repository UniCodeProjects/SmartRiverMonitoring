#include "../include/task/MessageReceiverTask.h"

#include <Arduino.h>

/// @brief The string that contains the information sent by the server regarding the REMOTE_CONTROL mode.
String remoteControlState;
/// @brief The string that contains the actual system state.
String receivedState;
/// @brief The variable that represents the valve opening level set by the dashboard user during the REMOTE_CONTROL mode.
int levelFromDashboard = 0;

MessageReceiverTask::MessageReceiverTask(const int period) : TaskImpl(period) {
}

void MessageReceiverTask::start() {
    if (isAutomaticMode || fromDashboard) {
        String messageReceived = Serial.readStringUntil('\n');
        if (messageReceived.startsWith("Remote")) {
            remoteControlState = messageReceived;
        } else if (messageReceived != "") {
            if (fromDashboard) {
                levelFromDashboard = messageReceived.toInt();
            } else {
                receivedState = messageReceived;
            }
        }
    }
}
