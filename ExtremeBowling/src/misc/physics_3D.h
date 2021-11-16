#ifndef PHYSICS_3D_H
#define PHYSICS_3D_H

#define _USE_MATH_DEFINES
#include <cmath> 
#include <iostream>
#include <vector>

#include "mathlib_3D.h"

enum class ColType {
    box, 
    sphere,
    none
};

class Collider3D {
public:
    ColType collider_type;
    Point3D *p_pos;
    Rot3D *p_rot;
    float size_x;
    float size_y;
    float size_z;
    Vec3D offset;
    Point3D old_pos;
    Collider3D();
    Collider3D(ColType col, Point3D *p_position, Rot3D *p_rotation, float s_x, float s_y, float s_z, float off_x, float off_y, float off_z);
    Point3D calculatePos();
    Vec3D collision(Collider3D col);
private:
    //static bool collisionSpherePoint(Point3D sph_p, float rad, Point3D p);
    //static Vec3D collisionBoxPoint(Collider3D box, Point3D box_p, Point3D old_bp, Point3D p, Point3D old_p);
    static Vec3D collisionBoxBox(Collider3D box_1, Collider3D box_2);
    static Vec3D collisionBoxSphere(Collider3D box, Collider3D sph);
    static Vec3D collisionSphereSphere(Collider3D sph_1, Collider3D sph_2);
};

class PhysicsObject3D{
private:
    Point3D pos;
    Vec3D vel;
    Vec3D acc;
    Rot3D rot;
    float rot_vel;
    bool moveable;

    float surface_friction;
    float acc_friction;
    
    int id;
    Collider3D collider;
    std::vector<int> collided;       // when an object collides with another object, they can add some value to collided to know what they collided with 
public:
    PhysicsObject3D();
    PhysicsObject3D(float p_x, float p_y, float p_z, bool move = false, float f = 0);

    // getters
    Point3D getPos();
    Vec3D getVel();
    Rot3D getRot();
    bool isMoveable();
    float getSurfaceFriction();
    int getId();
    std::vector<int> getCollided();

    // setters
    void setId(int object_id);
    void setPosition(float x, float y, float z);
    void setVelocity(float x, float y, float z);
    void setRotation(float x, float y, float z, float a);

    void setMoveable(bool move);
    void setSurfaceFriction(float f);
    void setAccFriction(float f);

    void addBoxCollider(float s_x, float s_y, float s_z, float off_x, float off_y, float off_z);
    void addCubeCollider(float size, float off_x, float off_y, float off_z);
    void addSphereCollider(float size, float off_x, float off_y, float off_z);

    // modifiers
    void addAcceleration(float x, float y, float z);
    void updatePhysics(float time, bool gravity, std::vector<PhysicsObject3D *> objs = {});
    
    void reflect(Vec3D ref_normal, float scale);
    
    void collision(PhysicsObject3D *other_obj);
    void collisionImmovable(PhysicsObject3D other_obj);
    void addCollided(int id);
};





#endif