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
#include "misc/camera.h"
#include "characters/boomba.h"
#include "characters/sweeper.h"

using namespace std;
using namespace std::chrono;

int refreshRate;
int frameTime;
int frameCount;
int windowX;
int windowY;
bool pauseStatus;
map<string, Asset> ll; // dictionary of characters

Ball ball(0, 10, 0, 8);
Camera ballCam(100);

PhysicsObject3D temp_floor(0, -1, 0, false, 0.1);    // PLACEHOLDER

// make separate enemySpawner class? 
random_device device;
mt19937 generator(device());
uniform_real_distribution<float> enemyX(-50, 50);
uniform_real_distribution<float> enemyZ(-50, 50);
//vector<Enemy*> enemies;
vector<Enemy *> enemies;
int initNumOfBoombas = 5;
float boombaDistToFloor = 5;
int initNumOfSweepers = 5;
float sweeperDistToFloor = 5;
//int initNumOfEnemies = initNumOfBoombas + initNumOfSweepers;

int prevX;
int prevY;

int time_past;

float light_pos[4] = {5,5,5,1};
float amb[4] = {1,1,1,1};
float diff[4] = {1,1,1,1};
float spec[4] = {1,1,1,1};

float ambMat2[4] = {0.5,0.5,0.5,1};
float diffMat2[4] = {0,1,0,1};
float specMat2[4] = {0,1,0,1};

void keyboard(unsigned char key, int _x, int _y) {
    // if (key == 'q') {
    //     exit(0);
    // }

    if (key  == ' '){
        pauseStatus = !pauseStatus;
    }
}

void mouse(int button, int state, int x, int y){
    //mouse left click-jump
}

void motion(int x, int y){
    //pan camera
}

void passive(int x, int y){
    if(!pauseStatus){
        ballCam.orbitHorizontal(x - prevX);
        ballCam.orbitVertical(y - prevY);

        prevX = x;
        prevY = y;

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
        }

        if (key == GLUT_KEY_RIGHT){
            ball.accelerate(sideways.x, 0, sideways.z);
        }

        if (key == GLUT_KEY_LEFT){
            ball.accelerate(-sideways.x, 0, -sideways.z);
        }

    }
}

void FPS (int val){
    //any code here
    int time_current = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int d_time = time_current - time_past;
    frameTime = d_time;
    time_past = time_current; 

    for (Enemy * i : enemies) {
        i->animate();
    }


    ball.runPhysics(min(d_time, 33));
    ballCam.changePosition(ball.getX(),ball.getY(),ball.getZ());


    glutPostRedisplay();

    d_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - time_past;
    
    frameCount += 1;
    if(d_time > 1000 / refreshRate){
        glutTimerFunc(1, FPS, 0);
        
    } else {
        glutTimerFunc(1000 / refreshRate, FPS, 0);
    }
    

}

void loadAsset(const char* filename, string name)
{
    Asset character;
    character = Asset();
    character.loadObj(filename);
    ll[name] = character; 
}

// sets the normals and builds the character based on mesh info
void displayAsset(string name)
{
    
    glPushMatrix();
        glBegin(GL_TRIANGLES);
        int size = ll[name].vtxIndices.size();
        int num_vertices = ll[name].tempVertices.size();
        int num_normals = ll[name].tempNormals.size();
        int index;
        // render each triangle
        for (int i = 0; i < size ; i++) {
            // vertices
            index = ll[name].vtxIndices[i] - 1;

            if (index < 0)
                index = num_vertices + index + 1;

            Point3D v = ll[name].tempVertices.at(index);

            glVertex3f(v.x, v.y, v.z);

            // textures will go here

            // normals
            index = ll[name].nIndices[i] - 1;

            if (index < 0)
                index = num_normals + index + 1;

            Vec3D n = ll[name].tempNormals.at(index);
            glNormal3f(n.x, n.y, n.z);
        }
        glEnd();
    glPopMatrix();

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
        ball.getX(),    ball.getY(),    ball.getZ(), // need to replace with ball location
        0,1,0
    );

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambMat2);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffMat2);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specMat2);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 27);
    /*
    glPushMatrix();
    glTranslatef(20,0,20);
    glScalef(0.1, 0.1, 0.1);
    displayAsset("powerup");
    glPopMatrix();
    */

    //graphics objects here


    glPushMatrix();
        glTranslatef(ball.getX(),ball.getY(),ball.getZ());
        glScalef(2, 2, 2);
        ball.displayAsset();
    glPopMatrix();

    glColor3f(1,0,0);
    glPushMatrix();
        glBegin(GL_POLYGON);
            glVertex3f(200,0,200);
            glVertex3f(200,0,-200);
            glVertex3f(-200,0,-200);
            glVertex3f(-200,0,200);
        glEnd();
    glPopMatrix();

    glColor3f(0, 0, 1);
    for (Enemy * i : enemies) {
        glPushMatrix();
            glTranslatef(i->getX(), i->getY(), i->getZ());
            glScalef(0.5, 0.5, 0.5);
            i->displayAsset();
        glPopMatrix();
    }


    displayFPS();

    glutSwapBuffers();

}

void init(){

    windowX = 800;
    windowY = 800;
    refreshRate = 120;
    frameTime = 0;
    // ball.loadObj("../src/objects/boomba.obj");
    //loadAsset("src/objects/powerup.obj", "powerup");

    temp_floor.addBoxCollider(400, 2, 400, 0, 0, 0);
    ball.addSceneObject(&temp_floor);

    for (int i = 0; i < initNumOfBoombas; i++) {
        enemies.push_back(new Boomba(enemyX(generator), boombaDistToFloor, enemyZ(generator))); // can change boombaDistToFloor later
    }

    for (int i = 0; i < initNumOfSweepers; i++) {
        enemies.push_back(new Sweeper(enemyX(generator), sweeperDistToFloor, enemyZ(generator)));
    }

    time_past = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void handleReshape(int w, int h) {
    windowX = w;
    windowY = h;
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70, windowX/windowY, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
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