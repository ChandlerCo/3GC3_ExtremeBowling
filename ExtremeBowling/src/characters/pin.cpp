#include "pin.h"

Pin::Pin(float inX, float inY, float inZ) : Asset(inX, inY, inZ)
{
    loadObj("pin");
}

void Pin::collisionAnimation()
{

}