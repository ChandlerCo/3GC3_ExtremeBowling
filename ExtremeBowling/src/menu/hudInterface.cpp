#include "hudInterface.h"

HudInterface::HudInterface(int windowX, int windowY) : Menu(windowX, windowY) {}

void HudInterface::display(int lives, int currentTime)
{
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

            glPushMatrix();

                glColor3f(0.95, 0.95, 0.95);
                glBegin(GL_QUADS);
                    glVertex2f(windowWidth*0.80, windowHeight*0.90);
                    glVertex2f(windowWidth, windowHeight*0.90);
                    glVertex2f(windowWidth, windowHeight);
                    glVertex2f(windowWidth*0.80, windowHeight);
                glEnd();
            
            glPopMatrix();

            glPushMatrix();

                glColor3f(1.0, 0.0, 0.0);
                void* font = GLUT_BITMAP_9_BY_15;
                string livesText = "Lives left: " + std::to_string(lives);
                float livesTextWidth = 0;
                for (int i = 0; i < (int) livesText.size(); i++) {
                    livesTextWidth += glutBitmapWidth(font, livesText[i]);
                }
                glRasterPos2f(windowWidth*0.90 - livesTextWidth / 2.0, windowHeight*0.935);
                for (char& c : livesText) {
                    glutBitmapCharacter(font, c);
                }
                string currentTimeText = "Time: " + std::to_string(currentTime/1000) + " seconds";
                float currentTimeTextWidth = 0;
                for (int i = 0; i < (int) currentTimeText.size(); i++) {
                    currentTimeTextWidth += glutBitmapWidth(font, currentTimeText[i]);
                }
                glRasterPos2f(windowWidth*0.90 - currentTimeTextWidth / 2.0, windowHeight*0.975);
                for (char& c : currentTimeText) {
                    glutBitmapCharacter(font, c);
                }

            glPopMatrix();


            glMatrixMode(GL_PROJECTION);
        glPopMatrix(); // retrieve projection matrix state
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix(); // retrieve modelview matrix state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_LIGHTING);
}