#include "../misc/physics_3D.h"
#include "../misc/mathlib_3D.h"
#include <vector>

#ifndef ASSET_H
#define ASSET_H

using namespace std;

class Asset {
    protected:
        PhysicsObject3D physics;

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

        std::vector <unsigned int> vtxIndices, texIndices, nIndices;
        std::vector <Point3D> tempVertices; //Mesh
        std::vector <Point3D> tempUV; // Textures 
        std::vector <Vec3D> tempNormals; // Normals

        bool loadObj(const char* filename);
};

#endif