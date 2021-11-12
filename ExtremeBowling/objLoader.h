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
        // vectors and faces
        std::vector<std::vector<float>*> *v = new std::vector<std::vector<float>*>;
        std::vector<std::vector<int>*>   *f    = new std::vector<std::vector<int>*>;
        std::vector<std::string>* split (std::string line, char sep); 
        float convert(std::string line);
        float *getNormal(float **c1, float **c2, float **c3); //calculate normal
};




#endif