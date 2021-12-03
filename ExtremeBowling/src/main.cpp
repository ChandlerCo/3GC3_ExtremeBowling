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

#include "characters/ball.h"
#include "characters/boomba.h"
#include "characters/sweeper.h"
#include "misc/camera.h"
#include "misc/menu.h"
#include "misc/level.h"

using namespace std;
using namespace std::chrono;

int refreshRate;
int frameTime;
int frameCount;
int windowX;
int windowY;
bool pauseStatus;


Ball ball(0, 10, 0, 8);
Camera ballCam(100);

PhysicsObject3D temp_floor(0, -1, 0, 1, 0.1);    // PLACEHOLDER
vector<PhysicsObject3D*> temp_scene_objs;

random_device device;
mt19937 generator(device());
uniform_real_distribution<float> enemyX(-50, 50);
uniform_real_distribution<float> enemyZ(-50, 50);
vector<Enemy *> enemies;
int initNumOfBoombas = 5;
float boombaDistToFloor = 5;
int initNumOfSweepers = 5;
float sweeperDistToFloor = 5;
//Level level1("map1");

int prevX;
int prevY;

int time_past;

Menu menu;


GLfloat lightPos[] =
	{ 0, 0, 1.5, 1 };
float lightAmb[] = { 1, 1, 1, 1 };
float lightDif[] = { 1, 1, 1, 1 };
float lightSpc[] = { 0.35, 0.35, 0.35, 1 };

float ambMat2[4] = {0.5,0.5,0.5,1};
float diffMat2[4] = {0,1,0,1};
float specMat2[4] = {0,1,0,1};
static int spin = 0;

void keyboard(unsigned char key, int _x, int _y) {
    // if (key == 'q') {
    //     exit(0);
    // }

    if (key  == ' '){
        pauseStatus = !pauseStatus;
    }
}

void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        ball.jump();
    }
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
    // if (0 <= x <= windowX || 0 <= y <= windowY) {
    //     pauseStatus = false; // if mouse inside window, game runs
    // }
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
        Vec3D forward(ball.getX() - ballCam.getX(),0,ball.getZ() - ballCam.getZ());
        forward = forward.normalize().multiply(30);
        Vec3D sideways = forward.crossProd(Vec3D(0, 1, 0)).normalize().multiply(30);

        if (key == GLUT_KEY_UP){
            ball.accelerate(forward.x, 0, forward.z);
        }
        
        if (key == GLUT_KEY_DOWN){
            ball.accelerate(-forward.x, 0, -forward.z);
            spin = (spin + 30) % 360;
        }

        if (key == GLUT_KEY_RIGHT){
            ball.accelerate(sideways.x, 0, sideways.z);
            spin = (spin + 30) % 360;
            
        }

        if (key == GLUT_KEY_LEFT){
            ball.accelerate(-sideways.x, 0, -sideways.z);
            spin = (spin - 30) % 360;
        }

    }
    glutPostRedisplay();
}

void FPS (int val){
    //any code here
    int time_current = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int d_time = time_current - time_past;
    frameTime = d_time;
    time_past = time_current; 

    if (!pauseStatus) {
        for (Enemy * i : enemies) {
            i->animate();
        }
    }

    if (!pauseStatus) {
        ball.runPhysics(min(d_time, 33), temp_scene_objs);
        ballCam.changePosition(ball.getX(),ball.getY(),ball.getZ());
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

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(
        ballCam.getX(),    ballCam.getY(),    ballCam.getZ(),
        ball.getX(),    ball.getY(),    ball.getZ(),
        0,1,0
    );

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpc);
    glShadeModel(GL_SMOOTH);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambMat2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffMat2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specMat2);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 27);
    
    
    //graphics objects here

    glPushMatrix();
        glPushMatrix();
            glRotated(spin, 1.0,0.0,0.0);
            glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glPopMatrix();
        ball.displayAsset();
    glPopMatrix();
    glFlush();



    glColor3f(1,0,0);
    glPushMatrix();
        glBegin(GL_POLYGON);
            glVertex3f(200,0,200);
            glVertex3f(200,0,-200);
            glVertex3f(-200,0,-200);
            glVertex3f(-200,0,200);
        glEnd();
    glPopMatrix();


    glColor3f(0, 1, 0);
    glPushMatrix();
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        for (Enemy * i : enemies) {
            i->displayAsset();
        }
    glPopMatrix();
    glFlush();

    if (pauseStatus) {
        menu.display(windowX, windowY);
    }


    displayFPS();

    glutSwapBuffers();

}

void init(){

    windowX = 800;
    windowY = 800;
    refreshRate = 120;
    frameTime = 0;


    temp_floor.addBoxCollider(400, 2, 400, 0, 0, 0);
    temp_scene_objs.push_back(&temp_floor);

    // for (int i = 0; i < initNumOfBoombas; i++) {
    //     enemies.push_back(new Boomba(enemyX(generator), boombaDistToFloor, enemyZ(generator))); // can change boombaDistToFloor later
    //     temp_scene_objs.push_back(enemies.at(i)->getPhysicsPointer()); // so that ball will check for collisions
    // }

    // for (int i = 0; i < initNumOfSweepers; i++) {
    //     enemies.push_back(new Sweeper(enemyX(generator), sweeperDistToFloor, enemyZ(generator)));
    //     temp_scene_objs.push_back(enemies.at(i + initNumOfBoombas)->getPhysicsPointer());
    // }

    time_past = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void handleReshape(int w, int h) {
    windowX = w;
    windowY = h;
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, windowX/windowY, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
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