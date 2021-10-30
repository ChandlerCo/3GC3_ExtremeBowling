#ifndef MATHLIB_3D_H
#define MATHLIB_3D_H

class Point3D {
public:
    Point3D();
    Point3D(float in_x, float in_y, float m_z);
    float x;
    float y;
    float z;

    float distanceTo(Point3D p);
    float fastDistanceTo(Point3D p);
    Point3D clone();
};

class Vec3D {
public:
    Vec3D();
    Vec3D(float in_x, float in_y, float m_z);
    float x;
    float y;
    float z;
    float length();
    Vec3D clone();
    Vec3D addVec(Vec3D p);
    Vec3D normalize();
    Vec3D multiply(float scalar);
    Point3D movePoint(Point3D source);

    static Vec3D createVector(Point3D p_1, Point3D p_2);
};

#endif
