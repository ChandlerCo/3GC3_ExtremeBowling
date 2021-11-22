#include "asset.h"

#include <fstream>
#include <sstream>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cstring>
#include <string>


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



Asset::Asset(float startX, float startY, float startZ){
    this->physics = PhysicsObject3D( startX, startY, startZ);

    //something to load object files or object type
}
Asset::Asset(){
    this->physics = PhysicsObject3D( 0, 0, 0);
}

float Asset::getX(){
    return this->physics.getPos().x;
}

float Asset::getY(){
    return this->physics.getPos().y;
}

float Asset::getZ(){
    return this->physics.getPos().z;
}

Rot3D Asset::getRot()
{
    return this->physics.getRot();
}

void Asset::position(float x, float y, float z)
{
    this->physics.setPosition(x, y, z);
}

void Asset::velocity(float x, float y, float z)
{
    this->physics.setVelocity(x, y, z);
}

void Asset::accelerate(float x, float y, float z)
{
    this->physics.addAcceleration(x, y, z);
}

void Asset::runPhysics(float time, bool gravity, vector<PhysicsObject3D *> objs)
{
    this->physics.updatePhysics(time, gravity, objs);
}

PhysicsObject3D * Asset::getPhysicsPointer()
{
    return &this->physics;
}

// Load the obj file

void Asset::displayAsset()
{
    glPushMatrix();
        glTranslatef(this->getX(), this->getY(), this->getZ());
        glScalef(0.5, 0.5, 0.5);
        this->graphics.displayAsset(physics.getRot());
    glPopMatrix();
	

}