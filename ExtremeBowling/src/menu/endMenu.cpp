#include "endMenu.h"

EndMenu::EndMenu(int windowX, int windowY) : Menu(windowX, windowY) {}

void EndMenu::display() 
{
    Menu::initMenu();

    glPushMatrix();

        glColor3f(1.0, 0.0, 0.0);
        void* font = GLUT_BITMAP_9_BY_15;

        // Game ended title
        string title = "GAME OVER";
        Menu::centerText(title, font, windowHeight*0.20);

        // Underline the title
        string underlineTitle = "____________";
        Menu::centerText(underlineTitle, font, windowHeight*0.205);

    glPopMatrix();

    Menu::endMenu();
}