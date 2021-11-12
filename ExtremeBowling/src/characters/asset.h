#include "../misc/physics_3D.h"
#include "../misc/objLoader.h"

#ifndef ASSET_H
#define ASSET_H

class Asset {
    protected:
        PhysicsObject3D physics;
        // Mesh and texture here
    public:
        Asset(float startX, float startY, float startZ);
        float getX();
        float getY();
        float getZ();
};

#endif