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
        float endX;
        float endY;
        float endZ;

        Point3D startPos;
        Point3D endPos;
        float speed;
        Vec3D forwardDir;
        Vec3D backwardDir;
        bool movingToEnd;

        bool collided;
    public:
        Enemy(float inX, float inY, float inZ, float endX, float endY, float endZ, int id);
        virtual void animate(float time);
        bool checkCollision();
        //virtual static int hitBall(void* context, Vec3D deflection, void* obj);
};

#endif