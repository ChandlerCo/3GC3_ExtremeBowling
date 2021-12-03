#include "startMenu.h"

StartMenu::StartMenu(int windowX, int windowY) : Menu(windowX, windowY)
{
    level1 = Button(windowWidth*0.40, windowWidth*0.60, windowHeight*0.34, windowHeight*0.30, "Level 1");
    level2 = Button (windowWidth*0.40, windowWidth*0.60, windowHeight*0.44, windowHeight*0.40, "Level 2");
    level3 = Button(windowWidth*0.40, windowWidth*0.60, windowHeight*0.54, windowHeight*0.50, "Level 3");

    instructions = Button(windowWidth*0.40, windowWidth*0.60, windowHeight*0.77, windowHeight*0.73, "Instructions");
    quit = Button(windowWidth*0.45, windowWidth*0.55, windowHeight*0.83, windowHeight*0.79, "Quit");
}

void StartMenu::display()
{
    Menu::initMenu();
        
    glPushMatrix();

        glColor3f(1.0, 0.0, 0.0);
        void* font = GLUT_BITMAP_9_BY_15;

        // Game title
        string title = "WELCOME TO EXTREME BOWLING";
        Menu::centerText(title, font, windowHeight*0.20);

        // Underline the title
        string underlineTitle = "__________________________";
        Menu::centerText(underlineTitle, font, windowHeight*0.205);

        // Buttons
        level1.display();
        level2.display();
        level3.display();
        instructions.display();
        quit.display();

    glPopMatrix();

    Menu::endMenu();
}

bool StartMenu::level1Clicked(int x, int y)
{
    return level1.clicked(x, y);
}

bool StartMenu::level2Clicked(int x, int y)
{
    return level2.clicked(x, y);
}

bool StartMenu::level3Clicked(int x, int y)
{
    return level3.clicked(x, y);
}

bool StartMenu::instructionsClicked(int x, int y)
{
    return instructions.clicked(x, y);
}

bool StartMenu::quitClicked(int x, int y)
{
    return quit.clicked(x, y);
}