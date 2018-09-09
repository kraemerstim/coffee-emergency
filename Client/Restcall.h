#ifndef RESTCALL_H
#define RESTCALL_H

#include "Button.h"

class Restcall {
    public:
        static int sendButtonPressed(int button_id);
        static bool initializeButton(Button* button);
};

#endif
