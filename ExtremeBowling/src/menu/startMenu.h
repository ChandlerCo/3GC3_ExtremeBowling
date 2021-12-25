#ifndef STARTMENU_H
#define STARTMENU_H

#include "menu.h"

class StartMenu : public Menu {
    public:
        StartMenu(int windowX, int windowY);
        void display();
        bool level1Clicked(float x, float y);
        bool level2Clicked(float x, float y);
        bool level3Clicked(float x, float y);
        bool instructionsClicked(float x, float y);
        bool quitClicked(float x, float y);
    private:
        int level1HighScore;
        int level2HighScore;
        int level3HighScore;
        Button level1;
        Button level2;
        Button level3;
        Button instructions;
        Button quit;
};

#endif