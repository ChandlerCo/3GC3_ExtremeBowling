#include "ioFuncs.h"
#include "characters/ball.h"
#include "misc/camera.h"

int refreshRate;
int windowX;
int windowY;
bool pauseStatus;

Ball ball(0,0,0);
Camera ballCam(100);




void FPS (int val){
  glutPostRedisplay();

    //any code here
  glutTimerFunc(1000/refreshRate, FPS, 0);

}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(
        ballCam.getX(),    ballCam.getY(),    ballCam.getZ(),
        0, 0, 0, // need to replace with ball location
        0,1,0
    );


    //graphics objects here
    glColor3b(1,1,1);
	glutSolidSphere(10,20,20);

	glutSwapBuffers();

}


void init(){
    windowX = 800;
    windowY = 800;
    refreshRate = 60;

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
