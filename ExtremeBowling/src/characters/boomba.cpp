#include "boomba.h"

Boomba::Boomba(float inX, float inY, float inZ) : Enemy(inX, inY, inZ)
{
    // initial rotation
    physics.setRotation(0, 1, 0, -90);
    loadObj("boomba");
}

void Boomba::animate()
{
    //std::cout << "boomba animate" << std::endl;

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

    // move boomba in forward direction until it reaches certain point
    // once limit reached, rotate 180, and move forward again until next limit reached

    if (physics.getPos().distanceTo(Point3D(inX, inY, inZ)) >= 5) {
        physics.setRotation(0, 1, 0, -physics.getRot().getAngle());
    }

    if (physics.getRot().getAngle() > 0) {
        physics.setPosition(physics.getPos().x + 0.1, physics.getPos().y, physics.getPos().z);
    }

    if (physics.getRot().getAngle() < 0) {
        physics.setPosition(physics.getPos().x - 0.1, physics.getPos().y, physics.getPos().z);
    }
    
    // Call update physics?
}

void Boomba::collisionAnimation()
{
    
}