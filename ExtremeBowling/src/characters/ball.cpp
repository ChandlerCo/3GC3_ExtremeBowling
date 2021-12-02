# include "ball.h"
# include <iostream>

Ball::Ball(float x, float y, float z, float radius): Asset(x, y, z)
{
    this->physics.setInteraction(Reaction::kinetic);
    this->physics.setSurfaceFriction(1);
    this->physics.addSphereCollider(radius * 2, 0, 0, 0);
    
    this->physics.setId(static_cast<int>(CharacterId::ball));

    this->physics.addCallback(static_cast<int>(CharacterId::boomba), &hitBoomba, this);
    this->physics.addCallback(static_cast<int>(CharacterId::sweeper), &hitSweeper, this);
    this->physics.addCallback(static_cast<int>(CharacterId::checkpoint), &hitCheckpoint, this);

    this->graphics = Graphics("ball");
    obj_scalar = 3;
    this->lives = 3;
}

void Ball::runPhysics(float time, vector<PhysicsObject3D*> world_objs)
{
    this->physics.updatePhysics(time, true, world_objs);

    // rotate ball
    Vec3D rot_axis = Vec3D(0, 1, 0).crossProd(this->physics.getVel());
    this->physics.addRotation(rot_axis.x, 0, rot_axis.z, this->physics.getVel().length()* time * 0.0072f);
}

void Ball::activatePowerUp(PowerUp powerup)
{
    this->active_power_up = powerup;
}

void Ball::jump(){
    this->physics.addVelocity(0,50,0);
}

int Ball::hitBoomba(void* context, Vec3D deflection, void* obj)
{
    Ball* b = static_cast<Ball*>(context);
    PhysicsObject3D* other = static_cast<PhysicsObject3D*>(obj);
    //b->physics.setVelocity(0, 20, 0);
    // if invincible, return -1

    return 0;
}

int Ball::hitSweeper(void* context, Vec3D deflection, void* obj)
{
    Ball* b = static_cast<Ball*>(context);
    PhysicsObject3D* other = static_cast<PhysicsObject3D*>(obj);
    //b->physics.setVelocity(0, 50, 0);

    return 0;
}

int Ball::hitCheckpoint(void* context, Vec3D deflection, void* obj)
{
    Ball* b = static_cast<Ball*>(context);
    PhysicsObject3D* other = static_cast<PhysicsObject3D*>(obj);
    // set ball's last checkpoint to obj position
    
    return 0;
}

int Ball::hitPowerUp(void* context, Vec3D deflection, void* obj)
{
    Ball* b = static_cast<Ball*>(context);
    PhysicsObject3D* other = static_cast<PhysicsObject3D*>(obj);

    return 0;
}
