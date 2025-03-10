
#include "SplitPlane2D.h"
#include "Object2D.h"

auto SplitPlane2D::split(const Object& object) const -> std::pair<Object*, Object*>
{
    return {new Object2D(), new Object2D()};
}
auto SplitPlane2D::isInFront(const Object& object) const -> bool { return true; }
auto SplitPlane2D::isInBack(const Object& object) const -> bool { return false; }