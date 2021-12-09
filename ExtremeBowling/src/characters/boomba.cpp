#include "boomba.h"

Boomba::Boomba(float inX, float inY, float inZ, float endX, float endY, float endZ, int id) : Enemy(inX, inY, inZ, endX, endY, endZ, id)
{
    speed = 0.5;

    // initial rotation
    this->physics.setRotation(0, 1, 0, -90); // may have to change this? 
    this->physics.addSphereCollider(3, -0.25, 1.75, 0);
    this->physics.setId(BOOMBA);
    this->physics.setLocalId(id);

    this->physics.addCallback(BALL, &hitBall, this);

    this->graphics = Graphics("boomba");
    this->obj_scalar = 0.5;

    // this->moveXBy = 0.5;
}

void Boomba::animate()
{
    //std::cout << "boomba animate" << std::endl;

    /* 
    in main, we'll have a glutTimerFunc or smth,
    and we'll call:
        for enemy in our vector of enemies:
            enemy.animate();
    */
   
    /* 
    so we want to update the position of the boomba
    here in this method. Want it to move left and right
    */

    /* 
    - Deviate only a certain distance from initial position
    - Rotate 90 degrees to left, then add acceleration
    - If boomba position passes certain limit, rotate 180 
    degrees, and start moving to the right
    */

    // move boomba in forward direction until it reaches certain point
    // once limit reached, rotate 180, and move forward again until next limit reached

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


    // if (physics.getPos().distanceTo(Point3D(inX, inY, inZ)) >= 10) {
    //     physics.addRelativeRotation(0, 1, 0, 180);
    //     moveXBy = -moveXBy;
    // }

    // physics.setPosition(physics.getPos().x + moveXBy, physics.getPos().y, physics.getPos().z);

    // if (physics.getRot().getAngle() > 0) {
    //     physics.setPosition(physics.getPos().x + moveXBy, physics.getPos().y, physics.getPos().z);
    // }

    // if (physics.getRot().getAngle() < 0) {
    //     physics.setPosition(physics.getPos().x - moveXBy, physics.getPos().y, physics.getPos().z);
    // }
    
    // Call update physics?
}

void Boomba::collisionAnimation()
{
    
}

int Boomba::hitBall(void* context, Vec3D deflection, void* obj)
{
    Boomba* e = static_cast<Boomba*>(context);
    PhysicsObject3D* ball = static_cast<PhysicsObject3D*>(obj);
    
    e->collided = true;

    return 1;   // forces boomba to have a collision
}

vector<Boomba*> Boomba::fromJson(vector<json> jsonData, float tileSize)
{
    int counter = 0;
    vector<Boomba*> boombas;
    for (json entry : jsonData)
    {
        float sX = (float)entry.find("start col").value() * tileSize;
        float sZ = (float)entry.find("start row").value() * tileSize;
        float eX = (float)entry.find("end col").value() * tileSize;
        float eZ = (float)entry.find("end row").value() * tileSize;
        boombas.push_back(new Boomba(sX, tileSize, sZ, eX, tileSize, eZ, counter));
        counter += 1;
    }
    return boombas;
}