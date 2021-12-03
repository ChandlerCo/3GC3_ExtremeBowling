#include "powerup.h"

PowerUp::PowerUp(float inX, float inY, float inZ) : Asset(inX, inY, inZ)
 {
      this->graphics = Graphics("powerup");
      this->obj_scalar = 5;
 }

void PowerUp::defaultAnimation()
{

}

void PowerUp::collisionAnimation()
{

}

void PowerUp::powerUpType()
{
    
}

bool PowerUp::checkCollision(){
    return collided;
}