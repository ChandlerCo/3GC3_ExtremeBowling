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
#include "PPM.h"
using namespace std;

class Menu {
    public:
        Menu(int windowX, int windowY);
        virtual void display();
        virtual void display(int lives, int currentTime); // for hudInterface
    protected:
        float windowWidth; // need to store window size as float for centering text
        float windowHeight;
        void centerText(string text, void* font, float y);
        void start2D();
        void end2D();
        void drawBackground();
};

#endif