#include "sweeper.h"

Sweeper::Sweeper(float inX, float inY, float inZ) : Enemy(inX, inY, inZ)
{
    this->physics = PhysicsObject3D(inX, inY, inZ);

    // initial position
    this->inX = inX;
    this->inY = inY;
    this->inZ = inZ;

    moveZBy = 0.1;
}

void Sweeper::animate()
{
    //std::cout << "sweeper animate" << std::endl;

    if (physics.getPos().distanceTo(Point3D(inX, inY, inZ)) >= 10) {
        physics.setRotation(0, 1, 0, 180); 
        moveZBy = -moveZBy;
    }

    physics.setPosition(physics.getPos().x, physics.getPos().y, physics.getPos().z + moveZBy);

    // Update physics?
}