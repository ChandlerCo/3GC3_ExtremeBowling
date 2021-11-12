#include "boomba.h"

Boomba::Boomba(float inX, float inY, float inZ)
{
    this->physics = PhysicsObject3D(inX, inY, inZ);

    // initial position
    this->inX = inX;
    this->inY = inY;
    this->inZ = inZ;
}

void Boomba::animate()
{
    /* 
    in main, we'll have a glutTimerFunc or smth,
    and we'll call:
        for enemy in our vector of enemies:
            enemy.animate();
    */
   
    /* 
    so we want to update the position of the boomba
    here in this method. Want it to move left and right
    */

    /* 
    - Deviate only a certain distance from initial position
    - Rotate 90 degrees to left, then add acceleration
    - If boomba position passes certain limit, rotate 180 
    degrees, and start moving to the right
    */

    // Check if boomba is at initial position, animation start
    if (inX == physics.getPos().x && inY == physics.getPos().y && inZ == physics.getPos().z) {
        physics.setRotation(0, 1, 0, -90);
    }

    // move boomba in forward direction until it reaches certain point
    // once limit reached, rotate 180, and move forward again until next limit reached

    if (physics.getPos().distanceTo(Point3D(inX, inY, inZ)) >= 3) {
        physics.setRotation(0, 1, 0, 180); // is rotation in respect to initial angle or current angle?
    }

    physics.addAcceleration(0.1, 0.1, 0.1); // is this enough to update the position?
    // Call update physics?
}

void Boomba::collisionAnimation()
{
    
}