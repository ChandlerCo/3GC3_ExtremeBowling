
#include "ioFuncs.h"
#include "main.cpp"

int prevX;
int prevY;

void keyboard(unsigned char key, int _x, int _y) {
    if (key == 'q') {
        exit(0);
    }

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
		forwardVec.normalize();

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