#ifndef PHYSICS_3D_H
#define PHYSICS_3D_H

#include <math.h> 
#include <iostream>

#include "mathlib_3D.h"

enum ColType {
    box, 
    sphere
};

struct Collider {
    colType collider_type;
    float size_x;
    float size_y;
    float size_z;
    float offset_x;
    float offset_y;
    float offset_z;
}

class PhysicsObject3D{
    private:
        Point3D pos;
        Vec3D vel;
        Vec3D acc;
        Rot3D rot;
        float rot_vel;
        
        int id;
        Collider collider;
        vector<int> collided;       // when an object collides with another object, they can add some value to collided to know what they collided with 
    public:
        PhysicsObject3D();
        PhysicsObject3D(float p_x, float p_y, float p_z);

        // getters
        Point3D getPos();
        Vec3D getVel();
        Rot3D getRot();
        int getId();
        vector<int> getCollided();

        // setters
        void setId(int object_id);
        void setVelocity(float x, float y, float z);
        void setRotation(float x, float y, float z, float a);

        void addBoxCollider(float s_x, float s_y, float s_z, float off_x, float off_y, float off_z);
        void addCubeCollider(float size, float off_x, float off_y, float off_z);
        void addSphereCollider(float size, float off_x, float off_y, float off_z);

        // modifiers
        void addAcceleration(float x, float y, float z);
        void updatePhysics(float friction, float time);
        void reflect(Vec3D ref_normal, float scale);
        void collision(Object2D *otherObj);
        void collisionImmovable(Object2D otherObj);
        void addCollided(int id);
};





#endif