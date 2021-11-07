#include "physics_3D.h"

#ifndef BOOMBA_H
#define BOOMBA_H

/* 
The Boomba class will be similar to the Goomba from Mario. It will be a character
that moves around randomly at a slow speed and will negatively affect the player 
if the player hits it. Ex. we could have the player be stunned and not be able to 
move for a certain amount of time after colliding with a Boomba, or we could have
the player bounce off of the Boomba and lose pins, or a life.
*/

class Boomba {
    private:
        PhysicsObject3D boombaPhysics;
        // Mesh *boombaMesh;
        // Texture boombaTexture;
    public:
        float getX();
        float getY();
        float getZ();

        void defaultMovement(); // random, slow movement, should not move off map by itself, avoid powerups?
        void collisionAnimation(); // will depend on if player has invisible powerup or not
};

#endif