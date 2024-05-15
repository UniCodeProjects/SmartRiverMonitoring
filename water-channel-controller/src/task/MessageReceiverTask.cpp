#include "../include/task/MessageReceiverTask.h"

#include <Arduino.h>

String remoteControlState;
String receivedState;
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
                levelFromDashboard = messageReceived == "0\n" ? 0 : messageReceived.toInt();
            } else {
                receivedState = messageReceived;
            }
        }
    }
}
