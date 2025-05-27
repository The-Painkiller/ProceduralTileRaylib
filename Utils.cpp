#include "Utils.h"

Vector2 Utils::GridSize = Vector2{};
int Utils::Random(int floor, int ceilingNotIncluded)
{
    return rand() % (ceilingNotIncluded - floor) + floor;
}

bool Utils::IsWithinRange(const Vector2 target)
{
    return target.x >= 0 && target.y >= 0 && target.x < GridSize.x && target.y < GridSize.y;
}

bool operator==(const Vector2& lhs, const Vector2& rhs)
{
    return(lhs.x == rhs.x && lhs.y == rhs.y);
}
