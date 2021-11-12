#ifndef BALL_H
#define BALL_H

#include "asset.h"

class Ball : public Asset{
    public:
        void accelerate(float x, float y, float z);
        using Asset::Asset;
};

#endif