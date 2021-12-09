#include "sweeper.h"

Sweeper::Sweeper(float inX, float inY, float inZ, float endX, float endY, float endZ, int id) : Enemy(inX, inY, inZ, endX, endY, endZ, id)
{
    speed = 1.0;

    //this->moveZBy = 1;
    this->graphics = Graphics("pin"); //we change this later

    this->physics.addBoxCollider(10, 10, 30, 0, 0, 15);
    this->physics.setId(SWEEPER);
    this->physics.setLocalId(id);

    this->physics.addCallback(BALL, &hitBall, this);
}

void Sweeper::animate() 
{
    //std::cout << "sweeper animate" << std::endl;

    if (physics.getPos().distanceTo(startPos) >= startPos.distanceTo(endPos)) {
        physics.addRelativeRotation(0, 1, 0, 180);
        movingToEnd = false;
    } else if (physics.getPos().distanceTo(endPos) >= endPos.distanceTo(startPos)) {
        physics.addRelativeRotation(0, 1, 0, 180);
        movingToEnd = true;
    }

    if (movingToEnd) { 
        physics.setPosition(physics.getPos().x + speed*forwardDir.x, physics.getPos().y + speed*forwardDir.y, physics.getPos().z + speed*forwardDir.z);
    } else {
        physics.setPosition(physics.getPos().x + speed*backwardDir.x, physics.getPos().y + speed*backwardDir.y, physics.getPos().z + speed*backwardDir.z);
    }

    // if (physics.getPos().distanceTo(Point3D(inX, inY, inZ)) >= 50) {
    //     physics.addRelativeRotation(0, 1, 0, 180); 
    //     moveZBy = -moveZBy;
    // }

    // physics.setPosition(physics.getPos().x, physics.getPos().y, physics.getPos().z + moveZBy);

    // Update physics?
}

int Sweeper::hitBall(void* context, Vec3D deflection, void* obj)
{
    Sweeper* e = static_cast<Sweeper*>(context);
    
    e->collided = true;

    return 0;
}

vector<Sweeper*> Sweeper::fromJson(vector<json> jsonData, float tileSize)
{
    int counter = 0;
    vector<Sweeper*> sweepers;
    for (json entry : jsonData)
    {
        float sX = (float)entry.find("start col").value() * tileSize;
        float sZ = (float)entry.find("start row").value() * tileSize;
        float eX = (float)entry.find("end col").value() * tileSize;
        float eZ = (float)entry.find("end row").value() * tileSize;
        sweepers.push_back(new Sweeper(sX, tileSize, sZ, eX, tileSize, eZ, counter));
        counter += 1;
    }
    return sweepers;
}