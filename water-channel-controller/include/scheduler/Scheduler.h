#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task/Task.h"

/// @brief The maximum number of tasks allowed by the scheduler.
#define MAX_TASKS 10

/// @brief The class that launches all the tasks.
class Scheduler {
   public:

    /// @brief Initialises the scheduler with the provided period.
    /// @param period The period of the scheduler.
    void initialize(const int period);

    /// @brief Adds a new task to the scheduler.
    /// @param task The task to be scheduled.
    /// @return true if the operation is successful, false otherwise.
    virtual bool addTask(Task* const task);

    /**
     * @brief Every time the scheduler's period elapses, this method attempts
     * to execute all the tasks registered in the scheduler.
     */
    virtual void tick();

   private:
    int period;
    int actualTasksNum;
    Task* tasks[MAX_TASKS];
};

#endif
