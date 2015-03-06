#include "MathFunc.h"
#include <math.h>

float ArcFunc(float x)
{
    if (x>=1.0) return -1.0;
    else return sqrt(1-(x-1)*(x-1));
}

float FArcFunc(float x)
{
    if (x>=1.0) return -1.0;
    else return 1-ArcFunc(1-x);
}
