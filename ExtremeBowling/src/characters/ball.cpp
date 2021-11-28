# include "ball.h"


Ball::Ball(float x, float y, float z, float radius): Asset(x, y, z)
{
    this->physics.setInteraction(Reaction::kinetic);
    this->physics.setSurfaceFriction(1);
    this->physics.addSphereCollider(radius * 2, 0, 0, 0);
    
    this->physics.setId(static_cast<int>(CharacterId::ball));

    this->physics.addCallback(static_cast<int>(CharacterId::boomba), &hitBoomba, this);
    this->physics.addCallback(static_cast<int>(CharacterId::sweeper), &hitSweeper, this);

    this->graphics = Graphics("ball");
    obj_scalar = 3;
}
void Ball::runPhysics(float time)
{
    this->physics.updatePhysics(time, true, this->scene_objs);

    // rotate ball
    Vec3D rot_axis = Vec3D(0, 1, 0).crossProd(this->physics.getVel());
    this->physics.addRotation(rot_axis.x, 0, rot_axis.z, this->physics.getVel().length()* time * 0.0072f);
}

void Ball::addSceneObject(PhysicsObject3D * new_object)
{
    this->scene_objs.push_back(new_object);
}

void Ball::activatePowerUp(PowerUp powerup)
{
    this->active_power_up = powerup;
}

void Ball::hitBoomba(void* context, Vec3D deflection)
{
    Ball* b = static_cast<Ball*>(context);
    //b->physics.setVelocity(0, 20, 0);
}

void Ball::hitSweeper(void* context, Vec3D deflection)
{
    Ball* b = static_cast<Ball*>(context);
    //b->physics.setVelocity(0, 50, 0);
}