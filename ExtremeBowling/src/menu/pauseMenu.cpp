#include "pauseMenu.h"

PauseMenu::PauseMenu(int windowX, int windowY) : Menu(windowX, windowY) {}

void PauseMenu::display()
{
    Menu::initMenu();

    glPushMatrix();

        glColor3f(1.0, 0.0, 0.0);
        void* font = GLUT_BITMAP_9_BY_15;

        // Game title
        string title = "EXTREME BOWLING";
        Menu::centerText(title, font, windowHeight*0.20);

        // Underline the title
        string underlineTitle = "_______________";
        centerText(underlineTitle, font, windowHeight*0.205);

        // Unpause game text 
        string unpause = "Press space to unpause game.";
        Menu::centerText(unpause, font, windowHeight*0.80);
        
    glPopMatrix();

    Menu::endMenu();
}