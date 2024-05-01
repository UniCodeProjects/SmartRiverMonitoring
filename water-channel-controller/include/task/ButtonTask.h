#ifndef BUTTON_TASK_H
#define BUTTON_TASK_H

#include "../components/Button.h"
#include "TaskImpl.h"

class ButtonTask : public TaskImpl {
   public:
    ButtonTask(Button* const button, const int period);
    void start();

   private:
    Button* button;
};

#endif
