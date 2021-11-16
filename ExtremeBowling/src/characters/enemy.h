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
        Enemy(float inX, float inY, float inZ, string filename);

        //virtual void animate();
        void animate();
        //using Asset::Asset;
};

#endif