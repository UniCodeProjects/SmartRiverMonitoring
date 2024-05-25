#ifndef MESSAGE_RECEIVER_TASK_H
#define MESSAGE_RECEIVER_TASK_H

#include "TaskImpl.h"

extern bool isAutomaticMode;
extern bool fromDashboard;

/// @brief The task that reads the values from the serial line and that communicates to the other tasks the strings read.
class MessageReceiverTask : public TaskImpl {
   public:
    /// @brief Default constructor.
    /// @param period The task period.
    MessageReceiverTask(const int period);

    void start();
};

#endif
