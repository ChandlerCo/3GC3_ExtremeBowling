#ifndef BALL_H
#define BALL_H

#include "asset.h"
#include "powerup.h"

class Ball : public Asset{
    public:
        using Asset::Asset;
        Ball(float x, float y, float z, float radius);
        void runPhysics(float time, vector<PhysicsObject3D*> world_objs);
        void activatePowerUp(PowerUp powerup);
        static int hitBoomba(void* context, Vec3D deflection, void* obj);
        static int hitSweeper(void* context, Vec3D deflection, void* obj);
        static int hitCheckpoint(void* context, Vec3D deflection, void* obj);
        static int hitPowerUp(void* context, Vec3D deflection, void* obj);
    private:
        PowerUp active_power_up;
        
};

#endif