#include "asset.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Asset {
    protected:
        // store initial position
        float inX;
        float inY;
        float inZ;
};

#endif