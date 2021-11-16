#include <cstring>
#include <string>
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
        Enemy(float inX, float inY, float inZ);
        virtual void animate();
};

#endif