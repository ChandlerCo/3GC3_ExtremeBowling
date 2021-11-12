#ifndef LOADOBJ_H
#define LOADOBJ_H
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

class loadObj
{
    public:
        loadObj(std::string filepath);  
        void drawObj(); //drawing


    private:
        std::string filepath="";
        // vertices and faces
        std::vector<std::vector<float>*> *v = new std::vector<std::vector<float>*>; //verticies
        std::vector<std::vector<int>*>   *f    = new std::vector<std::vector<int>*>; //faces
        std::vector<std::string>* split (std::string line, char sep); //split string
        float convert(std::string line); //turns a string into a float
        float *getNormal(float **c1, float **c2, float **c3); //calculate normal
};




#endif