#include "scheduler/Scheduler.h"

#include <TimerOne.h>

#define ONE_MILLISEC_IN_MICROSEC 1000l

/**
 * @brief This variable is set by the Timer1 when the scheduler's period elapses.
 * It indicates that the scheduler has to try to launch all the tasks registered in it.
 */
volatile bool canLaunchTasks;

/// @brief Timer1 interrupt handler.
void reachPeriod() {
    canLaunchTasks = true;
}

void Scheduler::initialize(const int period) {
    this->period = period;
    canLaunchTasks = false;
    actualTasksNum = 0;
    Timer1.initialize(ONE_MILLISEC_IN_MICROSEC * this->period);
    Timer1.attachInterrupt(reachPeriod);
}

bool Scheduler::addTask(Task* const task) {
    if (actualTasksNum < MAX_TASKS - 1) {
        tasks[actualTasksNum] = task;
        actualTasksNum++;
        return true;
    } else {
        return false;
    }
}

void Scheduler::tick() {
    if (canLaunchTasks) {
        canLaunchTasks = false;
        for (int i = 0; i < actualTasksNum; i++) {
            if (tasks[i]->canStart(period)) {
                tasks[i]->start();
            }
        }
    }
}
