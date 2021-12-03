#ifndef STARTMENU_H
#define STARTMENU_H

#include "menu.h"

class StartMenu : public Menu {
    public:
        StartMenu(int windowX, int windowY);
        void display();
        bool level1Clicked(int x, int y);
        bool level2Clicked(int x, int y);
        bool level3Clicked(int x, int y);
        bool instructionsClicked(int x, int y);
        bool quitClicked(int x, int y);
    private:
        Button level1;
        Button level2;
        Button level3;
        Button instructions;
        Button quit;
};

#endif