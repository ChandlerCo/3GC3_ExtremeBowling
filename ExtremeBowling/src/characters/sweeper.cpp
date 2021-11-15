#include "sweeper.h"

Sweeper::Sweeper(float inX, float inY, float inZ, string filename) : Enemy(inX, inY, inZ, filename)
{
    this->physics = PhysicsObject3D(inX, inY, inZ);

    // initial position
    this->inX = inX;
    this->inY = inY;
    this->inZ = inZ;

    moveZBy = 1;
}

void Sweeper::animate()
{
    //std::cout << "sweeper animate" << std::endl;

    if (physics.getPos().distanceTo(Point3D(inX, inY, inZ)) >= 50) {
        physics.setRotation(0, 1, 0, 180); 
        moveZBy = -moveZBy;
    }

    physics.setPosition(physics.getPos().x, physics.getPos().y, physics.getPos().z + moveZBy);

    // Update physics?
}