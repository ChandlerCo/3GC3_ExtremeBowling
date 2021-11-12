#include "asset.h"
#include <string>

#ifndef POWERUP_H
#define POWERUP_H

/*
Power ups will spawn in certain areas of the map, and will not respawn unless
the map is reset. They will have a similar look to the Mario kart power up boxes. 
*/

class PowerUp : public Asset {
    private:
        /* Store type of powerups:
        - gain a life
        - speed boost
        - increase/ decrease size of bowling ball
        - become "invisible" */
        std::string type[4]; // do we need to store types as strings?
    public:
        PowerUp(float inX, float inY, float inZ);
        void defaultAnimation(); // can have box slowly rotate or hover up and down
        void collisionAnimation(); // only call this when player collides
        void powerUpType(); // will let player class know which type of power up to apply
};

#endif