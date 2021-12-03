#include "asset.h"
#include <string>

#ifndef POWERUP_H
#define POWERUP_H

/*
Power ups will spawn in certain areas of the map, and will not respawn unless
the map is reset. They will have a similar look to the Mario kart power up boxes. 
*/

class PowerUp : public Asset {
    protected:
        bool collided;
    private:
        /* Store type of powerups:
        create id, load obj based on id, behaviour based on id
        - gain a life
            +1 to the life score
        - increase size of bowling ball
            gl scale
            adjust bounding box size

        - become "invisible" 
            alpha blending
            ghost mode in physics
        
            */
        int type;
    public:
        PowerUp(float inX, float inY, float inZ, int type, int local_id);
        void defaultAnimation(); // can have box slowly rotate or hover up and down
        void collisionAnimation(); // only call this when player collides
        int powerUpType(); // will let player class know which type of power up to apply
        using Asset::Asset;
        bool checkCollision();
        static int hitBall(void* context, Vec3D deflection, void* obj);
        static vector<PowerUp> fromJson(vector<json> jsonData, float tileSize);
};

#endif