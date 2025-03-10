#pragma once


class SplitPlane;

class Object
{
public:
    virtual ~Object() = default;

    [[nodiscard]] virtual auto createSplitPlane() const -> SplitPlane* = 0;
};



