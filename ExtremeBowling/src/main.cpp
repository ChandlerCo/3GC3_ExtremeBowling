#ifdef __APPLE__
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

// #include "ioFuncs.h"
#include "characters/ball.h"
#include "misc/camera.h"

using namespace std;
using namespace std::chrono;

int refreshRate;
int windowX;
int windowY;
bool pauseStatus;
map<string, Asset> ll; // dictionary of characters

Ball ball(0, 30, 0, 8);
Camera ballCam(100);

int prevX;
int prevY;

int time_past;

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
		Vec3D forwardVec(ball.getX() - ballCam.getX(),ball.getY() - ballCam.getY(),ball.getZ() - ballCam.getZ());
		forwardVec.normalize().multiply(10);

		if (key == GLUT_KEY_UP){
			ball.accelerate(forwardVec.x, forwardVec.y, forwardVec.z);
		}
		
		if (key == GLUT_KEY_DOWN){
			ball.accelerate(-forwardVec.x, -forwardVec.y, forwardVec.z);
		}

		if (key == GLUT_KEY_RIGHT){
			ball.accelerate(forwardVec.y, -forwardVec.x, forwardVec.z);
		}

		if (key == GLUT_KEY_LEFT){
			ball.accelerate(-forwardVec.y, forwardVec.x, forwardVec.z);
		}

	}
}


void FPS (int val){
    //any code here
	int time_current = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int d_time = time_current - time_past;
    time_past = time_current; 

	ball.runPhysics(min(d_time, 33));

	glutPostRedisplay();

	d_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - time_past;
  	glutTimerFunc(1000/refreshRate - d_time, FPS, 0);

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
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(
        ballCam.getX(),	ballCam.getY(),	ballCam.getZ(),
        ball.getX(),	ball.getY(),	ball.getZ(), // need to replace with ball location
        0,1,0
    );
	

	displayAsset("powerup");

    //graphics objects here
    glColor3f(1,1,1);
	glPushMatrix();
        glTranslatef(20,0,0);
        glutSolidCube(5);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(ball.getX(),ball.getY(),ball.getZ());
        glutSolidSphere(8,20,20);
    glPopMatrix();


	glutSwapBuffers();

}


void init(){
    windowX = 800;
    windowY = 800;
    refreshRate = 60;
    // ball.loadObj("../src/objects/boomba.obj");
	loadAsset("src/objects/powerup.obj", "powerup");

	time_past = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void handleReshape(int w, int h) {
    windowX = w;
    windowY = h;
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

	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowX, windowY);
    glutInitWindowPosition(300,300);

	glutCreateWindow("Extreme Bowling");	//creates the window



    //callbacks
	glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passive);
	glutSpecialFunc(special);
	glutReshapeFunc(handleReshape);
	
	glutDisplayFunc(display);	//registers "display" as the display callback function


	glutTimerFunc(1000/refreshRate,FPS, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glutMainLoop();

	return 0;					
}



#endif