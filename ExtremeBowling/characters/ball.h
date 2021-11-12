#include "misc/physics_3D.h"
#include "misc/objLoader.h"
#include "asset.h"

class Ball : public Asset{
    public:
        void accelerate(float x, float y, float z);
};