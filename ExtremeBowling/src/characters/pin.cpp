#include "pin.h"

Pin::Pin(float inX, float inY, float inZ) : Asset(inX, inY, inZ)
{
    loadObj("pin", this->vertices, this->uvs, this->normals);
}

void Pin::collisionAnimation()
{

}