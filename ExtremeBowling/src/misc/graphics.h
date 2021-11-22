#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <cstring>
#include <string>
#include "mathlib_3D.h"

using namespace std;

class Graphics {
    public:
        Graphics();
        Graphics(string filename);
        bool loadObj(string filename,
            vector <Vec3D> & out_vertices,
            vector <Vec3D> & out_uvs,
            vector <Vec3D> & out_normals 
        );
        
        vector <Vec3D> vertices; 
        vector <Vec3D> uvs; //texture mapping
        vector <Vec3D> normals;

        void displayAsset(Rot3D r);

};



#endif