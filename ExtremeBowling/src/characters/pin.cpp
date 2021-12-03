#include "pin.h"

Pin::Pin(float inX, float inY, float inZ, int local_id) : Asset(inX, inY, inZ)
{
    this->graphics = Graphics("pin");
    this->physics.setId(PIN);
    this->physics.setLocalId(local_id);

    this->physics.addCallback(BALL, &hitBall, this);
}

void Pin::collisionAnimation()
{

}

bool Pin::checkCollision(){
    return collided;
}

int Pin::hitBall(void* context, Vec3D deflection, void* obj)
{
    Pin* pin = static_cast<Pin*>(context);
    
    pin->collided = true;

    return 0;
}

vector<Pin> Pin::fromJson(vector<json> jsonData, float tileSize)
{
    int counter = 0;
    vector<Pin> pins;
    for (json entry : jsonData)
    {
        float sX = (float)entry.find("row").value() * tileSize;
        float sZ = (float)entry.find("col").value() * tileSize;
        pins.push_back(Pin(sX, tileSize, sZ, counter));
        counter += 1;
    }
    return pins;
}