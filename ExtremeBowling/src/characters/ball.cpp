# include "ball.h"


Ball::Ball(float x, float y, float z, float radius): Asset(x, y ,z)
{
    this->physics.addSphereCollider(radius * 2, 0, 0, 0);
}
void Ball::runPhysics(float time)
{
    this->physics.updatePhysics(time, true, this->scene_objs);

}
