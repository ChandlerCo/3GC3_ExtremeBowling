#include "instructionsMenu.h"

InstructionsMenu::InstructionsMenu(int windowX, int windowY) : Menu(windowX, windowY)
{
    back = Button(windowWidth*0.45, windowWidth*0.55, windowHeight*0.83, windowHeight*0.79, "Back");
}

void InstructionsMenu::display()
{
    Menu::initMenu();

    glPushMatrix();

        glColor3f(1.0, 0.0, 0.0);
        void* font = GLUT_BITMAP_9_BY_15;

        // Instructions 
        string title = "Instructions";
        Menu::centerText(title, font, windowHeight*0.20);

        // Underline the title
        string underlineTitle = "____________";
        Menu::centerText(underlineTitle, font, windowHeight*0.205);

        back.display();

    glPopMatrix();

    Menu::endMenu();
}

bool InstructionsMenu::backClicked(int x, int y)
{
    return back.clicked(x, y);
}