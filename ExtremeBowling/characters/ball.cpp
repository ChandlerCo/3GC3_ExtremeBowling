# include "ball.h"


void Ball::accelerate(float x, float y, float z){
    this->physics.addAcceleration(x,y,z);

}