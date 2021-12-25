#ifndef INSTRUCTIONSMENU_H
#define INSTRUCTIONSMENU_H

#include "menu.h"

class InstructionsMenu : public Menu {
    public:
        InstructionsMenu(int windowX, int windowY);
        void display();
        bool backClicked(float x, float y);
    private: 
        Button back;
};

#endif