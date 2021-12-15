 #include "graphics.h"
#include <iostream>

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



using namespace std;

GLuint Graphics::pinTexture = 0;
GLuint Graphics::sweeperTexture = 0;

Graphics::Graphics(){}

Graphics::Graphics(string filename, Material m){
    loadObj(filename, 
            this->vertices,
            this->uvs,
            this->normals);
    mat = m;
    this->texture = NO_TEXTURE;


}

bool Graphics::loadObj(string filename,
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
        //char tmp[256];
        printf("Impossible to open file %s from\n", filename.c_str());
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

    fclose(file);


    return true;
}

void Graphics::setMaterial(Material m)
{
    mat = m;
}

void Graphics::setTexture(int textureId)
{
    switch(textureId)
    {
        case PIN_TEXTURE:
            this->texture = pinTexture;
            break;
        case SWEEPER_TEXTURE:
            this->texture = sweeperTexture;
            break;
        default:
            this->texture = 0;
            break;
    }
}

GLuint Graphics::loadBMP(string filename){ // taken from tutorial website
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;

    unsigned char * data;

    filename = "src/objects/" + filename + ".bmp";
    FILE * file = fopen(filename.c_str(), "rb");

    if (!file){printf("Image could not be opened\n"); return 0;}

    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return false;
    }
    if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return false;
    }

    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);


    if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos==0)      dataPos=54; // The BMP header is done that way


    std::cout << "width " << width << std::endl;
    std::cout << "height " << height << std::endl;
    // Create a buffer
    data = new unsigned char [imageSize];

    // Read the actual data from the file into the buffer
    fread(data,1,imageSize,file);

    //Everything is in memory now, the file can be closed
    fclose(file);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;

}

void Graphics::loadTextures()
{   
    
    
    pinTexture = loadBMP("PinCoat");
    sweeperTexture = loadBMP("SweeperCoat");
}

// GLubyte* Graphics::LoadPPM(char* file, int* width, int* height, int* max)
// {
//     GLubyte* img;
//     FILE *fd;
//     int n, m;
//     int  k, nm;
//     char c;
//     int i;
//     char b[100];
//     float s;
//     int red, green, blue;
    
//     fd = fopen(file, "r");
//     fscanf(fd,"%[^\n] ",b);
//     if(b[0]!='P'|| b[1] != '3')
//     {
        
//         exit(0);
//     }

//     fscanf(fd, "%c",&c);
//     while(c == '#')
//     {
//         fscanf(fd, "%[^\n] ", b);
//         printf("%s\n",b);
//         fscanf(fd, "%c",&c);
//     }
//     ungetc(c,fd);
//     fscanf(fd, "%d %d %d", &n, &m, &k);
    
//     printf("%d rows  %d columns  max value= %d\n",n,m,k);
    
//     nm = n*m;
    
//     img = (GLubyte*)(malloc(3*sizeof(GLuint)*nm));
    
//     s=255.0/k;
    
    
//     for(i=0;i<nm;i++)
//     {
//         fscanf(fd,"%d %d %d",&red, &green, &blue );
//         img[3*nm-3*i-3]=red*s;
//         img[3*nm-3*i-2]=green*s;
//         img[3*nm-3*i-1]=blue*s;
//     }
//     fclose(fd);
    
//     *width = n;
//     *height = m;
//     *max = k;
    
//     return img;
// }

// void Graphics::initTextures()
// {
	
// 	glEnable(GL_TEXTURE_2D);
// 	glEnable(GL_TEXTURE_GEN_S);
// 	glEnable(GL_TEXTURE_GEN_T);
// 	glGenTextures(3, &texture);

// 	glBindTexture(GL_TEXTURE_2D, texture);
// 	GLubyte* wood = LoadPPM((char*)"../wood.ppm",&width1, &height1, &max1);
// 	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1,0, GL_RGB, GL_UNSIGNED_BYTE, wood);
// 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

// }




void Graphics::displayAsset(Rot3D r)
{
    
    if(texture != NO_TEXTURE){
        glBindTexture(GL_TEXTURE_2D, texture);
    } else {
        glBindTexture(GL_TEXTURE_2D, NO_TEXTURE);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat.amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat.diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat.spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat.shine);

    glPushMatrix();
        glRotatef(r.getAngle(), r.getX(), r.getY(), r.getZ());
        glBegin(GL_TRIANGLES);
        // render each triangle
        for (long unsigned int i = 0; i < this->vertices.size() ; i++) {
            glNormal3f(this->normals.at(i).x, this->normals.at(i).y, this->normals.at(i).z);
            if(texture != NO_TEXTURE){
                glTexCoord2f(uvs.at(i).x,uvs.at(i).y);
            }
            glVertex3f(this->vertices.at(i).x, this->vertices.at(i).y, this->vertices.at(i).z);
        }
        glEnd();
    glPopMatrix();

}