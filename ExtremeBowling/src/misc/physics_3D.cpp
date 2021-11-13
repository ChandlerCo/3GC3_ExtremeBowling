#include "physics_3D.h"

#define GRAVITY (-9.81)
#define MAX_SPD 1000
#define ZERO 0.0000001

Collider3D::Collider3D()
{
    collider_type = ColType::sphere;
    p_pos = NULL;
    p_rot = NULL;
    size_x = 0;
    size_y = 0;
    size_z = 0;
    offset = Vec3D(0, 0, 0);
    old_pos = Point3D(0, 0, 0);
}

Collider3D::Collider3D(ColType col, Point3D *p_position, Rot3D *p_rotation, float s_x, float s_y, float s_z, float off_x, float off_y, float off_z)
{
    collider_type = col;
    p_pos = p_position;
    p_rot = p_rotation;
    size_x = s_x;
    size_y = s_y;
    size_z = s_z;
    offset = Vec3D(off_x, off_y, off_z);
    old_pos = calculatePos();
}

Point3D Collider3D::calculatePos()
{
    Vec3D rot_offset = offset.clone();
    p_rot->rotate3D(&rot_offset);
    return rot_offset.movePoint(*p_pos);
}

Vec3D Collider3D::collision(Collider3D col)
{
    if (collider_type == ColType::box)
    {
        if (col.collider_type == ColType::box)
            return collisionBoxBox(*this, col);
        else
            return collisionBoxSphere(*this, col);
    }
    else if (col.collider_type == ColType::box)
    {
        //std::cout << "colliding with box\n";
        return collisionBoxSphere(col, *this).multiply(-1);
    }
    return collisionSphereSphere(*this, col);
}

/*
bool Collider3D::collisionSpherePoint(Point3D sph_p, float rad, Point3D p)
{
    return Vec3D::createVector(sph_p, p).length() < rad;
}
Vec3D Collider3D::collisionBoxPoint(Collider3D box, Point3D box_p, Point3D old_bp, Point3D p, Point3D old_p)
{
    Vec3D b_to_p = Vec3D::createVector(box_p, p);
}
*/
Vec3D Collider3D::collisionBoxBox(Collider3D box_1, Collider3D box_2)
{
    // check distance
    // check each corner on each box
    Point3D pos_1 = box_1.calculatePos();
    Point3D pos_2 = box_2.calculatePos();
    Vec3D b_to_b = Vec3D::createVector(pos_1, pos_2);
    float contact_length = std::max(std::max(box_1.size_x, box_1.size_y), box_1.size_z) + std::max(std::max(box_2.size_x, box_2.size_y), box_2.size_z);
    if (b_to_b.length() < ZERO)
        return Vec3D(1, 1, 1);
    if (b_to_b.length() < contact_length)
        return b_to_b;
    return Vec3D();
}
Vec3D Collider3D::collisionBoxSphere(Collider3D box, Collider3D sph)
{
    Point3D pos_box = box.calculatePos();
    Point3D pos_sph = sph.calculatePos();
    Vec3D b_to_s = Vec3D::createVector(pos_box, pos_sph);

    float rad = sph.size_x / 2;

    float contact_length = rad + std::max(std::max(box.size_x, box.size_y), box.size_z);
    //std::cout << b_to_s.length() << " | " << contact_length << " colliding with box\n";
    if (b_to_s.length() < contact_length)
    {
        if (b_to_s.length() <= ZERO)
            return Vec3D(1, 1, 1);

        // get axis for box
        Vec3D x_axis = Vec3D(box.size_x / 2, 0, 0);
        box.p_rot->rotate3D(&x_axis);
        Vec3D y_axis = Vec3D(0, box.size_y / 2, 0);
        //std::cout << y_axis.x << " | " << y_axis.y << " | " << y_axis.z << std::endl;
        box.p_rot->rotate3D(&y_axis);
        //std::cout << y_axis.x << " | " << y_axis.y << " | " << y_axis.z << std::endl;
        Vec3D z_axis = Vec3D(0, 0, box.size_z / 2);
        box.p_rot->rotate3D(&z_axis);

        float delta_x = x_axis.project(b_to_s).length();
        float delta_y = y_axis.project(b_to_s).length();
        float delta_z = z_axis.project(b_to_s).length();

        //std::cout << delta_x << " | " << delta_y << " | " << delta_z << " colliding with box\n";

        // check if colliding
        // sphere center is within box
        if (delta_x < box.size_x / 2 && delta_y < box.size_y / 2 && delta_z < box.size_z / 2)
        {
            // complicated reflection - need to find where previous sphere position was
            // placeholder: use closest face
            //std::cout << rad + (box.size_y / 2) - delta_y << " placeholder\n";
            float max_delta = std::max(std::max(delta_x, delta_y), delta_z);
            if (max_delta == delta_x)
            {
                if (x_axis.dotProd(b_to_s) > 0)
                    return x_axis.normalize().multiply(rad + box.size_x / 2 - delta_x);
                else
                    return x_axis.normalize().multiply(delta_x - rad - box.size_x / 2);
            }
            else if (max_delta == delta_y)
            {
                if (x_axis.dotProd(b_to_s) > 0)
                    return x_axis.normalize().multiply(rad + box.size_x / 2 - delta_x);
                else
                    return x_axis.normalize().multiply(delta_x - rad - box.size_x / 2);
            }
            else if (max_delta == delta_z)
            {
                if (x_axis.dotProd(b_to_s) > 0)
                    return x_axis.normalize().multiply(rad + box.size_x / 2 - delta_x);
                else
                    return x_axis.normalize().multiply(delta_x - rad - box.size_x / 2);
            }
            return y_axis.normalize().multiply(rad + (box.size_y / 2) - delta_y);
        }
        
        // if sphere center is within box on two axis
        if (delta_x < box.size_x / 2 && delta_y < box.size_y / 2) // front/back
        {
            if (delta_z < rad + box.size_z / 2)
            {
                if (z_axis.dotProd(b_to_s) > 0)
                    return z_axis.normalize().multiply(rad + box.size_z / 2 - delta_z);
                else
                    return z_axis.normalize().multiply(delta_z - rad - box.size_z / 2);
            }
                
            return Vec3D();
        }
        if (delta_x < box.size_x / 2 && delta_z < box.size_z / 2)
        {
            if (delta_y < rad + box.size_y / 2) // top/bottom
            {
                if (y_axis.dotProd(b_to_s) > 0)
                    return y_axis.normalize().multiply(rad + box.size_z / 2 - delta_y);
                else
                    return y_axis.normalize().multiply(delta_y - rad - box.size_z / 2);
            }
                
            return Vec3D();
        }
        if (delta_y < box.size_y / 2 && delta_z < box.size_z / 2)
        {
            if (delta_x < rad + box.size_x / 2) // left/right
            {
                if (x_axis.dotProd(b_to_s) > 0)
                    return x_axis.normalize().multiply(rad + box.size_x / 2 - delta_x);
                else
                    return x_axis.normalize().multiply(delta_x - rad - box.size_x / 2);
            }
            return Vec3D();
        }
        // TODO
        // check collision with edges and corner
        // for now, dont check
        return Vec3D();
        
        /*
        Point3D f_t_r = x_axis.addVec(y_axis.addVec(z_axis)).movePoint(Point3D());
        Point3D f_t_l = x_axis.multiply(-2).movePoint(f_t_r);
        Point3D f_b_l = y_axis.multiply(-2).movePoint(f_t_l);
        Point3D f_b_r = x_axis.multiply(2).movePoint(f_b_l);
        Point3D b_b_r = z_axis.multiply(-2).movePoint(f_b_r);
        Point3D b_b_l = x_axis.multiply(-2).movePoint(b_b_r);
        Point3D b_t_l = y_axis.multiply(2).movePoint(b_b_l);
        Point3D b_t_r = x_axis.multiply(2).movePoint(b_t_l);
        // if contacting an edge
        if (delta_x < box.size_x / 2) // front/back
            collisionSpherePoint(pos_sph, rad, )
        if (delta_x < box.size_x / 2 && delta_z < box.size_z / 2 && delta_y < rad + box.size_y / 2) // top/bottom
            return y_axis;
        if (delta_y < box.size_y / 2 && delta_z < box.size_z / 2 && delta_x < rad + box.size_x / 2) // left/right
            return x_axis;
        if (delta_x > box.size_x / 2 || delta_y > box.size_y / 2 || delta_z > box.size_z / 2)
            return NULL;
        
        // return normal of reflection plane
        // shortcut: use vector from center to center
        // complicated: compare previous positions
        Vec3D old_to_old = Vec3D::createVector(box.old_pos, sph.old_pos);
        Vec3D old_x = box.p_rot->rot3D(Vec3D(1, 0, 0));
        Vec3D old_y = box.p_rot->rot3D(Vec3D(0, 1, 0));
        Vec3D old_z = box.p_rot->rot3D(Vec3D(0, 0, 1));

        float old_dx = old_x.project(old_to_old).length();
        float old_dy = old_y.project(old_to_old).length();
        float old_dz = old_z.project(old_to_old).length();

        // check if previous positions were already colliding. if so, dont register collision
        if (old_dx < box.size_x / 2 && old_dy < box.size_y / 2 && old_dz < box.size_z / 2)
            return NULL;
        
        if (old_dx < box.size_x / 2 && old_dy < box.size_y / 2)     // reflect off either front or back
        {
            return z_axis;
        }
        else if (old_dx < box.size_x / 2 && old_dz < box.size_z / 2)     // reflect off either top or bottom
        {
            return y_axis;
        }
        else if (old_dy < box.size_y / 2 && old_dz < box.size_z / 2)     // reflect off left top or right
        {
            return x_axis;
        }
        */
        // proper way: find which face the vector from old position to new position intersects with
        // current short-cut: use center to center vector
       // return b_to_s;
    }
    return Vec3D();
}
Vec3D Collider3D::collisionSphereSphere(Collider3D sph_1, Collider3D sph_2)
{
    Point3D pos_1 = sph_1.calculatePos();
    Point3D pos_2 = sph_2.calculatePos();
    Vec3D reflection_normal = Vec3D::createVector(pos_1, pos_2);
    float contact_length = sph_1.size_x + sph_2.size_x;
    float len = reflection_normal.length();
    if (len < ZERO)
        return Vec3D(1, 1, 1);
    if (len < contact_length)
        return reflection_normal.normalize().multiply(contact_length - len); // reflection normal is also the length needed to push them apart
    return Vec3D();
}

PhysicsObject3D::PhysicsObject3D()
{
    pos = Point3D();
    vel = Vec3D();
    acc = Vec3D();
    rot = Rot3D();
    rot_vel = 0;

    moveable = false;
    surface_friction = 0;
    acc_friction = 0;

    id = 0;
    collider = Collider3D();
    collided.clear(); 
}

PhysicsObject3D::PhysicsObject3D(float p_x, float p_y, float p_z, bool move, float f)
{
    pos = Point3D(p_x, p_y, p_z);
    vel = Vec3D();
    acc = Vec3D();
    rot = Rot3D();
    rot_vel = 0;

    moveable = move;
    surface_friction = f;
    acc_friction = 0;

    id = 0;
    collider = Collider3D();
    collided.clear(); 
}

Point3D PhysicsObject3D::getPos()
{
    return pos;
}

Vec3D PhysicsObject3D::getVel()
{
    return vel;
}

Rot3D PhysicsObject3D::getRot()
{
    return rot;
}
bool PhysicsObject3D::isMoveable()
{
    return moveable;
}

float PhysicsObject3D::getSurfaceFriction()
{
    return surface_friction;
}

int PhysicsObject3D::getId()
{
    return id;
}

std::vector<int> PhysicsObject3D::getCollided()
{
    return collided;
}

void PhysicsObject3D::setId(int object_id)
{
    id = object_id;
}

void PhysicsObject3D::setPosition(float x, float y, float z)
{
    pos = Point3D(x, y ,z);
}

void PhysicsObject3D::setVelocity(float x, float y, float z)
{
    vel = Vec3D(x, y ,z);
}

void PhysicsObject3D::setRotation(float x, float y, float z, float a)
{
    rot = Rot3D(x, y, z, a);
}

void PhysicsObject3D::setMoveable(bool move)
{
    moveable = move;
}

void PhysicsObject3D::setAccFriction(float f)
{
    acc_friction = f;
}

void PhysicsObject3D::addBoxCollider(float s_x, float s_y, float s_z, float off_x, float off_y, float off_z)
{
    collider = Collider3D(ColType::box, &pos, &rot, s_x, s_y, s_z, off_x, off_y, off_z);
}

void PhysicsObject3D::addCubeCollider(float size, float off_x, float off_y, float off_z)
{
    collider = Collider3D(ColType::box, &pos, &rot, size, size, size, off_x, off_y, off_z);
}

void PhysicsObject3D::addSphereCollider(float size, float off_x, float off_y, float off_z)
{
    collider = Collider3D(ColType::sphere, &pos, &rot, size, size, size, off_x, off_y, off_z);
}

void PhysicsObject3D::addAcceleration(float x, float y, float z)
{
    acc = acc.addVec(Vec3D(x, y, z));
}
// updatePhysics
// friction: applies a friction force slowing down the object. set to 0 if not wanted
// time: time passed since last call in ms
void PhysicsObject3D::updatePhysics(float time, bool gravity, std::vector<PhysicsObject3D *> objs)
{
    time = time / 1000;     // convert to seconds

    // ------------------- deceleration due to friction -------------------------
    acc_friction = std::min(acc_friction * time, 1.0f);

    vel = vel.multiply(1-acc_friction); // calculate change in velocity

    acc_friction = 0;

    // --------------------------- kinematics ------------------------------------
    if (gravity)    // add gravity
        acc.addVec(0, GRAVITY, 0);

    vel = vel.addVec(acc.multiply(time));    // add acc to vel

    // apply speed limit to avoid objects passing through each other when moving at high speed
    if (vel.length() > MAX_SPD)
        vel = vel.multiply(MAX_SPD / vel.length());
    
    // add vel to position
    pos = vel.multiply(time).movePoint(pos);

    // reset acceleration
    acc = Vec3D();

    // ------------------------ collisions with other objects -------------------------
    for (std::vector<PhysicsObject3D *>::iterator it = objs.begin(); it < objs.end(); it++)
    {
        if (!moveable && (*it)->isMoveable())      // if this object is immovable but the other object is
            (*it)->collisionImmovable(*this);
        else if (moveable && !(*it)->isMoveable()) // if this object is movable and other object is immovable
            collisionImmovable(**it);
        else if (moveable && (*it)->isMoveable())  // if both objects are movable
            collision(*it);
    }

    // ----------------------------------------------FLOOR PLACEHOLDER---------------------------------------------
    // create floor
    PhysicsObject3D the_floor = PhysicsObject3D(pos.x, -5, pos.z);      // create a floor object directly below object
    the_floor.addBoxCollider(10, 10, 10, 0, 0, 0);                      // results in a floor at -5
    collisionImmovable(the_floor);
}

void PhysicsObject3D::reflect(Vec3D ref_normal, float scale)
{
    vel = vel.addVec(ref_normal.project(vel).multiply(-2)).multiply(scale);
}

void PhysicsObject3D::collision(PhysicsObject3D *other_obj)
{
    Vec3D ref_normal = collider.collision(other_obj->collider);

    if (ref_normal.length() == 0)
        return;

    // ref_normal is normal of reflection plane that both objects should move away from
    // this means it is the direction the two objects should move in order to move away from each other
    // the length of ref_normal is the length the two objects should be separated by in order to stop overlapping
    pos = ref_normal.multiply(-0.5).movePoint(pos);
    other_obj->pos = ref_normal.multiply(0.5).movePoint(other_obj->pos);

    if (ref_normal.dotProd(vel) > 0)
        vel = vel.addVec(ref_normal.project(vel).multiply(-1));

    if (ref_normal.dotProd(other_obj->vel) < 0)
        other_obj->vel = other_obj->vel.addVec(ref_normal.project(other_obj->vel).multiply(-1));

    acc_friction = other_obj->getSurfaceFriction() * surface_friction;
    other_obj->setAccFriction(acc_friction);
}

void PhysicsObject3D::collisionImmovable(PhysicsObject3D other_obj)
{
    Vec3D ref_normal = collider.collision(other_obj.collider);
    //std::cout << ref_normal.y << "<<" << std::endl;
    if (ref_normal.length() == 0)
        return;

    // ref_normal is normal of reflection plane that both objects should move away from
    // this means it is the direction the two objects should move in order to move away from each other
    // the length of ref_normal is the length the two objects should be separated by in order to stop overlapping
    
    acc_friction = other_obj.getSurfaceFriction() * surface_friction;

    // Move point so that it no longer touches the immovable object
    pos = ref_normal.multiply(-1).movePoint(pos);
    // Modify velocity so that it is not going into the other object
    if (ref_normal.dotProd(vel) > 0)
        vel = vel.addVec(ref_normal.project(vel).multiply(-1.75 + acc_friction));
    
    
    
    
}

void PhysicsObject3D::addCollided(int id)
{
    collided.push_back(id);
    vel = Vec3D();
}