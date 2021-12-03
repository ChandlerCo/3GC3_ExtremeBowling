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
        - increase/ decrease size of bowling ball
            gl scale
            adjust bounding box size

        - become "invisible" 
            alpha blending
            ghost mode in physics
        
        -4th powerup 
            reset powerup
            */
        std::string type[4]; // do we need to store types as strings?
    public:
        // PowerUp(float inX, float inY, float inZ);
        void defaultAnimation(); // can have box slowly rotate or hover up and down
        void collisionAnimation(); // only call this when player collides
        void powerUpType(); // will let player class know which type of power up to apply
        using Asset::Asset;
        bool checkCollision();
};

#endif