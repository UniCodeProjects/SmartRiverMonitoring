#include "task/TaskImpl.h"


TaskImpl::TaskImpl(const int period) {
    this->period = period;
    this->timeElapsed = 0;
}

bool TaskImpl::canStart(const int schedulerPeriod) {
    timeElapsed += schedulerPeriod;
    if (timeElapsed >= period) {
        timeElapsed = 0;
        return true;
    } else {
        return false;
    }
}