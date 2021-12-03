#include "enemy.h"

Enemy::Enemy(float inX, float inY, float inZ, float endX, float endY, float endZ, int id) : Asset(inX, inY, inZ)
{
    this->collided = false;
    this->inX = inX;
    this->inY = inY;
    this->inZ = inZ;
    this->endX = endX;
    this->endY = endY;
    this->endZ = endZ;
    this->physics.setLocalId(id);

    startPos = Point3D(inX, inY, inZ);
    endPos = Point3D(endX, endY, endZ);

    movingToEnd = true;

    forwardDir = Vec3D::createVector(Point3D(inX, inY, inZ), Point3D(endX, endY, endZ));
    forwardDir = forwardDir.normalize();
    backwardDir = Vec3D::createVector(Point3D(endX, endY, endZ), Point3D(inX, inY, inZ));
    backwardDir = backwardDir.normalize();
}

void Enemy::animate() {}

bool Enemy::checkCollision(){
    return collided;
}

/*
int Enemy::hitBall(void* context, Vec3D deflection, void* obj)
{
    Enemy* e = static_cast<Enemy*>(context);
    PhysicsObject3D* ball = static_cast<PhysicsObject3D*>(obj);
    
    e->collided = true;

    return 0;
}*/