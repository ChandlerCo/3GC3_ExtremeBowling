#include "powerup.h"

PowerUp::PowerUp(float inX, float inY, float inZ, int type, int local_id) : Asset(inX, inY, inZ)
{
    this->graphics = Graphics("powerup");
    //this->type = type; //type 1 is gain a life, type 2 is increase size, type 3 is ghost mode
    this->physics.setId(type);
    this->physics.setLocalId(local_id);
    this->obj_scalar = 5;
    this->physics.addCallback(BALL, &hitBall, this);
}

void PowerUp::defaultAnimation()
{

}

void PowerUp::collisionAnimation()
{

}

int PowerUp::powerUpType()
{
    return this->physics.getId();
}

bool PowerUp::checkCollision(){
    return collided;
}

int PowerUp::hitBall(void* context, Vec3D deflection, void* obj)
{
    PowerUp* power = static_cast<PowerUp*>(context);
    
    power->collided = true;

    return 0;
}

vector<PowerUp> PowerUp::fromJson(vector<json> jsonData, float tileSize)
{
    int counter = 0;
    vector<PowerUp> powerups;
    for (json entry : jsonData)
    {
        float sX = (float)entry.find("row").value() * tileSize;
        float sZ = (float)entry.find("col").value() * tileSize;
        int pwType = entry.find("type").value();
        powerups.push_back(PowerUp(sX, tileSize, sZ, pwType, counter));
        counter += 1;
    }
    return powerups;
}