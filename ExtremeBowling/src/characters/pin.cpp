#include "pin.h"

Pin::Pin(float inX, float inY, float inZ) : Asset(inX, inY, inZ)
{
    this->graphics = Graphics("pin");
}

void Pin::collisionAnimation()
{

}