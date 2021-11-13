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




Asset::Asset(float startX, float startY, float startZ){
    this->physics = PhysicsObject3D( startX, startY, startZ);

    //something to load object files or object type

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
bool Asset::loadObj(const char* filename)
{
    // counters
    int pos = 0;
    int tex = 0;
    int norm = 0;
    int face = 0;


    // open the file
    std::ifstream openOBJ;
    openOBJ.open(filename);
    
    if (!openOBJ.good())
    {
        std::cout << "Can't open OBJ file" << std::endl;
        exit(1);
    }

    // reading the file
    while(!openOBJ.eof()) 
    {

        std::string line;
        getline(openOBJ, line);
        std::string objType = line.substr(0,2);

    // vertices
        if (objType.compare("v ") == 0) 
        {
            // parse copied line
            char* first = new char[line.size()+1];
            memcpy(first, line.c_str(), line.size()+1);


            // extract the tokens
            Point3D vertex;
            strtok(first, " "); // skips past the v, vt, vn or f part

            // converting the contents of a string into a float value
            vertex.x = std::stof(std::strtok(NULL, " "));
            vertex.y = std::stof(std::strtok(NULL, " "));
            vertex.z = std::stof(std::strtok(NULL, " "));

            tempVertices.push_back(vertex);

            delete[] first;
            pos++;
        } else if (objType.compare("vn ") == 0)
        {
            char* first = new char[line.size()+1];
            memcpy(first, line.c_str(), line.size()+1);

            Vec3D normal;
            std::strtok(first, " ");

            normal.x = std::stof(std::strtok(NULL, " "));
            normal.y = std::stof(std::strtok(NULL, " "));
            normal.z = std::stof(std::strtok(NULL, " "));

            tempNormals.push_back(normal);

            delete[] first;
            norm++;

        // faces
        } else if (objType.compare("f ")== 0) 
        {
            char* first = new char[line.size()+1];
            memcpy(first, line.c_str(), line.size()+1);

            std::strtok(first, " ");
            for (int i = 0; i <= 2; i++) 
            {
                vtxIndices.push_back(std::stoi(std::strtok(NULL, " /"))); // vertices
                texIndices.push_back(std::stoi(std::strtok(NULL, " /"))); // textures
                nIndices.push_back(std::stoi(std::strtok(NULL, " /"))); // normals
            }
            delete[] first;
            face++;
        }
    }
    openOBJ.close();
    return true;
}
