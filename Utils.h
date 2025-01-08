#pragma once
#include <stdlib.h>
#include <time.h>
class Utils
{
public:
	Utils() { srand(time(NULL)); };
	static int Random(int floor, int ceilingNotIncluded);
};