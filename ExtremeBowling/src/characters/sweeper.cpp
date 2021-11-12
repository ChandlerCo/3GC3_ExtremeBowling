#include "sweeper.h"

Sweeper::Sweeper(float inX, float inY, float inZ)
{
    this->physics = PhysicsObject3D(inX, inY, inZ);

    // initial position
    this->inX = inX;
    this->inY = inY;
    this->inZ = inZ;
}

void Sweeper::animate()
{
    if (physics.getPos().distanceTo(Point3D(inX, inY, inZ)) >= 5) {
        physics.setRotation(0, 1, 0, 180); 
    }

    physics.addAcceleration(0.5, 0.5, 0.5);
    // Update physics?
}