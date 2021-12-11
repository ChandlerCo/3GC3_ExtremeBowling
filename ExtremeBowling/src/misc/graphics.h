#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include "mathlib_3D.h"

using namespace std;

#define BRASS {{0.329412f, 0.223529f, 0.027451f,0.2f}, {0.780392f, 0.568627f, 0.113725f, 0.2f}, {0.992157f, 0.941176f, 0.807843f, 0.2f}, 27.8974f}
#define BRONZE {{0.2125f, 0.1275f, 0.054f, 0.2f}, {0.714f, 0.4284f, 0.18144f, 0.2f}, {0.393548f, 0.271906f, 0.166721f, 0.2f}, 25.6f}
#define SILVER {{0.23125f, 0.23125f, 0.23125f, 0.2f}, {0.2775f, 0.2775f, 0.2775f, 0.2f}, {0.773911f, 0.773911f, 0.773911f, 0.2f}, 89.6f}
#define GOLD {{0.24725f, 0.2245f, 0.0645f, 0.2f}, {0.34615f, 0.3143f, 0.0903f, 0.2f}, {0.797357f, 0.723991f, 0.208006f, 0.2f}, 83.2f}
#define OBSIDIAN {{0.05375f, 0.05f, 0.06625f, 0.2f}, {0.18275f, 0.17f, 0.22525f, 0.2f}, {0.332741f, 0.328634f, 0.346435f, 0.2f}, 38.4f}


struct Material {
    float amb[4];
    float diff[4];
    float spec[4];
    float shine;
};

class Graphics {
    public:
        Graphics();
        Graphics(string filename, Material m=GOLD);
        bool loadObj(string filename,
            vector <Vec3D> & out_vertices,
            vector <Vec3D> & out_uvs,
            vector <Vec3D> & out_normals 
        );
        void setMaterial(Material m);
        static GLuint textures[3];
        static GLubyte *bowling, *red, *white;
        static int width, height, max;
        
        Material mat;
        vector <Vec3D> vertices; 
        vector <Vec3D> uvs; //texture mapping
        vector <Vec3D> normals;

        // static void initTextures();
        void displayAsset(Rot3D r);
        static GLubyte* LoadPPM(char* file, int* width, int* height, int* max);

};



#endif