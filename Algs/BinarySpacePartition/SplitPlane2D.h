#pragma once

#include "SplitPlane.h"

class Object;

class SplitPlane2D : public SplitPlane
{
public:
    auto split(const Object& object) const -> std::pair<Object*, Object*> override;
    auto isInFront(const Object& object) const -> bool override;
    auto isInBack(const Object& object) const -> bool override;
};