#include "camera.h"
#define _USE_MATH_DEFINES
#include <cmath>

Camera::Camera(float startDistance){
    this->sensitivity = 5;
    this->distance = startDistance;
    for(int i = 0; i < 3; i++){
        this->centre[i] = 0;
    }
    this->phi = M_PI/3 ;
    this->theta = M_PI/3;
    updatePosition();
}


void Camera::updatePosition(){
    this->position[0] = this->distance * sin(this->phi) * sin(this->theta) + this->centre[0];
	this->position[1] = this->distance * cos(this->theta) + this->centre[1];
	this->position[2] = this->distance * cos(this->phi) * sin(this->theta) + this->centre[2];
}

void Camera::changeDistance(bool direction){
    if(direction){
        this->distance +=1;
    } else{
        this->distance -=1;
    }
    updatePosition();
}

void Camera::orbitVertical(int amount){
    if((amount > 0 && theta < M_PI/2) || (amount < 0 && theta > M_PI/16) ){
        this->theta += M_PI*amount*sensitivity/1000;
        this->updatePosition();
    }
}

void Camera::orbitHorizontal(int amount){
        this->phi += M_PI*amount*sensitivity/1000;
        this->updatePosition();
    

}

void Camera::translate(float x, float y, float z){
    this->centre[0] += x;
    this->centre[1] += y;
    this->centre[2] += z;
    this->updatePosition();
}

void Camera::changePosition(float x, float y, float z){
    this->centre[0] = x;
    this->centre[1] = y;
    this->centre[2] = z;
    this->updatePosition();
}


float Camera::getX(){
    return this->position[0];
}

float Camera::getY(){
    return this->position[1];
}

float Camera::getZ(){
    return this->position[2];
}
