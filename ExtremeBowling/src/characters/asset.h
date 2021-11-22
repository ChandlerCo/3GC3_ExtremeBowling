#include "../misc/physics_3D.h"
#include "../misc/mathlib_3D.h"


#ifndef ASSET_H
#define ASSET_H

#include <vector>
#include "graphics.h"
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

        bool loadObj(string filename,
            vector <Vec3D> & out_vertices,
            vector <Vec3D> & out_uvs,
            vector <Vec3D> & out_normals 
        );
        
        vector <Vec3D> vertices; 
        vector <Vec3D> uvs; //texture mapping
        vector <Vec3D> normals;
        void displayAsset();
};

#endif