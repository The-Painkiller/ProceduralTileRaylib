#pragma once
#include <stdlib.h>
#include <time.h>
#include <raylib.h>
class Utils
{
public:
    inline Utils(const float gridSizeX, const float gridSizeY)
    {
        srand(time(NULL));
        GridSize = Vector2{ gridSizeX, gridSizeY };
    };
    static int Random(int floor, int ceilingNotIncluded);
    static bool IsWithinRange(const Vector2 target);

private:
    static Vector2 GridSize;
};
bool operator == (const Vector2& lhs, const Vector2& rhs);