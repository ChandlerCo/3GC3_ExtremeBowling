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

// texture variables
static GLuint textures[3];
static GLubyte *carpet, *marble, *rock;
static int width, height, max;

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
/*
static GLubyte *LoadPPM(char *file, int *width, int *height, int *max)
{
    GLubyte *img;
    FILE *fd;
    int n, m;
    int k, nm;
    char c;
    int i;
    char b[100];
    float s;
    int red, green, blue;

    fd = fopen(file, "r");
    fscanf(fd, "%[^\n] ", b);
    if (b[0] != 'P' || b[1] != '3')
    {
        exit(0);
    }
    fscanf(fd, "%c", &c);
    while (c == '#')
    {
        fscanf(fd, "%[^\n] ", b);
        fscanf(fd, "%c", &c);
    }
    ungetc(c, fd);
    fscanf(fd, "%d %d %d", &n, &m, &k);

    nm = n * m;

    img = (GLubyte *)(malloc(3 * sizeof(GLuint) * nm));

    s = 255.0 / k;

    for (i = 0; i < nm; i++)
    {
        fscanf(fd, "%d %d %d", &red, &green, &blue);
        img[3 * nm - 3 * i - 3] = red * s;
        img[3 * nm - 3 * i - 2] = green * s;
        img[3 * nm - 3 * i - 1] = blue * s;
    }

    fclose(fd);

    *width = n;
    *height = m;
    *max = k;

    return img;
}

static void initTexture()
{
	// Enable texturing
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glGenTextures(3, textures);

	// Set up first texture for carpet
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	carpet = LoadPPM((char*)"carpet.ppm", &width, &height, &max);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, carpet);

	// Set up second texture for marble
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	marble = LoadPPM((char*)"marble.ppm", &width, &height, &max);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, marble);

	// Set up third texture for rock
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	rock = LoadPPM((char*)"rock.ppm", &width, &height, &max);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, rock);

	// Remove texture binding for now
	glBindTexture(GL_TEXTURE_2D, 0);
}
*/
#endif