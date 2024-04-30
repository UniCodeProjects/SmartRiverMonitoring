#include "../include/task/ButtonTask.h"

ButtonTask::ButtonTask(Button* const button, const int period) : TaskImpl(period) {
    this->button = button;
}

void ButtonTask::start() {
    if (button->isPressed()) {
        isAutomaticMode = !isAutomaticMode;
    }
}
