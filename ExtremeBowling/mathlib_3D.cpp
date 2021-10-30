#include <math.h> 

#include "mathlib_3D.h"

Point3D::Point3D()
{
    x = 0;
    y = 0;
    z = 0;
}

Point3D::Point3D(float in_x, float in_y, float in_z)
{
    x = in_x;
    y = in_y;
    z = in_z;
}

float Point3D::distanceTo(Point3D p)
{
    return sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y) + (p.z - z) * (p.z - z));
}

float Point3D::fastDistanceTo(Point3D p)
{
    return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y) + (p.z - z) * (p.z - z);
}

Point3D Point3D::clone()
{
    return Point3D(x, y, z);
}

Vec3D::Vec3D()
{
    x = 0;
    y = 0;
    z = 0;
}

Vec3D::Vec3D(float in_x, float in_y, float in_z)
{
    x = in_x;
    y = in_y;
    z = in_z;
}

float Vec3D::length()
{
    return sqrt(x * x + y * y + z * z);
}

Vec3D Vec3D::clone()
{
    return Vec3D(x, y, z);
}

Vec3D Vec3D::addVec(Vec3D p)
{
    return Vec3D(x + p.x, y + p.y, z + p.z);
}

Vec3D Vec3D::normalize()
{
    float len = length();
    if (len == 0)
        return Vec3D();
    return Vec3D(x / len, y / len, z / len);
}

Vec3D Vec3D::multiply(float scalar)
{
    return Vec3D(x * scalar, y * scalar, z * scalar);
}

Vec3D Vec3D::createVector(Point3D p_1, Point3D p_2)
{
    return Vec3D(p_2.x - p_1.x, p_2.y - p_1.y, , p_2.z - p_1.z);
}

Point3D Vec3D::movePoint(Point3D source)
{
    return Point3D(source.x + x, source.y + y, source.z + z);
}