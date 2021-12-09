#include <cstring>
#include <string>
#include "enemy.h"

#ifndef SWEEPER_H
#define SWEEPER_H

/* 
The sweeper class will stay in one place, and will have a continuous movement that 
will move the player off the map if the player collides with it.
*/

class Sweeper : public Enemy {
    public:
        Sweeper(float inX, float inY, float inZ, float endX, float endY, float endZ, int id);
        // float moveZBy;

        //virtual void animate() override;
        void animate();
        // collision animation? 
        static int hitBall(void* context, Vec3D deflection, void* obj);
        static vector<Sweeper*> fromJson(vector<json> jsonData, float tileSize);
};

#endif