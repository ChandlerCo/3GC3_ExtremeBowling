#include <cstring>
#include <string>
#include "enemy.h"

#ifndef BOOMBA_H
#define BOOMBA_H

/* 
The Boomba class will be similar to the Goomba from Mario. It will be a character
that moves around randomly at a slow speed and will negatively affect the player 
if the player hits it. Ex. we could have the player be stunned and not be able to 
move for a certain amount of time after colliding with a Boomba, or we could have
the player bounce off of the Boomba and lose pins, or a life.
*/

class Boomba : public Enemy {
    private:
        Vec3D deflect;
    public:
        Boomba(float inX, float inY, float inZ, float endX, float endY, float endZ, int id);
        // float moveXBy;

        void animate(float time);
        void collisionAnimation();
        //float inY;
        static int hitBall(void* context, Vec3D deflection, void* obj);
        static vector<Boomba*> fromJson(vector<json> jsonData, float tileSize);
};

#endif