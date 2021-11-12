#include "asset.h"



Asset::Asset(float startX, float startY, float startZ){
    this->physics = PhysicsObject3D( startX, startY, startZ);

    //something to load object files or object type

}


float Asset::getX(){
    this->physics.getPos().x;
}

float Asset::getY(){
    this->physics.getPos().y;
}

float Asset::getZ(){
    this->physics.getPos().z;
}


