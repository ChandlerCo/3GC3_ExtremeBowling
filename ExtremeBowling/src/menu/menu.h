#ifndef MENU_H
#define MENU_H

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

#include <string>
#include "button.h"
using namespace std;

class Menu {
    public:
        Menu(int windowX, int windowY);
        virtual void display();
    protected:
        float windowWidth; // need to store window size as float for centering text
        float windowHeight;
        void centerText(string text, void* font, float y);
        void initMenu();
        void endMenu();
};

#endif