#include "physics_3D.h"

#ifndef SWEEPER_H
#define SWEEPER_H

/* 
The sweeper class will stay in one place, and will have a continuous movement that 
will move the player off the map if the player collides with it.
*/

class Sweeper {
    private:
        PhysicsObject3D sweeperPhysics;
        // Mesh *sweeperMesh;
        // Texture sweeperTexture;
    public:
        float getX();
        float getY();
        float getZ();

        void defaultMovement(); // will need to loop some movement
        void collisionAnimation(); // don't necessarily need this
};

#endif