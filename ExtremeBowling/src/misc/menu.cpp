#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <iostream>
#include "menu.h"

Menu::Menu() {}

void Menu::display(int windowWidth, int windowHeight)
{
    // we will be switching to 2d projection here
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); // save projection matrix state
        glLoadIdentity(); // reset projection matrix
        gluOrtho2D(0, 1, 1, 0);
        //gluOrtho2D(0, windowWidth, windowHeight, 0); // set 2d projection matrix
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); // save modelview matrix state
        glDisable(GL_CULL_FACE);
        glClear(GL_DEPTH_BUFFER_BIT);
            glLoadIdentity(); // reset modelview matrix state
            // draw menu here
            glDisable(GL_LIGHTING);
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_QUADS);
                // glVertex2f(10.0, 10.0);
                // glVertex2f(windowWidth - 10.0, 10.0);
                // glVertex2f(windowWidth - 10.0, windowHeight - 10.0);
                // glVertex2f(10.0, windowHeight - 10.0);
                glVertex2f(0.15, 0.15);
                glVertex2f(0.85, 0.15);
                glVertex2f(0.85, 0.85);
                glVertex2f(0.15, 0.85);
            glEnd();
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