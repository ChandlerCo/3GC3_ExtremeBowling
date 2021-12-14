#include "instructionsMenu.h"

InstructionsMenu::InstructionsMenu(int windowX, int windowY) : Menu(windowX, windowY)
{
    back = Button(windowWidth*0.45, windowWidth*0.55, windowHeight*0.83, windowHeight*0.79, "Back");
}

void InstructionsMenu::display()
{
    start2D();

    drawBackground();

    glPushMatrix();

        glColor3f(1.0, 0.0, 0.0);
        void* font = GLUT_BITMAP_9_BY_15;

        // Instructions title
        string title = "INSTRUCTIONS";
        Menu::centerText(title, font, windowHeight*0.20);

        // Underline the title
        string underlineTitle = "____________";
        Menu::centerText(underlineTitle, font, windowHeight*0.205);

        /* Game instructions */
        // Space to pause
        string space = "Press space to pause the game.";
        Menu::centerText(space, font, windowHeight*0.40);

        // Move mouse to move camera 
        string camera = "Look around by moving the mouse.";
        Menu::centerText(camera, font, windowHeight*0.45);

        // Arrow keys to move
        string arrowKeys = "Use arrow keys to move the ball.";
        Menu::centerText(arrowKeys, font, windowHeight*0.50);

        // Left click to jump
        string leftClick = "Left click to make the ball jump.";
        Menu::centerText(leftClick, font, windowHeight*0.55);

        back.display();

    glPopMatrix();

    end2D();
}

bool InstructionsMenu::backClicked(int x, int y)
{
    return back.clicked(x, y);
}