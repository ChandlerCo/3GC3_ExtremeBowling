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



#ifndef MAIN
#define MAIN

#include <chrono> // for more accurate time checking
#include <map>
#include <random>

// #include "ioFuncs.h"
#include "characters/ball.h"
#include "characters/boomba.h"
#include "characters/sweeper.h"
#include "misc/camera.h"
#include "misc/level.h"

#include "menu/menu.h"
#include "menu/startMenu.h"
#include "menu/instructionsMenu.h"
#include "menu/pauseMenu.h"

using namespace std;
using namespace std::chrono;

int refreshRate;
int windowX = 800; // need to initialize this first here for menu parameters
int windowY = 800;

bool pauseStatus;
bool startStatus;
bool instructionsStatus;

bool showFPS;

int frameTime;
int frameCount;
int time_past;

int prevX;
int prevY;

Camera ballCam(10);

StartMenu startMenu(windowX, windowY);
InstructionsMenu instructionsMenu(windowX, windowY);
PauseMenu pauseMenu(windowX, windowY);

Level currentLevel("src/levels/map1.json");
// Level level1;

void keyboard(unsigned char key, int _x, int _y) {
    // if (key == 'q') {
    //     exit(0);
    // }

    if (key == '`'){
        showFPS = !showFPS;
    }

    if (key  == ' ' && !startStatus){
        pauseStatus = !pauseStatus;
    }
}

void mouse(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (startStatus) {
            if (startMenu.instructionsClicked(x, y)) { // switch to instructions menu
                startStatus = false;
                instructionsStatus = true;
            } else if (startMenu.quitClicked(x, y)) { // quit program
                exit(0);
            } else if (startMenu.level1Clicked(x, y)) {
                startStatus = false;
                //instructionsStatus = false;
                pauseStatus = false;
            }
        } else if (instructionsStatus) {
            if (instructionsMenu.backClicked(x, y)) {
                instructionsStatus = false;
                startStatus = true;
            }
        }
    }

    glutPostRedisplay();
    //mouse left click-jump
}

void motion(int x, int y){
    if(x - prevX > 50 || y - prevY > 50){
        prevX = x;
        prevY = y;
    }
    if(!pauseStatus){
        ballCam.orbitHorizontal(x - prevX);
        ballCam.orbitVertical(y - prevY);

        prevX = x;
        prevY = y;
    }
    if (x > windowX || x < 0 || y > windowY || y < 0) {
        pauseStatus = true; // if mouse outside window, game pauses
    }  
}

void passive(int x, int y){
    if(x - prevX > 50 || y - prevY > 50){
        prevX = x;
        prevY = y;
    }
    if(!pauseStatus){
        ballCam.orbitHorizontal(x - prevX);
        ballCam.orbitVertical(y - prevY);

        prevX = x;
        prevY = y;
    }
    if (x > windowX || x < 0 || y > windowY || y < 0) {
        pauseStatus = true; // if mouse outside window, game pauses
    }
}


void special(int key, int x, int y){
    if(!pauseStatus){
        if (key == GLUT_KEY_UP){
            currentLevel.ballMove(ballCam.getForward());
        }
        if (key == GLUT_KEY_DOWN){
            currentLevel.ballMove(ballCam.getBackward());
        }
        if (key == GLUT_KEY_RIGHT){
            currentLevel.ballMove(ballCam.getRight());
        }
        if (key == GLUT_KEY_LEFT){
            currentLevel.ballMove(ballCam.getLeft());
        }

    }
    glutPostRedisplay();
}

void FPS (int val){
    int time_current = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int d_time = time_current - time_past;
    //frameTime = d_time;
    time_past = time_current; 

    if(!pauseStatus){
        currentLevel.runLevel(d_time);
        ballCam.changePosition(currentLevel.getBallX(),currentLevel.getBallY(),currentLevel.getBallZ());
    }

    glutPostRedisplay();


    d_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - time_past;
    
    frameCount += 1;
    if(d_time > 1000 / refreshRate){
        glutTimerFunc(1, FPS, 0);
        
    } else {
        glutTimerFunc(1000 / refreshRate, FPS, 0);
    }
}


void displayFPS(){

    if (displayFPS){
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, windowX, 0.0, windowY);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glColor3f(0.0, 1.0, 0.0);
        glRasterPos2i(10, windowY - 15);

        string s = to_string(1000 / (frameTime+1));
        void * font = GLUT_BITMAP_9_BY_15;
        for (string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(
        10,10,10, // ballCam.getX(),    ballCam.getY(),    ballCam.getZ(),
        0,0,0,//currentLevel.getBallX(),currentLevel.getBallY(),currentLevel.getBallZ(),
        0,1,0
    );


    // if (startStatus) {
    //     pauseStatus = true; // prevent movement of other things
    //     startMenu.display();
    // } else if (instructionsStatus) {
    //     pauseStatus = true; // prevent movement of other things
    //     instructionsMenu.display();
    // } else {
    //     //graphics objects here
    //     glDisable(GL_LIGHTING);
    //     glColor3f(1, 0, 1);
    //     glPushMatrix();
    //     //
    //     glutSolidCube(1);

    //     glPopMatrix();
        
    //     if (pauseStatus) {
    //         pauseMenu.display();
    //     }
    //     displayFPS();
    // }
    currentLevel.displayAssets();
    glFlush();
    glutSwapBuffers();

}

void init(){

    windowX = 800;
    windowY = 800;
    refreshRate = 120;
    frameTime = 0;
    showFPS = true;
    startStatus = true;

    time_past = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void handleReshape(int w, int h) {
    windowX = w;
    windowY = h;
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glShadeModel(GL_SMOOTH);
    
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, windowX/windowY, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


/* main function - program entry point */
int main(int argc, char** argv)
{
    init();

    glutInit(&argc, argv);        //starts up GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize(windowX, windowY);
    glutInitWindowPosition(300,300);

    glutCreateWindow("Extreme Bowling");    //creates the window

    

    //callbacks
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passive);
    glutSpecialFunc(special);
    glutReshapeFunc(handleReshape);
    
    glutDisplayFunc(display);    //registers "display" as the display callback function


    glutTimerFunc(1000/refreshRate,FPS, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glutMainLoop();

    return 0;                    
}





#endif