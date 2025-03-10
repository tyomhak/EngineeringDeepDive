#pragma once

#include "Object.h"

class Object2D : public Object
{
public:
    [[nodiscard]] auto createSplitPlane() const -> SplitPlane* override;
};

