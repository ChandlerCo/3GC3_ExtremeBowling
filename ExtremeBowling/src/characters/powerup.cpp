#include "powerup.h"

PowerUp::PowerUp(float inX, float inY, float inZ, int type, int local_id) : Asset(inX, inY, inZ)
{
    this->graphics = Graphics("powerup");
    this->physics.addCubeCollider(8, 0, 0, 0);
    this->physics.setInteraction(Reaction::ghost);
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

vector<PowerUp*> PowerUp::fromJson(vector<json> jsonData, float tileSize)
{
    int counter = 0;
    vector<PowerUp*> powerups;
    for (json entry : jsonData)
    {
        float sX = (float)entry.find("col").value() * tileSize;
        float sZ = (float)entry.find("row").value() * tileSize;
        int pwType = entry.find("type").value();
        powerups.push_back(new PowerUp(sX, tileSize, sZ, pwType, counter));
        counter += 1;
    }
    return powerups;
}