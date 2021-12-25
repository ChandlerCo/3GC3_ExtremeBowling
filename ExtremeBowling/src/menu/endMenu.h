#ifndef ENDMENU_H
#define ENDMENU_H

#include "menu.h"

class EndMenu : public Menu {
    public:
        EndMenu(int windowX, int windowY);
        void display();
        void setText(string message, int score);
        bool backToStartClicked(float x, float y);
    private:
        Button backToStart;
        string message;
        string score;
};


#endif