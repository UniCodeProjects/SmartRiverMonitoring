#ifndef TASK_H
#define TASK_H

/// @brief A generic task.
class Task {
   public:
    /// @brief Starts the task.
    virtual void start() = 0;

    /// @brief Retrieves true if the task can start, false otherwise.
    /// @param schedulerPeriod the period of the scheduler that manages this task.
    /// @return true if the task's period is elapsed, and so the task has to start, false otherwise.
    virtual bool canStart(const int schedulerPeriod) = 0;
};

#endif
