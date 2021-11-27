#include "sweeper.h"

Sweeper::Sweeper(float inX, float inY, float inZ) : Enemy(inX, inY, inZ)
{
    this->moveZBy = 1;
    this->graphics = Graphics("pin"); //we change this later

    physics.addBoxCollider(10, 10, 30, 0, 0, 15);
    physics.setId(static_cast<int>(CharacterId::sweeper));
}

void Sweeper::animate() 
{
    //std::cout << "sweeper animate" << std::endl;

    if (physics.getPos().distanceTo(Point3D(inX, inY, inZ)) >= 50) {
        physics.addRelativeRotation(0, 1, 0, 180); 
        moveZBy = -moveZBy;
    }

    physics.setPosition(physics.getPos().x, physics.getPos().y, physics.getPos().z + moveZBy);

    // Update physics?
}