#include "powerup.h"

PowerUp::PowerUp(float inX, float inY, float inZ, int type, int local_id) : Asset(inX, inY, inZ)
{
    this->physics.addCubeCollider(8, 0, 0, 0);
    this->physics.setInteraction(Reaction::ghost);
    this->physics.setId(type);
    this->physics.setLocalId(local_id);
    this->physics.addCallback(BALL, &hitBall, this);

    setGraphics();
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

void PowerUp::setGraphics()
{
    this->obj_scalar = 5;
    this->graphics = Graphics("powerup");
    switch (physics.getId())
    {
        case ADD_LIVES:
            // set graphics to be checkpoint tile (maybe change texture used?)
            graphics.setMaterial(RUBY);
            break;
        case HALF_SIZE:
            // set graphics to be checkpoint tile (maybe change texture used?)
            graphics.setMaterial(EMERALD);
            break;
        case GHOST_MODE:
            // set graphics to be normal tile
            graphics.setMaterial(WHITE_RUBBER);
            break;
    }
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