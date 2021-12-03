#include "enemy.h"

Enemy::Enemy(float inX, float inY, float inZ) : Asset(inX, inY, inZ)
{
    this->collided = false;
    this->inX = inX;
    this->inY = inY;
    this->inZ = inZ;
}

void Enemy::animate() {}

bool Enemy::checkCollision(){
    return collided;
}