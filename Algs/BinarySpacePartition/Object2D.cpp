
#include "Object2D.h"
#include "SplitPlane2D.h"


auto Object2D::createSplitPlane() const -> SplitPlane*
{
    return new SplitPlane2D();
}