#include <iostream>
#include "mathlib_3D.h"

Dimension3::Dimension3()
{
    x = 0;
    y = 0;
    z = 0;
}

Dimension3::Dimension3(float in_x, float in_y, float in_z)
{
    x = in_x;
    y = in_y;
    z = in_z;
}

Point3D::Point3D()
{
}

Point3D::Point3D(float in_x, float in_y, float in_z):Dimension3(in_x, in_y, in_z)
{
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

float Vec3D::quickLength()
{
    return x * x + y * y + z * z;
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

float Vec3D::dotProd(Vec3D v)
{
    return x * v.x + y * v.y + z * v.z;
}

Vec3D Vec3D::crossProd(Vec3D v)
{
    float c_x = y * v.z - z * v.y;
    float c_y = z * v.x - x * v.z;
    float c_z = x * v.y - y * v.x;

    return Vec3D(c_x, c_y, c_z);
}

// projects vector v onto this vector
Vec3D Vec3D::project(Vec3D v)
{
    return multiply(dotProd(v) / dotProd(*this));
}

Vec3D Vec3D::multiply(float scalar)
{
    return Vec3D(x * scalar, y * scalar, z * scalar);
}

Vec3D Vec3D::createVector(Point3D p_1, Point3D p_2)
{
    return Vec3D(p_2.x - p_1.x, p_2.y - p_1.y, p_2.z - p_1.z);
}

Point3D Vec3D::movePoint(Point3D source)
{
    return Point3D(source.x + x, source.y + y, source.z + z);
}

/* Rot3D
 * Stores rotation angles for x, y, z
 * Rotations are done in the order: x, y, z
 * Each rotation is done a its relative axis.
 * ie. done in the same way as
*/
Rot3D::Rot3D()
{
    angle = 0;
    axis = Vec3D(1, 0, 0);
}

Rot3D::Rot3D(float in_x, float in_y, float in_z, float in_a)
{
    angle = in_a;
    axis = Vec3D(in_x, in_y, in_z);
}

void Rot3D::rotate3D(Dimension3 *d)
{
    // rotate about x axis until rotation vector is in x-z plane
    // find angle
    float theta_x = atan2(axis.y, axis.z);

    Vec3D rot = axis.clone();
    rot3DAxisX(&rot, -theta_x);
    rot3DAxisX(d, -theta_x);
    //std::cout << d->x << " | " << d->y << " | " << d->z << std::endl;

    // rotate about y axis until rotation vector is on z axis
    // find angle
    float theta_y = atan2(rot.x, rot.z);

    rot3DAxisY(d, -theta_y);
    //std::cout << d->x << " | " << d->y << " | " << d->z << std::endl;

    // rotate vector by angle
    rot3DAxisZ(d, angle);
    //std::cout << d->x << " | " << d->y << " | " << d->z << std::endl;
    // reverse rotation about y axis
    rot3DAxisY(d, theta_y);
    //std::cout << d->x << " | " << d->y << " | " << d->z << std::endl;
    // reverse rotation about x axis
    rot3DAxisX(d, theta_x);
}

void Rot3D::rot3DAxisX(Dimension3 *d, float rad)
{
    float y = d->y;
    float z = d->z;
    d->y = cos(rad) * y - sin(rad) * z;
    d->z = sin(rad) * y + cos(rad) * z;
}
void Rot3D::rot3DAxisY(Dimension3 *d, float rad)
{
    float x = d->x;
    float z = d->z;
    d->x = cos(rad) * x + sin(rad) * z;
    d->z = -sin(rad) * x + cos(rad) * z;
}
void Rot3D::rot3DAxisZ(Dimension3 *d, float rad)
{
    float x = d->x;
    float y = d->y;
    d->x = cos(rad) * x - sin(rad) * y;
    d->y = sin(rad) * x + cos(rad) * y;
}
