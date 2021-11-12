#ifndef MATHLIB_3D_H
#define MATHLIB_3D_H

#include <math.h> 

class Dimension3 {
public:
    float x;
    float y;
    float z;
    Dimension3();
    Dimension3(float in_x, float in_y, float in_z);
}

class Point3D : public Dimension3 {
public:
    Point3D();
    Point3D(float in_x, float in_y, float in_z);


    float distanceTo(Point3D p);
    float fastDistanceTo(Point3D p);
    Point3D clone();
};

class Vec3D : public Dimension3{
public:
    Vec3D();
    Vec3D(float in_x, float in_y, float in_z);
    float length();
    Vec3D clone();
    Vec3D addVec(Vec3D p);
    Vec3D normalize();
    float dotProd(Vec3D v);
    Vec3D crossProd(Vec3D v);
    Vec3D project(Vec3D v);
    Vec3D multiply(float scalar);
    Point3D movePoint(Point3D source);

    static Vec3D createVector(Point3D p_1, Point3D p_2);
};

class Rot3D {
public:
    float angle;
    Vec3D axis;

    Rot3D();
    Rot3D(float in_x, float in_y, float in_z, float in_a);

    void rot3D(Dimension3 *d);

    static void rot3DAxisX(Dimension3 *d, float rad);
    static void rot3DAxisY(Dimension3 *d, float rad);
    static void rot3DAxisZ(Dimension3 *d, float rad);
};

#endif
