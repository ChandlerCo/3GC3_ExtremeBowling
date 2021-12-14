#include "endMenu.h"

EndMenu::EndMenu(int windowX, int windowY) : Menu(windowX, windowY) 
{
    backToStart = Button(windowWidth*0.40, windowWidth*0.60, windowHeight*0.83, windowHeight*0.79, "Back to Start");
}

void EndMenu::display() 
{
    start2D();

    drawBackground();

    glPushMatrix();

        glColor3f(1.0, 0.0, 0.0);
        void* font = GLUT_BITMAP_9_BY_15;

        // Game ended title
        Menu::centerText(message, font, windowHeight*0.20);

        // Underline the title
        string underlineTitle((int)message.size(), '_');
        Menu::centerText(underlineTitle, font, windowHeight*0.205);

        Menu::centerText(score, font, windowHeight*0.4);

        backToStart.display();

    glPopMatrix();

    end2D();
}

bool EndMenu::backToStartClicked(int x, int y) 
{
    return backToStart.clicked(x, y);
}

void EndMenu::setText(string message, int score)
{
    this->message = message;
    this->score = std::to_string(score);
}