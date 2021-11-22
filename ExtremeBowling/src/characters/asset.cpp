#include "asset.h"
#include "../misc/mathlib_3D.h"
#include "../misc/physics_3D.h"
#include <fstream>
#include <sstream>
#include <stdio.h> 
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cstring>
#include <string>

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



Asset::Asset(float startX, float startY, float startZ){
    this->physics = PhysicsObject3D( startX, startY, startZ);

    //something to load object files or object type
}
Asset::Asset(){
    this->physics = PhysicsObject3D( 0, 0, 0);
}

float Asset::getX(){
    return this->physics.getPos().x;
}

float Asset::getY(){
    return this->physics.getPos().y;
}

float Asset::getZ(){
    return this->physics.getPos().z;
}

Rot3D Asset::getRot()
{
    return this->physics.getRot();
}

void Asset::position(float x, float y, float z)
{
    this->physics.setPosition(x, y, z);
}

void Asset::velocity(float x, float y, float z)
{
    this->physics.setVelocity(x, y, z);
}

void Asset::accelerate(float x, float y, float z)
{
    this->physics.addAcceleration(x, y, z);
}

void Asset::runPhysics(float time, bool gravity, vector<PhysicsObject3D *> objs)
{
    this->physics.updatePhysics(time, gravity, objs);
}

PhysicsObject3D * Asset::getPhysicsPointer()
{
    return &this->physics;
}

// Load the obj file
bool Asset::loadObj(string filename,
                vector <Vec3D> & out_vertices,
                vector <Vec3D> & out_uvs,
                vector <Vec3D> & out_normals)
{

    vector <unsigned int> vtxIndices, uvIndices, nIndices;
    vector <Vec3D> tempVertices; //Mesh
    vector <Vec3D> tempUV; // Textures 
    vector <Vec3D> tempNormals; // Normals

    // open the file
    filename = "src/objects/" + filename + ".obj";
    FILE * file = fopen(filename.c_str(), "r");

    
    if( file == NULL ){
        printf("Impossible to open the file !\n");
         return false;
    }

    // reading the file
    while(true) 
    {
        
        char lineHeader[128];

        int res = fscanf(file, "%s", lineHeader);

        if (res == EOF)
            break;

        if (strcmp(lineHeader, "v") == 0) 
        {
            Vec3D vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            tempVertices.push_back(vertex);

        } else if (strcmp(lineHeader, "vn") == 0)
        {
            Vec3D normal;

            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            tempNormals.push_back(normal);

        // faces
        } else if (strcmp(lineHeader, "f")== 0) 
        {
            string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vtxIndices.push_back(vertexIndex[0]);
            vtxIndices.push_back(vertexIndex[1]);
            vtxIndices.push_back(vertexIndex[2]);
            uvIndices     .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            nIndices.push_back(normalIndex[0]);
            nIndices.push_back(normalIndex[1]);
            nIndices.push_back(normalIndex[2]);
        } else if (strcmp( lineHeader, "vt" ) == 0)
        {
            Vec3D uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            tempUV.push_back(uv);
        }
    }

    for( unsigned int i=0; i<vtxIndices.size(); i++ ){
        unsigned int vertexIndex = vtxIndices[i] - 1;
        if (vertexIndex < 0)
			vertexIndex += vtxIndices.size() + 1;
        Vec3D vertex = tempVertices[ vertexIndex ];
        out_vertices.push_back(vertex);
    }

    for( unsigned int i=0; i<uvIndices.size(); i++ ){
        unsigned int uvIndex = uvIndices[i] - 1;
        if (uvIndex < 0)
			uvIndex += uvIndices.size() + 1;
        Vec3D uv = tempUV[ uvIndex ];
        out_uvs.push_back(uv);
    }

    for( unsigned int i=0; i<nIndices.size(); i++ ){
        unsigned int normalIndex = nIndices[i] - 1;
        if (normalIndex < 0)
			normalIndex += nIndices.size() + 1;
        Vec3D normal = tempNormals[ normalIndex ];
        out_normals.push_back(normal);
    }

    return true;
}

void Asset::displayAsset()
{
	Rot3D r = physics.getRot();

	glPushMatrix();
        glRotatef(r.getAngle(), r.getX(), r.getY(), r.getZ());
		glBegin(GL_TRIANGLES);
		// render each triangle
		for (int i = 0; i < this->vertices.size() ; i++) {
			glVertex3f(this->vertices.at(i).x, this->vertices.at(i).y, this->vertices.at(i).z);
			glNormal3f(this->normals.at(i).x, this->normals.at(i).y, this->normals.at(i).z);
		}
		glEnd();
	glPopMatrix();

}