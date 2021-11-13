#include "asset.h"

#ifndef PIN_H
#define PIN_H

/* 
Pins will spawn in certain areas of the map, and will not respawn unless
the map is reset. 
*/

class Pin : public Asset {
    public:
        // Pin(float inX, float inY, float inZ);

        void collisionAnimation();
        using Asset::Asset;
};

#endif