#ifndef ASSET_H
#define ASSET_H

#include <vector>
#include "../misc/graphics.h"
#include "../misc/physics_3D.h"
#include "../misc/mathlib_3D.h"

using namespace std;

class Asset {
    protected:
        PhysicsObject3D physics;
        Graphics graphics;

    public:
        Asset();
        Asset(float startX, float startY, float startZ);
        float getX();
        float getY();
        float getZ();

        Rot3D getRot();

        void position(float x, float y, float z);
        void velocity(float x, float y, float z);
        void accelerate(float x, float y, float z);
        void runPhysics(float time, bool gravity = false, vector<PhysicsObject3D *> objs = {});

        PhysicsObject3D * getPhysicsPointer();

        void displayAsset();
};

#endif