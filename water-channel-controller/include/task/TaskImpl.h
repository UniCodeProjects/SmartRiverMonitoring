#ifndef TASK_IMPL_H
#define TASK_IMPL_H

#include "Task.h"

/// @brief Generic task implementation.
class TaskImpl : public Task {
   public:
    /// @brief TaskImpl's default constructor.
    /// @param period the period of the task.
    TaskImpl(const int period);

    /// @brief Starts the task.
    virtual void start() = 0;

    /// @brief Retrieves true if the task can start, false otherwise.
    /// @param schedulerPeriod the period of the scheduler that manages this task.
    /// @return true if the task's period is elapsed, and so the task has to start, false otherwise.
    virtual bool canStart(const int schedulerPeriod);

   protected:
    /// @brief The task's period.
    int period;

   private:
    int timeElapsed;
};

#endif
