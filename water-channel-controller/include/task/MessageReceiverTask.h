#ifndef MESSAGE_RECEIVER_TASK_H
#define MESSAGE_RECEIVER_TASK_H

#include "TaskImpl.h"

extern bool isAutomaticMode;
extern bool fromDashboard;

class MessageReceiverTask : public TaskImpl {
   public:
    MessageReceiverTask(const int period);
    void start();
};

#endif
