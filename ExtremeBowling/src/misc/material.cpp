#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

#ifndef MATERIAL
#define MATERIAL

// Enum for material names
enum Material 
{
    CYAN_PLASTIC, PERL, TIN, JADE, OBSIDIAN, RED_RUBBER
};

// will add texture variables here

static void setMatAmbience(float x, float y, float z, float a)
{
    float amb[4] = {x, y, z, a};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
}

static void setMatDif(float x, float y ,float z, float a)
{
    float dif[4] = {x,y,z,a};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
}

static void setMatSpc(float x, float y, float z, float a){
    float spec[4] = {x,y,z,a};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
}

static void setMatShine(float shine)
{
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}


// plain temp color for objects to be drawn in
static void setColor(float r, float g, float b)
{
    setMatAmbience(r,g,b,1);
    setMatDif(r,g,b,1);
    setMatSpc(r,g,b,1);
    setMatShine(2);
}


#endif