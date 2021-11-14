#include "enemy.h"

#ifndef SWEEPER_H
#define SWEEPER_H

/* 
The sweeper class will stay in one place, and will have a continuous movement that 
will move the player off the map if the player collides with it.
*/

class Sweeper : public Enemy {
    public:
        Sweeper(float inX, float inY, float inZ);
        float moveZBy;

        //virtual void animate() override;
        void animate();
        using Enemy::Enemy;
        // collision animation? 
};

#endif