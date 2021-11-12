
#include "ioFuncs.h"


void keyboard(unsigned char key, int _x, int _y) {
    if (key == 'q') {
        exit(0);
    }
}

void mouse(int button, int state, int x, int y){

}

void motion(int x, int y){

}
void passive(int x, int y){

}




void special(int key, int x, int y){
	if (key == GLUT_KEY_RIGHT){

	}

	if (key == GLUT_KEY_LEFT){

	}

	if (key == GLUT_KEY_UP){

	}
    
	if (key == GLUT_KEY_DOWN){

	}

}