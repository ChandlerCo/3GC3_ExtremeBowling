#ifndef BALL_H
#define BALL_H

#include "asset.h"
#include "powerup.h"

class Ball : public Asset{
    public:
        using Asset::Asset;
        Ball(float x, float y, float z, float radius);
        void runPhysics(float time);
        void addSceneObject(PhysicsObject3D * new_object);
        void activatePowerUp(PowerUp powerup);
        static void hitBoomba(void* context, Vec3D deflection);
        static void hitSweeper(void* context, Vec3D deflection);
    private:
        vector<PhysicsObject3D *> scene_objs;
        PowerUp active_power_up;
        
};

#endif