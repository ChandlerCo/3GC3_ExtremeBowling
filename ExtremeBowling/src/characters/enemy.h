#include "asset.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Asset {
    protected:
        // store initial position
        float inX;
        float inY;
        float inZ;
    public:

        /* 
        not sure if these need to be included here
        no implementation in enemy.cpp
        */
        void animate(); 
        void collisionAnimation(); 
};

#endif