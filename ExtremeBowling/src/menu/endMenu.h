#ifndef ENDMENU_H
#define ENDMENU_H

#include "menu.h"

class EndMenu : public Menu {
    public:
        EndMenu(int windowX, int windowY);
        void display();
        bool backToStartClicked(int x, int y);
    private:
        Button backToStart;
};


#endif