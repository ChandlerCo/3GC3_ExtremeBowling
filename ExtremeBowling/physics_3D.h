#include "mathlib_3D.h"

#ifndef PHYSICS_3D_H
#define PHYSICS_3D_H


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
        Vec3D rot;
        int id;
        Collider collider;
        vector<int> collided;       // when an object collides with another object, they can add some value to collided to know what they collided with 
    public:
        PhysicsObject3D();
        PhysicsObject3D(float p_x, float p_y, float v_x = 0, float v_y = 0, float a_x = 0, float a_y = 0);

        // getters
        Point3D getPos();
        int getId();
        vector<int> getCollided();

        // setters
        void setId(int object_id);
        void setVelocity(Vec3D new_vel);
        void setVelocity(float x, float y, float z);
        void addBoxCollider(float s_x, float s_y, float s_z, float off_x, float off_y, float off_z);
        void addCubeCollider(float size, float off_x, float off_y, float off_z);
        void addSphereCollider(float s_x, float s_y, float s_z, float off_x, float off_y, float off_z);
        void addPerfectSphereCollider(float size, float off_x, float off_y, float off_z);

        // modifiers
        void clearAcceleration();
        void addAcceleration(Vec3D new_acc);
        void addAcceleration(float x, float y, float z);
        void updatePhysics(float friction, float time);
        void collision(Object2D *otherObj);
        void collisionImmovable(Object2D otherObj);
        void addCollided(int id);
};





#endif