#ifndef BALL_H
#define BALL_H

#include "asset.h"

class Ball : public Asset{
    public:
        Ball(float x, float y, float z, float radius);
        void runPhysics(float time);
        using Asset::Asset;
        void addSceneObject(PhysicsObject3D * new_object);
    private:
        vector<PhysicsObject3D *> scene_objs;
};

#endif