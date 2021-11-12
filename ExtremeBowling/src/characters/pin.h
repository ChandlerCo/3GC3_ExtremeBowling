#include "physics_3D.h"

#ifndef PIN_H
#define PIN_H

/* 
Pins will spawn in certain areas of the map, and will not respawn unless
the map is reset. 
*/

class Pin {
    private:
        PhysicsObject3D powerUpPhysics;
        // Mesh *pinMesh;
        // Texture pinTexture;
    public:
        float getX();
        float getY();
        float getZ();

        void collisionAnimation(); // only call this when player collides 
};

#endif