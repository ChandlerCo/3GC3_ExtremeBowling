#include "physics_3D.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
    protected:
        PhysicsObject3D enemyPhysics;
        Point3D pos;
        // Mesh here
        // Texture here
    public:

        void defaultMovement(); 
        void collisionAnimation();
};

#endif