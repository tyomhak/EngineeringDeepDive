#pragma once

#include <utility>


class Object;


class SplitPlane
{
public:
    virtual ~SplitPlane() = default;

    virtual auto split(const Object& object) const -> std::pair<Object*, Object*> = 0;
    virtual auto isInFront(const Object& object) const -> bool = 0;
    virtual auto isInBack(const Object& object) const -> bool = 0;
};