//#include <iostream>
#include "menu.h"

Menu::Menu() {}

void Menu::display(int windowX, int windowY)
{
    this->windowWidth = windowX;
    this->windowHeight = windowY;

    // we will be switching to 2d projection here
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // save projection matrix state
        glLoadIdentity(); // reset projection matrix
        gluOrtho2D(0, windowWidth, windowHeight, 0); // set 2d projection matrix
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); // save modelview matrix state
        glDisable(GL_CULL_FACE);
        //glClear(GL_DEPTH_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
            glLoadIdentity(); // reset modelview matrix state
            glDisable(GL_LIGHTING);
            // draw menu background
            glPushMatrix();
                glColor3f(0.95, 0.95, 0.95);
                glBegin(GL_QUADS);
                    glVertex2f(windowWidth*0.15, windowHeight*0.15);
                    glVertex2f(windowWidth*0.85, windowHeight*0.15);
                    glVertex2f(windowWidth*0.85, windowHeight*0.85);
                    glVertex2f(windowWidth*0.15, windowHeight*0.85);
                glEnd();
            glPopMatrix();
            // draw text onto background
            glPushMatrix();
                glColor3f(1.0, 0.0, 0.0);
                void* font = GLUT_BITMAP_9_BY_15;

                // Game title
                string title = "EXTREME BOWLING";
                centerText(title, font, windowHeight*0.20);

                // Underline the title
                string underlineTitle = "_______________";
                centerText(underlineTitle, font, windowHeight*0.205);

                // Unpause game text 
                string unpause = "Press space to unpause game.";
                centerText(unpause, font, windowHeight*0.80);
                
            glPopMatrix();
            // switch back to 3d projection
            glMatrixMode(GL_PROJECTION);
        glPopMatrix(); // retrieve projection matrix state
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix(); // retrieve modelview matrix state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_LIGHTING);
}

// Will render and center text
void Menu::centerText(string text, void* font, float y)
{
    float textWidth = 0;
    for (int i = 0; i < text.size(); i++) {
        textWidth += glutBitmapWidth(font, text[i]);
    }
    glRasterPos2f(windowWidth / 2.0 - textWidth / 2.0, y);
    for (char& c : text) {
        glutBitmapCharacter(font, c);
    }
}