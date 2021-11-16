#include "enemy.h"

Enemy::Enemy(float inX, float inY, float inZ) : Asset(inX, inY, inZ)
{
    this->inX = inX;
    this->inY = inY;
    this->inZ = inZ;
}

void Enemy::animate() {}