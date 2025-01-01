#include "Utils.h"

int Utils::Random(int floor, int ceilingNotIncluded)
{
	return rand() % (ceilingNotIncluded - floor) + floor;
}