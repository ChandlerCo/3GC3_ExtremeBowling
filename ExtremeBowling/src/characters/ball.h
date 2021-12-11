#ifndef BALL_H
#define BALL_H

#include "asset.h"
#include "powerup.h"
#include "character_ids.h"

class Ball : public Asset{
    public:
        using Asset::Asset;
        Ball(float x, float y, float z, float radius);
        void init();
        void runPhysics(float time, vector<PhysicsObject3D*> &world_objs);
        void activatePowerUp(PowerUp powerup); // needs to be redefined
        void clearPowerUp(); //needs to be defined
        void jump();
        bool respawn();
        bool finished();
        int getLives();
        
        static int hitBoomba(void* context, Vec3D deflection, void* obj);
        static int hitSweeper(void* context, Vec3D deflection, void* obj);
        static int hitCheckpoint(void* context, Vec3D deflection, void* obj);
        static int hitFinish(void* context, Vec3D deflection, void* obj);
        static int hitFloor(void* context, Vec3D deflection, void* obj);
    private:
        Point3D lastCheckpoint;
        int lives;
        float radius;
        int powerUpType;
        bool finishedStatus;
        
};

#endif